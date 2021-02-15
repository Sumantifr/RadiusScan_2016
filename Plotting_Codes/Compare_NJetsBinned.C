#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_NJetsBinned()
{

const int nfiles = 4;
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/NJets_Binned.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Summer_Files/NJets_Binned_Pythia_Summer16_Run2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/Summer2016_8X21/Binned_NJets_Madgraph2016Summer_8X21.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/NJets_Binned_PHP8.root"};

const int nalgo = 12;
const char *jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"} ;

const int Etabins = 10;
const char* ybinname[Etabins] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const char *model_name[nfiles] = {"Data_2016G"/*,"Pythia_Flat","Herwig"*/,"Pythia8",/*"Powheg+Pythia8","Pythia8_GEN","Herwig++_RECO",*/"Madgraph_RECO"/*,"Madgraph_GEN"*/,"Powheg+Pythia8"};
const int col[nfiles] = {1,/*12,4,*/5,/*3,6,4,*/2/*,7*/,3};

char name[1000];

TFile *filein;

TH1D* hist_njets[nfiles][nalgo][Etabins];
//TH1D* hist_njets_rat[nfiles-1][nHLTmx+1];

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
 sprintf(name, "NJets_ak%i_EtaBin%i",ij+1,jk+1); 
 hist_njets[fg][ij][jk] = (TH1D*)filein->Get(name);

 if(fg==0) { hist_njets[fg][ij][jk]->Scale(1./7.163) ;  } 

//  hist_njets[fg][ij][jk]->SetBinContent(1,0);

  hist_njets[fg][ij][jk]->GetXaxis()->SetTitle("# of Jets") ;
  hist_njets[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
  hist_njets[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
  hist_njets[fg][ij][jk]->GetXaxis()->CenterTitle();
//  hist_njets[fg][ij]->GetXaxis()->SetRangeUser(0.5,20.);

  hist_njets[fg][ij][jk]->GetYaxis()->SetTitle("# of events (normalised)") ;
  hist_njets[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
  hist_njets[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
  hist_njets[fg][ij][jk]->GetYaxis()->CenterTitle();

 if(fg==0) { cout<<"mean "<<hist_njets[fg][ij][jk]->GetMean()<<endl;}
/*
 if(fg!=0){

   hist_njets_rat[fg-1][ij] = (TH1D*)hist_PV[fg][ij]->Clone();
   hist_njets_rat[fg-1][ij]->Divide(hist_PV[0][ij]) ;

   hist_njets_rat[fg-1][ij]->GetXaxis()->SetTitle("# of Primary Vertices") ;
   hist_njets_rat[fg-1][ij]->GetXaxis()->SetTitleSize(0.05);
   hist_njets_rat[fg-1][ij]->GetXaxis()->SetLabelSize(0.05);
   hist_njets_rat[fg-1][ij]->GetXaxis()->CenterTitle();
    
   hist_njets_rat[fg-1][ij]->GetYaxis()->SetTitleSize(0.05);
   hist_njets_rat[fg-1][ij]->GetYaxis()->SetLabelSize(0.05);
   hist_njets_rat[fg-1][ij]->GetYaxis()->CenterTitle();

    hist_njets_rat[fg-1][ij]->SetMinimum(0.);
    hist_njets_rat[fg-1][ij]->SetMaximum(5.);
  }
*/
  }//jk
 }//ij
}//fg

TCanvas *c1[nalgo][Etabins];
TLegend *leg[nalgo][Etabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

 sprintf(name,"canv_ak%i_EtaBin%i",ij+1,jk+1);
 c1[ij][jk] = tdrCanvas(name,hist_njets[2][ij][jk],4,0);

 leg[ij][jk] = tdrLeg(0.6,0.6,0.95,0.9);

 c1[ij][jk]->cd();

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.06);

  TString text;
  text+= jetname[ij];

  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.75,0.25,text);
  latex.DrawLatex(0.75,0.2,text1);


gPad->SetLogy(1);

for(int fg=0; fg<nfiles; fg++){
if((hist_njets[fg][ij][jk]->Integral()>1.e-7)){hist_njets[fg][ij][jk]->Scale(1./hist_njets[fg][ij][jk]->Integral());}
//hist_njets[fg][ij]->Scale(1./hist_njets[fg][ij]->GetEntries());

tdrDraw(hist_njets[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg],0,col[fg]);
/*hist_njets[fg][ij]->SetLineColor(col[fg]);
if(fg==0){ hist_njets[fg][ij]->Draw("e"); }
else{hist_njets[fg][ij]->Draw("sames"); }
*/
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
sprintf(name,"NJet_Binned_Plots/%s.eps",c1[ij][jk]->GetName());
c1[ij][jk]->SaveAs(name);

  }//jk
 }//ij

}

