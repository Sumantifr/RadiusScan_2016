#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TPaletteAxis.h"

//#define RunEF
#define RunG
void Compare_PV()
{

gStyle->SetTitleFont(42,"XYZ");
gStyle->SetTitleSize(0.06,"XYZ");

const int nfiles = 4;

int cor_tag = 2;

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50_excor.root"};
/*
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/MINIAOD/PileUp_Reweightning/MyDataPileupHistogram_13TeV.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso_nocorN.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_Pythia_ntuple_OneReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50_excorN.root"};
*/
double data_lumi = 1.;

#ifdef RunG
data_lumi = 33.418;
#elif defined (RunEF)
data_lumi = 7.2;
#endif

const char *model_name[nfiles] = {"Data 2016","Herwig++","P8(CUETP8M1)","Madgraph"};
const int col[nfiles] = {1,4,6,2};

const int nHLTmx = 10;

char name[1000];

TFile *filein;

TH1D* hist_pv[nfiles];
TH1D* hist_pv_rat[nfiles-1];

TH2D* cor_pvpu;

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
//filein->cd();

if(fg==0) { sprintf(name,"nprimsel_rewt_trigset");}
else { sprintf(name,"nprimsel_0_trigset");} 

//if(fg==0) { sprintf(name,"pileup");}
//else { sprintf(name,"pu_vertices");} 

hist_pv[fg] = (TH1D*)filein->Get(name);

hist_pv[fg]->GetXaxis()->SetTitle("# of Primary Vertices");
hist_pv[fg]->GetXaxis()->CenterTitle();

hist_pv[fg]->GetYaxis()->SetTitle("A.U.");
hist_pv[fg]->GetYaxis()->SetTitleOffset(2.5);
hist_pv[fg]->GetYaxis()->CenterTitle();

cout<<name<<" mean "<<hist_pv[fg]->GetMean()<<endl;

if(fg==cor_tag){ sprintf(name,"pileup_vs_nprimsel_reweighted"); 
cor_pvpu = (TH2D*)filein->Get(name);
cor_pvpu->GetXaxis()->SetTitle("# of Pile Up Vertices");
cor_pvpu->GetXaxis()->CenterTitle();
cor_pvpu->GetXaxis()->SetTitleSize(0.05);
cor_pvpu->GetXaxis()->SetLabelSize(0.05);

cor_pvpu->GetYaxis()->SetTitle("# of Primary Vertices");
cor_pvpu->GetYaxis()->CenterTitle();
cor_pvpu->GetYaxis()->SetTitleSize(0.05);
cor_pvpu->GetYaxis()->SetLabelSize(0.05);

 }
}//fg

TCanvas *c2;
TLegend *leg_pv;

sprintf(name,"PV_Plot_nowt");
c2 = tdrDiCanvas(name,hist_pv[0],hist_pv[1],6,0);

leg_pv = tdrLeg(0.65,0.7,0.85,0.95);
leg_pv->SetTextSize(0.035);
leg_pv->SetTextFont(42);

c2->cd(1);

gPad->SetLogx(0);
gPad->SetLogy(1);

hist_pv[0]->Scale(1./data_lumi);

for(int fg=0; fg<nfiles; fg++){
hist_pv[fg]->Scale(1./hist_pv[fg]->Integral());
if(fg!=0){
hist_pv_rat[fg-1] = (TH1D*)hist_pv[fg]->Clone();
hist_pv_rat[fg-1]->Divide(hist_pv[0]);
}

tdrDraw(hist_pv[fg],kFullCircle,col[fg],0,col[fg],0,0);
leg_pv->AddEntry(hist_pv[fg],model_name[fg],"l");
}

c2->cd(2);

TLine *line = new TLine(hist_pv[0]->GetBinLowEdge(1),1.,hist_pv[0]->GetBinLowEdge(hist_pv[0]->GetNbinsX()),1.);

gPad->SetLogx(0);
gPad->SetLogy(0);

for(int fg=0; fg<(nfiles-1); fg++){
  hist_pv_rat[fg]->SetLineColor(col[fg+1]);
  hist_pv_rat[fg]->GetYaxis()->SetTitle("MC/Data");
  hist_pv_rat[fg]->SetMinimum(0.);
//  hist_pv_rat[fg]->SetMaximum(2.);

 for(int bn=0; bn<(hist_pv_rat[fg]->GetNbinsX()); bn++){
  hist_pv_rat[fg]->SetBinError(bn+1,0);
 }

  if(fg==0) {  hist_pv_rat[fg]->Draw("e"); }
 else { hist_pv_rat[fg]->Draw("sames"); }
 }

line->Draw();

sprintf(name,"PV_Plots/%s.eps",c2->GetName());
c2->SaveAs(name);



  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.065);

  TString text;
  text+= model_name[cor_tag];

//  gStyle->SetPalette(55);

  TCanvas *c3;
  sprintf(name,"Cor_PUPV_%s",model_name[cor_tag]);
  c3 = tdrCanvas(name,hist_pv[cor_tag],6,0);
  c3->SetRightMargin(0.075);
  c3->cd();
  gPad->SetLogz(1);
  cor_pvpu->Draw("COLZ0");
  latex.DrawLatex(0.5,0.75,text);

   c3->Update();
   TPaletteAxis *palette = (TPaletteAxis*)cor_pvpu->GetListOfFunctions()->FindObject("palette");
   palette->SetX1NDC(0.915);
   palette->SetX2NDC(0.94);
   palette->SetY1NDC(0.12);
   palette->SetY2NDC(0.92);
   c3->Modified();
   c3->Update();

  sprintf(name,"PV_Plots/%s.eps",c3->GetName());
  c3->SaveAs(name);
}

int main()
{
Compare_PV();
}
