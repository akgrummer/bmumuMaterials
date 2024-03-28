#ifdef __CINT__

#include <string>
#include <vector>
#include <map>

#pragma link off all globals;
#pragma link off all functions;

#pragma link off all classes;
#pragma link off all typedefs;

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#pragma link C++ class std::vector< std::vector<int> >+;
#pragma link C++ class std::vector< std::vector<double> >+;

#pragma link C++ class std::map<std::string, int         >+;
#pragma link C++ class std::map<std::string, float       >+;
#pragma link C++ class std::map<std::string, double      >+;
#pragma link C++ class std::map<std::string, bool        >+;
#pragma link C++ class std::map<std::string, std::string >+;

#pragma link C++ class std::map<std::string, std::vector<int> >+;
#pragma link C++ class std::map<std::string, std::vector<float> >+;
#pragma link C++ class std::map<std::string, std::vector<double> >+;
#pragma link C++ class std::map<std::string, std::vector<bool> >+;
#pragma link C++ class std::map<std::string, std::vector<std::string> >+;

#endif

