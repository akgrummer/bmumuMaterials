#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasUtils.h"
void CreateGraphs(TString whichSet){
SetAtlasStyle();
TCanvas* c1 = new TCanvas("c1", "c1",0.,0., 800, 600);
struct SepInfo{
    // TString name;
    Double_t SepValue;
    SepInfo(Double_t _SepValue)
    {
        SepValue = _SepValue;
    }
    };
    // map<TString, SepInfo> NewNtuples ={
    //     {"N^{clos}_{trk} ACK", SepInfo(0.408700)},
    //     {"DOCA ACK", SepInfo(0.387300)},
    //     {"B Iso ACH", SepInfo(0.353700)},
    //     //Custom,
    //     {"N^{clos}_{trk} BEL Custom", SepInfo(0.438800)},
    //     {"DOCA BEL Custom", SepInfo(0.391600)},
    //     {"B Iso BEJ Custom", SepInfo(0.381400)},
    //     //loose,
    //     {"N^{clos}_{trk} BGL Loose", SepInfo(0.438300)},
    //     {"DOCA BGL Loose", SepInfo(0.391100)},
    //     {"B Iso BGJ Loose", SepInfo(0.386700)},
    //     //Run1,
    //     {"B Iso BDI As in Run 1", SepInfo(0.388600)},
    //     //rest,
    //     {"#Delta R", SepInfo(0.573100)},
    //     {"|#alpha_{2D}|", SepInfo(0.557900)},
    //     {"log(#chi^{2}_{#mu,xPV})", SepInfo(0.436400)},
    //     {"|d_{0}|^{min} sig.", SepInfo(0.393900)},
    //     {"L_{xy}", SepInfo(0.367000)},
    //     {"log(#chi^{2}_{xy})", SepInfo(0.298300)},
    //     {"|d_{0}|^{max} sig.", SepInfo(0.168200)},
    //     {"|IP_{B}^{3D}|", SepInfo(0.138200)},
    //     {"DOCA_{#mu#mu}", SepInfo(0.067320)},
    //     {"P^{min}_{L}", SepInfo(0.008266)},
    //     {"|#Delta #phi_{#mu#mu}|", SepInfo(0.005445)},
    //     {"p^B_{T}", SepInfo(0.004634)}


struct DescriptorLoc{
    // TString name;
    Double_t LocX;
    Double_t LocY;
    Double_t align;
    DescriptorLoc(Double_t _LocX, Double_t _LocY, Double_t _align)
    {
        LocX = _LocX;
        LocY = _LocY;
        align = _align;
    }
    };
    map<TString, DescriptorLoc> LabelPositions ={
        {"N^{clos}_{trk} ACK", DescriptorLoc(0.4266149,0.4178316, 13)},
        {"DOCA ACK", DescriptorLoc(0.3496762,0.4249862, 13)},
        {"B Iso ACH", DescriptorLoc(0.3618707,0.3494634, 13)},
        //Custom,
        {"N^{clos}_{trk} BEL Custom", DescriptorLoc(0.4027015,0.5008255, 13)},
        {"DOCA BEL Custom", DescriptorLoc(0.3132862,0.4550358, 13)},
        {"B Iso BEJ Custom", DescriptorLoc(0.2633649,0.3806687, 13)},
        //loose,
        {"N^{clos}_{trk} BGL Loose", DescriptorLoc(0.4027015,0.4807925, 13)},
        {"DOCA BGL Loose", DescriptorLoc(0.3195245,0.4407265, 13)},
        {"B Iso BGJ Loose", DescriptorLoc(0.2719306,0.4133599, 13)},
        //Run1,
        {"B Iso BDI As in Run 1", DescriptorLoc(0.2494456,0.3970143, 13)},
        //rest,
        {"#Delta R", DescriptorLoc(0.5960881,0.593836, 13)},
        {"|#alpha_{2D}|", DescriptorLoc(0.5773732,0.5709411, 13)},
        {"log(#chi^{2}_{#mu,xPV})", DescriptorLoc(0.4474092,0.4421574, 13)},
        {"|d_{0}|^{min} sig.", DescriptorLoc(0.3964632,0.3877821, 13)},
        {"L_{xy}", DescriptorLoc(0.382947,0.3763346, 13)},
        {"log(#chi^{2}_{xy})", DescriptorLoc(0.3128539,0.3020799, 13)},
        {"|d_{0}|^{max} sig.", DescriptorLoc(0.1770839,0.1745735, 13)},
        {"|IP_{B}^{3D}|", DescriptorLoc(0.151091,0.1473858, 13)},
        {"DOCA_{#mu#mu}", DescriptorLoc(0.08454944,0.07727023, 13)},
        {"P^{min}_{L}", DescriptorLoc(0.02887837,0.02552285, 13)},
        {"|#Delta #phi_{#mu#mu}|", DescriptorLoc(-0.0241061, 0.0225509, 13)},
        {"p^{B}_{T}", DescriptorLoc(0.02031265,0.05672813, 13)}
    };
    map<TString, DescriptorLoc> LabelPositionsRun1 ={
        // {"DOCA old nTuples prev. def. (Iskander)", DescriptorLoc(0.3356,0.266249, 13)},
        // {"DOCA old nTuples prev. def. (Aidan)", DescriptorLoc(0.3356,0.30637, 13)},
        {"DOCA ACK old nTuples prev. def.", DescriptorLoc(0.3356,0.30637, 13)},
        {"N^{clos}_{trk} ACK", DescriptorLoc(0.322187,0.4341483, 13)},
        {"DOCA ACK", DescriptorLoc(0.2611727,0.3881593, 13)},
        {"B Iso ACH", DescriptorLoc(0.4009509,0.3659066, 13)},
        //Custom,
        {"N^{clos}_{trk} BEL Custom", DescriptorLoc(0.2877971,0.4801374, 13)},
        {"DOCA BEL Custom", DescriptorLoc(0.2278922,0.4193132, 13)},
        {"B Iso BEJ Custom", DescriptorLoc(0.3998415,0.3881593, 13)},
        //loose,
        {"N^{clos}_{trk} BGL Loose", DescriptorLoc(0.2933439,0.4593681, 13)},
        {"DOCA BGL Loose", DescriptorLoc(0.2323296,0.404478, 13)},
        {"B Iso BGJ Loose", DescriptorLoc(0.3998415,0.4163462, 13)},
        //Run1,
        {"B Iso BDI As in Run 1", DescriptorLoc(0.3998415,0.4029945, 13)},
        //rest,
        {"#Delta R", DescriptorLoc(0.5396197,0.6003022, 13)},
        {"|#alpha_{2D}|", DescriptorLoc(0.52187,0.5750824, 13)},
        {"log(#chi^{2}_{#mu,xPV})", DescriptorLoc(0.4042789,0.4667857, 13)},
        {"|d_{0}|^{min} sig.", DescriptorLoc(0.322187,0.3896429, 13)},
        {"L_{xy}", DescriptorLoc(0.366561,0.3748077, 13)},
        {"log(#chi^{2}_{xy})", DescriptorLoc(0.2512658,0.3271739, 13)},
        {"|d_{0}|^{max} sig.", DescriptorLoc(0.1035865,0.1874931, 13)},
        {"|IP_{B}^{3D}|", DescriptorLoc(0.07582723,0.1533159, 13)},
        {"DOCA_{#mu#mu}", DescriptorLoc(0.02030869,0.09536324, 13)},
        {"P^{min}_{L}", DescriptorLoc(0.00920498,0.04632637, 13)},
        {"|#Delta #phi_{#mu#mu}|", DescriptorLoc(-0.0241061,0.0225509, 13)},
        {"p^{B}_{T}", DescriptorLoc(0.03585388,0.03592461, 13)}
    };
      // tex = new TLatex(0.322187,0.4341483,"N^{clos}_{trk} ACK");
      // tex = new TLatex(0.2611727,0.3881593,"DOCA ACK");
      // tex = new TLatex(0.4009509,0.3659066,"B Iso ACH");

      // tex = new TLatex(0.2877971,0.4801374,"N^{clos}_{trk} BEL Custom");
      // tex = new TLatex(0.2278922,0.4193132,"DOCA BEL Custom");
      // tex = new TLatex(0.3998415,0.3881593,"B Iso BEJ Custom");

      // tex = new TLatex(0.2933439,0.4593681,"N^{clos}_{trk} BGL Loose");
      // tex = new TLatex(0.2323296,0.404478,"DOCA BGL Loose");
      // tex = new TLatex(0.3998415,0.4163462,"B Iso BGJ Loose");

      // tex = new TLatex(0.3998415,0.4029945,"B Iso BDI As in Run 1");

      // tex = new TLatex(0.5396197,0.6003022,"#Delta R");
      // tex = new TLatex(0.52187,0.5750824,"|#alpha_{2D}|");
      // tex = new TLatex(0.4042789,0.4667857,"log(#chi^{2}_{#mu,xPV})");
      // tex = new TLatex(0.322187,0.3896429,"|d_{0}|^{min} sig.");
      // tex = new TLatex(0.366561,0.3748077,"L_{xy}");
      // tex = new TLatex(0.2512658,0.3271739,"log(#chi^{2}_{xy})");
      // tex = new TLatex(0.1035865,0.1874931,"|d_{0}|^{max} sig.");
      // tex = new TLatex(0.07582723,0.1533159,"|IP_{B}^{3D}|");
      // tex = new TLatex(0.02030869,0.09536324,"DOCA_{#mu#mu}");
      // tex = new TLatex(0.00920498,0.04632637,"P^{min}_{L}");
      // tex = new TLatex(-0.0241061,0.0225509,"|#Delta #phi_{#mu#mu}|");
      // tex = new TLatex(0.03585388,0.03592461,"p^{B}_{T}");

struct SepInfo3{
    // TString name;
    Double_t SepValue1;
    Double_t SepValue2;
    Double_t SepValue3;
    SepInfo3(Double_t _SepValue1, Double_t _SepValue2, Double_t _SepValue3)
    {
        SepValue1 = _SepValue1;
        SepValue2 = _SepValue2;
        SepValue3 = _SepValue3;
    }
    };
// partial run 2, 
// BDT1 separation, BDT2 separation, BDT3 separation
    map<TString, SepInfo3> oldnTuples ={
        {"N^{clos}_{trk}", SepInfo3(0.42660, 0.42560, 0.42590)},
        {"DOCA_{xtrk,loose,pt>0.5}", SepInfo3(0.31300, 0.32220, 0.32260)},
        {"B Isolation (I^{B}_{0.7})", SepInfo3(0.36160, 0.36200, 0.36650)},
        {"#Delta R", SepInfo3(0.59710, 0.59830, 0.60000)},
        {"|#alpha_{2D}|", SepInfo3(0.57890, 0.57890, 0.57570)},
        {"log(#chi^{2}_{#mu,xPV})", SepInfo3(0.44190, 0.43950, 0.44070)},
        {"|d_{0}|^{min} sig.", SepInfo3(0.39140, 0.38930, 0.39130)},
        {"L_{xy}", SepInfo3(0.38910, 0.38570, 0.38690)},
        {"log(#chi^{2}_{xy})", SepInfo3(0.30730, 0.30520, 0.30630)},
        {"|d_{0}|^{max} sig.", SepInfo3(0.17080, 0.16850, 0.17020)},
        {"|IP_{B}^{3D}|", SepInfo3(0.15100, 0.14910, 0.15060)},
        {"DOCA_{#mu#mu}", SepInfo3(0.08282, 0.08036, 0.08507)},
        {"P^{min}_{L}", SepInfo3(0.03469, 0.03507, 0.03403)},
        {"|#Delta #phi_{#mu#mu}|", SepInfo3(0.02661, 0.02697, 0.02672)},
        {"p^B_{T}", SepInfo3(0.04200, 0.04302, 0.04204)}
    };

// full run 2, 
// BDT1 separation, BDT2 separation, BDT3 separation
    map<TString, SepInfo3> newNtuplesSep ={
        {"DOCA ACK", SepInfo3(0.385400, 0.385300, 0.387900)},
        {"N^{clos}_{trk} ACK", SepInfo3(0.409500, 0.408400, 0.408800)},
        {"B Iso ACH", SepInfo3(0.352400, 0.353400, 0.357300)},
        //Custom,
        {"DOCA BEL Custom", SepInfo3(0.389900, 0.388900, 0.392000)},
        {"N^{clos}_{trk} BEL Custom", SepInfo3(0.439700, 0.439100, 0.438900)},
        {"B Iso BEJ Custom", SepInfo3(0.379500, 0.381200, 0.385100)},
        //loose,
        {"DOCA BGL Loose", SepInfo3(0.389200, 0.388500, 0.391700)},
        {"N^{clos}_{trk} BGL Loose", SepInfo3(0.438600, 0.438300, 0.438800)},
        {"B Iso BGJ Loose", SepInfo3(0.385000, 0.386400, 0.390700)},
        //Run1,
        {"B Iso BDI As in Run 1", SepInfo3(0.387000, 0.388200, 0.392700)},
        {"#Delta R", SepInfo3(0.571500, 0.573800, 0.574200)},
        {"|#alpha_{2D}|", SepInfo3(0.558900, 0.559000, 0.556800)},
        {"log(#chi^{2}_{#mu,xPV})", SepInfo3(0.438600, 0.436500, 0.437000)},
        {"|d_{0}|^{min} sig.", SepInfo3(0.395600, 0.391700, 0.394000)},
        {"L_{xy}", SepInfo3(0.370400, 0.365500, 0.367800)},
        {"log(#chi^{2}_{xy})", SepInfo3(0.299600, 0.297200, 0.298400)},
        {"|d_{0}|^{max} sig.", SepInfo3(0.169800, 0.167300, 0.169000)},
        {"|IP_{B}^{3D}|", SepInfo3(0.138900, 0.138600, 0.139000)},
        {"DOCA_{#mu#mu}", SepInfo3(0.067970, 0.066180, 0.070360)},
        {"P^{min}_{L}", SepInfo3(0.008564, 0.008699, 0.008293)},
        {"|#Delta #phi_{#mu#mu}|", SepInfo3(0.005495, 0.005609, 0.005725)},
        {"p^B_{T}", SepInfo3(0.004873, 0.005444, 0.004931)}
    };
// new nTuples done with consistent weighting
//with MC Weights, without MC weights, zero place holder
map<TString, SepInfo3> NewNtuplesCorrected ={
        // {"DOCA old nTuples prev. def. (Iskander)", SepInfo3(0.2629, 0., 0.)},
        {"DOCA ACK old nTuples prev. def. (Aidan)", SepInfo3(0.31300, 0., 0.)},
        {"N^{clos}_{trk} ACK", SepInfo3(0.421700, 0.407700, 0.)},
        {"DOCA ACK", SepInfo3(0.399800, 0.386100, 0.)},
        {"B Iso ACH", SepInfo3(0.360300, 0.350100, 0.)},
        //Custom,
        {"N^{clos}_{trk} BEL Custom", SepInfo3(0.451200, 0.435800, 0.)},
        {"DOCA BEL Custom", SepInfo3(0.404000, 0.389600, 0.)},
        {"B Iso BEJ Custom", SepInfo3(0.392900, 0.376500, 0.)},
        //loose,
        {"N^{clos}_{trk} BGL Loose", SepInfo3(0.449700, 0.435600, 0.)},
        {"DOCA BGL Loose", SepInfo3(0.403300, 0.389700, 0.)},
        {"B Iso BGJ Loose", SepInfo3(0.397100, 0.381100, 0.)},
        //Run1,
        {"B Iso BDI As in Run 1", SepInfo3(0.396100, 0.379300, 0.)},
        //rest,
        {"#Delta R", SepInfo3(0.591100, 0.569200, 0.)},
        {"|#alpha_{2D}|", SepInfo3(0.572000, 0.558900, 0.)},
        {"log(#chi^{2}_{#mu,xPV})", SepInfo3(0.439900, 0.437000, 0.)},
        {"|d_{0}|^{min} sig.", SepInfo3(0.393800, 0.394200, 0.)},
        {"L_{xy}", SepInfo3(0.381000, 0.368100, 0.)},
        {"log(#chi^{2}_{xy})", SepInfo3(0.305300, 0.299000, 0.)},
        {"|d_{0}|^{max} sig.", SepInfo3(0.171400, 0.168300, 0.)},
        {"|IP_{B}^{3D}|", SepInfo3(0.145300, 0.133800, 0.)},
        {"DOCA_{#mu#mu}", SepInfo3(0.075810, 0.067860, 0.)},
        {"p^B_{T}", SepInfo3(0.022770, 0.005916, 0.)},
        {"P^{min}_{L}", SepInfo3(0.022700, 0.010070, 0.)},
        {"|#Delta #phi_{#mu#mu}|", SepInfo3(0.012440, 0.005971, 0.)}
    };

//re-compute for old nTuples, with new DOCA definition, 
//with MC Weights, without MC weights, zero place holder
map<TString, SepInfo3> oldnTuplesRedone ={
    {"DOCA ACK old nTuples prev. def. (Aidan)", SepInfo3(0.31300, 0., 0.)},
    {"N^{clos}_{trk}", SepInfo3(0.420200, 0.407200, 0.)},
    {"DOCA_{xtrk,loose,pt>0.5}", SepInfo3(0.395600, 0.383700, 0.)},
    {"B Isolation (I^{B}_{0.7})", SepInfo3(0.362500, 0.352200, 0.)},
    {"#Delta R", SepInfo3(0.591000, 0.569800, 0.)},
    {"|#alpha_{2D}|", SepInfo3(0.570100, 0.556600, 0.)},
    {"log(#chi^{2}_{#mu,xPV})", SepInfo3(0.439700, 0.437200, 0.)},
    {"|d_{0}|^{min} sig.", SepInfo3(0.392700, 0.393900, 0.)},
    {"L_{xy}", SepInfo3(0.380200, 0.367600, 0.)},
    {"log(#chi^{2}_{xy})", SepInfo3(0.304700, 0.298800, 0.)},
    {"|d_{0}|^{max} sig.", SepInfo3(0.170700, 0.168400, 0.)},
    {"|IP_{B}^{3D}|", SepInfo3(0.146200, 0.133900, 0.)},
    {"DOCA_{#mu#mu}", SepInfo3(0.077490, 0.068450, 0.)},
    {"p^B_{T}", SepInfo3(0.023880, 0.005984, 0.)},
    {"P^{min}_{L}", SepInfo3(0.023530, 0.009807, 0.)},
    {"|#Delta #phi_{#mu#mu}|", SepInfo3(0.012820, 0.005714, 0.)}
};

map<TString, SepInfo3> Run1nTuples ={
    {"N^{clos}_{trk}", SepInfo3(0.371, 0., 0.)},
    {"DOCA_{xtrk,loose,pt>0.5}", SepInfo3(0.3213, 0., 0.)},
    {"B Isolation (I^{B}_{0.7})", SepInfo3(0.3905, 0., 0.)},
    {"#Delta R", SepInfo3(0.5327, 0., 0.)},
    {"|#alpha_{2D}|", SepInfo3(0.5149, 0., 0.)},
    {"log(#chi^{2}_{#mu,xPV})", SepInfo3(0.4126, 0., 0.)},
    {"|d_{0}|^{min} sig.", SepInfo3(0.3623, 0., 0.)},
    {"L_{xy}", SepInfo3(0.3728, 0., 0.)},
    {"log(#chi^{2}_{xy})", SepInfo3(0.2864, 0., 0.)},
    {"|d_{0}|^{max} sig.", SepInfo3(0.1523, 0., 0.)},
    {"|IP_{B}^{3D}|", SepInfo3(0.1054, 0., 0.)},
    {"DOCA_{#mu#mu}", SepInfo3(0.05768, 0., 0.)},
    {"p^B_{T}", SepInfo3(0.02995, 0., 0.)},
    {"P^{min}_{L}", SepInfo3(0.02572, 0., 0.)},
    {"|#Delta #phi_{#mu#mu}|", SepInfo3(0.01149, 0., 0.)}
};

// //custom
// 0.389900, 0.388900, 0.392000
// 0.439700, 0.439100, 0.438900
// 0.379500, 0.381200, 0.385100
//     //set1
//         6 &    0.389900 &          DOCA BEL (PPP) Custom TVA Trk Perigee &        12 &     0.04608 \\
//         3 &    0.439700 &  nCloseTracks BEL (PPP) Custom TVA Trk Perigee &         7 &     0.07052 \\
//         7 &    0.379500 &         B Iso BEJ (PPP) Custom TVA Trk Perigee &         3 &     0.10000 \\
//     //set2
//         6 &    0.388900 &          DOCA BEL (PPP) Custom TVA Trk Perigee &        11 &     0.04587 \\
//         3 &    0.439100 &  nCloseTracks BEL (PPP) Custom TVA Trk Perigee &         7 &     0.06584 \\
//         7 &    0.381200 &         B Iso BEJ (PPP) Custom TVA Trk Perigee &         3 &     0.09801 \\
//     //set3
//         6 &    0.392000 &          DOCA BEL (PPP) Custom TVA Trk Perigee &        11 &     0.04766 \\
//         3 &    0.438900 &  nCloseTracks BEL (PPP) Custom TVA Trk Perigee &         8 &     0.06270 \\
//         7 &    0.385100 &         B Iso BEJ (PPP) Custom TVA Trk Perigee &         3 &     0.10490 \\
// //loose
// 0.389200, 0.388500, 0.391700
// 0.438600, 0.438300, 0.438800
// 0.385000, 0.386400, 0.390700
//     //set1
//         6 &    0.389200 &          DOCA BGL (PPP) Loose TVA &        12 &     0.04803 \\
//         4 &    0.438600 &  nCloseTracks BGL (PPP) Loose TVA &         8 &     0.05989 \\
//         7 &    0.385000 &         B Iso BGJ (PPP) Loose TVA &         3 &     0.09508 \\
//     //set2
//         6 &    0.388500 &          DOCA BGL (PPP) Loose TVA &        10 &     0.05213 \\
//         3 &    0.438300 &  nCloseTracks BGL (PPP) Loose TVA &         8 &     0.06119 \\
//         7 &    0.386400 &         B Iso BGJ (PPP) Loose TVA &         3 &     0.09626 \\
//     //set3
//         6 &    0.391700 &          DOCA BGL (PPP) Loose TVA &        12 &     0.05074 \\
//         3 &    0.438800 &  nCloseTracks BGL (PPP) Loose TVA &         8 &     0.05816 \\
//         7 &    0.390700 &         B Iso BGJ (PPP) Loose TVA &         3 &     0.10190 \\
// //run1
// 0.387000, 0.388200, 0.392700 
//     //set1
//     6 &    0.387000 &  B Iso BDI (PVP) As in Run 1 &         3 &     0.09825 \\
//     //set2
//     6 &    0.388200 &  B Iso BDI (PVP) As in Run 1 &         3 &     0.09585 \\
//     //set3
//     6 &    0.392700 &  B Iso BDI (PVP) As in Run 1 &         3 &     0.10100 \\

    map<TString, SepInfo3>::iterator it;
    map<TString, SepInfo3>::iterator itold;
    map<TString, DescriptorLoc>::iterator iDescLoc;

    map<TString, SepInfo3> map1;
    map<TString, SepInfo3> map2;
    // map1 = NewNtuplesCorrected;
    map1 = oldnTuplesRedone;
    // map2 = oldnTuplesRedone;
    map2 = Run1nTuples;
    // it = NewNtuples.find("N^{clos}_{trk}");
    // cout << "N^{clos}_{trk} BDT1 sep = " << it->second.SepValue1 << "\n";
    int cnt(0);
    Int_t n = 30;
    Double_t x1[n], y1[n]; 
    TString descriptor[n];
    for ( it = map1.begin(); it != map1.end(); it++ )
    {
        // cout << it->first << " " << it->second.SepValue;
        if ((it->first).Contains("N^{clos}_{trk}")){ 
            itold = map2.find("N^{clos}_{trk}");
            // cout << " " << itold->second.SepValue1 << "\n";
        }else if((it->first).Contains("B Iso")){
            itold = map2.find("B Isolation (I^{B}_{0.7})");
            // cout << " " << itold->second.SepValue1 << "\n";
        }else if((it->first).Contains("DOCA")&& !(it->first).Contains("DOCA_{#mu#mu}")){
            itold = map2.find("DOCA_{xtrk,loose,pt>0.5}");
            // cout << " " << itold->second.SepValue1 << "\n";
        }else{
            itold = map2.find(it->first);
            // cout << " " << itold->second.SepValue1 << "\n";
        }
        descriptor[cnt] = it->first;
        if (whichSet.EqualTo("1")){
        y1[cnt] = it->second.SepValue1;
        x1[cnt] = itold->second.SepValue1;
        }else if (whichSet.EqualTo("2")){
        y1[cnt] = it->second.SepValue2;
        x1[cnt] = itold->second.SepValue2;
        }else if (whichSet.EqualTo("3")){
        y1[cnt] = it->second.SepValue3;
        x1[cnt] = itold->second.SepValue3;
        }
        cnt++;
    }

    TGraph *graph1 = (TGraph *)new TGraph(cnt,x1,y1);
    // graph1->GetXaxis()->SetTitle("Partial Run 2 Separation");
    graph1->GetXaxis()->SetTitle("Run 1 Separation");
    // graph1->GetYaxis()->SetTitle("new nTuple Separation");
    // graph1->GetYaxis()->SetTitle("Run 2 Separation (new nTuples)");
    graph1->GetYaxis()->SetTitle("Run 2 Separation (old nTuples)");
    graph1->SetLineColor(0);
    graph1->SetMarkerStyle(22);
    // graph1->SetMarkerSize(0.5);
    graph1->SetMarkerSize(0.7);
    graph1->SetMarkerColor(kRed+1);
    // TLatex *latex;
    const int n2 = cnt;
    // float adjX(0.), adjY(0.);
    // float multX = 0.;
    // float multY = 0.;
    // int adjAlign(0);
    TLatex *l[n2];
    // for (int i = 0; i<cnt; i++){
    //     if ((descriptor[i]).Contains("BE")){
    //         // adjX = 0.0;
    //         // adjY = 0.03;
    //         adjX = 0.0;
    //         adjY = 0.0;
    //     }else if ((descriptor[i]).Contains("BG")){
    //         adjX = 0.0;
    //         adjY = 0.;
    //         // adjY = 0.01;
    //     }else if ((descriptor[i]).Contains("AC")){
    //         adjX = 0.;
    //         // adjY = -0.01;
    //         adjY = 0.;
    //     }else if ((descriptor[i]).Contains("As in")){
    //         adjX = 0.;
    //         // adjY = -0.01;
    //         adjY = 0.;
    //     }else{
    //         adjX = 0.03;
    //         adjY = 0.;
    //     }
    //     if ((descriptor[i]).Contains("DOCA")&& !(descriptor[i]).Contains("DOCA_{#mu#mu}")){
    //         adjAlign = 33;
    //         adjX = 0.;
    //         multX = 0.;
    //         multY = 0.;
    //     }else if ((descriptor[i]).Contains("B Iso")){
    //         adjAlign = 23;
    //         adjY-=0.1;
    //         multX = 0.;
    //         multY = 0.8;
    //     }else if ((descriptor[i]).Contains("N^{clos}_{trk}")){
    //         adjAlign = 23;
    //         multX = 0.;
    //         multY = 0.;
    //     }else{
    //         adjAlign = 23;
    //         multX = 0.;
    //         multY = 0.;
    //     }
    map<TString, DescriptorLoc> SetLabelPositions;
    // SetLabelPositions = LabelPositions;
    SetLabelPositions = LabelPositionsRun1;
    int cnt2(0);
    for ( iDescLoc = SetLabelPositions.begin(); iDescLoc != SetLabelPositions.end(); iDescLoc++ )
    {
        if ((iDescLoc->first).Contains("N^{clos}_{trk}")){ 
            itold = oldnTuples.find("N^{clos}_{trk}");
            // cout << " " << itold->second.SepValue1 << "\n";
        }else if((iDescLoc->first).Contains("B Iso")){
            itold = oldnTuples.find("B Isolation (I^{B}_{0.7})");
            // cout << " " << itold->second.SepValue1 << "\n";
        }else if((iDescLoc->first).Contains("DOCA")&& !(iDescLoc->first).Contains("DOCA_{#mu#mu}")){
            itold = oldnTuples.find("DOCA_{xtrk,loose,pt>0.5}");
            // cout << " " << itold->second.SepValue1 << "\n";
        }else{
            itold = oldnTuples.find(iDescLoc->first);
            // cout << " " << itold->second.SepValue1 << "\n";
        }
        // l[cnt2] = new TLatex(itold->second.SepValue1, iDescLoc->second.LocY, iDescLoc->first); 
        l[cnt2] = new TLatex(iDescLoc->second.LocX, iDescLoc->second.LocY, iDescLoc->first); 
        l[cnt2]->SetTextSize(0.017);
        l[cnt2]->SetTextAlign(iDescLoc->second.align);
        graph1->GetListOfFunctions()->Add(l[cnt2]);
        cnt2++;
    }
    TLine *myLine =  new TLine (0.01, 0.01, 0.6, 0.6);
    myLine->SetLineColorAlpha(kBlue+1, 0.35);
        // c1->Update();
    // latex->DrawLatex(graph1->GetX()[5], graph1->GetY()[5],"my annotation");
    // latex = new TLatex(graph1->GetX()[6], graph1->GetY()[6],"my annotation 2"); 
    // latex->SetTextSize(0.025);
    // graph1->GetListOfFunctions()->Add(latex);
    // Double_t x,y;
    // for (int i=1; i<10; i++) {
    //     graph1->GetPoint(i,x,y);
    //     l = new TLatex(x,y+0.2,Form("%4.2f",y));
    //     l->SetTextSize(0.025);
    //     l->SetTextFont(42);
    //     l->SetTextAlign(21);
    //     l->DrawLatex();
    // }
     // TExec *ex = new TExec("ex","drawtext(descriptor);");
     // graph1->GetListOfFunctions()->Add(ex);
    // graph1->GetXaxis()->SetLimits(-0.05,0.65);
    // graph1->GetYaxis()->SetRangeUser(-0.025,0.65);
    graph1->GetXaxis()->SetLimits(0.,0.59);
    graph1->GetYaxis()->SetRangeUser(0.,0.65);
    graph1->Draw("ap");
    myLine->Draw("same");
    ATLASLabel(0.2, 0.8,"Internal",1);
    TString tex1text(""), tex2text("");
    if (whichSet.EqualTo("1")){
        // tex1text = "New nTuples: Datasets 1";
        // tex1text = "New nTuples: All";
        // tex2text = "Old nTuples: Datasets 1";
    }else if (whichSet.EqualTo("2")){
        tex1text = "No MC Weights";
        // tex1text = "New nTuples: Datasets 2";
        // tex2text = "Old nTuples: Datasets 2";
    }else if (whichSet.EqualTo("3")){
        tex1text = "New nTuples: Datasets 3";
        tex2text = "Old nTuples: Datasets 3";
    }
    TLatex *tex1, *tex2;
    tex1 = new TLatex(.05, .48, tex1text.Data());
    tex1->SetTextFont(62);
    tex1->SetTextSize(0.034468);
    tex1->SetLineWidth(2);
    tex1->Draw();
    tex2 = new TLatex(.05, .455, tex2text.Data());
    tex2->SetTextFont(62);
    tex2->SetTextSize(0.034468);
    tex2->SetLineWidth(2);
    tex2->Draw();

        //june 10 introduced the new ntuples BDT separated
    TString outTag("");
    if (whichSet.EqualTo("1")){
        outTag = "MCweights";
    }else if (whichSet.EqualTo("2")){
        outTag = "noWeights";
    }
// c1->SaveAs("SepComp_2020Jun16_"+whichSet+".pdf");
// c1->SaveAs("SepComp_2020Jun16_"+outTag+".pdf");
// c1->SaveAs("SepComp_2020Jun16_"+outTag+"Run1_v2.pdf");
c1->SaveAs("SepComp_2020Jun16_"+outTag+"Run1_oldnTuples2.pdf");
// delete c1;
}

