#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>
#include <iostream>

void Compare_TUnfold()
{
const int nfiles =3;
const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_TUnfold.root"};

const char *model_name[nfiles] = {"D'Agostini","TUnfold","SVD"};
const int col[nfiles] = {2,4,6};
const int sty[nfiles] = {1,2,3};

const int ref = 3;

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[1000];

double min_x = 97.;
double max_x = 3000.;

TLine *line = new TLine(min_x,1.,max_x,1.);
line->SetLineColor(kCyan);

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_radius[nfiles][nalgo][netarange];

TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

float leg_x1 = 0.25;
float leg_y1 = 0.6;
float leg_x2 = 0.45;
float leg_y2 = 0.9;

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
cout<<name<<endl;
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

    if(fg==0){
    sprintf(name,"tuf_TUnfold_%s_Etabin%i",JetRad[ij],jk+1);
	}
    if(fg==1){
    sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1);
	}
    if(fg==2){
    sprintf(name,"svd_unfold_%s_Etabin%i",JetRad[ij],jk+1);
        }

    hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);

     hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
     hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
     hist_pt[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
     hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();

     hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb^{-1}GeV^{-1})");
     hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
     hist_pt[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
     hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();

     if(fg!=0) {
                 hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
                 hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);


//               hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetRangeUser(min_x,max_x);
                 hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetTitleSize(0.095);
                 hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetLabelSize(0.09);
//               hist_pt_rat[fg-1][ij][jk]->GetXaxis()->

                 hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Ratio to D'Agostini");
                 hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.075);
                 hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.075);
                 hist_pt_rat[fg-1][ij][jk]->GetYaxis()->CenterTitle();
                 hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetNdivisions(406);
		 hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.8);	 	
 
		 hist_pt_rat[fg-1][ij][jk]->SetLineColor(col[fg]);
	         if(ij==3&&jk==0) { cout<<"rat plot "<<fg<<" col "<<col[fg]<<endl; }
                }
  }//jk
 }//ij
}//fg

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   hist_radius[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt[fg][ref][jk]) ;

   hist_radius[fg][ij][jk]->GetXaxis()->SetRangeUser(min_x,max_x);
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();


   if(fg!=0) {
                 hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
                 hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);

                 hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetRangeUser(min_x,max_x);
                 hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetTitleSize(0.095);
                 hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetLabelSize(0.085);

	}
                 hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Ratio to D'Agostini");
                 hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.075);
                 hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.075);
                 hist_radius_rat[fg-1][ij][jk]->GetYaxis()->CenterTitle();
                 hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetNdivisions(406);
		 hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.8);

		 hist_radius_rat[fg-1][ij][jk]->SetLineColor(col[fg]);
   }
  }
 }

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
   for(int fg=0; fg<nfiles; fg++){
     hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(min_x,max_x);
     hist_radius[fg][ij][jk]->GetXaxis()->SetRangeUser(min_x,max_x);
        if(fg!=0){
                        hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetRangeUser(min_x,max_x);
                        hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetRangeUser(min_x,max_x);
                 }
        }
   }
 }

TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

 sprintf(name,"ExCor_Pt_%s_EtaBin%i",JetRad[ij],jk+1);
 c2[ij][jk] = tdrDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],6,0);

 leg_pt[ij][jk] = tdrLeg(0.6,0.7,0.85,0.95);
 leg_pt[ij][jk]->SetTextFont(42);
 leg_pt[ij][jk]->SetTextSize(0.045);

 c2[ij][jk]->cd(1);

  gPad->SetLogx(1);
  gPad->SetLogy(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.065);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.125,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.2,text1);

  for(int fg=0; fg<nfiles; fg++){
  tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"l");
    }

  c2[ij][jk]->cd(2);

  gPad->SetLogx(1);

  for(int fg=0; fg<(nfiles-1); fg++){

        hist_pt_rat[fg][ij][jk]->SetMaximum(1.22);
        hist_pt_rat[fg][ij][jk]->SetMinimum(0.78);
	hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);

   if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
        else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
   }

  line->Draw("sames");

  sprintf(name,"TUnfold_Plots/Pt_Plots/%s.eps",c2[ij][jk]->GetName());
  c2[ij][jk]->SaveAs(name);

  }
 }

 TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

 if((ij<2)&&(jk>6)) continue;

 sprintf(name,"ExCor_Ratio_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] = tdrDiCanvas(name,hist_radius[0][ij][jk],hist_radius[1][ij][jk],6,0);

  leg_radius[ij][jk] = tdrLeg(0.6,0.7,0.85,0.95);
  leg_radius[ij][jk]->SetTextFont(42);
  leg_radius[ij][jk]->SetTextSize(0.045);

  c3[ij][jk]->cd(1);

  gPad->SetLogx(1);
  gPad->SetLogy(0);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.065);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1+0.2,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1+0.125,text1);

  for(int fg=0; fg<nfiles; fg++){

   hist_radius[fg][ij][jk]->SetMinimum(0);
   hist_radius[fg][ij][jk]->SetMaximum(3.);

   tdrDraw(hist_radius[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
   leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"l");
   }

   c3[ij][jk]->cd(2);

   gPad->SetLogx(1);

   for(int fg=0; fg<(nfiles-1); fg++){

   hist_radius_rat[fg][ij][jk]->SetMaximum(1.22);
   hist_radius_rat[fg][ij][jk]->SetMinimum(0.78);
   hist_radius_rat[fg][ij][jk]->SetLineColor(col[fg+1]);

   if(fg==0) {  hist_radius_rat[fg][ij][jk]->Draw("e"); }
        else { hist_radius_rat[fg][ij][jk]->Draw("sames"); }
   }

   line->Draw("sames");

   sprintf(name,"TUnfold_Plots/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
   c3[ij][jk]->SaveAs(name);

    }
  }
}

int main()
{
Compare_TUnfold();
}
