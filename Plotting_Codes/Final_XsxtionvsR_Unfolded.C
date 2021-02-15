#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TGraphAsymmErrors.h"

void Final_XsxtionvsR_Unfolded()
{

int unf_choice = 2;
unf_choice -= 1;
const char *unf_name[2] = {"bayes","svd"};
const char *unf_title[2] = {"Bayesian","SVD"};

const int nfiles = 8;

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_nocor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/test_Herwig.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Historam_P8_Noswap.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_Pythia_Userhook2_NNPDF30.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/HerwigEE5C_Files_sel.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/CT14nlo_files.root"};


//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_Pythia_Userhook2_NNPDF30.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/HerwigEE5C_Files_sel.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/CT14nlo_files.root"};

const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_excorfac2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/Bin84_hist_Powheg_Pythia_Userhook2_NNPDF30.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/Bin84_PH_Hwg_CUETHppS1_updated.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Herwig7/Bin84_hist_Herwig7_weighted.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Bin84_CT14nlo_files.root"};


ifstream fp_pt_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_ExpSys_Pt_excor_84.log");
ifstream fp_pt_stat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/StatUnfold_Pt.log");
ifstream fp_pt_th("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_Theory_Unc_Pt_84.log");

//double data_lumi = 32.883;

const int ref = 4;

const char *model_name[nfiles] = {"Data 2016","Herwig++(CUETHS1)","Pythia8(CUETP8M1)","Madgraph","PH+P8(CUETP8M1)","PH+Hwg(CUETHppS1)","Herwig7","NLOJet++ #otimes NP"};
const int col[nfiles] = {1,/*12,*/4,6,2,3,9,12,kCyan+3};
const int algo_style[nfiles] = {20,21,22,23,24,25,27,26};
const int line_sty[nfiles] = {kSolid,kDotted,kDotted,kDotted,kDashed,kDashed,kDashed,kSolid};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs"};//,"ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

double ymax[netarange] = {2.,2.,2.5,2.5,3.,3.,3.,3.,3.,3.} ;

const int nopbins = 10;
double pbins[nopbins+1]={84, 97, 133, 196, 272, 330, 395, 468, 548, 592, 5000.0};

const char* err_name[3] = {"Stat Error","Exp Syst","Exp+Theory Sys"};

/*
const int nopbins = 3;
double pbins[nopbins+1]={74.,120.,1000.,6000.};
*/
const char* pbin_name[nopbins] = {"84 < P_{T}(in GeV) < 97","97 < P_{T}(in GeV) < 133", "133 < P_{T}(in GeV) < 196", "196 < P_{T}(in GeV) < 272", "272 < P_{T}(in GeV) < 330","330 < P_{T}(in GeV) < 395","395 < P_{T}(in GeV) < 468","468 < P_{T}(in GeV) < 548","548 < P_{T}(in GeV) < 592","P_{T}(in GeV) > 592"} ;
//const char* pbin_name[nopbins] = {"74 < Pt < 120","120 < Pt <1000","Pt > 1000"};

const int noptbins = 61;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64, 74,*/ 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

double pt_err_th_up[nalgo][netarange][noptbins];
double pt_err_th_dn[nalgo][netarange][noptbins];

double pt_err_exp_up[nalgo][netarange][noptbins];
double pt_err_exp_dn[nalgo][netarange][noptbins];

double pt_err_stat_up[nalgo][netarange][noptbins];
double pt_err_stat_dn[nalgo][netarange][noptbins];

int xx;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
     for(int kl=0; kl<noptbins; kl++){
	fp_pt_exp>>xx>>xx>>xx>>pt_err_exp_up[ij][jk][kl]>>pt_err_exp_dn[ij][jk][kl];
	fp_pt_stat>>xx>>xx>>xx>>pt_err_stat_up[ij][jk][kl]>>pt_err_stat_dn[ij][jk][kl];	
	fp_pt_th>>xx>>xx>>xx>>pt_err_th_up[ij][jk][kl]>>pt_err_th_dn[ij][jk][kl];

	if(pt_err_exp_up[ij][jk][kl]<0 || pt_err_exp_up[ij][jk][kl] > 1) { pt_err_exp_up[ij][jk][kl] = 0;}
	if(pt_err_exp_dn[ij][jk][kl]<0 || pt_err_exp_dn[ij][jk][kl] > 1) { pt_err_exp_dn[ij][jk][kl] = 0;}
	if(pt_err_stat_up[ij][jk][kl]<0 || pt_err_stat_up[ij][jk][kl] > 1) { pt_err_stat_up[ij][jk][kl] = 0; }
	if(pt_err_stat_dn[ij][jk][kl]<0 || pt_err_stat_dn[ij][jk][kl] > 1) { pt_err_stat_dn[ij][jk][kl] = 0; }
	if(pt_err_th_up[ij][jk][kl]<0 || pt_err_th_up[ij][jk][kl] > 1) { pt_err_th_up[ij][jk][kl] = 0; }
	if(pt_err_th_dn[ij][jk][kl]<0 || pt_err_th_dn[ij][jk][kl] > 1) { pt_err_th_dn[ij][jk][kl] = 0; }
  }
 }
}

