#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>

void Compare_NPFactor()
{
const int nfiles = 4;

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/NP_Correction_Factor_Pythia.root",/*"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/NP_Correction_Factor_Herwig_norm.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/NP_Correction_Factor_Herwig_EE5_norm.root",*/"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/NP_Correction_Factor_Herwig_EE5C_ugur.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/NP_Correction_Factor_Herwig_CUETHppS1.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Pythia8_Rivet/CUETP8M1/NP_Correction_Factor_Pythia_Rivet.root"};

const int ref = 3;

const char *model_name[nfiles] = {"PH+P8(CUETP8M1)"/*,"PH+Herwig(CUETHppS1)","PH+Herwig(EE5)"*/,"PH+Herwig(EE5C)","PH+Herwig(CUETHppS1)","Pythia8(CUETP8M1)"};
const int col[nfiles] = {2/*,4,6*/,9,4,6};

static const int nalgo = 12 ;
static const int netarange = 10 ;

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

float leg_x1 = 0.25;
float leg_y1 = 0.35;
float leg_x2 = 0.45;
float leg_y2 = 0.6;

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

   hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("NP Correction for P_{T} Spectra");
   hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.065);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("NP Correction for Xsection Ratio");
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

    }
  }
 }

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int fg=0; fg<(nfiles-1); fg++){
	hist_pt_diff[fg][ij][jk] = (TH1D*)hist_pt[fg+1][ij][jk]->Clone();
	hist_pt_diff[fg][ij][jk]->Add(hist_pt[0][ij][jk],-1) ;
	
        hist_radius_diff[fg][ij][jk] = (TH1D*)hist_radius[fg+1][ij][jk]->Clone();
	hist_radius_diff[fg][ij][jk]->Add(hist_radius[0][ij][jk],-1) ;

	hist_pt_diff[fg][ij][jk]->GetYaxis()->SetTitle("MC - (PH+P8)");
	
        hist_radius_diff[fg][ij][jk]->GetYaxis()->SetTitle("MC - (PH+P8)");
	hist_radius_diff[fg][ij][jk]->GetYaxis()->SetTitleSize(0.065);

	for(int pt=0; pt<noptbins; pt++){
		if(abs(hist_pt_diff[fg][ij][jk]->GetBinContent(pt+1))<abs(hist_pt_diff[fg][ij][jk]->GetBinError(pt+1))){
			hist_pt_diff[fg][ij][jk]->SetBinContent(pt+1,0);
	//		hist_pt_diff[fg][ij][jk]->SetBinError(pt+1,0);
			}
		if(abs(hist_radius_diff[fg][ij][jk]->GetBinContent(pt+1))<abs(hist_radius_diff[fg][ij][jk]->GetBinError(pt+1))){
                        hist_radius_diff[fg][ij][jk]->SetBinContent(pt+1,0);
          //              hist_pt_diff[fg][ij][jk]->SetBinError(pt+1,0);
                        }
		}
	
   }
  }
 }

TCanvas *c2[nalgo][netarange];
TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   sprintf(name,"NP_Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
   c2[ij][jk] = tdrDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],2,0);

   leg_pt[ij][jk] = tdrLeg(leg_x1,leg_y1,leg_x2,leg_y2);
   leg_pt[ij][jk]->SetTextSize(.035);
   leg_pt[ij][jk]->SetTextFont(42);

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
/*
   latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);
*/
   latex.DrawLatex(0.4,0.85,text);
   latex.DrawLatex(0.4,0.8,text1);

   for(int fg=0; fg<nfiles; fg++){

      hist_pt[fg][ij][jk]->SetMaximum(1.8);
      hist_pt[fg][ij][jk]->SetMinimum(0.0);

      hist_pt[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.5);

      tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"lp");
    }

   c2[ij][jk]->cd(2);
   gPad->SetLogx(1);
 
   for(int fg=0; fg<(nfiles-1); fg++){
	hist_pt_diff[fg][ij][jk]->SetLineColor(col[fg+1]);
        hist_pt_diff[fg][ij][jk]->GetYaxis()->SetTitle("Herwig - P8");
	hist_pt_diff[fg][ij][jk]->GetYaxis()->SetTitleSize(0.065);
	hist_pt_diff[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
	hist_pt_diff[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.0);
	hist_pt_diff[fg][ij][jk]->SetMinimum(-0.3);
	hist_pt_diff[fg][ij][jk]->SetMaximum(0.3);
	if(fg==0) {  hist_pt_diff[fg][ij][jk]->Draw("e"); }
	 else { hist_pt_diff[fg][ij][jk]->Draw("sames"); }
 	}//fg

   sprintf(name,"NP_Plots/Pt_Plots/%s.eps",c2[ij][jk]->GetName());
   c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij

TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

    if((ij<2)&&(jk>6)) continue;

    sprintf(name,"NP_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
    c3[ij][jk] = tdrDiCanvas(name,hist_radius[0][ij][jk],hist_radius[1][ij][jk],2,0);

    leg_radius[ij][jk] = tdrLeg(leg_x1,0.35,leg_x2-0.05,0.55);
    leg_radius[ij][jk]->SetTextSize(0.04);
    leg_radius[ij][jk]->SetTextFont(42);

    c3[ij][jk]->cd(1);

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

    leg_x1 = 0.3;
    leg_x2 = 0.7;
    leg_y1 = 0.85;

    latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
    latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);
	
     for(int fg=0; fg<nfiles; fg++){

	hist_radius[fg][ij][jk]->SetMinimum(0.5);
        hist_radius[fg][ij][jk]->SetMaximum(1.4);

	hist_radius[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.5);

       tdrDraw(hist_radius[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
       leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"lp");
     }//fg

   c3[ij][jk]->cd(2);

   gPad->SetLogx(1);

   for(int fg=0; fg<(nfiles-1); fg++){

	hist_radius_diff[fg][ij][jk]->SetLineColor(col[fg+1]);

	hist_radius_diff[fg][ij][jk]->SetMinimum(-0.3);
	hist_radius_diff[fg][ij][jk]->SetMaximum(0.3);

  	 if(fg==0){
         hist_radius_diff[fg][ij][jk]->Draw("e");
  	 }else{
         hist_radius_diff[fg][ij][jk]->Draw("sames");
        }

     }//fg

	sprintf(name,"NP_Plots/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
	c3[ij][jk]->SaveAs(name);

   }//jk
 }//ij


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
   for(int bn=0; bn<noptbins; bn++){
      pt_err_up[ij][jk][bn] = 0.5*abs(hist_pt_diff[0][ij][jk]->GetBinContent(bn+1))*1./max(1.e-6,hist_pt[0][ij][jk]->GetBinContent(bn+1));
      pt_err_dn[ij][jk][bn] =  pt_err_up[ij][jk][bn];

      rad_err_up[ij][jk][bn] = 0.5*abs(hist_radius_diff[0][ij][jk]->GetBinContent(bn+1))*1./max(1.e-6,hist_radius[0][ij][jk]->GetBinContent(bn+1));
      rad_err_dn[ij][jk][bn] =  rad_err_up[ij][jk][bn];   

      fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<pt_err_up[ij][jk][bn]<<'\t'<<pt_err_dn[ij][jk][bn]<<endl;
      fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<rad_err_up[ij][jk][bn]<<'\t'<<rad_err_dn[ij][jk][bn]<<endl;
    }
  }
 }

fp_pt.close();
fp_rad.close();

}

int main()
{
Compare_NPFactor();
}
