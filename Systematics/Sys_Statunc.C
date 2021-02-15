#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TFile.h>
#include <fstream>
#include <TGraphErrors.h>
#include "TPaletteAxis.h"
#include "TStyle.h"


#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

using namespace std;

const int nalgo = 12;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
const char *jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char *jetradname[nalgo] = {"R=0.1/R=0.4","R=0.2/R=0.4","R=0.3/R=0.4","R=0.4/R=0.4","R=0.5/R=0.4","R=0.6/R=0.4","R=0.7/R=0.4","R=0.8/R=0.4","R=0.9/R=0.4","R=1.0/R=0.4","R=1.1/R=0.4","R=1.2/R=0.4"};
const char *jetradnamen[nalgo] = {"R=0.1","R=0.2","R=0.3","R=0.4","R=0.5","R=0.6","R=0.7","R=0.8","R=0.9","R=1.0","R=1.1","R=1.2"};

const int netarange = 1;//10;
//const char *ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"};
const char *ybinname[netarange] = {"|y|<0.5"};

const int ncomb = 10;

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int ref_rad = 3;

char name[100];

float leg_x1 = 0.25;
float leg_y1 = 0.6;
float leg_x2 = 0.45;
float leg_y2 = 0.85;

void Sys_Statunc()
{

//TFile *filein = new TFile("/home/suman/RooUnfold/Unfolded2016_DataStat10.root","read");
TFile *filein = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Stat/Legacy2016_07Aug_JECV18statmk_tot.root","read");
//TFile *filein = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Stat/Legacy2016_07Aug_JECV18stat_tot2.root","read");
//TFile *filein = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18statgm_tot.root","read");
//TFile *filein = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_P8_RM10_Combo.root");
//TFile *filein = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_P8_RM10_Combo.root","read");

TCanvas *c3[nalgo][netarange];
TCanvas *c2[nalgo][netarange];

TH1D *hist_pt[nalgo][netarange][ncomb];
TH1D *hist_rad[nalgo][netarange][ncomb];

TH1D *hist_pt_full[nalgo][netarange];
TH1D *hist_rad_full[nalgo][netarange];

double pt_points[nalgo][netarange][ncomb][noptbins];
double pt_mean[nalgo][netarange][noptbins];
double pt_rms[nalgo][netarange][noptbins];
double pt_stdev[nalgo][netarange][noptbins];

double rad_points[nalgo][netarange][ncomb][noptbins];
double rad_mean[nalgo][netarange][noptbins];
double rad_rms[nalgo][netarange][noptbins];
double rad_stdev[nalgo][netarange][noptbins];

TH1D *rm_unc[nalgo][netarange];
TH1D *rm_rad_unc[nalgo][netarange];

TGraphErrors *gr_pt[nalgo][netarange];
TGraphErrors *gr_rad[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

  sprintf(name,"RM_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
  rm_unc[ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"RM_Rad_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
  rm_rad_unc[ij][jk] = new TH1D(name,name,noptbins,ptbins);

 }
}

ofstream fp_pt;
fp_pt.open("Stat_Unc_DataXX_Pt_84_RefAK4.log");

ofstream fp_rad;
fp_rad.open("Stat_Unc_DataXX_Rad_84_RefAK4.log");

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<ncomb; kl++){
	sprintf(name,"JetpT_%s_EtaBin%i_Comb%i",JetRad[ij],jk+1,kl+1);
//	sprintf(name,"bayes_Bayes_%s_EtaBin%i_Comb%i",JetRad[ij],jk+1,kl+1);
	hist_pt[ij][jk][kl] = (TH1D*)filein->Get(name);
   }//kl
    sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
    hist_pt_full[ij][jk] = (TH1D*)filein->Get(name);
  }//jk
 }//ij


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<ncomb; kl++){
        hist_rad[ij][jk][kl] = (TH1D*)hist_pt[ij][jk][kl]->Clone();
		hist_rad[ij][jk][kl]->Divide(hist_pt[ref_rad][jk][kl]);
   }//kl
		hist_rad_full[ij][jk] = (TH1D*)hist_pt_full[ij][jk]->Clone();
		hist_rad_full[ij][jk]->Divide(hist_pt_full[ref_rad][jk]);
  }//jk
 }//ij


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
	 for(int lm=0; lm<int(ncomb); lm++){
	 
	  if(kl==lm) continue;	
		
      ptsumx[kl] += hist_pt[ij][jk][lm]->GetBinContent(bn+1);
      radsumx[kl] += hist_rad[ij][jk][lm]->GetBinContent(bn+1);
 
		}
		
		ptsumx[kl] *= 1./(ncomb-1);
		radsumx[kl] *= 1./(ncomb-1);
		
     }//kl
   
    for(int kl=0; kl<int(ncomb); kl++){
		sum += ptsumx[kl];
		rad_sum += radsumx[kl];
	}
   
    pt_mean[ij][jk][bn] = sum*1./(ncomb);
    
    rad_mean[ij][jk][bn] = rad_sum*1./(ncomb);
    
    for(int kl=0; kl<int(ncomb); kl++){
		sq_sum += pow((hist_pt[ij][jk][kl]->GetBinContent(bn+1) - pt_mean[ij][jk][bn]),2);
		rad_sq_sum += pow((hist_rad[ij][jk][kl]->GetBinContent(bn+1) - rad_mean[ij][jk][bn]),2);
	
	if(ij==7&&jk==0 && bn==5){
//		cout<<"sample "<<kl+1<<" diff "<<(hist_rad[ij][jk][kl]->GetBinContent(bn+1) - rad_mean[ij][jk][bn])<<" diffsquare "<<pow((hist_rad[ij][jk][kl]->GetBinContent(bn+1) - rad_mean[ij][jk][bn]),2)<<" rad_sq_sum "<<rad_sq_sum<<endl;
		}
	}
    
    
    pt_rms[ij][jk][bn] = sq_sum;
    
    if(ij==7&&jk==0){
    cout<<bn+1<<" rms "<<pt_rms[ij][jk][bn]<<endl;
	}
    
    pt_stdev[ij][jk][bn] =  sqrt(pt_rms[ij][jk][bn]* ((ncomb-1)*1./(ncomb)));
	if(isnan(pt_stdev[ij][jk][bn])) { pt_stdev[ij][jk][bn] = 1.e-6; }
	
	rad_rms[ij][jk][bn] = rad_sq_sum*1./(ncomb);
    rad_stdev[ij][jk][bn] = sqrt(rad_rms[ij][jk][bn]);
    if(isnan(rad_stdev[ij][jk][bn])) { rad_stdev[ij][jk][bn] = 1.e-6; }

