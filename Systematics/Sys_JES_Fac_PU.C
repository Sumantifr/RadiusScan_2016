#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include <fstream>
#include <TH1D.h>
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

void Sys_JES_Fac_PU()
{
const int nalgo = 12;
const int Etabins = 10;
const int njes = 8;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[Etabins] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const char* jes_name[njes] = {"PileUpDataMC","PileUpPtRef","PileUpPtBB","PileUpPtEC1","PileUpPtEC2","PileUpPtHF","PileUpMuZero","PileUpEnvelope"};
const char* jes_title[njes] = {"PileUpDataMC","PileUpPtRef","0.5 x PileUpPtBB","0.5 x PileUpPtEC1","PileUpPtEC2","PileUpPtHF","PileUpMuZero","PileUpEnvelope"};


const char* jes_dir[2] = {"JES Up","JES Down"};
const char *dirname[2] = {"JES_Up","JES_Down"};

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

double min_range = 84;
double max_range = 1588;

const int ref = 3;

int col_jes[njes] = {kGreen+3,kRed,kBlue,kCyan+3,kPink,kOrange+2,kMagenta+3,kYellow+3};
int sty_jes[njes] = {1,2,3,4,5,6,7,8};
int msty_jes[njes] = {23,0,26,26,0,0,0,0};
/* 
for(int ij=0; ij<njes; ij++){
sty_jes[ij] = ij+1;
}
*/

ofstream fp_pt;
fp_pt.open("JES_Pt_2016_Legacy_wAK4.log");

ofstream fp_rad;
fp_rad.open("JES_Rad_2016_Legacy_wAK4.log");

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

TCanvas *cpt[nalgo][Etabins];
TCanvas *crad[nalgo][Etabins];

TLegend *legpt[nalgo][Etabins];
TLegend *legrad[nalgo][Etabins];

//TFile *file0 = new TFile("/home/suman/RooUnfold/Unfolded_2016_Data_ModJES_Legacy_Jun2019.root","read");
TFile *file0 = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Output_JECPU_2016Total_AK8L1Base.root","read");
//TFile *file0 = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv11/hist_2016CRecoJetchs_PU_Data_total.root","read");
file0->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
	 
  for(int kl=0; kl<(2*njes+1); kl++){

    if(kl==0){
		sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
		}

    if(kl>0&&kl<=(njes)) {
		sprintf(name,"JetpT_%s_EtaBin%i_%s_up",JetRad[ij],jk+1,jes_name[kl-1]);
		}	
	if(kl>(njes)) {
		sprintf(name,"JetpT_%s_EtaBin%i_%s_dn",JetRad[ij],jk+1,jes_name[kl-1-(njes)]);
		}
//	cout<<name<<endl;
	
	Jet_pt[ij][jk][kl] = (TH1D*)file0->Get(name);

  }
	   sprintf(name,"JetpT_%s_EtaBin%i_SubTotalPileUp_up",JetRad[ij],jk+1);
       Jet_pt_tot[ij][jk][0] = (TH1D*)file0->Get(name);
       
	   sprintf(name,"JetpT_%s_EtaBin%i_SubTotalPileUp_dn",JetRad[ij],jk+1);
       Jet_pt_tot[ij][jk][1] = (TH1D*)file0->Get(name);
       
 }//jk
}//ij

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  for(int kl=0; kl<(2*njes+1); kl++){

        Jet_radius[ij][jk][kl] = (TH1D*)Jet_pt[ij][jk][kl]->Clone();
        Jet_radius[ij][jk][kl]->Divide(Jet_pt[ref][jk][kl]);
//        cout<<Jet_radius[ij][jk][kl]->GetName()<<endl;
  }
 for(int kl=0; kl<2; kl++){
	 Jet_radius_tot[ij][jk][kl] = (TH1D*)Jet_pt_tot[ij][jk][kl]->Clone();
	 Jet_radius_tot[ij][jk][kl]->Divide(Jet_pt_tot[ref][jk][kl]);
   }
 }//jk
}//ij

 TLatex latex;
 latex.SetNDC();
 latex.SetTextAngle(0);
 latex.SetTextColor(kBlack);

 latex.SetTextFont(42);
 latex.SetTextAlign(31);
 latex.SetTextSize(0.075);

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

  TH1D *huptot = (TH1D*)Jet_pt_tot[ij][jk][0]->Clone();
  huptot->Divide(Jet_pt[ij][jk][0]);
  huptot->GetXaxis()->SetRangeUser(84,2500);
  huptot->SetMinimum(0.85);
  huptot->SetMaximum(1.15);
  huptot->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  huptot->GetYaxis()->SetTitle("JES Varied Up / JES Nominal for Xsection");
  
  sprintf(name,"Canv_PtSpecta_%s_EtaBin%i_Up",JetRad[ij],jk+1);
  cpt[ij][jk] = tdrCanvas(name,huptot,7,0);
  legpt[ij][jk] = tdrLeg(0.15,0.675,0.35,0.9);
  legpt[ij][jk]->SetBorderSize(0); 
  legpt[ij][jk]->SetTextSize(0.025);
  legpt[ij][jk]->SetTextFont(42);
	 
  for(int kl=1; kl<(njes+1); kl++){
	
	TH1D *h1 = (TH1D*)Jet_pt[ij][jk][kl]->Clone();
	h1->Divide(Jet_pt[ij][jk][0]);
	
	h1->SetLineWidth(2);
	h1->SetStats(0);
	h1->GetXaxis()->SetRangeUser(84,2500);
	gPad->SetLogx(1);
	tdrDraw(h1,0,-1,sty_jes[kl-1],col_jes[kl-1],0,2) ;
	legpt[ij][jk]->AddEntry(h1,jes_title[kl-1],"lp");
   }
   
   tdrDraw(huptot,kSolid,-1,kSolid,kBlack,0,2) ;
   legpt[ij][jk]->AddEntry(huptot,"SubTotalPileUp","lp");
   
   latex.DrawLatex(0.6,0.85,jetname[ij]);
   latex.DrawLatex(0.6,0.75,ybinname[jk]);
   
   sprintf(name,"JES_Plots/Pt_Plots/Factorised/Legacy2016/PU/AK8L1Base/%s.png",cpt[ij][jk]->GetName());
   cpt[ij][jk]->SaveAs(name);
   
   TH1D *huptotrad = (TH1D*)Jet_pt_tot[ij][jk][0]->Clone();
   huptotrad->Divide(Jet_radius[ij][jk][0]);
   huptotrad->GetXaxis()->SetRangeUser(84,2500);
   huptotrad->SetMinimum(0.85);
   huptotrad->SetMaximum(1.15);
   huptotrad->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
   huptotrad->GetYaxis()->SetTitle("JES Varied Up / JES Nominal for Xsection Ratio");
   
   sprintf(name,"Canv_RadiusSpecta_%s_EtaBin%i_Up",JetRad[ij],jk+1);
   crad[ij][jk] = tdrCanvas(name,huptotrad,7,0);
   legrad[ij][jk] = tdrLeg(0.15,0.675,0.35,0.9);
   legrad[ij][jk]->SetBorderSize(0); 
   legrad[ij][jk]->SetTextSize(0.025);
   legrad[ij][jk]->SetTextFont(42);
	 
   for(int kl=1; kl<(njes+1); kl++){
	
	TH1D *h1 = (TH1D*)Jet_radius[ij][jk][kl]->Clone();
	h1->Divide(Jet_radius[ij][jk][0]);
	
	h1->SetLineWidth(2);
	h1->SetStats(0);
	h1->GetXaxis()->SetRangeUser(84,2500);
	gPad->SetLogx(1);
	tdrDraw(h1,0,-1,sty_jes[kl-1],col_jes[kl-1],0,2) ;
	legrad[ij][jk]->AddEntry(h1,jes_title[kl-1],"lp");
   }
   
   tdrDraw(huptotrad,kSolid,-1,kSolid,kBlack,0,2) ;
   legrad[ij][jk]->AddEntry(huptotrad,"SubTotalPileUp","lp");
   
   latex.DrawLatex(0.6,0.85,jetname[ij]);
   latex.DrawLatex(0.6,0.75,ybinname[jk]);
   
   sprintf(name,"JES_Plots/Ratio_Plots/Factorised/Legacy2016/PU/AK8L1Base/%s.png",crad[ij][jk]->GetName());
   crad[ij][jk]->SaveAs(name);
 }
 
}



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

	if (isnan(jes_pt_up[ij][jk][pt][kl-1])) { jes_pt_up[ij][jk][pt][kl] = 1.e-6; }
	if (isnan(jes_pt_up[ij][jk][pt][kl-1])) { jes_pt_dn[ij][jk][pt][kl] = 1.e-6; }

	}

    b0 = Jet_radius[ij][jk][0]->GetBinContent(pt+1);
    
 //   if(ij==0&&jk==0) { cout<<"b0 "<<b0<<endl; }

    for(int kl=1; kl<(njes+1); kl++){

        b1 = Jet_radius[ij][jk][kl]->GetBinContent(pt+1)-b0;
        b2 = Jet_radius[ij][jk][kl+njes]->GetBinContent(pt+1)-b0;
        
 //       if(ij==0&&jk==0&& (kl==njes)) { cout<<"b1 "<<b1<<" b2 "<<b2<<endl; }

        if(b1*b2>0){
			if(b1>0) { jes_radius_up[ij][jk][pt][kl-1] = (abs(b1)>abs(b2))?abs(b1):abs(b2) ; }
			else { jes_radius_dn[ij][jk][pt][kl-1] = (abs(b1)>abs(b2))?abs(b1):abs(b2) ; }
        }
        else{
			if(b1>0) { jes_radius_up[ij][jk][pt][kl-1] = b1 ;  jes_radius_dn[ij][jk][pt][kl-1] = abs(b2) ; }
			else { if (b2>0) {  jes_radius_up[ij][jk][pt][kl-1] = b2 ;  jes_radius_dn[ij][jk][pt][kl-1] = abs(b1) ; }  }
        }

		if (isnan(jes_radius_up[ij][jk][pt][kl-1]) || (jes_radius_up[ij][jk][pt][kl-1]>1.e+6)) { jes_radius_up[ij][jk][pt][kl] = 1.e-6; }
		if (isnan(jes_radius_dn[ij][jk][pt][kl-1]) || (jes_radius_dn[ij][jk][pt][kl-1]>1.e+6)) { jes_radius_dn[ij][jk][pt][kl] = 1.e-6; }

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

   if(ij==0&&jk==0) { cout<<"pt "<<pt+1<<" up "<<jes_pt_up_tot[ij][jk][pt]*1./a0<<endl; }

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
  
	  if(!(kl==0||kl==2||kl==3)) continue;	
	  if(kl==2||kl==3){
				jes_pt_up[ij][jk][pt][kl] *= 0.5; jes_pt_dn[ij][jk][pt][kl] *= 0.5; 
				jes_radius_up[ij][jk][pt][kl] *= 0.5; jes_radius_dn[ij][jk][pt][kl] *= 0.5; 
			   }
  
      jes_pt_up_sum[ij][jk][pt] += pow(jes_pt_up[ij][jk][pt][kl],2.);
      jes_pt_dn_sum[ij][jk][pt] += pow(jes_pt_dn[ij][jk][pt][kl],2.);

      jes_radius_up_sum[ij][jk][pt] += pow(jes_radius_up[ij][jk][pt][kl],2.);
      jes_radius_dn_sum[ij][jk][pt] += pow(jes_radius_dn[ij][jk][pt][kl],2.);

      }
  
      jes_pt_up_sum[ij][jk][pt] = sqrt(jes_pt_up_sum[ij][jk][pt]);
      jes_pt_dn_sum[ij][jk][pt] = sqrt(jes_pt_dn_sum[ij][jk][pt]);
      jes_radius_up_sum[ij][jk][pt] = sqrt(jes_radius_up_sum[ij][jk][pt]);
      jes_radius_dn_sum[ij][jk][pt] = sqrt(jes_radius_dn_sum[ij][jk][pt]);
      
      if(ij==0&&jk==0) { cout<<"rad "<<pt+1<<" up "<<jes_radius_up_tot[ij][jk][pt]*1./b0<<endl; }

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

// fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<JetpT_jes_up_sum[ij][jk]->GetBinContent(pt+1)<<'\t'<<JetpT_jes_dn_sum[ij][jk]->GetBinContent(pt+1)<<endl;
// fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<JetRad_jes_up_sum[ij][jk]->GetBinContent(pt+1)<<'\t'<<JetRad_jes_dn_sum[ij][jk]->GetBinContent(pt+1)<<endl;

 }
 
  JetpT_jes_dn_sum[ij][jk]->Scale(-1); JetpT_jes_dn[ij][jk]->Scale(-1);
  JetRad_jes_dn_sum[ij][jk]->Scale(-1); JetRad_jes_dn[ij][jk]->Scale(-1);

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
		
		double putval;
		
		putval = jes_pt_up[ij][jk][pt][kl]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1); if(isnan(putval)) { putval = 1.e-6; }
		JetpT_jes_up_fac[ij][jk][kl]->SetBinContent(pt+1,putval);
		putval = jes_pt_dn[ij][jk][pt][kl]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1); if(isnan(putval)) { putval = 1.e-6; }
		JetpT_jes_dn_fac[ij][jk][kl]->SetBinContent(pt+1,putval);
   
		putval = jes_radius_up[ij][jk][pt][kl]*1./Jet_radius[ij][jk][0]->GetBinContent(pt+1); if(isnan(putval)) { putval = 1.e-6; }
		JetRad_jes_up_fac[ij][jk][kl]->SetBinContent(pt+1,putval);
		putval = jes_radius_dn[ij][jk][pt][kl]*1./Jet_radius[ij][jk][0]->GetBinContent(pt+1); if(isnan(putval)) { putval = 1.e-6; }
		JetRad_jes_dn_fac[ij][jk][kl]->SetBinContent(pt+1,putval);
	
   }
 }



  JetpT_jes_up_fac[ij][jk][kl]->SetMarkerColor(col_jes[kl]);
  JetpT_jes_up_fac[ij][jk][kl]->SetMarkerStyle(msty_jes[kl]);
  JetpT_jes_up_fac[ij][jk][kl]->SetLineColor(col_jes[kl]);
  JetpT_jes_up_fac[ij][jk][kl]->SetLineStyle(sty_jes[kl]);
  JetpT_jes_up_fac[ij][jk][kl]->SetMinimum(-0.151);
  JetpT_jes_up_fac[ij][jk][kl]->SetMaximum(0.151);

  JetpT_jes_dn_fac[ij][jk][kl]->SetMarkerColor(col_jes[kl]);
  JetpT_jes_dn_fac[ij][jk][kl]->SetMarkerStyle(msty_jes[kl]);
  JetpT_jes_dn_fac[ij][jk][kl]->SetLineColor(col_jes[kl]);
  JetpT_jes_dn_fac[ij][jk][kl]->SetLineStyle(sty_jes[kl]);
  JetpT_jes_dn_fac[ij][jk][kl]->SetMinimum(-0.151);
  JetpT_jes_dn_fac[ij][jk][kl]->SetMaximum(0.151);
  JetpT_jes_dn_fac[ij][jk][kl]->Scale(-1);

  JetRad_jes_up_fac[ij][jk][kl]->SetMarkerColor(col_jes[kl]);
  JetRad_jes_up_fac[ij][jk][kl]->SetMarkerStyle(msty_jes[kl]);
  JetRad_jes_up_fac[ij][jk][kl]->SetLineColor(col_jes[kl]);
  JetRad_jes_up_fac[ij][jk][kl]->SetLineStyle(sty_jes[kl]);
  JetRad_jes_up_fac[ij][jk][kl]->SetMinimum(-0.151);
  JetRad_jes_up_fac[ij][jk][kl]->SetMaximum(0.151);

  JetRad_jes_dn_fac[ij][jk][kl]->SetMarkerColor(col_jes[kl]);
  JetRad_jes_dn_fac[ij][jk][kl]->SetMarkerStyle(msty_jes[kl]);
  JetRad_jes_dn_fac[ij][jk][kl]->SetLineColor(col_jes[kl]);
  JetRad_jes_dn_fac[ij][jk][kl]->SetLineStyle(sty_jes[kl]);
  JetRad_jes_dn_fac[ij][jk][kl]->SetMinimum(-0.151);
  JetRad_jes_dn_fac[ij][jk][kl]->SetMaximum(0.151);
  JetRad_jes_dn_fac[ij][jk][kl]->Scale(-1);
  

  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetLabelSize(0.05);
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->CenterTitle();
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetNoExponent();
  JetpT_jes_up_fac[ij][jk][kl]->GetXaxis()->SetRangeUser(min_range,max_range);

  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection");
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetLabelSize(0.05);
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->CenterTitle();
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleOffset(0.175);
  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetNdivisions(406);
  
  JetpT_jes_up_fac[ij][jk][kl]->SetLineWidth(2);
  JetpT_jes_dn_fac[ij][jk][kl]->SetLineWidth(2);

  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetLabelSize(0.05);
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->CenterTitle();
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetNoExponent();
  JetRad_jes_up_fac[ij][jk][kl]->GetXaxis()->SetRangeUser(min_range,max_range);

  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty in Ratio of Xsections");
  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetLabelSize(0.05);
  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->CenterTitle();
  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleOffset(0.175);
  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetNdivisions(505);
  
  JetRad_jes_up_fac[ij][jk][kl]->SetLineWidth(2);
  JetRad_jes_dn_fac[ij][jk][kl]->SetLineWidth(2);
  JetRad_jes_dn_fac[ij][jk][kl]->SetLineWidth(2);

  if(ij==0&&jk==0 && kl==(njes-1)){
	  for(int pt=0; pt<noptbins; pt++){
	  cout<<" pt "<<pt+1<<" "<<JetRad_jes_up_fac[ij][jk][kl]->GetBinContent(pt+1)<<endl;
			}
	  }

  }

 }
}

