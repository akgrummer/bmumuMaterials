#include <TString.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>
#include <map>
#include <string>

typedef std::map<std::string, int> map_str_int;

double       PVWeights;
float        PRIVX_mu;
double       B_MUCALC_mass;
unsigned int run_number;
map_str_int *HLT_trigger = 0;
//---------------------------------------------------------------------------
bool pass_trigger(map_str_int *HLT_trigger, unsigned int run_number)
{
    std::string trigger="";
    if (run_number <= 284484)
    {
	trigger="HLT_mu6_mu4_bBmumu";
	auto found = HLT_trigger->find(trigger) != HLT_trigger->end();

	return found;
    }
    else if (run_number > 284484)
    {
	trigger="HLT_mu6_mu4_bBmumu_Lxy0";
	auto found = HLT_trigger->find(trigger) != HLT_trigger->end();

	return found;
    }

    std::cout << "pass_trigger::Found run number:" << run_number << std::endl;

    return 0;
}
//---------------------------------------------------------------------------
int main()
{
    TString SERVER = "root://eosatlas.cern.ch/";
    TString PATH="/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuRel21Prod1/ntup/";
    TString SAMPLE="skimmed_MC/Bmumu/v2/user.acampove.300430.BPHY8_FNTUP.e4889_e5984_a875_r9364_r9315_p3371_Bmumu.root";

    TString FILES=SERVER+PATH+SAMPLE;

    TChain ch_bsmumu("T_mv");
    ch_bsmumu.Add( Form("%s/*.root", FILES.Data() ) );

    {
	ch_bsmumu.SetBranchStatus("*", 0);
	ch_bsmumu.SetBranchStatus("PVWeights", 1);
	ch_bsmumu.SetBranchStatus("B_MUCALC_mass", 1);
	ch_bsmumu.SetBranchStatus("HLT_trigger", 1);
	ch_bsmumu.SetBranchStatus("run_number", 1);
	ch_bsmumu.SetBranchStatus("PRIVX_mu", 1);

	ch_bsmumu.SetBranchAddress("PVWeights", &PVWeights);
	ch_bsmumu.SetBranchAddress("B_MUCALC_mass", &B_MUCALC_mass);
	ch_bsmumu.SetBranchAddress("HLT_trigger", &HLT_trigger);
	ch_bsmumu.SetBranchAddress("run_number", &run_number);
	ch_bsmumu.SetBranchAddress("PRIVX_mu", &PRIVX_mu);
    }
    //-------------------------------------------------
    TH1F h_Bmass("h_Bmass", "", 100, 0, 0);
    TH1F h_mu("h_mu", "", 50, 0, 50);
    //-------------------------------------------------
    auto nentries = ch_bsmumu.GetEntries();
    std::cout << "Entries: " << nentries << std::endl;
    for (unsigned int i_entry = 0; i_entry < nentries; i_entry++)
    {
	//-----------------------
	if (i_entry % 10000 == 0)
	    std::cout << "Entry " << i_entry << "/" << nentries << std::endl;
	//-----------------------
	auto nbytes = ch_bsmumu.GetEntry(i_entry);
	if (nbytes <= 0)
	{
	    std::cout << "Could not load entry " << i_entry << std::endl;
	    continue;
	}

	//if (i_entry > 10)
	//    break;

	auto pass_trigg = pass_trigger(HLT_trigger, run_number);
	if (!pass_trigg)
	    continue;

        h_Bmass.Fill(B_MUCALC_mass, PVWeights);
	h_mu.Fill(PRIVX_mu, PVWeights);
    }
    //---------------------------------------------------
    {
	TCanvas c_Bmass("c_Bmass", "", 600, 600);
	h_Bmass.Draw();
	c_Bmass.SaveAs("Bmass.pdf");

	TCanvas c_mu("c_mu", "", 600, 600);
	h_mu.Draw();
	c_mu.SaveAs("mu.pdf");
    }
    //---------------------------------------------------
    return 0;
}

