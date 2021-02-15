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

#include "TUnfold.h"
#include "RooUnfoldTUnfold.h"

using namespace std;
using namespace CLHEP;

#define Data
//#define MC

const int noptbins = 61;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64, 74,*/ 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int nalgo = 12;
const char* JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

//const int bayes_par[nalgo] = {6,6,6,7,7,7,7,8,8,9,9,9};
const int bayes_par[2][nalgo] = {{10,8,9,9,10,10,9,9,10,12,13,14},{13,11,11,11,12,12,13,13,14,15,16,16}};
const int svd_par[nalgo]= {7,7,7,7,7,9,9,9,9,9,9,9};

float data_lumi = 1;//32.882;
     
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
        if (iy==0) fakerate[ix-1] = h2d_correl->GetBinContent(ix,iy);

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
  
      if(iy>10 && effi[iy]>0.1 && effi[iy]<0.9){
        effi[iy] = effi[iy-1]-0.001;
	}

      if (effi[iy]<1.e-6) effi[iy]=1.e-6;
    } //iy

 for (int ix=0; ix<nbinx; ix++){
if(totalreco[ix+1]>1.e-6) {	fakerate[ix] /= totalreco[ix+1]; }
 else { fakerate[ix] = 0.; } 

 if((ix>20&&fakerate[ix]>0.05) || (ix>10&&fakerate[ix]>0.2)) { fakerate[ix] = 1.e-3;  }

 }//ix
   
 for(int ix=0; ix <((reco->GetNbinsX())+1); ix++){
 	reco->SetBinContent(ix+1,(1-fakerate[ix])*(reco->GetBinContent(ix+1)));
	reco->SetBinError(ix+1,(1-fakerate[ix])*(reco->GetBinError(ix+1)));
  }

 for(int ix=0; ix <((data->GetNbinsX())+1); ix++){
        data->SetBinContent(ix+1,(1-fakerate[ix])*(data->GetBinContent(ix+1)));
        data->SetBinError(ix+1,(1-fakerate[ix])*(data->GetBinError(ix+1)));
  }

 for(int ix=0; ix<(gen->GetNbinsX()+1); ix++){
       gen->SetBinContent(ix+1,(gen->GetBinContent(ix+1))*effi[ix]) ;
       gen->SetBinError(ix+1,(gen->GetBinError(ix+1))*effi[ix]) ;
  }

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


void Fold(TH2D* HistoMatrix, TH1D* HistoGen, TH1D* HistoUnfold, TH1D* HistoCorrect){

  double probFake=0.;
  double AwayMatrixTot=0.;
  
   for(int i=1;i<HistoGen->GetXaxis()->GetNbins()+1;i++){
    double Inside=0.;
    double ErrorP=0.;
    double sum = 0.;
    for(int j=1;j<HistoGen->GetXaxis()->GetNbins()+1;j++){
      probFake=0;
      AwayMatrixTot=HistoMatrix->GetBinContent(i,j)/HistoGen->GetBinContent(j);
      if(HistoGen->GetBinContent(j)==0) AwayMatrixTot=1;
      Inside=Inside+HistoUnfold->GetBinContent(j)*AwayMatrixTot;//*eff[j];///(1-probFake);
      ErrorP=ErrorP+HistoUnfold->GetBinError(j)*AwayMatrixTot/(1-probFake)*HistoUnfold->GetBinError(j)*AwayMatrixTot;
      sum+= +AwayMatrixTot;
    }
    HistoCorrect->SetBinContent(i,Inside);
    double Error=sqrt(ErrorP);
    //double Error=ErrorP;
    HistoCorrect->SetBinError(i,Error);
  }
}

void ReFold(TH2D* HistoMatrix,  TH1D* HistoGen, TH1D* HistoUnfold, TH1D* HistoCorrect){

for(int ij=0; ij<(HistoMatrix->GetNbinsX()); ij++){
double row_sum = 0.;
 for(int jk=0; jk<(HistoMatrix->GetNbinsX()); jk++){
  row_sum+=HistoMatrix->GetBinContent(jk+1,ij+1);
}//jk
if(row_sum>1.e-10){
 for(int jk=0; jk<(HistoMatrix->GetNbinsX()); jk++){
   HistoMatrix->SetBinContent(jk+1,ij+1,HistoMatrix->GetBinContent(jk+1,ij+1)*1./row_sum) ;
  }//jk
 }
}//ij

for(int ij=0; ij<(HistoMatrix->GetNbinsX()); ij++){
 double sum =0.;
 double error = 0.;
 for(int jk=0; jk<(HistoMatrix->GetNbinsX()); jk++){
  sum+= HistoMatrix->GetBinContent(ij+1,jk+1) * HistoUnfold->GetBinContent(jk+1) ;
  error+=HistoMatrix->GetBinContent(ij+1,jk+1) * HistoUnfold->GetBinError(jk+1);
 }//jk
   HistoCorrect->SetBinContent(ij+1,sum);
    HistoCorrect->SetBinError(ij+1,error);
}//ij

}