TCanvas *c2[nalgo][Etabins];
TLegend *leg_pt[nalgo][Etabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

 sprintf(name,"JES_Pt_%s_EtaBin%i_Allfac",JetRad[ij],jk+1);
 c2[ij][jk] = tdrCanvas(name,JetpT_jes_up_fac[ij][jk][0],7,0);

 c2[ij][jk]->SetRightMargin(0.275); // open for fac

 leg_pt[ij][jk] = new TLegend(0.725,0.12,0.975,0.92);
// leg_pt[ij][jk] = new TLegend(0.57,0.42,0.87,0.92);
 leg_pt[ij][jk]->SetBorderSize(1);
 leg_pt[ij][jk]->SetTextSize(0.0315);

 c2[ij][jk]->cd(1);
 gPad->SetLogx(1);

  TString text2;
  text2+= jes_dir[1];
  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

//  latex.DrawLatex(0.3,0.65,text2);
  latex.DrawLatex(0.4,0.85,text);
  latex.DrawLatex(0.4,0.75,text1);


for(int kl=0; kl<njes; kl++){
	
  if(!(kl==0||kl==2||kl==3)) continue;	
	
  JetpT_jes_up_fac[ij][jk][kl]->Smooth(5);
  JetpT_jes_dn_fac[ij][jk][kl]->Smooth(5);

  JetpT_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleOffset(1.25);

  tdrDraw(JetpT_jes_up_fac[ij][jk][kl],"LP",msty_jes[kl],col_jes[kl],sty_jes[kl],col_jes[kl],0,2) ;
  leg_pt[ij][jk]->AddEntry(JetpT_jes_up_fac[ij][jk][kl],jes_title[kl],"lp");
  tdrDraw(JetpT_jes_dn_fac[ij][jk][kl],"LP",msty_jes[kl],col_jes[kl],sty_jes[kl],col_jes[kl],0,2) ;
 }
 
 JetpT_jes_up_sum[ij][jk]->Smooth(5);
 JetpT_jes_up_sum[ij][jk]->SetMarkerStyle(kFullCircle);
 tdrDraw(JetpT_jes_up_sum[ij][jk],"LP",kFullCircle,kBlack,kSolid,kBlack,0,2) ;
 leg_pt[ij][jk]->AddEntry(JetpT_jes_up_sum[ij][jk],"SubTotalPileUp","lp");
 
 JetpT_jes_dn_sum[ij][jk]->Smooth(5);
 tdrDraw(JetpT_jes_dn_sum[ij][jk],"LP",kFullCircle,kBlack,kSolid,kBlack,0,2) ;
 
// JetpT_jes_up[ij][jk]->Smooth(5);
// tdrDraw(JetpT_jes_up[ij][jk],kSolid,-1,kSolid,kBlue+3,0,2) ;
// leg_pt[ij][jk]->AddEntry(JetpT_jes_up[ij][jk],"Total","l");
 
// JetpT_jes_dn[ij][jk]->Smooth(5);
// tdrDraw(JetpT_jes_dn[ij][jk],kSolid,-1,kSolid,kBlue+3,0,2) ;
 
 leg_pt[ij][jk]->Draw();

 sprintf(name,"JES_Plots/Pt_Plots/Factorised/Legacy2016/PU/AK8L1Base/%s.png",c2[ij][jk]->GetName());
 c2[ij][jk]->SaveAs(name);
	
  }
 }


