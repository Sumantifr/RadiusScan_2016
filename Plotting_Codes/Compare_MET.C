//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_MET()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 3;

//const char* filenames[nfiles] = {/*"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_CMSSW8X21_Prescalecor.root"*/"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Summer_Files/Pythia_Summer16_CMSSW8X21_JER0.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/Summer2016_8X21/Madgraph2016Summer_8X21_JER0.root"};

const char* filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/hist_Legacy_2016_withMETcut.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root"};

/*
const char* filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso_excor.root"};
*/
const int ref = 3;

const char *model_name[nfiles] = {"Data 2016","P8(CUETP8M1)","Madgraph"};//,"Herwig++"};
//const char *model_name[nfiles] = {"Before P_{T} Cut","After P_{T} cut"};
const int col[nfiles] = {1,6,2};

int nvar = 2;

char name[1000];

TFile *filein;

TH1D* hist_MET[nfiles][nvar];
TH1D* hist_MET_rat[nfiles-1][nvar];

float leg_x1 = 0.55;
float leg_y1 = 0.65;
float leg_x2 = 0.85;
float leg_y2 = 0.85;

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nvar; ij++){

   if(ij==0){
     if(fg==0){
     sprintf(name,"MET_Value");    
     }else { sprintf(name,"MET_Value"); }

    }else{
    if(fg==0){
     sprintf(name,"METbyEt");
     }else { sprintf(name,"METbyEt"); }
    }

    hist_MET[fg][ij] = (TH1D*)filein->Get(name);
/*
    for(int bn=0; bn<(hist_MET[fg][ij]->GetNbinsX()); bn++){
    hist_MET[fg][ij]->SetBinContent(bn+1,hist_MET[fg][ij]->GetBinContent(bn+1)*1./hist_MET[fg][ij]->GetBinWidth(bn+1));
    }
*/
    if(ij==0){
    hist_MET[fg][ij]->GetXaxis()->SetTitle("MET (in GeV)") ;
    }else{
     hist_MET[fg][ij]->GetXaxis()->SetTitle("MET Fraction");
    }    
    hist_MET[fg][ij]->GetXaxis()->SetTitleSize(0.05);
    hist_MET[fg][ij]->GetXaxis()->SetLabelSize(0.03); 
    hist_MET[fg][ij]->GetXaxis()->CenterTitle(); 
    hist_MET[fg][ij]->GetXaxis()->SetRangeUser(5,200.);

    hist_MET[fg][ij]->GetYaxis()->SetTitle("A.U.");
    hist_MET[fg][ij]->GetYaxis()->SetTitleSize(0.05);
    hist_MET[fg][ij]->GetYaxis()->SetLabelSize(0.035);
    hist_MET[fg][ij]->GetYaxis()->CenterTitle();

    hist_MET[fg][ij]->Sumw2();

    if(hist_MET[fg][ij]->Integral()>1.e-6){
        if(fg==0){hist_MET[fg][ij]->Scale(1./33.6);}
	hist_MET[fg][ij]->Scale(1./hist_MET[fg][ij]->Integral());
    }
 }//ij
}//fg



TCanvas *c1[nvar];
TLegend *leg_y[nvar];

TLine *line = new TLine(0.3,0.,0.3,hist_MET[1][1]->GetMaximum());
line->SetLineColor(3);


for(int ij=0; ij<nvar; ij++){

sprintf(name,"MET_Compare%i",ij+1);
//c1[ij] = tdrDiCanvas(name,hist_MET[0][ij],hist_MET[1][ij],6,0);
c1[ij] = tdrCanvas(name,hist_MET[0][ij],6,0);

leg_y[ij] = tdrLeg(0.65,0.65,0.85,0.85);
leg_y[ij]->SetTextSize(0.035);

c1[ij]->cd(1);

gPad->SetLogy(1);
gPad->SetLogx(0);

if(ij==0) { gPad->SetLogx(0); }
else { gPad->SetLogx(0); }

 for(int fg=0; fg<nfiles; fg++){

//  hist_MET[fg][ij]->Scale(1./hist_MET[fg][ij]->Integral());

      if(fg!=0){
//     if(fg==1){
//       hist_MET[fg][ij]->Scale(hist_MET[0][ij]->Integral()*1./hist_MET[fg][ij]->Integral());
//       }
      hist_MET_rat[fg-1][ij] = (TH1D*)hist_MET[fg][ij]->Clone();
      hist_MET_rat[fg-1][ij]->Divide(hist_MET[0][ij]);
      hist_MET_rat[fg-1][ij]->GetYaxis()->SetTitle("MC/Data");
       }
      tdrDraw(hist_MET[fg][ij],kFullCircle,col[fg],kSolid,col[fg] ,0,2);
      leg_y[ij]->AddEntry(hist_MET[fg][ij],model_name[fg],"l");
    }

 if(ij==1) { line->Draw() ;}
  /*
 c1[ij]->cd(2);

 if(ij==0) { gPad->SetLogx(0); }
else { gPad->SetLogx(0); }

 for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_MET_rat[fg][ij]->SetLineColor(col[fg+1]);
  hist_MET_rat[fg][ij]->SetMinimum(0.);
  hist_MET_rat[fg][ij]->SetMaximum(2.);
if(fg==0) {  hist_MET_rat[fg][ij]->Draw("e"); }
 else { hist_MET_rat[fg][ij]->Draw("sames"); }
 }
*/
sprintf(name,"MET_Plots/Legacy/%s.eps",c1[ij]->GetName());
c1[ij]->SaveAs(name);

 }//ij

}

int main()
{
Compare_MET();
}
