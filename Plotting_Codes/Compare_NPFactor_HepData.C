#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>
#include <TGraphAsymmErrors.h>

double MikkoFunc1(double *x, double *par){
return (par[3]+par[0]*pow(x[0],par[1])+par[2]*log(x[0])/x[0]);
}

double Inv_Func(double *x, double *par){
return (par[0]+par[1]*1./x[0]);
}

void Compare_NPFactor_HepData()
{
const int nfiles = 3;
/*
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/NP_Correction_Factor_Pythia.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/NP_Correction_Factor_Herwig_EE5C_ugur.root",
	 "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/NP_Correction_Factor_Herwig_CUETHppS1.root"};

*/
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/NP_Correction_Factor_Pythia_CT14nlo_wAK4.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/NP_Correction_Factor_Herwig_EE5C_ugur_wAK4.root",
	 "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/NP_Correction_Factor_Herwig_CUETHppS1_wAK4.root"};

const int ref = 3;

const char *model_name[nfiles] = {"PH+P8(CUETP8M1)","PH+Herwig(EE5C)","PH+Herwig(CUETHppS1)"};
const int col[nfiles] = {2,9,4};
const int sty[nfiles] = {kFullCircle,kFullCircle,kOpenSquare};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

double maxRange[netarange+1] = {1000,1000,1000,500,500,500,500,750,750,750};

//const char* jetname[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
const char* jetname[nalgo] = {"R = 0.1","R = 0.2","R = 0.3","R = 0.4","R = 0.5","R = 0.6","R = 0.7","R = 0.8","R = 0.9","R = 1.0","R = 1.1","R = 1.2"};
const char* ybinname[netarange] = {"|y| < 0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int noptbins = 62;
double ptbins[noptbins+1] = { 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int noptbins_1 = 33;
double ptbins_1[noptbins_1+1] = {84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588};


char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_diff[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_diff[nfiles-1][nalgo][netarange];

double rad_err_up[nalgo][netarange][noptbins];
double rad_err_dn[nalgo][netarange][noptbins];

TGraphAsymmErrors *gr_rad[nalgo][netarange];

TGraph *gr_rad_unc[nalgo][netarange];

TH1F *h_rad_cor[nalgo][netarange];
TH1F *h_rad_cor_full[nalgo][netarange];

TF1 *fit_rad[nalgo][netarange];
TF1 *fit_unc[nalgo][netarange];

const int nopbins = 10;
TH1F *h_np_unc[netarange][nopbins];

double radcor_mean[nalgo][netarange][noptbins];
double radcor_diff[nalgo][netarange][noptbins];

double radcor_full_mean[nalgo][netarange][noptbins];


float leg_x1 = 0.25;
float leg_y1 = 0.35;
float leg_x2 = 0.45;
float leg_y2 = 0.6;


for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   sprintf(name,"NP_Correction_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
   if(ij==3&&jk==1) { cout<<fg+1<<" mean "<<hist_pt[fg][ij][jk]->GetMean()<<endl;}

   sprintf(name,"NP_Correction_radius_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_radius[fg][ij][jk] = (TH1D*)filein->Get(name);
   sprintf(name,"NP_Correction_xsection_ratio_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_radius[fg][ij][jk]->SetName(name);

   hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)") ;
   hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();
   hist_pt[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_pt[fg][ij][jk]->GetXaxis()->SetTitleOffset(0.8);
   hist_pt[fg][ij][jk]->GetXaxis()->SetNoExponent();
   hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(84,1500);

   hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("NP Correction for Xsection");
   hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();
   hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.045);
   hist_pt[fg][ij][jk]->GetYaxis()->SetLabelSize(0.04);
   hist_pt[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.05);

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.055);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.055);
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleOffset(0.8);
   hist_radius[fg][ij][jk]->GetXaxis()->SetNoExponent();
   hist_radius[fg][ij][jk]->GetXaxis()->SetRangeUser(84,1500);

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("NP correction for cross section ratio");
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.055);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.055);
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.075);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelOffset(0.0125);
//   hist_radius[fg][ij][jk]->GetYaxis()->SetNdivisions(406);

    }
  }
 }

TH1D *hist_pt_p8[nalgo][netarange];

