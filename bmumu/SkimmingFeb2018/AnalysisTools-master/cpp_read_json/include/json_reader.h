#include <string>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

class json_reader
{
    public:
	json_reader(std::string filename_pileup, std::string filename_grl);
        json_reader(std::string filename_particles);

	float pileup(unsigned int run, unsigned int lumiblock);
	int pass_grl(unsigned int run, unsigned int lumiblock);

	void print_events();

    private:
        std::string m_filename_pileup;
        std::string m_filename_grl;
	std::string m_filename_particles;

        boost::property_tree::ptree m_root_pileup;
        boost::property_tree::ptree m_root_grl;
        boost::property_tree::ptree m_root_particles;
};
