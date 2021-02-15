//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_ydist()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 4;
/*
const char* filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/AJEC/hist_RecoJetchs_PU_Data_JetHT2016EF_CMSSW8X21.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Summer_Files/Pythia_Summer16_CMSSW8X21_Run2_v2.root"};
//const char* filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_CMSSW8X21_Prescalecor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_RawTrig.root"};
*/
/*
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/2016Files/hist_RecoJetchs_PU_Data_JetHT2016BCDEFGH_new.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root"/};
*/

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_nocor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root"};

double data_lumi = 33.4;

const int ref = 4;

const char *model_name[nfiles] = {"Data","Herwig++(CUETHS1)","P8(CUETP8M1)","Madgraph"};
const int col[nfiles] = {1,4,6,2};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;


char name[1000];

TFile *filein;

TH1D* hist_y[nfiles][nalgo];
TH1D* hist_y_rat[nfiles-1][nalgo];

TLine *line = new TLine(74,1,6000.,1.);
line->SetLineColor(7);

TLine *liney = new TLine(-4.7,1.,4.7,1.);
liney->SetLineColor(7);

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;


for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){

   if(fg<1) { sprintf(name,"Jety_%s",JetRad[ij]); }
   if(fg>0) {sprintf(name,"Jety_%s",JetRad[ij]);}

    hist_y[fg][ij] = (TH1D*)filein->Get(name);

    for(int bn=0; bn<(hist_y[fg][ij]->GetNbinsX()); bn++){
    hist_y[fg][ij]->SetBinContent(bn+1,hist_y[fg][ij]->GetBinContent(bn+1)*1./hist_y[fg][ij]->GetBinWidth(bn+1));
    }

    hist_y[fg][ij]->GetXaxis()->SetTitle("Jet Rapidity") ;
    hist_y[fg][ij]->GetXaxis()->SetTitleSize(0.05);
    hist_y[fg][ij]->GetXaxis()->SetLabelSize(0.05); 
    hist_y[fg][ij]->GetXaxis()->CenterTitle(); 
    hist_y[fg][ij]->GetXaxis()->SetRangeUser(-4.7,4.7);

    hist_y[fg][ij]->GetYaxis()->SetTitle("d#sigma/dy (fb)");
    hist_y[fg][ij]->GetYaxis()->SetTitleSize(0.05);
    hist_y[fg][ij]->GetYaxis()->SetLabelSize(0.05);
    hist_y[fg][ij]->GetYaxis()->CenterTitle();

 }//ij
}//fg



TCanvas *c1[nalgo];
TLegend *leg_y[nalgo];

for(int ij=0; ij<nalgo; ij++){

sprintf(name,"Rapidity_Compare_%s",JetRad[ij]);
c1[ij] = tdrDiCanvas(name,hist_y[0][ij],hist_y[1][ij],6,0);

leg_y[ij] = tdrLeg(0.4,0.5,0.75,0.75);
leg_y[ij]->SetTextSize(0.025);

c1[ij]->cd(1);

gPad->SetLogy(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.05);

  TString text;
  text+= jetname[ij];

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.2,leg_y1-0.05,text);

  hist_y[0][ij]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

//     hist_y[fg][ij]->Scale(1./hist_y[fg][ij]->Integral());

      if(fg!=0){
//     if(fg==1){
//      hist_y[fg][ij]->Scale(1./hist_y[fg][ij]->Integral());
//       }
      hist_y_rat[fg-1][ij] = (TH1D*)hist_y[fg][ij]->Clone();
      hist_y_rat[fg-1][ij]->Divide(hist_y[0][ij]);
      hist_y_rat[fg-1][ij]->GetYaxis()->SetTitle("MC/Data");
       }
      tdrDraw(hist_y[fg][ij],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_y[ij]->AddEntry(hist_y[fg][ij],model_name[fg],"l");
    }
  
 c1[ij]->cd(2);

 for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_y_rat[fg][ij]->SetLineColor(col[fg+1]);
  hist_y_rat[fg][ij]->SetMinimum(0.);
  hist_y_rat[fg][ij]->SetMaximum(2.);
if(fg==0) {  hist_y_rat[fg][ij]->Draw("e"); }
 else { hist_y_rat[fg][ij]->Draw("sames"); }
  liney->Draw();
 }

sprintf(name,"Rapidity_Plots/%s.eps",c1[ij]->GetName());
c1[ij]->SaveAs(name);

 }//ij

}

int main()
{
Compare_ydist();
}