//    rm_unc[ij][jk]->SetBinContent(bn+1,pt_stdev[ij][jk][bn]*1./max(1.e-9,pt_mean[ij][jk][bn]));
	rm_unc[ij][jk]->SetBinContent(bn+1,pt_stdev[ij][jk][bn]*1./max(1.e-9,hist_pt_full[ij][jk]->GetBinContent(bn+1)));
    if(rm_unc[ij][jk]->GetBinContent(bn+1) > (1. - 1.e-6)) {rm_unc[ij][jk]->SetBinContent(bn+1,(1. - 1.e-6)); }

//    rm_rad_unc[ij][jk]->SetBinContent(bn+1,rad_stdev[ij][jk][bn]*1./max(1.e-9,rad_mean[ij][jk][bn]));
    rm_rad_unc[ij][jk]->SetBinContent(bn+1,rad_stdev[ij][jk][bn]*1./max(1.e-9,hist_rad_full[ij][jk]->GetBinContent(bn+1)));
    if(rm_rad_unc[ij][jk]->GetBinContent(bn+1) > (1. - 1.e-6)) {rm_rad_unc[ij][jk]->SetBinContent(bn+1,(1. - 1.e-6)); }

	fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<max(0.,rm_unc[ij][jk]->GetBinContent(bn+1))<<'\t'<<max(0.,rm_unc[ij][jk]->GetBinContent(bn+1))<<endl;

    fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<max(0.,rm_rad_unc[ij][jk]->GetBinContent(bn+1))<<'\t'<<max(0.,rm_rad_unc[ij][jk]->GetBinContent(bn+1))<<endl;
    
    
