#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include <fstream>
#include <TH1D.h>
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

void Sys_JES_FacG()
{
const int nalgo = 12;
const int Etabins = 10;
const int njes = 28;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[Etabins] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const char* jes_name[njes] = {"AbsoluteStat", "AbsoluteScale", "AbsoluteFlavMap", "AbsoluteMPFBias", "Fragmentation", "SinglePionECAL", "SinglePionHCAL", "FlavorQCD", "TimePtEta","RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2","RelativePtHF", "RelativeBal", "RelativeSample", "RelativeFSR", "RelativeStatFSR", "RelativeStatEC", "RelativeStatHF", "PileUpDataMC", "PileUpPtRef", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF"};

const char* jes_dir[2] = {"JES Up","JES Down"};
const char *dirname[2] = {"JES_Up","JES_Down"};

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

double min_range = 84;
double max_range = 1588;

const int ref = 3;

int col_jes[njes] = {1,2,41,4,5,6,7,kGreen+1,9,11,kCyan+2,kCyan-10, kBlue-7, kMagenta-9, kRed-5,40,kTeal+3,42,43,44,45,46,28,32,36,49,50,51};
int sty_jes[njes] = {1,1,1,1,1,1,1,3,7,1,7,7,7,7,7,7,7,7,7,7,7,4,4,4,4,4,4,4};
/* 
for(int ij=0; ij<njes; ij++){
sty_jes[ij] = ij+1;
}
*/
ofstream fp_pt;
fp_pt.open("JES_Pt_Mod2016_Legacy.log");

ofstream fp_rad;
fp_rad.open("JES_Rad_Mod2016_Legacy.log");

char name[100];

TH1D *Jet_pt[nalgo][Etabins][2*njes+1];
TH1D *Jet_radius[nalgo][Etabins][2*njes+1];

TH1D *Jet_pt_tot[nalgo][Etabins][2];
TH1D *Jet_radius_tot[nalgo][Etabins][2];

double jes_pt_up[nalgo][Etabins][noptbins][njes] = {{{{0.}}}};
double jes_pt_dn[nalgo][Etabins][noptbins][njes] = {{{{0.}}}};
double jes_radius_up[nalgo][Etabins][noptbins][njes] = {{{{0.}}}};
double jes_radius_dn[nalgo][Etabins][noptbins][njes] = {{{{0.}}}};

double jes_pt_up_tot[nalgo][Etabins][noptbins] = {{{0.}}};
double jes_pt_dn_tot[nalgo][Etabins][noptbins] = {{{0.}}};
double jes_radius_up_tot[nalgo][Etabins][noptbins] = {{{0.}}};
double jes_radius_dn_tot[nalgo][Etabins][noptbins] = {{{0.}}};

double jes_pt_up_sum[nalgo][Etabins][noptbins] = {{{0.}}};
double jes_pt_dn_sum[nalgo][Etabins][noptbins] = {{{0.}}};
double jes_radius_up_sum[nalgo][Etabins][noptbins] = {{{0.}}};
double jes_radius_dn_sum[nalgo][Etabins][noptbins] = {{{0.}}};

//TFile *file0 = new TFile("/home/suman/RooUnfold/Unfolded_2016_Data_ModJES_Legacy.root","read");
TFile *file0 = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/hist_RecoJetchs_PU_Data_2016_JetHTfinal.root","read");
file0->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  for(int kl=0; kl<(2*njes+1); kl++){

//	if(kl>28) { kl += 9; }
 
//	sprintf(name,"bayes_unfold_%s_Etabin%i_JES%i",JetRad[ij],jk+1,kl);
	sprintf(name,"mcjets/JetpT_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,kl);
	if(kl>njes) {
//	sprintf(name,"bayes_unfold_%s_Etabin%i_JES%i",JetRad[ij],jk+1,kl+9);
	sprintf(name,"mcjets/JetpT_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,kl+9);
	}
	Jet_pt[ij][jk][kl] = (TH1D*)file0->Get(name);

  }

//       sprintf(name,"bayes_unfold_%s_Etabin%i_JES37",JetRad[ij],jk+1);
	   sprintf(name,"mcjets/JetpT_%s_EtaBin%i_JES37",JetRad[ij],jk+1);
       Jet_pt_tot[ij][jk][0] = (TH1D*)file0->Get(name);

//       sprintf(name,"bayes_unfold_%s_Etabin%i_JES74",JetRad[ij],jk+1);
	   sprintf(name,"mcjets/JetpT_%s_EtaBin%i_JES74",JetRad[ij],jk+1);
       Jet_pt_tot[ij][jk][1] = (TH1D*)file0->Get(name);
 }//jk
}//ij

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  for(int kl=0; kl<(2*njes+1); kl++){

        Jet_radius[ij][jk][kl] = (TH1D*)Jet_pt[ij][jk][kl]->Clone();
        Jet_radius[ij][jk][kl]->Divide(Jet_pt[ref][jk][kl]);
  }
 for(int kl=0; kl<2; kl++){
	 Jet_radius_tot[ij][jk][kl] = (TH1D*)Jet_pt_tot[ij][jk][kl]->Clone();
	 Jet_radius_tot[ij][jk][kl]->Divide(Jet_pt_tot[ref][jk][kl]);
   }
 }//jk
}//ij


