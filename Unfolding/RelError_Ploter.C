#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void RelError_Ploter()
{
//const char *filenames[1] = {"Unfolded_2016_Data_NTuple_MC_P8_nocor_84.root"};
//const char *filenames[1] = {"Unfolded_2016_Data_NTuples_TUnfold.root"};
const char *filenames[1] = {"Unfolded_2016_Data_NTuple_MC_P8_Legacy_new_excor.root"};
char name[100];

const char *unf_tech[3] = {"D'Agostini","SVD","Bin by Bin"};

static const int nalgo = 12 ;
static const int netarange = 10 ;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;
int col[netarange] = {1,2,kGreen+2,4,6,kYellow+2,7,9,12,24};


TH1D *bayes_err[nalgo][netarange];
TH1D *svd_err[nalgo][netarange];
TH1D *BbB_err[nalgo][netarange];

sprintf(name,"%s",filenames[0]);
TFile *filein = new TFile(name,"read");

for(int ij=0; ij<nalgo; ij++){
for(int jk=0; jk<netarange; jk++){

sprintf(name,"Bayes_%s_EtaBin%i_error",JetRad[ij],jk+1);
bayes_err[ij][jk] = (TH1D*)filein->Get(name);

sprintf(name,"SVD_%s_EtaBin%i_error",JetRad[ij],jk+1);
svd_err[ij][jk] = (TH1D*)filein->Get(name);

sprintf(name,"BinbyBin_%s_EtaBin%i_error",JetRad[ij],jk+1);
BbB_err[ij][jk] = (TH1D*)filein->Get(name);

bayes_err[ij][jk]->GetXaxis()->SetTitle("Bin No.");
bayes_err[ij][jk]->GetXaxis()->SetTitleSize(0.05);
bayes_err[ij][jk]->GetXaxis()->SetLabelSize(0.05);
bayes_err[ij][jk]->GetXaxis()->CenterTitle();

bayes_err[ij][jk]->GetYaxis()->SetTitle("Rel Err in Unfolded Data / Rel Err in Data");
bayes_err[ij][jk]->GetYaxis()->SetTitleSize(0.05);
bayes_err[ij][jk]->GetYaxis()->SetLabelSize(0.05);
bayes_err[ij][jk]->GetYaxis()->CenterTitle();

bayes_err[ij][jk]->SetLineColor(col[jk]);
bayes_err[ij][jk]->SetMaximum(2.*bayes_err[ij][jk]->GetMaximum());
}
}

TLatex latex;
latex.SetNDC();
latex.SetTextAngle(0);
latex.SetTextColor(kBlack);

latex.SetTextFont(42);
latex.SetTextAlign(31);
latex.SetTextSize(0.06);

TCanvas *c2[nalgo];
TLegend *leg2[nalgo];

for(int ij=0; ij<nalgo; ij++){
sprintf(name,"Canv_RelErr_%s",JetRad[ij]);
c2[ij] = tdrCanvas(name,bayes_err[ij][0],7,0);
leg2[ij] = tdrLeg(0.7,0.6,0.9,0.9);
leg2[ij]->SetTextFont(42);

TString text;
text+= jetname[ij];

latex.DrawLatex(0.4,0.8,text);
//latex.DrawLatex(0.4,0.35,text1);

for(int jk=0; jk<6; jk++){
  tdrDraw(bayes_err[ij][jk],kSolid,col[jk],kSolid,col[jk],2,0);
  leg2[ij]->AddEntry(bayes_err[ij][jk],ybinname[jk],"l");
 }
  leg2[ij]->Draw();
  sprintf(name,"Error_Plots/Legacy_Ex_Cor/%s.png",c2[ij]->GetName());
  c2[ij]->SaveAs(name);
}

/*
TCanvas *c1[nalgo][netarange];
TLegend *leg1[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   sprintf(name,"Canv_RelErr_%s_EtaBin%i",JetRad[ij],jk+1);
   c1[ij][jk] = tdrCanvas(name,bayes_err[ij][jk],6,0);
   leg1[ij][jk] = tdrLeg(0.55,0.7,0.9,0.95);
   
  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.4,0.4,text);
  latex.DrawLatex(0.4,0.35,text1);
  
  tdrDraw(bayes_err[ij][jk],kSolid,2,kSolid,2,0,0);
  leg1[ij][jk]->AddEntry(bayes_err[ij][jk],unf_tech[0],"l");
  leg1[ij][jk]->Draw();

  sprintf(name,"Error_Plots/%s.eps",c1[ij][jk]->GetName());
  c1[ij][jk]->SaveAs(name);
 }
}
*/

}
