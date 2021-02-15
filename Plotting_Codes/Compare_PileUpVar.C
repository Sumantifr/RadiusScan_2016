#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_PileUpVar()
{
const int nfiles = 3;

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_MC_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_PUup.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_PUdn.root"};

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor_PUup.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor_PUdn.root"};

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_Pythia_ntuple_OneReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_Pythia_ntuple_OneReso_PUUp.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_Pythia_ntuple_OneReso_PUDn.root"};

const char *model_name[nfiles] = {"PU Nominal","PU Up","PU Down"};
const int col[nfiles] = {1,2,4};

const int ref = 3;

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

float data_lumi = 1.;

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

//     sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1);
     sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);

     hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
     hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }//bn

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();
    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(74,3000.);

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb^{-1}GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();

  }//jk
 }//ij
}//fg

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt_org[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt_org[fg][ref][jk]) ;

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();
   hist_radius[fg][ij][jk]->GetXaxis()->SetRangeUser(74,3000.);

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->SetMinimum(0);
   hist_radius[fg][ij][jk]->SetMaximum(3.);

  }
 }
}

TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

 sprintf(name,"PU_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
 c2[ij][jk] = tdrDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],7,0);

 leg_pt[ij][jk] = tdrLeg(0.6,0.7,0.8,0.85);
 leg_pt[ij][jk]->SetTextFont(42);
 leg_pt[ij][jk]->SetTextSize(0.05);

 c2[ij][jk]->cd(1);

 gPad->SetLogx(1);
 gPad->SetLogy(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.06);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1-0.12,text1);

//  hist_pt[0][ij][jk]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

      if(fg!=0){
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Ratio to PU Nominal");
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetNdivisions(406);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.09);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.85);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.085);
        }

      tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"l");
    }

 c2[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

for(int fg=0; fg<(nfiles-1); fg++){

   hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
   hist_pt_rat[fg][ij][jk]->SetMinimum(0.9);
   hist_pt_rat[fg][ij][jk]->SetMaximum(1.1);

 if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
 }

sprintf(name,"PU_Plots/Detector_Lvl/Pt_Plots/%s.eps",c2[ij][jk]->GetName());

c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij

TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
 
 if((ij<2)&&(jk>6)) continue;

  sprintf(name,"PU_Ratio_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] = tdrDiCanvas(name,hist_radius[0][ij][jk],hist_radius[1][ij][jk],7,0);

  leg_radius[ij][jk] = tdrLeg(0.6,0.7,0.8,0.85);
  leg_radius[ij][jk]->SetTextFont(42);
  leg_radius[ij][jk]->SetTextSize(0.05);

  c3[ij][jk]->cd(1);

  gPad->SetLogx(1);
  gPad->SetLogy(0);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.06);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1-0.12,text1);

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Ratio to PU Nominal");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetNdivisions(406);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.085);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.85);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.085);

      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.9);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(1.1);

        }
      tdrDraw(hist_radius[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"l");
    }

   c3[ij][jk]->cd(2);

   gPad->SetLogx(1);
   gPad->SetLogy(0);

   for(int fg=0; fg<(nfiles-1); fg++){
   hist_radius_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
   if(fg==0){
         hist_radius_rat[fg][ij][jk]->Draw("e");
   }else{
         hist_radius_rat[fg][ij][jk]->Draw("sames");
        }
   }

  sprintf(name,"PU_Plots/Detector_Lvl/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//jk
 }//ij

}

int main()
{
Compare_PileUpVar();
}
