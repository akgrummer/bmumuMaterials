#include <reader.h>
#include <writer.h>

#include <iostream>

int main()
{
    TString path="/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuRel21Prod1/ntup/skimmed_MC/Bsmumu/v2/";
    TString sample="user.acampove.300426.BPHY8_FNTUP.e4889_e5984_a875_r9364_r9315_p3371_Bmumu.root/";

    //specify directory containing root files.
    writer wt(path+sample);
    //the information needed will go into a JSON file.
    wt.write("output.json");

    //Specify name of the JSON file.
    reader rd("output.json");
    //Specify systematic variation (+1, 0, -1), run number and lumiblock number.
    //the function will retrieve the pileup weight.
    auto up = rd(+1, 589);
    auto nm = rd( 0, 589);
    auto dn = rd(-1, 589);

    std::cout << up << std::endl;
    std::cout << nm << std::endl;
    std::cout << dn << std::endl;

    return 0;
}
