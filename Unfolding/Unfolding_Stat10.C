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

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int noptbins1 = 31;
double ptbins1[noptbins1+1] = {/*30,43,56,*/74,97,133,174,220,272,330,395,468,548,638,737,846,967,1101,1248,1410,1588,1784,2000,2238,2500,2787,3103,3450,3832,4252,4713,5220,5777,6389,7000};

const int nalgo = 12;
const char* JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const int ncomb = 10;

/*
const int nalgo = 1;
const char* JetRad[nalgo] = {"ak4"};
*/
//const int bayes_par[nalgo] = {7,6,6,7,7,7,7,8,8,9,9,9};

//const int bayes_par[2][nalgo] = {{7,7,7,7,7,7,8,8,8,9,12,12},{13,11,11,11,12,12,13,13,14,15,16,16}}; //nocor
const int bayes_par[2][nalgo] = {{10,8,9,9,10,10,9,9,10,12,13,14},{13,11,11,11,12,12,13,13,14,15,16,16}}; //nocor
const int svd_par[nalgo]= {7,7,7,7,7,9,9,9,9,9,9,9};
/*
const int bayes_par[2][nalgo]={{9},{11}};
const int svd_par[nalgo]= {7};
*/
float data_lumi = 34.67;//33.64;//32.1;//32.882;
     
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
if(totalreco[ix+1]>1.e-6) {     fakerate[ix] /= totalreco[ix+1]; }
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
fileout = new TFile("Unfolded2016_DataStat10.root","recreate") ;

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_nocor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root"};
//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root"};
//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root"};
//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root"};

//const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15.root"};
const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_stat_tot.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15_new_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15_new_excor.root"};
//"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_P8_RM10_Combo.root",
//"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_P8_RM10_Combo.root"};

char name[100];

/*const int nalgo = 1;
const char* JetRad[nalgo] = {"ak4"};
*/
const int Etabins = 10;

TH1D *hist_data[nalgo][Etabins][ncomb];
TH1D *hist_data2[nalgo][Etabins][ncomb];
TH1D *hist_reco[nalgo][Etabins][ncomb];
TH1D *hist_reco2[nalgo][Etabins][ncomb];
TH1D *hist_gen[nalgo][Etabins][ncomb];
TH1D *hist_gen2[nalgo][Etabins][ncomb];
TH2D *mat_rm[nalgo][Etabins][ncomb];
TH2D *mat_rm_b[nalgo][Etabins][ncomb];
TH1D *hist_bayes[nalgo][Etabins][ncomb] = {{{0}}};
TH1D *hist_svd[nalgo][Etabins][ncomb] = {{{0}}};
TH1D *hist_BbB[nalgo][Etabins][ncomb] = {{{0}}};

