#### Description

These scripts are meant to be used to check the TruthDecay tree in the flat ntuples.

#### Usage

`find_unmatched.py`: This script takes the flat ntuples as input and does the geometric 
plus $`p_{T}`$ matching between the reco decay products of the $`B`$ candidate and the corresponding objects at truth
level. Some objects are not matched and information about them is dumped into a JSON file. This
file is then used to find out if the xAOD contains the matching truth objects.

the format of the JSON file is:
`
"event_number": [
    reco_particle_pt,
    reco_particle_eta,
    reco_particle_phi,
    reco_truth_dr,    (for closest truth match)
    type_of_particle  (they tend to be mostly kaons [32])
]
`
The script is meant to be run in the cluster. To use it do:

`python slurm.py PROCESS`

where `PROCESS=bsmumu/bplus/bsjpsiphi`. For this to work `slurm.py` has to have the line:

`d_arg["EXECUTABLE"] = "find_unmatched.py"`

so that the jobs run the right script. The output also contains trees with the following branches:
`
reco_pt
reco_eta
reco_phi
truth_pt
truth_eta
truth_phi
truth_ID
`

which contain the kinematic quantities of the reco decay products and the corresponding truth ones. You use this if
you want to study the distance between reco and truth matched quantities in $`p_{T}`$, $`\eta`$ and $`\phi`$.

The output should be written accordint to the  line:

`OUTDIR="/data/atlasb7/grid/data15a16/NTUP/No_Match/%s" % PROC_DIR`

in *slurm.py*.

If you want to test it locally (no cluster) do:

`python slurm.py test NEVENTS PROCESS`

where NEVENTS is the number of entries over which you want to test.

**Before running this test, source the setup.sh script**

`check_unmatched_xaod_lvl.py`: The JSON file produced by the script above is fed to the branch
`truth_decay_unmatched_events` of the package:

https://gitlab.cern.ch/RootCore_Pkgs/Tester

the result is a ROOT file with a tree containing information about which matches were found at 
xAOD level. This script takes that file and provides plots with relevant information.

`plot_matched_particles.py`: For the subset of particles that were successfully matched with a
truth particle you might want to make a distribution of $`\Delta p_{T}`$, $`\Delta \eta`$ and
$`\Delta \phi`$. This script does that by doing:

`python plot_matched_particles.py`

no arguments are needed, **but** you have to change the directories where the output of 
*find_unmatched.py* is located.

`classify_matched.py` Now you are done studying the cases where the reco candidate's decay products
could not be matched. You have to check the classification of the other candidates. In order to do
that you use this script. This script also runs with SLURM, because the input is pretty large.

To use it do:

`python slurm.py PROCESS`

Where PROCESS=bsmumu/bplus/bsjpsiphi. You can also do tests using:

`python slurm.py test NEVENTS PROCESS`

the output are root files with a **decays** tree with the following branches:

decay
Bmass
event_number

That will tell you the mass distribution for a given set of decays. Again, make sure that in
`slurm.py` you have:

d_arg["EXECUTABLE"] = "classify_matched.py"

in order to run in the cluster the right script.

The output should be written accordint to the  line:

`OUTDIR="/data/atlasb7/grid/data15a16/NTUP/Classification/%s" % PROC_DIR`

in *slurm.py*.

`hist_matched_candidates.py`: Now that you have all those ROOT files with the **decays** trees,
you need to make histograms, for the mass distributions of each of the decays. This script does that
with:

`python hist_matched_candidates.py PROCESS`

the histograms end up in *Root/PROCESS_components.root*. 
Also **adjust the path containing the right input files**.

`plot_matched_candidates.py`: Now you can take **some** or all of the histograms to make plots. This
is done by doing:

`python hist_matched_candidates.py PROCESS`

the histogramming and plotting are split into two scripts to make things easier.

`decay_distribution.py`: This script is used to get the cumulative distribution of the decay frequen
cy. It is called as:

`python decay_distribution.py PROCESS`

You might want to put a bunch of plots in slides made with latex. To get those `.tex` files you do:

`python make_slides.py` PROCESS

You run:

`python make_tables.py` PROCESS

in order to produce the `tex` files you will need for some of the tables in the presentation.

To copy all these files to the directory with the presentation files you do:

`source copy_files.sh FILETYPE`

where *FILETYPE=plots/slides*. All the paths will have to be changed so that it works for you, of course.
All this is just a template.

`print_cutflow.py`: This script is used to print an overview of the cutflow after going from
flat ntuples to trees. You run it with:

`python print_cutflow.py`

you **NEED** to update the paths:

`
NTUP_DIR="/nfs/monet_3/home/campoverde/Data/user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254/"
TREE_DIR="/data/atlasb7/grid/data15a16/NTUP/Classification/"

BSMUMU_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_Bmumu.root"
BPLUS_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BpJpsiKp.root"
BSJPSIPHI_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BsJpsiPhi.root"
`