double a0,a1,a2;
double b0,b1,b2;

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

  for(int pt=0; pt<noptbins; pt++){

   a0 = Jet_pt[ij][jk][0]->GetBinContent(pt+1);

    for(int kl=1; kl<(njes+1); kl++){

		a1 = Jet_pt[ij][jk][kl]->GetBinContent(pt+1)-a0;
        a2 = Jet_pt[ij][jk][kl+njes]->GetBinContent(pt+1)-a0;

	
		if(a1*a2>0){
			if(a1>0) { jes_pt_up[ij][jk][pt][kl-1] = (abs(a1)>abs(a2))?abs(a1):abs(a2) ; }
			else { jes_pt_dn[ij][jk][pt][kl-1] = (abs(a1)>abs(a2))?abs(a1):abs(a2) ; }
		}
		else{
			if(a1>0) { jes_pt_up[ij][jk][pt][kl-1] = a1 ;  jes_pt_dn[ij][jk][pt][kl-1] = abs(a2) ; }
			else { if (a2>0) {  jes_pt_up[ij][jk][pt][kl-1] = a2 ;  jes_pt_dn[ij][jk][pt][kl-1] = abs(a1) ; }  }
		}

	}

    b0 = Jet_radius[ij][jk][0]->GetBinContent(pt+1);

    for(int kl=1; kl<(njes+1); kl++){

        b1 = Jet_radius[ij][jk][kl]->GetBinContent(pt+1)-b0;
        b2 = Jet_radius[ij][jk][kl+njes]->GetBinContent(pt+1)-b0;

        if(b1*b2>0){
			if(b1>0) { jes_radius_up[ij][jk][pt][kl-1] = (abs(b1)>abs(b2))?abs(b1):abs(b2) ; }
			else { jes_radius_dn[ij][jk][pt][kl-1] = (abs(b1)>abs(b2))?abs(b1):abs(b2) ; }
        }
        else{
			if(b1>0) { jes_radius_up[ij][jk][pt][kl-1] = b1 ;  jes_radius_dn[ij][jk][pt][kl-1] = abs(b2) ; }
			else { if (b2>0) {  jes_radius_up[ij][jk][pt][kl-1] = b2 ;  jes_radius_dn[ij][jk][pt][kl-1] = abs(b1) ; }  }
        }

    }

     float a11 = Jet_pt_tot[ij][jk][0]->GetBinContent(pt+1)- a0;
     float a22 = Jet_pt_tot[ij][jk][1]->GetBinContent(pt+1)- a0;
	
     if(a11*a22>0){
     if(a11>0){ jes_pt_up_tot[ij][jk][pt] = (abs(a11)>abs(a22))?abs(a11):abs(a22); }
		else { jes_pt_dn_tot[ij][jk][pt] = (abs(a11)>abs(a22))?abs(a11):abs(a22); }
	 }else{
		if(a11>0) { jes_pt_up_tot[ij][jk][pt] = a11; jes_pt_dn_tot[ij][jk][pt] = abs(a22); }
		else { if(a22>0) { jes_pt_up_tot[ij][jk][pt] = a22; jes_pt_dn_tot[ij][jk][pt] = abs(a11); } }
		}

   float b11 = Jet_radius_tot[ij][jk][0]->GetBinContent(pt+1)- b0;
   float b22 = Jet_radius_tot[ij][jk][1]->GetBinContent(pt+1)- b0;

   if(b11*b22>0){
     if(b11>0){ jes_radius_up_tot[ij][jk][pt] = (abs(b11)>abs(b22))?abs(b11):abs(b22); }
        else { jes_radius_dn_tot[ij][jk][pt] = (abs(b11)>abs(b22))?abs(b11):abs(b22); }
        }else{
        if(b11>0) { jes_radius_up_tot[ij][jk][pt] = b11; jes_radius_dn_tot[ij][jk][pt] = abs(b22); }
        else { if(b22>0) { jes_radius_up_tot[ij][jk][pt] = b22; jes_radius_dn_tot[ij][jk][pt] = abs(b11); } }
        }

   for(int kl=0; kl<njes; kl++){
  
      jes_pt_up_sum[ij][jk][pt] += pow(jes_pt_up[ij][jk][pt][kl],2.);
      jes_pt_dn_sum[ij][jk][pt] += pow(jes_pt_dn[ij][jk][pt][kl],2.);

      jes_radius_up_sum[ij][jk][pt] += pow(jes_radius_up[ij][jk][pt][kl],2.);
      jes_radius_dn_sum[ij][jk][pt] += pow(jes_radius_dn[ij][jk][pt][kl],2.);

      }
  
      jes_pt_up_sum[ij][jk][pt] = sqrt(jes_pt_up_sum[ij][jk][pt]);
      jes_pt_dn_sum[ij][jk][pt] = sqrt(jes_pt_dn_sum[ij][jk][pt]);
      jes_radius_up_sum[ij][jk][pt] = sqrt(jes_radius_up_sum[ij][jk][pt]);
      jes_radius_dn_sum[ij][jk][pt] = sqrt(jes_radius_dn_sum[ij][jk][pt]);

   }
 }
}


