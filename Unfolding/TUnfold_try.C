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


const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};


int getbinid(double val, int nbmx, double* array) {
  if (val<array[0]) return -1;
  for (int ix=1; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -1;
}

int LastBin_Counter(TH1D *h1){
int lastbin = 0;
for(int bn=0; bn<(h1->GetNbinsX()); bn++){
if((h1->GetBinContent(bn+1)) > 1.e-12){
lastbin = bn+1;
}
else { break;}
}
cout<<h1->GetName()<<" totbins "<<lastbin<<endl;
return lastbin;
}

int main()                                                                                                                                     {
double data_lumi = 27.8;

TFile *fileout ;
fileout = new TFile("TUnfold_Data.root","recreate") ;

const char* rootfiles[3] = {/*"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_JECor.root",*/"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/2016Files/hist_RecoJetchs_PU_Data_JetHT2016BCDEFGH.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Historam_P8_Noswap.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Historam_P8_Noswap.root"};

char name[100];

const int nalgo = 12;
const char* JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const int Etabins = 10;

TH1D *hist_data[nalgo][Etabins];
TH1D *hist_reco[nalgo][Etabins];
TH1D *hist_gen[nalgo][Etabins];
TH2D *mat_rm[nalgo][Etabins];
TH1D *hist_unf[nalgo][Etabins] = {{0}};

for(int jk=0; jk<nalgo; jk++){
  for(int kl=0; kl<Etabins; kl++){
  sprintf(name,"TUnfold_%s_EtaBin%i",JetRad[jk],kl+1);
  hist_unf[jk][kl] = new TH1D(name,name,noptbins,ptbins);
  }
}

int lastbin[nalgo][Etabins] = {{0}};

for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();

for(int jk=0; jk<nalgo; jk++){
  for(int kl=0; kl<Etabins; kl++){

if(ij==0) {
        sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
        hist_data[jk][kl] = (TH1D*)file1->Get(name);
        hist_data[jk][kl]->Scale(1./data_lumi);
//	hist_data[jk][kl]->Rebin(2);
        }
if(ij==1) {
        sprintf(name,"JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
        hist_reco[jk][kl] = (TH1D*)file1->Get(name);
//	hist_reco[jk][kl]->Rebin(2);

        sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[jk],kl+1);
        hist_gen[jk][kl] = (TH1D*)file1->Get(name);
//	hist_gen[jk][kl]->Rebin(2);
        }
if(ij==2) {
        sprintf(name,"RecoJetvsGenJet_%s_EtaBin%i",JetRad[jk],kl+1);
        mat_rm[jk][kl] = (TH2D*)file1->Get(name);
	for(int bn=0; bn<mat_rm[jk][kl]->GetNbinsX(); bn++){
	mat_rm[jk][kl]->SetBinContent(bn+1,0,0);
//	mat_rm[jk][kl]->SetBinContent(bn+1,noptbins+1,0);
	}
	mat_rm[jk][kl]->Rebin2D(2,2);
	if(jk==3&&kl==0){cout<<"Matrx integral "<<mat_rm[jk][kl]->Integral()<<endl;}
        }
    }//kl
   }//jk
 }//ij

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

   if((ij!=3)||(jk!=0)) continue;

//    if((ij<2)&&(jk>5)) continue;

   lastbin[ij][jk] = LastBin_Counter(hist_data[ij][jk]);

   RooUnfoldResponse response_b;
   sprintf(name,"unfold_%s_Etabin%i",JetRad[ij],jk+1);
   response_b = RooUnfoldResponse(hist_reco[ij][jk],hist_gen[ij][jk], mat_rm[ij][jk], name, name);

   TH1D *hist_input;
   hist_input = (TH1D*)hist_data[ij][jk]->Clone();

   TUnfold unfoldBbB(mat_rm[ij][jk],TUnfold::kHistMapOutputVert,TUnfold::kRegModeCurvature,TUnfold::kEConstraintNone);
   unfoldBbB.SetInput(hist_input);

   TUnfold::ERegMode regMode=TUnfold::kRegModeCurvature;

   unfoldBbB.RegularizeBins(1,1,2,regMode);  
   //unfoldBbB.DoUnfold() ;
  Double_t tauMin=-3.0;
  Double_t tauMax=3.0;
  Int_t nScan=30;
  Int_t iBest;
  TSpline *logTauX,*logTauY;
  TGraph *lCurve;

  unfoldBbB.ScanLcurve(nScan,tauMin,tauMax,&lCurve,&logTauX,&logTauY);
  std::cout<<"chi**2="<<unfoldBbB.GetChi2A()<<"+"<<unfoldBbB.GetChi2L()<<" / "<<unfoldBbB.GetNdf()<<"\n";

  Int_t *binMap=new Int_t[noptbins+2];
  for(Int_t i=1;i<=noptbins;i++) binMap[i]=i;
  binMap[0]=-1;
  binMap[noptbins+1]=-1;

   unfoldBbB.GetOutput(hist_unf[ij][jk],binMap);
   cout<<hist_unf[ij][jk]->Integral()<<endl;
   fileout->cd();
//   unfoldBbB.GetOutput(hist_unf[ij][jk]);
  

  }
 }

 fileout->cd();
 fileout->Write();
 fileout->Close();


}