// void drawtext(const Double_t *descriptor)
// {
//    Int_t i,n;
//    Double_t x,y;
//    TLatex *l;

//    TGraph *g = (TGraph*)gPad->GetListOfPrimitives()->FindObject("Graph");
//    n = g->GetN();
//    for (i=1; i<n; i++) {
//       g->GetPoint(i,x,y);
//       l = new TLatex(x+0.01,y+0.01,Form("%s",descriptor[i]);
//       l->SetTextSize(0.025);
//       l->SetTextFont(42);
//       l->SetTextAlign(21);
//       l->Paint();
//    }
// }


// nom:

// struct SepInfo{
//     // TString name;
//     Double_t SepValue;
//     };
//     map<TString, SepInfo> NewNtuples ={
//         {"N^{clos}_{trk} ACK", SepInfo(0.408700)}
//         {"DOCA ACK", SepInfo(0.387300)}
//         {"B Iso ACH", SepInfo(0.353700)}
//         //Custom
//         {"N^{clos}_{trk} BEL Custom", SepInfo(0.438800)}
//         {"DOCA BEL Custom", SepInfo(0.391600)}
//         {"B Iso BEJ Custom", SepInfo(0.381400)}
//         //loose
//         {"N^{clos}_{trk} BGL Loose", SepInfo(0.438300)}
//         {"DOCA BGL Loose", SepInfo(0.391100)}
//         {"B Iso BGJ Loose", SepInfo(0.386700)}
//         //Run1
//         {"B Iso BDI As in Run 1", SepInfo(0.388600)}
//         //rest
//         {"#Delta R", SepInfo(0.573100)}
//         {"|#alpha_{2D}|", SepInfo(0.557900)}
//         {"log(#chi^{2}_{#mu,xPV})", SepInfo(0.436400)}
//         {"d^0_{min, SepInfo(sig}", SepInfo(0.393900)}
//         {"L_{xy}", SepInfo(0.367000)}
//         {"log(#chi^{2}_{xy})", SepInfo(0.298300)}
//         {"d^0_{max, SepInfo(sig}", SepInfo(0.168200)}
//         {"|IP_{B}^{3D}|", SepInfo(0.138200)}
//         {"DOCA_{#mu#mu}", SepInfo(0.067320)}
//         {"P^{min}_{L}", SepInfo(0.008266)}
//         {"|#Delta #phi_{#mu#mu}|", SepInfo(0.005445)}
//         {"p^B_{T}", SepInfo(0.004634)}
//     }
// struct SepInfo3{
//     // TString name;
//     Double_t SepValue1;
//     Double_t SepValue2;
//     Double_t SepValue3;
//     };
// // partial run 2, 
// // BDT1 separation, BDT2 separation, BDT3 separation
//     map<TString, SepInfo3> oldnTuples ={
//         {"N^{clos}_{trk}", SepInfo3(0.42660, 0.42560, 0.42590)},
//         {"DOCA_{xtrk,loose,pt>0.5}", SepInfo3(0.31300, 0.32220, 0.32260)},
//         {"B Isolation (I^{B}_{0.7})", SepInfo3(0.36160, 0.36200, 0.36650)},
//         {"#Delta R", SepInfo3(0.59710, 0.59830, 0.60000)},
//         {"|#alpha_{2D}|", SepInfo3(0.57890, 0.57890, 0.57570)},
//         {"log(#chi^{2}_{#mu,xPV})", SepInfo3(0.44190, 0.43950, 0.44070)},
//         {"|d_{0}|^{min} sig.", SepInfo3(0.39140, 0.38930, 0.39130)},
//         {"L_{xy}", SepInfo3(0.38910, 0.38570, 0.38690)},
//         {"log(#chi^{2}_{xy})", SepInfo3(0.30730, 0.30520, 0.30630)},
//         {"|d_{0}|^{max} sig.", SepInfo3(0.17080, 0.16850, 0.17020)},
//         {"|IP_{B}^{3D}|", SepInfo3(0.15100, 0.14910, 0.15060)},
//         {"DOCA_{#mu#mu}", SepInfo3(0.08282, 0.08036, 0.08507)},
//         {"P^{min}_{L}", SepInfo3(0.03469, 0.03507, 0.03403)},
//         {"|#Delta #phi_{#mu#mu}|", SepInfo3(0.02661, 0.02697, 0.02672)},
//         {"p^B_{T}", SepInfo3(0.04200, 0.04302, 0.04204)}
//     }
// struct ImpInfo3{
//     TString name;
//     Double_t ImpValue1;
//     Double_t ImpValue2;
//     Double_t ImpValue3;
//     };

