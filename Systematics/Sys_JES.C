#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include <fstream>
#include <TH1D.h>
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

void Sys_JES()
{
const int nalgo = 12;
const int Etabins = 10;
const int njes = 26;

double min_range = 84., max_range = 2500.;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[Etabins] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const char* jes_name[njes] =  {"AbsoluteStat", "AbsoluteScale", "AbsoluteFlavMap", "AbsoluteMPFBias", "Fragmentation", "SinglePionHCAL", "SinglePionECAL", "FlavorQCD", "TimePt", "TimeEta", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativeFSR", "RelativePtBB", "RelativePtEC1", "RelativePtEC2","RelativePtHF", "RelativeStatEC", "RelativeStatHF", "PileUpDataMC", "PileUpPtRef", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF"};

const char* jes_dir[2] = {"JES Up","JES Down"};

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int ref = 3;

int col_jes[njes] = {1,2,3,4,5,6,7,8,9,11,kCyan+2,kCyan-10, kBlue-7, kMagenta-9, kRed-5,40,41,42,43,44,45,46,28,32,36,49};
int sty_jes[njes];
 
for(int ij=0; ij<njes; ij++){
sty_jes[ij] = ij+1;
}

ofstream fp_pt;
fp_pt.open("JES_Pt.log");

ofstream fp_rad;
fp_rad.open("JES_Rad.log");

char name[100];

TH1D *Jet_pt[nalgo][Etabins][2*njes+1];
TH1D *Jet_radius[nalgo][Etabins][2*njes+1];

double jes_pt_up[nalgo][Etabins][noptbins][njes] = {{{{0.}}}};
double jes_pt_dn[nalgo][Etabins][noptbins][njes] = {{{{0.}}}};
double jes_radius_up[nalgo][Etabins][noptbins][njes] = {{{{0.}}}};
double jes_radius_dn[nalgo][Etabins][noptbins][njes] = {{{{0.}}}};

double jes_pt_up_tot[nalgo][Etabins][noptbins] = {{{0.}}};
double jes_pt_dn_tot[nalgo][Etabins][noptbins] = {{{0.}}};
double jes_radius_up_tot[nalgo][Etabins][noptbins] = {{{0.}}};
double jes_radius_dn_tot[nalgo][Etabins][noptbins] = {{{0.}}};

TFile *file0 = new TFile("/home/suman/RooUnfold/Unfolded_2016_Data_JES.root","read");
file0->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  for(int kl=0; kl<(2*njes+1); kl++){
 
	sprintf(name,"bayes_unfold_%s_Etabin%i_JES%i",JetRad[ij],jk+1,kl);
	Jet_pt[ij][jk][kl] = (TH1D*)file0->Get(name);

  }
 }//jk
}//ij

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  for(int kl=0; kl<(2*njes+1); kl++){

        Jet_radius[ij][jk][kl] = (TH1D*)Jet_pt[ij][jk][kl]->Clone();
        Jet_radius[ij][jk][kl]->Divide(Jet_pt[ref][jk][kl]);
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
			if(b1>0) { jes_radius_up[ij][jk][pt][kl-1] = abs(b1);/*(abs(b1)>abs(b2))?abs(b1):abs(b2) ;*/ }
			else { jes_radius_dn[ij][jk][pt][kl-1] = abs(b2);/*(abs(b1)>abs(b2))?abs(b1):abs(b2) ;*/ }
        }
        else{
			if(b1>0) { jes_radius_up[ij][jk][pt][kl-1] = b1 ;  jes_radius_dn[ij][jk][pt][kl-1] = abs(b2) ; }
			else { if (b2>0) {  jes_radius_up[ij][jk][pt][kl-1] = b2 ;  jes_radius_dn[ij][jk][pt][kl-1] = abs(b1) ; }  }
        }

    }

    for(int kl=0; kl<njes; kl++){
  
      jes_pt_up_tot[ij][jk][pt] += pow(jes_pt_up[ij][jk][pt][kl],2.);
      jes_pt_dn_tot[ij][jk][pt] += pow(jes_pt_dn[ij][jk][pt][kl],2.);

      jes_radius_up_tot[ij][jk][pt] += pow(jes_radius_up[ij][jk][pt][kl],2.);
      jes_radius_dn_tot[ij][jk][pt] += pow(jes_radius_dn[ij][jk][pt][kl],2.);

     }
  
      jes_pt_up_tot[ij][jk][pt] = sqrt(jes_pt_up_tot[ij][jk][pt]);
      jes_pt_dn_tot[ij][jk][pt] = sqrt(jes_pt_dn_tot[ij][jk][pt]);
      jes_radius_up_tot[ij][jk][pt] = sqrt(jes_radius_up_tot[ij][jk][pt]);
      jes_radius_dn_tot[ij][jk][pt] = sqrt(jes_radius_dn_tot[ij][jk][pt]);

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

 for(int pt=0; pt<noptbins; pt++){
  
 if(Jet_pt[ij][jk][0]->GetBinContent(pt+1)>1.e-10){
	JetpT_jes_up[ij][jk]->SetBinContent(pt+1,jes_pt_up_tot[ij][jk][pt]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1));
	JetpT_jes_dn[ij][jk]->SetBinContent(pt+1,jes_pt_dn_tot[ij][jk][pt]*1./Jet_pt[ij][jk][0]->GetBinContent(pt+1));
 }


 if(Jet_radius[ij][jk][0]->GetBinContent(pt+1)>1.e-10){
	JetRad_jes_up[ij][jk]->SetBinContent(pt+1,jes_radius_up_tot[ij][jk][pt] * 1./Jet_radius[ij][jk][0]->GetBinContent(pt+1));
	JetRad_jes_dn[ij][jk]->SetBinContent(pt+1,jes_radius_dn_tot[ij][jk][pt] *1./Jet_radius[ij][jk][0]->GetBinContent(pt+1));
  }

 fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<JetpT_jes_up[ij][jk]->GetBinContent(pt+1)<<'\t'<<JetpT_jes_dn[ij][jk]->GetBinContent(pt+1)<<endl;
 fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<JetRad_jes_up[ij][jk]->GetBinContent(pt+1)<<'\t'<<JetRad_jes_dn[ij][jk]->GetBinContent(pt+1)<<endl;

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

  }

 }
}

