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
//#include "RooUnfHistoSvd.h"
#include "TLegend.h"

using namespace std;
using namespace CLHEP;
     
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


void Fold(TH2D* HistoMatrix, TH1D* HistoGen, TH1D* HistoUnfold, TH1D* HistoCorrect){

  double probFake=0.;
  double AwayMatrixTot=0.;

  for(int i=1;i<HistoGen->GetXaxis()->GetNbins()+1;i++){

    double Inside=0.;
    double ErrorP=0.;
    for(int j=1;j<HistoGen->GetXaxis()->GetNbins()+1;j++){
      probFake=0;
      AwayMatrixTot=HistoMatrix->GetBinContent(i,j)/HistoGen->GetBinContent(j);
      if(HistoGen->GetBinContent(j)==0) AwayMatrixTot=1;
      Inside=Inside+HistoUnfold->GetBinContent(j)*AwayMatrixTot/(1-probFake);
      ErrorP=ErrorP+HistoUnfold->GetBinError(j)*AwayMatrixTot/(1-probFake)*HistoUnfold->GetBinError(j)*AwayMatrixTot/(1-probFake);
    }

    HistoCorrect->SetBinContent(i,Inside);
    double Error=sqrt(ErrorP);
    //double Error=ErrorP;
    HistoCorrect->SetBinError(i,Error);
  }

}


int main()																																 
{	
const char* rootfiles[3] = {"../CPlusPlus/CMS_Files/Jets_in_CMS/Data_2015D/hist_RecoJetchs_PU_Data_2015D_JetHTCHS_NewPrescale_v2.root","../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root"/*, "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root"*/,"Response_Matrix/Spline_output_ak4.root"}	;

char name[100];

TH1D *hist_data;
TH1D *hist_reco;
TH1D *hist_gen;
TH2D *mat_rm;
TH2D *mat_rm_b;
TH1D *hist_bayes;
TH1D* hist_svd;
TH1D* hist_BbB;

int ialgo = 4;
int ieta = 1;

 cout<<"algo ak"<<ialgo<<" eta"<<ieta<<endl;
 
for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();
if(ij==0) {
	sprintf(name,"mcjets/JetpT_ak%i_EtaBin%i",ialgo,ieta);
	hist_data = (TH1D*)file1->Get(name);
	cout<<"data integral "<<hist_data->GetEntries()<<endl;
//	hist_data->Scale(1./hist_data->Integral());
	}
if(ij==1) {
	sprintf(name,"JetpT_ak%i_EtaBin%i",ialgo,ieta);
	hist_reco = (TH1D*)file1->Get(name); 
	cout<<"MC reco integral "<<hist_reco->GetEntries()<<endl;
	hist_reco->Scale(1./hist_reco->Integral());
	sprintf(name,"Gen_MC_JetpT_ak%i_EtaBin%i",ialgo,ieta);
	hist_gen = (TH1D*)file1->Get(name); 
	
	cout<<"MC gen integral "<<hist_gen->GetEntries()<<endl;
//	hist_gen->Scale(1./hist_gen->Integral());
	}
if(ij==2) {
//	sprintf(name,"RecoJetvsGenJet_Algo%i_EtabBin%i",ialgo-1,ieta+1);
	sprintf(name,"Response_Matrix_ak%i_EtaBin%i",ialgo,ieta);
	mat_rm = (TH2D*)file1->Get(name); 
/*        for(int ij=0; ij<mat_rm->GetNbinsX(); ij++){
         for(int jk=0; jk<mat_rm->GetNbinsX(); jk++){
              if(ij!=jk){ mat_rm->SetBinContent(ij+1,jk+1,0.); mat_rm->SetBinError(ij+1,jk+1,0.);   }
		}
         }
*/
	cout<<"nxbisn "<<mat_rm->GetNbinsX()<<" ybins "<<mat_rm->GetNbinsY()<<endl;
        mat_rm_b = (TH2D*)mat_rm->Clone();
	cout<<"Matrix entries "<<mat_rm_b->GetEntries()<<endl;
//        mat_rm_b->Scale(1./mat_rm_b->Integral());
//	mat_rm->Scale(1./5000);
	}
}

