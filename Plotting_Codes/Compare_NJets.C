#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_NJets()
{

const int nalgo = 12;
const char *jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"} ;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const int netabins = 10;
const char* ybinname[netabins] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int nfiles = 4;

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_nocor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root"};
/*
const char *filenames[nfiles] = {,"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root"}
*/
const char *model_name[nfiles] = {"2016 Data","Herwig++","Pythia8","Madgraph"};
const int col[nfiles] = {1,4,6,2};

double data_lumi = 33.418;

char name[1000];

TFile *filein;

TH1D* hist_njets[nfiles][nalgo][netabins];
//TH1D* hist_njets_rat[nfiles-1][nHLTmx+1];

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netabins; jk++){
// sprintf(name, "NJets_ak%i",ij+1); 
  sprintf(name, "NJets_%s_EtaBin%i",JetRad[ij],jk+1);
  cout<<name<<endl;
  hist_njets[fg][ij][jk] = (TH1D*)filein->Get(name);
//  cout<<name<<endl;

 if(fg==0) { hist_njets[fg][ij][jk]->Scale(1./data_lumi) ;  } 

//  hist_njets[fg][ij]->SetBinContent(1,0);

  hist_njets[fg][ij][jk]->GetXaxis()->SetTitle("# of Jets") ;
  hist_njets[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
  hist_njets[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
  hist_njets[fg][ij][jk]->GetXaxis()->CenterTitle();
//  hist_njets[fg][ij]->GetXaxis()->SetRangeUser(0.5,20.);

  hist_njets[fg][ij][jk]->GetYaxis()->SetTitle("# of events ") ;
  hist_njets[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
  hist_njets[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
  hist_njets[fg][ij][jk]->GetYaxis()->CenterTitle();
 
  }//jk
 }//ij
}//fg

TCanvas *c1[nalgo][netabins];
TLegend *leg[nalgo][netabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netabins; jk++){

sprintf(name,"canv_%s_EtaBin%i",JetRad[ij],jk+1);
c1[ij][jk] = tdrCanvas(name,hist_njets[2][ij][jk],6,0);

leg[ij][jk] = tdrLeg(0.6,0.6,0.95,0.9);

c1[ij][jk]->cd();

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.045);

  TString text;
  text+= jetname[ij];

  TString text1;
  text1+= ybinname[jk];

  latex.DrawLatex(0.35,0.3,text);
  latex.DrawLatex(0.35,0.25,text1);

gPad->SetLogy(1);

for(int fg=0; fg<nfiles; fg++){

tdrDraw(hist_njets[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,0,col[fg]);
leg[ij][jk]->AddEntry(hist_njets[fg][ij][jk],model_name[fg],"l");
}

leg[ij][jk]->Draw();
/*
c1[ij]->cd(2);

for(int fg=0; fg<(nfiles-1); fg++){
hist_njets_rat[fg][ij]->GetYaxis()->SetTitle("MC/Data");
hist_njets_rat[fg][ij]->SetLineColor(col[fg+1]);
if(fg==0) { hist_njets_rat[fg][ij]->Draw("e"); }
else { hist_njets_rat[fg][ij]->Draw("sames"); }
  }
*/
sprintf(name,"NJet_Plots/%s.eps",c1[ij][jk]->GetName());
c1[ij][jk]->SaveAs(name);

  }//jk
 }//ij

}

