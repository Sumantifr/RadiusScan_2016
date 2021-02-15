#include "TDecompSVD.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TTree.h>
#include <TCanvas.h>
#include "TVector.h"
#include <vector>
#include <TF1.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TStyle.h>
#include "TPostScript.h"
#include <TPad.h>
#include <TLine.h>
#include <TRandom.h>

#include "RooUnfold.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldBinByBin.h"
#include "RooUnfoldResponse.h"
#include "TLegend.h"

using namespace std;
using namespace CLHEP;

#define Data
//#define MC

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int noptbins1 = 31;
double ptbins1[noptbins1+1] = {/*30,43,56,*/74,97,133,174,220,272,330,395,468,548,638,737,846,967,1101,1248,1410,1588,1784,2000,2238,2500,2787,3103,3450,3832,4252,4713,5220,5777,6389,7000};

const int nalgo = 12;
const char* JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

//const int bayes_par[nalgo] = {6,6,6,7,7,7,7,8,8,9,9,9};
const int bayes_par[nalgo] = {10,8,7,7,7,7,8,9,10,12,13,14};
const int svd_par = 9;

double data_lumi = 33.6;
     
const char* namex;
char namey[100];
const char* titlex;
char titley[100];

int getbinid(double val, int nbmx, double* array) {
  if (val<array[0]) return -1;
  for (int ix=1; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -1;
}


int subtract_background(TH2D* h2d_correl, TH1D* reco, TH1D* gen, TH1D* data, double* fakerate, double* effi, double* purity, double* stbl) {

int nbinx = h2d_correl->GetNbinsX();
int nbiny = h2d_correl->GetNbinsY();

 const int nbinmx = 100 ;
 double totalgen[nbinmx]={0.};
 double totalreco[nbinmx]={0.};

 for (int ix=0; ix<nbinx+1; ix++) {
      for (int iy=0; iy<nbiny+1; iy++) {

	if(ix==0&&iy==0) continue ;
	 totalreco[ix] +=h2d_correl->GetBinContent(ix, iy); 
        if (iy==0) fakerate[ix-1] =h2d_correl->GetBinContent(ix,iy);

         totalgen[iy] +=h2d_correl->GetBinContent(ix, iy); 
        if (ix==0) effi[iy-1] =h2d_correl->GetBinContent(ix, iy);

	if (ix==0 || iy==0) {
          h2d_correl->SetBinContent(ix, iy, 0.0);
          h2d_correl->SetBinError(ix, iy, 0.0);
        }
  }//iy
 }//ix

 for (int iy=0; iy<nbiny; iy++) {
      effi[iy] = (totalgen[iy+1] - effi[iy])/max(1.e-10, totalgen[iy+1]);
      if (effi[iy]<1.e-3) effi[iy]=1.e-6;
    } //iy

 for (int ix=0; ix<nbinx; ix++){
	fakerate[ix] /=max(1.e-10, totalreco[ix+1]);
 }//ix
   
 for(int ix=0; ix <((reco->GetNbinsX())+1); ix++){
 	reco->SetBinContent(ix+1,(1-fakerate[ix])*(reco->GetBinContent(ix+1)));
	reco->SetBinError(ix+1,(1-fakerate[ix])*(reco->GetBinError(ix+1)));
  }

 for(int ix=0; ix <((data->GetNbinsX())+1); ix++){
        data->SetBinContent(ix+1,(1-fakerate[ix])*(data->GetBinContent(ix+1)));
        data->SetBinError(ix+1,(1-fakerate[ix])*(data->GetBinError(ix+1)));
  }
/*
 for(int ix=0; ix<(gen->GetNbinsX()+1); ix++){
       gen->SetBinContent(ix+1,(gen->GetBinContent(ix+1))*effi[ix]) ;
       gen->SetBinError(ix+1,(gen->GetBinError(ix+1))*effi[ix]) ;
  }
*/
 double tot_reco_in[nbinmx] = {0.};
 double tot_gen_in[nbinmx] = {0.};

 for(int bn=0; bn<nbinx; bn++){
  for(int am=0; am<nbiny; am++){
    tot_gen_in[am]+=h2d_correl->GetBinContent(bn+1,am+1);
    tot_reco_in[bn]+=h2d_correl->GetBinContent(bn+1,am+1);
  }
 }

    for(int bn=0; bn<nbinx; bn++){
    purity[bn] = (tot_reco_in[bn]>1.e-7)?h2d_correl->GetBinContent(bn+1,bn+1)*1./tot_reco_in[bn]:0.;
    stbl[bn] = (tot_gen_in[bn]>1.e-7)?h2d_correl->GetBinContent(bn+1,bn+1)*1./tot_gen_in[bn]:0.;
	}

}

int LastBin_Counter(TH1D *h1){
int lastbin = 0;
for(int bn=0; bn<(h1->GetNbinsX()); bn++){
if((h1->GetBinContent(bn+1)) > 1.e-12){
lastbin = bn+1;
}
else { break;}
}
return lastbin; 
}

int main()																																 
{	

double integral_ratio = 1.;
/*const char* rootfiles[3] = {"../CPlusPlus/CMS_Files/Jets_in_CMS/Data_2015D/hist_RecoJetchs_PU_Data_2015D_JetHTCHS_NewPrescale_v2.root","../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root"/,"Response_Matrix/Spline_output_ak4.root"}	;*/

TFile *fileout ;
fileout = new TFile("Unfolded_2016_Data_ModJES_Legacy_Jun2019.root","recreate") ;

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/hist_RecoJetchs_PU_Data_2016_JetHTfinal.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor.root"};
const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/hist_RecoJetchs_PU_Data_2016_JetHTfinal.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15.root"};

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_NTuples.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_NTuples.root"};

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_JECor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_NTuples.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_NTuples.root"};

char name[100];
/*
const int nalgo = 1;
const char* JetRad[nalgo] = {"ak4"};
*/
const int Etabins = 10;

const int njes = 75;

TH1D *hist_data[nalgo][Etabins][njes];
TH1D *hist_reco[nalgo][Etabins][njes];
TH1D *hist_gen[nalgo][Etabins][njes];
TH2D *mat_rm[nalgo][Etabins][njes];
TH2D *mat_rm_b[nalgo][Etabins][njes];
TH1D *hist_bayes[nalgo][Etabins][njes] = {{{0}}};
TH1D *hist_svd[nalgo][Etabins][njes] = {{{0}}};
TH1D *hist_BbB[nalgo][Etabins][njes] = {{{0}}};

int lastbin[nalgo][Etabins][njes] = {{{0}}};


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  for(int kl=0; kl<njes; kl++){
  
  sprintf(name,"Bayes_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,kl);
  hist_bayes[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins) ;
 
  sprintf(name,"SVD_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,kl);
  hist_svd[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"BinbyBin_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,kl);
  hist_BbB[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins) ;

  }//kl
 }//jk
}//ij

for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();

 for(int jk=0; jk<nalgo; jk++){
  for(int kl=0; kl<Etabins; kl++){
    for(int mn=0; mn<njes; mn++){

if(ij==0){
	sprintf(name,"mcjets/JetpT_%s_EtaBin%i_JES%i",JetRad[jk],kl+1,mn);
//	sprintf(name,"JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
	hist_data[jk][kl][mn] = (TH1D*)file1->Get(name);
	hist_data[jk][kl][mn]->Scale(1./data_lumi);
	}
if(ij==1) {
	sprintf(name,"JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
	hist_reco[jk][kl][mn] = (TH1D*)file1->Get(name); 
	sprintf(name,"%s_JES%i",hist_reco[jk][kl][mn]->GetName(),mn);
	hist_reco[jk][kl][mn]->SetName(name);
	
    sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
	hist_gen[jk][kl][mn] = (TH1D*)file1->Get(name); 
	sprintf(name,"%s_JES%i",hist_gen[jk][kl][mn]->GetName(),mn);
    hist_gen[jk][kl][mn]->SetName(name);	

	}
if(ij==2) {
	sprintf(name,"RecoJetvsGenJet_%s_EtaBin%i",JetRad[jk],kl+1);
	mat_rm[jk][kl][mn] = (TH2D*)file1->Get(name); 
    mat_rm_b[jk][kl][mn] = (TH2D*)mat_rm[jk][kl][mn]->Clone();

	sprintf(name,"%s_JES%i",mat_rm_b[jk][kl][mn]->GetName(),mn);
    mat_rm_b[jk][kl][mn]->SetName(name);
	}
     }//mn
   }//kl
  }//jk
}//ij


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  for(int kl=0; kl<njes; kl++){
    
    double fakerate[100] = {0.};
    double eff[100] ;
    for(int jj=0; jj<100; jj++){
     eff[jj] = 1.;
    }
	double purity[100];
    double stbl[100];

    subtract_background(mat_rm_b[ij][jk][kl],hist_reco[ij][jk][kl],hist_gen[ij][jk][kl],hist_data[ij][jk][kl],fakerate,eff,purity,stbl) ;

	RooUnfoldResponse response_b;
	sprintf(name,"unfold_%s_Etabin%i_JES%i",JetRad[ij],jk+1,kl);
	response_b = RooUnfoldResponse(hist_reco[ij][jk][kl],hist_gen[ij][jk][kl], mat_rm_b[ij][jk][kl], name, name);

	TH1D *hist_input;

	hist_input = (TH1D*)hist_data[ij][jk][kl]->Clone();

	RooUnfoldBayes unfoldBayes(&response_b,hist_input,bayes_par[ij],false);

	RooUnfoldSvd unfoldSvd(&response_b,hist_input,svd_par);

	RooUnfoldBinByBin unfoldBbB(&response_b,hist_input);

	fileout->cd();

	hist_bayes[ij][jk][kl] = (TH1D*) unfoldBayes.Hreco(RooUnfold::kCovariance)->Clone();	
	sprintf(name,"bayes_%s",hist_bayes[ij][jk][kl]->GetName());
	hist_bayes[ij][jk][kl]->SetName(name);
	

	hist_svd[ij][jk][kl]  =  (TH1D*) unfoldSvd.Hreco(RooUnfold::kCovariance)->Clone();
	sprintf(name,"svd_%s",hist_svd[ij][jk][kl]->GetName());
	hist_svd[ij][jk][kl]->SetName(name);
	
	hist_BbB[ij][jk][kl]  =  (TH1D*) unfoldBbB.Hreco(RooUnfold::kCovariance)->Clone();
	sprintf(name,"BbB_%s",hist_BbB[ij][jk][kl]->GetName());
	hist_BbB[ij][jk][kl]->SetName(name);
	

  }
 }
}

fileout->cd();
fileout->Write();
fileout->Close();

}

