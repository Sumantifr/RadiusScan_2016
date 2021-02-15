//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_NGenJet()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 4;

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Summer_Files/Pythia_Summer16_CMSSW8X21_Run2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/Summer2016_8X21/Madgraph2016Summer_Run2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/Summer2016_8X21/Herwigpp_Summer2016_8X21.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_Pythia_Userhook2_NNPDF30.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/hist_Powheg_Herwig_NNPDF30.root"/*,"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_PythiaNNPDF30_Up.root"*/};

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/HerwigEE5C_Files_sel.root"};//hist_Powheg_Herwig_NNPDF30.root"};

const int ref = 4;

const char *model_name[nfiles] = {"Pythia","Madgraph","Herwigpp",/*"Powheg_Pythia",*/"Powheg_Herwig"};//,"PHP8_mpiUP"};
const int col[nfiles] = {6,2,4,/*3,*/9};//12};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[1000];

TFile *filein;

TH1D* hist_njet[nfiles][nalgo][netarange];
TH1D* hist_njet_rat[nfiles-1][nalgo][netarange];

TLine *line = new TLine(0,1,20.,1.);
line->SetLineColor(7);


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
  
    sprintf(name,"NGenJets_%s_EtaBin%i",JetRad[ij],jk+1); 
    hist_njet[fg][ij][jk] = (TH1D*)filein->Get(name);

    cout<<name<<endl;

    hist_njet[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_njet[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
//    hist_njet[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05); 
    hist_njet[fg][ij][jk]->GetXaxis()->CenterTitle();    
        

    hist_njet[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy (fb GeV^{-1})");
    hist_njet[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);  
//    hist_njet[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
    hist_njet[fg][ij][jk]->GetYaxis()->CenterTitle();
    
  }//jk
 }//ij
}//fg


TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

sprintf(name,"NJet_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
c2[ij][jk] = tdrDiCanvas(name,hist_njet[0][ij][jk],hist_njet[1][ij][jk],6,0);

leg_pt[ij][jk] = tdrLeg(0.6,0.7,0.95,0.95);

c2[ij][jk]->cd(1);

 gPad->SetLogx(0);
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
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);


 for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      if(fg>2){
//      hist_njet[fg][ij][jk]->Scale(hist_njet[0][ij][jk]->Integral()*1./hist_pt[fg][ij][jk]->Integral());
	hist_njet[fg][ij][jk]->Scale(1./48191.824);
	}

      hist_njet[fg][ij][jk]->Scale(hist_njet[0][ij][jk]->Integral()*1./hist_njet[fg][ij][jk]->Integral());

      hist_njet_rat[fg-1][ij][jk] = (TH1D*)hist_njet[fg][ij][jk]->Clone();
      hist_njet_rat[fg-1][ij][jk]->Divide(hist_njet[0][ij][jk]);
      hist_njet_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC/CUETP8M1");
	}
      tdrDraw(hist_njet[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_njet[fg][ij][jk],model_name[fg],"l");
    }
  //leg_pt[ij][jk]->Draw();

 c2[ij][jk]->cd(2);

 gPad->SetLogx(0);
 gPad->SetLogy(0);

for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_njet_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_njet_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_njet_rat[fg][ij][jk]->SetMinimum(0.);
  hist_njet_rat[fg][ij][jk]->SetMaximum(20.);
if(fg==0) {  hist_njet_rat[fg][ij][jk]->Draw("e"); }
 else { hist_njet_rat[fg][ij][jk]->Draw("sames"); }
  line->Draw();
 }

sprintf(name,"NGenJet_Plots/%s.eps",c2[ij][jk]->GetName());
c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij

}

int main()
{
Compare_NGenJet();
}
