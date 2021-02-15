//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_MCRecoGen()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 3;

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Summer_Files/Pythia_Summer16_CMSSW8X21_Run2_v2.root"/*Pythia_Summer16_CMSSW8X21_JER0.root"*//*Pythia_Summer16_CMSSW8X21.root"*/,"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/Summer2016_8X21/Madgraph2016Summer_Run2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/Summer2016_8X21/hist_Herwigpp_Summer16_Run2.root"};

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root"};

/*
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_newexcor2facx2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso_excor.root"};
*/
const int ref = 3;

const char *model_name[nfiles] = {"Pythia8","Madgraph","Herwig++"};
const int col[nfiles] = {6,2,4};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;


char name[1000];

TFile *filein;

TH1D* hist_pt_reco[nfiles][nalgo][netarange];
TH1D* hist_pt_gen[nfiles][nalgo][netarange];
TH1D* hist_pt_ratio[nfiles][nalgo][netarange];

TLine *line = new TLine(74,1,6000.,1.);
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
  
    sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;
    hist_pt_reco[fg][ij][jk] = (TH1D*)filein->Get(name);
    sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
    hist_pt_gen[fg][ij][jk] = (TH1D*)filein->Get(name);
 
  /*
   for(int bn=0; bn<(hist_pt_reco[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt_reco[fg][ij][jk]->SetBinContent(bn+1,hist_pt_reco[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt_reco[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt_reco[fg][ij][jk]->SetBinError(bn+1,hist_pt_reco[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt_reco[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }

    for(int bn=0; bn<(hist_pt_gen[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt_gen[fg][ij][jk]->SetBinContent(bn+1,hist_pt_gen[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt_gen[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt_gen[fg][ij][jk]->SetBinError(bn+1,hist_pt_gen[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt_gen[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }
    */
/*
   hist_pt_reco[fg][ij][jk]->Scale(1./hist_pt_reco[fg][ij][jk]->Integral());
   hist_pt_gen[fg][ij][jk]->Scale(1./hist_pt_gen[fg][ij][jk]->Integral());
*/
  hist_pt_ratio[fg][ij][jk] = (TH1D*)hist_pt_reco[fg][ij][jk]->Clone();
  hist_pt_ratio[fg][ij][jk]->Divide(hist_pt_gen[fg][ij][jk]) ;

  hist_pt_ratio[fg][ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
  hist_pt_ratio[fg][ij][jk]->GetXaxis()->CenterTitle();
  hist_pt_ratio[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
  hist_pt_ratio[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05); 
 
  hist_pt_ratio[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy RECO/ d^{2}#sigma / dp_{T}dy GEN");
  hist_pt_ratio[fg][ij][jk]->GetYaxis()->CenterTitle();
  hist_pt_ratio[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
  hist_pt_ratio[fg][ij][jk]->GetYaxis()->SetLabelSize(0.04);

  hist_pt_ratio[fg][ij][jk]->GetXaxis()->SetRangeUser(0,2000.);
  hist_pt_ratio[fg][ij][jk]->SetMinimum(0.6);
  hist_pt_ratio[fg][ij][jk]->SetMaximum(1.4);
  }//jk
 }//ij
}//fg

TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

sprintf(name,"RecoGen_Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
c2[ij][jk] = tdrCanvas(name,hist_pt_ratio[0][ij][jk],6,0);

leg_pt[ij][jk] = tdrLeg(0.55,0.7,0.95,0.9);
leg_pt[ij][jk]->SetTextSize(0.04);
leg_pt[ij][jk]->SetTextFont(42);

c2[ij][jk]->cd();

 gPad->SetLogx(1);
 gPad->SetLogy(0);

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

 // cout<<0.5*(leg_x1+leg_x2)<<endl;

  if(ij>=0){
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.15,leg_y1+0.1,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.15,leg_y1+0.025,text1);
  }else{
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.15,leg_y1+0.4,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.15,leg_y1+0.325,text1);
  }

 for(int fg=0; fg<nfiles; fg++){

      tdrDraw(hist_pt_ratio[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt_ratio[fg][ij][jk],model_name[fg],"l");
    }

 line->Draw();
 leg_pt[ij][jk]->Draw();

sprintf(name,"RECO_GEN_Ratio_Plots/No_Cor/%s.eps",c2[ij][jk]->GetName());
c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij

}

int main()
{
Compare_MCRecoGen();
}