TH1D *JetpT_jes_up[nalgo][Etabins];
TH1D *JetpT_jes_dn[nalgo][Etabins];

TH1D *JetRad_jes_up[nalgo][Etabins];
TH1D *JetRad_jes_dn[nalgo][Etabins];

TH1D *JetpT_jes_up_fac[nalgo][Etabins][njes];
TH1D *JetpT_jes_dn_fac[nalgo][Etabins][njes];

TH1D *JetRad_jes_up_fac[nalgo][Etabins][njes];
TH1D *JetRad_jes_dn_fac[nalgo][Etabins][njes];

TH1D *JetpT_jes_up_sum[nalgo][Etabins];
TH1D *JetpT_jes_dn_sum[nalgo][Etabins];
TH1D *JetRad_jes_up_sum[nalgo][Etabins];
TH1D *JetRad_jes_dn_sum[nalgo][Etabins];


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

  sprintf(name,"JetpT_JES_up_%s_EtaBin%i",JetRad[ij],jk+1);
  JetpT_jes_up[ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"JetpT_JES_dn_%s_EtaBin%i",JetRad[ij],jk+1);
  JetpT_jes_dn[ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"JetRad_JES_up_%s_EtaBin%i",JetRad[ij],jk+1);
  JetRad_jes_up[ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"JetRad_JES_dn_%s_EtaBin%i",JetRad[ij],jk+1);
  JetRad_jes_dn[ij][jk] = new TH1D(name,name,noptbins,ptbins);
  
  sprintf(name,"JetpT_JES_up_sum_%s_EtaBin%i",JetRad[ij],jk+1);
  JetpT_jes_up_sum[ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"JetpT_JES_dn_sum_%s_EtaBin%i",JetRad[ij],jk+1);
  JetpT_jes_dn_sum[ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"JetRad_JES_up_sum_%s_EtaBin%i",JetRad[ij],jk+1);
  JetRad_jes_up_sum[ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"JetRad_JES_dn_sum_%s_EtaBin%i",JetRad[ij],jk+1);
  JetRad_jes_dn_sum[ij][jk] = new TH1D(name,name,noptbins,ptbins);

 for(int pt=0; pt<noptbins; pt++){
  
 if(Jet_pt[ij][jk][0]->GetBinContent(pt+1)>1.e-10){

	JetpT_jes_up[ij][jk]->SetBinContent(pt+1,jes_pt_up_tot[ij][jk][pt]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1));
	JetpT_jes_dn[ij][jk]->SetBinContent(pt+1,jes_pt_dn_tot[ij][jk][pt]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1));

	JetpT_jes_up_sum[ij][jk]->SetBinContent(pt+1,jes_pt_up_sum[ij][jk][pt]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1));
	JetpT_jes_dn_sum[ij][jk]->SetBinContent(pt+1,jes_pt_dn_sum[ij][jk][pt]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1));
 }


 if(Jet_radius[ij][jk][0]->GetBinContent(pt+1)>1.e-10){

	JetRad_jes_up[ij][jk]->SetBinContent(pt+1,jes_radius_up_tot[ij][jk][pt] * 1./Jet_radius[ij][jk][0]->GetBinContent(pt+1));
	JetRad_jes_dn[ij][jk]->SetBinContent(pt+1,jes_radius_dn_tot[ij][jk][pt] *1./Jet_radius[ij][jk][0]->GetBinContent(pt+1));

	JetRad_jes_up_sum[ij][jk]->SetBinContent(pt+1,jes_radius_up_sum[ij][jk][pt] * 1./Jet_radius[ij][jk][0]->GetBinContent(pt+1));
	JetRad_jes_dn_sum[ij][jk]->SetBinContent(pt+1,jes_radius_dn_sum[ij][jk][pt] *1./Jet_radius[ij][jk][0]->GetBinContent(pt+1));

  }