cout<<"matrix integral "<<mat_rm_b->Integral()<<endl;

TH1F *hist_reco2 = (TH1F*)hist_reco->Clone();
TH1F *hist_gen2 = (TH1F*)hist_gen->Clone();

double gen_integral = hist_gen->Integral();
double reco_integral = hist_reco->Integral();

//hist_gen->Scale(2.16);
//`hist_reco->Scale(2.16);

//hist_data->Scale(1./hist_data->Integral());
hist_gen->Scale(1./hist_gen->Integral());//GetEntries());
hist_reco->Scale(1./hist_reco->Integral());//GetEntries());
mat_rm_b->Scale(1./mat_rm_b->Integral());

RooUnfoldResponse response;
sprintf(name,"unfold_ak%i_etabin%i",ialgo,ieta);
response = RooUnfoldResponse(hist_reco2,hist_gen2, mat_rm, name, name);

RooUnfoldResponse response_b;
sprintf(name,"unfold_ak%i_etabin%i_b",ialgo,ieta);
response_b = RooUnfoldResponse(hist_reco,hist_gen, mat_rm_b, name, name);

RooUnfoldBayes unfoldBayes(&response_b,hist_reco,5,false);

RooUnfoldSvd unfoldSvd(&response_b,hist_reco,17);

RooUnfoldBinByBin unfoldBbB(&response_b,hist_reco);

hist_bayes = (TH1D*) unfoldBayes.Hreco(RooUnfold::kCovariance)->Clone();	
hist_svd  =  (TH1D*) unfoldSvd.Hreco(RooUnfold::kCovariance)->Clone();
hist_BbB  =  (TH1D*) unfoldBbB.Hreco(RooUnfold::kCovariance)->Clone();

ofstream fp;
fp.open("Error_list.log");

fp<<"       Bayesian       SVD    BinbyBin "<<endl;

for(int bn=0; bn<hist_data->GetNbinsX(); bn++){
fp<<"bin "<<bn+1<<"  "<<hist_bayes->GetBinError(bn+1)*1./hist_data->GetBinError(bn+1)<<"  "<<hist_svd->GetBinError(bn+1)*1./hist_data->GetBinError(bn+1)<<"  "<<hist_BbB->GetBinError(bn+1)*1./hist_data->GetBinError(bn+1)<<endl;
}

fp.close();

TH1D *hist_bayes_bfold = (TH1D*)hist_bayes->Clone();
TH1D *hist_svd_bfold = (TH1D*)hist_svd->Clone();
TH1D *hist_BbB_bfold = (TH1D*)hist_BbB->Clone();
/*
TMatrixD rm_mat_bfold = response_b.Mresponse();
TVectorD bayes_bfold = response_b.Mresponse() * unfoldBayes.Vreco();
TVectorD svd_bfold = response_b.Mresponse() * unfoldSvd.Vreco();
TVectorD BbB_bfold = response_b.Mresponse() * unfoldBbB.Vreco();

for(int bn=0; bn<hist_bayes_bfold->GetNbinsX(); bn++){
hist_bayes_bfold->SetBinContent(bn+1,bayes_bfold[bn]);
//cout<<bn+1<<"  "<<bayes_bfold[bn]<<" data "<<hist_data->GetBinContent(bn+1)<<endl;
hist_svd_bfold->SetBinContent(bn+1,svd_bfold[bn]);
hist_BbB_bfold->SetBinContent(bn+1,BbB_bfold[bn]);
}
*/

Fold(mat_rm_b,hist_gen,hist_bayes,hist_bayes_bfold);
Fold(mat_rm_b,hist_gen,hist_svd,hist_svd_bfold);
Fold(mat_rm_b,hist_gen,hist_BbB,hist_BbB_bfold);

TCanvas *c1;
c1 = new TCanvas("cav","canv",800,600);

