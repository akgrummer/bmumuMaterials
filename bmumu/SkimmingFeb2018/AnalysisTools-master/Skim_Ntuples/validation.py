import ROOT

import array

#--------------------------------------------------------
#Make trees with validation data
#--------------------------------------------------------
def Initialize():
    global INITIALIZED

    if not VALIDATE or INITIALIZED:
        return 0

    print("validation.py::Initialize::Will do validation")
    global val_file 
    global val_matching

    val_file=ROOT.TFile("validation.root", "recreate")
    val_matching=ROOT.TTree("matching", "")

    val_matching.Branch("matched" , matched , "matched/I")
    val_matching.Branch("dr_muon1", dr_muon1, "dr_muon1/F")
    val_matching.Branch("dr_muon2", dr_muon2, "dr_muon2/F")
    
    if FIRST_KAON:
        val_matching.Branch("dr_kaon", dr_kaon, "dr_kaon/F")
    
    if BOTH_KAONS:
        val_matching.Branch("dr_kaon1", dr_kaon1, "dr_kaon1/F")
        val_matching.Branch("dr_kaon2", dr_kaon2, "dr_kaon2/F")

    INITIALIZED=True
#--------------------------------------------------------
#Save entry
#--------------------------------------------------------
def Execute(l_distance, match):
    global val_matching

    if not VALIDATE or CLOSED:
        return 0

    size_tuple=len(l_distance)
    wrong_size = size_tuple < 2 or (FIRST_KAON and size_tuple != 3) or (BOTH_KAONS and size_tuple != 4)
    if wrong_size:
        print("Size of tuple is %d" % size_tuple)
        return 0

    matched[0]  = match
    dr_muon1[0] = l_distance[0]
    dr_muon2[0] = l_distance[1]

    if FIRST_KAON:
        dr_kaon[0] = l_distance[2]

    if BOTH_KAONS:
        dr_kaon1[0] = l_distance[2]
        dr_kaon2[0] = l_distance[3]

    val_file.cd()
    val_matching.Fill()
#--------------------------------------------------------
#Close everything
#--------------------------------------------------------
def Finalize():
    global CLOSED

    if not VALIDATE or CLOSED:
        print("validation.py::Won't save validation file.")
        print("     Validate: %d" % VALIDATE)
        print("     Closed: %d" % CLOSED)
        return 0

    print("validation.py::Finalize::Saving validation information.")

    val_file.cd()
    val_matching.Write()
    val_file.Close()

    CLOSED=True
#--------------------------------------------------------
#Make variables
#--------------------------------------------------------
VALIDATE=False
INITIALIZED=False
CLOSED=False
FIRST_KAON=False
BOTH_KAONS=False

matched =array.array("i", [0])
dr_muon1=array.array("f", [0])
dr_muon2=array.array("f", [0])
dr_kaon =array.array("f", [0])
dr_kaon1=array.array("f", [0])
dr_kaon2=array.array("f", [0])

val_file=ROOT.TFile()
val_matching=ROOT.TTree()
#--------------------------------------------------------
#--------------------------------------------------------

