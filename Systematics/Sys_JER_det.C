#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>
#include <iostream>

void Sys_JER_det()
{
const int nfiles = 3;

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_nocor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_nocor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_nocor.root"};

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor.root"};

const char *model_name[nfiles] = {"JER Nominal","JER Up","JER Down"};
const int col[nfiles] = {1,2,4};

const int ref = 4;

const int noptbins = 62;
double ptbins[noptbins+1] = {74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const char* jer_dir[2] = {"up","down"} ;

int col_jer[2] = {2,4};
int sty_jer[2] = {1,2};

char name[1000];

ofstream fp_pt;
fp_pt.open("JER_Pt_Det_Legacy.log");

ofstream fp_rad;
fp_rad.open("JER_Rad_Det_Legacy.log");

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_radius[nfiles][nalgo][netarange];

TH1D* JER_Pt[nalgo][netarange][2];
TH1D* JER_Rad[nalgo][netarange][2];

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){	
    for(int kl=0; kl<2; kl++){
    
	sprintf(name,"Pt_%s_Etabin%i_JER_%s",JetRad[ij],jk+1,jer_dir[kl]);
	JER_Pt[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins);

	sprintf(name,"Rad_%s_Etabin%i_JER_%s",JetRad[ij],jk+1,jer_dir[kl]);
        JER_Rad[ij][jk][kl] = new TH1D(name,name,noptbins,ptbins);

	JER_Pt[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
	JER_Pt[ij][jk][kl]->GetXaxis()->CenterTitle();
	JER_Pt[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
	JER_Pt[ij][jk][kl]->GetXaxis()->SetLabelSize(0.04);

	JER_Pt[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty in p_{T}");
        JER_Pt[ij][jk][kl]->GetYaxis()->CenterTitle();
        JER_Pt[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
        JER_Pt[ij][jk][kl]->GetYaxis()->SetLabelSize(0.035);

	JER_Rad[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
        JER_Rad[ij][jk][kl]->GetXaxis()->CenterTitle();
        JER_Rad[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
        JER_Rad[ij][jk][kl]->GetXaxis()->SetLabelSize(0.04);

        JER_Rad[ij][jk][kl]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection Ratio");
        JER_Rad[ij][jk][kl]->GetYaxis()->CenterTitle();
        JER_Rad[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
        JER_Rad[ij][jk][kl]->GetYaxis()->SetLabelSize(0.035);

   }
 }
}

double jer_pt_up[nalgo][netarange][noptbins] = {{{0.}}};
double jer_pt_dn[nalgo][netarange][noptbins] = {{{0.}}};
double jer_rad_up[nalgo][netarange][noptbins] = {{{0.}}};
double jer_rad_dn[nalgo][netarange][noptbins] = {{{0.}}};

float leg_x1 = 0.25;
float leg_y1 = 0.6;
float leg_x2 = 0.45;
float leg_y2 = 0.9;

float data_lumi = 1.;

double ar[nfiles] = {0};

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

//     sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1);
	if(fg==0) { sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1); }
	if(fg==1) { sprintf(name,"JetpT_%s_EtaBin%i_JER_up",JetRad[ij],jk+1); }
	if(fg==2) { sprintf(name,"JetpT_%s_EtaBin%i_JER_dn",JetRad[ij],jk+1); }

     hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);

  }//jk
 }//ij
}//fg

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   hist_radius[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt[fg][ref][jk]) ;
  }
 }
}

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int bn=0; bn<noptbins; bn++){

   double ar[nfiles] = {0};
   double bs[nfiles] = {0};   

    for(int fg=0; fg<nfiles; fg++){
		ar[fg] = hist_pt[fg][ij][jk]->GetBinContent(bn+1) - hist_pt[0][ij][jk]->GetBinContent(bn+1);
		bs[fg] = hist_radius[fg][ij][jk]->GetBinContent(bn+1) -  hist_radius[0][ij][jk]->GetBinContent(bn+1);
		}

   	if(ar[1]*ar[2]>0){
        if(ar[1]>0) { jer_pt_up[ij][jk][bn] = (abs(ar[1])>abs(ar[2]))?abs(ar[1]):abs(ar[2]) ; jer_pt_dn[ij][jk][bn] = 0.;}
        else { jer_pt_dn[ij][jk][bn] = (abs(ar[1])>abs(ar[2]))?abs(ar[1]):abs(ar[2]) ; jer_pt_up[ij][jk][bn] = 0.;}
        }
        else{
        if(ar[1]>0) { jer_pt_up[ij][jk][bn] = ar[1] ;  jer_pt_dn[ij][jk][bn] = abs(ar[2]) ; }
        else { if (ar[2]>0) {  jer_pt_up[ij][jk][bn] = ar[2] ;  jer_pt_dn[ij][jk][bn] = abs(ar[1]) ; }  }
        }

	if(bs[1]*bs[2]>0){
        if(bs[1]>0) { jer_rad_up[ij][jk][bn] = (abs(bs[1])>abs(bs[2]))?abs(bs[1]):abs(bs[2]) ; jer_rad_dn[ij][jk][bn] = 0.;}
        else { jer_rad_dn[ij][jk][bn] = (abs(bs[1])>abs(bs[2]))?abs(bs[1]):abs(bs[2]) ; jer_rad_up[ij][jk][bn] = 0.;}
        }
        else{
        if(bs[1]>0) { jer_rad_up[ij][jk][bn] = bs[1] ;  jer_rad_dn[ij][jk][bn] = abs(bs[2]) ; }
        else { if (bs[2]>0) {  jer_rad_up[ij][jk][bn] = bs[2] ;  jer_rad_dn[ij][jk][bn] = abs(bs[1]) ; }  }
        }

      }
   }
 }


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int bn=0; bn<noptbins; bn++){

	JER_Pt[ij][jk][0]->SetBinContent(bn+1,jer_pt_up[ij][jk][bn]*1./max(1.e-6,hist_pt[0][ij][jk]->GetBinContent(bn+1)));
	JER_Pt[ij][jk][1]->SetBinContent(bn+1,jer_pt_dn[ij][jk][bn]*1./max(1.e-6,hist_pt[0][ij][jk]->GetBinContent(bn+1)));

	fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<JER_Pt[ij][jk][0]->GetBinContent(bn+1)<<'\t'<<JER_Pt[ij][jk][1]->GetBinContent(bn+1)<<endl;

	JER_Rad[ij][jk][0]->SetBinContent(bn+1,jer_rad_up[ij][jk][bn]*1./max(1.e-6,hist_radius[0][ij][jk]->GetBinContent(bn+1)));
        JER_Rad[ij][jk][1]->SetBinContent(bn+1,jer_rad_dn[ij][jk][bn]*1./max(1.e-6,hist_radius[0][ij][jk]->GetBinContent(bn+1)));

	fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<JER_Rad[ij][jk][0]->GetBinContent(bn+1)<<'\t'<<JER_Rad[ij][jk][1]->GetBinContent(bn+1)<<endl;

	if(ij==3&&jk==0) { cout<<"pt up "<<bn<<" err "<<JER_Pt[ij][jk][0]->GetBinContent(bn+1)<<endl;}

   }
  }
 }


TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

 sprintf(name,"JER_Det_Pt_%s_EtaBin%i",JetRad[ij],jk+1);
 c2[ij][jk] = tdrCanvas(name,JER_Pt[ij][jk][0],6,0);

 leg_pt[ij][jk] = tdrLeg(0.6,0.7,0.95,0.95);

 c2[ij][jk]->cd(1);

 gPad->SetLogx(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.05);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);

  for(int kl=0; kl<2; kl++){
  JER_Pt[ij][jk][kl]->SetMaximum(0.11);
  tdrDraw(JER_Pt[ij][jk][kl],sty_jer[kl],-1,kSolid,col_jer[kl],0,2) ;
  leg_pt[ij][jk]->AddEntry(JER_Pt[ij][jk][kl],jer_dir[kl],"l");
   }

  sprintf(name,"JER_Det_Plots/Pt_Plots/%s.eps",c2[ij][jk]->GetName());
  c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij

TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
 
 if((ij<2)&&(jk>6)) continue;

  sprintf(name,"JER_Det_Ratio_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] = tdrCanvas(name,JER_Rad[ij][jk][0],6,0);

  leg_radius[ij][jk] = tdrLeg(0.6,0.7,0.95,0.95);

  c3[ij][jk]->cd(1);

  gPad->SetLogx(1);
  gPad->SetLogy(0);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.05);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);

  for(int kl=0; kl<2; kl++){
	 JER_Rad[ij][jk][kl]->SetMaximum(0.11);
	 tdrDraw(JER_Rad[ij][jk][kl],sty_jer[kl],-1,kSolid,col_jer[kl],0,2) ;
 	 leg_radius[ij][jk]->AddEntry(JER_Rad[ij][jk][kl],jer_dir[kl],"l");
   }


  sprintf(name,"JER_Det_Plots/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//jk
 }//ij

fp_pt.close();
fp_rad.close();
}

int main()
{
Sys_JER_det();
}
