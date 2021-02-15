//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 30 23:46:48 2018 by ROOT version 5.34/36
// from TTree T1/PFandGenJets
// found on file: root://se01.indiacms.res.in//store/user/chatterj/JetHT/crab_RChoice_Data_2016G_LegacyReReco/180501_204624/0000/rootuple_RecoJetchs_PU_Data_2016_JetHT_109.root
//////////////////////////////////////////////////////////

#ifndef suman_rscan_h
#define suman_rscan_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TVector.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <fstream>
#include <TProofOutputFile.h>
#include <iostream>
#include <fstream>
#include <TRandom3.h>
#include "TSystem.h"
#include "boost/config.hpp"
#include "boost/lexical_cast.hpp"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
int* dec2bin(int dec)
{
const int length = 10;//nHLTmx;
int input = dec;
int istep=0;
int div[length] = {0};
while(input>0){
  input = input/2;
  div[istep] = input%2;
  istep++;
 }

static int binary[10]; //nHLTmx

for(int ij=1; ij<(length+1); ij++){
 binary[ij-1] = div[length-ij];
 }
return binary;
}

Double_t pol5(Double_t* x, Double_t* par){
return (par[5]*pow(x[0],-2)+par[4]*pow(x[0],-1)+par[3]*pow(x[0],3)+par[2]*pow(x[0],2)+par[1]*pow(x[0],1)+par[0]);
}

