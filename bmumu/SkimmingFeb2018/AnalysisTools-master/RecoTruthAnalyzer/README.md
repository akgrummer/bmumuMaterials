#### How This Code Works

The code is running over the flat, candidate-wise ntuple (soft-link: MCbsmumuXntuple.root)
which must also contain truth decay information written by TruthDecayFinder 
(i.e. PDGid, mother, fdaughter, ldaughter, pt, eta, phi).
For each candidate it matches truth-to-reco information
for muons and (now commented out) the closest track to B candidate vertex.
Then it analyses origin(s) of the OS muon pair and assignes 
a TruthDecayCat category to each candidate.
This category can be used to dump selected candidates into a separate file.
which is specified (and located) as the input file appended with "_TruthDecayCat_XXX.root"
Also, bunch of histograms is produced; some of them are dumped into the truthInfoPlots.root file

#### How To Run The Code
In ROOT interpreter do:

`.L loader.C++`    
`.L extractReconstructedTruth.C++`    
`extractReconstructedTruth()`    

#### TODO for Run 2 analysis

Adjust truth decay variables to Run2 style (i.e. naming, [pT, eta, phi] to [px,py,pz])

