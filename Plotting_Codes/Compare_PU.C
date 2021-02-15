#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"

//#define RunEF
#define RunG
void Compare_PU()
{

gStyle->SetTitleFont(42,"XYZ");

const int nfiles = 4;

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/MINIAOD/PileUp_Reweightning/MyDataPileupHistogram_13TeV.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_nocorN.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Histograms_P8_Summer_noPU.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50_excorN_nopu.root"};
//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/MINIAOD/PileUp_Reweightning/MyDataPileupHistogram_13TeV.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso_nocorN.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_Pythia_ntuple_OneReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50_excorN.root"};

double data_lumi = 1.;

#ifdef RunG
data_lumi = 33.418;
#elif defined (RunEF)
data_lumi = 7.2;
#endif

const char *model_name[nfiles] = {"Data 2016","Herwig++","P8(CUETP8M1)","Madgraph"};
const int col[nfiles] ={1,4,6,2};

const int nHLTmx = 10;

char name[1000];

TFile *filein;

TH1D* hist_pv[nfiles];
TH1D* hist_pv_rat[nfiles-1];

TH1D* pu_proxy;

float leg_x1 = 0.2;
float leg_y1 = 0.4;
float leg_x2 = 0.55;
float leg_y2 = 0.7;

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
//filein->cd();

if(fg==0) { sprintf(name,"pileup");}
else { sprintf(name,"pu_vertices");} 

hist_pv[fg] = (TH1D*)filein->Get(name);
if(fg==0) { pu_proxy = (TH1D*)hist_pv[fg]->Clone(); }

hist_pv[fg]->GetXaxis()->SetTitle("# of PU Vertices");
hist_pv[fg]->GetXaxis()->CenterTitle();
hist_pv[fg]->GetXaxis()->SetTitleSize(0.06);
hist_pv[fg]->GetXaxis()->SetLabelSize(0.05);

hist_pv[fg]->GetYaxis()->SetTitle("A.U.");
hist_pv[fg]->GetYaxis()->SetTitleOffset(2.5);
hist_pv[fg]->GetYaxis()->SetTitleSize(0.06);
hist_pv[fg]->GetYaxis()->SetLabelSize(0.05);
hist_pv[fg]->GetYaxis()->CenterTitle();

cout<<name<<" mean "<<hist_pv[fg]->GetMean()<<endl;

}//fg

hist_pv[0] = (TH1D*)hist_pv[1]->Clone();
for(int bn=0; bn<hist_pv[0]->GetNbinsX(); bn++){
hist_pv[0]->SetBinContent(bn+1,pu_proxy->GetBinContent(bn+1));
hist_pv[0]->SetBinError(bn+1,pu_proxy->GetBinError(bn+1));
}

TCanvas *c2;
TLegend *leg_pv;

sprintf(name,"PU_Plot");
c2 = tdrDiCanvas(name,hist_pv[0],hist_pv[1],7,0);

leg_pv = tdrLeg(leg_x1,leg_y1,leg_x2,leg_y2);
leg_pv->SetTextSize(0.045);
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
leg_pv->AddEntry(hist_pv[fg],model_name[fg],"lp");
}

//leg_pv->Draw();

c2->cd(2);

TLine *line = new TLine(hist_pv[0]->GetBinLowEdge(1),1.,hist_pv[0]->GetBinLowEdge(hist_pv[0]->GetNbinsX()),1.);

gPad->SetLogx(0);
gPad->SetLogy(0);

for(int fg=0; fg<(nfiles-1); fg++){
  hist_pv_rat[fg]->SetLineColor(col[fg+1]);
  hist_pv_rat[fg]->GetYaxis()->SetTitle("MC/Data");
  hist_pv_rat[fg]->GetYaxis()->SetTitleOffset(0.7);
  hist_pv_rat[fg]->GetYaxis()->SetTitleSize(0.11);
  hist_pv_rat[fg]->SetMinimum(0.);
  hist_pv_rat[fg]->SetMaximum(2.);

 for(int bn=0; bn<(hist_pv_rat[fg]->GetNbinsX()); bn++){
  hist_pv_rat[fg]->SetBinError(bn+1,0);
 }

  if(fg==0) {  hist_pv_rat[fg]->Draw("e"); }
 else { hist_pv_rat[fg]->Draw("sames"); }
 }

line->Draw();

sprintf(name,"PUVert_Plots/%s_nowt.eps",c2->GetName());
c2->SaveAs(name);

}

int main()
{
Compare_PU();
}