/*
 fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<JetpT_jes_up[ij][jk]->GetBinContent(pt+1)<<'\t'<<JetpT_jes_dn[ij][jk]->GetBinContent(pt+1)<<endl;
 fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<JetRad_jes_up[ij][jk]->GetBinContent(pt+1)<<'\t'<<JetRad_jes_dn[ij][jk]->GetBinContent(pt+1)<<endl;
*/
 }

  for(int kl=0; kl<njes; kl++){
  
   sprintf(name,"JetpT_JES_up_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,kl+1);
   JetpT_jes_up_fac[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"JetpT_JES_dn_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,kl+1);
   JetpT_jes_dn_fac[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"JetRad_JES_up_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,kl+1);
   JetRad_jes_up_fac[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"JetRad_JES_dn_%s_EtaBin%i_JES%i",JetRad[ij],jk+1,kl+1);
   JetRad_jes_dn_fac[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins);


   for(int pt=0; pt<noptbins; pt++){

	if(Jet_pt[ij][jk][0]->GetBinContent(pt+1)>1.e-10){
		JetpT_jes_up_fac[ij][jk][kl]->SetBinContent(pt+1,jes_pt_up[ij][jk][pt][kl]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1));
		JetpT_jes_dn_fac[ij][jk][kl]->SetBinContent(pt+1,jes_pt_dn[ij][jk][pt][kl]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1));
   
		JetRad_jes_up_fac[ij][jk][kl]->SetBinContent(pt+1,jes_radius_up[ij][jk][pt][kl]*1./Jet_radius[ij][jk][0]->GetBinContent(pt+1));
		JetRad_jes_dn_fac[ij][jk][kl]->SetBinContent(pt+1,jes_radius_dn[ij][jk][pt][kl]*1./Jet_radius[ij][jk][0]->GetBinContent(pt+1));
   }
 }


  //cout<<"col "<<kl<<" "<<col_jes[kl]<<endl;

  JetpT_jes_up_fac[ij][jk][kl]->SetMarkerColor(col_jes[kl]);
  JetpT_jes_up_fac[ij][jk][kl]->SetLineColor(col_jes[kl]);
  JetpT_jes_up_fac[ij][jk][kl]->SetLineStyle(sty_jes[kl]);
  JetpT_jes_up_fac[ij][jk][kl]->SetMinimum(-0.11);
  JetpT_jes_up_fac[ij][jk][kl]->SetMaximum(0.11);

  JetpT_jes_dn_fac[ij][jk][kl]->SetMarkerColor(col_jes[kl]);
  JetpT_jes_dn_fac[ij][jk][kl]->SetLineColor(col_jes[kl]);
  JetpT_jes_dn_fac[ij][jk][kl]->SetLineStyle(sty_jes[kl]);
  JetpT_jes_dn_fac[ij][jk][kl]->SetMinimum(-0.11);
  JetpT_jes_dn_fac[ij][jk][kl]->SetMaximum(0.11);

  JetRad_jes_up_fac[ij][jk][kl]->SetMarkerColor(col_jes[kl]);
  JetRad_jes_up_fac[ij][jk][kl]->SetLineColor(col_jes[kl]);
  JetRad_jes_up_fac[ij][jk][kl]->SetLineStyle(sty_jes[kl]);
  JetRad_jes_up_fac[ij][jk][kl]->SetMinimum(-0.025);
  JetRad_jes_up_fac[ij][jk][kl]->SetMaximum(0.025);

  JetRad_jes_dn_fac[ij][jk][kl]->SetMarkerColor(col_jes[kl]);
  JetRad_jes_dn_fac[ij][jk][kl]->SetLineColor(col_jes[kl]);
  JetRad_jes_dn_fac[ij][jk][kl]->SetLineStyle(sty_jes[kl]);
  JetRad_jes_dn_fac[ij][jk][kl]->SetMinimum(-0.025);
  JetRad_jes_dn_fac[ij][jk][kl]->SetMaximum(0.025);
  

  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->CenterTitle();
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetRangeUser(min_range,max_range);

  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty in p_{T}");
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->CenterTitle();

  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->CenterTitle();
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetRangeUser(min_range,max_range);

  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty in Ratio of Xsections");
  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->CenterTitle();

  }

 }
}

