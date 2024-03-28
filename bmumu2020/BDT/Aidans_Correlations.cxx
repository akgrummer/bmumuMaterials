#include "/home/agrummer/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/home/agrummer/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/home/agrummer/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/home/agrummer/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/home/agrummer/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/home/agrummer/bmumu2020/AtlasStyle/AtlasUtils.h"

#include "TMVA/correlations.h"
#include "TMVA/Config.h"


#include "TH1.h"
#include "TH2.h"
#include "TPaletteAxis.h"

// this macro plots the correlation matrix of the various input
// variables used in TMVA (e.g. running TMVAnalysis.C).  Signal and
// Background are plotted separately

// input: - Input file (result from TMVA),
//        - use of colors or grey scale
//        - use of TMVA plotting TStyle
void Aidans_Correlations(){
    TString dataset = "BDToutput/2020July16/out_ALLvars/Set1";
    TString fin = "BDToutput/2020July16/out_ALLvars/Set1/bdt2020.root";
    // TString dataset = "BDToutput/2020July16/out_ALLvars_npvweights/Set1";
    // TString fin = "BDToutput/2020July16/out_ALLvars_npvweights/Set1/bdt2020.root";
Bool_t isRegression = kFALSE;
   // set style and remove existing canvas'
   // TMVAGlob::Initialize( useTMVAStyle );

   // checks if file with name "fin" is already open, and if not opens one
   TFile* file = (TFile *)new TFile( fin , "read");  

   // signal and background or regression problem
   Int_t ncls = (isRegression ? 1 : 2 );
   TString hName[2] = { "CorrelationMatrixS", "CorrelationMatrixB" };
   if (isRegression) hName[0]= "CorrelationMatrix";
   const Int_t width = 600;
   for (Int_t ic=0; ic<ncls; ic++) {

        TH2* h2 = dynamic_cast<TH2*> (file->GetDirectory(dataset.Data())->Get( hName[ic] ));
        if(!h2) {
        cout << "Did not find histogram " << hName[ic] << " in " << fin << endl;
        continue;
        }

        TCanvas* c = new TCanvas( hName[ic], 
            Form("Correlations between MVA input variables (%s)", 
                 (isRegression ? "" : (ic==0 ? "signal" : "background"))), 
            ic*(width+5)+200, 0, width, width ); 
        // Float_t newMargin1 = 0.13;
        // Float_t newMargin2 = 0.15;
        // if (gConfig().fVariablePlotting.fUsePaperStyle) newMargin2 = 0.13;

        // c->SetGrid();
        // c->SetTicks();
        c->SetTickx(1);
        c->SetTicky(1);
        // c->SetLeftMargin  ( newMargin2 );
        // c->SetBottomMargin( newMargin2 );
        // c->SetRightMargin ( newMargin1 );
        // c->SetTopMargin   ( newMargin1 );
        c->SetLeftMargin(0.16);
        c->SetRightMargin(0.13);
        c->SetTopMargin(0.14);
        c->SetBottomMargin(0.16);
        c->SetFrameBorderMode(0);
        c->SetFrameBorderMode(0);
        // gStyle->SetPalette( 1, 0 );
        //Scale the histograms:
        h2->Scale(1./100.);

        // gStyle->SetPaintTextFormat( "3g" );
        h2->SetMarkerSize( 0.9 );
        h2->SetMarkerColor( 1 );
        h2->SetMinimum(-1.0);
        h2->SetMaximum(1.0);
        // h2->SetEntries(648);
        h2->SetStats(0);
        h2->SetContour(20);
        h2->SetContourLevel(0,-1.00);
        h2->SetContourLevel(1,-.90);
        h2->SetContourLevel(2,-.80);
        h2->SetContourLevel(3,-.70);
        h2->SetContourLevel(4,-.60);
        h2->SetContourLevel(5,-.50);
        h2->SetContourLevel(6,-.40);
        h2->SetContourLevel(7,-.30);
        h2->SetContourLevel(8,-.20);
        h2->SetContourLevel(9,-.10);
        h2->SetContourLevel(10,0.0);
        h2->SetContourLevel(11,.10);
        h2->SetContourLevel(12,.20);
        h2->SetContourLevel(13,.30);
        h2->SetContourLevel(14,.40);
        h2->SetContourLevel(15,.50);
        h2->SetContourLevel(16,.60);
        h2->SetContourLevel(17,.70);
        h2->SetContourLevel(18,.80);
        h2->SetContourLevel(19,.90);
        Float_t labelSize = 0.040;
        // h2->GetXaxis()->SetLabelSize( labelSize );
        // h2->GetYaxis()->SetLabelSize( labelSize );
        // h2->LabelsOption( "d" );
        h2->GetXaxis()->SetBit(TAxis::kLabelsVert);
        h2->SetLabelOffset( 0.011 );// label offset on x axis    
        h2->GetYaxis()->SetLabelSize(0.02);
        h2->GetXaxis()->SetLabelSize(0.02);

        // h2->Draw("colz"); // color pads   
        gStyle->SetPaintTextFormat("4.2f");
        gStyle->SetHistMinimumZero(kTRUE);

        h2->Draw("colz");
        c->Update();
        // modify properties of paletteAxis
        TPaletteAxis* paletteAxis = (TPaletteAxis*)h2->GetListOfFunctions()->FindObject( "palette" );
        paletteAxis->SetLabelSize( 0.005 );
        paletteAxis->SetX1NDC( paletteAxis->GetX1NDC() + 0.02 );

        h2->Draw("text45same");  // add text, also adusts z axis palette 

        // add comment    
        // TText* t = new TText( 0.53, 0.88, "Linear correlation coefficients in %" );
        // t->SetNDC();
        // t->SetTextSize( 0.026 );
        // t->AppendPad();    

        // TMVAGlob::plot_logo( );

        c->Update();
        TString fname = dataset+"/plots/";
        fname += hName[ic];
        // TMVAGlob::imgconv( c, fname );
        c->SaveAs(fname + ".pdf");
   }
   return 0;
}