TCanvas *c2[nalgo][Etabins];
TLegend *leg_pt[nalgo][Etabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

 sprintf(name,"JES_Pt_%s_EtaBin%i_Allfac",JetRad[ij],jk+1);
 c2[ij][jk] = tdrCanvas(name,JetpT_jes_up[ij][jk],7,0);

// c2[ij][jk]->SetRightMargin(0.3); // open for fac

// leg_pt[ij][jk] = new TLegend(0.7,0.12,0.97,0.92);
 leg_pt[ij][jk] = new TLegend(0.35,0.67,0.62,0.88);
 leg_pt[ij][jk]->SetBorderSize(0);
 leg_pt[ij][jk]->SetTextSize(0.05);
 leg_pt[ij][jk]->SetTextFont(42);

 c2[ij][jk]->cd(1);
 gPad->SetLogx(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.06);

  TString text2;
  text2+= jes_dir[1];
  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

//  latex.DrawLatex(0.3,0.65,text2);
  latex.DrawLatex(0.4,0.35,text);
  latex.DrawLatex(0.4,0.275,text1);

 JetpT_jes_dn[ij][jk]->Scale(-1);

 JetpT_jes_up[ij][jk]->SetMinimum(-0.25);
 JetpT_jes_up[ij][jk]->SetMaximum(0.25);
 JetpT_jes_dn[ij][jk]->SetMinimum(-0.25);
 JetpT_jes_dn[ij][jk]->SetMaximum(0.25);

 
 JetpT_jes_up[ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
 JetpT_jes_up[ij][jk]->GetXaxis()->CenterTitle();
 JetpT_jes_up[ij][jk]->GetXaxis()->SetTitleSize(0.055);
 JetpT_jes_up[ij][jk]->GetXaxis()->SetLabelSize(0.06);

 JetpT_jes_up[ij][jk]->GetYaxis()->SetTitle("Relative Unc in Xsection");
 JetpT_jes_up[ij][jk]->GetYaxis()->CenterTitle();
 JetpT_jes_up[ij][jk]->GetYaxis()->SetTitleSize(0.055);
 JetpT_jes_up[ij][jk]->GetYaxis()->SetTitleOffset(1.025);
 JetpT_jes_up[ij][jk]->GetYaxis()->SetLabelSize(0.05);
 JetpT_jes_up[ij][jk]->GetYaxis()->SetNdivisions(406);

 JetpT_jes_dn[ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
 JetpT_jes_dn[ij][jk]->GetXaxis()->SetTitleSize(0.075);
 JetpT_jes_dn[ij][jk]->GetXaxis()->SetLabelSize(0.06);

 JetpT_jes_dn[ij][jk]->GetYaxis()->SetTitle("Relative Unc in Xsection");
 JetpT_jes_dn[ij][jk]->GetYaxis()->SetTitleSize(0.075);
 JetpT_jes_dn[ij][jk]->GetYaxis()->SetLabelSize(0.05);

 JetpT_jes_up[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
 JetpT_jes_dn[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

 JetpT_jes_up[ij][jk]->Smooth();
 JetpT_jes_dn[ij][jk]->Smooth();
 
 tdrDraw(JetpT_jes_up[ij][jk],kFullCircle,-1,kSolid,kRed,0,2);
 tdrDraw(JetpT_jes_dn[ij][jk],kFullCircle,-1,kSolid,kBlue,0,2);

 leg_pt[ij][jk]->AddEntry(JetpT_jes_up[ij][jk],"JES Up","l");
 leg_pt[ij][jk]->AddEntry(JetpT_jes_dn[ij][jk],"JES Dn","l");

 leg_pt[ij][jk]->Draw();

/*
for(int kl=0; kl<njes; kl++){

  JetpT_jes_dn_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetpT_jes_dn_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetpT_jes_dn_fac[ij][jk][kl]->GetXaxis()->CenterTitle();

  JetpT_jes_dn_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty");
  JetpT_jes_dn_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetpT_jes_dn_fac[ij][jk][kl]->GetYaxis()->CenterTitle();

  tdrDraw(JetpT_jes_dn_fac[ij][jk][kl],sty_jes[kl],-1,kSolid,col_jes[kl],0,2) ;
  leg_pt[ij][jk]->AddEntry(JetpT_jes_dn_fac[ij][jk][kl],jes_name[kl],"l");
 }

 leg_pt[ij][jk]->Draw();
*/
 sprintf(name,"JES_Plots/Pt_Plots/Total_Unc/%s.eps",c2[ij][jk]->GetName());
 c2[ij][jk]->SaveAs(name);

 }
}

TCanvas *c3[nalgo][Etabins];

TLegend *leg_rad[nalgo][Etabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

 sprintf(name,"JES_Radius_%s_EtaBin%i_Allfac",JetRad[ij],jk+1);
 c3[ij][jk] = tdrCanvas(name,JetRad_jes_up[ij][jk],7,0);

// c3[ij][jk]->SetRightMargin(0.3);

// leg_rad[ij][jk] = new TLegend(0.7,0.12,0.97,0.92);
 leg_rad[ij][jk] = new TLegend(0.4,0.68,0.65,0.88);
 leg_rad[ij][jk]->SetBorderSize(0);
 leg_rad[ij][jk]->SetTextSize(0.05);
 leg_rad[ij][jk]->SetTextFont(42);


 c3[ij][jk]->cd(1);
 gPad->SetLogx(1); 

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.06);

  TString text2;
  text2+= jes_dir[1];
  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

//  latex.DrawLatex(0.35,0.65,text2);
  latex.DrawLatex(0.45,0.4,text);
  latex.DrawLatex(0.45,0.325,text1);

 JetRad_jes_dn[ij][jk]->Scale(-1);

 JetRad_jes_up[ij][jk]->SetMinimum(-0.105);
 JetRad_jes_up[ij][jk]->SetMaximum(0.105);
 JetRad_jes_dn[ij][jk]->SetMinimum(-0.105);
 JetRad_jes_dn[ij][jk]->SetMaximum(0.105);

 JetRad_jes_up[ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
 JetRad_jes_up[ij][jk]->GetXaxis()->CenterTitle();
 JetRad_jes_up[ij][jk]->GetXaxis()->SetTitleSize(0.06);
 JetRad_jes_up[ij][jk]->GetXaxis()->SetLabelSize(0.05);

 JetRad_jes_up[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty");
 JetRad_jes_up[ij][jk]->GetYaxis()->CenterTitle();
 JetRad_jes_up[ij][jk]->GetYaxis()->CenterTitle();
 JetRad_jes_up[ij][jk]->GetYaxis()->SetTitleSize(0.05);
 JetRad_jes_up[ij][jk]->GetYaxis()->SetLabelSize(0.05);
 JetRad_jes_up[ij][jk]->GetYaxis()->SetTitleOffset(1.2);

 JetRad_jes_dn[ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
 JetRad_jes_dn[ij][jk]->GetXaxis()->CenterTitle();
 JetRad_jes_dn[ij][jk]->GetXaxis()->SetLabelSize(0.05);
 JetRad_jes_dn[ij][jk]->GetXaxis()->SetTitleSize(0.06);
 JetRad_jes_dn[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty");
 JetRad_jes_dn[ij][jk]->GetYaxis()->CenterTitle();
 JetRad_jes_dn[ij][jk]->GetYaxis()->SetTitleSize(0.05);
 
 JetRad_jes_up[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
 JetRad_jes_dn[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

 JetRad_jes_up[ij][jk]->Smooth(1);
 JetRad_jes_dn[ij][jk]->Smooth(1);

 tdrDraw(JetRad_jes_up[ij][jk],kFullCircle,kRed,kSolid,kRed,0,2);
 tdrDraw(JetRad_jes_dn[ij][jk],kFullCircle,kBlue,kSolid,kBlue,0,2);

 leg_rad[ij][jk]->AddEntry(JetRad_jes_up[ij][jk],"JES Up","l");
 leg_rad[ij][jk]->AddEntry(JetRad_jes_dn[ij][jk],"JES Down","l");
/*
 for(int kl=0; kl<njes; kl++){

  JetRad_jes_dn_fac[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  JetRad_jes_dn_fac[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
  JetRad_jes_dn_fac[ij][jk][kl]->GetXaxis()->CenterTitle();

  JetRad_jes_dn_fac[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty");
  JetRad_jes_dn_fac[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
  JetRad_jes_dn_fac[ij][jk][kl]->GetYaxis()->CenterTitle();

  tdrDraw(JetRad_jes_dn_fac[ij][jk][kl],sty_jes[kl],-1,kSolid,col_jes[kl],0,2) ;
  leg_rad[ij][jk]->AddEntry(JetRad_jes_dn_fac[ij][jk][kl],jes_name[kl],"l");
 }
*/
 leg_rad[ij][jk]->Draw();

 sprintf(name,"JES_Plots/Ratio_Plots/Total_Unc/%s.eps",c3[ij][jk]->GetName());
 c3[ij][jk]->SaveAs(name);

 }
}


}
