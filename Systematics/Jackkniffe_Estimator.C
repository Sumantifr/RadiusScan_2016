#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TFile.h>
#include <fstream>
#include <TGraphErrors.h>
#include "TPaletteAxis.h"
#include "TStyle.h"
#include "TPaletteAxis.h"
#include "TStyle.h"

#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

using namespace std;

const int nalgo = 12;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
const char *jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char *jetradname[nalgo] = {"R=0.1/R=0.4","R=0.2/R=0.4","R=0.3/R=0.4","R=0.4/R=0.4","R=0.5/R=0.4","R=0.6/R=0.4","R=0.7/R=0.4","R=0.8/R=0.4","R=0.9/R=0.4","R=1.0/R=0.4","R=1.1/R=0.4","R=1.2/R=0.4"};
const char *jetradnamen[nalgo] = {"R=0.1","R=0.2","R=0.3","R=0.4","R=0.5","R=0.6","R=0.7","R=0.8","R=0.9","R=1.0","R=1.1","R=1.2"};

const int netarange = 10;
const char *ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"};
//const char *ybinname[netarange] = {"|y|<0.5"};

const int ncomb = 10;

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int ref_rad = 3;

char name[100];

float leg_x1 = 0.25;
float leg_y1 = 0.6;
float leg_x2 = 0.45;
float leg_y2 = 0.85;

void Jackkniffe_Estimator()
{
TFile *filein = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Stat/Legacy2016_07Aug_JECV18statmk_tot.root","read");	
//TFile *filein = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_stat.root","read");
//TFile *filein = new TFile("/home/suman/RooUnfold/Unfolded_Data_NTuple_MC_P8_JECv15_RM_mkStat.root");

TH1D *hist_pt[nalgo][netarange][ncomb];
TH1D *hist_pt_sub[nalgo][netarange][ncomb];
TH1D *hist_rad[nalgo][netarange][ncomb];

TH1D *hist_pt_full[nalgo][netarange];
TH1D *hist_rad_full[nalgo][netarange];

ofstream fp_pt;
//fp_pt.open("Unc_Pt_Jackknife_Stat_Data.log") ;
fp_pt.open("stat_pt.log");

ofstream fp_rad;
//fp_rad.open("Unc_Rad_Jackknife_Stat_Data.log") ;
fp_rad.open("stat_rad.log");

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
/*
   sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_pt_full[ij][jk] = (TH1D*)filein->Get(name);
*/	  
   for(int kl=0; kl<ncomb; kl++){
	sprintf(name,"JetpT_%s_EtaBin%i_Comb%i",JetRad[ij],jk+1,kl+1);
//	sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i_Comb%i",JetRad[ij],jk+1,kl+1);
//	sprintf(name,"svd_unfold_%s_Etabin%i_comb%i",JetRad[ij],jk+1,kl+1);
	hist_pt[ij][jk][kl] = (TH1D*)filein->Get(name);
	
   }//kl
   
  }//jk
 }//ij


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<ncomb; kl++){
        hist_rad[ij][jk][kl] = (TH1D*)hist_pt[ij][jk][kl]->Clone();
		hist_rad[ij][jk][kl]->Divide(hist_pt[ref_rad][jk][kl]);
   }//kl
//		hist_rad_full[ij][jk] = (TH1D*)hist_pt_full[ij][jk]->Clone();
//		hist_rad_full[ij][jk]->Divide(hist_pt_full[ref_rad][jk]);
 }//jk
}//ij


double pt_mean[nalgo][netarange][noptbins];
double pt_rms[nalgo][netarange][noptbins];
double pt_stdev[nalgo][netarange][noptbins];

double rad_mean[nalgo][netarange][noptbins];

