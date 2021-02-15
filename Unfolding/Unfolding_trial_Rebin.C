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
#include <TH1F.h>
#include <TH2F.h>
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

const int netarange = 10;
double nbin_eta[netarange] = {62,44,40,34,30,23,20,14,7,7};

int nxmod2 = 62;
double xmod2[100] = {0.};/*[62+1] = {74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};*/
     
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


TH1D* rebin_hist(TH1D* thin/*, int ijetpt*/,int eta) {

  TH1D* thout;
  //  thout->Sumw2();
 double xval[100]={0};
  double xmean[100]={0};
  double zval[100]={0};
  double zerr[100]={0};

  double mxx=0; // peak poisition 

  double zval2[100]={0};

  double yvl[100]={0};
  double erryvl[100]={0};

  int nbinx = thin->GetNbinsX();
  for (int ij=0; ij<nbinx+2; ij++) {
    xval[ij] = thin->GetBinLowEdge(ij);
    xmean[ij] = thin->GetBinCenter(ij);
    zval[ij] = thin->GetBinContent(ij);
    zerr[ij] = thin->GetBinError(ij);
    if (mxx<zval[ij]) {mxx = zval[ij];}
  }

 if (nxmod2<0) { 
    
    int tmpiter = 0; // remove first four bins
    int ifirst = tmpiter+1; //130210 //Remove underflow bin

    //choose an upper limit according to bincontent
    //Negelect over flow bins, there should not be
  
    int ilast = nbin_eta[eta];

    //According to bin content change bin sizes

    xmod2[0] = xval[ifirst];
    zval2[0] = 0.0;
    nxmod2=0;
    for (int ij=ifirst; ij<=ilast; ij++) {
      zval2[nxmod2] =zval[ij];
      xmod2[++nxmod2] = xval[ij+1];
    }
    if (zval2[nxmod2]>0) {
      xmod2[nxmod2] = xval[ilast+1]; 
    }
 
 cout <<"ilast "<<ilast<<" "<<nxmod2<<" "<<xmod2[nxmod2]<<endl;
  }


  namex = thin->GetName();
  sprintf(namey, "Roo_%s", namex);
  titlex = thin->GetTitle();
  sprintf(titley, "Roo_%s", titlex);
  thout = new TH1D(namey, titley, nxmod2, xmod2);

   for (int ij=0; ij<nbinx+1; ij++) {
    int ix = getbinid(xmean[ij], nxmod2, xmod2);
    if (ix>=0 && ix<nxmod2) {
      yvl[ix] +=zval[ij];
      erryvl[ix] += zerr[ij]*zerr[ij];
    }
  }

  for (int ix=0; ix<nxmod2; ix++) {
    thout->SetBinContent(ix+1, yvl[ix]);
    thout->SetBinError(ix+1, sqrt(erryvl[ix]));
  }
  return thout;

}


TH2D* rebin_hist2d(TH2D* thin/*, int ijetpt*/) {

double zval[100][100]={0};
  double zerr[100][100]={0};
  int nbinx = thin->GetNbinsX();
  int nbiny = thin->GetNbinsY();

  cout<<"input x bins "<<nbinx<<" y bins "<<nbiny<<endl;

  for (int ij=0; ij<nbinx+2; ij++) {
    int ix = getbinid(thin->GetXaxis()->GetBinCenter(ij), nxmod2, xmod2);
    for (int jk=0; jk<nbiny+2; jk++) {
      if (ij==nbinx+1 && jk==nbiny+1) continue;
      int iy = getbinid(thin->GetYaxis()->GetBinCenter(jk), nxmod2, xmod2);
      if (ix<0 || iy<0) continue;
      if (ix>nxmod2 && iy>nxmod2) continue;
      double val=thin->GetBinContent(ij, jk);
      double err=thin->GetBinError(ij, jk);
      if (ix>nbinx+2 && iy<nbinx+2) {
	zval[nxmod2][iy] += val;
	zerr[nxmod2][iy] += err*err;
      } else if (ix<nbinx+2 && iy>nbinx+2) {
	zval[ix][nxmod2] += val;
	zerr[ix][nxmod2] += err*err;
      } else {
	zval[ix][iy] += val;
	zerr[ix][iy] += err*err;
      }
    }
  }
  namex = thin->GetName();
  sprintf(namey, "Roo_%s", namex);
  titlex = thin->GetTitle();
  sprintf(titley, "Roo_%s", titlex);
  TH2D* thout = new TH2D(namey, titley, nxmod2, xmod2, nxmod2, xmod2);
  
  for (int ix=0; ix<=nxmod2; ix++) {
    for (int iy=0; iy<=nxmod2; iy++) {
      thout->SetBinContent(ix+1, iy+1, zval[ix][iy]);
      thout->SetBinError(ix+1, iy+1, sqrt(zerr[ix][iy]));
    }
  }
 
  thout->GetXaxis()->SetTitleFont(42);
  thout->GetXaxis()->SetLabelFont(42);
  thout->GetXaxis()->SetLabelSize(0.07);
  thout->GetXaxis()->SetLabelOffset(.01);

  thout->GetYaxis()->SetTitleFont(42);
  thout->GetYaxis()->SetLabelFont(42);
  thout->GetYaxis()->SetLabelSize(0.07);
  thout->GetYaxis()->SetLabelOffset(.01);
  
  return thout;
}

