//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_NeuParticle()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 2;
const char* filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_JECor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Summer_Files/Pythia_Summer16_CMSSW8X21_Run2_v2_NeuParticle.root"};
//const char* filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_CMSSW8X21_Prescalecor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_RawTrig.root"};

const int ref = 4;

const char *model_name[nfiles] = {"Data_2016G","Pythia_CUETP8M1"};
//const char *model_name[nfiles] = {"Before P_{T} Cut","After P_{T} cut"};
const int col[nfiles] = {1,2};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;


char name[1000];

TFile *filein;

TH1D* hist_neumul[nfiles][nalgo];
TH1D* hist_neumul_rat[nfiles-1][nalgo];

TLine *liney = new TLine(0.,1.,20.,1.);
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

   if(fg<1) { sprintf(name,"mcjets/Neutral_Hadron_Multiplicity_%s",JetRad[ij]); }
   if(fg>0) {sprintf(name,"Neutral_Hadron_Multiplicity_%s",JetRad[ij]);}

    hist_neumul[fg][ij] = (TH1D*)filein->Get(name);
    cout<<"file "<<fg+1<<" mean "<<hist_neumul[fg][ij]->GetMean()<<endl;
    for(int bn=0; bn<(hist_neumul[fg][ij]->GetNbinsX()); bn++){
    hist_neumul[fg][ij]->SetBinContent(bn+1,hist_neumul[fg][ij]->GetBinContent(bn+1)*1./hist_neumul[fg][ij]->GetBinWidth(bn+1));
    }

    hist_neumul[fg][ij]->GetXaxis()->SetTitle("No. of Neutral Particles") ;
    hist_neumul[fg][ij]->GetXaxis()->SetTitleSize(0.05);
    hist_neumul[fg][ij]->GetXaxis()->SetLabelSize(0.05); 
    hist_neumul[fg][ij]->GetXaxis()->CenterTitle(); 
    hist_neumul[fg][ij]->GetXaxis()->SetRangeUser(-0.01,20.);

    hist_neumul[fg][ij]->GetYaxis()->SetTitle("d#sigma/d(neu_mul) (fb^{-1})");
    hist_neumul[fg][ij]->GetYaxis()->SetTitleSize(0.05);
    hist_neumul[fg][ij]->GetYaxis()->SetLabelSize(0.05);
    hist_neumul[fg][ij]->GetYaxis()->CenterTitle();

 }//ij
}//fg



TCanvas *c1[nalgo];
TLegend *leg_y[nalgo];

for(int ij=0; ij<nalgo; ij++){

sprintf(name,"Rapidity_Compare_%s",JetRad[ij]);
c1[ij] = tdrDiCanvas(name,hist_neumul[0][ij],hist_neumul[1][ij],5,0);

leg_y[ij] = tdrLeg(0.3,0.3,0.75,0.55);

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

//  hist_neumul[0][ij]->Scale(1./7.6);

 for(int fg=0; fg<nfiles; fg++){

      if(fg>=0){
//     if(fg==1){
       hist_neumul[fg][ij]->Scale(1./hist_neumul[fg][ij]->Integral());
//       }
      hist_neumul_rat[fg-1][ij] = (TH1D*)hist_neumul[fg][ij]->Clone();
      hist_neumul_rat[fg-1][ij]->Divide(hist_neumul[0][ij]);
      hist_neumul_rat[fg-1][ij]->GetYaxis()->SetTitle("MC/Data");
       }
      tdrDraw(hist_neumul[fg][ij],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_y[ij]->AddEntry(hist_neumul[fg][ij],model_name[fg],"l");
    }
  
 c1[ij]->cd(2);

 for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_neumul_rat[fg][ij]->SetLineColor(col[fg+1]);
  hist_neumul_rat[fg][ij]->SetMinimum(0.);
  hist_neumul_rat[fg][ij]->SetMaximum(2.);
if(fg==0) {  hist_neumul_rat[fg][ij]->Draw("e"); }
 else { hist_neumul_rat[fg][ij]->Draw("sames"); }
  liney->Draw();
 }

sprintf(name,"Neutral_Particles/%s.eps",c1[ij]->GetName());
c1[ij]->SaveAs(name);

 }//ij

}

int main()
{
Compare_NeuParticle();
}