int getbinid(double val, int nbmx, double* array) {
  if (val<array[0]) return -2;
  for (int ix=0; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -3;
}

double theta_to_eta(double theta) { return -log(tan(theta/2.)); }

double PhiInRange(const double& phi) {
  double phiout = phi;

  if( phiout > 2*M_PI || phiout < -2*M_PI) {
    phiout = fmod( phiout, 2*M_PI);
  }
  if (phiout <= -M_PI) phiout += 2*M_PI;
  else if (phiout >  M_PI) phiout -= 2*M_PI;

  return phiout;
}

double delta2R(double eta1, double phi1, double eta2, double phi2) {
  return sqrt(pow(eta1 - eta2,2) +pow(PhiInRange(phi1 - phi2),2));
}

class suman_rscan : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   TRandom3* gRandom3 = new TRandom3();

   // Declaration of leaf types
   Int_t           irun;
   Int_t           ilumi;
   UInt_t          ievt;
   Int_t           nprim;
   Double_t        Rho;
   Double_t        event_weight;
   Int_t           trig_value;
   Bool_t          ihlt01;
   Bool_t          ihlt02;
   Bool_t          ihlt03;
   Bool_t          ihlt04;
   Bool_t          ihlt05;
   Bool_t          ihlt06;
   Bool_t          ihlt07;
   Bool_t          ihlt08;
   Bool_t          ihlt09;
   Bool_t          ihlt10;
   Float_t         PFMET;
   Float_t         PFMETPhi;
   Float_t         sumEt;
   Float_t         miset;
   Float_t		   misphi;
   Int_t           nvert;
   Int_t           nchict;
   Int_t 		   npu_vert;
   Float_t 		   pthat;
   
   Float_t minPFPt; 
   static const int njetmx =20;
   
   Float_t tot_weight;
   
   Int_t           npfjets01;
   Float_t         pfjetpT01[njetmx];   //[npfjets01]
   Float_t         pfjetpTup01[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn01[njetmx];   //[npfjets01]
   Float_t         pfjetarea01[njetmx];   //[npfjets01]
   Float_t         pfjety01[njetmx];   //[npfjets01]
   Float_t         pfjetphi01[njetmx];   //[npfjets01]
   Float_t         pfjetenr01[njetmx];   //[npfjets01]
   Bool_t          pfjettightID01[njetmx];   //[npfjets01]
   Bool_t          pfjetlooseID01[njetmx];   //[npfjets01]
   Float_t         pfjetJEC01[njetmx];   //[npfjets01]
   Float_t         pfjetJECL101[njetmx];   //[npfjets01]
   Float_t 		   pfjetJECL201[njetmx];   //[npfjets01]
   Float_t 		   pfjetJECL2L301[njetmx];   //[npfjets01]
   Float_t         pfjetCHF01[njetmx];   //[npfjets01]
   Float_t         pfjetNHF01[njetmx];   //[npfjets01]
   Float_t         pfjetCHM01[njetmx];   //[npfjets01]
   Float_t         pfjetNEMF01[njetmx];   //[npfjets01]
   Float_t         pfjettotnum01[njetmx];   //[npfjets01]
   Float_t         pfjetneunum01[njetmx];   //[npfjets01]
   Float_t         pfjetwidth01[njetmx];   //[npfjets01]
   Int_t		   ngenjets01;
   Int_t 		   genjetmul01[njetmx];
   Float_t         genjetenr01[njetmx]; 
   Float_t         genjetpT01[njetmx]; 
   Float_t         genjetarea01[njetmx];
   Float_t         genjety01[njetmx];
   Float_t         genjetphi01[njetmx];
   Double_t        trig_weight01;
   Int_t           npfjets02;
   Float_t         pfjetpT02[njetmx];   //[npfjets02]
   Float_t         pfjetpTup02[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn02[njetmx];   //[npfjets01]
   Float_t         pfjetarea02[njetmx];   //[npfjets02]
   Float_t         pfjety02[njetmx];   //[npfjets02]
   Float_t         pfjetphi02[njetmx];   //[npfjets02]
   Float_t         pfjetenr02[njetmx];   //[npfjets02]
   Bool_t          pfjettightID02[njetmx];   //[npfjets02]
   Bool_t          pfjetlooseID02[njetmx];   //[npfjets02]
   Float_t         pfjetJEC02[njetmx];   //[npfjets02]
   Float_t         pfjetJECL102[njetmx];   //[npfjets02]
   Float_t 		   pfjetJECL202[njetmx];   //[npfjets02]
   Float_t 		   pfjetJECL2L302[njetmx];   //[npfjets02]
   Float_t         pfjetCHF02[njetmx];   //[npfjets02]
   Float_t         pfjetNHF02[njetmx];   //[npfjets02]
   Float_t         pfjetCHM02[njetmx];   //[npfjets02]
   Float_t         pfjetNEMF02[njetmx];   //[npfjets02]
   Float_t         pfjettotnum02[njetmx];   //[npfjets02]
   Float_t         pfjetneunum02[njetmx];   //[npfjets02]
   Float_t         pfjetwidth02[njetmx];   //[npfjets02]
   Int_t		   ngenjets02;
   Int_t 		   genjetmul02[njetmx];
   Float_t         genjetenr02[njetmx]; 
   Float_t         genjetpT02[njetmx]; 
   Float_t         genjetarea02[njetmx];
   Float_t         genjety02[njetmx];
   Float_t         genjetphi02[njetmx];
   Double_t        trig_weight02;
   Int_t           npfjets03;
   Float_t         pfjetpT03[njetmx];   //[npfjets03]
   Float_t         pfjetpTup03[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn03[njetmx];   //[npfjets01]
   Float_t         pfjetarea03[njetmx];   //[npfjets03]
   Float_t         pfjety03[njetmx];   //[npfjets03]
   Float_t         pfjetphi03[njetmx];   //[npfjets03]
   Float_t         pfjetenr03[njetmx];   //[npfjets03]
   Bool_t          pfjettightID03[njetmx];   //[npfjets03]
   Bool_t          pfjetlooseID03[njetmx];   //[npfjets03]
   Float_t         pfjetJEC03[njetmx];   //[npfjets03]
   Float_t         pfjetJECL103[njetmx];   //[npfjets03]
   Float_t 		   pfjetJECL203[njetmx];   //[npfjets03]
   Float_t 		   pfjetJECL2L303[njetmx];   //[npfjets03]
   Float_t         pfjetCHF03[njetmx];   //[npfjets03]
   Float_t         pfjetNHF03[njetmx];   //[npfjets03]
   Float_t         pfjetCHM03[njetmx];   //[npfjets03]
   Float_t         pfjetNEMF03[njetmx];   //[npfjets03]
   Float_t         pfjettotnum03[njetmx];   //[npfjets03]
   Float_t         pfjetneunum03[njetmx];   //[npfjets03]
   Float_t         pfjetwidth03[njetmx];   //[npfjets03]
   Int_t		   ngenjets03;
   Int_t 		   genjetmul03[njetmx];
   Float_t         genjetenr03[njetmx]; 
   Float_t         genjetpT03[njetmx]; 
   Float_t         genjetarea03[njetmx];
   Float_t         genjety03[njetmx];
   Float_t         genjetphi03[njetmx];
   Double_t        trig_weight03;
   Int_t           npfjets04;
   Float_t         pfjetpT04[njetmx];   //[npfjets04]
   Float_t         pfjetpTup04[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn04[njetmx];   //[npfjets01]
   Float_t         pfjetarea04[njetmx];   //[npfjets04]
   Float_t         pfjety04[njetmx];   //[npfjets04]
   Float_t         pfjetphi04[njetmx];   //[npfjets04]
   Float_t         pfjetenr04[njetmx];   //[npfjets04]
   Bool_t          pfjettightID04[njetmx];   //[npfjets04]
   Bool_t          pfjetlooseID04[njetmx];   //[npfjets04]
   Float_t         pfjetJEC04[njetmx];   //[npfjets04]
   Float_t         pfjetJECL104[njetmx];   //[npfjets04]
   Float_t 		   pfjetJECL204[njetmx];   //[npfjets04]
   Float_t 		   pfjetJECL2L304[njetmx];   //[npfjets04]
   Float_t         pfjetCHF04[njetmx];   //[npfjets04]
   Float_t         pfjetNHF04[njetmx];   //[npfjets04]
   Float_t         pfjetCHM04[njetmx];   //[npfjets04]
   Float_t         pfjetNEMF04[njetmx];   //[npfjets04]
   Float_t         pfjettotnum04[njetmx];   //[npfjets04]
   Float_t         pfjetneunum04[njetmx];   //[npfjets04]
   Float_t         pfjetwidth04[njetmx];   //[npfjets04]
   Int_t		   ngenjets04;
   Int_t 		   genjetmul04[njetmx];
   Float_t         genjetenr04[njetmx]; 
   Float_t         genjetpT04[njetmx]; 
   Float_t         genjetarea04[njetmx];
   Float_t         genjety04[njetmx];
   Float_t         genjetphi04[njetmx];
   Double_t        trig_weight04;
   Int_t           npfjets05;
   Float_t         pfjetpT05[njetmx];   //[npfjets05]
   Float_t         pfjetpTup05[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn05[njetmx];   //[npfjets01]
   Float_t         pfjetarea05[njetmx];   //[npfjets05]
   Float_t         pfjety05[njetmx];   //[npfjets05]
   Float_t         pfjetphi05[njetmx];   //[npfjets05]
   Float_t         pfjetenr05[njetmx];   //[npfjets05]
   Bool_t          pfjettightID05[njetmx];   //[npfjets05]
   Bool_t          pfjetlooseID05[njetmx];   //[npfjets05]
   Float_t         pfjetJEC05[njetmx];   //[npfjets05]
   Float_t         pfjetJECL105[njetmx];   //[npfjets05]
   Float_t 		   pfjetJECL205[njetmx];   //[npfjets05]
   Float_t 		   pfjetJECL2L305[njetmx];   //[npfjets05]
   Float_t         pfjetCHF05[njetmx];   //[npfjets05]
   Float_t         pfjetNHF05[njetmx];   //[npfjets05]
   Float_t         pfjetCHM05[njetmx];   //[npfjets05]
   Float_t         pfjetNEMF05[njetmx];   //[npfjets05]
   Float_t         pfjettotnum05[njetmx];   //[npfjets05]
   Float_t         pfjetneunum05[njetmx];   //[npfjets05]
   Float_t         pfjetwidth05[njetmx];   //[npfjets05]
   Int_t		   ngenjets05;
   Int_t 		   genjetmul05[njetmx];
   Float_t         genjetenr05[njetmx]; 
   Float_t         genjetpT05[njetmx]; 
   Float_t         genjetarea05[njetmx];
   Float_t         genjety05[njetmx];
   Float_t         genjetphi05[njetmx];
   Double_t        trig_weight05;
   Int_t           npfjets06;
   Float_t         pfjetpT06[njetmx];   //[npfjets06]
   Float_t         pfjetpTup06[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn06[njetmx];   //[npfjets01] 
   Float_t         pfjetarea06[njetmx];   //[npfjets06]
   Float_t         pfjety06[njetmx];   //[npfjets06]
   Float_t         pfjetphi06[njetmx];   //[npfjets06]
   Float_t         pfjetenr06[njetmx];   //[npfjets06]
   Bool_t          pfjettightID06[njetmx];   //[npfjets06]
   Bool_t          pfjetlooseID06[njetmx];   //[npfjets06]
   Float_t         pfjetJEC06[njetmx];   //[npfjets06]
   Float_t         pfjetJECL106[njetmx];   //[npfjets06]
   Float_t 		   pfjetJECL206[njetmx];   //[npfjets06]
   Float_t 		   pfjetJECL2L306[njetmx];   //[npfjets06]
   Float_t         pfjetCHF06[njetmx];   //[npfjets06]
   Float_t         pfjetNHF06[njetmx];   //[npfjets06]
   Float_t         pfjetCHM06[njetmx];   //[npfjets06]
   Float_t         pfjetNEMF06[njetmx];   //[npfjets06]
   Float_t         pfjettotnum06[njetmx];   //[npfjets06]
   Float_t         pfjetneunum06[njetmx];   //[npfjets06]
   Float_t         pfjetwidth06[njetmx];   //[npfjets06]
   Int_t		   ngenjets06;
   Int_t 		   genjetmul06[njetmx];
   Float_t         genjetenr06[njetmx]; 
   Float_t         genjetpT06[njetmx]; 
   Float_t         genjetarea06[njetmx];
   Float_t         genjety06[njetmx];
   Float_t         genjetphi06[njetmx];
   Double_t        trig_weight06;
   Int_t           npfjets07;
   Float_t         pfjetpT07[njetmx];   //[npfjets07]
   Float_t         pfjetpTup07[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn07[njetmx];   //[npfjets01] 
   Float_t         pfjetarea07[njetmx];   //[npfjets07]
   Float_t         pfjety07[njetmx];   //[npfjets07]
   Float_t         pfjetphi07[njetmx];   //[npfjets07]
   Float_t         pfjetenr07[njetmx];   //[npfjets07]
   Bool_t          pfjettightID07[njetmx];   //[npfjets07]
   Bool_t          pfjetlooseID07[njetmx];   //[npfjets07]
   Float_t         pfjetJEC07[njetmx];   //[npfjets07]
   Float_t         pfjetJECL107[njetmx];   //[npfjets07]
   Float_t 		   pfjetJECL207[njetmx];   //[npfjets07]
   Float_t 		   pfjetJECL2L307[njetmx];   //[npfjets07]
   Float_t         pfjetCHF07[njetmx];   //[npfjets07]
   Float_t         pfjetNHF07[njetmx];   //[npfjets07]
   Float_t         pfjetCHM07[njetmx];   //[npfjets07]
   Float_t         pfjetNEMF07[njetmx];   //[npfjets07]
   Float_t         pfjettotnum07[njetmx];   //[npfjets07]
   Float_t         pfjetneunum07[njetmx];   //[npfjets07]
   Float_t         pfjetwidth07[njetmx];   //[npfjets07]
   Int_t		   ngenjets07;
   Int_t 		   genjetmul07[njetmx];
   Float_t         genjetenr07[njetmx]; 
   Float_t         genjetpT07[njetmx]; 
   Float_t         genjetarea07[njetmx];
   Float_t         genjety07[njetmx];
   Float_t         genjetphi07[njetmx];
   Double_t        trig_weight07;
   Int_t           npfjets08;
   Float_t         pfjetpT08[njetmx];   //[npfjets08]
   Float_t         pfjetpTup08[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn08[njetmx];   //[npfjets01] 
   Float_t         pfjetarea08[njetmx];   //[npfjets08]
   Float_t         pfjety08[njetmx];   //[npfjets08]
   Float_t         pfjetphi08[njetmx];   //[npfjets08]
   Float_t         pfjetenr08[njetmx];   //[npfjets08]
   Bool_t          pfjettightID08[njetmx];   //[npfjets08]
   Bool_t          pfjetlooseID08[njetmx];   //[npfjets08]
   Float_t         pfjetJEC08[njetmx];   //[npfjets08]
   Float_t         pfjetJECL108[njetmx];   //[npfjets08]
   Float_t 		   pfjetJECL208[njetmx];   //[npfjets08]
   Float_t 		   pfjetJECL2L308[njetmx];   //[npfjets08]
   Float_t         pfjetCHF08[njetmx];   //[npfjets08]
   Float_t         pfjetNHF08[njetmx];   //[npfjets08]
   Float_t         pfjetCHM08[njetmx];   //[npfjets08]
   Float_t         pfjetNEMF08[njetmx];   //[npfjets08]
   Float_t         pfjettotnum08[njetmx];   //[npfjets08]
   Float_t         pfjetneunum08[njetmx];   //[npfjets08]
   Float_t         pfjetwidth08[njetmx];   //[npfjets08]
   Int_t		   ngenjets08;
   Int_t 		   genjetmul08[njetmx];
   Float_t         genjetenr08[njetmx]; 
   Float_t         genjetpT08[njetmx]; 
   Float_t         genjetarea08[njetmx];
   Float_t         genjety08[njetmx];
   Float_t         genjetphi08[njetmx];
   Double_t        trig_weight08;
   Int_t           npfjets09;
   Float_t         pfjetpT09[njetmx];   //[npfjets09]
   Float_t         pfjetpTup09[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn09[njetmx];   //[npfjets01] 
   Float_t         pfjetarea09[njetmx];   //[npfjets09]
   Float_t         pfjety09[njetmx];   //[npfjets09]
   Float_t         pfjetphi09[njetmx];   //[npfjets09]
   Float_t         pfjetenr09[njetmx];   //[npfjets09]
   Bool_t          pfjettightID09[njetmx];   //[npfjets09]
   Bool_t          pfjetlooseID09[njetmx];   //[npfjets09]
   Float_t         pfjetJEC09[njetmx];   //[npfjets09]
   Float_t         pfjetJECL109[njetmx];   //[npfjets09]
   Float_t 		   pfjetJECL209[njetmx];   //[npfjets09]
   Float_t 		   pfjetJECL2L309[njetmx];   //[npfjets09]
   Float_t         pfjetCHF09[njetmx];   //[npfjets09]
   Float_t         pfjetNHF09[njetmx];   //[npfjets09]
   Float_t         pfjetCHM09[njetmx];   //[npfjets09]
   Float_t         pfjetNEMF09[njetmx];   //[npfjets09]
   Float_t         pfjettotnum09[njetmx];   //[npfjets09]
   Float_t         pfjetneunum09[njetmx];   //[npfjets09]
   Float_t         pfjetwidth09[njetmx];   //[npfjets09]
   Int_t		   ngenjets09;
   Int_t 		   genjetmul09[njetmx];
   Float_t         genjetenr09[njetmx]; 
   Float_t         genjetpT09[njetmx]; 
   Float_t         genjetarea09[njetmx];
   Float_t         genjety09[njetmx];
   Float_t         genjetphi09[njetmx];
   Double_t        trig_weight09;
   Int_t           npfjets10;
   Float_t         pfjetpT10[njetmx];   //[npfjets10]
   Float_t         pfjetpTup10[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn10[njetmx];   //[npfjets01] 
   Float_t         pfjetarea10[njetmx];   //[npfjets10]
   Float_t         pfjety10[njetmx];   //[npfjets10]
   Float_t         pfjetphi10[njetmx];   //[npfjets10]
   Float_t         pfjetenr10[njetmx];   //[npfjets10]
   Bool_t          pfjettightID10[njetmx];   //[npfjets10]
   Bool_t          pfjetlooseID10[njetmx];   //[npfjets10]
   Float_t         pfjetJEC10[njetmx];   //[npfjets10]
   Float_t         pfjetJECL110[njetmx];   //[npfjets10]
   Float_t 		   pfjetJECL210[njetmx];   //[npfjets10]
   Float_t 		   pfjetJECL2L310[njetmx];   //[npfjets10]
   Float_t         pfjetCHF10[njetmx];   //[npfjets10]
   Float_t         pfjetNHF10[njetmx];   //[npfjets10]
   Float_t         pfjetCHM10[njetmx];   //[npfjets10]
   Float_t         pfjetNEMF10[njetmx];   //[npfjets10]
   Float_t         pfjettotnum10[njetmx];   //[npfjets10]
   Float_t         pfjetneunum10[njetmx];   //[npfjets10]
   Float_t         pfjetwidth10[njetmx];   //[npfjets10]
   Int_t		   ngenjets10;
   Int_t 		   genjetmul10[njetmx];
   Float_t         genjetenr10[njetmx]; 
   Float_t         genjetpT10[njetmx]; 
   Float_t         genjetarea10[njetmx];
   Float_t         genjety10[njetmx];
   Float_t         genjetphi10[njetmx];
   Double_t        trig_weight10;
   Int_t           npfjets11;
   Float_t         pfjetpT11[njetmx];   //[npfjets11]
   Float_t         pfjetpTup11[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn11[njetmx];   //[npfjets01] 
   Float_t         pfjetarea11[njetmx];   //[npfjets11]
   Float_t         pfjety11[njetmx];   //[npfjets11]
   Float_t         pfjetphi11[njetmx];   //[npfjets11]
   Float_t         pfjetenr11[njetmx];   //[npfjets11]
   Bool_t          pfjettightID11[njetmx];   //[npfjets11]
   Bool_t          pfjetlooseID11[njetmx];   //[npfjets11]
   Float_t         pfjetJEC11[njetmx];   //[npfjets11]
   Float_t         pfjetJECL111[njetmx];   //[npfjets11]
   Float_t 		   pfjetJECL211[njetmx];   //[npfjets11]
   Float_t 		   pfjetJECL2L311[njetmx];   //[npfjets11]
   Float_t         pfjetCHF11[njetmx];   //[npfjets11]
   Float_t         pfjetNHF11[njetmx];   //[npfjets11]
   Float_t         pfjetCHM11[njetmx];   //[npfjets11]
   Float_t         pfjetNEMF11[njetmx];   //[npfjets11]
   Float_t         pfjettotnum11[njetmx];   //[npfjets11]
   Float_t         pfjetneunum11[njetmx];   //[npfjets11]
   Float_t         pfjetwidth11[njetmx];   //[npfjets11]
   Int_t		   ngenjets11;
   Int_t 		   genjetmul11[njetmx];
   Float_t         genjetenr11[njetmx]; 
   Float_t         genjetpT11[njetmx]; 
   Float_t         genjetarea11[njetmx];
   Float_t         genjety11[njetmx];
   Float_t         genjetphi11[njetmx];
   Double_t        trig_weight11;
   Int_t           npfjets12;
   Float_t         pfjetpT12[njetmx];   //[npfjets12]
   Float_t         pfjetpTup12[njetmx];   //[npfjets01]
   Float_t         pfjetpTdn12[njetmx];   //[npfjets01] 
   Float_t         pfjetarea12[njetmx];   //[npfjets12]
   Float_t         pfjety12[njetmx];   //[npfjets12]
   Float_t         pfjetphi12[njetmx];   //[npfjets12]
   Float_t         pfjetenr12[njetmx];   //[npfjets12]
   Bool_t          pfjettightID12[njetmx];   //[npfjets12]
   Bool_t          pfjetlooseID12[njetmx];   //[npfjets12]
   Float_t         pfjetJEC12[njetmx];   //[npfjets12]
   Float_t         pfjetJECL112[njetmx];   //[npfjets12]
   Float_t 		   pfjetJECL212[njetmx];   //[npfjets12]
   Float_t 		   pfjetJECL2L312[njetmx];   //[npfjets12]
   Float_t         pfjetCHF12[njetmx];   //[npfjets12]
   Float_t         pfjetNHF12[njetmx];   //[npfjets12]
   Float_t         pfjetCHM12[njetmx];   //[npfjets12]
   Float_t         pfjetNEMF12[njetmx];   //[npfjets12]
   Float_t         pfjettotnum12[njetmx];   //[npfjets12]
   Float_t         pfjetneunum12[njetmx];   //[npfjets12]
   Float_t         pfjetwidth12[njetmx];   //[npfjets12]
   Int_t		   ngenjets12;
   Int_t 		   genjetmul12[njetmx];
   Float_t         genjetenr12[njetmx]; 
   Float_t         genjetpT12[njetmx]; 
   Float_t         genjetarea12[njetmx];
   Float_t         genjety12[njetmx];
   Float_t         genjetphi12[njetmx];
   Double_t        trig_weight12;

   // List of branches
   TBranch        *b_irun;   //!
   TBranch        *b_ilumi;   //!
   TBranch        *b_ievt;   //!
   TBranch        *b_nprim;   //!
   TBranch        *b_Rho;   //!
   TBranch        *b_event_weight;   //!
   TBranch        *b_trig_value;   //!
   TBranch        *b_ihlt01;   //!
   TBranch        *b_ihlt02;   //!
   TBranch        *b_ihlt03;   //!
   TBranch        *b_ihlt04;   //!
   TBranch        *b_ihlt05;   //!
   TBranch        *b_ihlt06;   //!
   TBranch        *b_ihlt07;   //!
   TBranch        *b_ihlt08;   //!
   TBranch        *b_ihlt09;   //!
   TBranch        *b_ihlt10;   //!
   TBranch        *b_miset;   //!
   TBranch        *b_misphi;   //!
   TBranch        *b_sumEt;   //!
   TBranch        *b_nvert;   //!
   TBranch        *b_nchict;   //!
   TBranch        *b_npfjets01;   //!
   TBranch        *b_pfjetpT01;   //!
   TBranch        *b_pfjetarea01;   //!
   TBranch        *b_pfjety01;   //!
   TBranch        *b_pfjetphi01;   //!
   TBranch        *b_pfjetenr01;   //!
   TBranch        *b_pfjettightID01;   //!
   TBranch        *b_pfjetlooseID01;   //!
   TBranch        *b_pfjetJEC01;   //!
   TBranch        *b_pfjetJECL101;   //!
   TBranch        *b_pfjetJECL201;   //!
   TBranch        *b_pfjetJECL2L301;   //!
   TBranch        *b_pfjetCHF01;   //!
   TBranch        *b_pfjetNHF01;   //!
   TBranch        *b_pfjetCHM01;   //!
   TBranch        *b_pfjetNEMF01;   //!
   TBranch        *b_pfjettotnum01;   //!
   TBranch        *b_pfjetneunum01;   //!
   TBranch        *b_pfjetwidth01;   //!
   TBranch        *b_trig_weight01;   //!
   TBranch        *b_npfjets02;   //!
   TBranch        *b_pfjetpT02;   //!
   TBranch        *b_pfjetarea02;   //!
   TBranch        *b_pfjety02;   //!
   TBranch        *b_pfjetphi02;   //!
   TBranch        *b_pfjetenr02;   //!
   TBranch        *b_pfjettightID02;   //!
   TBranch        *b_pfjetlooseID02;   //!
   TBranch        *b_pfjetJEC02;   //!
   TBranch        *b_pfjetJECL102;   //!
   TBranch        *b_pfjetJECL202;   //!
   TBranch        *b_pfjetJECL2L302;   //!
   TBranch        *b_pfjetCHF02;   //!
   TBranch        *b_pfjetNHF02;   //!
   TBranch        *b_pfjetCHM02;   //!
   TBranch        *b_pfjetNEMF02;   //!
   TBranch        *b_pfjettotnum02;   //!
   TBranch        *b_pfjetneunum02;   //!
   TBranch        *b_pfjetwidth02;   //!
   TBranch        *b_trig_weight02;   //!
   TBranch        *b_npfjets03;   //!
   TBranch        *b_pfjetpT03;   //!
   TBranch        *b_pfjetarea03;   //!
   TBranch        *b_pfjety03;   //!
   TBranch        *b_pfjetphi03;   //!
   TBranch        *b_pfjetenr03;   //!
   TBranch        *b_pfjettightID03;   //!
   TBranch        *b_pfjetlooseID03;   //!
   TBranch        *b_pfjetJEC03;   //!
   TBranch        *b_pfjetJECL103;   //!
   TBranch        *b_pfjetJECL203;   //!
   TBranch        *b_pfjetJECL2L303;   //!
   TBranch        *b_pfjetCHF03;   //!
   TBranch        *b_pfjetNHF03;   //!
   TBranch        *b_pfjetCHM03;   //!
   TBranch        *b_pfjetNEMF03;   //!
   TBranch        *b_pfjettotnum03;   //!
   TBranch        *b_pfjetneunum03;   //!
   TBranch        *b_pfjetwidth03;   //!
   TBranch        *b_trig_weight03;   //!
   TBranch        *b_npfjets04;   //!
   TBranch        *b_pfjetpT04;   //!
   TBranch        *b_pfjetarea04;   //!
   TBranch        *b_pfjety04;   //!
   TBranch        *b_pfjetphi04;   //!
   TBranch        *b_pfjetenr04;   //!
   TBranch        *b_pfjettightID04;   //!
   TBranch        *b_pfjetlooseID04;   //!
   TBranch        *b_pfjetJEC04;   //!
   TBranch        *b_pfjetJECL104;   //!
   TBranch        *b_pfjetJECL204;   //!
   TBranch        *b_pfjetJECL2L304;   //!
   TBranch        *b_pfjetCHF04;   //!
   TBranch        *b_pfjetNHF04;   //!
   TBranch        *b_pfjetCHM04;   //!
   TBranch        *b_pfjetNEMF04;   //!
   TBranch        *b_pfjettotnum04;   //!
   TBranch        *b_pfjetneunum04;   //!
   TBranch        *b_pfjetwidth04;   //!
   TBranch        *b_trig_weight04;   //!
   TBranch        *b_npfjets05;   //!
   TBranch        *b_pfjetpT05;   //!
   TBranch        *b_pfjetarea05;   //!
   TBranch        *b_pfjety05;   //!
   TBranch        *b_pfjetphi05;   //!
   TBranch        *b_pfjetenr05;   //!
   TBranch        *b_pfjettightID05;   //!
   TBranch        *b_pfjetlooseID05;   //!
   TBranch        *b_pfjetJEC05;   //!
   TBranch        *b_pfjetJECL105;   //!
   TBranch        *b_pfjetJECL205;   //!
   TBranch        *b_pfjetJECL2L305;   //!
   TBranch        *b_pfjetCHF05;   //!
   TBranch        *b_pfjetNHF05;   //!
   TBranch        *b_pfjetCHM05;   //!
   TBranch        *b_pfjetNEMF05;   //!
   TBranch        *b_pfjettotnum05;   //!
   TBranch        *b_pfjetneunum05;   //!
   TBranch        *b_pfjetwidth05;   //!
   TBranch        *b_trig_weight05;   //!
   TBranch        *b_npfjets06;   //!
   TBranch        *b_pfjetpT06;   //!
   TBranch        *b_pfjetarea06;   //!
   TBranch        *b_pfjety06;   //!
   TBranch        *b_pfjetphi06;   //!
   TBranch        *b_pfjetenr06;   //!
   TBranch        *b_pfjettightID06;   //!
   TBranch        *b_pfjetlooseID06;   //!
   TBranch        *b_pfjetJEC06;   //!
   TBranch        *b_pfjetJECL106;   //!
   TBranch        *b_pfjetJECL206;   //!
   TBranch        *b_pfjetJECL2L306;   //!
   TBranch        *b_pfjetCHF06;   //!
   TBranch        *b_pfjetNHF06;   //!
   TBranch        *b_pfjetCHM06;   //!
   TBranch        *b_pfjetNEMF06;   //!
   TBranch        *b_pfjettotnum06;   //!
   TBranch        *b_pfjetneunum06;   //!
   TBranch        *b_pfjetwidth06;   //!
   TBranch        *b_trig_weight06;   //!
   TBranch        *b_npfjets07;   //!
   TBranch        *b_pfjetpT07;   //!
   TBranch        *b_pfjetarea07;   //!
   TBranch        *b_pfjety07;   //!
   TBranch        *b_pfjetphi07;   //!
   TBranch        *b_pfjetenr07;   //!
   TBranch        *b_pfjettightID07;   //!
   TBranch        *b_pfjetlooseID07;   //!
   TBranch        *b_pfjetJEC07;   //!
   TBranch        *b_pfjetJECL107;   //!
   TBranch        *b_pfjetJECL207;   //!
   TBranch        *b_pfjetJECL2L307;   //!
   TBranch        *b_pfjetCHF07;   //!
   TBranch        *b_pfjetNHF07;   //!
   TBranch        *b_pfjetCHM07;   //!
   TBranch        *b_pfjetNEMF07;   //!
   TBranch        *b_pfjettotnum07;   //!
   TBranch        *b_pfjetneunum07;   //!
   TBranch        *b_pfjetwidth07;   //!
   TBranch        *b_trig_weight07;   //!
   TBranch        *b_npfjets08;   //!
   TBranch        *b_pfjetpT08;   //!
   TBranch        *b_pfjetarea08;   //!
   TBranch        *b_pfjety08;   //!
   TBranch        *b_pfjetphi08;   //!
   TBranch        *b_pfjetenr08;   //!
   TBranch        *b_pfjettightID08;   //!
   TBranch        *b_pfjetlooseID08;   //!
   TBranch        *b_pfjetJEC08;   //!
   TBranch        *b_pfjetJECL108;   //!
   TBranch        *b_pfjetJECL208;   //!
   TBranch        *b_pfjetJECL2L308;   //!
   TBranch        *b_pfjetCHF08;   //!
   TBranch        *b_pfjetNHF08;   //!
   TBranch        *b_pfjetCHM08;   //!
   TBranch        *b_pfjetNEMF08;   //!
   TBranch        *b_pfjettotnum08;   //!
   TBranch        *b_pfjetneunum08;   //!
   TBranch        *b_pfjetwidth08;   //!
   TBranch        *b_trig_weight08;   //!
   TBranch        *b_npfjets09;   //!
   TBranch        *b_pfjetpT09;   //!
   TBranch        *b_pfjetarea09;   //!
   TBranch        *b_pfjety09;   //!
   TBranch        *b_pfjetphi09;   //!
   TBranch        *b_pfjetenr09;   //!
   TBranch        *b_pfjettightID09;   //!
   TBranch        *b_pfjetlooseID09;   //!
   TBranch        *b_pfjetJEC09;   //!
   TBranch        *b_pfjetJECL109;   //!
   TBranch        *b_pfjetJECL209;   //!
   TBranch        *b_pfjetJECL2L309;   //!
   TBranch        *b_pfjetCHF09;   //!
   TBranch        *b_pfjetNHF09;   //!
   TBranch        *b_pfjetCHM09;   //!
   TBranch        *b_pfjetNEMF09;   //!
   TBranch        *b_pfjettotnum09;   //!
   TBranch        *b_pfjetneunum09;   //!
   TBranch        *b_pfjetwidth09;   //!
   TBranch        *b_trig_weight09;   //!
   TBranch        *b_npfjets10;   //!
   TBranch        *b_pfjetpT10;   //!
   TBranch        *b_pfjetarea10;   //!
   TBranch        *b_pfjety10;   //!
   TBranch        *b_pfjetphi10;   //!
   TBranch        *b_pfjetenr10;   //!
   TBranch        *b_pfjettightID10;   //!
   TBranch        *b_pfjetlooseID10;   //!
   TBranch        *b_pfjetJEC10;   //!
   TBranch        *b_pfjetJECL110;   //!
   TBranch        *b_pfjetJECL210;   //!
   TBranch        *b_pfjetJECL2L310;   //!
   TBranch        *b_pfjetCHF10;   //!
   TBranch        *b_pfjetNHF10;   //!
   TBranch        *b_pfjetCHM10;   //!
   TBranch        *b_pfjetNEMF10;   //!
   TBranch        *b_pfjettotnum10;   //!
   TBranch        *b_pfjetneunum10;   //!
   TBranch        *b_pfjetwidth10;   //!
   TBranch        *b_trig_weight10;   //!
   TBranch        *b_npfjets11;   //!
   TBranch        *b_pfjetpT11;   //!
   TBranch        *b_pfjetarea11;   //!
   TBranch        *b_pfjety11;   //!
   TBranch        *b_pfjetphi11;   //!
   TBranch        *b_pfjetenr11;   //!
   TBranch        *b_pfjettightID11;   //!
   TBranch        *b_pfjetlooseID11;   //!
   TBranch        *b_pfjetJEC11;   //!
   TBranch        *b_pfjetJECL111;   //!
   TBranch        *b_pfjetJECL211;   //!
   TBranch        *b_pfjetJECL2L311;   //!
   TBranch        *b_pfjetCHF11;   //!
   TBranch        *b_pfjetNHF11;   //!
   TBranch        *b_pfjetCHM11;   //!
   TBranch        *b_pfjetNEMF11;   //!
   TBranch        *b_pfjettotnum11;   //!
   TBranch        *b_pfjetneunum11;   //!
   TBranch        *b_pfjetwidth11;   //!
   TBranch        *b_trig_weight11;   //!
   TBranch        *b_npfjets12;   //!
   TBranch        *b_pfjetpT12;   //!
   TBranch        *b_pfjetarea12;   //!
   TBranch        *b_pfjety12;   //!
   TBranch        *b_pfjetphi12;   //!
   TBranch        *b_pfjetenr12;   //!
   TBranch        *b_pfjettightID12;   //!
   TBranch        *b_pfjetlooseID12;   //!
   TBranch        *b_pfjetJEC12;   //!
   TBranch        *b_pfjetJECL112;   //!
   TBranch        *b_pfjetJECL212;   //!
   TBranch        *b_pfjetJECL2L312;   //!
   TBranch        *b_pfjetCHF12;   //!
   TBranch        *b_pfjetNHF12;   //!
   TBranch        *b_pfjetCHM12;   //!
   TBranch        *b_pfjetNEMF12;   //!
   TBranch        *b_pfjettotnum12;   //!
   TBranch        *b_pfjetneunum12;   //!
   TBranch        *b_pfjetwidth12;   //!
   TBranch        *b_trig_weight12;   //!

   suman_rscan(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~suman_rscan() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ifstream ifp; 

   static const int nalgo = 12 ;
//   const char* JetRad[nalgo] ;
   static const int netarange = 10 ;
//   const char* JetEta[netarange] ;
   double etarng[netarange+1];

  static const int noptbins = 62 ;
  static const int noptbins1 = 68 ;
     
  //static double minPFPt = 20.;    
     
  static const int npileupmx = 80;
  static const int nHLTmx= 10; 
  static const int npu_bin = 3;
 
  static const int nopol = 6;
  
  static const int nrun = 10;
 
  TProofOutputFile *OutFile;
  TFile *fileOut; 
  ofstream fp ;

  TF1* fit_cor[nalgo][netarange];
		
  TH1F* hist_pfmet;
  TH1F* hist_SumEt;
  TH1F* hist_METbyET;

  TH1F* hist_PV_all;
  TH1F* hist_PV_sel;
  TH1F* hist_PU;

  TH2F* PU_vs_PV_all;
  TH2F* PU_vs_PV_sel;
  TH2F* PU_vs_PV_sel_rewt;

  TH1F* NJets[nalgo][netarange];
  TH1F* NJets_comb[nalgo][netarange][nrun];
  TH1F* JetpT_comb[nalgo][netarange][nrun];
  TH1F* JetpT[nalgo][netarange];
  TH1F* JetpT_up[nalgo][netarange];
  TH1F* JetpT_dn[nalgo][netarange];
  TH1F* LeadJetpT[nalgo][netarange];
  TH1F* DiJet_Mass[nalgo][netarange];
  TH1F* Jeteta[nalgo];
  TH1F* LeadJeteta[nalgo];
  TH1F* Leading2JetsDeltaR[nalgo];
  TH1F* Leading2JetsDeltaPhi[nalgo] ;
  TH1F* Prescale_JetpT[nalgo][netarange][nHLTmx] ;
  TH1F* Prescale_JetpT_all[nalgo][netarange][nHLTmx] ;  
  TH1F* JetWidth[nalgo][netarange];

  TH1F* LeadJetRatio[nalgo][netarange];									    

  TH1F* NGenJets[nalgo][netarange];
  TH1F* GenJetpT[nalgo][netarange][nrun];
  TH1F* GenLeadJetpT[nalgo][netarange];
  TH1F* GenMCJetpT[nalgo][netarange];
  TH1F* GenMCJetpT_pow[nalgo][netarange];
  TH1F* GenMCLeadJetpT[nalgo][netarange];
  TH1F* Gen_DiJet_Mass[nalgo][netarange];
  TH1F* GenJeteta[nalgo];
  TH1F* GenLeadJeteta[nalgo];
  TH1F* GenLeading2JetsDeltaR[nalgo];
  TH1F* GenLeading2JetsDeltaPhi[nalgo] ;
  TH1F* DeltaR_RecoGen[nalgo][netarange][noptbins] ;
  TH1F* DeltaR_RecoGen_mat[nalgo][netarange][noptbins] ;
  TH1F* Resolution[nalgo][netarange][noptbins];
  TH2F* Pt_Ratio[nalgo][netarange];
  TH2F* Pt_Ratio_nomatch[nalgo][netarange];
  TH2F* JetPt_vs_JEC[nalgo][netarange];
  TH2F* JetPt_vs_JECL1[nalgo][netarange];
  TH2F* JetPt_vs_JECL2[nalgo][netarange];
  TH2F* JetPt_vs_JECL2L3[nalgo][netarange];
  
  TH2F* RecoVsGenJetpT[nalgo][netarange] ;
  TH2F* RecoVsGenJetNo[nalgo][netarange] ;
  TH2F* JEC_fac[nalgo][netarange] ;
  TH2F* Response_y[nalgo];
  TH2F* Pthat_vs_LeadPt[nalgo];
  TH2F* Mes_Cov[nalgo][netarange];

  TH1F* y_Reso[nalgo];
  TH1F* phi_Reso[nalgo];

  TH1F* PileupVertices[nHLTmx] ;

  int njets[nalgo] ;
  int pfjetmul[nalgo][njetmx] ;
  float pfjetenr[nalgo][njetmx], pfjetmom[nalgo][njetmx], pfjetpT[nalgo][njetmx], pfjetarea[nalgo][njetmx], pfjetthe[nalgo][njetmx], pfjety[nalgo][njetmx], pfjetphi[nalgo][njetmx],  pfjetpTup[nalgo][njetmx], pfjetpTdn[nalgo][njetmx], pfjetJEC[nalgo][njetmx], pfjetJECL1[nalgo][njetmx], pfjetJECL2[nalgo][njetmx], pfjetJECL2L3[nalgo][njetmx], pfjetwidth[nalgo][njetmx];
  int pfjettightID[nalgo][njetmx], pfjetlooseID[nalgo][njetmx] ;
  double trig_weight[nalgo];
  
  int ngenjets[nalgo] ;
  int genjetmul[nalgo];
  float genjetenr[nalgo][njetmx], genjetmom[nalgo][njetmx], genjetpT[nalgo][njetmx], genjetpz[nalgo][njetmx], genjetarea[nalgo][njetmx], genjetthe[nalgo][njetmx], genjety[nalgo][njetmx], genjetphi[nalgo][njetmx] ;

  double weight;
  double weighttrg[nHLTmx];
  
// vector<int> jkmore;
  int *_outlist = new int[ 100000000 ];
  
  bool ihlt[nHLTmx];

  double compres[nHLTmx];
  char name[100];
  char title[100];
 
  double ex_cor[nalgo][netarange][noptbins1] = {{{1.}}};
//  double cor_expo[nalgo][netarange][nopol] = {{{1.}}};
 
  bool isMC;
  
  int gmrand;
 
   ClassDef(suman_rscan,0);
};

#endif

#ifdef suman_rscan_cxx
void suman_rscan::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("irun", &irun, &b_irun);
   fChain->SetBranchAddress("ilumi", &ilumi, &b_ilumi);
   fChain->SetBranchAddress("ievt", &ievt, &b_ievt);
   fChain->SetBranchAddress("nprim", &nprim, &b_nprim);
   fChain->SetBranchAddress("Rho", &Rho, &b_Rho);
   fChain->SetBranchAddress("event_weight", &event_weight, &b_event_weight);
   fChain->SetBranchAddress("trig_value", &trig_value, &b_trig_value);
   fChain->SetBranchAddress("ihlt01", &ihlt01, &b_ihlt01);
   fChain->SetBranchAddress("ihlt02", &ihlt02, &b_ihlt02);
   fChain->SetBranchAddress("ihlt03", &ihlt03, &b_ihlt03);
   fChain->SetBranchAddress("ihlt04", &ihlt04, &b_ihlt04);
   fChain->SetBranchAddress("ihlt05", &ihlt05, &b_ihlt05);
   fChain->SetBranchAddress("ihlt06", &ihlt06, &b_ihlt06);
   fChain->SetBranchAddress("ihlt07", &ihlt07, &b_ihlt07);
   fChain->SetBranchAddress("ihlt08", &ihlt08, &b_ihlt08);
   fChain->SetBranchAddress("ihlt09", &ihlt09, &b_ihlt09);
   fChain->SetBranchAddress("ihlt10", &ihlt10, &b_ihlt10);
   fChain->SetBranchAddress("PFMET", &PFMET, &b_miset);
   fChain->SetBranchAddress("PFMETPhi", &PFMETPhi, &b_misphi);
   fChain->SetBranchAddress("sumEt", &sumEt, &b_sumEt);
   fChain->SetBranchAddress("nvert", &nvert, &b_nvert);
   fChain->SetBranchAddress("nchict", &nchict, &b_nchict);
   fChain->SetBranchAddress("npfjets01", &npfjets01, &b_npfjets01);
   fChain->SetBranchAddress("pfjetpT01", pfjetpT01, &b_pfjetpT01);
   fChain->SetBranchAddress("pfjetarea01", pfjetarea01, &b_pfjetarea01);
   fChain->SetBranchAddress("pfjety01", pfjety01, &b_pfjety01);
   fChain->SetBranchAddress("pfjetphi01", pfjetphi01, &b_pfjetphi01);
   fChain->SetBranchAddress("pfjetenr01", pfjetenr01, &b_pfjetenr01);
   fChain->SetBranchAddress("pfjettightID01", pfjettightID01, &b_pfjettightID01);
   fChain->SetBranchAddress("pfjetlooseID01", pfjetlooseID01, &b_pfjetlooseID01);
   fChain->SetBranchAddress("pfjetJEC01", pfjetJEC01, &b_pfjetJEC01);
   fChain->SetBranchAddress("pfjetJECL101", pfjetJECL101, &b_pfjetJECL101);
   fChain->SetBranchAddress("pfjetJECL201", pfjetJECL201, &b_pfjetJECL201);
   fChain->SetBranchAddress("pfjetJECL2L301", pfjetJECL2L301, &b_pfjetJECL2L301);
   fChain->SetBranchAddress("pfjetCHF01", pfjetCHF01, &b_pfjetCHF01);
   fChain->SetBranchAddress("pfjetNHF01", pfjetNHF01, &b_pfjetNHF01);
   fChain->SetBranchAddress("pfjetCHM01", pfjetCHM01, &b_pfjetCHM01);
   fChain->SetBranchAddress("pfjetNEMF01", pfjetNEMF01, &b_pfjetNEMF01);
   fChain->SetBranchAddress("pfjettotnum01", pfjettotnum01, &b_pfjettotnum01);
   fChain->SetBranchAddress("pfjetneunum01", pfjetneunum01, &b_pfjetneunum01);
   fChain->SetBranchAddress("pfjetwidth01", pfjetwidth01, &b_pfjetwidth01);
   fChain->SetBranchAddress("trig_weight01", &trig_weight01, &b_trig_weight01);
   fChain->SetBranchAddress("npfjets02", &npfjets02, &b_npfjets02);
   fChain->SetBranchAddress("pfjetpT02", pfjetpT02, &b_pfjetpT02);
   fChain->SetBranchAddress("pfjetarea02", pfjetarea02, &b_pfjetarea02);
   fChain->SetBranchAddress("pfjety02", pfjety02, &b_pfjety02);
   fChain->SetBranchAddress("pfjetphi02", pfjetphi02, &b_pfjetphi02);
   fChain->SetBranchAddress("pfjetenr02", pfjetenr02, &b_pfjetenr02);
   fChain->SetBranchAddress("pfjettightID02", pfjettightID02, &b_pfjettightID02);
   fChain->SetBranchAddress("pfjetlooseID02", pfjetlooseID02, &b_pfjetlooseID02);
   fChain->SetBranchAddress("pfjetJEC02", pfjetJEC02, &b_pfjetJEC02);
   fChain->SetBranchAddress("pfjetJECL102", pfjetJECL102, &b_pfjetJECL102);
   fChain->SetBranchAddress("pfjetJECL202", pfjetJECL202, &b_pfjetJECL202);
   fChain->SetBranchAddress("pfjetJECL2L302", pfjetJECL2L302, &b_pfjetJECL2L302);
   fChain->SetBranchAddress("pfjetCHF02", pfjetCHF02, &b_pfjetCHF02);
   fChain->SetBranchAddress("pfjetNHF02", pfjetNHF02, &b_pfjetNHF02);
   fChain->SetBranchAddress("pfjetCHM02", pfjetCHM02, &b_pfjetCHM02);
   fChain->SetBranchAddress("pfjetNEMF02", pfjetNEMF02, &b_pfjetNEMF02);
   fChain->SetBranchAddress("pfjettotnum02", pfjettotnum02, &b_pfjettotnum02);
   fChain->SetBranchAddress("pfjetneunum02", pfjetneunum02, &b_pfjetneunum02);
   fChain->SetBranchAddress("pfjetwidth02", pfjetwidth02, &b_pfjetwidth02);
   fChain->SetBranchAddress("trig_weight02", &trig_weight02, &b_trig_weight02);
   fChain->SetBranchAddress("npfjets03", &npfjets03, &b_npfjets03);
   fChain->SetBranchAddress("pfjetpT03", pfjetpT03, &b_pfjetpT03);
   fChain->SetBranchAddress("pfjetarea03", pfjetarea03, &b_pfjetarea03);
   fChain->SetBranchAddress("pfjety03", pfjety03, &b_pfjety03);
   fChain->SetBranchAddress("pfjetphi03", pfjetphi03, &b_pfjetphi03);
   fChain->SetBranchAddress("pfjetenr03", pfjetenr03, &b_pfjetenr03);
   fChain->SetBranchAddress("pfjettightID03", pfjettightID03, &b_pfjettightID03);
   fChain->SetBranchAddress("pfjetlooseID03", pfjetlooseID03, &b_pfjetlooseID03);
   fChain->SetBranchAddress("pfjetJEC03", pfjetJEC03, &b_pfjetJEC03);
   fChain->SetBranchAddress("pfjetJECL103", pfjetJECL103, &b_pfjetJECL103);
   fChain->SetBranchAddress("pfjetJECL203", pfjetJECL203, &b_pfjetJECL203);
   fChain->SetBranchAddress("pfjetJECL2L303", pfjetJECL2L303, &b_pfjetJECL2L303);
   fChain->SetBranchAddress("pfjetCHF03", pfjetCHF03, &b_pfjetCHF03);
   fChain->SetBranchAddress("pfjetNHF03", pfjetNHF03, &b_pfjetNHF03);
   fChain->SetBranchAddress("pfjetCHM03", pfjetCHM03, &b_pfjetCHM03);
   fChain->SetBranchAddress("pfjetNEMF03", pfjetNEMF03, &b_pfjetNEMF03);
   fChain->SetBranchAddress("pfjettotnum03", pfjettotnum03, &b_pfjettotnum03);
   fChain->SetBranchAddress("pfjetneunum03", pfjetneunum03, &b_pfjetneunum03);
   fChain->SetBranchAddress("pfjetwidth03", pfjetwidth03, &b_pfjetwidth03);
   fChain->SetBranchAddress("trig_weight03", &trig_weight03, &b_trig_weight03);
   fChain->SetBranchAddress("npfjets04", &npfjets04, &b_npfjets04);
   fChain->SetBranchAddress("pfjetpT04", pfjetpT04, &b_pfjetpT04);
   fChain->SetBranchAddress("pfjetarea04", pfjetarea04, &b_pfjetarea04);
   fChain->SetBranchAddress("pfjety04", pfjety04, &b_pfjety04);
   fChain->SetBranchAddress("pfjetphi04", pfjetphi04, &b_pfjetphi04);
   fChain->SetBranchAddress("pfjetenr04", pfjetenr04, &b_pfjetenr04);
   fChain->SetBranchAddress("pfjettightID04", pfjettightID04, &b_pfjettightID04);
   fChain->SetBranchAddress("pfjetlooseID04", pfjetlooseID04, &b_pfjetlooseID04);
   fChain->SetBranchAddress("pfjetJEC04", pfjetJEC04, &b_pfjetJEC04);
   fChain->SetBranchAddress("pfjetJECL104", pfjetJECL104, &b_pfjetJECL104);
   fChain->SetBranchAddress("pfjetJECL204", pfjetJECL204, &b_pfjetJECL204);
   fChain->SetBranchAddress("pfjetJECL2L304", pfjetJECL2L304, &b_pfjetJECL2L304);
   fChain->SetBranchAddress("pfjetCHF04", pfjetCHF04, &b_pfjetCHF04);
   fChain->SetBranchAddress("pfjetNHF04", pfjetNHF04, &b_pfjetNHF04);
   fChain->SetBranchAddress("pfjetCHM04", pfjetCHM04, &b_pfjetCHM04);
   fChain->SetBranchAddress("pfjetNEMF04", pfjetNEMF04, &b_pfjetNEMF04);
   fChain->SetBranchAddress("pfjettotnum04", pfjettotnum04, &b_pfjettotnum04);
   fChain->SetBranchAddress("pfjetneunum04", pfjetneunum04, &b_pfjetneunum04);
   fChain->SetBranchAddress("pfjetwidth04", pfjetwidth04, &b_pfjetwidth04);
   fChain->SetBranchAddress("trig_weight04", &trig_weight04, &b_trig_weight04);
   fChain->SetBranchAddress("npfjets05", &npfjets05, &b_npfjets05);
   fChain->SetBranchAddress("pfjetpT05", pfjetpT05, &b_pfjetpT05);
   fChain->SetBranchAddress("pfjetarea05", pfjetarea05, &b_pfjetarea05);
   fChain->SetBranchAddress("pfjety05", pfjety05, &b_pfjety05);
   fChain->SetBranchAddress("pfjetphi05", pfjetphi05, &b_pfjetphi05);
   fChain->SetBranchAddress("pfjetenr05", pfjetenr05, &b_pfjetenr05);
   fChain->SetBranchAddress("pfjettightID05", pfjettightID05, &b_pfjettightID05);
   fChain->SetBranchAddress("pfjetlooseID05", pfjetlooseID05, &b_pfjetlooseID05);
   fChain->SetBranchAddress("pfjetJEC05", pfjetJEC05, &b_pfjetJEC05);
   fChain->SetBranchAddress("pfjetJECL105", pfjetJECL105, &b_pfjetJECL105);
   fChain->SetBranchAddress("pfjetJECL205", pfjetJECL205, &b_pfjetJECL205);
   fChain->SetBranchAddress("pfjetJECL2L305", pfjetJECL2L305, &b_pfjetJECL2L305);
   fChain->SetBranchAddress("pfjetCHF05", pfjetCHF05, &b_pfjetCHF05);
   fChain->SetBranchAddress("pfjetNHF05", pfjetNHF05, &b_pfjetNHF05);
   fChain->SetBranchAddress("pfjetCHM05", pfjetCHM05, &b_pfjetCHM05);
   fChain->SetBranchAddress("pfjetNEMF05", pfjetNEMF05, &b_pfjetNEMF05);
   fChain->SetBranchAddress("pfjettotnum05", pfjettotnum05, &b_pfjettotnum05);
   fChain->SetBranchAddress("pfjetneunum05", pfjetneunum05, &b_pfjetneunum05);
   fChain->SetBranchAddress("pfjetwidth05", pfjetwidth05, &b_pfjetwidth05);
   fChain->SetBranchAddress("trig_weight05", &trig_weight05, &b_trig_weight05);
   fChain->SetBranchAddress("npfjets06", &npfjets06, &b_npfjets06);
   fChain->SetBranchAddress("pfjetpT06", pfjetpT06, &b_pfjetpT06);
   fChain->SetBranchAddress("pfjetarea06", pfjetarea06, &b_pfjetarea06);
   fChain->SetBranchAddress("pfjety06", pfjety06, &b_pfjety06);
   fChain->SetBranchAddress("pfjetphi06", pfjetphi06, &b_pfjetphi06);
   fChain->SetBranchAddress("pfjetenr06", pfjetenr06, &b_pfjetenr06);
   fChain->SetBranchAddress("pfjettightID06", pfjettightID06, &b_pfjettightID06);
   fChain->SetBranchAddress("pfjetlooseID06", pfjetlooseID06, &b_pfjetlooseID06);
   fChain->SetBranchAddress("pfjetJEC06", pfjetJEC06, &b_pfjetJEC06);
   fChain->SetBranchAddress("pfjetJECL106", pfjetJECL106, &b_pfjetJECL106);
   fChain->SetBranchAddress("pfjetJECL206", pfjetJECL206, &b_pfjetJECL206);
   fChain->SetBranchAddress("pfjetJECL2L306", pfjetJECL2L306, &b_pfjetJECL2L306);
   fChain->SetBranchAddress("pfjetCHF06", pfjetCHF06, &b_pfjetCHF06);
   fChain->SetBranchAddress("pfjetNHF06", pfjetNHF06, &b_pfjetNHF06);
   fChain->SetBranchAddress("pfjetCHM06", pfjetCHM06, &b_pfjetCHM06);
   fChain->SetBranchAddress("pfjetNEMF06", pfjetNEMF06, &b_pfjetNEMF06);
   fChain->SetBranchAddress("pfjettotnum06", pfjettotnum06, &b_pfjettotnum06);
   fChain->SetBranchAddress("pfjetneunum06", pfjetneunum06, &b_pfjetneunum06);
   fChain->SetBranchAddress("pfjetwidth06", pfjetwidth06, &b_pfjetwidth06);
   fChain->SetBranchAddress("trig_weight06", &trig_weight06, &b_trig_weight06);
   fChain->SetBranchAddress("npfjets07", &npfjets07, &b_npfjets07);
   fChain->SetBranchAddress("pfjetpT07", pfjetpT07, &b_pfjetpT07);
   fChain->SetBranchAddress("pfjetarea07", pfjetarea07, &b_pfjetarea07);
   fChain->SetBranchAddress("pfjety07", pfjety07, &b_pfjety07);
   fChain->SetBranchAddress("pfjetphi07", pfjetphi07, &b_pfjetphi07);
   fChain->SetBranchAddress("pfjetenr07", pfjetenr07, &b_pfjetenr07);
   fChain->SetBranchAddress("pfjettightID07", pfjettightID07, &b_pfjettightID07);
   fChain->SetBranchAddress("pfjetlooseID07", pfjetlooseID07, &b_pfjetlooseID07);
   fChain->SetBranchAddress("pfjetJEC07", pfjetJEC07, &b_pfjetJEC07);
   fChain->SetBranchAddress("pfjetJECL107", pfjetJECL107, &b_pfjetJECL107);
   fChain->SetBranchAddress("pfjetJECL207", pfjetJECL207, &b_pfjetJECL207);
   fChain->SetBranchAddress("pfjetJECL2L307", pfjetJECL2L307, &b_pfjetJECL2L307);
   fChain->SetBranchAddress("pfjetCHF07", pfjetCHF07, &b_pfjetCHF07);
   fChain->SetBranchAddress("pfjetNHF07", pfjetNHF07, &b_pfjetNHF07);
   fChain->SetBranchAddress("pfjetCHM07", pfjetCHM07, &b_pfjetCHM07);
   fChain->SetBranchAddress("pfjetNEMF07", pfjetNEMF07, &b_pfjetNEMF07);
   fChain->SetBranchAddress("pfjettotnum07", pfjettotnum07, &b_pfjettotnum07);
   fChain->SetBranchAddress("pfjetneunum07", pfjetneunum07, &b_pfjetneunum07);
   fChain->SetBranchAddress("pfjetwidth07", pfjetwidth07, &b_pfjetwidth07);
   fChain->SetBranchAddress("trig_weight07", &trig_weight07, &b_trig_weight07);
   fChain->SetBranchAddress("npfjets08", &npfjets08, &b_npfjets08);
   fChain->SetBranchAddress("pfjetpT08", pfjetpT08, &b_pfjetpT08);
   fChain->SetBranchAddress("pfjetarea08", pfjetarea08, &b_pfjetarea08);
   fChain->SetBranchAddress("pfjety08", pfjety08, &b_pfjety08);
   fChain->SetBranchAddress("pfjetphi08", pfjetphi08, &b_pfjetphi08);
   fChain->SetBranchAddress("pfjetenr08", pfjetenr08, &b_pfjetenr08);
   fChain->SetBranchAddress("pfjettightID08", pfjettightID08, &b_pfjettightID08);
   fChain->SetBranchAddress("pfjetlooseID08", pfjetlooseID08, &b_pfjetlooseID08);
   fChain->SetBranchAddress("pfjetJEC08", pfjetJEC08, &b_pfjetJEC08);
   fChain->SetBranchAddress("pfjetJECL108", pfjetJECL108, &b_pfjetJECL108);
   fChain->SetBranchAddress("pfjetJECL208", pfjetJECL208, &b_pfjetJECL208);
   fChain->SetBranchAddress("pfjetJECL2L308", pfjetJECL2L308, &b_pfjetJECL2L308);
   fChain->SetBranchAddress("pfjetCHF08", pfjetCHF08, &b_pfjetCHF08);
   fChain->SetBranchAddress("pfjetNHF08", pfjetNHF08, &b_pfjetNHF08);
   fChain->SetBranchAddress("pfjetCHM08", pfjetCHM08, &b_pfjetCHM08);
   fChain->SetBranchAddress("pfjetNEMF08", pfjetNEMF08, &b_pfjetNEMF08);
   fChain->SetBranchAddress("pfjettotnum08", pfjettotnum08, &b_pfjettotnum08);
   fChain->SetBranchAddress("pfjetneunum08", pfjetneunum08, &b_pfjetneunum08);
   fChain->SetBranchAddress("pfjetwidth08", pfjetwidth08, &b_pfjetwidth08);
   fChain->SetBranchAddress("trig_weight08", &trig_weight08, &b_trig_weight08);
   fChain->SetBranchAddress("npfjets09", &npfjets09, &b_npfjets09);
   fChain->SetBranchAddress("pfjetpT09", pfjetpT09, &b_pfjetpT09);
   fChain->SetBranchAddress("pfjetarea09", pfjetarea09, &b_pfjetarea09);
   fChain->SetBranchAddress("pfjety09", pfjety09, &b_pfjety09);
   fChain->SetBranchAddress("pfjetphi09", pfjetphi09, &b_pfjetphi09);
   fChain->SetBranchAddress("pfjetenr09", pfjetenr09, &b_pfjetenr09);
   fChain->SetBranchAddress("pfjettightID09", pfjettightID09, &b_pfjettightID09);
   fChain->SetBranchAddress("pfjetlooseID09", pfjetlooseID09, &b_pfjetlooseID09);
   fChain->SetBranchAddress("pfjetJEC09", pfjetJEC09, &b_pfjetJEC09);
   fChain->SetBranchAddress("pfjetJECL109", pfjetJECL109, &b_pfjetJECL109);
   fChain->SetBranchAddress("pfjetJECL209", pfjetJECL209, &b_pfjetJECL209);
   fChain->SetBranchAddress("pfjetJECL2L309", pfjetJECL2L309, &b_pfjetJECL2L309);
   fChain->SetBranchAddress("pfjetCHF09", pfjetCHF09, &b_pfjetCHF09);
   fChain->SetBranchAddress("pfjetNHF09", pfjetNHF09, &b_pfjetNHF09);
   fChain->SetBranchAddress("pfjetCHM09", pfjetCHM09, &b_pfjetCHM09);
   fChain->SetBranchAddress("pfjetNEMF09", pfjetNEMF09, &b_pfjetNEMF09);
   fChain->SetBranchAddress("pfjettotnum09", pfjettotnum09, &b_pfjettotnum09);
   fChain->SetBranchAddress("pfjetneunum09", pfjetneunum09, &b_pfjetneunum09);
   fChain->SetBranchAddress("pfjetwidth09", pfjetwidth09, &b_pfjetwidth09);
   fChain->SetBranchAddress("trig_weight09", &trig_weight09, &b_trig_weight09);
   fChain->SetBranchAddress("npfjets10", &npfjets10, &b_npfjets10);
   fChain->SetBranchAddress("pfjetpT10", pfjetpT10, &b_pfjetpT10);
   fChain->SetBranchAddress("pfjetarea10", pfjetarea10, &b_pfjetarea10);
   fChain->SetBranchAddress("pfjety10", pfjety10, &b_pfjety10);
   fChain->SetBranchAddress("pfjetphi10", pfjetphi10, &b_pfjetphi10);
   fChain->SetBranchAddress("pfjetenr10", pfjetenr10, &b_pfjetenr10);
   fChain->SetBranchAddress("pfjettightID10", pfjettightID10, &b_pfjettightID10);
   fChain->SetBranchAddress("pfjetlooseID10", pfjetlooseID10, &b_pfjetlooseID10);
   fChain->SetBranchAddress("pfjetJEC10", pfjetJEC10, &b_pfjetJEC10);
   fChain->SetBranchAddress("pfjetJECL110", pfjetJECL110, &b_pfjetJECL110);
   fChain->SetBranchAddress("pfjetJECL210", pfjetJECL210, &b_pfjetJECL210);
   fChain->SetBranchAddress("pfjetJECL2L310", pfjetJECL2L310, &b_pfjetJECL2L310);
   fChain->SetBranchAddress("pfjetCHF10", pfjetCHF10, &b_pfjetCHF10);
   fChain->SetBranchAddress("pfjetNHF10", pfjetNHF10, &b_pfjetNHF10);
   fChain->SetBranchAddress("pfjetCHM10", pfjetCHM10, &b_pfjetCHM10);
   fChain->SetBranchAddress("pfjetNEMF10", pfjetNEMF10, &b_pfjetNEMF10);
   fChain->SetBranchAddress("pfjettotnum10", pfjettotnum10, &b_pfjettotnum10);
   fChain->SetBranchAddress("pfjetneunum10", pfjetneunum10, &b_pfjetneunum10);
   fChain->SetBranchAddress("pfjetwidth10", pfjetwidth10, &b_pfjetwidth10);
   fChain->SetBranchAddress("trig_weight10", &trig_weight10, &b_trig_weight10);
   fChain->SetBranchAddress("npfjets11", &npfjets11, &b_npfjets11);
   fChain->SetBranchAddress("pfjetpT11", pfjetpT11, &b_pfjetpT11);
   fChain->SetBranchAddress("pfjetarea11", pfjetarea11, &b_pfjetarea11);
   fChain->SetBranchAddress("pfjety11", pfjety11, &b_pfjety11);
   fChain->SetBranchAddress("pfjetphi11", pfjetphi11, &b_pfjetphi11);
   fChain->SetBranchAddress("pfjetenr11", pfjetenr11, &b_pfjetenr11);
   fChain->SetBranchAddress("pfjettightID11", pfjettightID11, &b_pfjettightID11);
   fChain->SetBranchAddress("pfjetlooseID11", pfjetlooseID11, &b_pfjetlooseID11);
   fChain->SetBranchAddress("pfjetJEC11", pfjetJEC11, &b_pfjetJEC11);
   fChain->SetBranchAddress("pfjetJECL111", pfjetJECL111, &b_pfjetJECL111);
   fChain->SetBranchAddress("pfjetJECL211", pfjetJECL211, &b_pfjetJECL211);
   fChain->SetBranchAddress("pfjetJECL2L311", pfjetJECL2L311, &b_pfjetJECL2L311);
   fChain->SetBranchAddress("pfjetCHF11", pfjetCHF11, &b_pfjetCHF11);
   fChain->SetBranchAddress("pfjetNHF11", pfjetNHF11, &b_pfjetNHF11);
   fChain->SetBranchAddress("pfjetCHM11", pfjetCHM11, &b_pfjetCHM11);
   fChain->SetBranchAddress("pfjetNEMF11", pfjetNEMF11, &b_pfjetNEMF11);
   fChain->SetBranchAddress("pfjettotnum11", pfjettotnum11, &b_pfjettotnum11);
   fChain->SetBranchAddress("pfjetneunum11", pfjetneunum11, &b_pfjetneunum11);
   fChain->SetBranchAddress("pfjetwidth11", pfjetwidth11, &b_pfjetwidth11);
   fChain->SetBranchAddress("trig_weight11", &trig_weight11, &b_trig_weight11);
   fChain->SetBranchAddress("npfjets12", &npfjets12, &b_npfjets12);
   fChain->SetBranchAddress("pfjetpT12", pfjetpT12, &b_pfjetpT12);
   fChain->SetBranchAddress("pfjetarea12", pfjetarea12, &b_pfjetarea12);
   fChain->SetBranchAddress("pfjety12", pfjety12, &b_pfjety12);
   fChain->SetBranchAddress("pfjetphi12", pfjetphi12, &b_pfjetphi12);
   fChain->SetBranchAddress("pfjetenr12", pfjetenr12, &b_pfjetenr12);
   fChain->SetBranchAddress("pfjettightID12", pfjettightID12, &b_pfjettightID12);
   fChain->SetBranchAddress("pfjetlooseID12", pfjetlooseID12, &b_pfjetlooseID12);
   fChain->SetBranchAddress("pfjetJEC12", pfjetJEC12, &b_pfjetJEC12);
   fChain->SetBranchAddress("pfjetJECL112", pfjetJECL112, &b_pfjetJECL112);
   fChain->SetBranchAddress("pfjetJECL212", pfjetJECL212, &b_pfjetJECL212);
   fChain->SetBranchAddress("pfjetJECL2L312", pfjetJECL2L312, &b_pfjetJECL2L312);
   fChain->SetBranchAddress("pfjetCHF12", pfjetCHF12, &b_pfjetCHF12);
   fChain->SetBranchAddress("pfjetNHF12", pfjetNHF12, &b_pfjetNHF12);
   fChain->SetBranchAddress("pfjetCHM12", pfjetCHM12, &b_pfjetCHM12);
   fChain->SetBranchAddress("pfjetNEMF12", pfjetNEMF12, &b_pfjetNEMF12);
   fChain->SetBranchAddress("pfjettotnum12", pfjettotnum12, &b_pfjettotnum12);
   fChain->SetBranchAddress("pfjetneunum12", pfjetneunum12, &b_pfjetneunum12);
   fChain->SetBranchAddress("pfjetwidth12", pfjetwidth12, &b_pfjetwidth12);
   fChain->SetBranchAddress("trig_weight12", &trig_weight12, &b_trig_weight12);
/*
   ifstream ifp("correction_plynomial.log");

    for(int ij=0; ij<nalgo; ij++){
           for(int jk=0; jk<netarange; jk++){
                  double parvalues[nopol]={0};
                   for(int kl=0; kl<nopol; kl++){
                           ifp>>cor_expo[ij][jk][kl];
                           parvalues[kl] = cor_expo[ij][jk][kl];
                   }

                fit_cor[ij][jk]->SetParameters(parvalues);
           }
   }

   ifp.close();
*/

//generating random numbers for 1-10
std::vector<float> _jkmore;
Long64_t nentries5 = (fChain ? fChain->GetEntriesFast() : fChain->GetEntriesFast());
for (Long64_t jentry5=0; jentry5<nentries5; jentry5++) {

 if (_jkmore.size()==0) { // if jkmore is empty, reset it first
     for (int ijk = 0; ijk != nrun; ++ijk) _jkmore.push_back(ijk);
   }
 int m = _jkmore.size(); assert(m!=0);
 int mout = gRandom3->Integer(m);
 int iout = int(_jkmore[mout]);
 _outlist[jentry5] = iout;
 _jkmore.erase(_jkmore.begin()+mout); 
  
  } 

}

Bool_t suman_rscan::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   gmrand = int((1000*gRandom3->Uniform())/100);
   return kTRUE;
}

#endif // #ifdef suman_rscan_cxx