int main()																																 
{	
const char* rootfiles[3] = {"../CPlusPlus/CMS_Files/Jets_in_CMS/Data_2015D/hist_RecoJetchs_PU_Data_2015D_JetHTCHS_NewPrescale_v2.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root",/*"../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root"*/"Response_Matrix/Spline_output_ak8.root"/*"Response_Matrix/Spline_output_ak4_1M.root"*/};

double scale_fac_b, scale_fac_s;
cout<<"scale bayesian by ?"<<endl;
cin>>scale_fac_b;
cout<<"scale svd by ?"<<endl;
cin>>scale_fac_s;

char name[100];

TH1D *hist_data;
TH1D *hist_reco;
TH1D *hist_gen;
TH2D *mat_rm;
TH2D *mat_rm_b;
TH2D *mat_rm_trial;
TH1D *hist_bayes;
TH1D* hist_svd;
TH1D* hist_BbB;


nxmod2 = -1;

int ialgo = 8;
int ieta = 1;

cout<<"algo ak"<<ialgo<<" eta"<<ieta<<endl;
 
for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();
if(ij==0) {
	sprintf(name,"mcjets/JetpT_ak%i_EtaBin%i",ialgo,ieta);
//	hist_data = rebin_hist((TH1D*)file1->Get(name),ieta-1);
	hist_data = (TH1D*)file1->Get(name);
	hist_data->Scale(1./hist_data->Integral());
	}
if(ij==1) {
	sprintf(name,"JetpT_ak%i_EtaBin%i",ialgo,ieta);
//	hist_reco = rebin_hist((TH1D*)file1->Get(name),ieta-1);
	hist_reco = (TH1D*)file1->Get(name); 
	hist_reco->Scale(1./hist_reco->Integral());
	sprintf(name,"Gen_MC_JetpT_ak%i_EtaBin%i",ialgo,ieta);
//	hist_gen = rebin_hist((TH1D*)file1->Get(name),ieta-1);
	hist_gen = (TH1D*)file1->Get(name); 
	hist_gen->Scale(1./hist_gen->Integral());
	}
if(ij==2) {
//	sprintf(name,"RecoJetvsGenJet_Algo%i_EtabBin%i",ialgo-1,ieta);
	sprintf(name,"Response_Matrix_ak%i_EtaBin%i",ialgo,ieta);
//	mat_rm = rebin_hist2d((TH2D*)file1->Get(name)); 
	mat_rm = (TH2D*)file1->Get(name); 
	cout<<"nxbisn "<<mat_rm->GetNbinsX()<<" ybins "<<mat_rm->GetNbinsY()<<endl;
  	  mat_rm_b = (TH2D*)mat_rm->Clone();
          mat_rm_b->Scale(1./ mat_rm_b->Integral()/*scale_fac_b*/);
//	  mat_rm->Scale(1./scale_fac_s);
	}
}
/*
for(int ij=0; ij<mat_rm->GetNbinsX(); ij++){
 for(int jk=0; jk<mat_rm->GetNbinsX(); jk++){
   cout<<mat_rm->GetBinContent(ij+1,jk+1)<<",";
  }
   cout<<endl;
}
*/
cout<<"matrix integral "<<mat_rm->Integral()<<endl;

mat_rm_trial = (TH2D*)mat_rm->Clone();

for(int ix=0; ix<(mat_rm->GetXaxis()->GetNbins()); ix++){
	double sum = 0;
	double sumerr = 0;
	for(int iy=0; iy<(mat_rm->GetXaxis()->GetNbins()); iy++){
		sum+= mat_rm->GetBinContent(ix+1,iy+1);
		sumerr+= mat_rm->GetBinError(ix+1,iy+1);
		}
	 for(int iy=0; iy<(mat_rm->GetXaxis()->GetNbins()); iy++){
		mat_rm_trial->SetBinContent(ix+1,iy+1,(mat_rm->GetBinContent(ix+1,iy+1))*1./sum);
		mat_rm_trial->SetBinError(ix+1,iy+1,(mat_rm->GetBinError(ix+1,iy+1))*1./sumerr);
		}	
	}



