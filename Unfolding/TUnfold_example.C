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

#include "TLegend.h"

#include "TUnfold.h"

using namespace std;
using namespace CLHEP;

const int noptbins1 = 31;
double ptbins1[noptbins1+1] = {74,97,133,174,220,272,330,395,468,548,638,737,846,967,1101,1248,1410,1588,1784,2000,2238,2500,2787,3103,3450,3832,4252,4713,5220,5777,6389,7000};


const int noptbins = 62;
double ptbins[noptbins+1] = {74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

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

//int main()       
void TUnfold_example()                        
{
const char* rootfiles[3] = {"/home/suman/RooUnfold/Example_Data_MG.root","/home/suman/RooUnfold/P8_RECOGEN.root","/home/suman/RooUnfold/P8_RECOGEN.root"};

char name[100];

TH1D *hist_data;
TH1D *hist_reco;
TH1D *hist_gen;
TH1D *hist_truth;
TH2D *mat_rm;

int lastbin = 0;

for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();

if(ij==0) {
        sprintf(name,"JetpT_ak4_EtaBin1");
        hist_data = (TH1D*)file1->Get(name);
/*
	sprintf(name,"Gen_MC_JetpT_ak4_EtaBin1");
	hist_truth = (TH1D*)file1->Get(name);
	cout<<hist_truth->GetMean()<<endl;
*/
        }
if(ij==1) {
        sprintf(name,"JetpT_ak4_EtaBin1");
        hist_reco = (TH1D*)file1->Get(name);

        sprintf(name,"Gen_MC_JetpT_ak4_EtaBin1");
        hist_gen = (TH1D*)file1->Get(name);
        }
if(ij==2) {
        sprintf(name,"RecoJetvsGenJet_ak4_EtaBin1");
        mat_rm = (TH2D*)file1->Get(name);
	for(int bn=0; bn<mat_rm->GetNbinsX(); bn++){
	mat_rm->SetBinContent(bn+1,0,0);
	}
	mat_rm->Rebin2D(1,2);
        }
 }//ij

   TFile *fileout ;
   fileout = new TFile("TUnfold_example.root","recreate") ;
   TH1D *hist_unf;
   sprintf(name,"TUnfold_ak4_EtaBin1");
   hist_unf = new TH1D(name,name,noptbins1,ptbins1);

//   hist_unf = (TH1D*)hist_data->Clone();

   lastbin = LastBin_Counter(hist_data);

//   TUnfold unfoldBbB(mat_rm,TUnfold::kHistMapOutputVert,TUnfold::kRegModeCurvature,TUnfold::kEConstraintNone);
   TUnfold unfoldBbB(mat_rm,TUnfold::kHistMapOutputVert);

   TUnfold::ERegMode regMode=TUnfold::kRegModeCurvature;
//   TUnfold::ERegMode regMode=TUnfold::kRegModeSize;
   unfoldBbB.SetInput(hist_data);
   unfoldBbB.RegularizeBins(1,1,2,regMode);  

  Double_t tauMin=-3.0;
  Double_t tauMax=3.0;
  Int_t nScan=30;
  Int_t iBest;
  TSpline *logTauX,*logTauY;
  TGraph *lCurve;

  unfoldBbB.ScanLcurve(nScan,tauMin,tauMax,&lCurve,&logTauX,&logTauY);
  std::cout<<"chi**2="<<unfoldBbB.GetChi2A()<<"+"<<unfoldBbB.GetChi2L()<<" / "<<unfoldBbB.GetNdf()<<"\n";

//  unfoldBbB.DoUnfold(0) ;

  Int_t *binMap=new Int_t[noptbins+2];
  for(Int_t i=1;i<=noptbins;i++) binMap[i]=i;
  binMap[0]=-1;
  binMap[noptbins+1]=-1;

  unfoldBbB.GetOutput(hist_unf,binMap);  

  hist_data->SetLineColor(kBlack);
  hist_reco->SetLineColor(kBlue);
  hist_gen->SetLineColor(kRed);
  hist_unf->SetLineColor(kMagenta);
//  hist_truth->SetLineColor(7);

  hist_data->SetStats(0); hist_data->SetMinimum(1.);
  hist_reco->SetStats(0);
  hist_gen->SetStats(0);
  hist_unf->SetStats(0);

  for(int bn=0; bn<(hist_data->GetNbinsX()); bn++){
  hist_data->SetBinContent(bn+1,hist_data->GetBinContent(bn+1)*1./hist_data->GetBinWidth(bn+1));
  hist_reco->SetBinContent(bn+1,hist_reco->GetBinContent(bn+1)*1./hist_reco->GetBinWidth(bn+1));
  hist_gen->SetBinContent(bn+1,hist_gen->GetBinContent(bn+1)*1./hist_gen->GetBinWidth(bn+1));
//  hist_truth->SetBinContent(bn+1,hist_truth->GetBinContent(bn+1)*1./hist_gen->GetBinWidth(bn+1));
  }

  for(int bn=0; bn<(hist_unf->GetNbinsX()); bn++){
  hist_unf->SetBinContent(bn+1,hist_unf->GetBinContent(bn+1)*1./hist_unf->GetBinWidth(bn+1));
  }

  TCanvas *c1 = new TCanvas("Tunfold_output","Tunfold_output",800,600);
  TLegend *leg1 = new TLegend(0.7,0.7,0.85,0.85);
  leg1->SetBorderSize(0);
  c1->cd(1);
  
  gPad->SetLogx(1);
  gPad->SetLogy(1);

  hist_data->Draw("e"); leg1->AddEntry(hist_data,"DATA","l");
  hist_gen->Draw("sames");  leg1->AddEntry(hist_gen,"GEN","l");
  hist_unf->Draw("sames"); leg1->AddEntry(hist_unf,"Unfolded","l");
//  hist_truth->Draw("sames"); leg1->AddEntry(hist_truth,"Unfolded","l");
  leg1->Draw();

//  TH1D *hist_gen_rat = (TH1D*)hist_gen->Clone(); hist_gen_rat->Divide(hist_data);
  
  sprintf(name,"%s.eps",c1->GetName());
  c1->SaveAs(name);

 fileout->cd();
 fileout->Write();
 fileout->Close();
}