void BackFold_Gen(RooUnfoldResponse response_b, TH1D* hist_gen, TH1D* hist_back,double *eff,double* fakerate){
for(int am=0; am<(hist_gen->GetNbinsX()); am++){
hist_gen->SetBinContent(am+1,/*eff[am]*/hist_gen->GetBinContent(am+1)) ;
}
TMatrixD rm_mat_bfold = response_b.Mresponse();
for(int bn=0; bn<(hist_gen->GetNbinsX()); bn++){
  double sum = 0.;
  double err_sq=0.;
  for(int am=0; am<(hist_gen->GetNbinsX()); am++){
   sum+=rm_mat_bfold[bn][am]*hist_gen->GetBinContent(am+1);
   err_sq+=pow(rm_mat_bfold[bn][am]*hist_gen->GetBinError(am+1),2.);
  }//am
    err_sq = sqrt(err_sq);
    hist_back->SetBinContent(bn+1,sum*1./(1-fakerate[bn]));
    hist_back->SetBinError(bn+1,err_sq*1./(1-fakerate[bn]));
 }//bn
}

void BackFold_Bayesian(RooUnfoldResponse response_b, RooUnfoldBayes unfold, TH1D* hist_back,double *eff,double* fakerate){

TMatrixD rm_mat_bfold = response_b.Mresponse();
TVectorD bfold_proxy = unfold.Vreco();
TVectorD bfold_err_proxy = unfold.ErecoV();
/*
for(int bn=0; bn < (hist_back->GetNbinsX()); bn++){
bfold_proxy[bn]*=eff[bn];
bfold_err_proxy[bn]*=eff[bn];
}
*/
TVectorD bfold = rm_mat_bfold * bfold_proxy;
TVectorD bfold_err = rm_mat_bfold * bfold_err_proxy;

for(int bn=0; bn < (hist_back->GetNbinsX()); bn++){
 hist_back->SetBinContent(bn+1,bfold[bn]*1./(1-fakerate[bn])) ;
 hist_back->SetBinError(bn+1,bfold_err[bn]*1./(1-fakerate[bn])) ;
}

double sum=0;
for(int ij=0; ij < (hist_back->GetNbinsX()); ij++){
sum+=rm_mat_bfold[5][ij];
}
}

void BackFold_Svd(RooUnfoldResponse response_b, RooUnfoldSvd unfold, TH1D* hist_back,double *eff,double* fakerate){

TMatrixD rm_mat_bfold = response_b.Mresponse();
TVectorD bfold_proxy = unfold.Vreco();
TVectorD bfold_err_proxy = unfold.ErecoV();
/*
for(int bn=0; bn < (hist_back->GetNbinsX()); bn++){
bfold_proxy[bn]*=eff[bn];
bfold_err_proxy[bn]*=eff[bn];
}
*/
TVectorD bfold = response_b.Mresponse() * bfold_proxy;//unfold.Vreco();
TVectorD bfold_err = rm_mat_bfold * bfold_err_proxy;

for(int bn=0; bn < (hist_back->GetNbinsX()); bn++){
  hist_back->SetBinContent(bn+1,bfold[bn]*1./(1-fakerate[bn])) ;
  hist_back->SetBinError(bn+1,bfold_err[bn]*1./(1-fakerate[bn])) ;
 }
}

