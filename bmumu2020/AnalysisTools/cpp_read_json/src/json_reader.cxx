#include <iostream>

#include "json_reader.h"

//*****************************
json_reader::json_reader(std::string filename_pileup, std::string filename_grl)
{
    m_filename_pileup = filename_pileup;
    m_filename_grl    = filename_grl;

    boost::property_tree::read_json(m_filename_pileup, m_root_pileup);
    boost::property_tree::read_json(m_filename_grl,    m_root_grl);

    for (auto &it_grl : m_root_grl)
    {
	auto key = it_grl.first;
	auto child = m_root_grl.get_child(key);

	auto it_bg = child.begin();
	it_bg++;
	it_bg++;

	//std::cout << (*it_bg).second.data() << std::endl;
	std::cout << (*it_bg).second.get_value<float>() << std::endl;

	//for (auto &number : child)
	//{
	//    std::cout << number.second.data() << std::endl;
	//}
    }
}
//*****************************
json_reader::json_reader(std::string filename_particles)
{
    m_filename_particles = filename_particles;

    boost::property_tree::read_json(m_filename_particles, m_root_particles);
}
//*****************************
float json_reader::pileup(unsigned int run, unsigned int lumiblock)
{
    auto key = std::to_string(run) + std::string("_") + std::to_string(lumiblock);
    float pileup = 0;

    try
    {
	pileup = m_root_pileup.get<float>(key);
    }
    catch(boost::property_tree::ptree_bad_path)
    {
	std::cout << "Cannot find run " << run << " and lumiblock " << lumiblock << std::endl;
	return -3;
    }
    catch(boost::property_tree::ptree_bad_data)
    {
	std::cout << "Pileup value cannot be translated." << std::endl;
	return -3;
    }

    return pileup;
}
//*****************************
int json_reader::pass_grl(unsigned int run, unsigned int lumiblock)
{
    auto key = std::to_string(run) + std::string("_") + std::to_string(lumiblock);

    std::string s_pass_grl = "";

    try
    {
	s_pass_grl = m_root_pileup.get<std::string>(key);
    }
    catch(boost::property_tree::ptree_bad_path)
    {
	std::cout << "Cannot find run " << run << " and lumiblock " << lumiblock << std::endl;
	return -3;
    }
    catch(boost::property_tree::ptree_bad_data)
    {
	std::cout << "Pileup value cannot be translated." << std::endl;
	return -3;
    }

    auto b_pass_grl = atoi(s_pass_grl.c_str());

    return b_pass_grl;
}
//*****************************
void json_reader::print_events()
{
    unsigned int limit = 0;
    for(auto &root_entry : m_root_particles)
    {
	limit += 1;
	if (limit >= 100)
	{
	    break;
	}

	auto event_number = root_entry.first;
	auto event_branch = root_entry.second;

	std::cout << "Event number " << event_number << std::endl;
	
	if ( event_branch.size() <= 1 )
	    continue;

	for (auto &particle_entry: event_branch)
	{
	    auto particle_key    = particle_entry.first;
	    auto particle_branch = particle_entry.second;

	    std::cout << "    Particle key " << particle_key << std::endl;

	    for (auto &component_entry: particle_branch)
	    {
		auto component_key    = component_entry.first;
		auto component_branch = component_entry.second;

		std::cout << "         Component " << component_branch.get_value<float>() << std::endl;
	    }
	}
    }
}
//*****************************

