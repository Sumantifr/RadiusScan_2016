//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"


void Compare_FinalPlot()
{
cout<<"hi"<<endl;

const int ref_rad = 7;

const int nfiles = 2;
//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_JECor.root"/*AJEC/hist_RecoJetchs_PU_Data_JetHT2016EF_CMSSW8X21.root"*/,/*"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/Summer2016_8X21/hist_Herwigpp_Summer16_Run2.root",*/"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Summer_Files/Pythia_Summer16_CMSSW8X21_Run2_v2.root"/*"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/Summer2016_8X21/Madgraph2016Summer_Run2.root"*/};

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/2016Files/hist_RecoJetchs_PU_Data_JetHT2016BCDEFGH_new.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root"};

double data_lumi = 32.882;

const char *model_name[nfiles] = {"Data 2016"/*,"Pythia_Flat"*/,/*"Herwig",*/"Pythia8"/*,"Madgraph"*/};
const int col[nfiles] = {1,/*12,4,*/6/*,2*/};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int algo_col[nalgo] = {2,3,4,6,7,11,kCyan+2,kCyan-10, kBlue-7, kMagenta-9, kRed-5, kYellow-6};//{2,3,4,5,6,7,9,12,28,37,44,49};
const int algo_sty[nalgo] = {2,3,4,5,8,21,22,23,25,26,27,28};

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

double delta_pt[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

double delta_radius[nfiles-1][nalgo][netarange];

double max_range = 3000.;
double min_range = 74.;

TLine *line = new TLine(min_range,1,max_range,1.);
line->SetLineColor(7);

TLine *liney = new TLine(-5.,1.,5.,1.);
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
  for(int jk=0; jk<netarange; jk++){
  
   if((fg<1)){ sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;/*sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[ij],jk+1);*/}
   if((fg>0)) {sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
     hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
     hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleOffset(0.65);    

    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();    

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb^{-1}GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);  
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();
    
  }//jk


 }//ij
}//fg


for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt_org[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt_org[fg][ref_rad][jk]) ;
   

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.04);
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleOffset(0.65);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   sprintf(name,"Ratio of d^{2}#sigma / dp_{T}dy w.r.t. %s Jets",JetRad[ref_rad]);
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle(name);
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->SetMinimum(0);
   hist_radius[fg][ij][jk]->SetMaximum(2.0);

  }
 }
}

TCanvas *c2[netarange];

TLegend *leg_pt[netarange];

 for(int jk=0; jk<netarange; jk++){


sprintf(name,"Di_Pt_Compare_Canv_EtaBin%i",jk+1);
c2[jk] = tdrDiCanvas(name,hist_pt[0][ref_rad][jk],hist_pt[1][ref_rad][jk],4,0);

leg_pt[jk] = tdrLeg(0.6,0.7,0.95,0.95);

c2[jk]->cd(1);

 gPad->SetLogx(1);
 gPad->SetLogy(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.04);

  //TString text;
  //text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1,text1);

for(int ij=0; ij<nalgo; ij++){

  hist_pt[0][ij][jk]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

      if(fg!=0){
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC/Data");
	}

         if(fg==0){
             tdrDraw(hist_pt[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,col[fg] ,1001,2);
        }
        else{
                tdrDraw(hist_pt[fg][ij][jk],1,0,1,algo_col[ij] ,1001,0);
                hist_pt[fg][ij][jk]->SetLineWidth(2);
        }

if(fg!=0){      leg_pt[jk]->AddEntry(hist_pt[fg][ij][jk],jetname[ij],"l"); }
	leg_pt[jk]->SetTextSize(0.02);
    }//fg
  }//ij

 c2[jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);


for(int fg=0; fg<(nfiles-1); fg++){
 for(int ij=0; ij<nalgo; ij++){

  hist_pt_rat[fg][ij][jk]->SetLineColor(algo_col[ij]);
  hist_pt_rat[fg][ij][jk]->SetMinimum(0.);
  hist_pt_rat[fg][ij][jk]->SetMaximum(3.);

  hist_pt_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

if(fg==0&&ij==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
  }
 }

line->Draw();

sprintf(name,"Final_Pt_Plots/Run2016G/%s.eps",c2[jk]->GetName());
c2[jk]->SaveAs(name);

  }//jk


TCanvas *c3[netarange];

TLegend *leg_radius[netarange];

 for(int jk=0; jk<netarange; jk++){

  sprintf(name,"Di_Ratio_Compare_Canv_EtaBin%i",jk+1);
  c3[jk] = tdrCanvas(name,hist_radius[0][ref_rad][jk],6,0);

  leg_radius[jk] = tdrLeg(0.6,0.68,0.95,0.91);
 
  c3[jk]->cd(1);
  
  gPad->SetLogx(1);
  gPad->SetLogy(0);

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

  for(int ij=0; ij<nalgo; ij++){
   for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC/Data");

      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(2.);

        }
 

   if(fg==0){
   	     tdrDraw(hist_radius[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,col[fg] ,1001,2);
	}
	else{
		tdrDraw(hist_radius[fg][ij][jk],1,0,1,algo_col[ij] ,1001,0);
		hist_radius[fg][ij][jk]->SetLineWidth(2);
	}
if(fg==0){	hist_radius[fg][ij][jk]->SetMarkerSize(1);  }
if(fg!=0)  {   leg_radius[jk]->AddEntry(hist_radius[fg][ij][jk],jetname[ij],"l"); }
      leg_radius[jk]->SetTextSize(0.02);
    }//fg
 }//ij

  sprintf(name,"Final_Ratio_Plots/Run2016G/%s.eps",c3[jk]->GetName());
  c3[jk]->SaveAs(name);

  }//jk

}

int main()
{
Compare_FinalPlot();
}
