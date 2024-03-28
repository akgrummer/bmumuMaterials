#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <TKey.h>

#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
	std::cout << "Need three arguments." << std::endl;
	return 1;
    }

    TString FILENAME(argv[1]);
    TString OCHANNEL(argv[2]);
    TString NCHANNEL(argv[3]);

    TFile ifile(FILENAME);
    auto idir  =(TDirectoryFile*)ifile.Get("PileupReweighting");

    if(!idir)
    {
	std::cout << "PileupReweighting not found." << std::endl;
	return 1;
    }

    auto l_key = idir->GetListOfKeys();
    if(!l_key)
    {
	std::cout << "List of keys not found." << std::endl;
	return 1;
    }

    TH1  *ihist=0;
    TTree *itree=0;

    TIter it_key(l_key);
    while(TObject *key = it_key())
    {
	TObject *obj = ((TKey*)key)->ReadObj();
	
	auto tmp_tree = dynamic_cast<TTree*>(obj);
	if (tmp_tree)
	{
	    itree=tmp_tree;
	    std::cout << "Tree found" << std::endl;
	    continue;
	}
	auto tmp_hist = dynamic_cast<TH1*>(obj);
	if (tmp_hist)
	{
	    ihist=tmp_hist;
	    std::cout << "Histogram found" << std::endl;
	    continue;
	}
    }

    if(!itree)
    {
	std::cout << "Input tree not found." << std::endl;
	return 1;
    }

    if(!ihist)
    {
	std::cout << "Input histogram not found." << std::endl;
	return 1;
    }

    TString ihist_name = ihist->GetName();
    TString ohist_name = ihist_name.ReplaceAll(OCHANNEL, NCHANNEL);

    auto otree=itree->CloneTree(0);
    auto ohist=(TH1D*)ihist->Clone(ohist_name);
    ohist->SetTitle(ohist_name);

    std::vector<unsigned int> *period_ends   = 0;
    std::vector<unsigned int> *period_starts = 0;
    char hist_name[28];
    int channel;

    itree->SetBranchAddress("Channel", &channel);
    itree->SetBranchAddress("PeriodEnds", &period_ends);
    itree->SetBranchAddress("PeriodStarts", &period_starts);
    itree->SetBranchAddress("HistName", hist_name);

    auto nentries = itree->GetEntries();
    std::cout << nentries << std::endl;
    for (int i_entry = 0; i_entry < nentries; i_entry++)
    {
	itree->GetEntry(i_entry);

	TString hname(hist_name);
	hname = hname.ReplaceAll(OCHANNEL, NCHANNEL);
	auto cc_hname = hname.Data();
	auto len = strlen(cc_hname);
	strcpy(hist_name, cc_hname);

	channel = NCHANNEL.Atoi();

	otree->Fill();
    }

    TFile ofile("prw_file.root", "recreate");
    TDirectoryFile dir("PileupReweighting", "");
    dir.Add(otree);
    dir.Add(ohist);
    dir.Write();
    ofile.Close();

    return 0;
}