fp_pt_exp.close();
fp_pt_stat.close();

cout<<"file done"<<endl;

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

TLine *line = new TLine(0.05,1,0.1*nalgo+0.05,1.);
line->SetLineColor(7);

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

	if((fg<1)){ sprintf(name,"%s_unfold_%s_Etabin%i",unf_name[unf_choice],JetRad[ij],jk+1) ;}
	if((fg>0)) {sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
//	if(fg==4) {sprintf(name,/*"mcjets*/"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}

//	if((nfiles>6)&&(fg==(nfiles-1))) {sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}

	hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
	if(fg==0){
	hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
	}
//	if(fg==0) { hist_pt[fg][ij][jk]->Scale(1./data_lumi) ;  }
	if(fg>3&&fg<(nfiles-2)) { hist_pt[fg][ij][jk]->Scale(1./48191.824);}
	if(fg==(nfiles-2)) { hist_pt[fg][ij][jk]->Scale(11502051.6); }     
 
        if((nfiles>7)&&(fg<(nfiles-1))){
	for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
	     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)));//*(ybin[jk+1]-ybin[jk])));
     	     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)));//*(ybin[jk+1]-ybin[jk])));
    		}
	}

//	if(fg>0) { hist_pt[fg][ij][jk]->Scale(hist_pt[fg][ij][jk]->Integral()*1./hist_pt[0][ij][jk]->Integral());  }

      }
   }
   
   if(fg==3) {
	for(int jk=0; jk<netarange; jk++){
	 for(int bn=0; bn<noptbins; bn++){
//		cout<<"bn "<<bn+1<<endl;
		float kfac = (hist_pt[2][nalgo-2][jk]->GetBinContent(bn+1) > 1.e-9) ? hist_pt[2][nalgo-1][jk]->GetBinContent(bn+1) *1./ hist_pt[2][nalgo-2][jk]->GetBinContent(bn+1) : 1;
		if(kfac > 1.e-6){
		hist_pt[fg][nalgo-1][jk]->SetBinContent(bn+1,kfac*hist_pt[fg][nalgo-1][jk]->GetBinContent(bn+1));
			}
		}
	   }
	}
	
	 if(fg==5||fg==6) {
	for(int jk=0; jk<netarange; jk++){
	 for(int bn=0; bn<noptbins; bn++){
//		cout<<"bn "<<bn+1<<endl;
		float kfac = (hist_pt[fg][nalgo-3][jk]->GetBinContent(bn+1) > 1.e-9) ? hist_pt[fg][nalgo-2][jk]->GetBinContent(bn+1) *1./ hist_pt[fg][nalgo-3][jk]->GetBinContent(bn+1) : 1;
		if(kfac > 1.e-6){
		hist_pt[fg][nalgo-1][jk]->SetBinContent(bn+1,kfac*hist_pt[fg][nalgo-2][jk]->GetBinContent(bn+1));
			}
		}
	   }
	}

}