//    cout<<"AK"<<ij+1<<" bin "<<bn+1<<" ptunc "<<pt_stdev[ij][jk][bn]<<" mean "<<pt_mean[ij][jk][bn]<<" rel "<<pt_stdev[ij][jk][bn]*1./pt_mean[ij][jk][bn]<<" radunc "<<rad_stdev[ij][jk][bn]<<" mean "<<rad_mean[ij][jk][bn]<<" relerr "<<rad_stdev[ij][jk][bn]*1./rad_mean[ij][jk][bn]<<endl;
    
     }
   }
 }
fp_pt.close();
fp_rad.close();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
  for(int bn=0; bn<noptbins; bn++){

   double sum = 0;
   double rad_sum = 0;

    for(int kl=0; kl<int(ncomb); kl++){

      sum += hist_pt[ij][jk][kl]->GetBinContent(bn+1);
      rad_sum += hist_rad[ij][jk][kl]->GetBinContent(bn+1);
     }//kl

    pt_mean[ij][jk][bn] = sum*1./(ncomb);
    rad_mean[ij][jk][bn] = rad_sum*1./(ncomb);
   }
 }
}

double corfactor_pt[nalgo][netarange][noptbins][noptbins];
double corfactor_rad[nalgo][netarange][noptbins][noptbins];

TFile *fileout = new TFile("Correlation_output.root","RECREATE");

TH2D *rad_correlation[nalgo][netarange];
TH2D *pt_correlation[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   sprintf(name,"TwoD_pt_correlation_%s_EtaBin%i",JetRad[ij],jk+1);
   pt_correlation[ij][jk] = new TH2D(name,name,noptbins,ptbins,noptbins,ptbins);
   pt_correlation[ij][jk]->Sumw2();

   sprintf(name,"TwoD_rad_correlation_%s_EtaBin%i",JetRad[ij],jk+1);
   rad_correlation[ij][jk] = new TH2D(name,name,noptbins,ptbins,noptbins,ptbins);
   rad_correlation[ij][jk]->Sumw2();
  }
}

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   for(int kl=0; kl<noptbins; kl++){
     for(int lm=0; lm<noptbins; lm++){
		double xx=0;
		for(int sm=0; sm<ncomb; sm++) {
          xx += ((hist_pt[ij][jk][sm]->GetBinContent(kl+1) - pt_mean[ij][jk][kl])* (hist_pt[ij][jk][sm]->GetBinContent(lm+1) - pt_mean[ij][jk][lm]));
		}
		xx *= 1./ncomb;
		corfactor_pt[ij][jk][kl][lm] = xx*sqrt(ncomb-1);
		}
    }
       