TFile *_filept = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/NP_Correction_Factor_Pythia.root","read");

 for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){
		  sprintf(name,"NP_Correction_radius_%s_EtaBin%i",JetRad[ij],jk+1);
		  hist_pt_p8[ij][jk] = (TH1D*)_filept->Get(name);
	  }
 }

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int fg=0; fg<(nfiles-1); fg++){
	
	hist_pt_diff[fg][ij][jk] = (TH1D*)hist_pt[fg+1][ij][jk]->Clone();
	hist_pt_diff[fg][ij][jk]->Add(hist_pt[0][ij][jk],-1) ;
	
    hist_radius_diff[fg][ij][jk] = (TH1D*)hist_radius[fg+1][ij][jk]->Clone();
	hist_radius_diff[fg][ij][jk]->Add(hist_radius[0][ij][jk],-1) ;

	hist_pt_diff[fg][ij][jk]->GetYaxis()->SetTitle("MC - (PH+P8)");
	hist_pt_diff[fg][ij][jk]->GetYaxis()->SetTitleSize(0.065);
	hist_pt_diff[fg][ij][jk]->GetXaxis()->SetLabelSize(0.5);
	
    hist_radius_diff[fg][ij][jk]->GetYaxis()->SetTitle("MC - (PH+P8)");
	hist_radius_diff[fg][ij][jk]->GetYaxis()->SetTitleSize(0.065);

   }
  }
 }

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
	 
	 gr_rad[ij][jk] = new TGraphAsymmErrors();
	 gr_rad_unc[ij][jk] = new TGraph();
	 
	 sprintf(name,"NP_Cor_AK%i_Eta%i",ij+1,jk+1);
	 h_rad_cor[ij][jk] = new TH1F(name,name,noptbins_1,ptbins_1);
	 
	 sprintf(name,"NP_Cor_Full_AK%i_Eta%i",ij+1,jk+1);
	 h_rad_cor_full[ij][jk] = new TH1F(name,name,noptbins,ptbins);
	 
	 for(int pt=0; pt<noptbins_1; pt++){	// for hepdata
		
		int pt1 = pt+1;
		 
		radcor_diff[ij][jk][pt] = max(abs(hist_radius_diff[0][ij][jk]->GetBinContent(pt1+1)),abs(hist_radius_diff[1][ij][jk]->GetBinContent(pt1+1)));
	
		float radsum = 0;
		for(int fg=0; fg<(nfiles-1); fg++){
			radsum += hist_radius[fg][ij][jk]->GetBinContent(pt1+1);
		}
		
		radcor_mean[ij][jk][pt] = radsum*1./(nfiles-1);
	
	    if(isnan(radcor_diff[ij][jk][pt])) { radcor_diff[ij][jk][pt] = 1.e-6; }	
	    /*
	    if((ij<3) && pt>0 && (radcor_mean[ij][jk][pt] < 0.8* radcor_mean[ij][jk][pt-1])){
			radcor_mean[ij][jk][pt] = 1.005 * radcor_mean[ij][jk][pt-1];
			}
		if((ij<3) && pt>0 && (radcor_mean[ij][jk][pt] > 1.2* radcor_mean[ij][jk][pt-1])){
			radcor_mean[ij][jk][pt] = 1.025 * radcor_mean[ij][jk][pt-1];
			}		
		*/
		if((ij>=9) && (jk==3||jk==2) && pt>0 && (radcor_mean[ij][jk][pt] > 1.075* radcor_mean[ij][jk][pt-1])){
			radcor_mean[ij][jk][pt] = 0.98 * radcor_mean[ij][jk][pt-1];
			}
		
		float err;
		err = radcor_diff[ij][jk][pt];
		
		if(ij==11 && (jk==0)) { err *= 0; }
			
		gr_rad[ij][jk]->SetPoint(pt,hist_pt[0][ij][jk]->GetBinCenter(pt1+1),radcor_mean[ij][jk][pt]);
		gr_rad[ij][jk]->SetPointEYhigh(pt,0.5*err);
		gr_rad[ij][jk]->SetPointEYlow(pt,0.5*err);
		
		gr_rad_unc[ij][jk]->SetPoint(pt,hist_pt[0][ij][jk]->GetBinCenter(pt1+1),0.5*radcor_diff[ij][jk][pt]);
		
		h_rad_cor[ij][jk]->SetBinContent(pt+1,radcor_mean[ij][jk][pt]);
	
	}
	
	for(int pt=0; pt<noptbins; pt++){	// for hepdata
		
		float radsum = 0;
		for(int fg=0; fg<(nfiles-1); fg++){
			radsum += hist_radius[fg][ij][jk]->GetBinContent(pt+1);
		}
		
		radcor_full_mean[ij][jk][pt] = radsum*1./(nfiles-1);
		
		if((ij>=9) && pt>0 && (radcor_full_mean[ij][jk][pt] > 1.075* radcor_full_mean[ij][jk][pt-1])){
			radcor_full_mean[ij][jk][pt] = 0.98 * radcor_full_mean[ij][jk][pt-1];
			}
		/*
		if((ij<3) && pt>0 && (radcor_full_mean[ij][jk][pt] < 0.8* radcor_full_mean[ij][jk][pt-1])){
			radcor_full_mean[ij][jk][pt] = 1.05 * radcor_full_mean[ij][jk][pt-1];
			}	
		*/
		
		h_rad_cor_full[ij][jk]->SetBinContent(pt+1,radcor_full_mean[ij][jk][pt]);
	}
		
		sprintf(name,"Fit_Rad_%s",hist_pt[0][ij][jk]->GetName());
