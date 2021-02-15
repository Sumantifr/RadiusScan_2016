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
double nbin_eta[netarange] = {46,44,40,34,30,23,20,14,7,7};

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


TH1F* rebin_hist(TH1F* thin/*, int ijetpt*/,int eta) {

  TH1F* thout;
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
  thout = new TH1F(namey, titley, nxmod2, xmod2);

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


TH2F* rebin_hist2d(TH2F* thin/*, int ijetpt*/) {

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
  TH2F* thout = new TH2F(namey, titley, nxmod2, xmod2, nxmod2, xmod2);
  
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
const char* rootfiles[3] = {"../CPlusPlus/CMS_Files/Jets_in_CMS/Data_2015D/hist_RecoJetchs_PU_Data_2015D_JetHTCHS_NewPrescale_v2.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root", /*"../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root"*/"Response_Matrix/Spline_output_total.root"}	;

char name[100];

TH1F *hist_data;
TH1F *hist_reco;
TH1F *hist_gen;
TH2F *mat_rm;
TH2F *mat_rm_b;
TH1F *hist_bayes;
TH1F* hist_svd;
TH1F* hist_BbB;

nxmod2 = -1;

int ialgo = 4;
int ieta = 1;

 cout<<"algo ak"<<ialgo<<" eta"<<ieta<<endl;
 
for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();
if(ij==0) {
	sprintf(name,"mcjets/JetpT_ak%i_EtaBin%i",ialgo,ieta);
	hist_data = rebin_hist((TH1F*)file1->Get(name),ieta-1);
//	hist_data = (TH1F*)file1->Get(name);
	}
if(ij==1) {
	sprintf(name,"JetpT_ak%i_EtaBin%i",ialgo,ieta);
	hist_reco = rebin_hist((TH1F*)file1->Get(name),ieta-1);
//	hist_reco = (TH1F*)file1->Get(name); 
	sprintf(name,"Gen_MC_JetpT_ak%i_EtaBin%i",ialgo,ieta);
	hist_gen = rebin_hist((TH1F*)file1->Get(name),ieta-1);
//	hist_gen = (TH1F*)file1->Get(name); 
	}
if(ij==2) {
//	sprintf(name,"RecoJetvsGenJet_Algo%i_EtabBin%i",ialgo-1,ieta+1);
	sprintf(name,"Response_Matrix_ak%i_EtaBin%i",ialgo,ieta);
	mat_rm = rebin_hist2d((TH2F*)file1->Get(name)); 
	cout<<"nxbisn "<<mat_rm->GetNbinsX()<<" ybins "<<mat_rm->GetNbinsY()<<endl;
    mat_rm_b = (TH2F*)mat_rm->Clone();
    mat_rm_b->Scale(1./mat_rm_b->Integral());
	}
}

RooUnfoldResponse response;
sprintf(name,"unfold_ak%i_etabin%i",ialgo,ieta);
response = RooUnfoldResponse(hist_reco,hist_gen, mat_rm, name, name);

RooUnfoldResponse response_b;
sprintf(name,"unfold_ak%i_etabin%i_b",ialgo,ieta);
response_b = RooUnfoldResponse(hist_reco,hist_gen, mat_rm_b, name, name);

RooUnfoldBayes unfoldBayes(&response_b,hist_data,4,false);

RooUnfoldSvd unfoldSvd(&response,hist_data,7);

RooUnfoldBinByBin unfoldBbB(&response,hist_data);

hist_bayes = (TH1F*) unfoldBayes.Hreco(RooUnfold::kCovariance)->Clone();	
hist_svd  =  (TH1F*) unfoldSvd.Hreco(RooUnfold::kCovariance)->Clone();
hist_BbB  =  (TH1F*) unfoldBbB.Hreco(RooUnfold::kCovariance)->Clone();

TCanvas *c1;
c1 = new TCanvas("cav","canv",800,600);

TPad *main_pad;
TPad *pad[2];

hist_data->Scale(1./hist_data->Integral());
hist_reco->Scale(1./hist_reco->Integral());
hist_gen->Scale(1./hist_gen->Integral());
hist_bayes->Scale(1./hist_bayes->Integral());
hist_svd->Scale(1./hist_svd->Integral());
hist_BbB->Scale(1./hist_BbB->Integral());

c1->cd();
/*
main_pad = new TPad("c1pad","c1pad",0.,0.,1.,1.);
main_pad->cd();
main_pad->Divide(1,2,1.e-40,1.e-40);

pad[0] = (TPad*)main_pad->GetPad(1);

pad[0]->SetPad(0.01,0.4,0.985,0.985);
pad[0]->SetTopMargin(0.01);
pad[0]->SetBottomMargin(0.015);
pad[0]->SetRightMargin(0.01);
pad[0]->cd();

gPad->SetLogx(1);
gPad->SetLogy(1);

hist_data->SetLineColor(1);
hist_data->Draw("e");
hist_bayes->SetLineColor(2);
hist_bayes->Draw("sames");
hist_svd->SetLineColor(3);
hist_svd->Draw("sames");
*/
/*
pad[1] = (TPad*)main_pad->GetPad(2);

pad[1]->SetPad(0.01,0.05,0.985,0.4);
pad[1]->SetTopMargin(0.01);
pad[1]->SetBottomMargin(0.1);
pad[1]->SetRightMargin(0.01);
pad[1]->cd();
*/
gPad->SetLogx(1);
gPad->SetLogy(0);


hist_reco->Divide(hist_gen);
hist_reco->SetLineColor(1);
hist_reco->SetMaximum(2.);
hist_reco->SetMinimum(0.);
hist_reco->Draw("e");

/*
hist_data->Divide(hist_gen);
hist_data->SetLineColor(1);
hist_data->SetMaximum(2.);
hist_data->SetMinimum(0.);
hist_data->Draw("e");
*/
hist_bayes->Divide(hist_gen);
hist_bayes->SetLineColor(2);
hist_bayes->Draw("sames");
hist_svd->Divide(hist_gen);
hist_svd->SetLineColor(3);
hist_svd->Draw("sames");
hist_BbB->Divide(hist_gen);
hist_BbB->SetLineColor(7);
hist_BbB->Draw("sames");

TLine *line = new TLine(hist_reco->GetBinLowEdge(2),1.,nbin_eta[ieta-1],1.);
line->SetLineColor(4);
//line->Draw();

c1->SaveAs("unfolding_result.eps");

}

