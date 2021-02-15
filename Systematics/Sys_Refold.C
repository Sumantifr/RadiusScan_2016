#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include <fstream>
#include <TH1D.h>
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

void Sys_Refold()
{
const int nalgo = 12;
const int Etabins = 10;

const int noptbins = 61;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[Etabins] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

int ref = 3;

char name[100];

//TFile *filein = new TFile("/home/suman/RooUnfold/Unfolded_2016_Data.root");
//TFile *filein = new TFile("/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excor.root");
TFile *filein = new TFile("/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root");

TH1D *hist_pt[nalgo][Etabins];
TH1D *hist_rad[nalgo][Etabins];

double refold_pt_up[nalgo][Etabins][noptbins];
double refold_pt_dn[nalgo][Etabins][noptbins];
double refold_rad_up[nalgo][Etabins][noptbins];
double refold_rad_dn[nalgo][Etabins][noptbins];

filein->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

  sprintf(name,"Bayes_%s_EtaBin%i_back",JetRad[ij],jk+1);
  hist_pt[ij][jk] = (TH1D*)filein->Get(name);

  hist_pt[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
  hist_pt[ij][jk]->GetXaxis()->SetTitleSize(0.05);
  hist_pt[ij][jk]->GetXaxis()->SetLabelSize(0.05);
  hist_pt[ij][jk]->GetXaxis()->CenterTitle();
  hist_pt[ij][jk]->GetXaxis()->SetRangeUser(74,3000.);

  hist_pt[ij][jk]->GetYaxis()->SetTitle("Refolded / Original");
  hist_pt[ij][jk]->GetYaxis()->SetTitleSize(0.05);
  hist_pt[ij][jk]->GetYaxis()->SetLabelSize(0.05);
  hist_pt[ij][jk]->GetYaxis()->CenterTitle();
  hist_pt[ij][jk]->GetYaxis()->SetNdivisions(406);

  for(int bn=0; bn<noptbins; bn++){

  double diff = (hist_pt[ij][jk]->GetBinContent(bn+1) > 1.e-6) ? (hist_pt[ij][jk]->GetBinContent(bn+1) - 1) : 0;
  if(diff>0) {refold_pt_up[ij][jk][bn] = diff;}
	else { refold_pt_dn[ij][jk][bn] = -diff;}

  }
 }
}

const int refrad = 3;

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
	hist_rad[ij][jk] = (TH1D*)hist_pt[ij][jk]->Clone();
	hist_rad[ij][jk]->Divide(hist_pt[refrad][jk]);
	}
    }

ofstream fp_pt;
fp_pt.open("Refold_Pt_excor_84.log");

ofstream fp_rad;
fp_rad.open("Refold_Rad_excor_84.log");

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
  for(int bn=0; bn<noptbins; bn++){
    refold_rad_up[ij][jk][bn] =  (hist_rad[ij][jk]->GetBinContent(bn+1) > 1.e-6) ? fabs(hist_rad[ij][jk]->GetBinContent(bn+1) - 1) : 0 ;//sqrt(pow(refold_pt_up[ij][jk][bn],2.)+pow(refold_pt_up[ref][jk][bn],2.));
    refold_rad_dn[ij][jk][bn] =  (hist_rad[ij][jk]->GetBinContent(bn+1) > 1.e-6) ? fabs(hist_rad[ij][jk]->GetBinContent(bn+1) - 1) : 0 ;// sqrt(pow(refold_pt_dn[ij][jk][bn],2.)+pow(refold_pt_dn[ref][jk][bn],2.));

    fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<refold_pt_up[ij][jk][bn]<<'\t'<<refold_pt_dn[ij][jk][bn]<<endl;
    fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<refold_rad_up[ij][jk][bn]<<'\t'<<refold_rad_dn[ij][jk][bn]<<endl;
  }
 }
}

fp_pt.close();
fp_rad.close();

TCanvas *c2[nalgo][Etabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

   hist_pt[ij][jk]->SetMinimum(0.5);
   hist_pt[ij][jk]->SetMaximum(1.5);

   sprintf(name,"Canv_pt_%s_EtaBin%i",JetRad[ij],jk+1);
   c2[ij][jk] = tdrCanvas(name,hist_pt[ij][jk],7,0);

   c2[ij][jk]->cd();

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

   latex.DrawLatex(0.5,0.75,text);
   latex.DrawLatex(0.5,0.7,text1);

   tdrDraw(hist_pt[ij][jk],kFullCircle,kBlue,kSolid,kBlue,1001,2);
   
   sprintf(name,"Refold_Plots/Pt_Plots/%s.eps",c2[ij][jk]->GetName());
   c2[ij][jk]->SaveAs(name);
  }
}


TCanvas *c3[nalgo][Etabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

   hist_rad[ij][jk]->SetMinimum(0.5);
   hist_rad[ij][jk]->SetMaximum(1.5);

   sprintf(name,"Canv_rad_%s_EtaBin%i",JetRad[ij],jk+1);
   c3[ij][jk] = tdrCanvas(name,hist_rad[ij][jk],7,0);

   c3[ij][jk]->cd();

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

   latex.DrawLatex(0.5,0.75,text);
   latex.DrawLatex(0.5,0.7,text1);

   tdrDraw(hist_rad[ij][jk],kFullCircle,kBlue,kSolid,kBlue,1001,2);

   sprintf(name,"Refold_Plots/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
   c3[ij][jk]->SaveAs(name);
  }
}


}

int main()
{
Sys_Refold();
}