TCanvas *c3[nalgo][Etabins];

TLegend *leg_rad[nalgo][Etabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

 sprintf(name,"JES_Radius_%s_EtaBin%i_Allfac",JetRad[ij],jk+1);
 c3[ij][jk] = tdrCanvas(name,JetRad_jes_up_fac[ij][jk][0],7,0);

 c3[ij][jk]->SetRightMargin(0.275);

 leg_rad[ij][jk] = new TLegend(0.727,0.12,0.975,0.92);
//leg_rad[ud][ij][jk] = new TLegend(0.57,0.42,0.87,0.92);
 leg_rad[ij][jk]->SetBorderSize(1);
 leg_rad[ij][jk]->SetTextSize(0.0315);

 c3[ij][jk]->cd(1);
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
  latex.DrawLatex(0.4,0.85,text);
  latex.DrawLatex(0.4,0.75,text1);
  
 for(int kl=0; kl<njes; kl++){

  if(!(kl==0||kl==2||kl==3)) continue;
	 
  JetRad_jes_up_fac[ij][jk][kl]->Smooth(5);
  JetRad_jes_dn_fac[ij][jk][kl]->Smooth(5);

  JetRad_jes_up_fac[ij][jk][kl]->GetYaxis()->SetTitleOffset(1.25);
  
//  if(ij==0&&jk==0){ cout<<kl+1<<" mstyle "<<JetRad_jes_up_fac[ij][jk][kl]->GetMarkerStyle()<<endl; }
 // JetRad_jes_up_fac[ij][jk][kl]->Draw("SAME:LP");
  
  tdrDraw(JetRad_jes_up_fac[ij][jk][kl],"LP",msty_jes[kl],col_jes[kl],sty_jes[kl],col_jes[kl],0,2) ;
  leg_rad[ij][jk]->AddEntry(JetRad_jes_up_fac[ij][jk][kl],jes_title[kl],"lp");
  tdrDraw(JetRad_jes_dn_fac[ij][jk][kl],"LP",msty_jes[kl],col_jes[kl],sty_jes[kl],col_jes[kl],0,2) ;
 }
 
 
 JetRad_jes_up_sum[ij][jk]->Smooth(5);
 JetRad_jes_up_sum[ij][jk]->SetMarkerStyle(kFullCircle);
 tdrDraw(JetRad_jes_up_sum[ij][jk],"LP",kFullCircle,kBlack,kSolid,kBlack,0,2) ;
 leg_rad[ij][jk]->AddEntry(JetRad_jes_up_sum[ij][jk],"Total","lp");
 
 JetRad_jes_dn_sum[ij][jk]->Smooth(5);
 tdrDraw(JetRad_jes_dn_sum[ij][jk],"LP",kFullCircle,kBlack,kSolid,kBlack,0,2) ;
 
// JetRad_jes_up[ij][jk]->Smooth(5);
// tdrDraw(JetRad_jes_up[ij][jk],kSolid,-1,kSolid,kBlue+3,0,2) ;
// leg_rad[ij][jk]->AddEntry(JetRad_jes_up[ij][jk],"Total","l");
 
// JetRad_jes_dn[ij][jk]->Smooth(5);
// tdrDraw(JetRad_jes_dn[ij][jk],kSolid,-1,kSolid,kBlue+3,0,2) ;
 
 leg_rad[ij][jk]->Draw();

 sprintf(name,"JES_Plots/Ratio_Plots/Factorised/Legacy2016/PU/AK8L1Base/%s.png",c3[ij][jk]->GetName());
 c3[ij][jk]->SaveAs(name);
	

 }
}

}
