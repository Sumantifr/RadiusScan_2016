#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TMultiGraph.h"

void Final_XsxtionvsR()
{

const int nfiles = 4;

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_nocor.root" /*"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/2016Files/hist_RecoJetchs_PU_Data_JetHT2016BCDEFGH_new.root"*//*hist_RecoJetchs_PU_Data_JetHT2016G_JECor.root"*//*AJEC/hist_RecoJetchs_PU_Data_JetHT2016EF_CMSSW8X21.root"*/,"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/test_Herwig.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root"};
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor_excor.root",
								"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root",
								"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15_new_excor.root",
								"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root"};
	
double data_lumi = /*2.562+3.127+7.169+8.545;32.882*/ 34.67; //(7.6+3.106+2.535+4.330+4.049+3.127+0.217);

const int ref = 5;

const char *model_name[nfiles] = {"2016BCDEFGH","Herwig","Pythia8(CUETP8M1)","Madgraph"};
const int col[nfiles] = {1,/*12,*/4,6,2};
const int algo_style[nfiles] = {20,21,22,23};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

double ymax[netarange] = {2.,2.,2.,2.5,3.,3.,3.,3.,3.,3.} ;

const int nopbins = 10;
double pbins[nopbins+1]={74, 97, 133, 220, 272, 330, 395, 468, 548, 638, 2500.0};

const char* pbin_name[nopbins] = {"74 < Pt < 97","97 < Pt < 133", "133 < Pt <196", "196 < Pt <272", "272 < Pt <330","330< Pt <395","395< Pt <468","468< Pt <548","548< Pt <592","Pt > 614"} ;

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];

TLine *line = new TLine(0,1,1.2,1.);
line->SetLineColor(7);

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

	if((fg<1)){ sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;}
	if((fg>0)) {sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}

	hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
	if(fg==0) { hist_pt[fg][ij][jk]->Scale(1./data_lumi) ;  }

	for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
	     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     	     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    	}

//	if(fg>0) { hist_pt[fg][ij][jk]->Scale(hist_pt[fg][ij][jk]->Integral()*1./hist_pt[0][ij][jk]->Integral());  }

      }
   }
}

double xsection[nfiles][nalgo][netarange][nopbins];

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
   for(int jk=0; jk<netarange; jk++){

     TAxis *axis = hist_pt[fg][ij][jk]->GetXaxis();

     int amin =0, amax =0;

     for(int kl=0; kl<nopbins; kl++){
	amin = axis->FindBin(pbins[kl]);
	amax = axis->FindBin(pbins[kl+1]);

	xsection[fg][ij][jk][kl] = hist_pt[fg][ij][jk]->Integral(amin,amax);
//	if(fg==0) { cout<<JetRad[ij]<<"eta "<<jk+1<<" pt "<<kl+1<<" sigma "<<xsection[fg][ij][jk][kl]<<endl ;}

       }

      }
    }
  }

TH1D *sigmaR[nfiles][netarange][nopbins];
TH1D *sigmaR_rat[nfiles-1][netarange][nopbins];

for(int fg=0; fg<nfiles; fg++){
 for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<nopbins; kl++){
	sprintf(name,"histRad_EtaBin%i_ptbin%i_File%i",jk+1,kl+1,fg+1);
	sigmaR[fg][jk][kl] = new TH1D(name,name,nalgo,0.05,1.25);
	for(int ij=0; ij<nalgo; ij++){
	sigmaR[fg][jk][kl]->SetBinContent(ij+1,xsection[fg][ij][jk][kl]);
	}
	if(fg>0){
	sigmaR_rat[fg-1][jk][kl] = (TH1D*)sigmaR[fg][jk][kl]->Clone();
	sigmaR_rat[fg-1][jk][kl]->Divide(sigmaR[0][jk][kl]);

	sigmaR_rat[fg-1][jk][kl]->SetLineColor(col[fg]);
	sigmaR_rat[fg-1][jk][kl]->SetMaximum(ymax[jk]);
	sigmaR_rat[fg-1][jk][kl]->SetMinimum(0.);

	sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetTitle("Jet Radius");
	sigmaR_rat[fg-1][jk][kl]->GetXaxis()->CenterTitle();
	sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetTitleSize(0.07);
	sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetLabelSize(0.06);
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitle("MC/Data");
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->CenterTitle();
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitleSize(0.055);
	sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetLabelSize(0.065);

	sigmaR_rat[fg-1][jk][kl]->SetMarkerSize(1);
	sigmaR_rat[fg-1][jk][kl]->SetMarkerStyle(algo_style[fg]);
	sigmaR_rat[fg-1][jk][kl]->SetMarkerColor(col[fg]);
	}
   }
 }
}

