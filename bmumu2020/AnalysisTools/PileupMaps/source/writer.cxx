#include <writer.h>

#include <TChain.h>
#include <TObjString.h>

#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;
//---------------------------------------
writer::writer(TString directory)
{
    m_directory=directory;
    m_isInitialized=false;
    m_chain=0;
}
//---------------------------------------
bool writer::initialize()
{
    m_chain = new TChain("T_mv");
    m_v_obj.push_back(m_chain);

    m_chain->Add( Form("%s/*.root", m_directory.Data()) );

    auto ntrees = m_chain->GetNtrees();
    if (ntrees == 0)
    {
	std::cout << "writer::initialize::Found " << ntrees << " files." << std::endl;
	return false;
    }

    {
	m_chain->SetBranchStatus("*", 0);
	m_chain->SetBranchStatus("run_number", 1);
	m_chain->SetBranchStatus("lumi_block", 1);
	m_chain->SetBranchStatus("PVWeights", 1);
	m_chain->SetBranchStatus("PVWeights_up", 1);
	m_chain->SetBranchStatus("PVWeights_down", 1);

	m_chain->SetBranchAddress("run_number", &m_run_number);
	m_chain->SetBranchAddress("lumi_block", &m_lumi_block);
	m_chain->SetBranchAddress("PVWeights", &m_PVWeights);
	m_chain->SetBranchAddress("PVWeights_up", &m_PVWeights_up);
	m_chain->SetBranchAddress("PVWeights_down", &m_PVWeights_down);
    }

    m_isInitialized = true;

    return true;
}
//---------------------------------------
bool writer::write(TString outputfile)
{
    if (!m_isInitialized)
	initialize();
    //-----------------------------------------
    pt::ptree root;
    //-----------------------------------------
    auto nentries = m_chain->GetEntries();
    std::cout << "writer::read::Found " << nentries << " entries." << std::endl;

    for (unsigned int i_entry = 0; i_entry < nentries; i_entry ++)
    {
	auto nbytes=m_chain->GetEntry(i_entry);
	if (nbytes == 0)
	{
	    std::cout << "writer::read::Cannot get entry " << i_entry << std::endl;
	    continue;
	}

	if (i_entry % 100000 == 0)
	    std::cout << "writer::read::Entry " << i_entry << "/" << nentries << std::endl; 

        TString pileup_str=Form("%.5f_%.5f_%.5f", m_PVWeights, m_PVWeights_up, m_PVWeights_down);
        m_pileup_str.insert(pileup_str);
    }

    unsigned int i_entry=0;
    for (auto pileup_str : m_pileup_str)
    {
        i_entry++;

        auto key_nm = Form("%d.nm", i_entry);
        auto key_up = Form("%d.up", i_entry);
        auto key_dn = Form("%d.dn", i_entry);

        auto pileup_n_str= GetString(pileup_str, 0);
        auto pileup_u_str= GetString(pileup_str, 1);
        auto pileup_d_str= GetString(pileup_str, 2);

        IS_EMPTY(pileup_n_str, Form("writer::write::Substring %d is empty", 0) );
        IS_EMPTY(pileup_u_str, Form("writer::write::Substring %d is empty", 1) );
        IS_EMPTY(pileup_d_str, Form("writer::write::Substring %d is empty", 2) );

        auto pileup_n = atof(pileup_n_str.Data());
        auto pileup_u = atof(pileup_u_str.Data());
        auto pileup_d = atof(pileup_d_str.Data());

        root.put(key_nm, pileup_n_str.Data() );
        root.put(key_up, pileup_u_str.Data() );
        root.put(key_dn, pileup_d_str.Data() );
    }

    pt::write_json(outputfile.Data(), root);

    return true;
}
//---------------------------------------
TString writer::GetString(TString str, unsigned int i_str)
{
    auto arr_str = str.Tokenize("_");

    if (!arr_str)
    {
        std::cout << "writer::GetString::Cannot split " << str << " with underscores." << std::endl;
        return "";
    }

    auto nsubstr=arr_str->GetEntries();
    if (nsubstr != 3)
    {
        std::cout << "writer::GetString::Found " << nsubstr << " substrings in " << str << std::endl;
        return "";
    }

    if (nsubstr < i_str + 1)
    {
        std::cout << "writer::GetString::Cannot retrieve " << i_str << " substring out of " << nsubstr << std::endl;
        return "";
    }

    auto obj = arr_str->At(i_str);
    auto obj_str = dynamic_cast<TObjString*>(obj);

    if (!obj_str)
    {
        std::cout << "writer::GetString::Cannot retrieve substring for " << str << std::endl;
        return "";

    }

    return obj_str->String();
}
//---------------------------------------
writer::~writer()
{
    for (auto obj : m_v_obj)
    {
	if (obj)
	    delete obj;

	obj = 0;
    }
}
//---------------------------------------