RooUnfoldResponse response;
sprintf(name,"unfold_ak%i_etabin%i",ialgo,ieta);
response = RooUnfoldResponse(hist_reco,hist_gen, mat_rm, name, name);

RooUnfoldResponse response_b;
sprintf(name,"unfold_ak%i_etabin%i_b",ialgo,ieta);
response_b = RooUnfoldResponse(hist_reco,hist_gen, mat_rm_b, name, name);

RooUnfoldBayes unfoldBayes(&response_b,hist_data,4,false);

RooUnfoldSvd unfoldSvd(&response_b,hist_data,25);

RooUnfoldBinByBin unfoldBbB(&response_b,hist_data);

hist_bayes = (TH1D*) unfoldBayes.Hreco(RooUnfold::kCovariance)->Clone();	
hist_svd  =  (TH1D*) unfoldSvd.Hreco(RooUnfold::kCovariance)->Clone();
hist_BbB  =  (TH1D*) unfoldBbB.Hreco(RooUnfold::kCovariance)->Clone();

TH1D *hist_bayes_bfold = (TH1D*)hist_bayes->Clone();
TH1D *hist_svd_bfold = (TH1D*)hist_svd->Clone();
TH1D *hist_BbB_bfold = (TH1D*)hist_BbB->Clone();

TMatrixD rm_mat_bfold = response_b.Mresponse();
TVectorD bayes_bfold = response_b.Mresponse() * unfoldBayes.Vreco();
TVectorD svd_bfold = response_b.Mresponse() * unfoldSvd.Vreco();
TVectorD BbB_bfold = response_b.Mresponse() * unfoldBbB.Vreco();

for(int bn=0; bn<hist_bayes_bfold->GetNbinsX(); bn++){
hist_bayes_bfold->SetBinContent(bn+1,bayes_bfold[bn]);
cout<<bn+1<<"  "<<bayes_bfold[bn]<<endl;
hist_svd_bfold->SetBinContent(bn+1,svd_bfold[bn]);
hist_BbB_bfold->SetBinContent(bn+1,BbB_bfold[bn]);
}

TCanvas *c1;
c1 = new TCanvas("cav","canv",800,600);

TLegend *leg = new TLegend(0.12,0.7,0.42,0.9);

hist_data->Scale(1./hist_data->Integral());
hist_reco->Scale(1./hist_reco->Integral());
hist_gen->Scale(1./hist_gen->Integral());
hist_bayes->Scale(1./hist_bayes->Integral());
hist_svd->Scale(1./hist_svd->Integral());
hist_BbB->Scale(1./hist_BbB->Integral());
hist_bayes_bfold->Scale(1./hist_bayes_bfold->Integral());
hist_svd_bfold->Scale(1./hist_svd_bfold->Integral());
hist_BbB_bfold->Scale(1./hist_BbB_bfold->Integral());

c1->cd();

gPad->SetLogx(1);
gPad->SetLogy(0);
gPad->SetLogz(1);
/*
hist_reco->Divide(hist_gen);
hist_reco->SetLineColor(1);
hist_reco->SetMaximum(2.);
hist_reco->SetMinimum(0.);
hist_reco->SetStats(0);
hist_reco->GetYaxis()->SetTitle("Unfolded/Gen MC");
hist_reco->Draw("e");
leg->AddEntry(hist_reco,"MC_Recolevel");

hist_data->Divide(hist_gen);
hist_data->SetLineColor(1);
hist_data->SetMaximum(2.);
hist_data->SetMinimum(0.);
hist_data->SetStats(0);
hist_data->GetYaxis()->SetTitle("Unfolded/Gen MC");
hist_data->Draw("e");
leg->AddEntry(hist_data,"Data_Recolevel");

hist_bayes->Divide(hist_gen);
hist_bayes->SetLineColor(2);
hist_bayes->SetStats(0);
hist_bayes->Draw("sames");
leg->AddEntry(hist_bayes,"Data_unfolded_Bayesian");
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
hist_bayes_bfold->Divide(hist_data);

*/

hist_bayes_bfold->SetLineColor(2);
hist_bayes_bfold->SetStats(0);
hist_bayes_bfold->SetMinimum(0.);
hist_bayes_bfold->SetMaximum(2.0);
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
leg->AddEntry(hist_BbB_bfold,"Svd_Backfolded/Data");

TLine *line = new TLine(hist_reco->GetBinLowEdge(2),1.,/*nbin_eta[ieta-1]*/3000,1.);
line->SetLineColor(4);
line->Draw();

leg->Draw();
/*
mat_rm_trial->SetStats(0);
mat_rm_trial->Draw("colz");
*/
sprintf(name,"Plots/Backfolding_result_scale_Bayesian%i_Svd%i.eps",int(scale_fac_b),int(scale_fac_s));
c1->SaveAs(name);

}

