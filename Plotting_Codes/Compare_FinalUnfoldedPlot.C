//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include <fstream>

//#define RunEF
//#define RunG

void Compare_FinalUnfoldedPlot()
{

int unf_choice = 1;
unf_choice -= 1;
const char *unf_title[2] = {"Bayesian","SVD"};
const char *unf_name[2] = {"bayes","svd"};

const int ref_rad = 3;

const int nfiles = 2;

const int noptbins = 61;

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor.root"/*Unfolded_2016_Data.root"*/,/*"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_Pythia_Userhook2_NNPDF30.root"*/"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/HerwigEE5C_Files_sel.root"};

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor_PUnom.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/Bin84_hist_Powheg_Pythia_Userhook2_NNPDF30.root"};

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/Bin84_hist_Powheg_Pythia_Userhook2_NNPDF30.root"};

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Herwig7/Bin84_hist_Herwig7_weighted.root"};

const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/Bin84_HerwigEE5C_Files_sel.root"};

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Bin84_CT14nlo_files.root"};

ifstream fp_pt_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_ExpSys_Pt_excor_84.log");
ifstream fp_rad_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_ExpSys_Rad_excor_84.log");

ifstream fp_pt_th("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_Theory_Unc_Pt_84.log");
ifstream fp_rad_th("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_Theory_Unc_Rad_84.log");

double data_lumi = 33.4;

const char *model_name[nfiles] = {"Data 2016",/*"PH+P8"*//*,"Pythia_Flat","Herwig"*/"PH+Hwgpp"/*,"Madgraph","NLOJet++""Herwig7"*/};
const int col[nfiles] = {1,/*12,4,*/4/*,2*/};

static const int nalgo = 11 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11"/*,"ak12"*/};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs"/*,"ak12chs"*/};
const char* jetname_mod[nalgo] = {"ak1chs-0.75","ak2chs-0.5","ak3chs-0.25","ak4chs","ak5chs+0.25","ak6chs+0.5","ak7chs+0.75","ak8chs+1.0","ak9chs+1.25","ak10chs+1.5","ak11chs+1.75"/*,"ak12chs"*/};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int algo_col[nalgo] = {2,3,4,6,7,11,kCyan+2,kCyan-10, kBlue-7, kMagenta-9, kRed-5/*, kYellow-6*/};//{2,3,4,5,*/6,7,9,12,28,37,44,49};
const int algo_sty[nalgo] = {2,3,4,5,8,21,22,23,25,26,27/*,28*/};

const char *err_name[2] = {"Exp Sys","Theory Sys"};

double max_range = 2500.;
double min_range = 84.;

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

double delta_pt[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

double delta_radius[nfiles-1][nalgo][netarange];

double rad_err_exp_up[nalgo][netarange][noptbins];
double rad_err_exp_dn[nalgo][netarange][noptbins];
double rad_err_th_up[nalgo][netarange][noptbins];
double rad_err_th_dn[nalgo][netarange][noptbins];

TGraphAsymmErrors *err_rad_exp[nalgo][netarange];
TGraphAsymmErrors *err_rad_th[nalgo][netarange];

TLine *line = new TLine(84,1,6000.,1.);
line->SetLineColor(7);

TLine *liney = new TLine(-5.,1.,5.,1.);
liney->SetLineColor(7);

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
     for(int kl=0; kl<noptbins; kl++){
             int xx1,xx2,xx3;
             fp_rad_exp>>xx1>>xx2>>xx3>>rad_err_exp_up[ij][jk][kl]>>rad_err_exp_dn[ij][jk][kl];
             fp_rad_th>>xx1>>xx2>>xx3>>rad_err_th_up[ij][jk][kl]>>rad_err_th_dn[ij][jk][kl];
	}
    }
 }


for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
  