if(ij==7&&jk==0){
 for(int bn=0; bn<noptbins; bn++){
//	cout<<(rm_unc[ij][jk]->GetBinContent(bn+1))<<"\t"<<sqrt(corfactor_pt[ij][jk][bn][bn])*1./(pt_mean[ij][jk][bn])<<endl;
/*
	if(!isnan(sqrt(corfactor_pt[ij][jk][bn][bn])*1./(pt_mean[ij][jk][bn]))){
		rm_unc[ij][jk]->SetBinContent(bn+1,sqrt(corfactor_pt[ij][jk][bn][bn])*1./(pt_mean[ij][jk][bn]));
	}else{
		rm_unc[ij][jk]->SetBinContent(bn+1,1.e-8);
	 }
*/
  }
}

  for(int kl=0; kl<noptbins; kl++){
     for(int lm=0; lm<noptbins; lm++){
	  double yy=0;
	  yy = corfactor_pt[ij][jk][kl][lm]*1./sqrt(corfactor_pt[ij][jk][kl][kl]*corfactor_pt[ij][jk][lm][lm]);
	  if(isnan(yy)) { yy = 0; }	  
	  pt_correlation[ij][jk]->SetBinContent(kl+1,lm+1,yy);
		}
    }	


  }
}

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   for(int kl=0; kl<noptbins; kl++){
     for(int lm=0; lm<noptbins; lm++){
		double xx=0;
		for(int sm=0; sm<ncomb; sm++) {
          xx += ((hist_rad[ij][jk][sm]->GetBinContent(kl+1) - rad_mean[ij][jk][kl])* (hist_rad[ij][jk][sm]->GetBinContent(lm+1) - rad_mean[ij][jk][lm]));
		}
		xx *= 1./ncomb;
		corfactor_rad[ij][jk][kl][lm] = xx;
		}
    }
       

  for(int kl=0; kl<noptbins; kl++){
     for(int lm=0; lm<noptbins; lm++){
	  double yy=0;
	  yy = corfactor_rad[ij][jk][kl][lm]*1./sqrt(corfactor_rad[ij][jk][kl][kl]*corfactor_rad[ij][jk][lm][lm]);
	  if(ij==3) {
		  if(kl==lm){ yy = 1.0; }
		  else { yy = 0; }
		  }
	  if(isnan(yy)) { yy = 0; }	  
	  rad_correlation[ij][jk]->SetBinContent(kl+1,lm+1,yy);
		}
    }	


  }
}

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
if(ij==7&&jk==0){
 for(int bn=0; bn<noptbins; bn++){
//	cout<<"rad "<<(rm_rad_unc[ij][jk]->GetBinContent(bn+1))<<"\t"<<sqrt(corfactor_rad[ij][jk][bn][bn])*1./(rad_mean[ij][jk][bn])<<endl;
     }
   }
 }
}
TCanvas *canv_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

  sprintf(name,"Cor_Mat_Pt_%s_EtaBin%i",JetRad[ij],jk+1);
  canv_pt[ij][jk] = new TCanvas(name,name,50,50,800,800);
  
  canv_pt[ij][jk]->SetFillColor(0);
  canv_pt[ij][jk]->SetBorderMode(0);
  canv_pt[ij][jk]->SetFrameFillStyle(0);
  canv_pt[ij][jk]->SetFrameBorderMode(0);
  canv_pt[ij][jk]->SetLeftMargin( 0.1*600/800 + 0.05 );
  canv_pt[ij][jk]->SetRightMargin( 0.1*600/600 + 0.025);
  canv_pt[ij][jk]->SetTopMargin( 0.08*800/600 );
  canv_pt[ij][jk]->SetBottomMargin( 0.1*800/600 );

  sprintf(name,"AK%i Jet p_{T} (GeV)",ij+1);
  pt_correlation[ij][jk]->GetXaxis()->SetTitle(name);
  pt_correlation[ij][jk]->GetXaxis()->SetTitleSize(0.05);
  pt_correlation[ij][jk]->GetXaxis()->SetLabelSize(0.05);
  pt_correlation[ij][jk]->GetXaxis()->CenterTitle();
  pt_correlation[ij][jk]->GetXaxis()->SetRangeUser(84,1501);
  pt_correlation[ij][jk]->GetXaxis()->SetNdivisions(406);
  
  pt_correlation[ij][jk]->GetYaxis()->SetTitle("AK4 Jet p_{T} (GeV)");
  pt_correlation[ij][jk]->GetYaxis()->SetTitleSize(0.05);
  pt_correlation[ij][jk]->GetYaxis()->SetLabelSize(0.05);
  pt_correlation[ij][jk]->GetYaxis()->CenterTitle();
  pt_correlation[ij][jk]->GetYaxis()->SetRangeUser(84,1501);
  pt_correlation[ij][jk]->GetYaxis()->SetNdivisions(406);
	
  pt_correlation[ij][jk]->GetZaxis()->SetTitle("Correlation Coefficient");
  pt_correlation[ij][jk]->GetZaxis()->SetTitleSize(0.035);
  pt_correlation[ij][jk]->GetZaxis()->SetLabelSize(0.035);
  pt_correlation[ij][jk]->GetZaxis()->CenterTitle();
  pt_correlation[ij][jk]->GetZaxis()->SetNdivisions(406);	
  
  pt_correlation[ij][jk]->SetStats(0);
  pt_correlation[ij][jk]->SetTitle(0);

  assert(pt_correlation[ij][jk]);
  pt_correlation[ij][jk]->GetYaxis()->SetTitleOffset(1.1);
  pt_correlation[ij][jk]->GetXaxis()->SetTitleOffset(1.1);
  pt_correlation[ij][jk]->Draw("AXIS");
  
  canv_pt[ij][jk]->cd();
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  pt_correlation[ij][jk]->Draw("colz");
  
  canv_pt[ij][jk]->Update();
  TPaletteAxis *palette = (TPaletteAxis*)pt_correlation[ij][jk]->GetListOfFunctions()->FindObject("palette");
  palette->SetX1NDC(0.875);
  palette->SetX2NDC(0.915);
  palette->SetY1NDC(0.13);
  palette->SetY2NDC(0.9);
  canv_pt[ij][jk]->Modified();
  canv_pt[ij][jk]->Update();
  
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kRed+4);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.045);

  TString text;
  text+= jetradnamen[ij];
  TString text1;
  text1+=  ybinname[jk];
  TString text2;
  text2+= "Anti-k_{T} CHS";
  
  latex.DrawLatex(0.45,0.7,text);
  latex.DrawLatex(0.55,0.925,text1);
  latex.DrawLatex(0.45,0.775,text2);

  sprintf(name,"StatUnc_Plots/Pt_Plots/MC/%s.png",canv_pt[ij][jk]->GetName());
  canv_pt[ij][jk]->SaveAs(name);
 }
}



