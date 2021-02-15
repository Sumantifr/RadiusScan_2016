#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TLine.h"

void Compare_JEC_Data()
{

const int nfiles = 1;

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/Legacy_PROOF_2016total_wJEC_METFilter.root"};

const char *model_name[nfiles] = {"Data"};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int algo_col[nalgo] = {1,2,3,4,6,7,11,kCyan+2,kCyan-10, kBlue-7, kMagenta-9, kRed-5};
const int algo_sty[nalgo] = {2,3,4,5,8,21,22,23,25,26,27,28};

char name[1000];

TFile *filein;

TH2D* hist_JEC_2D[nfiles][nalgo][netarange];
TH2D* hist_JECL1_2D[nfiles][nalgo][netarange];
TH2D* hist_JECL2_2D[nfiles][nalgo][netarange];
TH2D* hist_JECL2L3_2D[nfiles][nalgo][netarange];

TProfile* hist_JEC[nfiles][nalgo][netarange];
TProfile* hist_JECL1[nfiles][nalgo][netarange];
TProfile* hist_JECL2[nfiles][nalgo][netarange];
TProfile* hist_JECL2L3[nfiles][nalgo][netarange];

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

    sprintf(name,"JetPt_vs_JEC_%s_EtaBin%i",JetRad[ij],jk+1);
    hist_JEC_2D[fg][ij][jk] = (TH2D*)filein->Get(name);
    hist_JEC[fg][ij][jk] = hist_JEC_2D[fg][ij][jk]->ProfileX();

    sprintf(name,"JetPt_vs_JECL1_%s_EtaBin%i",JetRad[ij],jk+1);
    hist_JECL1_2D[fg][ij][jk] = (TH2D*)filein->Get(name);
    hist_JECL1[fg][ij][jk] = hist_JECL1_2D[fg][ij][jk]->ProfileX();
 
    sprintf(name,"JetPt_vs_JECL2_%s_EtaBin%i",JetRad[ij],jk+1);
    hist_JECL2_2D[fg][ij][jk] = (TH2D*)filein->Get(name);
    hist_JECL2[fg][ij][jk] = hist_JECL2_2D[fg][ij][jk]->ProfileX();

    sprintf(name,"JetPt_vs_JECL2L3_%s_EtaBin%i",JetRad[ij],jk+1);
    hist_JECL2L3_2D[fg][ij][jk] = (TH2D*)filein->Get(name);
    hist_JECL2L3[fg][ij][jk] = hist_JECL2L3_2D[fg][ij][jk]->ProfileX();
//    if(jk==0){ cout<<JetRad[ij]<<" bin 1 "<<hist_JECL1[fg][ij][jk]->GetBinContent(1)<<endl;}   

    hist_JEC[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
    hist_JEC[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_JEC[fg][ij][jk]->GetXaxis()->SetLabelSize(0.04);

    hist_JEC[fg][ij][jk]->GetYaxis()->SetTitle("Total Correction");
    hist_JEC[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
    hist_JEC[fg][ij][jk]->GetYaxis()->SetLabelSize(0.04);


    hist_JECL1[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
    hist_JECL1[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_JECL1[fg][ij][jk]->GetXaxis()->SetLabelSize(0.04);

    hist_JECL1[fg][ij][jk]->GetYaxis()->SetTitle("L1 Correction");
    hist_JECL1[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
    hist_JECL1[fg][ij][jk]->GetYaxis()->SetLabelSize(0.04);

    hist_JECL2[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
    hist_JECL2[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_JECL2[fg][ij][jk]->GetXaxis()->SetLabelSize(0.04);

    hist_JECL2[fg][ij][jk]->GetYaxis()->SetTitle("L2 Correction");
    hist_JECL2[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
    hist_JECL2[fg][ij][jk]->GetYaxis()->SetLabelSize(0.04);

    hist_JECL2L3[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
    hist_JECL2L3[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_JECL2L3[fg][ij][jk]->GetXaxis()->SetLabelSize(0.04);
 
    hist_JECL2L3[fg][ij][jk]->GetYaxis()->SetTitle("L2L3 Residual Correction");
    hist_JECL2L3[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
    hist_JECL2L3[fg][ij][jk]->GetYaxis()->SetLabelSize(0.04);
  }
 }
}


TCanvas *c2[netarange];
TCanvas *c3[netarange];
TCanvas *c4[netarange];
TCanvas *c5[netarange];

TLegend *leg_tot[netarange];
TLegend *leg_L1[netarange];
TLegend *leg_L2[netarange];
TLegend *leg_L2L3[netarange];

for(int jk=0; jk<netarange; jk++) {

sprintf(name,"JEC_EtaBin%i",jk+1);

hist_JEC[0][4][jk]->SetMinimum(0.8);
hist_JEC[0][4][jk]->SetMaximum(1.15);

c2[jk] = tdrCanvas(name,hist_JEC[0][4][jk],6,0);

leg_tot[jk] = tdrLeg(0.7,0.14,0.9,0.5);
leg_tot[jk]->SetTextSize(0.04);
leg_tot[jk]->SetTextFont(42);

hist_JECL1[0][4][jk]->SetMinimum(0.8);
hist_JECL1[0][4][jk]->SetMaximum(1.15);

sprintf(name,"JECL1_EtaBin%i",jk+1);
c3[jk] = tdrCanvas(name,hist_JECL1[0][4][jk],6,0);

leg_L1[jk] = tdrLeg(0.7,0.6,0.9,0.9);
leg_L1[jk]->SetTextSize(0.04);
leg_L1[jk]->SetTextFont(42);

hist_JECL2[0][4][jk]->SetMinimum(0.8);
hist_JECL2[0][4][jk]->SetMaximum(1.15);

sprintf(name,"JECL2_EtaBin%i",jk+1);
c4[jk] = tdrCanvas(name,hist_JECL2[0][4][jk],6,0);

leg_L2[jk] = tdrLeg(0.7,0.2,0.9,0.5);
leg_L2[jk]->SetTextSize(0.04);
leg_L2[jk]->SetTextFont(42);

hist_JECL2L3[0][4][jk]->SetMinimum(0.8);
hist_JECL2L3[0][4][jk]->SetMaximum(1.15);

sprintf(name,"JECL2L3_EtaBin%i",jk+1);
c5[jk] = tdrCanvas(name,hist_JECL2L3[0][4][jk],6,0);

leg_L2L3[jk] = tdrLeg(0.7,0.15,0.9,0.5);
leg_L2L3[jk]->SetTextSize(0.04);
leg_L2L3[jk]->SetTextFont(42);


  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.04);


  c2[jk]->cd();

  gPad->SetLogx(1);

  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex((leg_x1+leg_x2),leg_y1,text1);

  for(int ij=0; ij<nalgo; ij++){
 
    for(int fg=0; fg<nfiles; fg++){
       tdrDraw(hist_JEC[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,algo_col[ij] ,1001,2);
     }
  
  leg_tot[jk]->AddEntry(hist_JEC[0][ij][jk],jetname[ij],"lp"); 

   }

  leg_tot[jk]->Draw();

  sprintf(name,"Data_JEC/Total_JEC/%s.eps",c2[jk]->GetName());
  c2[jk]->SaveAs(name);


  c3[jk]->cd();

  gPad->SetLogx(1);

  latex.DrawLatex((leg_x1+leg_x2),leg_y1,text1);

  for(int ij=0; ij<nalgo; ij++){

    for(int fg=0; fg<nfiles; fg++){
       tdrDraw(hist_JECL1[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,algo_col[ij] ,1001,2);
     }
  
  leg_L1[jk]->AddEntry(hist_JECL1[0][ij][jk],jetname[ij],"lp");

   }

  sprintf(name,"Data_JEC/L1_JEC/%s.eps",c3[jk]->GetName());
  c3[jk]->SaveAs(name);

  c4[jk]->cd();

  gPad->SetLogx(1);

  latex.DrawLatex((leg_x1+leg_x2)-0.4,leg_y1,text1);

  for(int ij=0; ij<nalgo; ij++){

    for(int fg=0; fg<nfiles; fg++){
       tdrDraw(hist_JECL2[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,algo_col[ij] ,1001,2);
     }

  leg_L2[jk]->AddEntry(hist_JECL2[0][ij][jk],jetname[ij],"lp");

   }

  sprintf(name,"Data_JEC/L2_JEC/%s.eps",c4[jk]->GetName());
  c4[jk]->SaveAs(name);

  c5[jk]->cd();

  gPad->SetLogx(1);

  latex.DrawLatex((leg_x1+leg_x2)-0.4,leg_y1,text1);

  for(int ij=0; ij<nalgo; ij++){

    for(int fg=0; fg<nfiles; fg++){
       tdrDraw(hist_JECL2L3[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,algo_col[ij] ,1001,2);
     }

  leg_L2L3[jk]->AddEntry(hist_JECL2L3[0][ij][jk],jetname[ij],"lp");

   }

  sprintf(name,"Data_JEC/L2L3_JEC/%s.eps",c5[jk]->GetName());
  c5[jk]->SaveAs(name);
 } 


//// ak4&ak8 only ////
TLine *line = new TLine(74,1.,7000,1.);
line->SetLineColor(kYellow+1);

TCanvas *c1[4][netarange];
TLegend *leg1[4][netarange];

for(int jk=0; jk<netarange; jk++) {

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.04);

  TString text1;
  text1+=  ybinname[jk];

 for(int kl=0; kl<4; kl++) {

  if(kl==0){
        sprintf(name,"Total_JEC_ak4ak8_EtaBin%i",jk+1);
	c1[kl][jk] = tdrCanvas(name,hist_JEC[0][4][jk],6,0);
	leg1[kl][jk] = tdrLeg(0.7,0.2,0.9,0.4);

	c1[kl][jk]->cd();

	gPad->SetLogx(1);
	latex.DrawLatex((leg_x1+leg_x2)-0.4,leg_y1,text1);

	for(int fg=0; fg<nfiles; fg++){
	 for(int ij=0; ij<nalgo; ij++){
	   if(ij==3||ij==7){
 	      tdrDraw(hist_JEC[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,algo_col[ij] ,1001,2);
	      leg1[kl][jk]->AddEntry(hist_JEC[0][ij][jk],jetname[ij],"lp");
		} 
	   }
    	}
	line->Draw("sames");
	sprintf(name,"Data_JEC/Total_JEC/%s.eps",c1[kl][jk]->GetName());
  	c1[kl][jk]->SaveAs(name);
    }

  if(kl==1){
        sprintf(name,"L1_JEC_ak4ak8_EtaBin%i",jk+1);
        c1[kl][jk] = tdrCanvas(name,hist_JECL1[0][4][jk],6,0);
        leg1[kl][jk] = tdrLeg(0.7,0.6,0.9,0.8);
     
        c1[kl][jk]->cd();

	gPad->SetLogx(1);
        latex.DrawLatex((leg_x1+leg_x2)-0.4,leg_y1,text1);
	
        for(int fg=0; fg<nfiles; fg++){
         for(int ij=0; ij<nalgo; ij++){
           if(ij==3||ij==7){
              tdrDraw(hist_JECL1[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,algo_col[ij] ,1001,2);
              leg1[kl][jk]->AddEntry(hist_JECL1[0][ij][jk],jetname[ij],"lp");
                }
           }
        }
	line->Draw("sames");
        sprintf(name,"Data_JEC/L1_JEC/%s.eps",c1[kl][jk]->GetName());
        c1[kl][jk]->SaveAs(name);
    }

  if(kl==2){
        sprintf(name,"L2_JEC_ak4ak8_EtaBin%i",jk+1);
        c1[kl][jk] = tdrCanvas(name,hist_JECL2[0][4][jk],6,0);
        leg1[kl][jk] = tdrLeg(0.7,0.2,0.9,0.4);
    	
	c1[kl][jk]->cd();

	gPad->SetLogx(1);
        latex.DrawLatex((leg_x1+leg_x2)-0.4,leg_y1,text1);

        for(int fg=0; fg<nfiles; fg++){
         for(int ij=0; ij<nalgo; ij++){
           if(ij==3||ij==7){
              tdrDraw(hist_JECL2[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,algo_col[ij] ,1001,2);
              leg1[kl][jk]->AddEntry(hist_JECL2[0][ij][jk],jetname[ij],"lp");
                }
           }
        }
	line->Draw("sames");
        sprintf(name,"Data_JEC/L2_JEC/%s.eps",c1[kl][jk]->GetName());
        c1[kl][jk]->SaveAs(name);
    }
 
  if(kl==3){
        sprintf(name,"L2L3_JEC_ak4ak8_EtaBin%i",jk+1);
        c1[kl][jk] = tdrCanvas(name,hist_JECL2L3[0][4][jk],6,0);
        leg1[kl][jk] = tdrLeg(0.7,0.2,0.9,0.4);
    
	c1[kl][jk]->cd();

	gPad->SetLogx(1);
        latex.DrawLatex((leg_x1+leg_x2)-0.4,leg_y1,text1);

        for(int fg=0; fg<nfiles; fg++){
         for(int ij=0; ij<nalgo; ij++){
           if(ij==3||ij==7){
              tdrDraw(hist_JECL2L3[fg][ij][jk],algo_sty[ij],algo_col[ij],kSolid,algo_col[ij] ,1001,2);
              leg1[kl][jk]->AddEntry(hist_JECL2L3[0][ij][jk],jetname[ij],"lp");
                }
           }
        }
	line->Draw("sames");
        sprintf(name,"Data_JEC/L2L3_JEC/%s.eps",c1[kl][jk]->GetName());
        c1[kl][jk]->SaveAs(name);
    }

 }
}


}

int main()
{
Compare_JEC_Data();
}