double rad_rms[nalgo][netarange][noptbins];
double rad_stdev[nalgo][netarange][noptbins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
  for(int bn=0; bn<noptbins; bn++){
  
   double sum = 0;
   double sq_sum = 0;

   double rad_sum = 0;  
   double rad_sq_sum = 0;

   double ptsumx[ncomb] = {0};
   double radsumx[ncomb] = {0};
   
    for(int kl=0; kl<int(ncomb); kl++){
		sum += hist_pt[ij][jk][kl]->GetBinContent(bn+1);
		rad_sum += hist_rad[ij][jk][kl]->GetBinContent(bn+1);
	}
  
    pt_mean[ij][jk][bn] = sum*1./(ncomb);
    rad_mean[ij][jk][bn] = rad_sum*1./(ncomb);
    
     for(int kl=0; kl<int(ncomb); kl++){
		sq_sum += pow((hist_pt[ij][jk][kl]->GetBinContent(bn+1) - pt_mean[ij][jk][bn]),2);
		rad_sq_sum += pow((hist_rad[ij][jk][kl]->GetBinContent(bn+1) - rad_mean[ij][jk][bn]),2);
	 }
   
	pt_rms[ij][jk][bn] = sq_sum * 1./ncomb;
	pt_rms[ij][jk][bn] *= (ncomb-1);
//	pt_rms[ij][jk][bn] *= (ncomb*1./(ncomb-1));
    pt_stdev[ij][jk][bn] =  sqrt(pt_rms[ij][jk][bn]) ;
	if(isnan(pt_stdev[ij][jk][bn])) { pt_stdev[ij][jk][bn] = 1.e-6; }
	
	rad_rms[ij][jk][bn] = rad_sq_sum * 1./ncomb;
	rad_rms[ij][jk][bn] *= (ncomb-1);
//	rad_rms[ij][jk][bn] *= (ncomb*1./(ncomb-1));
    rad_stdev[ij][jk][bn] =  sqrt(rad_rms[ij][jk][bn] );
	if(isnan(rad_stdev[ij][jk][bn])) { rad_stdev[ij][jk][bn] = 1.e-6; }
		}
	}
}

double corfactor_pt[nalgo][netarange][noptbins][noptbins];
double corfactor_rad[nalgo][netarange][noptbins][noptbins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){	 
   for(int am=0; am<noptbins; am++){
    for(int bn=0; bn<noptbins; bn++){
   
   double sumx = 0;
   for(int kl=0; kl<int(ncomb); kl++){
		sumx += (hist_pt[ij][jk][kl]->GetBinContent(am+1) - pt_mean[ij][jk][am])*(hist_pt[ref_rad][jk][kl]->GetBinContent(bn+1) - pt_mean[ref_rad][jk][bn]);		
	 }
	 corfactor_pt[ij][jk][am][bn]  = sumx * 1./(ncomb);
	 corfactor_pt[ij][jk][am][bn] *= (ncomb-1);
//	 corfactor_pt[ij][jk][am][bn] *= (ncomb*1./(ncomb-1));
  
   double sumy = 0;
   for(int kl=0; kl<int(ncomb); kl++){
		sumy += (hist_rad[ij][jk][kl]->GetBinContent(am+1) - rad_mean[ij][jk][am])*(hist_rad[ij][jk][kl]->GetBinContent(bn+1) - rad_mean[ij][jk][bn]);		
	 }
	 corfactor_rad[ij][jk][am][bn]  = sumy * 1./(ncomb);
//	 corfactor_rad[ij][jk][am][bn] *= (ncomb-1);
	 corfactor_rad[ij][jk][am][bn] *= (ncomb*1./(ncomb-1));

   }
  }
 }
}