//   if((fg<1)){ sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;/*sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[ij],jk+1);*/}
//   if((fg>0)) {sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
     if((fg<1)){ sprintf(name,"%s_unfold_%s_Etabin%i",unf_name[unf_choice],JetRad[ij],jk+1);}
     if((fg>0)) {sprintf(name,/*mcjets*/"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
     hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
 
    if(fg==1) { hist_pt[1][ij][jk]->Scale(11502051.63); }
   
    hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();    

    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

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
   hist_radius[fg][ij][jk]->Divide(hist_pt_org[fg][ref_rad][jk]) ;
 
   double add_fac = (ij - ref_rad) * 0.25;
   for(int bn=0; bn<hist_radius[fg][ij][jk]->GetNbinsX(); bn++){
	hist_radius[fg][ij][jk]->SetBinContent(bn+1,hist_radius[fg][ij][jk]->GetBinContent(bn+1) + add_fac);
   }

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   sprintf(name,"Ratio of d^{2}#sigma / dp_{T}dy w.r.t. %s Jets (%s)",JetRad[ref_rad],model_name[1]);
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle(name);
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.04);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

   hist_radius[fg][ij][jk]->SetMinimum(-0.75);
   hist_radius[fg][ij][jk]->SetMaximum(6.0);

   if(fg>0){
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC/Data");
			  
	double add_fac = (ij - ref_rad) * 0.25;

	for(int bn=0; bn<hist_pt_rat[fg-1][ij][jk]->GetNbinsX(); bn++){
		hist_pt_rat[fg-1][ij][jk]->SetBinContent(bn+1,hist_pt_rat[fg-1][ij][jk]->GetBinContent(bn+1)+add_fac);
			 }
   	hist_pt_rat[fg-1][ij][jk]->SetMinimum(0);
   	hist_pt_rat[fg-1][ij][jk]->SetMaximum(3.);
        }

  }
 }
}

TCanvas *c2[netarange];

TLegend *leg_pt[netarange];

 for(int jk=0; jk<netarange; jk++){


sprintf(name,"Di_Pt_Compare_Canv_EtaBin%i",jk+1);
c2[jk] = tdrCanvas(name,hist_pt_rat[0][ref_rad][jk],6,0);

leg_pt[jk] = tdrLeg(0.6,0.65,0.95,0.9);

c2[jk]->cd(1);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.04);

  //TString text;
  //text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1,text1);

for(int ij=0; ij<nalgo; ij++){

//  hist_pt[0][ij][jk]->Scale(1./data_lumi);
//  hist_pt[1][ij][jk]->Scale(1./48191.824);  

 for(int fg=0; fg<(nfiles-1); fg++){
	
      tdrDraw(hist_pt_rat[fg][ij][jk],1,0,1,algo_col[ij],1001,0);

      leg_pt[jk]->AddEntry(hist_pt_rat[fg][ij][jk],jetname_mod[ij],"l"); 
      leg_pt[jk]->SetTextSize(0.02);
    }//fg


   double xval[noptbins], yval[noptbins], err_up[noptbins], err_dn[noptbins], yval1[noptbins], err_up1[noptbins], err_dn1[noptbins];
   for(int bn=0; bn<noptbins; bn++){
	xval[bn] = hist_radius[0][ij][jk]->GetBinLowEdge(bn+1);
//	if(ij==0&&jk==0) { cout<<bn+1<<" pt "<<xval[bn]<<endl;}
	yval[bn] = hist_radius[0][ij][jk]->GetBinContent(bn+1);
	err_up[bn] = hist_radius[0][ij][jk]->GetBinContent(bn+1) * rad_err_exp_up[ij][jk][bn];
	err_dn[bn] = hist_radius[0][ij][jk]->GetBinContent(bn+1) * rad_err_exp_dn[ij][jk][bn];
	yval1[bn] = hist_radius[1][ij][jk]->GetBinContent(bn+1);
        err_up1[bn] = hist_radius[1][ij][jk]->GetBinContent(bn+1) * rad_err_th_up[ij][jk][bn];
        err_dn1[bn] = hist_radius[1][ij][jk]->GetBinContent(bn+1) * rad_err_th_dn[ij][jk][bn];
   	}
   err_rad_exp[ij][jk] = new TGraphAsymmErrors(noptbins,xval,yval,NULL,NULL,err_up,err_dn);
   err_rad_th[ij][jk] = new TGraphAsymmErrors(noptbins,xval,yval1,NULL,NULL,err_up1,err_dn1);

  }//ij
