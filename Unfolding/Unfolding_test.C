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

#include "RooUnfold.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldBinByBin.h"
#include "RooUnfoldResponse.h"

using namespace std;
using namespace CLHEP;

const int noptbins = 62;
double ptbins[noptbins+1] = {74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};
/*
const int noptbins1 = 42;
double ptbins1[noptbins1+1] = {74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500};
*/
const int noptbins1 = 62;
double ptbins1[noptbins1+1] = {74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

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
        reco->SetBinError(ix+1,sqrt(1-fakerate[ix])*(reco->GetBinError(ix+1)));
  }

 for(int ix=0; ix <((data->GetNbinsX())+1); ix++){
        data->SetBinContent(ix+1,(1-fakerate[ix])*(data->GetBinContent(ix+1)));
        data->SetBinError(ix+1,sqrt(1-fakerate[ix])*(data->GetBinError(ix+1)));
  }

 for(int ix=0; ix<(gen->GetNbinsX()+1); ix++){
       gen->SetBinContent(ix+1,(gen->GetBinContent(ix+1))*effi[ix]) ;
       gen->SetBinError(ix+1,(gen->GetBinError(ix+1))*sqrt(effi[ix])) ;
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




int main()       
//void TUnfold_example()                        
{
//const char* rootfiles[3] = {"/home/suman/RooUnfold/Example_Data_MG.root","/home/suman/RooUnfold/P8_RECOGEN.root","/home/suman/RooUnfold/P8_RECOGEN.root"};
const char* rootfiles[3] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15_new_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15_new_excor.root"};

char name[100];

TH1D *hist_data;
TH1D *hist_reco;
TH1D *hist_gen;
TH1D *hist_truth;
TH2D *mat_rm;

TH1D *hist_data1;
TH1D *hist_reco1;
TH1D *hist_gen1;
TH1D *hist_truth1;
TH2D *mat_rm1;

 hist_data1 = new TH1D("JetpT_ak4_EtaBin1_new","JetpT_ak4_EtaBin1_new_data",noptbins1,ptbins1);
 hist_reco1 = new TH1D("JetpT_ak4_EtaBin1_new_reco","JetpT_ak4_EtaBin1_new_reco",noptbins1,ptbins1);
 hist_gen1 = new TH1D("JetpT_ak4_EtaBin1_new_gen","JetpT_ak4_EtaBin1_new_gen",noptbins1,ptbins1);
 mat_rm1 = new TH2D("2d_reco_gen","2D RECO GEN",noptbins1,ptbins1,noptbins1,ptbins1);


int lastbin = 0;

for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();

if(ij==0) {
        sprintf(name,"JetpT_ak4_EtaBin1");
        hist_data = (TH1D*)file1->Get(name);
	hist_data->Scale(1./34.67);
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
//	mat_rm->Rebin2D(1,2);
        }
 }//ij


   for(int bn=0; bn<noptbins1; bn++){

   hist_data1->SetBinContent(bn+1,hist_data->GetBinContent(bn+1)); hist_data1->SetBinError(bn+1,hist_data->GetBinError(bn+1));
   hist_reco1->SetBinContent(bn+1,hist_reco->GetBinContent(bn+1)); hist_reco1->SetBinError(bn+1,hist_reco->GetBinError(bn+1));
   hist_gen1->SetBinContent(bn+1,hist_gen->GetBinContent(bn+1)); hist_gen1->SetBinError(bn+1,hist_gen->GetBinError(bn+1));

     for(int am=0; am<noptbins1; am++){
        mat_rm1->SetBinContent(bn+1,am+1,mat_rm->GetBinContent(bn+1,am+1));
        mat_rm1->SetBinError(bn+1,am+1,mat_rm->GetBinError(bn+1,am+1));
      }

   }

   double fakerate[100] = {0};
   double eff[100] = {0};
   double purity[100] = {0};
   double stbl[100] = {0};

   subtract_background(mat_rm1,hist_reco1,hist_gen1,hist_data1,fakerate,eff,purity,stbl) ;

   TFile *fileout ;
   fileout = new TFile("RooUnfold_example2.root","recreate") ;
//   TH1D *hist_unf;
//   sprintf(name,"RooUnfold_ak4_EtaBin1");
//   hist_unf = new TH1D(name,name,noptbins,ptbins);
   TH1D *hist_unf1;
   sprintf(name,"RooUnfold_ak4_EtaBin1_lowbin");
   hist_unf1 = new TH1D(name,name,noptbins1,ptbins1);

   TH1D *hist_relerr;
   hist_relerr = new TH1D("Rel_Error_Unfold","Rel_Error_Unfold",noptbins,1,noptbins);
 
   TH2D* COV_Mat_bayes;
   COV_Mat_bayes = new TH2D("Cov_Mat_Bayesian","Cov_Mat_Bayesian",noptbins,ptbins,noptbins,ptbins);
 
//   lastbin = LastBin_Counter(hist_data);

   RooUnfoldResponse response_b;
   sprintf(name,"unfold_AK4_Etabin1");
   response_b = RooUnfoldResponse(hist_reco1,hist_gen1, mat_rm1, name, name);

//  unfoldBbB.DoUnfold(0) ;

 // for(int iter=1; iter<20; iter++){
  int iter = 9;

   RooUnfoldBayes unfoldBayes(&response_b,hist_data1,iter,false);

   hist_unf1 = (TH1D*) unfoldBayes.Hreco(RooUnfold::kCovariance)->Clone();

  TMatrixD covmatrix_bayes;
  covmatrix_bayes.ResizeTo(mat_rm1->GetNbinsX(),mat_rm1->GetNbinsY());
  covmatrix_bayes = unfoldBayes.Ereco(RooUnfold::kCovariance);

  TMatrixD corrmatrix_bayes;
  corrmatrix_bayes.ResizeTo(mat_rm1->GetNbinsX(),mat_rm1->GetNbinsY());
 
  for(int ix=0; ix<(mat_rm1->GetNbinsX()); ix++){
    for(int iy=0; iy<(mat_rm1->GetNbinsY()); iy++){
 		if(covmatrix_bayes(ix,ix)>1.e-6 && covmatrix_bayes(iy,iy)>1.e-6){
		corrmatrix_bayes(ix,iy) = covmatrix_bayes(ix,iy) * 1./sqrt(covmatrix_bayes(ix,ix)*covmatrix_bayes(iy,iy));
			}
		}
	}

 double rho = 0;
  for(int ix=0; ix<(mat_rm1->GetNbinsX()); ix++){
   double sum=0;
   for(int iy=0; iy<(mat_rm1->GetNbinsY()); iy++){
     sum += corrmatrix_bayes(ix,iy);
    }
   rho += sum;
  }

  cout<<iter<<" rho /M "<<rho*1./mat_rm1->GetNbinsX()<<endl;
  
//}//iter
  
// /*
  hist_data1->SetLineColor(kBlack);
  hist_reco1->SetLineColor(kBlue);
  hist_gen1->SetLineColor(kRed);
  hist_unf1->SetLineColor(kMagenta);
//  hist_truth->SetLineColor(7);

  hist_data1->SetStats(0); //hist_data->SetMinimum(1.);
  hist_reco1->SetStats(0);
  hist_gen1->SetStats(0);
  hist_unf1->SetStats(0);

  sprintf(name,"RooUnfold_%s",hist_unf1->GetName());
  hist_unf1->SetName(name);


  for(int bn=0; bn<noptbins1; bn++){
 
  float relerr_unf = ( hist_unf1->GetBinContent(bn+1) > 1.e-7) ? hist_unf1->GetBinError(bn+1) *1./ hist_unf1->GetBinContent(bn+1): 1.e-7 ;
  float relerr_data = ( hist_data1->GetBinContent(bn+1) > 1.e-7) ? hist_data1->GetBinError(bn+1) *1./ hist_data1->GetBinContent(bn+1): 1.e-7 ;

  hist_relerr->SetBinContent(bn+1,relerr_unf*1./relerr_data);
  hist_relerr->SetBinError(bn+1,0);
  }

  for(int bn=0; bn<(hist_unf1->GetNbinsX()); bn++){
//    cout<<eff[bn]<<endl;
    hist_unf1->SetBinContent(bn+1,hist_unf1->GetBinContent(bn+1)*1./eff[bn]);
    hist_unf1->SetBinError(bn+1,hist_unf1->GetBinError(bn+1)*1./sqrt(eff[bn]));
//  hist_unf->SetBinContent(bn+1,hist_unf->GetBinContent(bn+1)*1./hist_unf->GetBinWidth(bn+1));
  }

  for(int ix=0; ix<covmatrix_bayes.GetNcols(); ix++){
        for(int iy=0; iy<covmatrix_bayes.GetNcols(); iy++){

               if(log10(covmatrix_bayes(ix,iy))>0){

                COV_Mat_bayes->Fill(ptbins[ix]+0.5,ptbins[iy]+0.5,log10(covmatrix_bayes(ix,iy)+1));
                }
                else{
                COV_Mat_bayes->Fill(ptbins[ix]+0.5,ptbins[iy]+0.5,-log10(-covmatrix_bayes(ix,iy)+1));
                    }
                }
        }

  TCanvas *c1 = new TCanvas("Roounfold_output","Roounfold_output",800,600);
  TLegend *leg1 = new TLegend(0.7,0.7,0.85,0.85);
  leg1->SetBorderSize(0);
  c1->cd(1);
  
  gPad->SetLogx(1);
  gPad->SetLogy(1);

  hist_data1->Draw("e"); leg1->AddEntry(hist_data1,"DATA","l");
  hist_gen1->Draw("sames");  leg1->AddEntry(hist_gen1,"GEN","l");
  hist_unf1->Draw("sames"); leg1->AddEntry(hist_unf1,"Unfolded","l");
//  hist_truth->Draw("sames"); leg1->AddEntry(hist_truth,"Unfolded","l");
  leg1->Draw();

//  TH1D *hist_gen_rat = (TH1D*)hist_gen->Clone(); hist_gen_rat->Divide(hist_data);
  
  sprintf(name,"%s.eps",c1->GetName());
  c1->SaveAs(name);

 fileout->cd();
 fileout->Write();
 fileout->Close();
// */
}
