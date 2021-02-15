#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include "TMath.h"
#include <fstream>

void Compare_P8Gen()
{
const int nfiles = 4;
const int nmc = 3;
/*
//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_MG.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_Hwg.root"};Ratio//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_MG.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_Hwg.root"};

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/RooUnfold/Unfolded_2016_Data_Hwg_MC_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_Hwg_MC_MG.root","/home/suman/RooUnfold/Unfolded_2016_Data_Herwig_MC_Herwig.root"};
*/
/*
//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_P8_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_MG_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_Hwg_excor.root"};

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_P8_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_MG_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_Hwg_excor.root"};

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_Hwg_MC_P8_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_Hwg_MC_MG_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_Hwg_MC_Hwg_excor.root"};
*/

const char *filenames[nmc][nfiles] = {{"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/RooUnfold/Unfolded_2016_Data_Hwg_MC_Hwg_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_Hwg_MC_P8_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_Hwg_MC_MG_TUnfold.root"},
	{"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_Hwg_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_P8_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_MG_TUnfold.root"},
	{"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_Hwg_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_P8_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_MG_TUnfold.root"}};

const char *model_name[nmc][nfiles] = {{"Herwig GEN","Unfolded by Herwig","Unfolded by P8","Unfolded by Madgraph"},
					{"P8 Gen","Unfolded by Herwig","Unfolded by P8","Unfolded by Madgraph"},
					{"Madgraph Gen","Unfolded by Herwig","Unfolded by P8","Unfolded by Madgraph"}};
					
const char *mc_name[nmc] = {"Hwg","P8","MG"};
const char *mc_reco[nmc] = {"RECO level : Herwig","RECO level : P8","RECO level : Madgraph"};
const int col[nfiles] = {1,4,6,2};

int od_1 , od_2, gen;
const int noptbins = 31;

const int ref = 3;

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[100];

const char *outfilenames[nfiles] = {"Pythia","Madgraph","Herwig"} ;

ofstream fp_pt[nmc];
ofstream fp_rad[nmc];
for(int mc=0; mc<nmc; mc++){
sprintf(name,"Unf_Pt_%s_TUnfold_bayes.log",outfilenames[mc]);
fp_pt[mc].open(name) ;
sprintf(name,"Unf_Rad_%s_TUnfold_bayes.log",outfilenames[mc]);
fp_rad[mc].open(name) ;
}

TFile *filein;

TH1D* hist_pt[nmc][nfiles][nalgo][netarange];
TH1D* hist_pt_rat[nmc][nfiles-1][nalgo][netarange];
TH1D* hist_pt_org[nmc][nfiles][nalgo][netarange];

TH1D* hist_radius[nmc][nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nmc][nfiles-1][nalgo][netarange];

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

double unf_pt[nmc][nalgo][netarange][noptbins];
double unf_rad[nmc][nalgo][netarange][noptbins];

float data_lumi = 33.4 ;//1.;

for(int mc=0; mc<nmc; mc++){
	
  gen = mc+1;
  if(mc==0){od_1 = 2, od_2 = 3;}
  if(mc==1){od_1 = 1, od_2 = 3;}
  if(mc==2){od_1 = 1, od_2 = 2;}
	
 for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[mc][fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

     if(fg==0) { sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1); }
	else { sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1); }
//	else { sprintf(name,"tuf_TUnfold_%s_Etabin%i",JetRad[ij],jk+1); }

     hist_pt[mc][fg][ij][jk] = (TH1D*)filein->Get(name);
     if(fg==0) { hist_pt[mc][fg][ij][jk]->Rebin(2); }
     
     hist_pt_org[mc][fg][ij][jk] = (TH1D*)hist_pt[mc][fg][ij][jk]->Clone();

   for(int bn=0; bn<(hist_pt[mc][fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[mc][fg][ij][jk]->SetBinContent(bn+1,hist_pt[mc][fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[mc][fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[mc][fg][ij][jk]->SetBinError(bn+1,hist_pt[mc][fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[mc][fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }//bn

    hist_pt[mc][fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[mc][fg][ij][jk]->GetXaxis()->SetTitleSize(0.075);
    hist_pt[mc][fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
    hist_pt[mc][fg][ij][jk]->GetXaxis()->SetTitleOffset(1.);
    hist_pt[mc][fg][ij][jk]->GetXaxis()->CenterTitle();

    hist_pt[mc][fg][ij][jk]->GetXaxis()->SetRangeUser(84,3000);   

    hist_pt[mc][fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb^{-1}GeV^{-1})");
    hist_pt[mc][fg][ij][jk]->GetYaxis()->SetTitleSize(0.055);
    hist_pt[mc][fg][ij][jk]->GetYaxis()->SetLabelSize(0.045);
    hist_pt[mc][fg][ij][jk]->GetYaxis()->CenterTitle();

   }//jk
  }//ij
 }//fg
 /*
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
 hist_pt[mc][0][ij][jk]->Scale(hist_pt[mc][gen][ij][jk]->Integral()*1./hist_pt[mc][0][ij][jk]->Integral());
  }
 }
 */ 
}//mc

for(int mc=0; mc<nmc; mc++){
for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[mc][fg][ij][jk] = (TH1D*)hist_pt_org[mc][fg][ij][jk]->Clone();
   hist_radius[mc][fg][ij][jk]->Divide(hist_pt_org[mc][fg][ref][jk]) ;

   hist_radius[mc][fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[mc][fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
   hist_radius[mc][fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[mc][fg][ij][jk]->GetXaxis()->SetTitleOffset(1.);
   hist_radius[mc][fg][ij][jk]->GetXaxis()->CenterTitle();

   hist_radius[mc][fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[mc][fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[mc][fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[mc][fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[mc][fg][ij][jk]->SetMinimum(-1.);
   hist_radius[mc][fg][ij][jk]->SetMaximum(4.);

   hist_radius[mc][fg][ij][jk]->GetXaxis()->SetRangeUser(84,3000);

   }
  }
 }
}

TCanvas *c2[nmc][nalgo][netarange];

TLegend *leg_pt[nmc][nalgo][netarange];

for(int mc=0; mc<nmc; mc++){

  gen = mc+1;
  if(mc==0){od_1 = 2, od_2 = 3;}
  if(mc==1){od_1 = 1, od_2 = 3;}
  if(mc==2){od_1 = 1, od_2 = 2;}

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

 sprintf(name,"P8_Compare_Canv_%s_EtaBin%i_%s",JetRad[ij],jk+1,mc_name[mc]);
 c2[mc][ij][jk] = tdrDiCanvas(name,hist_pt[mc][0][ij][jk],hist_pt[mc][1][ij][jk],6,0);

 leg_pt[mc][ij][jk] = tdrLeg(0.5,0.7,0.85,0.95);
// leg_pt[ij][jk] = tdrLeg(0.55,0.7,0.9,0.95);

 c2[mc][ij][jk]->cd(1);

 gPad->SetLogx(1);
 gPad->SetLogy(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.065);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];
  TString text2;
  text2+= mc_reco[mc];

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.125,text1);
  latex.SetTextSize(0.055);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.225,leg_y1+0.15,text2);

 // hist_pt[mc][0][ij][jk]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

      if(fg!=0){
      hist_pt_rat[mc][fg-1][ij][jk] = (TH1D*)hist_pt[mc][fg][ij][jk]->Clone();
      hist_pt_rat[mc][fg-1][ij][jk]->Divide(hist_pt[mc][0][ij][jk]);
      hist_pt_rat[mc][fg-1][ij][jk]->GetYaxis()->SetTitle("Unfolded / Gen");
        }

   //  if(fg!=gen||fg!=0) continue;
//	   if(fg==gen||fg==0){
      tdrDraw(hist_pt[mc][fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[mc][ij][jk]->AddEntry(hist_pt[mc][fg][ij][jk],model_name[mc][fg],"l");
//		}
    }
 leg_pt[mc][ij][jk]->SetTextSize(0.04);
 leg_pt[mc][ij][jk]->SetTextFont(42);

 c2[mc][ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

for(int fg=0; fg<(nfiles-1); fg++){

   hist_pt_rat[mc][fg][ij][jk]->SetLineColor(col[fg+1]);
   hist_pt_rat[mc][fg][ij][jk]->SetMinimum(0.5);
   hist_pt_rat[mc][fg][ij][jk]->SetMaximum(1.5);

   hist_pt_rat[mc][fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_pt_rat[mc][fg][ij][jk]->GetXaxis()->SetTitleSize(0.12);
   hist_pt_rat[mc][fg][ij][jk]->GetXaxis()->SetLabelSize(0.1);
   hist_pt_rat[mc][fg][ij][jk]->GetXaxis()->CenterTitle();  

   hist_pt_rat[mc][fg][ij][jk]->GetXaxis()->SetRangeUser(84,3000.);
 
   hist_pt_rat[mc][fg][ij][jk]->GetYaxis()->SetTitleSize(0.1);
   hist_pt_rat[mc][fg][ij][jk]->GetYaxis()->SetTitleOffset(0.5);
   hist_pt_rat[mc][fg][ij][jk]->GetYaxis()->SetLabelSize(0.075);
/*
   if(fg==(gen-1)) {  hist_pt_rat[mc][fg][ij][jk]->Draw("e"); }
	else { continue; }
	}
 */
 if(fg==0) {  hist_pt_rat[mc][fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[mc][fg][ij][jk]->Draw("sames"); }
 }
 
//sprintf(name,"Unfolded_GEN/ExCor_84/GEN_Herwig/Pt_Plots/%s.eps",c2[ij][jk]->GetName());
sprintf(name,"Closure_Test/TUnfold/Gen_%s/Pt_Plots/%s.eps",mc_name[mc],c2[mc][ij][jk]->GetName());
c2[mc][ij][jk]->SaveAs(name);

for(int pt=0; pt<noptbins; pt++){

unf_pt[mc][ij][jk][pt] = TMath::Max(abs(hist_pt[mc][od_1][ij][jk]->GetBinContent(pt+1) - hist_pt[mc][gen][ij][jk]->GetBinContent(pt+1)),abs(hist_pt[mc][od_2][ij][jk]->GetBinContent(pt+1) - hist_pt[mc][gen][ij][jk]->GetBinContent(pt+1)));
unf_pt[mc][ij][jk][pt]*=1./TMath::Max(1.e-6,hist_pt[mc][0][ij][jk]->GetBinContent(pt+1));

fp_pt[mc]<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<TMath::Max(0.,unf_pt[mc][ij][jk][pt])<<'\t'<<TMath::Max(0.,unf_pt[mc][ij][jk][pt])<<endl;

}

  }//jk
 }//ij
}//mc

TCanvas *c3[nmc][nalgo][netarange];

TLegend *leg_radius[nmc][nalgo][netarange];

for(int mc=0; mc<nmc; mc++){

  gen = mc+1;
  if(mc==0){od_1 = 2, od_2 = 3;}
  if(mc==1){od_1 = 1, od_2 = 3;}
  if(mc==2){od_1 = 1, od_2 = 2;}	
	
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
 
// if((ij<2)&&(jk>6)) continue;

  sprintf(name,"P8_Ratio_Compare_Canv_%s_EtaBin%i_%s",JetRad[ij],jk+1,mc_name[mc]);
  c3[mc][ij][jk] = tdrDiCanvas(name,hist_radius[mc][0][ij][jk],hist_radius[mc][1][ij][jk],6,0);

  leg_radius[mc][ij][jk] = tdrLeg(0.45,0.7,0.85,0.95);

  c3[mc][ij][jk]->cd(1);

  gPad->SetLogx(1);
  gPad->SetLogy(0);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.05);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];
  TString text2;
  text2+= mc_reco[mc];

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.1,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.1,leg_y1-0.1,text1);
  latex.SetTextSize(0.055);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.15,leg_y1-0.7,text2);

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[mc][fg-1][ij][jk] = (TH1D*)hist_radius[mc][fg][ij][jk]->Clone();
      hist_radius_rat[mc][fg-1][ij][jk]->Divide(hist_radius[mc][0][ij][jk]);
      hist_radius_rat[mc][fg-1][ij][jk]->GetYaxis()->SetTitle("Unfolded / Gen");

      hist_radius_rat[mc][fg-1][ij][jk]->SetMinimum(0.5);
      hist_radius_rat[mc][fg-1][ij][jk]->SetMaximum(1.5);

      hist_radius_rat[mc][fg-1][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
      hist_radius_rat[mc][fg-1][ij][jk]->GetXaxis()->SetTitleSize(0.05);
      hist_radius_rat[mc][fg-1][ij][jk]->GetXaxis()->SetLabelSize(0.05);
      hist_radius_rat[mc][fg-1][ij][jk]->GetXaxis()->CenterTitle();

      hist_radius_rat[mc][fg-1][ij][jk]->GetXaxis()->SetRangeUser(84,3000.);
        }

    //  if(fg!=0||fg!=gen) continue;
//	if(fg==0||fg==gen){
      tdrDraw(hist_radius[mc][fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[mc][ij][jk]->AddEntry(hist_radius[mc][fg][ij][jk],model_name[mc][fg],"l");
//		}
    }


  leg_radius[mc][ij][jk]->SetTextSize(0.04);
  leg_radius[mc][ij][jk]->SetTextFont(42);

   c3[mc][ij][jk]->cd(2);

   gPad->SetLogx(1);
   gPad->SetLogy(0);

   for(int fg=0; fg<(nfiles-1); fg++){
   hist_radius_rat[mc][fg][ij][jk]->SetLineColor(col[fg+1]);
/*
   if(fg==(gen-1)) { hist_radius_rat[mc][fg][ij][jk]->Draw("e");}
   else { continue; }
*/
   if(fg==0){
         hist_radius_rat[mc][fg][ij][jk]->Draw("e");
   }else{
         hist_radius_rat[mc][fg][ij][jk]->Draw("sames");
        }

   }

//  sprintf(name,"Unfolded_GEN/ExCor_84/GEN_Herwig/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
  sprintf(name,"Closure_Test/TUnfold/Gen_%s/Ratio_Plots/%s.eps",mc_name[mc],c3[mc][ij][jk]->GetName());
  c3[mc][ij][jk]->SaveAs(name);

  for(int pt=0; pt<noptbins; pt++){
    unf_rad[mc][ij][jk][pt] = TMath::Max(abs(hist_radius[mc][od_1][ij][jk]->GetBinContent(pt+1) - hist_radius[mc][gen][ij][jk]->GetBinContent(pt+1)),abs(hist_radius[mc][od_2][ij][jk]->GetBinContent(pt+1) - hist_radius[mc][gen][ij][jk]->GetBinContent(pt+1)));
    unf_rad[mc][ij][jk][pt]*=1./TMath::Max(1.e-6,hist_radius[mc][0][ij][jk]->GetBinContent(pt+1));

    fp_rad[mc]<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<TMath::Max(0.,unf_rad[mc][ij][jk][pt])<<'\t'<<TMath::Max(0.,unf_rad[mc][ij][jk][pt])<<endl;
  }


  }//jk
 }//ij
}//mc


}

int main()
{
Compare_P8Gen();
}