TH1D *pt_err[nalgo][netarange];
TH1D *rad_err[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

  sprintf(name,"Pt_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
  pt_err[ij][jk] = new TH1D(name,name,noptbins,ptbins);
  pt_err[ij][jk]->Sumw2();

  sprintf(name,"Rad_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
  rad_err[ij][jk] = new TH1D(name,name,noptbins,ptbins);
  rad_err[ij][jk]->Sumw2();

 }
}

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
	for(int bn=0; bn<noptbins; bn++){
	
	 double err = 0;
	 
	 err = pt_stdev[ij][jk][bn]*1./ pt_mean[ij][jk][bn];//hist_pt_full[ij][jk]->GetBinContent(bn+1);
	 
	 if(isnan(err)) { err = 1.e-6; }
	 pt_err[ij][jk]->SetBinContent(bn+1,err*100);
	 
	 fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<err<<'\t'<<err<<endl;
	
//	 err = pow(pt_stdev[ij][jk][bn]*1./hist_pt_full[ij][jk]->GetBinContent(bn+1),2) + pow(pt_stdev[ref_rad][jk][bn]*1./hist_pt_full[ref_rad][jk]->GetBinContent(bn+1),2) - 2*corfactor_pt[ij][jk][bn][bn]*1./(hist_pt_full[ij][jk]->GetBinContent(bn+1) * hist_pt_full[ref_rad][jk]->GetBinContent(bn+1) ) ;
	 err = pow(pt_stdev[ij][jk][bn]*1./pt_mean[ij][jk][bn],2) + pow(pt_stdev[ref_rad][jk][bn]*1./pt_mean[ref_rad][jk][bn],2) - 2*corfactor_pt[ij][jk][bn][bn]*1./(pt_mean[ij][jk][bn] * pt_mean[ref_rad][jk][bn] ) ;
	 
	 err = sqrt(err);
	
	 if(ij==7&&jk==0){
	 cout<<"err "<<err<<" stdev "<<rad_stdev[ij][jk][bn]*1./rad_mean[ij][jk][bn]<<endl;
	 }
	 
	 if(isnan(err)) { err = 1.e-6; }
	 rad_err[ij][jk]->SetBinContent(bn+1,err*100);

   }
 }
}


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
	 
	 pt_err[ij][jk]->SetStats(0);
	 
	 pt_err[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
	 pt_err[ij][jk]->GetXaxis()->SetTitleSize(0.06);
     pt_err[ij][jk]->GetXaxis()->CenterTitle();
     pt_err[ij][jk]->GetXaxis()->SetLabelSize(0.05);
     pt_err[ij][jk]->GetXaxis()->SetNdivisions(510);
     pt_err[ij][jk]->GetXaxis()->SetRangeUser(84,3000);

     pt_err[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection(in %)");
     pt_err[ij][jk]->GetYaxis()->SetTitleSize(0.06);
     pt_err[ij][jk]->GetYaxis()->CenterTitle();
     pt_err[ij][jk]->GetYaxis()->SetLabelSize(0.05);
     pt_err[ij][jk]->GetYaxis()->SetTitleOffset(1.05);
     
     pt_err[ij][jk]->SetLineColor(kBlue);
     pt_err[ij][jk]->SetMarkerColor(kBlue);

     pt_err[ij][jk]->SetMaximum(5.1);
     pt_err[ij][jk]->SetMinimum(-0.01);
     pt_err[ij][jk]->Smooth(1);
     
     for(int bn=0; bn<(noptbins); bn++){
		fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<0.01*pt_err[ij][jk]->GetBinContent(bn+1)<<'\t'<<0.01*pt_err[ij][jk]->GetBinContent(bn+1)<<endl;
	 }
     
     rad_err[ij][jk]->SetStats(0);
	 
	 rad_err[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
	 rad_err[ij][jk]->GetXaxis()->SetTitleSize(0.06);
     rad_err[ij][jk]->GetXaxis()->CenterTitle();
     rad_err[ij][jk]->GetXaxis()->SetLabelSize(0.05);
     rad_err[ij][jk]->GetXaxis()->SetNdivisions(510);
     rad_err[ij][jk]->GetXaxis()->SetRangeUser(84,3000);

     rad_err[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection(in %)");
     rad_err[ij][jk]->GetYaxis()->SetTitleSize(0.06);
     rad_err[ij][jk]->GetYaxis()->CenterTitle();
     rad_err[ij][jk]->GetYaxis()->SetLabelSize(0.05);
     rad_err[ij][jk]->GetYaxis()->SetTitleOffset(1.05);
     
     rad_err[ij][jk]->SetLineColor(kRed);
     rad_err[ij][jk]->SetMarkerColor(kRed);

     rad_err[ij][jk]->SetMaximum(5.1);
     rad_err[ij][jk]->SetMinimum(-0.01);
     rad_err[ij][jk]->Smooth(1);
     
     for(int bn=0; bn<(noptbins); bn++){
		fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<0.01*rad_err[ij][jk]->GetBinContent(bn+1)<<'\t'<<0.01*rad_err[ij][jk]->GetBinContent(bn+1)<<endl;
	 }
 }
}

TCanvas *c1 = new TCanvas("c1","c1",50,50,800,600);
//c1->Divide(1,2);
c1->cd(1);
gPad->SetLogx(1);
pt_err[7][0]->Draw("hist");
rad_err[7][0]->Draw("hist,sames");
c1->SaveAs("Error.png");

TGraphErrors *gr_pt[nalgo][netarange];
TGraphErrors *gr_rad[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
	
	double yy[noptbins] = {0};
	double yyerr[noptbins] = {0};

    for(int bn=0; bn<(noptbins); bn++){
        yyerr[bn] = pt_err[ij][jk]->GetBinContent(bn+1);
        if(isnan(yyerr[bn])) { yyerr[bn] = 1.e-6; }
    }

   sprintf(name,"Pt_Error_%s_EtaBin%i",JetRad[ij],jk+1);
   gr_pt[ij][jk] = new TGraphErrors(noptbins,ptbins,yy,NULL,yyerr);

   gr_pt[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
   gr_pt[ij][jk]->GetXaxis()->SetTitleSize(0.05);
   gr_pt[ij][jk]->GetXaxis()->CenterTitle();
   gr_pt[ij][jk]->GetXaxis()->SetLabelSize(0.05);
   gr_pt[ij][jk]->GetXaxis()->SetNdivisions(510);
   gr_pt[ij][jk]->GetXaxis()->SetRangeUser(84,3000.);

   gr_pt[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection (in %)");
   gr_pt[ij][jk]->GetYaxis()->SetTitleSize(0.05);
   gr_pt[ij][jk]->GetYaxis()->CenterTitle();
   gr_pt[ij][jk]->GetYaxis()->SetLabelSize(0.05);
   gr_pt[ij][jk]->GetYaxis()->SetTitleOffset(1.05);

   gr_pt[ij][jk]->SetMarkerStyle(kFullCircle);
   gr_pt[ij][jk]->SetMarkerColor(kBlack);
   gr_pt[ij][jk]->SetLineColor(kBlue);
   gr_pt[ij][jk]->SetLineWidth(-2002);
   gr_pt[ij][jk]->SetFillStyle(3004);
   gr_pt[ij][jk]->SetFillColor(kBlue);

   gr_pt[ij][jk]->SetMaximum(5.1);
   gr_pt[ij][jk]->SetMinimum(-5.1); 
   
   double yyerrx[noptbins] = {0};

   for(int bn=0; bn<(noptbins); bn++){
       yyerrx[bn] = rad_err[ij][jk]->GetBinContent(bn+1);
       if(isnan(yyerr[bn])) { yyerrx[bn] = 1.e-6; }
   }

   sprintf(name,"Rad_Error_%s_EtaBin%i",JetRad[ij],jk+1);
   gr_rad[ij][jk] = new TGraphErrors(noptbins,ptbins,yy,NULL,yyerrx);

   gr_rad[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
   gr_rad[ij][jk]->GetXaxis()->SetTitleSize(0.05);
   gr_rad[ij][jk]->GetXaxis()->CenterTitle();
   gr_rad[ij][jk]->GetXaxis()->SetLabelSize(0.05);
   gr_rad[ij][jk]->GetXaxis()->SetNdivisions(510);

   gr_rad[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Ratio of Xsections (in %)");
   gr_rad[ij][jk]->GetYaxis()->SetTitleSize(0.045);
   gr_rad[ij][jk]->GetYaxis()->CenterTitle();
   gr_rad[ij][jk]->GetYaxis()->SetLabelSize(0.05);
   gr_rad[ij][jk]->GetYaxis()->SetTitleOffset(1.05);
   
   gr_rad[ij][jk]->GetXaxis()->SetRangeUser(84,3000.);
   gr_rad[ij][jk]->SetMarkerStyle(kFullSquare);
   gr_rad[ij][jk]->SetMarkerColor(kBlack);
   gr_rad[ij][jk]->SetLineColor(kRed);
   gr_rad[ij][jk]->SetFillStyle(3005);
   gr_rad[ij][jk]->SetLineWidth(-2002);
   gr_rad[ij][jk]->SetFillColor(kRed);

   gr_rad[ij][jk]->SetMaximum(5.1);
   gr_rad[ij][jk]->SetMinimum(-5.1); 
   
 }
}

TCanvas *c2[nalgo][netarange];
TCanvas *c3[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
  
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
  
//   sprintf(name,"Canvas_Stat_Pt_Unc_Jackknife_%s_EtaBin%i",JetRad[ij],jk+1);
   sprintf(name,"Canvas_Stat_Pt_Unc_Jackknife_%s_EtaBin%i",JetRad[ij],jk+1);
   c2[ij][jk] = tdrCanvas(name,pt_err[ij][jk],7,0);

   c2[ij][jk]->cd();

   gPad->SetLogx(1);
   
   gr_pt[ij][jk]->Draw("AP");
   gr_pt[ij][jk]->Draw("SAME:E3");
   
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.225,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.15,text1);

   sprintf(name,"StatUnc_Plots/Pt_Plots/Data/%s.png",c2[ij][jk]->GetName());
   c2[ij][jk]->SaveAs(name);
    
 //  sprintf(name,"Canvas_Stat_Rad_Unc_Jackknife_%s_EtaBin%i",JetRad[ij],jk+1);
   sprintf(name,"Canvas_Stat_Rad_Unc_Jackknife_%s_EtaBin%i",JetRad[ij],jk+1);
   c3[ij][jk] = tdrCanvas(name,rad_err[ij][jk],7,0);
   
   gPad->SetLogx(1);
   
   gr_rad[ij][jk]->Draw("AP");
   gr_rad[ij][jk]->Draw("SAME:E3");
   
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.225,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.15,text1);

   sprintf(name,"StatUnc_Plots/Ratio_Plots/Data/%s.png",c3[ij][jk]->GetName());
   c3[ij][jk]->SaveAs(name);
  }
}

TFile *fileout = new TFile("Correlation_output_Jackknife.root","RECREATE");

TH2D *hist2d_ptcov[nalgo][netarange];
TH2D *hist2d_ptcor[nalgo][netarange];

TH2D *hist2d_radcov[nalgo][netarange];
TH2D *hist2d_radcor[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
 
  sprintf(name,"twoD_Covariance_pt_%s_EtaBin%i",JetRad[ij],jk+1);
  hist2d_ptcov[ij][jk] = new TH2D(name,name,noptbins,ptbins,noptbins,ptbins);
  
  sprintf(name,"twoD_Correlation_pt_%s_EtaBin%i",JetRad[ij],jk+1);
  hist2d_ptcor[ij][jk] = new TH2D(name,name,noptbins,ptbins,noptbins,ptbins);
  
  sprintf(name,"twoD_Covariance_rad_%s_EtaBin%i",JetRad[ij],jk+1);
  hist2d_radcov[ij][jk] = new TH2D(name,name,noptbins,ptbins,noptbins,ptbins);
  hist2d_radcov[ij][jk]->Sumw2();
  
  sprintf(name,"twoD_Correlation_rad_%s_EtaBin%i",JetRad[ij],jk+1);
  hist2d_radcor[ij][jk] = new TH2D(name,name,noptbins,ptbins,noptbins,ptbins);
  hist2d_radcor[ij][jk]->Sumw2();
  
  for(int am=0; am<noptbins; am++){
    for(int bn=0; bn<noptbins; bn++){
	
		hist2d_ptcov[ij][jk]->SetBinContent(am+1,bn+1,corfactor_pt[ij][jk][am][bn]);
//		hist2d_ptcor[ij][jk]->SetBinContent(am+1,bn+1,corfactor_pt[ij][jk][am][bn]*1./sqrt(fabs(corfactor_pt[ij][jk][am][am])*(fabs(corfactor_pt[ij][jk][bn][bn]))));
		hist2d_ptcor[ij][jk]->SetBinContent(am+1,bn+1,corfactor_pt[ij][jk][am][bn]*1./(pt_stdev[ij][jk][am]*pt_stdev[ref_rad][jk][bn]));
	
	    hist2d_radcov[ij][jk]->SetBinContent(am+1,bn+1,corfactor_rad[ij][jk][am][bn]);
		hist2d_radcor[ij][jk]->SetBinContent(am+1,bn+1,corfactor_rad[ij][jk][am][bn]*1./sqrt(fabs(corfactor_rad[ij][jk][am][am])*(fabs(corfactor_rad[ij][jk][bn][bn]))));
	
	
	 }
   }
 }
}



TLatex latex;
latex.SetNDC();
latex.SetTextAngle(0);
latex.SetTextColor(kRed+4);

latex.SetTextFont(42);
latex.SetTextAlign(31);
latex.SetTextSize(0.045);

TString text2;
text2+= "Anti-k_{T} CHS";

TCanvas *canv_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
	 
  TString text;
  text+= jetradnamen[ij];
  TString text1;
  text1+=  ybinname[jk];	 

  sprintf(name,"Cor_Mat_Jackknife_Pt_%s_EtaBin%i",JetRad[ij],jk+1);
//  canv_pt[ij][jk] = new TCanvas(name,name,50,50,1200,600);
//  canv_pt[ij][jk]->Divide(2,1);
  canv_pt[ij][jk] = new TCanvas(name,name,50,50,800,600);
  
  canv_pt[ij][jk]->SetFillColor(0);
  canv_pt[ij][jk]->SetBorderMode(0);
  canv_pt[ij][jk]->SetFrameFillStyle(0);
  canv_pt[ij][jk]->SetFrameBorderMode(0);
 /*
  canv_pt[ij][jk]->SetLeftMargin( 0.1*600/800 );
  canv_pt[ij][jk]->SetRightMargin( 0.1*600/600 + 0.05);
  canv_pt[ij][jk]->SetTopMargin( 0.08*800/600 );
  canv_pt[ij][jk]->SetBottomMargin( 0.1*800/600 );
*/
  sprintf(name,"AK%i Jet p_{T} (GeV)",ij+1);
  hist2d_ptcov[ij][jk]->GetXaxis()->SetTitle(name);
  hist2d_ptcov[ij][jk]->GetXaxis()->SetTitleSize(0.05);
  hist2d_ptcov[ij][jk]->GetXaxis()->SetLabelSize(0.05);
  hist2d_ptcov[ij][jk]->GetXaxis()->CenterTitle();
  hist2d_ptcov[ij][jk]->GetXaxis()->SetRangeUser(84,3001);
  hist2d_ptcov[ij][jk]->GetXaxis()->SetNdivisions(406);
  
  hist2d_ptcov[ij][jk]->GetYaxis()->SetTitle("AK4 Jet p_{T} (GeV)");
  hist2d_ptcov[ij][jk]->GetYaxis()->SetTitleSize(0.05);
  hist2d_ptcov[ij][jk]->GetYaxis()->SetLabelSize(0.05);
  hist2d_ptcov[ij][jk]->GetYaxis()->CenterTitle();
  hist2d_ptcov[ij][jk]->GetYaxis()->SetRangeUser(84,3001);
  hist2d_ptcov[ij][jk]->GetYaxis()->SetNdivisions(406);
	
//  hist2d_ptcov[ij][jk]->GetZaxis()->SetTitle("Correlation Coefficient");
  hist2d_ptcov[ij][jk]->GetZaxis()->SetTitleSize(0.035);
  hist2d_ptcov[ij][jk]->GetZaxis()->SetLabelSize(0.035);
  hist2d_ptcov[ij][jk]->GetZaxis()->CenterTitle();
  hist2d_ptcov[ij][jk]->GetZaxis()->SetNdivisions(406);	

  hist2d_ptcov[ij][jk]->SetStats(0);
  hist2d_ptcov[ij][jk]->SetStats(0);

  assert(hist2d_ptcov[ij][jk]);
  hist2d_ptcov[ij][jk]->GetYaxis()->SetTitleOffset(1.1);
  hist2d_ptcov[ij][jk]->GetXaxis()->SetTitleOffset(1.1);
  
  sprintf(name,"AK%i Jet p_{T} (GeV)",ij+1);
  hist2d_ptcor[ij][jk]->GetXaxis()->SetTitle(name);
  hist2d_ptcor[ij][jk]->GetXaxis()->SetTitleSize(0.05);
  hist2d_ptcor[ij][jk]->GetXaxis()->SetLabelSize(0.05);
  hist2d_ptcor[ij][jk]->GetXaxis()->CenterTitle();
  hist2d_ptcor[ij][jk]->GetXaxis()->SetRangeUser(84,3001);
  hist2d_ptcor[ij][jk]->GetXaxis()->SetNdivisions(406);
  hist2d_ptcor[ij][jk]->GetXaxis()->SetNoExponent();
  
  hist2d_ptcor[ij][jk]->GetYaxis()->SetTitle("AK4 Jet p_{T} (GeV)");
  hist2d_ptcor[ij][jk]->GetYaxis()->SetTitleSize(0.05);
  hist2d_ptcor[ij][jk]->GetYaxis()->SetLabelSize(0.05);
  hist2d_ptcor[ij][jk]->GetYaxis()->CenterTitle();
  hist2d_ptcor[ij][jk]->GetYaxis()->SetRangeUser(84,3001);
  hist2d_ptcor[ij][jk]->GetYaxis()->SetNdivisions(406);
  hist2d_ptcor[ij][jk]->GetYaxis()->SetNoExponent();
	
  hist2d_ptcor[ij][jk]->GetZaxis()->SetTitle("Correlation Coefficient");
  hist2d_ptcor[ij][jk]->GetZaxis()->SetTitleSize(0.045);
  hist2d_ptcor[ij][jk]->GetZaxis()->SetLabelSize(0.04);
  hist2d_ptcor[ij][jk]->GetZaxis()->CenterTitle();
  hist2d_ptcor[ij][jk]->GetZaxis()->SetNdivisions(406);	
  
  hist2d_ptcor[ij][jk]->SetStats(0); 
  hist2d_ptcor[ij][jk]->SetStats(0); 
  hist2d_ptcor[ij][jk]->SetMaximum(1.01);
  hist2d_ptcor[ij][jk]->SetMinimum(-1.01);

  assert(hist2d_ptcor[ij][jk]);
  hist2d_ptcor[ij][jk]->GetYaxis()->SetTitleOffset(1.1);
  hist2d_ptcor[ij][jk]->GetXaxis()->SetTitleOffset(1.1);
  
  canv_pt[ij][jk]->cd(1);
  
  gPad->SetLeftMargin( 0.1*600/800 + 0.05);
  gPad->SetRightMargin( 0.1*600/600 + 0.05);
  gPad->SetTopMargin( 0.08*800/600 );
  gPad->SetBottomMargin( 0.1*800/600 );
  /*
  hist2d_ptcov[ij][jk]->Draw("AXIS");
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  gPad->SetLogz(0);
  hist2d_ptcov[ij][jk]->Draw("colz");
  
  gPad->Update();
  TPaletteAxis *palette = (TPaletteAxis*)hist2d_ptcov[ij][jk]->GetListOfFunctions()->FindObject("palette");
  palette->SetX1NDC(0.875);
  palette->SetX2NDC(0.915);
  palette->SetY1NDC(0.13);
  palette->SetY2NDC(0.9);
  gPad->Modified();
  gPad->Update();
  
  latex.DrawLatex(0.45,0.7,text);
  latex.DrawLatex(0.55,0.925,text1);
  latex.DrawLatex(0.45,0.775,text2);

  canv_pt[ij][jk]->cd(2);
  
  gPad->SetLeftMargin( 0.1*600/800 + 0.025);
  gPad->SetRightMargin( 0.1*600/600 + 0.05);
  gPad->SetTopMargin( 0.08*800/600 );
  gPad->SetBottomMargin( 0.1*800/600 );
  */
  hist2d_ptcor[ij][jk]->Draw("AXIS");
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  hist2d_ptcor[ij][jk]->Draw("colz");
  
  gPad->Update();
  TPaletteAxis *palette1 = (TPaletteAxis*)hist2d_ptcor[ij][jk]->GetListOfFunctions()->FindObject("palette");
  palette1->SetX1NDC(0.85);
  palette1->SetX2NDC(0.905);
  palette1->SetY1NDC(0.13);
  palette1->SetY2NDC(0.9);
  canv_pt[ij][jk]->Modified();
  canv_pt[ij][jk]->Update();
  
  latex.DrawLatex(0.45,0.7,text);
  latex.DrawLatex(0.55,0.925,text1);
  latex.DrawLatex(0.45,0.775,text2);

  sprintf(name,"StatUnc_Plots/Pt_Plots/Data/%s.png",canv_pt[ij][jk]->GetName());
  canv_pt[ij][jk]->SaveAs(name);
 }
}

fileout->cd();
fileout->Write();
fileout->Close();

}