//		fit_rad[ij][jk] = new TF1(name,MikkoFunc1,84,3000,4);
		fit_rad[ij][jk] = new TF1(name,MikkoFunc1,84,1588,4); // for hepdata
		fit_rad[ij][jk]->SetParameters(-1,-1,1,1);
		fit_rad[ij][jk]->FixParameter(3,1);
		
		sprintf(name,"Fit_Rad_Unc_%s",hist_pt[0][ij][jk]->GetName());
		fit_unc[ij][jk] = new TF1(name,Inv_Func,84,3000,2);
		fit_unc[ij][jk]->SetParameters(1,0.2);
 }
}


float np_nlo_rad[nfiles-1][nalgo][netarange][nopbins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
   for(int fg=0; fg<(nfiles-1); fg++){
	   
	for(int bn=0; bn<nopbins; bn++){
			
	switch(bn){
			
	case 0:
	np_nlo_rad[fg][ij][jk][bn] = hist_radius[fg][ij][jk]->GetBinContent(2);
	break;
			
	case 1:
	np_nlo_rad[fg][ij][jk][bn] = (hist_radius[fg][ij][jk]->GetBinContent(3)+hist_radius[fg][ij][jk]->GetBinContent(4))*1./2;
	break;
		
	case 2:
	np_nlo_rad[fg][ij][jk][bn] = (hist_radius[fg][ij][jk]->GetBinContent(5)+hist_radius[fg][ij][jk]->GetBinContent(6)+hist_radius[fg][ij][jk]->GetBinContent(7))*1./3;
	break;
			
	case 3:
	np_nlo_rad[fg][ij][jk][bn] = (hist_radius[fg][ij][jk]->GetBinContent(8)+hist_radius[fg][ij][jk]->GetBinContent(9)+hist_radius[fg][ij][jk]->GetBinContent(10))*1./3;
	break;
			
	case 4:
	np_nlo_rad[fg][ij][jk][bn] = (hist_radius[fg][ij][jk]->GetBinContent(11)+hist_radius[fg][ij][jk]->GetBinContent(12))*1./2;
	break;
			
	case 5:
	np_nlo_rad[fg][ij][jk][bn] = (hist_radius[fg][ij][jk]->GetBinContent(13)+hist_radius[fg][ij][jk]->GetBinContent(14))*1./2;
	break;
			
	case 6:
	np_nlo_rad[fg][ij][jk][bn] = (hist_radius[fg][ij][jk]->GetBinContent(15)+hist_radius[fg][ij][jk]->GetBinContent(16))*1./2;
	break;
			
	case 7:
	np_nlo_rad[fg][ij][jk][bn] = (hist_radius[fg][ij][jk]->GetBinContent(17)+hist_radius[fg][ij][jk]->GetBinContent(18))*1./2;
	break;
			
	case 8:
	np_nlo_rad[fg][ij][jk][bn] = (hist_radius[fg][ij][jk]->GetBinContent(19)+hist_radius[fg][ij][jk]->GetBinContent(20))*1./2;
	break;
			
	case 9:
	double tot_cor = 0;
	for(int bn=0; bn<14; bn++){
         tot_cor += hist_radius[fg][ij][jk]->GetBinContent(20+1+bn);                 
    }
	
	np_nlo_rad[fg][ij][jk][bn] = tot_cor*1./14;
	break;
		}
	}
   
   }
   
  }
}
   

// Ratio Plots //

TCanvas *c3[nalgo][netarange];
TLegend *leg_rad[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   sprintf(name,"NP_Ratio_Compare_Canv_%s_EtaBin%i_HEPDATA",JetRad[ij],jk+1);
//   c2[ij][jk] = tdrDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],2,0);
   c3[ij][jk] = tdrCanvas(name,hist_radius[0][ij][jk],2,0);
   
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);
 
   leg_rad[ij][jk] = tdrLeg(0.2,0.675,0.45,0.875);
   leg_rad[ij][jk]->SetTextSize(.0525);
   leg_rad[ij][jk]->SetTextFont(42);

   c3[ij][jk]->cd(1);
   gPad->SetLogx(1);

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
   TString text2;
   text2+= "Anti-k_{T}";