TLegend *leg = new TLegend(0.22,0.7,0.52,0.9);
/*
hist_data->Scale(1./hist_data->Integral());
hist_reco->Scale(1./hist_reco->Integral());
hist_gen->Scale(1./hist_gen->Integral());
hist_bayes->Scale(1./hist_bayes->Integral());
hist_svd->Scale(1./hist_svd->Integral());
hist_BbB->Scale(1./hist_BbB->Integral());
hist_bayes_bfold->Scale(1./hist_bayes_bfold->Integral());
hist_svd_bfold->Scale(1./hist_svd_bfold->Integral());
hist_BbB_bfold->Scale(1./hist_BbB_bfold->Integral());
*/

cout<<"data integral "<<hist_data->Integral()<<endl;
cout<<"reco integral "<<reco_integral<<endl;
cout<<"gen integral "<<gen_integral<<endl;
cout<<"bayesian integral "<<hist_bayes->Integral()<<endl;
cout<<"svd integral "<<hist_svd->Integral()<<endl;
cout<<"BinbyBin integral "<<hist_BbB->Integral()<<endl;

/*
hist_bayes->Scale(1.*hist_data->Integral()/reco_integral);
hist_svd->Scale(1.*hist_data->Integral()/reco_integral);
hist_BbB->Scale(1.*hist_data->Integral()/reco_integral);
*/
//hist_gen->Scale(1.*hist_data->Integral());

c1->cd();

gPad->SetLogx(1);
gPad->SetLogy(0);

hist_reco->Divide(hist_gen);
hist_reco->SetLineColor(1);
hist_reco->SetMaximum(2.);
hist_reco->SetMinimum(0.);
hist_reco->SetStats(0);
hist_reco->GetYaxis()->SetTitle("Unfolded/Gen MC");
hist_reco->Draw("e");
leg->AddEntry(hist_reco,"MC_RecoLevel");

/*
hist_data->Divide(hist_gen);
hist_data->SetLineColor(1);
hist_data->SetMaximum(2.);
hist_data->SetMinimum(0.);
hist_data->SetStats(0);
hist_data->GetYaxis()->SetTitle("Unfolded/Gen MC");
hist_data->Draw("e");
leg->AddEntry(hist_data,"Data_RecoLevel");
*/
hist_bayes->Divide(hist_gen);
hist_bayes->SetLineColor(2);
hist_bayes->SetStats(0);
hist_bayes->Draw("sames");
leg->AddEntry(hist_bayes,"Data_unfolded_Bayes");
hist_svd->Divide(hist_gen);
hist_svd->SetLineColor(3);
hist_svd->SetStats(0);
hist_svd->Draw("sames");
leg->AddEntry(hist_svd,"Data_unfolded_Svd");
hist_BbB->Divide(hist_gen);
hist_BbB->SetLineColor(7);
hist_BbB->SetStats(0);
hist_BbB->Draw("sames");
leg->AddEntry(hist_BbB,"Data_unfolded_BinbyBin");

/*
hist_bayes_bfold->Divide(hist_data);
hist_bayes_bfold->SetLineColor(2);
hist_bayes_bfold->SetStats(0);
hist_bayes_bfold->SetMinimum(0.);
//hist_bayes_bfold->SetMaximum(2.0);
hist_bayes_bfold->GetYaxis()->SetTitle("Backfolded / Data");
hist_bayes_bfold->Draw("e");
leg->AddEntry(hist_bayes_bfold,"Bayesian_Backfolded/Data");

hist_svd_bfold->Divide(hist_data);
hist_svd_bfold->SetLineColor(3);
hist_svd_bfold->SetStats(0);
hist_svd_bfold->Draw("sames");
leg->AddEntry(hist_svd_bfold,"Svd_Backfolded/Data");

hist_BbB_bfold->Divide(hist_data);
hist_BbB_bfold->SetLineColor(7);
hist_BbB_bfold->SetStats(0);
hist_BbB_bfold->Draw("sames");
leg->AddEntry(hist_BbB_bfold,"BinbyBin_Backfolded/Data");

TLine *line = new TLine(hist_data->GetBinLowEdge(2),1.,5000,1.);
line->SetLineColor(4);
//line->Draw();
*/
leg->Draw();
c1->SaveAs("unfolding_result.eps");

}

