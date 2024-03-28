#include "json_reader.h"

int main()
{
    json_reader obj_2015("../shared/pileup_2015.json", "../shared/grl_2015.json");

    //std::cout<<obj_2015.pileup(280950, 744)<<std::endl;
    //std::cout<<obj_2015.pass_grl(280950, 744)<<std::endl;

    //std::cout<<obj_2015.pileup(28950, 744)<<std::endl;
    //std::cout<<obj_2015.pass_grl(28950, 744)<<std::endl;

    //json_reader obj("particles.json");
    //obj.print_events();

    return 0;
}
