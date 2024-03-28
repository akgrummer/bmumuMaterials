The root files in this folder contain the QLC and DDW weights for the different processes.
The naming scheme is quite easy to understand:
QLCfile_*   contains the QLC for the given process
DDWfile_*   contains the DDW for the given process


QLC:
each file contains 2 histograms (TH2D*), for instance QLCfile_BpToJpsiK.root contains
 h_QLC_BpJpsiK
 h_QLC_err_BpJpsiK
The first histogram contains the inverse of the weights, while the second contains the uncertainties on the first histogram. No correlation matrix is given in this case, because the QLC are uncorrelated between each other.
The histograms have |eta_B| on the X axis and pT(B) (MeV) on the y axis,
in order to get a weight or its uncertainty retrieve the content of the bin relative to the candidate.
The maximum of the Y axis is 100000 MeV (100 GeV), in case the pT is higher, use the last bin of the histogram --> ATTENTION: OVERFLOW BIN IS EMPTY

ATTENTION: as was done in Run1, the histograms contain the inverse of the weights, so they have to be applied as 1/QLC.




DDW:
each file contains 6 histograms (4 TH1D* and 2 TH2D*), for instance DDWfile_BpToJpsiK.root contains
h_DDWpt_even_BpJpsiK
h_DDWeta_even_BpJpsiK
h_DDWpt_odd_BpJpsiK
h_DDWeta_odd_BpJpsiK
h_covarianceDDW_even_BpJpsiK
h_covarianceDDW_odd_BpJpsiK

Histograms labelled even (odd) are obtained using the even (odd) MC and data events
h_DDWpt_*_BpJpsiK and h_DDWeta_*_BpJpsiK contain the 1D distribution of the DDWs.
In order to retrieve the weight (error), get the content (error) of the bin relative to the candidate.
Regarding the pT DDW, if the pT of the B candidate is higher than 100000 MeV (100 GeV) use the content of the last bin.
h_covarianceDDW_*_BpJpsiK is a TH2D* that contains the correlation matrix of the DDWs. Each bin on the X or Y axes refers to a DDW.




The file applyWeights.cpp contains an example on how to retrieve the QLC and the DDW from the files and how to calculate the result wegiht.