int lastbin[nalgo][Etabins][ncomb] = {{{0}}};

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
   for(int kl=0; kl<ncomb; kl++){	 
  
  sprintf(name,"Bayes_%s_EtaBin%i_Comb%i",JetRad[ij],jk+1,kl+1);
  hist_bayes[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins) ;
 
  sprintf(name,"SVD_%s_EtaBin%i_Comb%i",JetRad[ij],jk+1,kl+1);
  hist_svd[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins) ;

  sprintf(name,"BinbyBin_%s_EtaBin%i_Comb%i",JetRad[ij],jk+1,kl+1);
  hist_BbB[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins) ;
   
   }
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
	for(int lm=0; lm<ncomb; lm++){  

if(ij==0) {
//	sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
	sprintf(name,"JetpT_%s_EtaBin%i_Comb%i",JetRad[jk],kl+1,lm+1);
	hist_data[jk][kl][lm] = (TH1D*)file1->Get(name);
	hist_data[jk][kl][lm]->Scale(ncomb*1./data_lumi);
	cout<<hist_data[jk][kl][lm]->GetName()<<" mean "<<hist_data[jk][kl][lm]->GetMean()<<endl;
	}
if(ij==1) {
	sprintf(name,"JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
	hist_reco[jk][kl][lm] = (TH1D*)file1->Get(name); 
	
        sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
	hist_gen[jk][kl][lm] = (TH1D*)file1->Get(name); 
        cout<<"GEN "<<hist_gen[jk][kl][lm]->GetName()<<" mean "<<hist_gen[jk][kl][lm]->GetMean()<<endl;	
	}
if(ij==2) {
	sprintf(name,"RecoJetvsGenJet_%s_EtaBin%i",JetRad[jk],kl+1);
//	sprintf(name,"Response_Matrix_%s_EtaBin%i",JetRad[jk],kl+1);
//	sprintf(name,"RecoJetvsGenJet_Algo%i_EtabBin%i",jk+1,kl+1);

	mat_rm_b[jk][kl][lm] = (TH2D*)file1->Get(name);
	mat_rm[jk][kl][lm] = (TH2D*)mat_rm_b[jk][kl][lm]->Clone();
    mat_rm[jk][kl][lm]->Rebin2D(1,2);
	}
   }//kl
  }//jk
}//ij

}
for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  for(int lm=0; lm<ncomb; lm++){ 
    
    double fakerate[100] = {0.};
    double eff[100] ;
    for(int jj=0; jj<100; jj++){
     eff[jj] = 1.;
    }
   double purity[100] = {0.};
   double stbl[100] = {0.};
    
    lastbin[ij][jk][lm] = LastBin_Counter(hist_data[ij][jk][lm]);

    hist_data2[ij][jk][lm] = (TH1D*)hist_data[ij][jk][lm]->Clone();
    hist_reco2[ij][jk][lm] = (TH1D*)hist_reco[ij][jk][lm]->Clone();
    hist_gen2[ij][jk][lm] = (TH1D*)hist_gen[ij][jk][lm]->Clone();

//    subtract_background(mat_rm_b[ij][jk][lm],hist_reco[ij][jk][lm],hist_gen[ij][jk][lm],hist_data[ij][jk][lm],fakerate,eff,purity,stbl) ;


RooUnfoldResponse response_b;
sprintf(name,"unfold_%s_Etabin%i",JetRad[ij],jk+1);
response_b = RooUnfoldResponse(hist_reco[ij][jk][lm],hist_gen[ij][jk][lm], mat_rm_b[ij][jk][lm], name, name);

TUnfold unfoldtuf(mat_rm[ij][jk][lm],TUnfold::kHistMapOutputVert/*,TUnfold::kRegModeCurvature,TUnfold::kEConstraintNone*/);
TUnfold::ERegMode regMode=TUnfold::kRegModeSize;

TH1D *hist_input;

#ifdef Data
hist_input = (TH1D*)hist_data[ij][jk][lm]->Clone();
#elif defined (MC)
hist_input = (TH1D*)hist_reco[ij][jk][lm]->Clone();
#endif

int iter = (jk<5)?bayes_par[0][ij]:bayes_par[1][ij];
RooUnfoldBayes unfoldBayes(&response_b,hist_input,iter,false);

RooUnfoldSvd unfoldSvd(&response_b,hist_input,svd_par[ij]);

RooUnfoldBinByBin unfoldBbB(&response_b,hist_input);

//cout<<hist_input->GetName()<<" Chisquare "<<unfoldBayes.Chi2(hist_gen[ij][jk],RooUnfold::kCovariance)<<endl;

fileout->cd();

sprintf(name,"bayes_%s",hist_bayes[ij][jk][lm]->GetName());
hist_bayes[ij][jk][lm] = (TH1D*) unfoldBayes.Hreco(RooUnfold::kCovariance)->Clone();	
//sprintf(name,"bayes_%s",hist_bayes[ij][jk][lm]->GetName());
hist_bayes[ij][jk][lm]->SetName(name);
for(int bn=0; bn<(hist_bayes[ij][jk][lm]->GetNbinsX()); bn++){
//eff[bn] = 1.;
hist_bayes[ij][jk][lm]->SetBinContent(bn+1,(hist_bayes[ij][jk][lm]->GetBinContent(bn+1))*1./eff[bn]);
hist_bayes[ij][jk][lm]->SetBinError(bn+1,(hist_bayes[ij][jk][lm]->GetBinError(bn+1))*1./eff[bn]);
}

sprintf(name,"svd_%s",hist_svd[ij][jk][lm]->GetName());
hist_svd[ij][jk][lm]  =  (TH1D*) unfoldSvd.Hreco(RooUnfold::kCovariance)->Clone();
//sprintf(name,"svd_%s",hist_svd[ij][jk][lm]->GetName());
hist_svd[ij][jk][lm]->SetName(name);
for(int bn=0; bn<(hist_svd[ij][jk][lm]->GetNbinsX()); bn++){
//eff[bn] = 1.;
hist_svd[ij][jk][lm]->SetBinContent(bn+1,(hist_svd[ij][jk][lm]->GetBinContent(bn+1))*1./eff[bn]);
hist_svd[ij][jk][lm]->SetBinError(bn+1,(hist_svd[ij][jk][lm]->GetBinError(bn+1))*1./eff[bn]);
}

sprintf(name,"BbB_%s",hist_BbB[ij][jk][lm]->GetName());
hist_BbB[ij][jk][lm]  =  (TH1D*) unfoldBbB.Hreco(RooUnfold::kCovariance)->Clone();
//sprintf(name,"BbB_%s",hist_BbB[ij][jk][lm]->GetName());
hist_BbB[ij][jk][lm]->SetName(name);
for(int bn=0; bn<(hist_BbB[ij][jk][lm]->GetNbinsX()); bn++){
hist_BbB[ij][jk][lm]->SetBinContent(bn+1,(hist_BbB[ij][jk][lm]->GetBinContent(bn+1))*1./eff[bn]);
hist_BbB[ij][jk][lm]->SetBinError(bn+1,(hist_BbB[ij][jk][lm]->GetBinError(bn+1))*1./eff[bn]);
}

  }
 }
}


fileout->cd();
fileout->Write();
fileout->Close();

cout<<"integral ratio "<<integral_ratio<<endl;
cout<<"done .. end!"<<endl;
}

