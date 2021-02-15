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
int nbin_eta[netarange] = {62,44,40,34,30,23,20,14,7,7};

const int nalgo = 10;
const char* JetRad[nalgo] = {"ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11"};
const int EtaBins = 10;

int nxmod2 = 62;
double xmod2[100] = {0.};/*[62+1] = {74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};*/

const int noptbins = 62;
double ptbins[noptbins+1] = {74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};
     
     
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
const char* rootfiles[3] = {"../CPlusPlus/CMS_Files/Jets_in_CMS/Data_2015D/hist_RecoJetchs_PU_Data_2015D_JetHTCHS_NewPrescale_v2.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root"/*"Response_Matrix/Spline_output_total.root"*/}	;

char name[100];

TFile *fileout;
fileout = new TFile("Unfold_Output.root","RECREATE") ;

TH1F *hist_data[nalgo][EtaBins];
TH1F *hist_reco[nalgo][EtaBins];
TH1F *hist_gen[nalgo][EtaBins];
TH2F *mat_rm[nalgo][EtaBins];
TH2F *mat_rm_b[nalgo][EtaBins];
TH2F *mat_rm_trial[nalgo][EtaBins];
TH1F *hist_bayes[nalgo][EtaBins];
TH1F* hist_svd[nalgo][EtaBins];
TH1F* hist_BbB[nalgo][EtaBins];

TH1F *rat_data[nalgo][EtaBins];
TH1F *rat_reco[nalgo][EtaBins];
TH1F *rat_bayes[nalgo][EtaBins];
TH1F *rat_svd[nalgo][EtaBins];
TH1F *rat_BbB[nalgo][EtaBins];

for(int ij=0; ij<nalgo; ij++){
	for(int jk=0; jk<EtaBins; jk++){
		sprintf(name,"Ratio_Data_by_GEN_%s_Etabin%i",JetRad[ij],jk+1);
		rat_data[ij][jk] = new TH1F(name,name,nbin_eta[jk],ptbins);
		
		sprintf(name,"Ratio_MC_Reco_by_GEN_%s_Etabin%i",JetRad[ij],jk+1);
		rat_reco[ij][jk] = new TH1F(name,name,nbin_eta[jk],ptbins);
		
		sprintf(name,"Ratio_Unfolded_Bayes_by_GEN_%s_Etabin%i",JetRad[ij],jk+1);
		rat_bayes[ij][jk] = new TH1F(name,name,nbin_eta[jk],ptbins);
		
		sprintf(name,"Ratio_Unfolded_Svd_by_GEN_%s_Etabin%i",JetRad[ij],jk+1);
		rat_svd[ij][jk] = new TH1F(name,name,nbin_eta[jk],ptbins);
		
		sprintf(name,"Ratio_Unfolded_BinbyBin_by_GEN_%s_Etabin%i",JetRad[ij],jk+1);
		rat_BbB[ij][jk] = new TH1F(name,name,nbin_eta[jk],ptbins);
		}
	}