TCanvas *c2[2][nalgo][Etabins];
TLegend *leg_pt[2][nalgo][Etabins];

for(int ud=0; ud<2; ud++){
for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

 sprintf(name,"JES_Pt_%s_EtaBin%i_Allfac_%s",JetRad[ij],jk+1,dirname[ud]);
 c2[ud][ij][jk] = tdrCanvas(name,JetpT_jes_up_fac[ij][jk][0],7,0);

 c2[ud][ij][jk]->SetRightMargin(0.3); // open for fac

 leg_pt[ud][ij][jk] = new TLegend(0.7,0.12,0.95,0.92);
// leg_pt[ud][ij][jk] = new TLegend(0.57,0.42,0.87,0.92);
 leg_pt[ud][ij][jk]->SetBorderSize(0);

 c2[ud][ij][jk]->cd(1);
 gPad->SetLogx(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.075);

  TString text2;
  text2+= jes_dir[1];
  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

//  latex.DrawLatex(0.3,0.65,text2);
  latex.DrawLatex(0.4,0.55,text);
  latex.DrawLatex(0.4,0.45,text1);
/*
 JetpT_jes_up[ij][jk]->SetMinimum(0.);
 JetpT_jes_up[ij][jk]->SetMaximum(1.);
 JetpT_jes_dn[ij][jk]->SetMinimum(0.);
 JetpT_jes_dn[ij][jk]->SetMaximum(1.);

 tdrDraw(JetpT_jes_up[ij][jk],kFullCircle,-1,kSolid,kRed,0,2);
 tdrDraw(JetpT_jes_dn[ij][jk],kFullCircle,-1,kSolid,kBlue,0,2);

 leg_pt[ij][jk]->AddEntry(JetpT_jes_up[ij][jk],"JES Up","l");
 leg_pt[ij][jk]->AddEntry(JetpT_jes_dn[ij][jk],"JES Dn","l");

 leg_pt[ij][jk]->Draw();
*/

if(ud==0){
for(int kl=0; kl<njes; kl++){

  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->CenterTitle();

  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty");
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->CenterTitle();
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleOffset(0.8);

  JetpT_jes_up_fac[ij][jk][kl]->Smooth(5);

  tdrDraw(JetpT_jes_up_fac[ij][jk][kl],sty_jes[kl],-1,sty_jes[kl],col_jes[kl],0,2) ;
  leg_pt[ud][ij][jk]->AddEntry(JetpT_jes_up_fac[ij][jk][kl],jes_name[kl],"l");
 }
 
 JetpT_jes_up_sum[ij][jk]->Smooth(5);
 tdrDraw(JetpT_jes_up_sum[ij][jk],kSolid,-1,kSolid,kBlack,0,2) ;
 leg_pt[ud][ij][jk]->AddEntry(JetpT_jes_up_sum[ij][jk],"Sum","l");
 
 JetpT_jes_up[ij][jk]->Smooth(5);
 tdrDraw(JetpT_jes_up[ij][jk],kSolid,-1,kSolid,kBlue+3,0,2) ;
 leg_pt[ud][ij][jk]->AddEntry(JetpT_jes_up[ij][jk],"Total","l");

 leg_pt[ud][ij][jk]->Draw();

 sprintf(name,"JES_Plots/Pt_Plots/Factorised/Legacy2016/JES_Up/%s.eps",c2[ud][ij][jk]->GetName());
 c2[ud][ij][jk]->SaveAs(name);
	}

if(ud==1){
for(int kl=0; kl<njes; kl++){

  JetpT_jes_dn_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetpT_jes_dn_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetpT_jes_dn_fac[ij][jk][kl]->GetXaxis()->CenterTitle();
  JetpT_jes_dn_fac[ij][jk][kl]->GetXaxis()->SetRangeUser(min_range,max_range);

  JetpT_jes_dn_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty");
  JetpT_jes_dn_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetpT_jes_dn_fac[ij][jk][kl]->GetYaxis()->CenterTitle();
  JetpT_jes_dn_fac[ij][jk][kl]->GetYaxis()->SetTitleOffset(0.8);

  JetpT_jes_dn_fac[ij][jk][kl]->Smooth(5);

  tdrDraw(JetpT_jes_dn_fac[ij][jk][kl],sty_jes[kl],-1,sty_jes[kl],col_jes[kl],0,2) ;
  leg_pt[ud][ij][jk]->AddEntry(JetpT_jes_dn_fac[ij][jk][kl],jes_name[kl],"l");
 }
 
 JetpT_jes_dn_sum[ij][jk]->Smooth(5);
 tdrDraw(JetpT_jes_dn_sum[ij][jk],kSolid,-1,kSolid,kBlack,0,2) ;
 leg_pt[ud][ij][jk]->AddEntry(JetpT_jes_dn_sum[ij][jk],"Sum","l");
 
 JetpT_jes_dn[ij][jk]->Smooth(5);
 tdrDraw(JetpT_jes_dn[ij][jk],kSolid,-1,kSolid,kBlue+3,0,2) ;
 leg_pt[ud][ij][jk]->AddEntry(JetpT_jes_dn[ij][jk],"Total","l");

 leg_pt[ud][ij][jk]->Draw();

 sprintf(name,"JES_Plots/Pt_Plots/Factorised/Legacy2016/JES_Dn/%s.eps",c2[ud][ij][jk]->GetName());
 c2[ud][ij][jk]->SaveAs(name);
	}
		
  }
 }
}

