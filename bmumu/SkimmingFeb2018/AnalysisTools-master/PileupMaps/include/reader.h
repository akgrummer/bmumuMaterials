#pragma once

#include <TString.h>
#include <TChain.h>
#include <TObject.h>

#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

typedef std::vector<TObject*> v_obj;

class reader
{
    public:
	reader(TString filename);
	double operator()(int sigma, unsigned int index);
	~reader();
    private:
	bool initialize();

	boost::property_tree::ptree m_root;
	TString m_filename;
	bool m_isInitialized;

	v_obj m_v_obj;
};