// // importance
// // BDT1 importance, BDT2 importance, BDT3 importance
// {"#Delta R", 0.11780, 0.11210, 0.12130}
// {"|#alpha_{2D}|", 0.11570, 0.11160, 0.11090}
// {"log(#chi^{2}_{#mu,xPV})", 0.08314, 0.09386, 0.08429}
// {"N^{clos}_{trk}", 0.05866, 0.05540, 0.05722}
// {"|d_{0}|^{min} sig.", 0.03611, 0.03779, 0.04055}
// {"L_{xy}", 0.04241, 0.05308, 0.04072}
// {"B Isolation (I^{B}_{0.7})", 0.09715, 0.09587, 0.09922}
// {"DOCA_{xtrk,loose,pt>0.5}", 0.03732, 0.03431, 0.03193}
// {"log(#chi^{2}_{xy})", 0.07723, 0.07944, 0.08526}
// {"|d_{0}|^{max} sig.", 0.05087, 0.04772, 0.05091}
// {"|IP_{B}^{3D}|", 0.05032, 0.05628, 0.04972}
// {"DOCA_{#mu#mu}", 0.05599, 0.05470, 0.05282}
// {"p^B_{T}", 0.06338, 0.05780, 0.05925}
// {"P^{min}_{L}", 0.04700, 0.04544, 0.04763}
// {"|#Delta #phi_{#mu#mu}|", 0.06692, 0.06463, 0.06827}