TH1D *NP_factor[nalgo][netarange];

TFile *file_np = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/NP_Correction_Factor_Pythia.root","read");
file_np->cd();

if(nfiles>6){

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   sprintf(name,"NP_Correction_%s_EtaBin%i",JetRad[ij],jk+1);
   NP_factor[ij][jk] = (TH1D*)file_np->Get(name);
   for(int bn=0; bn<(hist_pt[nfiles-1][ij][jk]->GetNbinsX()); bn++){
        hist_pt[nfiles-1][ij][jk]->SetBinContent(bn+1,hist_pt[nfiles-1][ij][jk]->GetBinContent(bn+1)* NP_factor[ij][jk]->GetBinContent(bn+1));
        }
//	hist_pt[nfiles-1][ij][jk]->Scale(1./(ybin[jk+1]-ybin[jk]));
/*	
	if(ij==3&&jk==0){
		for(int abin=0; abin<noptbins; abin++){
              	cout<<JetRad[ij]<<" eta"<<jk+1<<" pt"<<abin<<" cont "<<hist_pt[0][ij][jk]->GetBinContent(abin+1)<<endl;
				}
                        }
*/
  }
 }
}

double xsection[nfiles][nalgo][netarange][nopbins];

double stat_error_up[nalgo][netarange][nopbins] = {{{0}}};
double stat_error_dn[nalgo][netarange][nopbins] = {{{0}}};
double exp_error_up[nalgo][netarange][nopbins] = {{{0}}};
double exp_error_dn[nalgo][netarange][nopbins] = {{{0}}};
double th_error_up[nalgo][netarange][nopbins] = {{{0}}};
double th_error_dn[nalgo][netarange][nopbins] = {{{0}}};

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
   for(int jk=0; jk<netarange; jk++){

     TAxis *axis = hist_pt[fg][ij][jk]->GetXaxis();

     int amin =0, amax =0;

     for(int kl=0; kl<nopbins; kl++){
	amin = axis->FindBin(pbins[kl]);
	amax = axis->FindBin(pbins[kl+1]);

	xsection[fg][ij][jk][kl]=0;
/*
	for(int abin=amin; abin<amax; abin++){
	xsection[fg][ij][jk][kl]+= hist_pt[fg][ij][jk]->GetBinContent(abin+1) * hist_pt[fg][ij][jk]->GetBinWidth(abin+1);
	}
*/
	xsection[fg][ij][jk][kl] = hist_pt[fg][ij][jk]->Integral(amin,amax,"width");

	if(fg==0&&ij==5&&jk==1){
	cout<<"amin "<<amin<<" amax "<<amax<<" cont "<<hist_pt[fg][ij][jk]->GetBinContent(amin+1)<<" integral "<<hist_pt[fg][ij][jk]->Integral(amin,amax)<<" xsection "<<xsection[fg][ij][jk][kl]<<endl;
	}

	if(fg==0){

		stat_error_up[ij][jk][kl] = stat_error_dn[ij][jk][kl] = exp_error_up[ij][jk][kl] = exp_error_dn[ij][jk][kl] = 0;

		for(int abin=amin; abin<amax; abin++){

		stat_error_up[ij][jk][kl] += pow(pt_err_stat_up[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
		stat_error_dn[ij][jk][kl] += pow(pt_err_stat_dn[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
		exp_error_up[ij][jk][kl] += pow(pt_err_exp_up[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
		exp_error_dn[ij][jk][kl] += pow(pt_err_exp_dn[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
		th_error_up[ij][jk][kl] += pow(pt_err_th_up[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
		th_error_dn[ij][jk][kl] += pow(pt_err_th_dn[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
/*	      if(ij==5&&jk==1){
	      cout<<JetRad[ij]<<" eta"<<jk+1<<" pt"<<abin<<" cont "<<hist_pt_org[fg][ij][jk]->GetBinContent(abin+1)<<" div cont "<<hist_pt[fg][ij][jk]->GetBinContent(abin+1)<<" errfrac up "<<pt_err_exp_up[ij][jk][abin]<<" errorfrac down "<<pt_err_exp_dn[ij][jk][abin]<<" errup mul "<<pt_err_exp_up[ij][jk][abin]*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1)<<" errdn mul "<<pt_err_exp_dn[ij][jk][abin]*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1)<<endl;
*/
			}

		th_error_up[ij][jk][kl] += exp_error_up[ij][jk][kl];
		th_error_dn[ij][jk][kl] += exp_error_dn[ij][jk][kl];

		stat_error_up[ij][jk][kl] = sqrt(stat_error_up[ij][jk][kl]);// * (ybin[jk+1]-ybin[jk]);
		stat_error_dn[ij][jk][kl] = sqrt(stat_error_dn[ij][jk][kl]);// * (ybin[jk+1]-ybin[jk]);
		exp_error_up[ij][jk][kl] = sqrt(exp_error_up[ij][jk][kl]);// * (ybin[jk+1]-ybin[jk]);
		exp_error_dn[ij][jk][kl] = sqrt(exp_error_dn[ij][jk][kl]);// * (ybin[jk+1]-ybin[jk]);

		th_error_up[ij][jk][kl] = sqrt(th_error_up[ij][jk][kl]);
		th_error_dn[ij][jk][kl] = sqrt(th_error_dn[ij][jk][kl]);

		if(ij==3&&jk==0){
		cout<<"tot err up "<<exp_error_up[ij][jk][kl]<<" tot err dn "<<exp_error_dn[ij][jk][kl]<<" therr up "<<th_error_up[ij][jk][kl]<<" therr dn "<<th_error_dn[ij][jk][kl]<<" cont "<<xsection[fg][ij][jk][kl]<<endl;
			}
		}

       }

      }
    }
  }


TH1D *sigmaR[nfiles][netarange][nopbins];
TH1D *sigmaR_rat[nfiles-1][netarange][nopbins];

for(int fg=0; fg<nfiles; fg++){
 for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<nopbins; kl++){
	sprintf(name,"histRad_EtaBin%i_ptbin%i_File%i",jk+1,kl+1,fg+1);
	sigmaR[fg][jk][kl] = new TH1D(name,name,nalgo,0.05,1.25);
	for(int ij=0; ij<nalgo; ij++){
	sigmaR[fg][jk][kl]->SetBinContent(ij+1,xsection[fg][ij][jk][kl]);
	}
	if(fg>0){
	sigmaR_rat[fg-1][jk][kl] = (TH1D*)sigmaR[fg][jk][kl]->Clone();
	sigmaR_rat[fg-1][jk][kl]->Divide(sigmaR[0][jk][kl]);

	sigmaR_rat[fg-1][jk][kl]->SetLineColor(col[fg]);
	sigmaR_rat[fg-1][jk][kl]->SetLineStyle(line_sty[fg]);
	sigmaR_rat[fg-1][jk][kl]->SetMaximum(ymax[jk]);
	sigmaR_rat[fg-1][jk][kl]->SetMinimum(0.25);

	sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetTitle("Jet Radius");
	sigmaR_rat[fg-1][jk][kl]->GetXaxis()->CenterTitle();
	sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetTitleSize(0.1);
	sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetLabelSize(0.08);
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitle("Ratio to Data");
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->CenterTitle();
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitleSize(0.1);
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetLabelSize(0.075);
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitleOffset(0.7);
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetNdivisions(505);

	sigmaR_rat[fg-1][jk][kl]->SetMarkerSize(1);
	sigmaR_rat[fg-1][jk][kl]->SetMarkerStyle(algo_style[fg]);
	sigmaR_rat[fg-1][jk][kl]->SetMarkerColor(col[fg]);
	}
   }
 }
}

TGraph *gr_pt[nfiles][netarange][nopbins];
TMultiGraph *mul_gr[netarange][nopbins];
TMultiGraph *mul_gr_err[netarange][nopbins];

TLegend *leg[netarange][nopbins];
TLegend *leg_err[netarange][nopbins];

TGraphAsymmErrors *tg_error[netarange][nopbins];
TGraphAsymmErrors *tg_th_error[netarange][nopbins];

for(int jk=0; jk<netarange; jk++){
  for(int kl=0; kl<nopbins; kl++){

        if(jk<6){
	leg[jk][kl] = new TLegend(0.17,0.625,0.4,0.9);
	leg_err[jk][kl] = new TLegend(0.17,0.535,0.4,0.625);
	}
	else{
        leg[jk][kl] = new TLegend(0.6,0.15,0.8,0.4);
	leg_err[jk][kl] = new TLegend(0.6,0.125,0.8,0.15);
	}

	leg_err[jk][kl]->SetTextSize(0.03);
	leg_err[jk][kl]->SetTextFont(42);
	leg_err[jk][kl]->SetBorderSize(0);

	mul_gr[jk][kl] = new TMultiGraph();
	mul_gr_err[jk][kl] = new TMultiGraph();

     for(int fg=0; fg<nfiles; fg++){

	gr_pt[fg][jk][kl] = new TGraph();

	for(int ij=0; ij<nalgo; ij++){
	gr_pt[fg][jk][kl]->SetPoint(ij,0.1*(ij+1),xsection[fg][ij][jk][kl]) ;
        }	

	gr_pt[fg][jk][kl]->SetLineColor(col[fg]);
	gr_pt[fg][jk][kl]->GetXaxis()->SetTitle("Jet Radius");
	gr_pt[fg][jk][kl]->GetXaxis()->SetTitleSize(0.05);
	gr_pt[fg][jk][kl]->GetXaxis()->SetLabelSize(0.035);

	gr_pt[fg][jk][kl]->SetMarkerColor(col[fg]);
	gr_pt[fg][jk][kl]->SetMarkerSize(1);
	gr_pt[fg][jk][kl]->SetMarkerStyle(algo_style[fg]);
	gr_pt[fg][jk][kl]->SetLineStyle(line_sty[fg]);

	mul_gr[jk][kl]->Add(gr_pt[fg][jk][kl]);
	leg[jk][kl]->AddEntry(gr_pt[fg][jk][kl],model_name[fg],"lp");
  }

	double xval[nalgo], yval[nalgo], yerr_up[nalgo], yerr_dn[nalgo], yerr_th_up[nalgo], yerr_th_dn[nalgo];
	for(int ij=0; ij<nalgo; ij++){
	
		xval[ij] = 0.1*(ij+1);
		yval[ij] = xsection[0][ij][jk][kl];
		yerr_up[ij] = exp_error_up[ij][jk][kl];//stat_error_up[ij][jk][kl];	
		yerr_dn[ij] = exp_error_dn[ij][jk][kl];//stat_error_dn[ij][jk][kl];

		yerr_th_up[ij] = th_error_up[ij][jk][kl];
		yerr_th_dn[ij] = th_error_dn[ij][jk][kl];

		if(jk==0&&kl==(nopbins-1)){
		cout<<jk<<" "<<kl<<" "<<ij<<" "<<xval[ij]<<" "<<yval[ij]<<" "<<yerr_up[ij]<<endl;
		  }
		}

		tg_error[jk][kl] = new TGraphAsymmErrors(nalgo,xval,yval,NULL,NULL,yerr_up,yerr_dn);
		tg_th_error[jk][kl] = new TGraphAsymmErrors(nalgo,xval,yval,NULL,NULL,yerr_th_up,yerr_th_dn);
		mul_gr_err[jk][kl]->Add(tg_error[jk][kl]);
		leg_err[jk][kl]->AddEntry(tg_error[jk][kl],err_name[1],"f");
		leg_err[jk][kl]->AddEntry(tg_th_error[jk][kl],err_name[2],"f");
			
//	mul_gr[jk][kl]->GetXaxis()->SetTitle("Jet Radius");
//	mul_gr[jk][kl]->GetXaxis()->SetTitleSize(0.05);
//	mul_gr[jk][kl]->GetXaxis()->SetLabelSize(0.035);
 }	
}

TCanvas *c2[netarange][nopbins];
//TLegend *leg[netarange][nopbins];

for(int jk=0; jk<netarange; jk++){
 for(int kl=0; kl<nopbins; kl++){

   sprintf(name,"Xsection_EtaBin%i_PtBin%i",jk+1,kl+1);
   c2[jk][kl] = tdrmyDiCanvas(name,sigmaR[2][jk][kl],sigmaR[0][jk][kl],2.,6,0);
   c2[jk][kl]->cd(1);
   gPad->SetLogy(0);
   gPad->SetLogx(0);

   TLatex latex;
   latex.SetNDC();
   latex.SetTextAngle(0);
   latex.SetTextColor(kBlack);

   latex.SetTextFont(42);
   latex.SetTextAlign(31);
   latex.SetTextSize(0.055);

   TString text;
   text+= ybinname[jk];
   TString text1;
   text1+= pbin_name[kl] ;

   mul_gr[jk][kl]->Draw("ALP");

   tg_error[jk][kl]->SetFillColor(kViolet+3);
   tg_error[jk][kl]->SetFillStyle(3005);
   tg_error[jk][kl]->Draw("SAME:E3");

   tg_th_error[jk][kl]->SetFillColor(kPink-7);
   tg_th_error[jk][kl]->SetFillStyle(3004);
   tg_th_error[jk][kl]->Draw("SAME:E3");

//   tg_error[jk][kl]->Draw("sames");

   mul_gr[jk][kl]->GetYaxis()->SetTitle("Integrated Cross Section (in fb)");
   mul_gr[jk][kl]->GetYaxis()->SetTitleSize(0.055);
   mul_gr[jk][kl]->GetYaxis()->CenterTitle();
   mul_gr[jk][kl]->GetYaxis()->SetTitleOffset(1.3);

   leg[jk][kl]->SetBorderSize(0);
   leg[jk][kl]->SetTextSize(0.04);
   leg[jk][kl]->SetTextFont(42);
   leg[jk][kl]->Draw();
   leg_err[jk][kl]->Draw("sames");

   if(jk<6){
   latex.DrawLatex(0.75,0.85,text);
   latex.SetTextSize(0.05);
   latex.DrawLatex(0.875,0.075,text1);
        }else{
           latex.DrawLatex(0.75,0.45,text);
           latex.DrawLatex(0.78,0.38,text1);
        }

   c2[jk][kl]->cd(2);
   gPad->SetLogx(0);

   for(int fg=0; fg<(nfiles-1); fg++){

  if(fg==0) {    sigmaR_rat[fg][jk][kl]->Draw("CP"); }
	else {	sigmaR_rat[fg][jk][kl]->Draw("CPSAME");	}
   }

   line->Draw();
  

  sprintf(name,"Xsection_Plots_Unfolded/Bin84/%s/XsectionR_EtaBin%i_PtBin%i.eps",unf_title[unf_choice],jk+1,kl+1);
  c2[jk][kl]->SaveAs(name);

 }
}

}

int main()
{
Final_XsxtionvsR_Unfolded();
}

