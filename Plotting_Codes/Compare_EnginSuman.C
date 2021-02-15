//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"

//#define RunEF
#define RunG

void Compare_EnginSuman()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 2;

const char *filenames[5] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Engin/common2016_October2018_V17.root",
			    "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor.root",
		            "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor_EraBCD.root",
			    "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor_EraEF.root",
			    "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor_EraGH.root"
};

const int ref = 4;

const char *model_name[nfiles] = {"Engin","Suman"};
const int col[nfiles] = {1,2};

static const int netarange = 1;//5 ;

const char* jetname[1] = {"ak4chs"} ;

double ybin[netarange+1] = {0,0.5};//,1.0,1.5,2.0,2.5};
const char* ybinname[netarange] = {"|y|<0.5"};//,"0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5"};

const int noptbins = 50;

double ptbins[noptbins+1] = {/*64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832};

char name[1000];

TFile *filein;
const int neras = 4;
const char *Era[neras] = {"2016_Total","2016_BCD", "2016_EF", "2016_GH"};
int tags[neras] = {7,4,5,6};
TH1D* hist_pt[2][neras][netarange];
TH1D* hist_ptn[2][neras][netarange];
TH1D* hist_pt_rat[1][neras][netarange];
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

float data_lumiGH = 16.375*1000;
float data_lumiBCD = 10.069*1000;
float data_lumiEF = 7.195*1000;
float data_lumitot = 33.639*1000;

for(int fg=0; fg<5; fg++){
cout<<filenames[fg]<<endl;
sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

for(int jk=0; jk<netarange; jk++){
  
  if(fg==0){
	sprintf(name,"ak4/y_0.0-0.5/hptData_full2016_detector_%ibin",jk+1);
        hist_pt[fg][0][jk] = (TH1D*)filein->Get(name);
        sprintf(name,"ak4/y_0.0-0.5/hptData_BCD2016_detector_%ibin",jk+1);
        hist_pt[fg][1][jk] = (TH1D*)filein->Get(name);
	sprintf(name,"ak4/y_0.0-0.5/hptData_EF2016_detector_%ibin",jk+1);
        hist_pt[fg][2][jk] = (TH1D*)filein->Get(name);
	sprintf(name,"ak4/y_0.0-0.5/hptData_GH2016_detector_%ibin",jk+1);
        hist_pt[fg][3][jk] = (TH1D*)filein->Get(name);
	 }

  if(fg==1||fg==2||fg==3||fg==4){
     if(fg==1){
     sprintf(name,"JetpT_ak4_EtaBin%i",jk+1);
     hist_pt[1][0][jk] = (TH1D*)filein->Get(name);
     hist_pt[1][0][jk]->Scale(1./data_lumitot);
     }
     if(fg==2){
     sprintf(name,"JetpT_ak4_EtaBin%i",jk+1);
     hist_pt[1][1][jk] = (TH1D*)filein->Get(name);
     hist_pt[1][1][jk]->Scale(1./data_lumiBCD);
     }
     if(fg==3){
     sprintf(name,"JetpT_ak4_EtaBin%i",jk+1);
     hist_pt[1][2][jk] = (TH1D*)filein->Get(name);
     hist_pt[1][2][jk]->Scale(1./data_lumiEF);
     }
     if(fg==4){
     sprintf(name,"JetpT_ak4_EtaBin%i",jk+1);
     hist_pt[1][3][jk] = (TH1D*)filein->Get(name);
     hist_pt[1][3][jk]->Scale(1./data_lumiGH);
     cout<<"cc "<<hist_pt[1][3][jk]->GetBinContent(2)<<endl;
       }
     }
   }
 }

 for(int fg=0; fg<2; fg++){
  for(int jk=0; jk<netarange; jk++){
   for(int iera=0; iera<neras; iera++){
    sprintf(name,"File%i_Eta%i_Era%i",fg+1,jk+1,iera+1);
    hist_ptn[fg][iera][jk] = new TH1D(name,name,noptbins,ptbins);
    hist_ptn[fg][iera][jk]->Sumw2();

    if(fg==0){
    for(int bn=0; bn<(hist_ptn[fg][iera][jk]->GetNbinsX()); bn++){
      hist_ptn[fg][iera][jk]->SetBinContent(bn+1,hist_pt[fg][iera][jk]->GetBinContent(bn+2));
      hist_ptn[fg][iera][jk]->SetBinError(bn+1,hist_pt[fg][iera][jk]->GetBinError(bn+2));
      }
    }
   if(fg==1){
    for(int bn=0; bn<(hist_ptn[fg][iera][jk]->GetNbinsX()); bn++){
      hist_ptn[fg][iera][jk]->SetBinContent(bn+1,hist_pt[fg][iera][jk]->GetBinContent(bn+1));
      hist_ptn[fg][iera][jk]->SetBinError(bn+1,hist_pt[fg][iera][jk]->GetBinError(bn+1));
      }
    }

   }
  }
 }

 for(int fg=0; fg<2; fg++){
  for(int jk=0; jk<netarange; jk++){
   for(int iera=0; iera<neras; iera++){

    if(fg==1){
    for(int bn=0; bn<(hist_ptn[fg][iera][jk]->GetNbinsX()); bn++){
        hist_ptn[fg][iera][jk]->SetBinContent(bn+1,hist_ptn[fg][iera][jk]->GetBinContent(bn+1)*1./hist_ptn[fg][iera][jk]->GetBinWidth(bn+1));
        hist_ptn[fg][iera][jk]->SetBinError(bn+1,hist_ptn[fg][iera][jk]->GetBinError(bn+1)*1./(hist_ptn[fg][iera][jk]->GetBinWidth(bn+1)));
	}
    }

    hist_ptn[fg][iera][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_ptn[fg][iera][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_ptn[fg][iera][jk]->GetXaxis()->CenterTitle();    

    hist_ptn[fg][iera][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(pb^{-1}GeV^{-1})");
    hist_ptn[fg][iera][jk]->GetYaxis()->SetTitleSize(0.05);  
    hist_ptn[fg][iera][jk]->GetYaxis()->CenterTitle();
   
    hist_ptn[fg][iera][jk]->GetXaxis()->SetRangeUser(74,3000.);
         }
      }
    }

TCanvas *c2[netarange][neras];

TLegend *leg_pt[netarange][neras];

for(int jk=0; jk<netarange; jk++){
 for(int iera=0; iera<neras; iera++){

// if((ij!=ialgo)||(jk!=ieta)) continue;

sprintf(name,"ES_Compare_Canv_EtaBin%i_%s",jk+1,Era[iera]);
int ieta_tag = tags[iera];
c2[jk][iera] = tdrDiCanvas(name,hist_ptn[0][iera][jk],hist_ptn[1][iera][jk],ieta_tag,0);

leg_pt[jk][iera] = tdrLeg(0.6,0.7,0.95,0.95);

c2[jk][iera]->cd(1);

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

       hist_pt_rat[0][iera][jk] = (TH1D*)hist_ptn[1][iera][jk]->Clone();

       hist_pt_rat[0][iera][jk]->Divide(hist_ptn[0][iera][jk]);	
       hist_pt_rat[0][iera][jk]->GetXaxis()->SetRangeUser(74,3000.);
	
       hist_pt_rat[0][iera][jk]->GetYaxis()->SetTitle("Suman/Engin");
       hist_pt_rat[0][iera][jk]->GetYaxis()->SetTitleSize(0.075);
       hist_pt_rat[0][iera][jk]->GetYaxis()->CenterTitle();
       hist_pt_rat[0][iera][jk]->GetYaxis()->SetLabelSize(0.05);

       hist_pt_rat[0][iera][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
       hist_pt_rat[0][iera][jk]->GetXaxis()->SetTitleSize(0.075);
       hist_pt_rat[0][iera][jk]->GetXaxis()->CenterTitle();
       hist_pt_rat[0][iera][jk]->GetXaxis()->SetLabelSize(0.05);

//      hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(0,2000.);
      for(int fg=0; fg<2; fg++){
      tdrDraw(hist_ptn[fg][iera][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[jk][iera]->AddEntry(hist_ptn[fg][iera][jk],model_name[fg],"l");
      }    

 c2[jk][iera]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

  hist_pt_rat[0][iera][jk]->SetLineColor(col[1]);
  hist_pt_rat[0][iera][jk]->SetMinimum(0.8);
  hist_pt_rat[0][iera][jk]->SetMaximum(1.2);
  hist_pt_rat[0][iera][jk]->Draw("e");

line->Draw();

sprintf(name,"Engin_Me/JECv18/%s.eps",c2[jk][iera]->GetName());
c2[jk][iera]->SaveAs(name);
   
    }//iera
  }//jk

}

int main()
{
Compare_EnginSuman();
}
