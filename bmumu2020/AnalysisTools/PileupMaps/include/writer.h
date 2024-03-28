#pragma once

#include <TString.h>
#include <TChain.h>
#include <TObject.h>

#include <vector>
#include <set>

typedef std::vector<TObject*> v_obj;
typedef std::set<TString>     set_str;

//*************************************************************
#define IS_EMPTY(STR, MSG)              \
{                                       \
    if (STR=="")                        \
    {                                   \
        std::cout << MSG << std::endl;  \
        return false;                   \
    }                                   \
}   
//*************************************************************

class writer
{
    public:
	writer(TString directory);
	bool write(TString outputfile);
	~writer();
    private:
        TString      GetString(TString str, unsigned int i_str);
	bool         initialize();

	TString      m_directory;
	bool         m_isInitialized;
        set_str      m_pileup_str;
	v_obj        m_v_obj;

	double       m_PVWeights;
	double       m_PVWeights_up;
	double       m_PVWeights_down;

	unsigned int m_run_number;
	int          m_lumi_block;

	TChain      *m_chain;
};

