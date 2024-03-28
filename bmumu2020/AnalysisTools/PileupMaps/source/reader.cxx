#include <reader.h>

#include <TChain.h>

#include <iostream>
#include <fstream>

namespace pt = boost::property_tree;
//---------------------------------------
reader::reader(TString filename)
{
    m_filename=filename;
    m_isInitialized=false;
}
//---------------------------------------
bool reader::initialize()
{
    std::fstream ifile(m_filename.Data());
    if (!ifile.is_open())
    {
	std::cout << "reader::initialize::Cannot open " << m_filename << std::endl;
	return false;
    }

    boost::property_tree::read_json(m_filename.Data(), m_root);

    m_isInitialized=true;

    return true;
}
//---------------------------------------
double reader::operator()(int sigma, unsigned int index)
{
    if (!m_isInitialized)
	initialize();
    //-----------------------------------------
    TString syst;
    if (sigma == 1)
    {
	syst="up";
    }
    else if (sigma == 0)
    {
	syst="nm";
    }
    else if (sigma == -1)
    {
	syst="dn";
    }
    else
    {
	std::cout << "reader::operator()::Invalid syatematic variation " << sigma << std::endl;
	return 0;
    }
    //-----------------------------------------
    TString key = Form("%d.%s", index, syst.Data());

    double value;
    try
    {
	value=m_root.get<double>(key.Data());
    }
    catch(boost::property_tree::ptree_bad_path)
    {
	std::cout << "Cannot find systematic variation " << syst << std::endl; 
	std::cout << "Key: " << key << std::endl;
	return 0;
    }
    //-----------------------------------------
    return value;
}
//---------------------------------------
reader::~reader()
{
    for (auto obj : m_v_obj)
    {
	if (obj)
	    delete obj;

	obj = 0;
    }
}
//---------------------------------------