TCanvas *canv_rad[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

  sprintf(name,"Cor_Mat_Radius_%s_EtaBin%i",JetRad[ij],jk+1);
  canv_rad[ij][jk] = new TCanvas(name,name,50,50,800,800);
  
  canv_rad[ij][jk]->SetFillColor(0);
  canv_rad[ij][jk]->SetBorderMode(0);
  canv_rad[ij][jk]->SetFrameFillStyle(0);
  canv_rad[ij][jk]->SetFrameBorderMode(0);
  canv_rad[ij][jk]->SetLeftMargin( 0.1*600/800 + 0.05 );
  canv_rad[ij][jk]->SetRightMargin( 0.1*600/600 + 0.025);
  canv_rad[ij][jk]->SetTopMargin( 0.08*800/600 );
  canv_rad[ij][jk]->SetBottomMargin( 0.1*800/600 );

  
  rad_correlation[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  rad_correlation[ij][jk]->GetXaxis()->SetTitleSize(0.05);
  rad_correlation[ij][jk]->GetXaxis()->SetLabelSize(0.05);
  rad_correlation[ij][jk]->GetXaxis()->CenterTitle();
  rad_correlation[ij][jk]->GetXaxis()->SetRangeUser(84,1501);
  rad_correlation[ij][jk]->GetXaxis()->SetNdivisions(406);
  
  rad_correlation[ij][jk]->GetYaxis()->SetTitle("Jet p_{T} (GeV)");
  rad_correlation[ij][jk]->GetYaxis()->SetTitleSize(0.05);
  rad_correlation[ij][jk]->GetYaxis()->SetLabelSize(0.05);
  rad_correlation[ij][jk]->GetYaxis()->CenterTitle();
  rad_correlation[ij][jk]->GetYaxis()->SetRangeUser(84,1501);
  rad_correlation[ij][jk]->GetYaxis()->SetNdivisions(406);
	
  rad_correlation[ij][jk]->GetZaxis()->SetTitle("Correlation Coefficient");
  rad_correlation[ij][jk]->GetZaxis()->SetTitleSize(0.035);
  rad_correlation[ij][jk]->GetZaxis()->SetLabelSize(0.035);
  rad_correlation[ij][jk]->GetZaxis()->CenterTitle();
  rad_correlation[ij][jk]->GetZaxis()->SetNdivisions(406);	
  
  rad_correlation[ij][jk]->SetStats(0);
  rad_correlation[ij][jk]->SetTitle(0);

  assert(rad_correlation[ij][jk]);
  rad_correlation[ij][jk]->GetYaxis()->SetTitleOffset(1.1);
  rad_correlation[ij][jk]->GetXaxis()->SetTitleOffset(1.1);
  rad_correlation[ij][jk]->Draw("AXIS");
  
  canv_rad[ij][jk]->cd();
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  rad_correlation[ij][jk]->Draw("colz");
  
  canv_rad[ij][jk]->Update();
  TPaletteAxis *palette = (TPaletteAxis*)rad_correlation[ij][jk]->GetListOfFunctions()->FindObject("palette");
  palette->SetX1NDC(0.875);
  palette->SetX2NDC(0.915);
  palette->SetY1NDC(0.13);
  palette->SetY2NDC(0.9);
  canv_rad[ij][jk]->Modified();
  canv_rad[ij][jk]->Update();
  
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kRed+4);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.045);

  TString text;
  text+= jetradname[ij];
  TString text1;
  text1+=  ybinname[jk];
  TString text2;
  text2+= "Anti-k_{T} CHS";
  
  latex.DrawLatex(0.45,0.7,text);
  latex.DrawLatex(0.55,0.925,text1);
  latex.DrawLatex(0.45,0.775,text2);

  sprintf(name,"StatUnc_Plots/Ratio_Plots/MC/%s.png",canv_rad[ij][jk]->GetName());
  canv_rad[ij][jk]->SaveAs(name);
 }
}


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   rm_unc[ij][jk]->Scale(100);
   rm_rad_unc[ij][jk]->Scale(100);

   sprintf(name,"Canvas_Stat_Pt_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
   c2[ij][jk] = tdrCanvas(name,rm_unc[ij][jk],7,0);

   c2[ij][jk]->cd();

   gPad->SetLogx(1);

   rm_unc[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
   rm_unc[ij][jk]->GetXaxis()->SetTitleSize(0.06);
   rm_unc[ij][jk]->GetXaxis()->CenterTitle();
   rm_unc[ij][jk]->GetXaxis()->SetLabelSize(0.05);
   rm_unc[ij][jk]->GetXaxis()->SetNdivisions(510);

   rm_unc[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection(in %)");
   rm_unc[ij][jk]->GetYaxis()->SetTitleSize(0.06);
   rm_unc[ij][jk]->GetYaxis()->CenterTitle();
   rm_unc[ij][jk]->GetYaxis()->SetLabelSize(0.05);
   rm_unc[ij][jk]->GetYaxis()->SetTitleOffset(1.05);

   rm_unc[ij][jk]->SetMaximum(5.1);
   rm_unc[ij][jk]->SetMinimum(-0.01);

   rm_unc[ij][jk]->Smooth(1);

   double yy[noptbins] = {0};
   double yyerr[noptbins] = {0};

   for(int bn=0; bn<(rm_unc[ij][jk]->GetNbinsX()); bn++){
        yyerr[bn] = rm_unc[ij][jk]->GetBinContent(bn+1);
   }

   sprintf(name,"Pt_Error_%s_EtaBin%i",JetRad[ij],jk+1);
   gr_pt[ij][jk] = new TGraphErrors(noptbins,ptbins,yy,NULL,yyerr);

   gr_pt[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
   gr_pt[ij][jk]->GetXaxis()->SetTitleSize(0.06);
   gr_pt[ij][jk]->GetXaxis()->CenterTitle();
   gr_pt[ij][jk]->GetXaxis()->SetLabelSize(0.05);
   gr_pt[ij][jk]->GetXaxis()->SetNdivisions(510);

   gr_pt[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection(in %)");
   gr_pt[ij][jk]->GetYaxis()->SetTitleSize(0.06);
   gr_pt[ij][jk]->GetYaxis()->CenterTitle();
   gr_pt[ij][jk]->GetYaxis()->SetLabelSize(0.05);
   gr_pt[ij][jk]->GetYaxis()->SetTitleOffset(1.05);

   gr_pt[ij][jk]->SetMaximum(5.1);
   gr_pt[ij][jk]->SetMinimum(-5.1);

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

   gr_pt[ij][jk]->GetXaxis()->SetRangeUser(84,3000.);
//   rm_unc[ij][jk]->Smooth(1);
//   tdrDraw(rm_unc[ij][jk],kLine,5,kSolid,kYellow+2,4005,kYellow+2);
   gr_pt[ij][jk]->SetMarkerStyle(kFullCircle);
   gr_pt[ij][jk]->SetMarkerColor(kBlack);
   gr_pt[ij][jk]->SetLineColor(kBlue);
   gr_pt[ij][jk]->SetLineWidth(-2002);
   gr_pt[ij][jk]->SetFillStyle(3004);
   gr_pt[ij][jk]->SetFillColor(kBlue);

   gr_pt[ij][jk]->Draw("AP");
   gr_pt[ij][jk]->Draw("SAME:E3");
   
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.225,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.15,text1);

   sprintf(name,"StatUnc_Plots/Pt_Plots/%s.png",c2[ij][jk]->GetName());
   c2[ij][jk]->SaveAs(name);

   sprintf(name,"Canvas_Stat_Rad_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
   c3[ij][jk] = tdrCanvas(name,rm_rad_unc[ij][jk],7,0);

   c3[ij][jk]->cd();

   gPad->SetLogx(1);
   
   rm_rad_unc[ij][jk]->Smooth(1);

   double yyerr1[noptbins] = {0};
   
   double coly[noptbins] = {0};
   
   for(int bn=0; bn<(rm_rad_unc[ij][jk]->GetNbinsX()); bn++){
	   for(int am=0; am<(rm_rad_unc[ij][jk]->GetNbinsX()); am++){
	  if(am!=bn) continue;
	  if(isnan(pt_correlation[ij][jk]->GetBinContent(am+1,bn+1))) continue;
//	  cout<<"COR "<<pt_correlation[ij][jk]->GetBinContent(am+1,bn+1)<<endl;
	   coly[bn] += pt_correlation[ij][jk]->GetBinContent(am+1,bn+1)*rm_unc[ij][jk]->GetBinContent(am+1);//corfactor_pt[ij][jk][kl][lm]
		
	}
   }
   
   for(int bn=0; bn<(rm_rad_unc[ij][jk]->GetNbinsX()); bn++){
//	yyerr1[bn] =   pow(rm_unc[ij][jk]->GetBinContent(bn+1),2)+pow(rm_unc[ref_rad][jk]->GetBinContent(bn+1),2)-2.*coly[bn]*rm_unc[ref_rad][jk]->GetBinContent(bn+1);
    if(isnan(corfactor_pt[ij][jk][bn][bn])||isnan(pt_mean[ij][jk][bn])||isnan(pt_mean[ref_rad][jk][bn])||isnan(corfactor_pt[ij][jk][bn][bn]*1./(pt_mean[ij][jk][bn]*pt_mean[ref_rad][jk][bn]))) { yyerr1[bn] = 1.e-9; continue; }
    yyerr1[bn] =   pow(rm_unc[ij][jk]->GetBinContent(bn+1),2)+pow(rm_unc[ref_rad][jk]->GetBinContent(bn+1),2)-2.*corfactor_pt[ij][jk][bn][bn]*1./(pt_mean[ij][jk][bn]*pt_mean[ref_rad][jk][bn]);
    if(ij==7&&jk==0){
 //   cout<<bn+1<<" cor "<<corfactor_pt[ij][jk][bn][bn]*1./(pt_mean[ij][jk][bn]*pt_mean[ref_rad][jk][bn])<<endl;
}
    yyerr1[bn] = sqrt(fabs(yyerr1[bn]));
   }
   
   for(int bn=0; bn<(rm_rad_unc[ij][jk]->GetNbinsX()); bn++){
        yyerr1[bn] = rm_rad_unc[ij][jk]->GetBinContent(bn+1);
   }

   sprintf(name,"Rad_Error_%s_EtaBin%i",JetRad[ij],jk+1);
   gr_rad[ij][jk] = new TGraphErrors(noptbins,ptbins,yy,NULL,yyerr1);

   rm_rad_unc[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
   rm_rad_unc[ij][jk]->GetXaxis()->SetTitleSize(0.05);
   rm_rad_unc[ij][jk]->GetXaxis()->CenterTitle();
   rm_rad_unc[ij][jk]->GetXaxis()->SetLabelSize(0.05);

   rm_rad_unc[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection Ratio (in %)");
   rm_rad_unc[ij][jk]->GetYaxis()->SetTitleSize(0.05);
   rm_rad_unc[ij][jk]->GetYaxis()->CenterTitle();
   rm_rad_unc[ij][jk]->GetYaxis()->SetLabelSize(0.05);
   rm_rad_unc[ij][jk]->GetYaxis()->SetTitleOffset(1.05);

   rm_rad_unc[ij][jk]->SetMaximum(10.1);
   rm_rad_unc[ij][jk]->SetMinimum(-10.1);

   gr_rad[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
   gr_rad[ij][jk]->GetXaxis()->SetTitleSize(0.05);
   gr_rad[ij][jk]->GetXaxis()->CenterTitle();
   gr_rad[ij][jk]->GetXaxis()->SetLabelSize(0.05);

   gr_rad[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection Ratio (in %)");
   gr_rad[ij][jk]->GetYaxis()->SetTitleSize(0.05);
   gr_rad[ij][jk]->GetYaxis()->CenterTitle();
   gr_rad[ij][jk]->GetYaxis()->SetLabelSize(0.05);
   gr_rad[ij][jk]->GetYaxis()->SetTitleOffset(1.05);

   gr_rad[ij][jk]->SetMaximum(10.1);
   gr_rad[ij][jk]->SetMinimum(-10.1);

/*
   TLatex latex;
   latex.SetNDC();
   latex.SetTextAngle(0);
   latex.SetTextColor(kBlack);

   latex.SetTextFont(42);
   latex.SetTextAlign(31);
   latex.SetTextSize(0.065);

   TString text11;
   text11+= jetname[ij];
   TString text12;
   text12+= ybinname[jk];
 */
   gr_rad[ij][jk]->GetXaxis()->SetRangeUser(84,3000.);
//   rm_rad_unc[ij][jk]->Smooth(1);
//   tdrDraw(rm_rad_unc[ij][jk],kLine,5,kSolid,kYellow+2,4005,kYellow+2);
   gr_rad[ij][jk]->SetMarkerStyle(kFullSquare);
   gr_rad[ij][jk]->SetMarkerColor(kBlack);
   gr_rad[ij][jk]->SetLineColor(kRed);
   gr_rad[ij][jk]->SetFillStyle(3005);
   gr_rad[ij][jk]->SetLineWidth(-2002);
   gr_rad[ij][jk]->SetFillColor(kRed);

   gr_rad[ij][jk]->Draw("AP");
   gr_rad[ij][jk]->Draw("SAME:E3");

   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.225,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.15,text1);

   sprintf(name,"StatUnc_Plots/Ratio_Plots/%s.png",c3[ij][jk]->GetName());
   c3[ij][jk]->SaveAs(name);
 }
}


fileout->cd();
fileout->Write();
fileout->Close();

}

int main()
{
Sys_Statunc();
}
