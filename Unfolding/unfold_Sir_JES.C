/*
TH1F* xxx = new TH1F("name", "name", 100, -.5, 99.5);

Fill(0, weight);
Fill (1, 1);

*/


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


#include <TRandom.h>

#include "RooUnfold.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldResponse.h"
//#include "RooUnfHistoSvd.h"
#include "TLegend.h"

using namespace std;
using namespace CLHEP;

const double mass_pi=0.139;

bool pedsub=true;

const int ptstrt=0;

const int nextraUnfold=2*26;
//int nAlgoorder[nextraUnfold+1]={10,3,4,5,6,9,7,8};
const char* srcnames[nextraUnfold+1] =
  { "central",
   "AbsoluteStat", "AbsoluteScale_u", "AbsoluteFlavMap_u", "AbsoluteMPFBias_u", "Fragmentation_u", "SinglePionHCAL_u", "SinglePionECAL_u", "FlavorQCD_u", "TimePt_u", "TimeEta_u", "RelativeJEREC1_u", "RelativeJEREC2_u", "RelativeJERHF_u", "RelativeFSR_u", "RelativePtBB_u", "RelativePtEC1_u", "RelativePtEC2_u","RelativePtHF_u", "RelativeStatEC_u", "RelativeStatHF_u", "PileUpDataMC_u", "PileUpPtRef_u", "PileUpPtBB_u", "PileUpPtEC1_u", "PileUpPtEC2_u", "PileUpPtHF_u",
  "AbsoluteStat_d", "AbsoluteScale_d", "AbsoluteFlavMap_d", "AbsoluteMPFBias_d", "Fragmentation_d", "SinglePionHCAL_d", "SinglePionECAL_d", "FlavorQCD_d", "TimePt_d", "TimeEta_d", "RelativeJEREC1_d", "RelativeJEREC2_d", "RelativeJERHF_d", "RelativeFSR_d", "RelativePtBB_d", "RelativePtEC1_d", "RelativePtEC2_d","RelativePtHF_d", "RelativeStatEC_d", "RelativeStatHF_d", "PileUpDataMC_d", "PileUpPtRef_d", "PileUpPtBB_d", "PileUpPtEC1_d", "PileUpPtEC2_d", "PileUpPtHF_d"  };

const int ngenfiles=1;
const char* genrootname[ngenfiles]={"../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/Madgraph_MCJets_CHS_GenFull.root"}; //, "../2012/test_pythia8_redbin.root"};
const char* genmodelname[ngenfiles]={"gen_Madgraph"}; //, "gen_pythia8"};

const int nfiles=4;

//const char* rootname[nfiles]={"../CPlusPlus/CMS_Files/Jets_in_CMS/Data_2015D/hist_RecoJetchs_PU_Data_2015D_JetHTCHS_NewPrescale_v2.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/Madgraph_MCJets_CHS_GenFull.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_PythiaFiles_pTBinnedCHS_LumiWeighted.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/hist_PFJetCHS_HerwigFlat_LumiWeighted.root"};
 
const char* rootname[nfiles]={"../CPlusPlus/CMS_Files/Jets_in_CMS/Data_2015D/hist_RecoJetchs_PU_Data_2015D_JetHTCHS_NewPrescale_v2.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/Madgraph_MCJets_CHS_syst.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/hist_PFJetCHS_HerwigFlat_LumiWeighted_syst.root"};

const char* modelname[nfiles]={"Data", /*"Pythia6",*/"Madgraph", "Pythia8", "Herwig"};
//const char* modelname[nfiles]={"0Madgraph","1Madgraph","2Madgraph","3Madgraph","4Madgraph"};

static const int nalgo = 10 ;
const char* JetRad[nalgo] = {"ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11"};
static const int netarange = 10 ;
const char* JetEta[netarange] = {"|eta|<0.5","0.5<|eta|<1.0","1.0<|eta|<1.5","1.5<|eta|<2.0","2.0<|eta|<2.5","2.5<|eta|<3.0","3.0<|eta|<3.2","3.2<|eta|<3.7","3.7<|eta|<4.2","4.2<|eta|<4.7"} ;
double etarng[netarange+1] ={0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.2, 3.7, 4.2, 4.7};
double nbin_eta[netarange] = {46,44,40,34,30,23,20,14,7,7};

const int indexx=2 ;

TFile* fileInput[nfiles+ngenfiles]; 

int nxmod2;
double xmod2[200];

//const int nextraUnfold = 0;

TH1D* h_mcgeninput[nfiles+ngenfiles]={0};
TH1D* h_recoinput[nfiles]={0};
TH1D* h_recoinputwobkgsub[nfiles]={0};

TH1D* h_unfoldedbayes[nfiles]={0};
TH1D* h_unfoldedsvd[nfiles]={0};

TH2D* h2d_mccorrel=0;
TH1D* h1d_mcreco=0;

TH1D* tmphist1=0;
TH1D* tmphist1x=0;
TH1D* tmphist2=0;
TH1D* tmphist2x=0;

TH1D* h_tmpgen=0;


TH1D* rathist1[nfiles][2] ={0};
TH1D* rathist2[nfiles][2] ={0};
TH1D* rathist3[nfiles][2] ={0};
TH1D* rathist4[nfiles][2] ={0};
TH1D* rathist5[nfiles][2] ={0};
TH1D* rathist6[nfiles][2] ={0};
TH1D* rathist7[nfiles][2] ={0};
TH1D* rathist8[nfiles][2] ={0};
TH1D* rathist9[nfiles][2] ={0};
TH1D* rathist10[nfiles][2] ={0};


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

void calc_deltax(TH1D* thin, double* param) {
  double avedev = 0.0;
  double errsq = 0.0;
  double chisq = 0.0;

  for (int ij=0; ij<thin->GetNbinsX(); ij++) {
    double val = thin->GetBinContent(ij+1);
    if (val >1) val=1./val;
    
    double err = max(min(1., thin->GetBinError(ij+1)), 1.e-6);
    if (err<=1.e-6 || err>=1) continue;
    avedev +=fabs(1 - val)/pow(err, 2.);
    errsq +=pow(1./err, 2.);
    chisq +=pow( (1 - val)/err, 2.);
  }
  avedev /=errsq; avedev = int(1000.*avedev+0.0005)/1000.;
  chisq = int(10.*chisq+0.05)/10.;
  param[0] = avedev;
  param[1] = chisq;
}

void hist_setbins(TH1D* th, int lm) {
  const int nbmx=100;
  int nbn=th->GetNbinsX();
  if (nbn>nbmx) nbn = nbmx;

  double dx=0.2*(nfiles/2.-lm)*th->GetBinWidth(nbn/2);
  double xval[nbmx];
  for (int ix=0; ix<=nbn; ix++) { //GMAA
    xval[ix] = th->GetBinLowEdge(ix+1)+dx;
  }
  th->SetBins(nbn, xval);
}


