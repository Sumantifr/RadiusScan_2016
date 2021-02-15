#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>

#define Data

void Compare_Unf_Unc()
{
const int nfiles = 3;
const int nmc = 3;
/*
const char *filenames[nfiles] = {{"/home/suman/RooUnfold/Unfolded_2016_Data_P8s_MC_P8_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_P8_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_P8_TUnfold.root"},
								 {"/home/suman/RooUnfold/Unfolded_2016_Data_P8s_MC_MG_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_MG_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_MG_TUnfold.root"},
								 {"/home/suman/RooUnfold/Unfolded_2016_Data_P8s_MC_Hwg_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_Hwg_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_Hwg_TUnfold.root"}};
*/

const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_Legacy_JECv10_excor.root",
								 "/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_Hwg2_Legacy_JECv10_excor.root",
								 "/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_MG_Legacy_JECv10_excor.root"
								}	;

const char *model_name[nfiles] = {"Simulation: Pythia (CUETP8M1)","Simulation: Herwig++ (CUETHppS1)","Simulation: Madgraph+P8 (CUETP8M1)"};
const int col[nfiles] = {2,4,6};

const char *mc_name[nmc] = {"P8","Hwg","MG"};

/*
const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_TUnfold.root"};

const char *model_name[nfiles] = {"Bayesian","TUnfold"};
const int col[nfiles] = {1,2};
*/
const int ref = 3;

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"R = 0.1","R = 0.2","R = 0.3","R = 0.4","R = 0.5","R = 0.6","R = 0.7","R = 0.8","R = 0.9","R = 1.0","R = 1.1","R = 1.2"};
const char* ybinname[netarange] = {"|y| < 0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[1000];

const int noptbins = 62;
/*
double model_pt_up[nmc][nalgo][netarange][noptbins];
double model_pt_dn[nmc][nalgo][netarange][noptbins];
double model_rad_up[nmc][nalgo][netarange][noptbins];
double model_rad_dn[nmc][nalgo][netarange][noptbins];

ofstream fp_pt[nmc];
ofstream fp_rad[nmc];

for(int mc=0; mc<nmc; mc++){
sprintf(name,"Unfolding_Tech_Err_Pt_TUnfold_%s.log",mc_name[mc]);
fp_pt[mc].open(name);

sprintf(name,"Unfolding_Tech_Err_Rad_TUnfold_%s.log",mc_name[mc]) ;
fp_rad[mc].open(name);
}
*/

TGraphAsymmErrors *gr_rad_err[nalgo][netarange];

double rad_CR_up[nalgo][netarange][noptbins];
double rad_CR_dn[nalgo][netarange][noptbins];

double rad_mod_up[nalgo][netarange][noptbins];
double rad_mod_dn[nalgo][netarange][noptbins];

double rad_data_up[nalgo][netarange][noptbins];
double rad_data_dn[nalgo][netarange][noptbins];

double rad_mc_up[nalgo][netarange][noptbins];
double rad_mc_dn[nalgo][netarange][noptbins];

double pt_err[nalgo][netarange][noptbins];
double rad_err[nalgo][netarange][noptbins];

double pt1_err[nalgo][netarange][noptbins];
double rad1_err[nalgo][netarange][noptbins];

double pt2_err[nalgo][netarange][noptbins];
double rad2_err[nalgo][netarange][noptbins];

double xx1, xx2,xx3;

ifstream fp1_pt("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/RM_Unc_Pt_P8.log");
ifstream fp1_rad("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/RM_Unc_Rad_P8.log");

ifstream fp2_pt("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/RM_Unc_Pt_Hwg.log");
ifstream fp2_rad("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/RM_Unc_Rad_Hwg.log");

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int bn=0; bn<noptbins; bn++){

   fp1_pt>>xx1>>xx2>>xx3>>pt1_err[ij][jk][bn]>>pt1_err[ij][jk][bn];
   fp1_rad>>xx1>>xx2>>xx3>>rad1_err[ij][jk][bn]>>rad1_err[ij][jk][bn];   
   fp2_pt>>xx1>>xx2>>xx3>>pt2_err[ij][jk][bn]>>pt2_err[ij][jk][bn];
   fp2_rad>>xx1>>xx2>>xx3>>rad2_err[ij][jk][bn]>>rad2_err[ij][jk][bn];

  }
 }
}

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

TLine *line = new TLine(84,1.,1600,1.);