void BackFold_BinbyBin(RooUnfoldResponse response_b, RooUnfoldBinByBin unfold, TH1D* hist_back,double *eff,double* fakerate){

TMatrixD rm_mat_bfold = response_b.Mresponse();
TVectorD bfold_proxy = unfold.Vreco();
TVectorD bfold_err_proxy = unfold.ErecoV();
/*
for(int bn=0; bn < (hist_back->GetNbinsX()); bn++){
bfold_proxy[bn]*=eff[bn];
bfold_err_proxy[bn]*=eff[bn];
}
*/
TVectorD bfold = response_b.Mresponse() * bfold_proxy; //unfold.Vreco();
TVectorD bfold_err = rm_mat_bfold * bfold_err_proxy;

for(int bn=0; bn < (hist_back->GetNbinsX()); bn++){
  hist_back->SetBinContent(bn+1,bfold[bn]*1./(1-fakerate[bn])) ;
  hist_back->SetBinError(bn+1,bfold_err[bn]*1./(1-fakerate[bn])) ;
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
double integral_ratio = 1;//33.418;

TFile *fileout ;
fileout = new TFile("Unfolded_2016C_Data_NTuple_MC_P8_nocor_trial_nocor.root","recreate") ;

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root"};

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root"};

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_files_excornewx2_84.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50.root"};

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_excorfac2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50.root"};

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_excor.root"};

/////const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_files_nocor_84.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_Pythia_ntuple_OneReso_PUDn.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_Pythia_ntuple_OneReso_PUDn.root"};

const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root"};

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_lowptbins.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_lowptbins.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_lowptbins.root"};

char name[100];

/*const int nalgo = 1;
const char* JetRad[nalgo] = {"ak4"};
*/
const int Etabins = 10;

TH1D *hist_data[nalgo][Etabins];
TH1D *hist_data2[nalgo][Etabins];
TH1D *hist_reco[nalgo][Etabins];
TH1D *hist_reco2[nalgo][Etabins];
TH1D *hist_gen[nalgo][Etabins];
TH1D *hist_gen2[nalgo][Etabins];
TH2D *mat_rm[nalgo][Etabins];
TH2D *mat_rm_b[nalgo][Etabins];
TH1D *hist_bayes[nalgo][Etabins] = {{0}};
TH1D *hist_svd[nalgo][Etabins] = {{0}};
TH1D *hist_BbB[nalgo][Etabins] = {{0}};
TH1D *hist_bayes_back[nalgo][Etabins] = {{0}};
TH1D *hist_svd_back[nalgo][Etabins] = {{0}};
TH1D *hist_BbB_back[nalgo][Etabins] = {{0}};
TH1D *hist_bayes_error[nalgo][Etabins] = {{0}};
TH1D *hist_svd_error[nalgo][Etabins] = {{0}};
TH1D *hist_BbB_error[nalgo][Etabins] = {{0}};
TH1D *hist_gen_fold[nalgo][Etabins] = {{0}};

TH1D* hist_eff[nalgo][Etabins];
TH1D* hist_fake[nalgo][Etabins];
TH1D* hist_purity[nalgo][Etabins];
TH1D* hist_stbl[nalgo][Etabins];


TH2D* COV_Mat_bayes[nalgo][Etabins];
TH2D* COV_Mat_svd[nalgo][Etabins];
TH2D* COV_Mat_BbB[nalgo][Etabins];

int lastbin[nalgo][Etabins] = {{0}};

double chisq_bayes[nalgo][Etabins] = {{0.}};
double chisq_svd[nalgo][Etabins] = {{0.}};
TMatrixD covdata_bayes[nalgo][Etabins];
TMatrixD covdata_svd[nalgo][Etabins];

TMatrixD covmatrix_bayes[nalgo][Etabins];
TMatrixD covmatrix_svd[nalgo][Etabins];
TMatrixD covmatrix_BbB[nalgo][Etabins];

TMatrixD mat_measured[nalgo][Etabins];
TH2D *hist_mat_measured[nalgo][Etabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  
  sprintf(name,"Bayes_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_bayes[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;
 
  sprintf(name,"SVD_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_svd[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"BinbyBin_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_BbB[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"COV_Bayes_%s_EtaBin%i",JetRad[ij],jk+1);
  COV_Mat_bayes[ij][jk] = new TH2D(name,name,noptbins,0,noptbins,noptbins,0,noptbins);
  COV_Mat_bayes[ij][jk]->Sumw2();

  sprintf(name,"COV_SVD_%s_EtaBin%i",JetRad[ij],jk+1);
  COV_Mat_svd[ij][jk] = new TH2D(name,name,noptbins,0,noptbins,noptbins,0,noptbins);
  COV_Mat_svd[ij][jk]->Sumw2();

  sprintf(name,"COV_BbB_%s_EtaBin%i",JetRad[ij],jk+1);
  COV_Mat_BbB[ij][jk] = new TH2D(name,name,noptbins,0,noptbins,noptbins,0,noptbins);
  COV_Mat_BbB[ij][jk]->Sumw2();

  sprintf(name,"Bayes_%s_EtaBin%i_back",JetRad[ij],jk+1);
  hist_bayes_back[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"SVD_%s_EtaBin%i_back",JetRad[ij],jk+1);
  hist_svd_back[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"BinbyBin_%s_EtaBin%i_back",JetRad[ij],jk+1);
  hist_BbB_back[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"Bayes_%s_EtaBin%i_error",JetRad[ij],jk+1);
  hist_bayes_error[ij][jk] = new TH1D(name,name,noptbins,1,noptbins);

  sprintf(name,"SVD_%s_EtaBin%i_error",JetRad[ij],jk+1);
  hist_svd_error[ij][jk] = new TH1D(name,name,noptbins,1,noptbins);

  sprintf(name,"BinbyBin_%s_EtaBin%i_error",JetRad[ij],jk+1);
  hist_BbB_error[ij][jk] = new TH1D(name,name,noptbins,1,noptbins);

  sprintf(name,"Gen_Fold_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_gen_fold[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"Efficiency_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_eff[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"Fake_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_fake[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"Purity_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_purity[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;
 
  sprintf(name,"Stability_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_stbl[ij][jk] = new TH1D(name,name,noptbins,ptbins) ;

 }
}

/*
int ialgo = 4;
int ieta = 1;

 cout<<"algo ak"<<ialgo<<" eta"<<ieta<<endl;
 */
for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();

 for(int jk=0; jk<nalgo; jk++){
  for(int kl=0; kl<Etabins; kl++){

if(ij==0) {
//	sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
	sprintf(name,"JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
	hist_data[jk][kl] = (TH1D*)file1->Get(name);
	hist_data[jk][kl]->Scale(1./data_lumi);

	sprintf(name,"Measured_Cov_%s_EtaBin%i",JetRad[jk],kl+1);
        hist_mat_measured[jk][kl] = (TH2D*)file1->Get(name);
	}
if(ij==1) {
	sprintf(name,"JetpT_%s_EtaBin%i_JER_dn",JetRad[jk],kl+1);
	hist_reco[jk][kl] = (TH1D*)file1->Get(name); 
	
        sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
	hist_gen[jk][kl] = (TH1D*)file1->Get(name); 
	
	}
if(ij==2) {
	sprintf(name,"RecoJetvsGenJet_%s_EtaBin%i",JetRad[jk],kl+1);
//	sprintf(name,"Response_Matrix_%s_EtaBin%i",JetRad[jk],kl+1);
//	sprintf(name,"RecoJetvsGenJet_Algo%i_EtabBin%i",jk+1,kl+1);
	mat_rm[jk][kl] = (TH2D*)file1->Get(name); 
        mat_rm_b[jk][kl] = (TH2D*)mat_rm[jk][kl]->Clone();
 /* 
	mat_measured[jk][kl].ResizeTo(hist_mat_measured[jk][kl]->GetNbinsX(),hist_mat_measured[jk][kl]->GetNbinsY());
	for(int ix=0; ix<(hist_mat_measured[jk][kl]->GetNbinsX()); ix++){
	  for(int iy=0; iy<(hist_mat_measured[jk][kl]->GetNbinsY()); iy++){
		    if(ix==iy){
		    		mat_measured[jk][kl][ix][iy]=hist_mat_measured[jk][kl]->GetBinContent(ix+1,iy+1);
			}else{
				mat_measured[jk][kl][ix][iy]=hist_mat_measured[jk][kl]->GetBinContent(ix+1,iy+1);
			     }
		  }
		}
*/
	}
   }//kl
  }//jk
}//ij


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
    
    double fakerate[100] = {0.};
    double eff[100] ;
    for(int jj=0; jj<100; jj++){
     eff[jj] = 1.;
    }
   double purity[100] = {0.};
   double stbl[100] = {0.};

   if(ij==3&&jk==0){
   for(int bn=0; bn<(hist_reco[ij][jk]->GetNbinsX()); bn++){
     }
   }

    lastbin[ij][jk] = LastBin_Counter(hist_data[ij][jk]);

    hist_data2[ij][jk] = (TH1D*)hist_data[ij][jk]->Clone();
    hist_reco2[ij][jk] = (TH1D*)hist_reco[ij][jk]->Clone();
    hist_gen2[ij][jk] = (TH1D*)hist_gen[ij][jk]->Clone();

    subtract_background(mat_rm_b[ij][jk],hist_reco[ij][jk],hist_gen[ij][jk],hist_data[ij][jk],fakerate,eff,purity,stbl) ;

    if(ij==3&&jk==0){
	for(int bn=0; bn<(hist_gen[ij][jk]->GetNbinsX()); bn++){
                double row_sum = 0;
                double col_sum = 0;
	  for(int am=0; am<(hist_gen[ij][jk]->GetNbinsX()); am++){
		row_sum+= mat_rm[ij][jk]->GetBinContent(bn,am);
		col_sum+= mat_rm[ij][jk]->GetBinContent(am,bn);
		}
	 	
	}
    }
  
 for(int bn=0; bn<(hist_gen[ij][jk]->GetNbinsX()); bn++){
 	 hist_eff[ij][jk]->SetBinContent(bn+1,eff[bn]);
  	 hist_fake[ij][jk]->SetBinContent(bn+1,fakerate[bn]) ;
	 hist_purity[ij][jk]->SetBinContent(bn+1,purity[bn]);
	 hist_stbl[ij][jk]->SetBinContent(bn+1,stbl[bn]);
 }

 hist_eff[ij][jk]->SetMinimum(-0.01); hist_eff[ij][jk]->SetMaximum(1.01);
 hist_fake[ij][jk]->SetMinimum(-0.01); hist_fake[ij][jk]->SetMaximum(1.01);
 hist_purity[ij][jk]->SetMinimum(-0.01); hist_purity[ij][jk]->SetMaximum(1.01);
 hist_stbl[ij][jk]->SetMinimum(-0.01); hist_stbl[ij][jk]->SetMaximum(1.01);

/*
if(hist_gen[ij][jk]->Integral()!=0) { hist_gen[ij][jk]->Scale(1./hist_gen[ij][jk]->Integral()); }//GetEntries());
if(hist_reco[ij][jk]->Integral()!=0) { hist_reco[ij][jk]->Scale(1./hist_reco[ij][jk]->Integral()); }//GetEntries());
if(mat_rm_b[ij][jk]->Integral()!=0)  { mat_rm_b[ij][jk]->Scale(1./mat_rm_b[ij][jk]->Integral()); }
*/

RooUnfoldResponse response_b;
sprintf(name,"unfold_%s_Etabin%i",JetRad[ij],jk+1);
response_b = RooUnfoldResponse(hist_reco[ij][jk],hist_gen[ij][jk], mat_rm_b[ij][jk], name, name);

TH1D *hist_input;

#ifdef Data
hist_input = (TH1D*)hist_data[ij][jk]->Clone();
#elif defined (MC)
hist_input = (TH1D*)hist_reco[ij][jk]->Clone();
#endif

int iter = (jk<5)?bayes_par[0][ij]:bayes_par[1][ij];
RooUnfoldBayes unfoldBayes(&response_b,hist_input,iter,false);
//unfoldBayes.SetMeasuredCov(mat_measured[ij][jk]);

RooUnfoldSvd unfoldSvd(&response_b,hist_input,svd_par[ij]);

RooUnfoldBinByBin unfoldBbB(&response_b,hist_input);


covmatrix_bayes[ij][jk].ResizeTo(mat_rm_b[ij][jk]->GetNbinsX(),mat_rm_b[ij][jk]->GetNbinsY());
covmatrix_bayes[ij][jk] = unfoldBayes.Ereco(RooUnfold::kCovariance);
covmatrix_svd[ij][jk].ResizeTo(mat_rm_b[ij][jk]->GetNbinsX(),mat_rm_b[ij][jk]->GetNbinsY());
covmatrix_svd[ij][jk] = unfoldSvd.Ereco(RooUnfold::kCovariance);
covmatrix_BbB[ij][jk].ResizeTo(mat_rm_b[ij][jk]->GetNbinsX(),mat_rm_b[ij][jk]->GetNbinsY());
covmatrix_BbB[ij][jk] = unfoldBbB.Ereco(RooUnfold::kCovariance);

//cout<<hist_input->GetName()<<" Chisquare "<<unfoldBayes.Chi2(hist_gen[ij][jk],RooUnfold::kCovariance)<<endl;

fileout->cd();

hist_bayes[ij][jk] = (TH1D*) unfoldBayes.Hreco(RooUnfold::kCovariance)->Clone();	
sprintf(name,"bayes_%s",hist_bayes[ij][jk]->GetName());
hist_bayes[ij][jk]->SetName(name);
for(int bn=0; bn<(hist_bayes[ij][jk]->GetNbinsX()); bn++){
//eff[bn] = 1.;
hist_bayes[ij][jk]->SetBinContent(bn+1,(hist_bayes[ij][jk]->GetBinContent(bn+1))*1./eff[bn]);
hist_bayes[ij][jk]->SetBinError(bn+1,(hist_bayes[ij][jk]->GetBinError(bn+1))*1./eff[bn]);
}

hist_svd[ij][jk]  =  (TH1D*) unfoldSvd.Hreco(RooUnfold::kCovariance)->Clone();
sprintf(name,"svd_%s",hist_svd[ij][jk]->GetName());
hist_svd[ij][jk]->SetName(name);
for(int bn=0; bn<(hist_svd[ij][jk]->GetNbinsX()); bn++){
//eff[bn] = 1.;
hist_svd[ij][jk]->SetBinContent(bn+1,(hist_svd[ij][jk]->GetBinContent(bn+1))*1./eff[bn]);
hist_svd[ij][jk]->SetBinError(bn+1,(hist_svd[ij][jk]->GetBinError(bn+1))*1./eff[bn]);
}

hist_BbB[ij][jk]  =  (TH1D*) unfoldBbB.Hreco(RooUnfold::kCovariance)->Clone();
sprintf(name,"BbB_%s",hist_BbB[ij][jk]->GetName());
hist_BbB[ij][jk]->SetName(name);
for(int bn=0; bn<(hist_BbB[ij][jk]->GetNbinsX()); bn++){
hist_BbB[ij][jk]->SetBinContent(bn+1,(hist_BbB[ij][jk]->GetBinContent(bn+1))*1./eff[bn]);
hist_BbB[ij][jk]->SetBinError(bn+1,(hist_BbB[ij][jk]->GetBinError(bn+1))*1./eff[bn]);
}

if((ij==3)&&(jk==0)){
integral_ratio = hist_bayes[ij][jk]->Integral()*1./hist_input->Integral();
}
/*
Fold(mat_rm_b[ij][jk],hist_gen[ij][jk],hist_bayes[ij][jk],hist_bayes_back[ij][jk]);
Fold(mat_rm_b[ij][jk],hist_gen[ij][jk],hist_svd[ij][jk],hist_svd_back[ij][jk]);
Fold(mat_rm_b[ij][jk],hist_gen[ij][jk],hist_BbB[ij][jk],hist_BbB_back[ij][jk]);
*/
/*
ReFold(mat_rm_b[ij][jk],hist_gen[ij][jk],hist_bayes[ij][jk],hist_bayes_back[ij][jk]);
ReFold(mat_rm_b[ij][jk],hist_gen[ij][jk],hist_svd[ij][jk],hist_svd_back[ij][jk]);
ReFold(mat_rm_b[ij][jk],hist_gen[ij][jk],hist_BbB[ij][jk],hist_BbB_back[ij][jk]);
*/
BackFold_Bayesian(response_b,unfoldBayes,hist_bayes_back[ij][jk],eff,fakerate);
BackFold_Svd(response_b,unfoldSvd,hist_svd_back[ij][jk],eff,fakerate);
BackFold_BinbyBin(response_b,unfoldBbB,hist_BbB_back[ij][jk],eff,fakerate);

//Fold(mat_rm_b[ij][jk],hist_gen[ij][jk],hist_gen[ij][jk],hist_gen_fold[ij][jk]);
BackFold_Gen(response_b,hist_gen[ij][jk],hist_gen_fold[ij][jk],eff,fakerate);
hist_gen_fold[ij][jk]->Divide(hist_reco2[ij][jk]) ;


#ifdef Data
hist_bayes_back[ij][jk]->Divide(hist_data2[ij][jk]);
hist_svd_back[ij][jk]->Divide(hist_data2[ij][jk]);
hist_BbB_back[ij][jk]->Divide(hist_data2[ij][jk]);
/*
hist_bayes[ij][jk]->Divide(hist_data2[ij][jk]);
hist_svd[ij][jk]->Divide(hist_data2[ij][jk]);
hist_BbB[ij][jk]->Divide(hist_data2[ij][jk]);
*/
/*
hist_svd[ij][jk]->Divide(hist_bayes[ij][jk]);
hist_BbB[ij][jk]->Divide(hist_bayes[ij][jk]);
*/
TMatrixD RM_mat = response_b.Mresponse();
RM_mat.ResizeTo(lastbin[ij][jk],lastbin[ij][jk]);

TVectorD data_bayes_diff;
data_bayes_diff.ResizeTo(lastbin[ij][jk]);

TVectorD data_svd_diff;
data_svd_diff.ResizeTo(lastbin[ij][jk]);

for(int bn=0; bn<lastbin[ij][jk]; bn++){
if(hist_data[ij][jk]->GetBinContent(bn+1)>1.e-7){
data_bayes_diff[bn] = (hist_bayes_back[ij][jk]->GetBinContent(bn+1)-1.)*hist_data2[ij][jk]->GetBinContent(bn+1) ;
data_svd_diff[bn] = (hist_svd_back[ij][jk]->GetBinContent(bn+1)-1.)*hist_data2[ij][jk]->GetBinContent(bn+1) ;
 }
else{
  data_bayes_diff[bn] = 0;
  data_svd_diff[bn] = 0.;
 }
}

TMatrixD data_errmat;
data_errmat.ResizeTo(lastbin[ij][jk],lastbin[ij][jk]);
for(int am=0; am<lastbin[ij][jk]; am++){
 for(int bn=0; bn<lastbin[ij][jk]; bn++){
  if(am==bn){
  data_errmat[am][bn] = pow(hist_data2[ij][jk]->GetBinError(am+1),2.);
	}
 else { data_errmat[am][bn] = 0;  }
 }
}

TMatrixD err_mat ;
err_mat.ResizeTo(lastbin[ij][jk],lastbin[ij][jk]);

for(int am=0; am<lastbin[ij][jk]; am++){
 for(int bn=0; bn<lastbin[ij][jk]; bn++){
  err_mat[am][bn] = covmatrix_bayes[ij][jk](am,bn) ;
 }
}

TMatrixD pseudo_err_mat;
TMatrixD pseudo_err_mat_2;
pseudo_err_mat.ResizeTo(lastbin[ij][jk],lastbin[ij][jk]);
pseudo_err_mat_2.ResizeTo(lastbin[ij][jk],lastbin[ij][jk]);

for(int am=0; am<lastbin[ij][jk]; am++){
 for(int bn=0; bn<lastbin[ij][jk]; bn++){
  pseudo_err_mat_2(am,bn) = RM_mat(bn,am);
  }
}

pseudo_err_mat =  err_mat * RM_mat;
err_mat = pseudo_err_mat_2 * pseudo_err_mat;

for(int am=0; am<lastbin[ij][jk]; am++){
 for(int bn=0; bn<lastbin[ij][jk]; bn++){
   err_mat(am,bn) = err_mat(am,bn)+data_errmat(am,bn);
 }
}

err_mat.Invert();

TVectorD diff_vec;
diff_vec.ResizeTo(lastbin[ij][jk]);
diff_vec = err_mat* data_bayes_diff;

for(int bn=0; bn<lastbin[ij][jk]; bn++){
chisq_bayes[ij][jk]+=data_bayes_diff[bn]*diff_vec[bn] ;
}
cout<<hist_data[ij][jk]->GetName()<<'\t'<<"Bayesian ChiSq/ndf  "<<chisq_bayes[ij][jk]*1./lastbin[ij][jk]<<endl;

//////////SVD Chi^2///////////
for(int am=0; am<lastbin[ij][jk]; am++){
 for(int bn=0; bn<lastbin[ij][jk]; bn++){
  err_mat[am][bn] = covmatrix_svd[ij][jk][am][bn] + data_errmat[am][bn] ;
 }
}

err_mat.Invert();

diff_vec = err_mat* data_svd_diff;

for(int bn=0; bn<lastbin[ij][jk]; bn++){
chisq_svd[ij][jk]+=data_svd_diff[bn]*diff_vec[bn] ;
}
cout<<hist_data[ij][jk]->GetName()<<'\t'<<"SVD ChiSq/ndf  "<<chisq_svd[ij][jk]*1./lastbin[ij][jk]<<endl;


//diff_vec = err_mat* data_svd_diff;
/*
for(int bn=0; bn<hist_data[ij][jk]->GetNbinsX(); bn++){
chisq_svd[ij][jk]+=data_svd_diff[bn]*diff_vec[bn] ;
}
*/
//cout<<hist_data[ij][jk]->GetName()<<'\t'<<"Bayesian ChiSq  "<<chisq_bayes[ij][jk]<<'\t'<<"SVD Chisq "<<chisq_svd[ij][jk]<<endl;

for(int bn=0; bn<noptbins; bn++){

double rel_error_data = ( hist_data[ij][jk]->GetBinContent(bn+1) > 1.e-7) ? hist_data[ij][jk]->GetBinError(bn+1) *1./ hist_data[ij][jk]->GetBinContent(bn+1): 1.e-7 ;
double rel_error_bayes =( hist_bayes[ij][jk]->GetBinContent(bn+1)>1.e-7 ) ? hist_bayes[ij][jk]->GetBinError(bn+1)* 1./hist_bayes[ij][jk]->GetBinContent(bn+1) : 1.e-7 ;
double rel_error_svd = (hist_svd[ij][jk]->GetBinContent(bn+1)>1.e-7) ? hist_svd[ij][jk]->GetBinError(bn+1)* 1./hist_svd[ij][jk]->GetBinContent(bn+1) : 1.e-7 ;
double rel_error_BbB = (hist_BbB[ij][jk]->GetBinContent(bn+1)>1.e-7) ? hist_BbB[ij][jk]->GetBinError(bn+1)*1./hist_BbB[ij][jk]->GetBinContent(bn+1) : 1.e-7 ;

if( rel_error_data > 1.e-7){

hist_bayes_error[ij][jk]->SetBinContent(bn+1,rel_error_bayes*1./rel_error_data);
hist_bayes_error[ij][jk]->SetBinError(bn+1,0.);

hist_svd_error[ij][jk]->SetBinContent(bn+1,rel_error_svd*1./rel_error_data);
hist_svd_error[ij][jk]->SetBinError(bn+1,0.);

hist_BbB_error[ij][jk]->SetBinContent(bn+1,rel_error_BbB*1./rel_error_data);
hist_BbB_error[ij][jk]->SetBinError(bn+1,0.);
 }
}//bn

#elif defined (MC)

hist_bayes_back[ij][jk]->Divide(hist_reco2[ij][jk]);
hist_svd_back[ij][jk]->Divide(hist_reco2[ij][jk]);
hist_BbB_back[ij][jk]->Divide(hist_reco2[ij][jk]);
/*
hist_bayes[ij][jk]->Divide(hist_reco2[ij][jk]);
hist_svd[ij][jk]->Divide(hist_reco2[ij][jk]);
hist_BbB[ij][jk]->Divide(hist_reco2[ij][jk]);
*/
/*
hist_svd[ij][jk]->Divide(hist_bayes[ij][jk]);
hist_BbB[ij][jk]->Divide(hist_bayes[ij][jk]);
*/
for(int bn=0; bn<noptbins; bn++){
if (hist_reco[ij][jk]->GetBinError(bn+1) > 1.e-7){
hist_bayes_error[ij][jk]->SetBinContent(bn+1,hist_bayes[ij][jk]->GetBinError(bn+1)*1./hist_reco[ij][jk]->GetBinError(bn+1));
hist_bayes_error[ij][jk]->SetBinError(bn+1,0.);

hist_svd_error[ij][jk]->SetBinContent(bn+1,hist_svd[ij][jk]->GetBinError(bn+1)*1./hist_reco[ij][jk]->GetBinError(bn+1));
hist_svd_error[ij][jk]->SetBinError(bn+1,0.);

hist_BbB_error[ij][jk]->SetBinContent(bn+1,hist_BbB[ij][jk]->GetBinError(bn+1)*1./hist_reco[ij][jk]->GetBinError(bn+1));
hist_BbB_error[ij][jk]->SetBinError(bn+1,0.);
 }
}//bn


#endif
 }
}



for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  cout<<"mean "<<JetRad[ij]<<" etabin"<<jk+1<<" data "<<hist_data[ij][jk]->GetMean()<<" gen "<<hist_gen[ij][jk]->GetMean()<<" bayes "<<hist_bayes[ij][jk]->GetMean()<<" svd "<<hist_svd[ij][jk]->GetMean()<<" BbB "<<hist_BbB[ij][jk]->GetMean()<<endl;
 cout<<"std dev "<<JetRad[ij]<<" etabin"<<jk+1<<" data "<<hist_data[ij][jk]->GetStdDev()<<" gen "<<hist_gen[ij][jk]->GetStdDev()<<" bayes "<<hist_bayes[ij][jk]->GetStdDev()<<" svd "<<hist_svd[ij][jk]->GetStdDev()<<" BbB "<<hist_BbB[ij][jk]->GetStdDev()<<endl;
 }
}


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

  for(int ix=0; ix<covmatrix_bayes[ij][jk].GetNcols(); ix++){
	for(int iy=0; iy<covmatrix_bayes[ij][jk].GetNcols(); iy++){

               if(log(covmatrix_bayes[ij][jk](ix,iy))>0){

		COV_Mat_bayes[ij][jk]->Fill(ix+0.5,iy+0.5,log10(covmatrix_bayes[ij][jk](ix,iy)+1));
		}
		else{
		COV_Mat_bayes[ij][jk]->Fill(ix+0.5,iy+0.5,-log10(-covmatrix_bayes[ij][jk](ix,iy)+1));
		}		

		}	
	}

 for(int ix=0; ix<covmatrix_svd[ij][jk].GetNcols(); ix++){
        for(int iy=0; iy<covmatrix_svd[ij][jk].GetNcols(); iy++){

               if(log(covmatrix_svd[ij][jk](ix,iy))>0){

                COV_Mat_svd[ij][jk]->Fill(ix+0.5,iy+0.5,log10(covmatrix_svd[ij][jk](ix,iy)+1));
                }
                else{
                COV_Mat_svd[ij][jk]->Fill(ix+0.5,iy+0.5,-log10(-covmatrix_svd[ij][jk](ix,iy)+1));
                }

        }
     }

  for(int ix=0; ix<covmatrix_BbB[ij][jk].GetNcols(); ix++){
        for(int iy=0; iy<covmatrix_BbB[ij][jk].GetNcols(); iy++){

               if(log(covmatrix_BbB[ij][jk](ix,iy))>0){

                COV_Mat_BbB[ij][jk]->Fill(ix+0.5,iy+0.5,log10(covmatrix_BbB[ij][jk](ix,iy)+1));
                }
                else{
                COV_Mat_BbB[ij][jk]->Fill(ix+0.5,iy+0.5,-log10(-covmatrix_BbB[ij][jk](ix,iy)+1));
                }

        }
     }


  }
}


fileout->cd();
fileout->Write();
fileout->Close();

cout<<"integral ratio "<<integral_ratio<<endl;

TCanvas *c1 = new TCanvas("ak4_eta1","ak4_eta1",600,600);
c1->cd();
gPad->SetLogz(1);
covmatrix_bayes[3][0].Draw("colz");
c1->SaveAs("ak4_eta1.eps");

cout<<"done .. end!"<<endl;
}

