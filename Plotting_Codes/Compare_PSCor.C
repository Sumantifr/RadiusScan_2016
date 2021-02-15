#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>

void Compare_PSCor()
{
const int nfiles = 1;

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Pythia8_Rivet/CUETP8M1/Pure_PS1_Correction_Factor_Pythia_Rivet.root"};

const int ref = 4;

const char *model_name[nfiles] = {"P8(CUETP8M1)"};
//const int col[nfiles] = {2/*,4,6*/,9,4,6};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const int algo_col[nalgo] = {2,3,4,6,7,11,kCyan+2,kCyan-10, kBlue-7, kMagenta-9, kRed-5, kYellow-6};//{2,3,4,5,6,7,9,12,28,37,44,49};
const int algo_sty[nalgo] = {2,3,4,5,8,21,22,23,25,26,27,28};

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int noptbins = 62;

char name[1000];

ofstream fp_pt;
fp_pt.open("NP_Pt.log");

ofstream fp_rad;
fp_rad.open("NP_Rad.log");

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_diff[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_diff[nfiles-1][nalgo][netarange];

double pt_err_up[nalgo][netarange][noptbins];
double pt_err_dn[nalgo][netarange][noptbins];
double rad_err_up[nalgo][netarange][noptbins];
double rad_err_dn[nalgo][netarange][noptbins];

float leg_x1 = 0.6;
float leg_y1 = 0.6;
float leg_x2 = 0.85;
float leg_y2 = 0.9;

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   sprintf(name,"NP_Correction_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);

   sprintf(name,"NP_Correction_radius_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_radius[fg][ij][jk] = (TH1D*)filein->Get(name);

   hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.065);
   hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();

   hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("PS Correction for P_{T} Spectra");
   hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.065);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("PS Correction for Xsection Ratio");
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

    }
  }
 }

TCanvas *c2[netarange];
TLegend *leg_pt[netarange];

 for(int jk=0; jk<netarange; jk++){

   sprintf(name,"NP_Pt_Compare_Canv_EtaBin%i",jk+1);
   c2[jk] = tdrCanvas(name,hist_pt[0][nalgo-1][jk],6,0);

   leg_pt[jk] = tdrLeg(leg_x1,leg_y1,leg_x2,leg_y2);
   leg_pt[jk]->SetTextSize(.035);
   leg_pt[jk]->SetTextFont(42);

   c2[jk]->cd(1);
   gPad->SetLogx(1);

   TLatex latex;
   latex.SetNDC();
   latex.SetTextAngle(0);
   latex.SetTextColor(kBlack);

   latex.SetTextFont(42);
   latex.SetTextAlign(31);
   latex.SetTextSize(0.05);

   TString text1;
   text1+=  ybinname[jk];
/*
   latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);
*/
   latex.DrawLatex(0.4,0.8,text1);

   for(int fg=0; fg<nfiles; fg++){
    for(int ij=0; ij<nalgo; ij++){

      hist_pt[fg][ij][jk]->SetMaximum(1.8);
      hist_pt[fg][ij][jk]->SetMinimum(0.0);

      hist_pt[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.5);

      tdrDraw(hist_pt[fg][ij][jk],algo_sty[ij],algo_col[ij],algo_sty[ij],algo_col[ij],1001,2);
      leg_pt[jk]->AddEntry(hist_pt[fg][ij][jk],jetname[ij],"lp");
    }
   }

   sprintf(name,"PS_Plots/Pt_Plots/%s.eps",c2[jk]->GetName());
   c2[jk]->SaveAs(name);

  }//jk

TCanvas *c3[netarange];

TLegend *leg_radius[netarange];

 for(int jk=0; jk<netarange; jk++){

 //   if((ij<2)&&(jk>6)) continue;

    sprintf(name,"PS_Compare_Canv_EtaBin%i",jk+1);
    c3[jk] = tdrCanvas(name,hist_radius[0][nalgo-1][jk],6,0);

    leg_radius[jk] = tdrLeg(leg_x1,leg_y1,leg_x2,leg_y2);
    leg_radius[jk]->SetTextSize(0.04);
    leg_radius[jk]->SetTextFont(42);

    c3[jk]->cd(1);

    gPad->SetLogx(1);

    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);

    latex.SetTextFont(42);
    latex.SetTextAlign(31);
    latex.SetTextSize(0.05);
    
    TString text1;
    text1+=  ybinname[jk];

    leg_x1 = 0.3;
    leg_x2 = 0.7;
    leg_y1 = 0.85;

    latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);
	
     for(int fg=0; fg<nfiles; fg++){
	for(int ij=0; ij<nalgo; ij++){

	hist_radius[fg][ij][jk]->SetMinimum(0.0);
        hist_radius[fg][ij][jk]->SetMaximum(2.1);

	hist_radius[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.5);

       tdrDraw(hist_radius[fg][ij][jk],algo_sty[ij],algo_col[ij],algo_sty[ij],algo_col[ij],1001,2);
       leg_radius[jk]->AddEntry(hist_radius[fg][ij][jk],jetname[ij],"lp");

     }//ij
    }//fg

	sprintf(name,"PS_Plots/Ratio_Plots/%s.eps",c3[jk]->GetName());
	c3[jk]->SaveAs(name);

  }//jk

}

int main()
{
Compare_PSCor();
}