/*
 c2[jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);


for(int fg=0; fg<(nfiles-1); fg++){
 for(int ij=0; ij<nalgo; ij++){

  hist_pt_rat[fg][ij][jk]->SetLineColor(algo_col[ij]);
  hist_pt_rat[fg][ij][jk]->SetMinimum(0.);
  hist_pt_rat[fg][ij][jk]->SetMaximum(3.);
if(fg==0&&ij==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
  }
 }

line->Draw();
*/
sprintf(name,"Final_Pt_Plots/Unfolded_Run2016/Ex_Cor_84/PH_Hwg/%s.eps",c2[jk]->GetName());
c2[jk]->SaveAs(name);

  }//jk


TCanvas *c3[netarange];

TLegend *leg_radius[netarange];
TLegend *leg_err[netarange];

 for(int jk=0; jk<netarange; jk++){

  sprintf(name,"Di_Ratio_Compare_Canv_EtaBin%i",jk+1);
  c3[jk] = tdrCanvas(name,hist_radius[0][ref_rad][jk],6,0);

  leg_radius[jk] = tdrLeg(0.43,0.625,0.9,0.9);
  leg_err[jk] = tdrLeg(0.7,0.75,0.9,0.9);
  leg_err[jk]->SetTextFont(42);
  leg_err[jk]->SetTextSize(0.038);

  c3[jk]->cd(1);
  
  gPad->SetLogx(1);
  gPad->SetLogy(0);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.06);

  TString text1;
  text1+=  ybinname[jk];

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.1,leg_y1,text1);

  TLatex latex1;
  latex1.SetNDC();
  latex1.SetTextAngle(0);
  latex1.SetTextColor(kRed);

  latex1.SetTextFont(42);
  latex1.SetTextAlign(31);
  latex1.SetTextSize(0.035);

  latex1.DrawLatex(0.5*(leg_x1+leg_x2)+0.375,leg_y1-0.2,"Col Lines : MC");
  latex1.DrawLatex(0.5*(leg_x1+leg_x2)+0.4,leg_y1-0.15,"Col Symbols : Data");

  for(int ij=0; ij<nalgo; ij++){
   for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC/Data");

      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(2.);

        }
   if(fg==0){
   	     tdrDraw(hist_radius[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,col[fg] ,1001,2);
	}
	else{
		tdrDraw(hist_radius[fg][ij][jk],1,0,1,algo_col[ij] ,1001,0);
		hist_radius[fg][ij][jk]->SetLineWidth(2);
	}
if(fg==0){	hist_radius[fg][ij][jk]->SetMarkerSize(1);  }
if(fg!=0)  {   leg_radius[jk]->AddEntry(hist_radius[fg][ij][jk],jetname_mod[ij],"l"); }

	leg_radius[jk]->SetTextSize(0.0325);
	leg_radius[jk]->SetTextFont(42);
    }//fg
 }//ij

  
  for(int ij=0; ij<nalgo; ij++){

  err_rad_exp[ij][jk]->SetFillColor(algo_col[ij]);
  err_rad_exp[ij][jk]->SetFillStyle(3005);
  err_rad_exp[ij][jk]->Draw("SAME:E3");

  err_rad_th[ij][jk]->SetFillColor(algo_col[ij]);
  err_rad_th[ij][jk]->SetFillStyle(3004);
  err_rad_th[ij][jk]->Draw("SAME:E3");
  }
/*
  err_rad_exp[0][jk]->SetFillColor(1);
  err_rad_th[0][jk]->SetFillColor(1);
*/
  leg_err[jk]->AddEntry(err_rad_exp[0][jk],err_name[0],"f");
  leg_err[jk]->AddEntry(err_rad_th[0][jk],err_name[1],"f");
//  leg_err[jk]->Draw();

  sprintf(name,"Final_Ratio_Plots/Unfolded_Run2016/Ex_Cor_84/%s/PH_Hwg/%s_PHHwg.eps",unf_title[unf_choice],c3[jk]->GetName());
  c3[jk]->SaveAs(name);

  }//jk

}

int main()
{
Compare_FinalUnfoldedPlot();
}