/*
   latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);
*/
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.5,leg_y1+0.475,text2);
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.5,leg_y1+0.4,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.5,leg_y1+0.325,text1);

   gr_rad[ij][jk]->SetFillColorAlpha(kYellow+2,0.75);
   gr_rad[ij][jk]->SetLineWidth(-2002);
   gr_rad[ij][jk]->SetLineColor(kMagenta+3);
   gr_rad[ij][jk]->SetFillStyle(1005);
   gr_rad[ij][jk]->Draw("E3");
   

   for(int fg=0; fg<nfiles; fg++){

      hist_radius[fg][ij][jk]->SetMaximum(1.51);
      hist_radius[fg][ij][jk]->SetMinimum(0.79);
      hist_radius[fg][ij][jk]->SetStats(0);
      hist_radius[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.25);
      
      sprintf(name,"%s_Model%i",hist_radius[fg][ij][jk]->GetName(),fg+1);
      hist_radius[fg][ij][jk]->SetName(name);
      sprintf(name,"NP correction : %s/%s %s %s",JetRad[ij],JetRad[3],ybinname[jk],model_name[fg]);
	  hist_radius[fg][ij][jk]->SetTitle(name);
	
	  if(ij==(nalgo-1) && fg==2){ continue; }
	
      tdrDraw(hist_radius[fg][ij][jk],"][ E X0",sty[fg],col[fg],kSolid,col[fg] ,1001,2);
      leg_rad[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"pe");
    }
  
  if(jk<5){
	   gr_rad[ij][jk]->Fit(fit_rad[ij][jk],"MR","",84,1588); // for hepdata
	   fit_rad[ij][jk]->SetLineColor(kMagenta+3);
	   fit_rad[ij][jk]->Draw("C0,sames");
	   leg_rad[ij][jk]->AddEntry(gr_rad[ij][jk],"Final correction","lf");
	      }

    sprintf(name,"NP_Total_Plots/Ratio_Plots/%s.pdf",c3[ij][jk]->GetName());
	c3[ij][jk]->SaveAs(name);

   }//jk
 }//ij
 
 
for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<nopbins; kl++){
   
    sprintf(name,"NP_Unc_Inc_Eta%i_PtBin%i",jk+1,kl+1);
    h_np_unc[jk][kl] = new TH1F(name,name,nalgo,0.05,1.25);
   
    for(int ij=0; ij<nalgo; ij++){
	   float xx = abs(np_nlo_rad[1][ij][jk][kl] - np_nlo_rad[0][ij][jk][kl]);
	   float yy = 0.5*abs(np_nlo_rad[1][ij][jk][kl] + np_nlo_rad[0][ij][jk][kl]);
	   h_np_unc[jk][kl]->SetBinContent(ij+1,yy);
	   h_np_unc[jk][kl]->SetBinError(ij+1,xx);
    }
   
  }
}

TFile *fileOut = new TFile("NP_Fig2.root","RECREATE");
fileOut->cd();

/*
for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){	
	
hist_radius[fg][ij][ij]->Write();
hist_radius[fg][jk][jk]->Write();
	}
  }
}
*/


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){	

 for(int pt=0; pt<(h_rad_cor_full[ij][jk]->GetNbinsX()); pt++){
	h_rad_cor_full[ij][jk]->SetBinContent(pt+1,fit_rad[ij][jk]->Eval(h_rad_cor_full[ij][jk]->GetBinCenter(pt+1)));	
 }
 
 for(int pt=0; pt<(h_rad_cor[ij][jk]->GetNbinsX()); pt++){
	h_rad_cor[ij][jk]->SetBinContent(pt+1,fit_rad[ij][jk]->Eval(h_rad_cor[ij][jk]->GetBinCenter(pt+1)));	
 }
 
 if(ij==11&&jk==0){
	 for(int pt=0; pt<noptbins_1; pt++){
		gr_rad[ij][jk]->SetPointEYhigh(pt,0.5*radcor_diff[ij][jk][pt]);
		gr_rad[ij][jk]->SetPointEYlow(pt,0.5*radcor_diff[ij][jk][pt]);
		}
	 }
 
 sprintf(name,"Gr_NP_Cor_AK%i_Eta%i",ij+1,jk+1);
 gr_rad[ij][jk]->SetName(name);
 sprintf(name,"NP Correction AK%i %s",ij+1,ybinname[jk]);
 gr_rad[ij][jk]->SetTitle(name);
 gr_rad[ij][jk]->Write();
 
 sprintf(name,"Fitted NP Correction AK%i %s",ij+1,ybinname[jk]);
 fit_rad[ij][jk]->SetTitle(name);
 fit_rad[ij][jk]->Write();
 
 h_rad_cor[ij][jk]->Write();
 h_rad_cor_full[ij][jk]->Write();
 
  } 
}

for(int jk=0; jk<netarange; jk++){	
 for(int kl=0; kl<nopbins; kl++){
	h_np_unc[jk][kl]->Write();

 }
}

fileOut->Write();
fileOut->Close();

delete fileOut;
	
}

int main()
{
Compare_NPFactor_HepData();
}