for(int rad=0; rad<nalgo; rad++){
	for(int jk=0; jk<EtaBins; jk++){

nxmod2 = -1;

int ialgo = rad+2;
int ieta = jk+1;

cout<<"algo ak"<<ialgo<<" eta"<<ieta<<endl;
 
for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();
if(ij==0) {
	sprintf(name,"mcjets/JetpT_ak%i_EtaBin%i",ialgo,ieta);
	hist_data[rad][jk] = rebin_hist((TH1F*)file1->Get(name),ieta-1);
//	hist_data = (TH1F*)file1->Get(name);
	}
if(ij==1) {
	sprintf(name,"JetpT_ak%i_EtaBin%i",ialgo,ieta);
	hist_reco[rad][jk] = rebin_hist((TH1F*)file1->Get(name),ieta-1);
//	hist_reco = (TH1F*)file1->Get(name); 
	sprintf(name,"Gen_MC_JetpT_ak%i_EtaBin%i",ialgo,ieta);
	hist_gen[rad][jk] = rebin_hist((TH1F*)file1->Get(name),ieta-1);
//	hist_gen = (TH1F*)file1->Get(name); 
	}
if(ij==2) {
	sprintf(name,"RecoJetvsGenJet_Algo%i_EtabBin%i",ialgo-1,ieta);
//	sprintf(name,"Response_Matrix_ak%i_EtaBin%i",ialgo,ieta);
	mat_rm[rad][jk] = rebin_hist2d((TH2F*)file1->Get(name)); 
//	mat_rm = (TH2F*)file1->Get(name); 
	cout<<"nxbisn "<<mat_rm[rad][jk]->GetNbinsX()<<" ybins "<<mat_rm[rad][jk]->GetNbinsY()<<endl;
  	  mat_rm_b[rad][jk] = (TH2F*)mat_rm[rad][jk]->Clone();
          mat_rm_b[rad][jk]->Scale(1./mat_rm_b[rad][jk]->Integral());
	}
}

mat_rm_trial[rad][jk] = (TH2F*)mat_rm[rad][jk]->Clone();

for(int ix=0; ix<(mat_rm[rad][jk]->GetXaxis()->GetNbins()); ix++){
	double sum = 0;
	double sumerr = 0;
	for(int iy=0; iy<(mat_rm[rad][jk]->GetYaxis()->GetNbins()); iy++){
		sum+= mat_rm[rad][jk]->GetBinContent(ix+1,iy+1);
		sumerr+= mat_rm[rad][jk]->GetBinError(ix+1,iy+1);
		}
	 for(int iy=0; iy<(mat_rm[rad][jk]->GetYaxis()->GetNbins()); iy++){
		mat_rm_trial[rad][jk]->SetBinContent(ix+1,iy+1,(mat_rm[rad][jk]->GetBinContent(ix+1,iy+1))*1./sum);
		mat_rm_trial[rad][jk]->SetBinError(ix+1,iy+1,(mat_rm[rad][jk]->GetBinError(ix+1,iy+1))*1./sumerr);
		}	
	}

RooUnfoldResponse response;
sprintf(name,"unfold_ak%i_etabin%i",ialgo,ieta);
response = RooUnfoldResponse(hist_reco[rad][jk],hist_gen[rad][jk], mat_rm[rad][jk], name, name);

RooUnfoldResponse response_b;
sprintf(name,"unfold_ak%i_etabin%i_b",ialgo,ieta);
response_b = RooUnfoldResponse(hist_reco[rad][jk],hist_gen[rad][jk], mat_rm_b[rad][jk], name, name);

RooUnfoldBayes unfoldBayes(&response_b,hist_data[rad][jk],4,false);

RooUnfoldSvd unfoldSvd(&response,hist_data[rad][jk],7);

RooUnfoldBinByBin unfoldBbB(&response,hist_data[rad][jk]);

hist_bayes[rad][jk] = (TH1F*) unfoldBayes.Hreco(RooUnfold::kCovariance)->Clone();	
hist_svd[rad][jk]  =  (TH1F*) unfoldSvd.Hreco(RooUnfold::kCovariance)->Clone();
hist_BbB[rad][jk]  =  (TH1F*) unfoldBbB.Hreco(RooUnfold::kCovariance)->Clone();

sprintf(name,"Bayesian_%s",hist_bayes[rad][jk]->GetName());
hist_bayes[rad][jk]->SetName(name);
sprintf(name,"SVD_%s",hist_svd[rad][jk]->GetName());
hist_svd[rad][jk]->SetName(name);
sprintf(name,"BinbyBin_%s",hist_BbB[rad][jk]->GetName());
hist_BbB[rad][jk]->SetName(name);

hist_data[rad][jk]->Scale(1./hist_data[rad][jk]->Integral());
hist_reco[rad][jk]->Scale(1./hist_reco[rad][jk]->Integral());
hist_gen[rad][jk]->Scale(1./hist_gen[rad][jk]->Integral());
hist_bayes[rad][jk]->Scale(1./hist_bayes[rad][jk]->Integral());
hist_svd[rad][jk]->Scale(1./hist_svd[rad][jk]->Integral());
hist_BbB[rad][jk]->Scale(1./hist_BbB[rad][jk]->Integral());

cout<<"no. of bins in data "<<rat_data[rad][jk]->GetNbinsX()<<endl;
cout<<"no. of bins in gen "<<hist_gen[rad][jk]->GetNbinsX()<<endl;
cout<<"no. of bins in bayes "<<rat_bayes[rad][jk]->GetNbinsX()<<endl;
cout<<"no. of bins in svd "<<rat_svd[rad][jk]->GetNbinsX()<<endl;
cout<<"no. of bins in BbB "<<rat_BbB[rad][jk]->GetNbinsX()<<endl;

rat_data[rad][jk]->Divide(hist_data[rad][jk],hist_gen[rad][jk],1.,1.);
rat_reco[rad][jk]->Divide(hist_reco[rad][jk],hist_gen[rad][jk],1.,1.);
rat_bayes[rad][jk]->Divide(hist_bayes[rad][jk],hist_gen[rad][jk],1.,1.);
rat_svd[rad][jk]->Divide(hist_svd[rad][jk],hist_gen[rad][jk],1.,1.);
rat_BbB[rad][jk]->Divide(hist_BbB[rad][jk],hist_gen[rad][jk],1.,1.);

 }//jk
}//rad

fileout->cd();
fileout->Write();
fileout->Close();
}

