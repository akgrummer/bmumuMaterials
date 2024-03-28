import ROOT

#********************************************************************
#Returns period for a given run number
#********************************************************************
def GetPeriod(run_number):
    if run_number in range(276262 , 276954 + 1):
        return "2015_D"
    if run_number in range(278727 , 279928 + 1):
        return "2015_E"
    if run_number in range(279932 , 280422 + 1):
        return "2015_F"
    if run_number in range(280423 , 281075 + 1):
        return "2015_G"
    if run_number in range(281130 , 281411 + 1):
        return "2015_H"
    if run_number in range(281662 , 282482 + 1):
        return "2015_I"
    if run_number in range(282625 , 284484 + 1):
        return "2015_J"
    if run_number in range(286328 , 286474 + 1):
        return "2015_K"
    if run_number in range(286665 , 287983 + 1):
        return "2015_L"

    l_H_2016=[305359,309314,309346,310216]

    if run_number in range(289496 , 300287 + 1) and (run_number not in l_H_2016):
        return "2016_A"
    if run_number in range(300345 , 300908 + 1) and (run_number not in l_H_2016):
        return "2016_B"
    if run_number in range(301912 , 302393 + 1) and (run_number not in l_H_2016):
        return "2016_C"
    if run_number in range(302737 , 303560 + 1) and (run_number not in l_H_2016):
        return "2016_D"
    if run_number in range(303638 , 303892 + 1) and (run_number not in l_H_2016):
        return "2016_E"
    if run_number in range(303943 , 304494 + 1) and (run_number not in l_H_2016):
        return "2016_F"
    if run_number in range(305291 , 306714 + 1) and (run_number not in l_H_2016):
        return "2016_G"
    if run_number in range(307124 , 308084 + 1) and (run_number not in l_H_2016):
        return "2016_I"
    if run_number in range(308979 , 309166 + 1) and (run_number not in l_H_2016):
        return "2016_J"
    if run_number in range(309311 , 309759 + 1) and (run_number not in l_H_2016):
        return "2016_K"
    if run_number in range(310015 , 311481 + 1) and (run_number not in l_H_2016):
        return "2016_L"

    if run_number in l_H_2016:
        return "2016_H"

    print("Could not find run number %s" % run_number)

    return ""
#********************************************************************
#********************************************************************