// // BDT1 partial, 
// // separation, importance
// {"#Delta R", 0.59710, 0.11780}
// {"|#alpha_{2D}|", 0.57890, 0.11570}
// {"log(#chi^{2}_{#mu,xPV})", 0.44190, 0.08314}
// {"N^{clos}_{trk}", 0.42660, 0.05866}
// {"|d_{0}|^{min} sig.", 0.39140, 0.03611}
// {"L_{xy}", 0.38910, 0.04241}
// {"B Isolation (I^{B}_{0.7})", 0.36160, 0.09715}
// {"DOCA_{xtrk,loose,pt>0.5}", 0.31300, 0.03732}
// {"log(#chi^{2}_{xy})", 0.30730, 0.07723}
// {"|d_{0}|^{max} sig.", 0.17080, 0.05087}
// {"|IP_{B}^{3D}|", 0.15100, 0.05032}
// {"DOCA_{#mu#mu}", 0.08282, 0.05599}
// {"p^B_{T}", 0.04200, 0.06338}
// {"P^{min}_{L}", 0.03469, 0.04700}
// {"|#Delta #phi_{#mu#mu}|", 0.02661, 0.06692}
// //BDT2 partial
// // separation, importance
// {"#Delta R", 0.59830, 0.11210}
// {"|#alpha_{2D}|", 0.57890, 0.11160}
// {"log(#chi^{2}_{#mu,xPV})", 0.43950, 0.09386}
// {"N^{clos}_{trk}", 0.42560, 0.05540}
// {"|d_{0}|^{min} sig.", 0.38930, 0.03779}
// {"L_{xy}",0.38570, 0.05308}
// {"B Isolation (I^{B}_{0.7})", 0.36200, 0.09587}
// {"DOCA_{xtrk,loose,pt>0.5}", 0.32220, 0.03431}
// {"log(#chi^{2}_{xy})", 0.30520, 0.07944}
// {"|d_{0}|^{max} sig.", 0.16850, 0.04772}
// {"|IP_{B}^{3D}|", 0.14910, 0.05628}
// {"DOCA_{#mu#mu}", 0.08036, 0.05470}
// {"p^B_{T}", 0.04302, 0.05780}
// {"P^{min}_{L}", 0.03507, 0.04544}
// {"|#Delta #phi_{#mu#mu}|", 0.02697, 0.06463}
// //BDT3 partial
// // separation, importance
// {"#Delta R", 0.60000, 0.12130}
// {"|#alpha_{2D}|", 0.57570, 0.11090}
// {"log(#chi^{2}_{#mu,xPV})", 0.44070, 0.08429}
// {"N^{clos}_{trk}", 0.42590, 0.05722}
// {"|d_{0}|^{min} sig.", 0.39130, 0.04055}
// {"L_{xy}", 0.38690, 0.04072}
// {"B Isolation (I^{B}_{0.7})", 0.36650, 0.09922}
// {"DOCA_{xtrk,loose,pt>0.5}", 0.32260, 0.03193}
// {"log(#chi^{2}_{xy})", 0.30630, 0.08526}
// {"|d_{0}|^{max} sig.", 0.17020, 0.05091}
// {"|IP_{B}^{3D}|", 0.15060, 0.04972}
// {"DOCA_{#mu#mu}", 0.08507, 0.05282}
// {"p^B_{T}", 0.04204, 0.05925}
// {"P^{min}_{L}", 0.03403, 0.04763}
// {"|#Delta #phi_{#mu#mu}|", 0.02672, 0.06827}
void PlotSep(){
    TString whichSet = "1";
    CreateGraphs(whichSet);
    // whichSet = "2";
    // CreateGraphs(whichSet);
    // whichSet = "3";
    // CreateGraphs(whichSet);
}