TCanvas *c3[2][nalgo][Etabins];

TLegend *leg_rad[2][nalgo][Etabins];

for(int ud=0; ud<2; ud++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<Etabins; jk++){

 sprintf(name,"JES_Radius_%s_EtaBin%i_Allfac_%s",JetRad[ij],jk+1,dirname[ud]);
 c3[ud][ij][jk] = tdrCanvas(name,JetRad_jes_up_fac[ij][jk][0],7,0);

 c3[ud][ij][jk]->SetRightMargin(0.3);

 leg_rad[ud][ij][jk] = new TLegend(0.7,0.12,0.95,0.92);
//leg_rad[ud][ij][jk] = new TLegend(0.57,0.42,0.87,0.92);
 leg_rad[ud][ij][jk]->SetBorderSize(0);

 c3[ud][ij][jk]->cd(1);
 gPad->SetLogx(1); 

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.075);

  TString text2;
  text2+= jes_dir[1];
  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

//  latex.DrawLatex(0.35,0.65,text2);
  latex.DrawLatex(0.4,0.55,text);
  latex.DrawLatex(0.4,0.45,text1);

/*
 JetRad_jes_up[ij][jk]->SetMinimum(0.);
 JetRad_jes_up[ij][jk]->SetMaximum(1.);
 JetRad_jes_dn[ij][jk]->SetMinimum(0.);
 JetRad_jes_dn[ij][jk]->SetMaximum(1.);
*/

 JetRad_jes_up[ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
 JetRad_jes_up[ij][jk]->GetXaxis()->CenterTitle();
 JetRad_jes_up[ij][jk]->GetXaxis()->SetTitleSize(0.05);
 JetRad_jes_up[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty");
 JetRad_jes_up[ij][jk]->GetYaxis()->CenterTitle();
 JetRad_jes_up[ij][jk]->GetYaxis()->SetTitleSize(0.05);

 JetRad_jes_dn[ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
 JetRad_jes_dn[ij][jk]->GetXaxis()->CenterTitle();
 JetRad_jes_dn[ij][jk]->GetXaxis()->SetTitleSize(0.05);
 JetRad_jes_dn[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
 JetRad_jes_dn[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty");
 JetRad_jes_dn[ij][jk]->GetYaxis()->CenterTitle();
 JetRad_jes_dn[ij][jk]->GetYaxis()->SetTitleSize(0.05);
 /*
 tdrDraw(JetRad_jes_up[ij][jk],kFullCircle,kRed,kSolid,kRed,0,2);
 tdrDraw(JetRad_jes_dn[ij][jk],kFullCircle,kBlue,kSolid,kBlue,0,2);

 leg_rad[ij][jk]->AddEntry(JetRad_jes_up[ij][jk],"JES_up","l");
 leg_rad[ij][jk]->AddEntry(JetRad_jes_dn[ij][jk],"JES_dn","l");
*/
if(ud==0){
 for(int kl=0; kl<njes; kl++){

  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->CenterTitle();

  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty");
  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->CenterTitle();

  JetRad_jes_up_fac[ij][jk][kl]->Smooth(5);

  tdrDraw(JetRad_jes_up_fac[ij][jk][kl],sty_jes[kl],-1,sty_jes[kl],col_jes[kl],0,2) ;
  leg_rad[ud][ij][jk]->AddEntry(JetRad_jes_up_fac[ij][jk][kl],jes_name[kl],"l");
 }
 
 
 JetRad_jes_up_sum[ij][jk]->Smooth(5);
 tdrDraw(JetRad_jes_up_sum[ij][jk],kSolid,-1,kSolid,kBlack,0,2) ;
 leg_rad[ud][ij][jk]->AddEntry(JetRad_jes_up_sum[ij][jk],"Sum","l");
 
 JetRad_jes_up[ij][jk]->Smooth(5);
 tdrDraw(JetRad_jes_up[ij][jk],kSolid,-1,kSolid,kBlue+3,0,2) ;
 leg_rad[ud][ij][jk]->AddEntry(JetRad_jes_up[ij][jk],"Total","l");

 leg_rad[ud][ij][jk]->Draw();

 sprintf(name,"JES_Plots/Ratio_Plots/Factorised/Legacy2016/JES_Up/%s.eps",c3[ud][ij][jk]->GetName());
 c3[ud][ij][jk]->SaveAs(name);
	}
if(ud==1){
 for(int kl=0; kl<njes; kl++){

  JetRad_jes_dn_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetRad_jes_dn_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetRad_jes_dn_fac[ij][jk][kl]->GetXaxis()->CenterTitle();

  JetRad_jes_dn_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty");
  JetRad_jes_dn_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetRad_jes_dn_fac[ij][jk][kl]->GetYaxis()->CenterTitle();

  JetRad_jes_dn_fac[ij][jk][kl]->Smooth(5);

  tdrDraw(JetRad_jes_dn_fac[ij][jk][kl],sty_jes[kl],-1,sty_jes[kl],col_jes[kl],0,2) ;
  leg_rad[ud][ij][jk]->AddEntry(JetRad_jes_dn_fac[ij][jk][kl],jes_name[kl],"l");
 }
 
 JetRad_jes_dn_sum[ij][jk]->Smooth(5);
 tdrDraw(JetRad_jes_dn_sum[ij][jk],kSolid,-1,kSolid,kBlack,0,2) ;
 leg_rad[ud][ij][jk]->AddEntry(JetRad_jes_dn_sum[ij][jk],"Sum","l");
 
 JetRad_jes_dn[ij][jk]->Smooth(5);
 tdrDraw(JetRad_jes_dn[ij][jk],kSolid,-1,kSolid,kBlue+3,0,2) ;
 leg_rad[ud][ij][jk]->AddEntry(JetRad_jes_dn[ij][jk],"Total","l");
 

 leg_rad[ud][ij][jk]->Draw();

 sprintf(name,"JES_Plots/Ratio_Plots/Factorised/Legacy2016/JES_Dn/%s.eps",c3[ud][ij][jk]->GetName());
 c3[ud][ij][jk]->SaveAs(name);
	}
  }
 }
}
}