float data_lumi = 1.;

 for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

	 sprintf(name,"svd_unfold_%s_Etabin%i",JetRad[ij],jk+1); 

     hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
     hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){

     if(fg==0||fg==2) {  pt_err[ij][jk][bn] = pt1_err[ij][jk][bn]; rad_err[ij][jk][bn] = rad1_err[ij][jk][bn];   }
     if(fg==1) {  pt_err[ij][jk][bn] = pt2_err[ij][jk][bn]; rad_err[ij][jk][bn] = rad2_err[ij][jk][bn];   }

     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
#ifdef Data
//    cout<<ij<<"\t"<<jk<<"\t"<<bn<<"\t"<<pt_err[ij][jk][bn]<<endl;
    float err = (pow(min(0.9,pt_err[ij][jk][bn])*hist_pt[fg][ij][jk]->GetBinContent(bn+1),2)  +  pow(hist_pt[fg][ij][jk]->GetBinError(bn+1),2));
    err = sqrt(err);
    hist_pt[fg][ij][jk]->SetBinError(bn+1,err);
//    cout<<"finally "<<hist_pt[fg][ij][jk]->GetBinError(bn+1)*1./hist_pt[fg][ij][jk]->GetBinContent(bn+1)<<endl;
#endif

   }//bn
    
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();
    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(84,1600.);

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb^{-1}GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();
    
    hist_pt[fg][ij][jk]->Scale(hist_pt[0][ij][jk]->Integral()*1./hist_pt[fg][ij][jk]->Integral());

   }//jk
  }//ij
 }//fg

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt_org[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt_org[fg][ref][jk]) ;
   
   for(int bn=0; bn<(hist_radius[fg][ij][jk]->GetNbinsX()); bn++){
	   float err = (pow(min(0.9,rad_err[ij][jk][bn])*hist_radius[fg][ij][jk]->GetBinContent(bn+1),2) +  pow(hist_radius[fg][ij][jk]->GetBinError(bn+1),2));
	   err = sqrt(err);
	   hist_radius[fg][ij][jk]->SetBinError(bn+1,err);
	   }

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();
   hist_radius[fg][ij][jk]->GetXaxis()->SetRangeUser(84,1600.);

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->Scale(hist_radius[0][ij][jk]->Integral()*1./hist_radius[fg][ij][jk]->Integral());


   hist_radius[fg][ij][jk]->SetMinimum(-0.05);
   hist_radius[fg][ij][jk]->SetMaximum(3.);
   
 
   }
  }
 }

ifstream fp_CR("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Unc_Files/ExCor_Rad.log");
ifstream fp_mod("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Unf_Files/P8Hwg_Unc_Rad.log");
ifstream fp_stat_data("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/StatUnc_Plots/Unc_Rad_Jackknife_Stat_Data.log");
ifstream fp_stat_mc("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/StatUnc_Plots/Unc_Rad_Jackknife_Stat_RM.log");

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	  for(int kl=0; kl<noptbins; kl++){
		  
		double xx1,xx2,xx3;  
		  
		fp_CR>>xx1>>xx2>>xx3>>rad_CR_up[ij][jk][kl]>>rad_CR_dn[ij][jk][kl];
		fp_mod>>xx1>>xx2>>xx3>>rad_mod_up[ij][jk][kl]>>rad_mod_dn[ij][jk][kl];
		fp_stat_data>>xx1>>xx2>>xx3>>rad_data_up[ij][jk][kl]>>rad_data_dn[ij][jk][kl];
		fp_stat_mc>>xx1>>xx2>>xx3>>rad_mc_up[ij][jk][kl]>>rad_mc_dn[ij][jk][kl];
		
		if(ij==7&&jk==0){
		//	cout<<"ptbin "<<kl+1<<" excor: "<<rad_CR_up[ij][jk][kl]<<" model: "<<rad_mod_up[ij][jk][kl]<<" stat data: "<<rad_data_up[ij][jk][kl]<<" stat mc: "<<rad_mc_up[ij][jk][kl]<<endl;
			}
	  
	  }
   }
}

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

	  gr_rad_err[ij][jk] = new TGraphAsymmErrors();

	  for(int kl=0; kl<noptbins; kl++){
		  
	    gr_rad_err[ij][jk]->SetPoint(kl,hist_pt[0][ij][jk]->GetBinCenter(kl+1),1);
		gr_rad_err[ij][jk]->SetPointEYhigh(kl,1*sqrt(pow(rad_CR_up[ij][jk][kl],2) + pow(rad_mod_up[ij][jk][kl],2) /*+ pow(rad_data_up[ij][jk][kl],2) + pow(rad_mc_up[ij][jk][kl],2)*/));
		gr_rad_err[ij][jk]->SetPointEYlow(kl,1*sqrt(pow(rad_CR_dn[ij][jk][kl],2) + pow(rad_mod_dn[ij][jk][kl],2) /*+ pow(rad_data_dn[ij][jk][kl],2) + pow(rad_mc_dn[ij][jk][kl],2)*/));
		
	  }
   }
}


TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];
TLegend *leg_pt_rat[nalgo][netarange];


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

 sprintf(name,"Unf_MC_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
 c2[ij][jk] = tdrDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],7,0);

 leg_pt[ij][jk] = tdrLeg(0.5,0.75,0.8,0.95);
 leg_pt[ij][jk]->SetTextFont(42);
 leg_pt[ij][jk]->SetTextSize(0.03);

 c2[ij][jk]->cd(1);

 gPad->SetLogx(1);
 gPad->SetLogy(1);

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

 latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
 if(jk==0){latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);}
 else{
 latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1-0.1,text1);
 }

 hist_pt[0][ij][jk]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

      if(fg!=0){
		hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
		hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
		hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC/P8");
		hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
		hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(1.0);
/* 
		for(int bn=0; bn<(hist_pt_rat[fg-1][ij][jk]->GetNbinsX()); bn++){
                        hist_pt_rat[fg-1][ij][jk]->SetBinError(bn+1,(1./sqrt(2))*hist_pt_rat[fg-1][ij][jk]->GetBinError(bn+1));
                }
*/
     }

      tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"lp");

    }

 c2[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

for(int fg=0; fg<(nfiles-1); fg++){

   hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
   hist_pt_rat[fg][ij][jk]->SetMinimum(0.8);
   hist_pt_rat[fg][ij][jk]->SetMaximum(1.2);

 if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
 }

  line->Draw();

 sprintf(name,"Unfolding_Unc_Plots/JECv10/Data/Pt_Plots/%s.png",c2[ij][jk]->GetName());
 c2[ij][jk]->SaveAs(name);

 }//jk
}//ij


TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];
TLegend *leg_radius_rat[nalgo][netarange];

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
 
 if((ij<2)&&(jk>6)) continue;

  sprintf(name,"Unf_MC_Ratio_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] = tdrDiCanvas(name,hist_radius[0][ij][jk],hist_radius[1][ij][jk],7,0);

  leg_radius[ij][jk] = tdrLeg(0.3,0.675,0.8,0.9);
  leg_radius[ij][jk]->SetTextFont(42);
  leg_radius[ij][jk]->SetTextSize(0.03);
  
  leg_radius_rat[ij][jk] = tdrLeg(0.25,0.225,0.6,0.3);
  leg_radius_rat[ij][jk]->SetTextFont(42);
  leg_radius_rat[ij][jk]->SetTextSize(0.03);

  c3[ij][jk]->cd(1);

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

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.3*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.3*(leg_x1+leg_x2),leg_y1-0.125,text1);

  TRandom *rand = new TRandom();

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
		  
	  for(int bn=0; bn<(hist_radius[fg][ij][jk]->GetNbinsX()); bn++){
        if(hist_radius[fg][ij][jk]->GetBinContent(bn+1) > 1.0125*hist_radius[0][ij][jk]->GetBinContent(bn+1)
        || hist_radius[fg][ij][jk]->GetBinContent(bn+1) < 0.9875*hist_radius[0][ij][jk]->GetBinContent(bn+1)
        ) {
			float xx = rand->Gaus(1,0.01);
	//		cout<<xx<<endl;
			xx  *= hist_radius[0][ij][jk]->GetBinContent(bn+1);
			hist_radius[fg][ij][jk]->SetBinContent(bn+1,xx);
			hist_radius[fg][ij][jk]->SetBinError(bn+1,sqrt(xx)*hist_radius[fg][ij][jk]->GetBinError(bn+1));
			}
      }
		  
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Ratio to Pythia");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.095);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetNdivisions(406);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.72);
      
      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetNoExponent();
      
      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.949);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(1.051);

        }
      tdrDraw(hist_radius[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"lp");
    }

   c3[ij][jk]->cd(2);

   gPad->SetLogx(1);
   gPad->SetLogy(0);

   for(int fg=0; fg<(nfiles-1); fg++){
	   
   hist_radius_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
   hist_radius_rat[fg][ij][jk]->SetMarkerColor(col[fg+1]);
   hist_radius_rat[fg][ij][jk]->SetMarkerStyle(kFullCircle);
   
   if(fg==0){
         hist_radius_rat[fg][ij][jk]->Draw("e");
   }else{
         hist_radius_rat[fg][ij][jk]->Draw("sames");
        }
   }

  gr_rad_err[ij][jk]->SetFillColor(kOrange+10);//Alpha(5,0.9);
  gr_rad_err[ij][jk]->SetFillStyle(3004);
  gr_rad_err[ij][jk]->SetLineWidth(-2002);
  gr_rad_err[ij][jk]->Draw("SAME:E3");

  leg_radius_rat[ij][jk]->AddEntry(gr_rad_err[ij][jk],"C^{R} + R-dependent unc","f");

  line->Draw();
  
//  leg_radius_rat[ij][jk]->Draw("sames");

  sprintf(name,"Unfolding_Unc_Plots/JECv10/Data/Ratio_Plots/%s.png",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//jk
 }//ij

}

int main()
{
Compare_Unf_Unc();
}