void convert_errorplot(TH1D* thin, int ifil, int ior) {
  int nbins = thin->GetNbinsX();
  for (int ix=1; ix<=nbins; ix++) {
    double val= thin->GetBinContent(ix);
    double err = thin->GetBinError(ix);
    if (err > val) cout <<"==       ================== "<<thin->GetName()<<" "<<ifil<<" "<<ior<<" "<<val <<" "<<err/max(1.e-6,val)<<endl;
    if (val>1.e-6) {
      thin->SetBinContent(ix, err/val);
    } else {
      thin->SetBinContent(ix, 0.0);
    }

    thin->SetBinError(ix, 0.0);
  }
  thin->SetLineColor(ifil);
  thin->SetLineStyle(2*ior+1);
  thin->SetLineWidth(2*ior+1);
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


  for (int ij=0; ij<nbinx+2; ij++) {
    zval[ij] = thin->GetBinContent(ij);
    if (mxx<zval[ij]) {mxx = zval[ij];}
  }

 if (nxmod2<0) { 
    
    int tmpiter = 0; // remove first four bins
    int ifirst = tmpiter+1; //130210 //Remove underflow bin

    //choose an upper limit according to bincontent
    //Negelect over flow bins, there should not be
    
    int ilast = nbin_eta[eta]; //nbinx;
   /* for (int ij=0; ij<nbinx; ij++) {
      cout<<" ij "<< ij<<" "<<zval[ij]<<endl;
      if (zval[ij] < 1) { ilast = ij-1; 
	break; 
      }
   }*/
   
    

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

  thout->GetXaxis()->SetTitleFont(42);
  thout->GetXaxis()->SetLabelFont(42);
  thout->GetXaxis()->SetLabelSize(0.07);
  thout->GetXaxis()->SetLabelOffset(.01);

  thout->GetYaxis()->SetTitleFont(42);
  thout->GetYaxis()->SetLabelFont(42);
  thout->GetYaxis()->SetLabelSize(0.07);
  thout->GetYaxis()->SetLabelOffset(.01);

  thout->GetXaxis()->SetTitleOffset(0.9);
  thout->GetXaxis()->SetTitleSize(0.07);

  thout->SetLineWidth(1);
  thout->GetXaxis()->SetTitle(thout->GetTitle());

  return thout;

}

TH2D* rebin_hist2d(TH2D* thin/*, int ijetpt*/) {

double zval[100][100]={0};
  double zerr[100][100]={0};
  int nbinx = thin->GetNbinsX();
  int nbiny = thin->GetNbinsY();

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


/* 
  double zval[100][100]={0};
  double zerr[100][100]={0};
  int nbinx = thin->GetNbinsX();
  int nbiny = thin->GetNbinsY();
 
  for (int ij=0; ij<nxmod2; ij++) {
    for (int jk=0; jk<nxmod2; jk++) {
      double val=thin->GetBinContent(ij, jk);
      double err=thin->GetBinError(ij, jk);
      
	zval[ij][jk] = val;
	zerr[ij][jk] = err*err;
      
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
*/
 
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

void normlise_hist(TH1D* hist, double ntot) {
  if (ntot<1.) ntot = 1.;
  double nttox = max(1.,hist->Integral());
  double ratio = ntot/nttox;
  for (int ij=0; ij<hist->GetNbinsX(); ij++) {
    hist->SetBinContent(ij+1, ratio*hist->GetBinContent(ij+1));
    hist->SetBinError(ij+1, ratio*hist->GetBinError(ij+1));
  }
}

void add_index(int ijk, TNamed* hist, int ndim) {

  namex = hist->GetName();
  sprintf(namey, "%i_%s", ijk, namex);
  hist->SetName(namey);
  
  titlex = hist->GetTitle();
  sprintf(titley, "%i_%s", ijk, titlex);
  hist->SetTitle(titley);
}

void add_nameindex(TNamed* hist, char ttl[]) {

  namex = hist->GetName();
  sprintf(namey, "%s_%s", ttl, namex);
  hist->SetName(namey);
  
  titlex = hist->GetTitle();
  sprintf(titley, "%s_%s", ttl, titlex);
  hist->SetTitle(titley);
}

void calc_chisq(double* chi2, TH1D* h_data, TH1D* h_mc) {
  const int nbinmx=100;
  double vdata[nbinmx]={0.};
  double vmc[nbinmx]={0.};
  double totdata=0.;
  double totmc = 0.;
  double errdata[nbinmx]={0.};
  double errmc[nbinmx]={0.};  
  double toterr[nbinmx]={0.}; 
  int nbin = h_mc->GetNbinsX();
  
  int nbndata = h_data->GetNbinsX();
  if (nbin <nbinmx) {
    for (int ij=0; ij<nbin; ij++) {
      
      vdata[ij] = h_data->GetBinContent(ij+1);
      totdata += vdata[ij]; 
      vmc[ij] = h_mc->GetBinContent(ij+1);
      totmc +=vmc[ij];

      errdata[ij] = h_data->GetBinError(ij+1);
      errmc[ij] = h_mc->GetBinError(ij+1);
    }

    if (totmc <1.) totmc = 1.;
    if (totdata <1.) totdata = 1.;
    for (int ij=0; ij<nbin; ij++) {
      vdata[ij] /=totdata;
      vmc[ij] /=totmc;
      errdata[ij] /=totdata;
      errmc[ij] /=totmc;
      toterr[ij] = sqrt(errdata[ij]*errdata[ij] + errmc[ij]*errmc[ij]);
    } 

    //Calculate chisquare
    chi2[0] =  chi2[1] = chi2[2] = 0;
    for (int ij=0; ij<nbin; ij++) {
      chi2[0] += pow((vdata[ij] - vmc[ij]), 2.0); 
      chi2[1] += pow((vdata[ij] - vmc[ij])/max(1.e-6,errdata[ij]), 2.0);
      chi2[2] += pow((vdata[ij] - vmc[ij])/max(1.e-6,toterr[ij]), 2.0);
    }
  } else {
    cout <<"Increase nbinmx, which is equal to "<<nbinmx<<" less than histogrammes binning "<<nbin<<endl;

  }
}

void calc_chisq_svd(double* chi2, TH1D* h_unfold, TMatrixD cov, TMatrixD cov2,TH1D* h_mc) {

  double ratio = h_unfold->Integral()/max(1., h_mc->Integral());
  const int nbinmx=100;
  double vdata[nbinmx]={0.};
  double vmc[nbinmx]={0.};
  double errdata[nbinmx]={0.};
  double errmc[nbinmx]={0.};  
  double toterr[nbinmx]={0.}; 
  int nbin = h_mc->GetNbinsX();
  TVectorD diffdmc(nbin);

  int nbndata = h_unfold->GetNbinsX();
  if (nbin <nbinmx) {
    for (int ij=0; ij<nbin; ij++) {
      
      vdata[ij] = h_unfold->GetBinContent(ij+1);
      vmc[ij] = ratio*h_mc->GetBinContent(ij+1);

      errdata[ij] = h_unfold->GetBinError(ij+1);
      errmc[ij] = ratio*h_mc->GetBinError(ij+1);
      diffdmc(ij) = vdata[ij] - vmc[ij];
      toterr[ij] = sqrt(errdata[ij]*errdata[ij] + errmc[ij]*errmc[ij]);
    }
    //Calculate chisquare
    chi2[0] =  chi2[1] = chi2[2] = chi2[3] = chi2[4]=0;
    for (int ij=0; ij<nbin; ij++) {
      chi2[0] += pow((vdata[ij] - vmc[ij]), 2.0); 
      chi2[1] += pow((vdata[ij] - vmc[ij])/max(1.e-6,errdata[ij]), 2.0);
      chi2[2] += pow((vdata[ij] - vmc[ij])/max(1.e-6,toterr[ij]), 2.0);
    } 

    int ncols=cov.GetNcols();

    for (int ix=0; ix<ncols; ix++) {
      cov(ix,ix) += errmc[ix]*errmc[ix];
      cov2(ix,ix) += errmc[ix]*errmc[ix];
    }

    cov.Invert();
    cov2.Invert();

    TVectorD covdx = cov*diffdmc;
    for (int ix=0; ix<cov.GetNcols(); ix++) { chi2[3] +=diffdmc(ix)*covdx(ix);}
    
    TVectorD covdx2 = cov2*diffdmc;
    for (int ix=0; ix< ncols; ix++) { chi2[4] +=diffdmc(ix)*covdx2(ix);}

  } else {
    cout <<"Increase nbinmx, which is equal to "<<nbinmx<<" less than histogrammes binning "<<nbin<<endl;

  }
}

double calc_chisq_sss(TH1D* h_unfold, TH1D* h_mc, TMatrixD cov) {

  double ratio = h_unfold->Integral()/max(1., h_mc->Integral());
  const int nbinmx=100;
  double vdata[nbinmx]={0.};
  double vmc[nbinmx]={0.};
  double errdata[nbinmx]={0.};
  double errmc[nbinmx]={0.};  
  double toterr[nbinmx]={0.}; 
  int nbin = h_mc->GetNbinsX();
  TVectorD diffdmc(nbin);

  int nbndata = h_unfold->GetNbinsX();
  double chi2 = 0.0;
  if (nbin <nbinmx) {
    for (int ij=0; ij<nbin; ij++) {
      
      vdata[ij] = h_unfold->GetBinContent(ij+1);
      vmc[ij] = ratio*h_mc->GetBinContent(ij+1);
      diffdmc(ij) = vdata[ij] - vmc[ij];
    }
    //Calculate chisquare
    
    TVectorD covdx = cov*diffdmc;
    for (int ix=0; ix<cov.GetNcols(); ix++) { chi2 +=diffdmc(ix)*covdx(ix);}
    
  } else {
    cout <<"Increase nbinmx, which is equal to "<<nbinmx<<" less than histogrammes binning "<<nbin<<endl;

  }
  return int(1000.*(chi2+0.0005))/1000.;
}


void calc_deltax_cov(double* delta, TH1D* h1, TH1D* h2, TMatrixD cov1, TMatrixD cov2) {

  double totdata=0.;
  double totmc = 0.;

  const int nbinmx=100;
  double vdata[nbinmx]={0.};
  double vmc[nbinmx]={0.};

  double errdata[nbinmx]={0.};
  double errmc[nbinmx]={0.};  
  double errmc2[nbinmx]={0.};  
  double toterr[nbinmx]={0.}; 
  double totraterr[nbinmx]={0.}; 
  double rat[nbinmx]={0.};

  int nbin = h1->GetNbinsX();
  
  int nbndata = h1->GetNbinsX();
  TVectorD diffdmc(nbin);
  if (nbin <nbinmx) {
    for (int ij=0; ij<nbin; ij++) {
      
      vdata[ij] = h1->GetBinContent(ij+1);
      totdata += vdata[ij]; 
      vmc[ij] = h2->GetBinContent(ij+1);
      totmc +=vmc[ij];

      errdata[ij] = h1->GetBinError(ij+1);
      errmc[ij] = h2->GetBinError(ij+1);
    }

    if (totmc <1.) totmc = 1.;
    if (totdata <1.) totdata = 1.;

    double ratio = totdata/ max(1., totmc);
    for (int ij=0; ij<nbin; ij++) {
      diffdmc(ij) = vdata[ij] - ratio*vmc[ij];
      errmc2[ij] = ratio*errmc[ij]*ratio*errmc[ij];
      toterr[ij] = sqrt(errdata[ij]*errdata[ij] + errmc2[ij]);
    } 

    //Calculate chisquare
    //    double errsq = 0.;
    double chisq = 0.;

    for (int ij=0; ij<nbin; ij++) {
      if (errdata[ij] >1.e-6 || errmc[ij]>1.e-6) {

       cout<<"data "<<vdata[ij]<<" mc "<<vmc[ij]<<" ratio "<<ratio<<endl ;
	
	chisq += pow( (vdata[ij] - ratio*vmc[ij])/max(1.e-6,toterr[ij]), 2.0);
      }
    }
    chisq = int(10.*(chisq+0.05))/10.;
    
    //    delta[0] = avedev;
    delta[1] = chisq;

    if (cov1.GetNcols() ==0) {
      int ncols = h1->GetNbinsX(); 
      cov1.ResizeTo(ncols, ncols);
      for (int ix=0; ix<ncols; ix++) {
	cov1(ix, ix) =errdata[ix]*errdata[ix];
      }
    }
    
    int ncols=cov2.GetNcols();
    
    if (ncols==0) {
      ncols = cov1.GetNcols();
      cov2.ResizeTo(ncols, ncols);
      for (int ix=0; ix<ncols; ix++) {
	cov2(ix, ix) =errmc2[ix];
      }
    } else { //If defined, just modified with ratio
      for (int ix=0; ix< ncols; ix++) {
	for (int iy=0; iy< ncols; iy++) {
	  cov2(ix, iy) *=ratio*ratio;
	}
      }
    }
    
    TMatrixD comcovariance = cov1 + cov2;

    comcovariance.Invert();
    
    TVectorD covdx = comcovariance*diffdmc;
    delta[2] = 0;
    for (int ix=0; ix< ncols; ix++) { delta[2] +=diffdmc(ix)*covdx(ix);}
    delta[2]= int(10.*delta[2]+0.05)/10.;

    for (int ij=0; ij<nbin; ij++) {
      vdata[ij] /=totdata;
      vmc[ij] /=totmc;
      errdata[ij] /=totdata;
      errmc[ij] /=totmc;
      
      rat[ij] = vdata[ij]/max(1.e-6,abs(vmc[ij]));	

      if (rat[ij] >1.0) rat[ij] = 1/rat[ij];
      if (rat[ij] <=0.0) rat[ij] = 1.e-6;

      totraterr[ij] = rat[ij] * sqrt (pow(errdata[ij]/max(1.e-6, abs(vdata[ij])),2.0) + pow(errmc[ij]/max(1.e-6, abs(vmc[ij])),2.0));
    } 

    //Calculate chisquare
    double avedev = 0.;
    double errsq = 0.;
    
    for (int ij=0; ij<nbin; ij++) {
      if ((vdata[ij] >1.e-6 && vmc[ij]>1.e-6) && (errdata[ij] >1.e-6 || errmc[ij]>1.e-6) && totraterr[ij] >1.e-6) {
	avedev +=abs( 1 - rat[ij])/pow(max(1.e-6,totraterr[ij]), 2.0);
	errsq +=pow(1./max(1.e-6,totraterr[ij]), 2.0);
      }
    }
    avedev /=errsq; avedev = int(1000.*avedev+0.0005)/1000.;
    
    delta[0] = avedev;
  } else {
    cout <<"Increase nbinmx, which is equal to "<<nbinmx<<" less than histogrammes binning "<<nbin<<endl;
  }
}


int subtract_background(TH2D* h2d_correl, TH1D* data, TH1D* mc1, TH1D* mc2, TH1D*mc3, double* fakerate, double* effi, int jk) {
  int nbinx = h2d_correl->GetNbinsX();
  int nbiny = h2d_correl->GetNbinsY();
  const int nbinmx=100;
  if (nbinx>nbinmx || nbiny > nbinmx) {
    cout <<"Increase nbinmx, which is "<< nbinmx<<" in subtract_background"<<endl;
    cout <<"Reconstructed objects are not pedestal subtracted"<<endl;
    return 0;
  }
  double totalgen[nbinmx]={0.};
  double totalreco[nbinmx]={0.};
  if (jk==0) {
    for (int ix=0; ix<nbinx+1; ix++) {
      for (int iy=0; iy<nbiny+1; iy++) {
	if (ix==0/*nbinx*/ && iy==0/*nbiny*/) continue;
	totalreco[ix] +=h2d_correl->GetBinContent(ix, iy);
	if (iy==0) fakerate[ix] =h2d_correl->GetBinContent(ix,iy);
	
	totalgen[iy] +=h2d_correl->GetBinContent(ix, iy);
	if (ix==0) effi[iy] =h2d_correl->GetBinContent(ix, iy);
	      //cout <<"fake & effi ix "<< ix<<" "<<iy<<" "<<h2d_correl->GetBinContent(ix+1, iy+1)<<" "<<totalgen[iy]<<" "<<fakerate[ix]<<" "<<totalreco[ix]<<" "<<effi[iy]<<endl;
	
	if (ix==0 || iy==0) {
	  h2d_correl->SetBinContent(ix, iy, 0.0);
	  h2d_correl->SetBinError(ix, iy, 0.0);
	}
      }
    }
    
    for (int iy=1; iy<nbiny+1; iy++) {
      effi[iy-1] = (totalgen[iy] - effi[iy])/max(1.0, totalgen[iy]);
      if (effi[iy-1]<1.e-3) effi[iy-1]=1.e-3;
    }
    for (int ix=1; ix<nbinx+1; ix++){
       //  cout <<"fake "<< ix<<" "<< fakerate[ix]<<" "<<totalreco[ix]<<" "<<mc1->GetBinContent(ix+1)<<" "<<mc2->GetBinContent(ix+1)<<" "<<mc1->GetBinError(ix+1)<<" "<<mc2->GetBinError(ix+1)<<endl;
      fakerate[ix-1] /=max(1.0, totalreco[ix]);
    }
  }

  if (pedsub) { 
    for (int ix=0; ix<nbinx; ix++) {
      if (jk<6) { 
	mc1->SetBinContent(ix+1, (1.- fakerate[ix])*mc1->GetBinContent(ix+1));
	mc1->SetBinError(ix+1, (1.- fakerate[ix])*mc1->GetBinError(ix+1));

	if (nfiles>=3) { 
	  mc2->SetBinContent(ix+1, (1.- fakerate[ix])*mc2->GetBinContent(ix+1));
	  mc2->SetBinError(ix+1, (1.- fakerate[ix])*mc2->GetBinError(ix+1));
	}	

	if (nfiles>=4) {
	  mc3->SetBinContent(ix+1, (1.- fakerate[ix])*mc3->GetBinContent(ix+1));
	  mc3->SetBinError(ix+1, (1.- fakerate[ix])*mc3->GetBinError(ix+1));
	}	
      } 
    /*  if (jk==0 || jk==6 || jk==7) {
	data->SetBinContent(ix+1, (1.- fakerate[ix])*data->GetBinContent(ix+1));
	data->SetBinError(ix+1, (1.- fakerate[ix])*data->GetBinError(ix+1));
      }*/
    }
  }
  return 1;
}


void fill_histogramme(int lm, int jk, int mn, int nmcfill,int jes) {
  // lm : input file number
  // jk : algo_no
  // mn : jetetamn
  // nmcfill : fill Geninformation only once for two algorithms
  // jes : nextraUnfold 

  char histname[100];
  fileInput[lm]->cd();

  //  Only Reco input;
if(lm==0){

  sprintf(histname,"mcjets/JetpT_%s_EtaBin%i_JES%i",JetRad[jk], mn+1,jes);
  }
else {
  sprintf(histname,"JetpT_%s_EtaBin%i",JetRad[jk], mn+1); 
  }
  
  cout<<jk<<" "<<lm<<" name "<<histname<<endl ; 

  tmphist2 = (TH1D*)fileInput[lm]->Get(histname);
  tmphist2x = (TH1D*)tmphist2->Clone();


  namex = tmphist2x->GetName();
  sprintf(namey, "%s_%s", namex,modelname[lm]);
  tmphist2x->SetName(namey);
  titlex = tmphist2x->GetTitle();
  sprintf(titley, "%s_%s", namex,titlex);
  tmphist2x->SetTitle(titley);

  h_recoinput[lm] = (TH1D*)/*tmphist2x->Clone();*/rebin_hist(tmphist2x,mn);
  h_recoinputwobkgsub[lm] = (TH1D*)h_recoinput[lm]->Clone();
  
  cout<<"bkg subtracted mean "<<h_recoinputwobkgsub[lm]->GetMean()<<" name "<<h_recoinputwobkgsub[lm]->GetName()<<endl;
  //Generated input

  if (lm>0 && nmcfill==0) { //Only for MC and and only once for two jet types
    sprintf(histname, "Gen_MC_JetpT_%s_EtaBin%i",JetRad[jk], mn+1);//"JetpT_%s_EtaBin%i",JetRad[jk], mn+1);
    tmphist1 = (TH1D*)fileInput[lm]->Get(histname);
    tmphist1x = (TH1D*)tmphist1->Clone();

    namex = tmphist1x->GetName();
    sprintf(namey, "%s_%s", modelname[lm], namex);
    tmphist1x->SetName(namey);
    titlex = tmphist1x->GetTitle();
    sprintf(titley, "%s_%s", modelname[lm], titlex);
    tmphist1x->SetTitle(titley);
  
    h_mcgeninput[lm] = (TH1D*)/*tmphist1x->Clone();*/rebin_hist(tmphist1x,mn);
  }
  //Response matrix;

  if (lm==indexx) { //2d only from PFjet
    
    sprintf(histname, "RecoJetvsGenJet_Algo%i_EtabBin%i",jk+1,mn+1);
    
    cout<<jk<<" "<<lm<<" "<<histname<<endl;
    
    h2d_mccorrel = (TH2D*)/*fileInput[lm]->Get(histname) ;*/rebin_hist2d((TH2D*)fileInput[lm]->Get(histname));//, 0, kl);
    
  //  h2d_mccorrel->Draw();
    
    //cout<<"In histfill, nbinx "<<h2d_mccorrel->GetNbinsX()<<endl ;
  
  }

  if (tmphist1) { delete tmphist1; tmphist1=0;}
  if (tmphist1x) { delete tmphist1x; tmphist1x=0;}
  
  //if (tmphist2) { delete tmphist2; tmphist2=0;}
  //if (tmphist2x) { delete tmphist2x; tmphist2x=0;}
}


void fill_genhistogramme(int lm, int kl, int mn) {
  // lm : input file number
  // ij : jetptbn
  // mn : jetetamn
  // kl : Index of eventshape variables, for the time being, 3 or 6
  
  char histname[100];
  fileInput[nfiles+lm]->cd();
  
  sprintf(histname, "Gen_MC_JetpT_%s_EtaBin%i", JetRad[kl],mn+1);
  tmphist1 = (TH1D*)fileInput[nfiles+lm]->Get(histname);
  tmphist1x = (TH1D*)tmphist1->Clone();
  
  namex = tmphist1x->GetName();
  sprintf(namey, "%s_%s", genmodelname[lm], namex);
  tmphist1x->SetName(namey);
  titlex = tmphist1x->GetTitle();
  sprintf(titley, "%s_%s", genmodelname[lm], titlex);
  tmphist1x->SetTitle(titley);
 
  h_mcgeninput[nfiles] = /*(TH1D*)tmphist1x->Clone();*/rebin_hist(tmphist1x/*, kl*/,mn);

  cout<<"gen pt mean "<<h_mcgeninput[nfiles]->GetMean()<<endl ;
/*  
  sprintf(histname, "RecoJetvsGenJet_algo%i_EtaBin%i",kl+1,mn+1);
    
  h2d_mccorrel = rebin_hist2d((TH2D*)fileInput[lm]->Get(histname), ij, kl);
  */
  
  if (tmphist1) { delete tmphist1; tmphist1=0;}
  if (tmphist1x) { delete tmphist1x; tmphist1x=0;}
  
}


void hist_labels(TH1D* hist, int icol) {

  hist->GetXaxis()->SetTitleFont(42);
  hist->GetXaxis()->SetLabelFont(42);
  hist->GetXaxis()->SetLabelSize(0.08);
  hist->GetXaxis()->SetLabelOffset(.01);

  hist->GetYaxis()->SetTitleFont(42);
  hist->GetYaxis()->SetLabelFont(42);
  hist->GetYaxis()->SetLabelSize(0.08);
  hist->GetYaxis()->SetLabelOffset(.01);

  hist->SetMarkerColor(icol);
  hist->SetMarkerStyle(22+icol);
  hist->SetMarkerSize(0.44);
}

int main()
{

  gStyle->SetPaintTextFormat("5.2e"); //4.1f    
  
  gStyle->SetOptLogx(1);
  gStyle->SetOptLogy(1);  
  gStyle->SetTitleFillColor(10);
  gStyle->SetStatColor(10);
  
  gStyle->SetCanvasColor(10);
  gStyle->SetOptStat(0); //1110);
  gStyle->SetOptTitle(1);

  gStyle->SetTitleW(.96);
  gStyle->SetTitleH(.06);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(.02);
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleColor(10);
  gStyle->SetTitleOffset(-0.05);
  gStyle->SetTitleBorderSize(0); //1);
  gStyle->SetTitleFontSize(0.10);

  gStyle->SetPalette(1,0);
  gStyle->SetPadColor(10);
  gStyle->SetPadBorderMode(0);
  gStyle->SetStatColor(10);
  gStyle->SetPadBorderMode(0);
  gStyle->SetStatBorderSize(1);

  gStyle->SetStatStyle(1001);
  gStyle->SetOptFit(101);
  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);

  gStyle->SetStatX(.99);
  gStyle->SetStatY(.99);
  gStyle->SetStatW(.45);
  gStyle->SetStatH(.16);
  gStyle->SetLabelSize(0.095,"XY");  
  gStyle->SetLabelOffset(0.21,"XYZ");
  gStyle->SetTitleSize(0.065,"XY");  
  gStyle->SetTitleOffset(0.06,"XYZ");
  gStyle->SetPadTopMargin(0.075); 
  gStyle->SetPadBottomMargin(0.075);
  gStyle->SetPadLeftMargin(0.09);
  gStyle->SetPadRightMargin(0.02);
  /*  gStyle->SetPadGridX(1);
    gStyle->SetPadGridY(1);
    gStyle->SetGridStyle(3);
    gStyle->SetNdivisions(606,"XY"); */

  gStyle->SetMarkerSize(0.44);
  gStyle->SetMarkerColor(2);
  gStyle->SetMarkerStyle(20);
  
  char mcrootfile[100];
  char datarootfile[100];
  char hist_mc[100];
  char hist_reco[100];
  char hist_unfol[100];

  //Number of iterations/regularisation paramters in bayes and SVD 
  double dataerr[100]; //be sure that 
  double datval[100]; 
  double mxdaterr=0.0;
  double relsumerr=0.0;
  double relsum2err=0.0;
  
  int    mxdatbin=-1;
  TCanvas *c1;
  
  TCanvas *c2[4];
  for(int ic=0; ic<4; ic++){
	  sprintf(namey,"Plot_%i",ic);
	  c2[ic] = new TCanvas(namey,namey,800,650);
	  }
  
  sprintf(titley, "unfold_systematics");  
  sprintf(namey, "outfile_%s_%s.root", titley,modelname[indexx]);
  
  TFile* fileOut = new TFile(namey, "recreate");
  
  sprintf(namey, "outfile%s.ps", titley);
  TPostScript ps(namey, 111); // "outfilex.ps",111);  
  ps.Range(20,30); //ps.Range(10,20);
  ps.NewPage();  
  
   for (int ij=0; ij<nfiles; ij++) {
    fileInput[ij] = new TFile(rootname[ij], "read");
  }
  for (int ij=0; ij<ngenfiles; ij++) {
    fileInput[nfiles+ij] = new TFile(genrootname[ij], "read");
  }
  
  char histname[100];
  char histname2[100];
  
  TH1F *hist_org[nalgo][netarange] ;
  TH1F *hist_data[nalgo][netarange] ;

  
  char odname[100], evname[100], padmcname[100];
  
  
  
  for(int ij=0; ij<nalgo; ij++){
   for (int mn=0; mn<netarange ; mn++) {
	   
	   int natype=0; //fill Geninformation only once for four algorithm
	   
		nxmod2 =-1;
		RooUnfoldResponse response;
	   
		double fakerate[100]={0.};     //This array size should be larger than histograme bin size
		double efficiency[100]={0};
		
		for(int ef=0;ef<100;ef++){
			efficiency[ef] = 1.0 ;
			}
		
		int niterdata=-1;

   //            fileOut->cd();
	
		for (int jk=0; jk<nextraUnfold+1; jk++) {
		for (int lm=0; lm<nfiles; lm++) {
			fill_histogramme(lm,ij,mn,0,jk/*,natype*/);
                       if((lm==0)&&(jk==1)) { hist_data[ij][mn] = (TH1F*)h_recoinput[lm]->Clone(); }
		}
		
		 if (jk==0) {
	    for (int lm=0; lm<ngenfiles; lm++) {
	         fill_genhistogramme(lm,ij,mn);
	    } 
	  }
////	  natype++;
		
////	   }//for (int jk=0; jk<nextraUnfold+1; jk++)

           cout<<"nxmod2 "<<nxmod2<<endl ;
        
	   
	  int nbinx = h2d_mccorrel->GetNbinsX();
	  int nbiny = h2d_mccorrel->GetNbinsY();
	  
	  //cout<<"nbinx nbiny "<<nbinx<<" "<<nbiny<<endl ;
	  
	  for(int ir=0; ir<h2d_mccorrel->GetNbinsX(); ir++){
		  for(int ic=0; ic<h2d_mccorrel->GetNbinsY(); ic++){
		//	 cout<< h2d_mccorrel->GetBinContent(ir+1,ic+1)<<" " ;
			  }
		 // cout<<endl ;
		  }
	  
	  
	  int isub = subtract_background(h2d_mccorrel,  h_recoinput[0], h_recoinput[1], h_recoinput[2], h_recoinput[3], fakerate, efficiency, 0);
	  
	  cout<<"subtracted \n";
	  
/*	  for(int gg=0; gg<nbinx; gg++){
	  cout<<"fake "<<fakerate[gg]<<"  eff  "<<efficiency[gg]<<endl ;
  }*/
	  
	 // cout<<"index "<<indexx<<" h_mcgeninput name "<<h_mcgeninput[indexx]->GetName()<<" Mean "<<h_mcgeninput[indexx]->GetMean()<<endl ;
	//  cout<<"index "<<indexx<<" h_recoinput name "<<h_recoinput[indexx]->GetName()<<" Mean "<<h_recoinput[indexx]->GetMean()<<endl ;
	  
	    sprintf(namey, "unfold_%s", h_recoinput[indexx]->GetName());
    	    sprintf(titley, "unfold_%s", h_recoinput[indexx]->GetTitle());
	    
	  //  cout<<h_recoinput[indexx]->GetName()<<"  Mean  "<<h_recoinput[indexx]->GetMean()<<" bins "<<h_recoinput[indexx]->GetNbinsX()<<" Integral "<<h_recoinput[indexx]->Integral()<<endl ;
	  //  cout<<h_mcgeninput[indexx]->GetName()<<" Mean "<<h_mcgeninput[indexx]->GetMean()<<" bins "<<h_mcgeninput[indexx]->GetNbinsX()<<" Integral "<<h_mcgeninput[indexx]->Integral()<<endl;
	   
	    response = RooUnfoldResponse(h_recoinput[indexx], h_mcgeninput[indexx], h2d_mccorrel, namey, titley); 
	    
//	    cout<<"response name "<<namey<<endl ;
	  
	  TMatrixD tmatr(h2d_mccorrel->GetNbinsX(), h2d_mccorrel->GetNbinsY()); // just gen_vs_reco matrix
	  
	  for (int ix=0; ix<h2d_mccorrel->GetNbinsX(); ix++) {
	    double xxx = 0;
	    for (int iy=0; iy<h2d_mccorrel->GetNbinsY(); iy++) {
	      tmatr(ix,iy) = h2d_mccorrel->GetBinContent(ix+1,iy+1);
	      xxx +=tmatr(ix,iy);
	    }
	  }
	 
	  TMatrixD tmatrdd(h2d_mccorrel->GetNbinsX(), h2d_mccorrel->GetNbinsY());// probability matrix for error in A^-A^-nu
	  
	  for (int ix=0; ix<h2d_mccorrel->GetNbinsX(); ix++) {
	    for (int iy=0; iy<h2d_mccorrel->GetNbinsY(); iy++) {
	      double scal = h_mcgeninput[indexx]->GetBinContent(iy+1)*efficiency[iy]; //GMA
	      //              cout<<"scal "<<scal<<endl ;
	      tmatrdd(ix,iy) = tmatr(ix,iy)/scal; //GMAA
	      //               if(ix==iy) cout<<"element "<<ix<<" "<<scal<<" "<<tmatrdd(ix,iy)<<endl ;
	      
	 //     cout<<tmatrdd(ix,iy)<<" " ;
	      
	    }
	    
	  //  cout<<endl ;
	  }
	  cout<<"Before inverted\n";
	 
          cout<<"tmatrdd determinant "<<tmatrdd.Determinant()<<endl ;
 
	  tmatrdd.Invert();
	  
	  cout<<"Inverted\n" ;
	  
	  int icount=0;
	 // int nmxxiter = min(nitermx, nbinx+1);
	  
	  int contbayes=0;
	  int contsvd = 0;
	  
	  int start = 1;
	  int iend =  start+1;
////OR
   /////    iend=nmxxiter; start=iend-1;
	  
	   for (int ijk=start; ijk<iend; ijk++) {
		   
		   icount++;
		   
		   const int svdsft = min(9,nxmod2-1) ;
		   double xshft = 0.15;
		   double yshft = 0.12;
		   
	    c1 = new TCanvas("c1", "Statistics and efficiency", 600, 850);
	    c1->Divide(2,5); //(3,2); 
	    int icol=0;
	    TLegend *tleg = new TLegend(xshft, yshft, xshft+0.1,  yshft+0.25, "","brNDC");
	    tleg->SetFillColor(10);
	    tleg->SetTextSize(0.05);
	    tleg->SetBorderSize(0);
	    tleg->SetTextFont(42);

	    TLegend *tleg1 = new TLegend(xshft, yshft, xshft+0.1, yshft+0.25, "","brNDC");
	    tleg1->SetFillColor(10);
	    tleg1->SetTextSize(0.05);
	    tleg1->SetBorderSize(0);
	    tleg1->SetTextFont(42);

	    TLegend *tleg2 = new TLegend(xshft, yshft, xshft+0.1, yshft+0.25, "","brNDC");
	    tleg2->SetFillColor(10);
	    tleg2->SetTextSize(0.05);
	    tleg2->SetBorderSize(0);
	    tleg2->SetTextFont(42);

	    TLegend *tleg7 = new TLegend(.12,0.70,0.25,0.90,"","brNDC");
	    tleg7->SetFillColor(10);
	    tleg7->SetTextSize(0.055);
	    tleg7->SetBorderSize(0);
	    tleg7->SetTextFont(42);

	    TLegend *tleg8 = new TLegend(.12,0.70,0.25,0.90,"","brNDC");
	    tleg8->SetFillColor(10);
	    tleg8->SetTextSize(0.055);
	    tleg8->SetBorderSize(0);
	    tleg8->SetTextFont(42);


	    TMatrixD covmatrixbayes[nfiles];
	    TMatrixD covmatrixsvd[nfiles];
	    
	    mxdaterr=0;
	    int lm=0;
	    
	    for (lm=0; lm<nfiles; lm++) {
	      
	      bool isData = true; //(lm==0) ? true : false;
	      bool isMC = (lm>0) ? true : false;
	      
	      //	      if ( (lm==0 && isData) ||  //For data defaul reco and Energy Scale
	      //		   (lm>0 && isMC)) {  //For MC defaul reco and different smearings
		
		TMatrixD tmatrcowen(h2d_mccorrel->GetNbinsX(), h2d_mccorrel->GetNbinsY()); //Cowen eqn 11.26
		
		TMatrixD tmatrai(h2d_mccorrel->GetNbinsX(), h2d_mccorrel->GetNbinsY()); //for A^-1, eqn 53
		

		icol++; if (icol%5==0) icol++;

		covmatrixsvd[lm].ResizeTo(h2d_mccorrel->GetNbinsX(), h2d_mccorrel->GetNbinsY());
		covmatrixbayes[lm].ResizeTo(h2d_mccorrel->GetNbinsX(), h2d_mccorrel->GetNbinsY());
		
		for (int ix=0; ix<h2d_mccorrel->GetNbinsX(); ix++) {
		  for (int iy=0; iy<h2d_mccorrel->GetNbinsY(); iy++) {
		    tmatrcowen(ix,iy) = 0.0;
		    for (int iz=0; iz<h2d_mccorrel->GetNbinsY(); iz++) { 
		      tmatrcowen(ix,iy) += tmatrdd(ix,iz)*tmatrdd(iy,iz)*h_recoinput[lm]->GetBinContent(iz+1);
		      //		    cout <<"ixxx "<< ix<<" "<<iy<<" "<<iz<<" "<<tmatrcowen(ix,iy)<<" "<< tmatrdd(ix,iz)<<" "<<tmatrdd(iy,iz)<<" "<<h_recoinput[lm]->GetBinContent(iz+1)<<endl;
		    }
		    //		  cout <<tmatrcowen(ix,iy)<<" ";
		  }
		  //		cout<<endl;
		}
		
		for (int ix=0; ix<h2d_mccorrel->GetNbinsX(); ix++) {
		  double scal = h_recoinput[lm]->GetBinError(ix+1); //GMA
		  if (scal<1.e-8) scal = 1.e-8;
		  for (int iy=0; iy<h2d_mccorrel->GetNbinsY(); iy++) {
		    tmatrai(ix,iy) = tmatr(ix,iy)/scal; //GMAA
		    //		  cout<<tmatrai(ix,iy)<<" ";
		  }
		  //		cout<<scal<<" "<<h_recoinput[lm]->GetBinContent(ix+1)<<endl;
		}
		
		TMatrixD aInverse(h2d_mccorrel->GetNbinsX(), h2d_mccorrel->GetNbinsY());
		for (int ix=0; ix<h2d_mccorrel->GetNbinsX(); ix++) {
		  for (int iy=0; iy<h2d_mccorrel->GetNbinsX(); iy++) {
		    aInverse(ix,iy)=0.0;
		    for (int iz=0; iz<h2d_mccorrel->GetNbinsX(); iz++) {
		      aInverse(ix,iy) +=tmatrai(iz,ix)*tmatrai(iz,iy)/(efficiency[ix]*h_mcgeninput[indexx]->GetBinContent(ix+1)*efficiency[iy]*h_mcgeninput[indexx]->GetBinContent(iy+1)); // /Scale/Scale; //GMAA
		      
		      //		    file_out <<"inv "<<iz<<" "<< tmatrai(iz,ix)<<" "<<tmatrai(iz,iy)<<" "<<efficiency[ix]<<" "<<h_mcgeninput[indexx]->GetBinContent(ix+1)<<" "<<efficiency[iy]<<" "<<h_mcgeninput[indexx]->GetBinContent(iy+1)<<" "<<aInverse(ix,iy)<<endl;
		    }
		  }
		}
		cout<<" det = "<<aInverse.Determinant()<<endl;
	
	
	  if (lm>=0) { // Not only for data
		  mxdaterr = 0.0;	
		  relsumerr=0;
		  relsum2err=0;
		  for (int ix=0; ix<h_recoinput[lm]->GetNbinsX(); ix++) {
		    datval[ix] = h_recoinput[lm]->GetBinContent(ix+1);
		    dataerr[ix] = h_recoinput[lm]->GetBinError(ix+1) / max(1.e-6,datval[ix]);
		    if (datval[ix]>0) {
		      relsumerr += dataerr[ix];
		      relsum2err += dataerr[ix]*dataerr[ix];
		    }
		    if (mxdaterr<dataerr[ix]) {
		      mxdaterr = dataerr[ix]; mxdatbin=ix;
		    }
		  }
		}
		
		cout<<"Before Bayes\n" ;
		
		response.Draw();
		
		RooUnfoldBayes unfoldbayes(&response, h_recoinput[lm], /*ijk*/7, false);
		//		RooUnfoldSvd unfoldbayes(&response, h_recoinput[lm], svdsft); //ijk+svdsft); //svdsft; //ijk+svdsft

		//unfoldbayes.SetVerbose(0);
		
		cout<<"After Bayes & Before svd\n";
		
		RooUnfoldSvd unfoldsvd(&response, h_recoinput[lm], svdsft); //ijk+svdsft); //svdsft; //ijk+svdsft
		unfoldsvd.SetVerbose(0);
		
		cout<<"After Svd\n" ;
		
		fileOut->cd() ;
		
		h_unfoldedbayes[lm] = (TH1D*) unfoldbayes.Hreco(RooUnfold::kCovariance)->Clone();
		
	   // h_unfoldedbayes[lm]->Draw();	
		
		cout<<"Bayes into hist\n";
		
	//	cout<<"h_unfoldedbayes[lm] integral "<<h_unfoldedbayes[lm]->Integral()<<endl;
	//	cout<<"h_recoinput[lm] integral "<<h_recoinput[lm]->Integral()<<endl;
		
		h_unfoldedsvd[lm] = (TH1D*) unfoldsvd.Hreco(RooUnfold::kCovariance)->Clone();
		
	//	h_unfoldedsvd[lm] ->Draw() ;
		
		cout<<"Svd into hist\n" ;
		
		cout<<"h_unfoldedsvd[lm] integral "<<h_unfoldedsvd[lm]->Integral()<<endl;
		
		sprintf(namey, "bayes_%s_%s_%s", modelname[lm], JetRad[ij], srcnames[jk]);
		add_nameindex(h_unfoldedbayes[lm], namey);

		sprintf(namey, "svd_%s_%s_%s", modelname[lm], JetRad[ij], srcnames[jk]); //ijk+svdsft); //svdsft; //ijk+svdsft
		add_nameindex(h_unfoldedsvd[lm], namey);
		
		if (lm>=0) {  //Not only for data
		  int nbinsx=h_unfoldedbayes[lm]->GetNbinsX();
		  int nbn=0;
		  double reluerr=0;
		  double relu2err=0;
		  for (int ix=0; ix<nbinsx; ix++) {
		    double bincon = h_unfoldedbayes[lm]->GetBinContent(ix+1);
		    double binerr = h_unfoldedbayes[lm]->GetBinError(ix+1) /max(1.e-6,bincon);
		    
		    if (binerr > dataerr[ix]) nbn++;
	//	    /*file_out*/cout<<"xbayes "/*<<varname[kl]*/<<" "<<ijk<<" "<< ix<<" "<< nbn<<" "<<nbinsx<<" "<<binerr<<" "<< dataerr[ix]<<endl;
		    
		    if (bincon>0) {
		      reluerr +=binerr;
		      relu2err +=binerr*binerr;
		    }
		    
		    //		    file_out <<"ix1 "<<ix<<" "<<h_unfoldedbayes[lm]->GetBinContent(ix+1)<<" "<<datval[ix]<<" "<<h_unfoldedbayes[lm]->GetBinError(ix+1)<<" "<<dataerr[ix]<<endl;
		    //		    if (h_unfoldedbayes[lm]->GetBinError(ix+1)>dataerr[ix]) nbn++;
		  }
		  if (lm==0 ) { 
		      if ( nbn>=nbinsx) contbayes++;
		  }
		  
		////  file_out <<"iter "<<h_unfoldedbayes[lm]->GetName()<<" "<<nbn<<" "<<nbinsx<<" "<<reluerr<<" "<<relsumerr<<" "<<relu2err<<" "<<relsum2err<<endl;
		  
		  nbn=0;
		  reluerr=0;
		  relu2err=0;
		  for (int ix=0; ix<nbinsx; ix++) {
		    double bincon = h_unfoldedsvd[lm]->GetBinContent(ix+1);
		    double binerr = h_unfoldedsvd[lm]->GetBinError(ix+1) /max(1.e-6, bincon);
		    
		    if (binerr > dataerr[ix]) nbn++;
		 ////   file_out<<"xsvd "<<varname[kl]<<" "<< svdsft<<" "<<ix<<" "<< nbn<<" "<<nbinsx<<" "<<binerr<<" "<< dataerr[ix]<<endl;
		    

		    if (bincon>0) {
		      reluerr +=binerr;
		      relu2err +=binerr*binerr;
		    }
		    //		    file_out <<"ix2 "<<ix<<" "<<h_unfoldedsvd[lm]->GetBinContent(ix+1)<<" "<<datval[ix]<<" "<<h_unfoldedsvd[lm]->GetBinError(ix+1)<<" "<<dataerr[ix]<<endl;
		    //		    if (h_unfoldedsvd[lm]->GetBinError(ix+1)>dataerr[ix]) nbn++;
		  }
		  if (lm==0 && nbn>=nbinsx) contsvd++; //put condition only for data
	/////	  file_out <<"iter "<<h_unfoldedsvd[lm]->GetName()<<" "<<nbn<<" "<<nbinsx<<" "<<reluerr<<" "<<relsumerr<<" "<<relu2err<<" "<<relsum2err<<endl;
		  
		}
		
	//	covmatrixsvd[lm] = unfoldsvd.GetPropCov();
	//	covmatrixbayes[lm] = unfoldbayes.GetPropCov();
		
		
		covmatrixsvd[lm] = unfoldsvd.Ereco(RooUnfold::kCovariance);
                covmatrixbayes[lm] = unfoldbayes.Ereco(RooUnfold::kCovariance);
		
		double chisq[19]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
		double chiainv[2]={0.,0.};
		
		if (lm>0) {
			
			chiainv[0] = calc_chisq_sss(h_unfoldedbayes[lm],  h_mcgeninput[lm], aInverse);
			chiainv[1] = calc_chisq_sss(h_unfoldedsvd[lm],  h_mcgeninput[lm], aInverse);
		  
			aInverse.Invert();
			
			calc_chisq(&chisq[3], h_unfoldedbayes[lm], h_mcgeninput[lm]);   
		  calc_chisq_svd(&chisq[6], h_unfoldedsvd[lm], covmatrixsvd[lm], aInverse, h_mcgeninput[lm]);
		  
		  TH1D* h_tmpgen = (TH1D*)h_mcgeninput[lm]->Clone();
		  //		h_tmpgen->Sumw2();
		  normlise_hist(h_tmpgen, h_unfoldedbayes[lm]->Integral());
		  
		  chisq[11] = unfoldbayes.Chi2(h_tmpgen, RooUnfold::kNoError);
		  chisq[12] = unfoldbayes.Chi2(h_tmpgen, RooUnfold::kErrors);
		  chisq[13] = unfoldbayes.Chi2(h_tmpgen, RooUnfold::kCovariance);
		  chisq[14] = unfoldbayes.Chi2(h_tmpgen, RooUnfold::kCovToy);
		  
		  normlise_hist(h_tmpgen, h_unfoldedsvd[lm]->Integral());
		  
		  chisq[15] = unfoldsvd.Chi2(h_tmpgen, RooUnfold::kNoError);
		  chisq[16] = unfoldsvd.Chi2(h_tmpgen, RooUnfold::kErrors);
		  chisq[17] = unfoldsvd.Chi2(h_tmpgen, RooUnfold::kCovariance);
		  chisq[18] = unfoldsvd.Chi2(h_tmpgen, RooUnfold::kCovToy);
			
		} //if (lm>0) 
		
		//	      h_unfoldedbayes[lm]->Scale(1./h_unfoldedbayes[lm]->Integral());
		hist_labels(h_unfoldedbayes[lm], icol);
		
		//	      h_unfoldedsvd[lm]->Scale(1./h_unfoldedsvd[lm]->Integral());
		hist_labels(h_unfoldedsvd[lm], icol);
		
		//	      h_recoinputwobkgsub[lm]->Scale(1./h_recoinputwobkgsub[lm]->Integral());
		hist_labels(h_recoinputwobkgsub[lm], icol);
		
		if (lm>0) { 
		  //		h_mcgeninput[lm]->Scale(1./h_mcgeninput[lm]->Integral());
		  hist_labels(h_mcgeninput[lm], icol);
		}
		
		//double deltax1[3]={0.,0.,0.};
		
		double deltax1[3]={0.,0.,0.};
		//		if (jk==0 || jk==6 || jk==7) {
		  cout <<"icol1 "<<icol<<endl;
		if (icol > 1) {
		  c1->cd(2);
		  gPad->SetLogy(0);
		  rathist2[lm][0] = (TH1D*)h_recoinputwobkgsub[lm]->Clone(); 
		  rathist2[lm][1] = (TH1D*)h_recoinputwobkgsub[!isData]->Clone();

	          rathist2[lm][0]->Scale(1./rathist2[lm][0]->Integral());
		  rathist2[lm][1]->Scale(1./rathist2[lm][1]->Integral());

		  rathist2[lm][0]->Divide(rathist2[lm][1]);
		  
		  TMatrixD cov1; cov1.ResizeTo(0,0);
		  TMatrixD cov2; cov2.ResizeTo(0,0);
		  calc_deltax_cov(deltax1, h_recoinputwobkgsub[lm], h_recoinputwobkgsub[!isData], cov1, cov2);
		  rathist2[lm][0]->SetMaximum(5.0); rathist2[lm][0]->SetMinimum(0.0); 
		  
		  hist_setbins(rathist2[lm][0], lm);
		  
		  if (icol==2) {
		    rathist2[lm][0]->Draw();
		  } else {
		    rathist2[lm][0]->Draw("same:E:x0");
		  }
		}
		
		c1->cd(1);

		
		rathist1[lm][0] = (TH1D*)h_recoinputwobkgsub[lm]->Clone(); 
		rathist1[lm][0]->Scale(1./rathist1[lm][0]->Integral());
		rathist1[lm][0]->SetMaximum(1.18*rathist1[lm][0]->GetMaximum());
		hist_setbins(rathist1[lm][0], lm);
		
		rathist1[lm][0]->SetTile("");
		rathist1[lm][0]->GetXaxis()->SetTitle("Jet #P_{T}");
		rathist1[lm][0]->GetXaxis()->CenetrTitle();
		rathist1[lm][0]->GetXaxis()->SetTitleSize(0.05);
		
		if(jk==2&&lm==0){
			c2[0]->cd();
			if (icol==1) {
		  rathist1[lm][0]->Draw();
		} else {
		  rathist1[lm][0]->Draw("same:E:x0");	
		}
			}
		  
		//		if (lm==0) {
		if (icol==1) {
		  rathist1[lm][0]->Draw();
		} else {
		  rathist1[lm][0]->Draw("same:E:x0");	
		}
		
		if (icount>0) { 
		  if (icol==1) { 
		    sprintf (namey, "%s : %i + %i", modelname[lm], ijk, svdsft);
		  } else {
		    sprintf (namey, "%s : <#Delta>/#chi^2 %g/%g", modelname[lm], deltax1[0], deltax1[1]);
		  }
		  tleg->AddEntry(rathist1[lm][0], namey,"lpfe");
		}
		
		double deltax2[3]={0.,0.,0.};
		
		  cout <<"icol1x "<<icol<<endl;
		  
		  sprintf(evname,"%s_JES%i","ratio_unfbydata",jk);
		  sprintf(padmcname,"%s_JES%i","ratio_mc",jk);
          sprintf(odname,"%s_JES%i","Pt_spec",jk);
  
		  
		if (icol>1) {
		  c1->cd(4);
		  gPad->SetLogy(0);
		  rathist4[lm][0] = (TH1D*)h_unfoldedbayes[lm]->Clone(); 
		  rathist4[lm][1] = (TH1D*)h_unfoldedbayes[!isData]->Clone();
	/////	  file_out<<"4name "<< rathist4[lm][0]->GetName()<<" "<<rathist4[lm][0]->GetTitle()<<endl;
		  rathist4[lm][0]->Scale(1./rathist4[lm][0]->Integral());
		  rathist4[lm][1]->Scale(1./rathist4[lm][1]->Integral());
		  rathist4[lm][0]->Divide(rathist4[lm][1]);
		  
		   add_nameindex(rathist4[lm][0],evname);
		 
		  calc_deltax_cov(deltax2, h_unfoldedbayes[lm],  h_unfoldedbayes[!isData], covmatrixbayes[lm], covmatrixbayes[!isData]);  //need to be open
		  rathist4[lm][0]->SetMaximum(5.0); rathist4[lm][0]->SetMinimum(0.0); 
		  hist_setbins(rathist4[lm][0], lm);
		  rathist4[lm][0]->Draw((icol==2) ? " ":"same:E:x0");
		}	      
		
		c1->cd(3);

		rathist3[lm][0] = (TH1D*)h_unfoldedbayes[lm]->Clone(); 
		///// file_out<<"3name "<< rathist3[lm][0]->GetName()<<" "<<rathist3[lm][0]->GetTitle()<<endl;
		rathist3[lm][0]->Scale(1./rathist3[lm][0]->Integral());
		rathist3[lm][0]->SetMaximum(1.18*rathist3[lm][0]->GetMaximum());
		hist_setbins(rathist3[lm][0], lm);
		
		add_nameindex(rathist3[lm][0],odname);
		   
		if (icol==1) {
		  rathist3[lm][0]->Draw();
		} else {
		  rathist3[lm][0]->Draw("same:E:x0");	
		}
		
		if (icount>0 && icol>1) {
		  sprintf (namey, "<#Delta>/#chi^2 %g/%g", deltax2[0], deltax2[2]);
		  tleg1->AddEntry(rathist3[lm][0], namey,"lpfe");
		}
		
		double deltax3[3]={0.,0.,0.};
		  cout <<"icol2x "<<icol<<endl;
		if (icol>1) {
		  c1->cd(6);
		  gPad->SetLogy(0);
		  rathist6[lm][1] = (TH1D*)h_unfoldedsvd[!isData]->Clone();
		  rathist6[lm][0] = (TH1D*)h_unfoldedsvd[lm]->Clone(); 
		//  file_out<<"6name "<< rathist6[lm][0]->GetName()<<" "<<rathist6[lm][0]->GetTitle()<<endl;
		  rathist6[lm][0]->Scale(1./rathist6[lm][0]->Integral());
		  rathist6[lm][1]->Scale(1./rathist6[lm][1]->Integral());
		  rathist6[lm][0]->Divide(rathist6[lm][1]);
		  
		  add_nameindex(rathist6[lm][0],evname);
		
		  calc_deltax_cov(deltax3, h_unfoldedsvd[lm],  h_unfoldedsvd[!isData], covmatrixsvd[lm], covmatrixsvd[!isData]);  
		  
		  
		 rathist6[lm][0]->SetMaximum(5.0); rathist6[lm][0]->SetMinimum(0.0); 
		  hist_setbins(rathist6[lm][0], lm);
		  rathist6[lm][0]->SetTile("");
		  rathist6[lm][0]->GetXaxis()->SetTitle("Jet #P_{T}");
		  rathist6[lm][0]->GetXaxis()->CenetrTitle();
		  rathist6[lm][0]->GetXaxis()->SetTitleSize(0.05);
		  
		  if(jk==2&&lm==0){
			c2[1]->cd();
			if (icol==2) {
		  rathist6[lm][0]->Draw();
		} else {
		  rathist6[lm][0]->Draw("same:E:x0");	
		}
			}
		  
		  if (icol==2) {
		    rathist6[lm][0]->Draw();
		  } else {
		    rathist6[lm][0]->Draw("same:E:x0");
		  }
		}
			
		c1->cd(5);

		rathist5[lm][0] = (TH1D*)h_unfoldedsvd[lm]->Clone(); 
		rathist5[lm][0]->Scale(1./rathist5[lm][0]->Integral());
		rathist5[lm][0]->SetMaximum(1.18*rathist5[lm][0]->GetMaximum());
		hist_setbins(rathist5[lm][0], lm);
		
		add_nameindex(rathist5[lm][0],odname);
		
		rathist5[lm][0]->SetTile("");
		rathist5[lm][0]->GetXaxis()->SetTitle("Jet #P_{T}");
		rathist5[lm][0]->GetXaxis()->CenetrTitle();
		rathist5[lm][0]->GetXaxis()->SetTitleSize(0.05);
		
		if(jk==2&&lm==0){
			c2[2]->cd();
			if (icol==1) {
		  rathist5[lm][0]->Draw();
		} else {
		  rathist5[lm][0]->Draw("same:E:x0");	
		}
			}
		
		if (icol==1) {
		  rathist5[lm][0]->Draw();
		} else {
		  rathist5[lm][0]->Draw("same:E:x0");	
		}
		
		if (icount>0 && lm>0) {
		  sprintf (namey, "<#Delta>/#chi^2 %g/%g", deltax3[0], deltax3[2]);
		  tleg2->AddEntry(rathist5[lm][0], namey,"lpfe");
		}
		
		if(jk==0){
		
		double deltax7[3]={0.,0.,0.};
		double deltax8[3]={0.,0.,0.};
		cout <<"icol3x "<<icol<<endl;
		if (icol>1) {
		  c1->cd(7);
		  gPad->SetLogy(0) ;
                  		  
		  rathist7[lm][0] = (TH1D*)h_unfoldedbayes[lm]->Clone(); 
		/////  file_out<<"7name "<< rathist7[lm][0]->GetName()<<" "<<rathist7[lm][0]->GetTitle()<<endl;
		  rathist7[lm][0]->Scale(1./rathist7[lm][0]->Integral());
		  sprintf(namey, "%s", "rat");
		  add_nameindex(rathist7[lm][0], namey);
		  
		  rathist7[lm][1] = (TH1D*)h_mcgeninput[/*nfiles*/lm]->Clone();
		  //		  for (int iy=0; iy<rathist7[lm][1]->GetNbinsX()+2; iy++) {rathist7[lm][1]->SetBinError(iy, 0.0);}
		  
		  rathist7[lm][1]->Scale(1./rathist7[lm][1]->Integral());
		  rathist7[lm][0]->Divide(rathist7[lm][1]);
		  
		 add_nameindex(rathist7[lm][0],padmcname);
		  
		  //		rathist7[lm][0]->SetMaximum(1.02); rathist7[lm][0]->SetMinimum(0.98); 
//		  rathist7[lm][0]->SetMaximum(1.2); rathist7[lm][0]->SetMinimum(0.8); 
		  
		  TMatrixD cov2; cov2.ResizeTo(0,0);
         	  calc_deltax_cov(deltax7, h_unfoldedbayes[lm], h_mcgeninput[lm], covmatrixbayes[lm], cov2);  //need to be open
		  hist_setbins(rathist7[lm][0], lm);
		  if (icol==2) {
		    rathist7[lm][0]->Draw();
		  } else {
		    rathist7[lm][0]->Draw("same:E:x0");
		  }
		  
		  if (icount>0 && lm>0) {
		    sprintf (namey, "%g/%g/%g", deltax7[0], deltax7[2], int(10.*(chiainv[0]+0.05))/10.);
		    tleg7->AddEntry(rathist7[lm][0], namey,"lpfe");
		  }
		  
		  c1->cd(8);
		  gPad->SetLogy(0) ;		  

		  rathist8[lm][0] = (TH1D*)h_unfoldedsvd[lm]->Clone();
		  rathist8[lm][0]->Scale(1./rathist8[lm][0]->Integral());
		  sprintf(titley, "%s", "rat");
		  add_nameindex(rathist8[lm][0], titley);
		  
		  rathist8[lm][1] = (TH1D*)h_mcgeninput[/*nfiles*/lm]->Clone();

		  rathist8[lm][1]->Scale(1./rathist8[lm][1]->Integral());
		  rathist8[lm][0]->Divide(rathist8[lm][1]);
		 // rathist8[lm][0]->SetMaximum(1.2); rathist8[lm][0]->SetMinimum(0.8); 
		 
		 add_nameindex(rathist4[lm][0],padmcname);
		 
		  cov2.ResizeTo(0,0);

                  if(lm==1) {cout<<"svd madgraph"<<endl ;}

		  calc_deltax_cov(deltax8, h_unfoldedsvd[lm], h_mcgeninput[lm], covmatrixsvd[lm], cov2);
		  hist_setbins(rathist8[lm][0], lm);
		  
		  rathist8[lm][0]->SetTile("");
		  rathist8[lm][0]->GetXaxis()->SetTitle("Jet #P_{T}");
		  rathist8[lm][0]->GetXaxis()->CenetrTitle();
		  rathist8[lm][0]->GetXaxis()->SetTitleSize(0.05);
		  
		  if(jk==2&&lm==0){
			c2[3]->cd();
			if (icol==2) {
		  rathist8[lm][0]->Draw();
		} else {
		  rathist8[lm][0]->Draw("same:E:x0");	
		}
			}
		  
		  if (icol==2) {
		    rathist8[lm][0]->Draw();
		  } else {
		    rathist8[lm][0]->Draw("same:E:x0");
		  }
		  
		  if (icount>0 && lm>0) {
		    sprintf (namey, "%g/%g/%g", deltax8[0], deltax8[2], int(10.*(chiainv[1]+0.05))/10.);
		    tleg8->AddEntry(rathist8[lm][0], namey,"lpfe");
		  }
		}
	}//ij (jk==0)		
			   
		//		   }
		

		if (isMC) {
		  c1->cd(9);
		  
		  convert_errorplot(rathist9[lm][0]= (TH1D*)h_recoinput[lm]->Clone(), icol, 0);
		  rathist10[lm][0] = (TH1D*) rathist9[lm][0]->Clone();	  
		
		  if (lm==0) rathist9[lm][0]->SetMaximum(1.5*rathist9[lm][0]->GetMaximum());
		  
		  rathist9[lm][0]->Draw((icol==1)?"":"same");
		  
		  convert_errorplot(rathist9[lm][1] = (TH1D*)h_unfoldedbayes[lm]->Clone(), icol, 1);
		  rathist9[lm][1]->Draw("same");
		  
		  c1->cd(10);
		  if (lm==0) rathist10[lm][0]->SetMaximum(3.5*rathist10[lm][0]->GetMaximum());
		  rathist10[lm][0]->Draw((icol==1)?"":"same");
		  
		  convert_errorplot(rathist10[lm][1] = (TH1D*)h_unfoldedsvd[lm]->Clone(), icol, 1);
		  rathist10[lm][1]->Draw("same");
		}
	
		} // for (lm=0; lm<nfiles; lm++)
		
	    c1->cd(1); if (icount>0) tleg->Draw();
	    c1->cd(3); if (icount>0) tleg1->Draw();
	    c1->cd(5); if (icount>0) tleg2->Draw();
	    c1->cd(7); if (icount>0) tleg7->Draw();
	    c1->cd(8); if (icount>0) tleg8->Draw();

	    c1->Update();
            ps.NewPage();    

            if (tleg) { delete tleg; tleg=0;}
	    if (tleg1) { delete tleg1; tleg1=0;}
	    if (tleg2) { delete tleg2; tleg2=0;}
	    if (tleg7) { delete tleg7; tleg7=0;}
	    if (tleg8) { delete tleg8; tleg8=0;}
	    if (c1) { delete c1; c1=0;}


            fileOut->cd();
	    
	    for (int lm=0; lm<nfiles; lm++) {
//	      if (h_unfoldedbayes[lm]) h_unfoldedbayes[lm]->Write();
//	      if (h_unfoldedsvd[lm]) h_unfoldedsvd[lm]->Write();
	      if (lm>0) {
		if (rathist7[lm][0]) rathist7[lm][0]->Write();
		if (rathist8[lm][0]) rathist8[lm][0]->Write();
	      }
	    }
	    for (int lm=0; lm<nfiles; lm++) {
/*	      for (int ix=0; ix<2; ix++) {
		if (rathist1[lm][ix]) {delete rathist1[lm][ix]; rathist1[lm][ix] = 0;}
		if (rathist2[lm][ix]) {delete rathist2[lm][ix]; rathist2[lm][ix] = 0;}
		if (rathist3[lm][ix]) {delete rathist3[lm][ix]; rathist3[lm][ix] = 0;}
		if (rathist4[lm][ix]) {delete rathist4[lm][ix]; rathist4[lm][ix] = 0;}
		if (rathist5[lm][ix]) {delete rathist5[lm][ix]; rathist5[lm][ix] = 0;}
		if (rathist6[lm][ix]) {delete rathist6[lm][ix]; rathist6[lm][ix] = 0;}
		if (rathist7[lm][ix]) {delete rathist7[lm][ix]; rathist7[lm][ix] = 0;}
		if (rathist8[lm][ix]) {delete rathist8[lm][ix]; rathist8[lm][ix] = 0;}
		if (rathist9[lm][ix]) {delete rathist9[lm][ix]; rathist9[lm][ix] = 0;}
		if (rathist10[lm][ix]) {delete rathist10[lm][ix]; rathist10[lm][ix] = 0;}

	      }*/
	      if (h_unfoldedbayes[lm]) { delete h_unfoldedbayes[lm]; h_unfoldedbayes[lm]=0;}
	      if (h_unfoldedsvd[lm]) { delete h_unfoldedsvd[lm]; h_unfoldedsvd[lm]=0;}
	    } 
		   
		} //for (int ijk=start; ijk<iend; ijk++)
	} // for (int jk=0; jk<nextraUnfold+1; jk++)	 
	  
           fileOut->cd();
	  if (h2d_mccorrel) h2d_mccorrel->Write();
	  for (int lm=0; lm<2; lm++) {
	    if (h_recoinputwobkgsub[lm]) h_recoinputwobkgsub[lm]->Write();
	  }
            //h_mcgeninput[nfiles]->Write();
		} //for (int mn=etastrt; mn<etastrt+1; mn++)
	}//for(int ij=0; ij<nalgo; ij++)
	
  fileOut->cd();
  fileOut->Write();
  ps.Close();
  fileOut->Close();
  
  for(int ic=0; ic<4;ic++){
  sprintf(namey,"Plot_%i.eps",ic);
  c2[ic]->SaveAs(namey);
  }
}