TGraph *gr_pt[nfiles][netarange][nopbins];
TMultiGraph *mul_gr[netarange][nopbins];

TLegend *leg[netarange][nopbins];

for(int jk=0; jk<netarange; jk++){
  for(int kl=0; kl<nopbins; kl++){

        if(jk<6){
	leg[jk][kl] = new TLegend(0.18,0.65,0.4,0.9);
	}
	else{
        leg[jk][kl] = new TLegend(0.6,0.15,0.8,0.4);
	}

	mul_gr[jk][kl] = new TMultiGraph();

     for(int fg=0; fg<nfiles; fg++){

	gr_pt[fg][jk][kl] = new TGraph();

	for(int ij=0; ij<nalgo; ij++){
	gr_pt[fg][jk][kl]->SetPoint(ij,0.1*(ij+1),xsection[fg][ij][jk][kl]) ;
        }	

	gr_pt[fg][jk][kl]->SetLineColor(col[fg]);
	gr_pt[fg][jk][kl]->GetXaxis()->SetTitle("Jet Radius");
	gr_pt[fg][jk][kl]->GetXaxis()->SetTitleSize(0.05);
	gr_pt[fg][jk][kl]->GetXaxis()->SetLabelSize(0.035);

	gr_pt[fg][jk][kl]->SetMarkerColor(col[fg]);
	gr_pt[fg][jk][kl]->SetMarkerSize(1);
	gr_pt[fg][jk][kl]->SetMarkerStyle(algo_style[fg]);

	mul_gr[jk][kl]->Add(gr_pt[fg][jk][kl]);
	leg[jk][kl]->AddEntry(gr_pt[fg][jk][kl],model_name[fg],"l");
  }
//	mul_gr[jk][kl]->GetXaxis()->SetTitle("Jet Radius");
//	mul_gr[jk][kl]->GetXaxis()->SetTitleSize(0.05);
//	mul_gr[jk][kl]->GetXaxis()->SetLabelSize(0.035);
 }	
}

TCanvas *c2[netarange][nopbins];
//TLegend *leg[netarange][nopbins];

for(int jk=0; jk<netarange; jk++){
 for(int kl=0; kl<nopbins; kl++){

   sprintf(name,"Xsection_EtaBin%i_PtBin%i",jk+1,kl+1);
   c2[jk][kl] = tdrDiCanvas(name,sigmaR[2][jk][kl],sigmaR[0][jk][kl],4,0);
  // c2[kl][kl] = new TCanvas(name,name,800,600);
   //cout<<"canv "<<c2[kl][kl]->GetName()<<endl;
   c2[jk][kl]->cd(1);
   gPad->SetLogy(1);

   TLatex latex;
   latex.SetNDC();
   latex.SetTextAngle(0);
   latex.SetTextColor(kBlack);

   latex.SetTextFont(42);
   latex.SetTextAlign(31);
   latex.SetTextSize(0.05);

   TString text;
   text+= ybinname[jk];
   TString text1;
   text1+= pbin_name[kl] ;



//   sigmaR[jk][kl]->Draw();
   mul_gr[jk][kl]->Draw("ALP");

   leg[jk][kl]->SetBorderSize(0);
   leg[jk][kl]->Draw();


   if(jk<6){
   latex.DrawLatex(0.7,0.85,text);
   latex.DrawLatex(0.7,0.8,text1);
        }else{
           latex.DrawLatex(0.7,0.45,text);
           latex.DrawLatex(0.7,0.4,text1);
        }

   c2[jk][kl]->cd(2);

   for(int fg=0; fg<(nfiles-1); fg++){
  if(fg==0) {    sigmaR_rat[fg][jk][kl]->Draw("CP"); }
	else {	sigmaR_rat[fg][jk][kl]->Draw("CPSAME");	}
   }

   line->Draw();
  

  sprintf(name,"Xsection_Plots/Legacy_Excor/XsectionR_EtaBin%i_PtBin%i.eps",jk+1,kl+1);
  c2[jk][kl]->SaveAs(name);

 }
}

}

int main()
{
Final_XsxtionvsR();
}

