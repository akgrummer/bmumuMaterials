#include <map>
#include <vector>
#include <string>

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;

#endif

#ifdef __CINT__
#pragma link C++ class std::map<std::string, int>+;
#pragma link C++ class std::map<std::string, float>+;
#pragma link C++ class std::map<std::string, std::string>+;
#pragma link C++ class std::map<std::string, std::vector<int> >+;
#pragma link C++ class std::map<std::string, std::vector<float> >+;
#pragma link C++ class std::map<std::string, std::vector<std::string> >+;
#endif
