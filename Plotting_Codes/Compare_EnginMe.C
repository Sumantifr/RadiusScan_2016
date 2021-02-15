//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"

//#define RunEF
#define RunG

void Compare_EnginMe()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 2;

const char *filenames[nfiles] = {"CommonBin_ak4_Engin_JECv17_2016GH_AOD.root","CommonBin_ak4_Suman_JECv17_2016GH_MINIAOD_hist_v18.root"};

const int ref = 4;

const char *model_name[nfiles] = {"Engin","Suman"};
const int col[nfiles] = {1,2};

static const int netarange = 5 ;

const char* jetname[1] = {"ak4chs"} ;

double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5"};

const int noptbins = 50;

double ptbins[noptbins+1] = {/*64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832};

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][netarange];
TH1D* hist_pt_rat[nfiles-1][netarange];
/*
for(int fg=0; fg<(nfiles-1); fg++){
 for(int jk=0; jk<netarange; jk++){
   sprintf(name,"rat_file%i_eta%i",fg+1,jk+1);
   hist_pt_rat[fg][jk] = new TH1D(name,name,noptbins,ptbins);
   hist_pt_rat[fg][jk]->Sumw2();
  }
}
*/
TLine *line = new TLine(74,1,6000.,1.);
line->SetLineColor(7);

TLine *liney = new TLine(-5.,1.,5.,1.);
liney->SetLineColor(7);

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

float data_lumi = 16.375*1000;

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

  for(int jk=0; jk<netarange; jk++){
  
     sprintf(name,"JetpT_ak4_EtaBin%i",jk+1); 
     hist_pt[fg][jk] = (TH1D*)filein->Get(name);
  
  if(fg==1){
/*
   for(int bn=0; bn<(hist_pt[fg][jk]->GetNbinsX()); bn++){
     hist_pt[fg][jk]->SetBinContent(bn+1,hist_pt[fg][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][jk]->GetBinWidth(bn+1)));
     hist_pt[fg][jk]->SetBinError(bn+1,hist_pt[fg][jk]->GetBinError(bn+1)*1.0/sqrt(hist_pt[fg][jk]->GetBinWidth(bn+1)));
      }
*/
     hist_pt[fg][jk]->Scale(1./data_lumi);
    }

    hist_pt[fg][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][jk]->GetXaxis()->CenterTitle();    

    hist_pt[fg][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(pb^{-1}GeV^{-1})");
    hist_pt[fg][jk]->GetYaxis()->SetTitleSize(0.05);  
    hist_pt[fg][jk]->GetYaxis()->CenterTitle();
   
    hist_pt[fg][jk]->GetXaxis()->SetRangeUser(74,3000.);
 
  }//jk

}//fg


TCanvas *c2[netarange];

TLegend *leg_pt[netarange];

for(int jk=0; jk<netarange; jk++){

// if((ij!=ialgo)||(jk!=ieta)) continue;

sprintf(name,"Di_Pt_Compare_Canv_EtaBin%i",jk+1);
c2[jk] = tdrDiCanvas(name,hist_pt[0][jk],hist_pt[1][jk],5,0);

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
  latex.SetTextSize(0.05);
 
  TString text;
  text+=  jetname[0];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);

//  hist_pt[0][ij][jk]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

//	hist_pt[fg][jk]->Scale(1./hist_pt[fg][jk]->Integral());

      if(fg!=0){
      hist_pt_rat[fg-1][jk] = (TH1D*)hist_pt[fg][jk]->Clone();
//      hist_pt_rat[fg-1][jk]->Divide(hist_pt[0][jk]);
/*
      for(int bn=0; bn<(hist_pt[fg][jk]->GetNbinsX()+1); bn++){
	hist_pt_rat[fg-1][jk]->SetBinContent(bn+1,hist_pt[fg][jk]->GetBinContent(bn+1)*1./max(1.e-12,hist_pt[0][jk]->GetBinContent(bn+1+10)));
	//hist_pt_rat[fg-1][jk]->SetBinError(bn+1,0.);
       }
*/
       hist_pt_rat[fg-1][jk]->Divide(hist_pt[0][jk]);	
       hist_pt_rat[fg-1][jk]->GetXaxis()->SetRangeUser(74,3000.);
	
       hist_pt_rat[fg-1][jk]->GetYaxis()->SetTitle("Suman/Engin");
       hist_pt_rat[fg-1][jk]->GetYaxis()->SetTitleSize(0.075);
       hist_pt_rat[fg-1][jk]->GetYaxis()->CenterTitle();
       hist_pt_rat[fg-1][jk]->GetYaxis()->SetLabelSize(0.05);

       hist_pt_rat[fg-1][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
       hist_pt_rat[fg-1][jk]->GetXaxis()->SetTitleSize(0.075);
       hist_pt_rat[fg-1][jk]->GetXaxis()->CenterTitle();
       hist_pt_rat[fg-1][jk]->GetXaxis()->SetLabelSize(0.05);
	
	}
//      hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(0,2000.);
      tdrDraw(hist_pt[fg][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[jk]->AddEntry(hist_pt[fg][jk],model_name[fg],"l");
    }

 c2[jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);


for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_pt_rat[fg][jk]->SetLineColor(col[fg+1]);
  hist_pt_rat[fg][jk]->SetMinimum(0.8);
  hist_pt_rat[fg][jk]->SetMaximum(1.2);
//  hist_pt_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(0,2000.);
//if(fg==0) {  hist_pt_rat[fg][jk]->Draw("e"); }
// else { hist_pt_rat[fg][jk]->Draw("sames"); }
   hist_pt_rat[fg][jk]->Draw("e");
 }

line->Draw();

sprintf(name,"Engin_Me/JECv18/%s.eps",c2[jk]->GetName());
c2[jk]->SaveAs(name);

  }//jk
/*
for(int  bn=0; bn<noptbins; bn++){
cout<<"bin "<<bn+1<<"\t"<<hist_pt[0][0]->GetBinContent(bn+1+10)<<"\t"<<hist_pt[1][0]->GetBinContent(bn+1)<<" rat "<<hist_pt[1][0]->GetBinContent(bn+1)*1./max(1.e-12,hist_pt[0][0]->GetBinContent(bn+1+10))<<endl;
}
*/

}

int main()
{
Compare_EnginMe();
}
