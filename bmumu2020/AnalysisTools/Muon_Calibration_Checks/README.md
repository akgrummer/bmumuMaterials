#### Description

These scripts are used to check the effects of the muon calibration.
Before running these scripts do:

`setupATLAS || setupATLASSi`
`lsetup root`

The names of the input files have to be defined in `settings.py`.

#### Usage

1. **kinematics_change.py**: This script is used to visualize the change in the values of
$`p_T`$, $`\eta`$ and $`\phi`$. You can set the tolerance inside the script. You will get the kinematic
variables with entries above the tolerance if `PREFIX="large_dev"` and the opposite if 
`PREFIX="small_dev"`. You have to make a `kinematics/` directory before running the stript.

2. **mass_resolution.py**: This script calculates the mass resolution before and after calibration.
It has to be used like:

`python mass_resolution.py SETTING`

where `SETTING=Bsmumu/Bplus`.
3. **muon_pt_resolution.py**: This script is used to study the $`p_T`$ resolution of muons. It has to
be called as:

`python muon_pt_resolution.py SETTING`

where `SETTING=Bsmumu/Bplus`.
4. **fit_responses.py**: This script is used to fit the $`p_T`$ response. It takes as input the
workspace produced by `muon_pt_resolution.py`.

