	#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>

void Compare_Data_ModelVar()
{
const int nfiles = 3;

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Histograms_P8_Summer_tight.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_MG.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_Herwig.root"};

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_MG.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG_MC_Herwig.root"};

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/Summer2016_8X21/Herwig_SUmmer_PUSub.root","/home/suman/RooUnfold/Unfolded_2016_Data_Herwig_MC_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_Herwig_MC_MG.root","/home/suman/RooUnfold/Unfolded_2016_Data_Herwig_MC_Herwig.root"};

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_MG.root","/home/suman/RooUnfold/Unfolded_2016_Data_Hwg.root"};

//const char *unf_tech[3] = {"SVD Unfolding","Bin by Bin Unfolding","D'Agostini Unfolding"};
const int nunf = 3;
const char *unf_tech[nunf] = {"SVD Unfolding","TUnfold","D'Agostini Unfolding"};
const char *unf_name[nunf] = {"svd_unfold","tuf_TUnfold","bayes_unfold"};
const char *unf_store[nunf] = {"SVD","TUnfold","Bayesian"};

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_MG_excorfac2_84.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_Hwg_excorfac2_84.root"};
const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_P8_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_MG_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_Hwg_TUnfold.root"};

const char *model_name[nfiles] = {"Unfolded by Pythia8","Unfolded by Madgraph","Unfolded by Herwig"};
const int col[nfiles] = {6,2,4};

const int ref = 3;

static const int noptbins = 31;

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

double unf_pt_up[nalgo][netarange][noptbins] = {{{0.}}};
double unf_pt_dn[nalgo][netarange][noptbins] = {{{0.}}};
double unf_rad_up[nalgo][netarange][noptbins] = {{{0.}}};
double unf_rad_dn[nalgo][netarange][noptbins] = {{{0.}}};

ofstream fp_pt;
fp_pt.open("Unf_Data_Pt_TUnf.log");

ofstream fp_rad;
fp_rad.open("Unf_Data_Rad_TUnf.log");

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange][nunf];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange][nunf];
TH1D* hist_pt_org[nfiles][nalgo][netarange][nunf];

TH1D* hist_radius[nfiles][nalgo][netarange][nunf];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange][nunf];

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

float data_lumi = 1.;

TLine *line = new TLine(84,1.,3000.,1.) ;
line->SetLineColor(7);

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<nunf; kl++){

     int unf_tag = kl;

     sprintf(name,"%s_%s_Etabin%i",unf_name[unf_tag],JetRad[ij],jk+1);

     hist_pt[fg][ij][jk][kl] = (TH1D*)filein->Get(name);
     hist_pt_org[fg][ij][jk][kl] = (TH1D*)hist_pt[fg][ij][jk][kl]->Clone();

   for(int bn=0; bn<(hist_pt[fg][ij][jk][kl]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk][kl]->SetBinContent(bn+1,hist_pt[fg][ij][jk][kl]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk][kl]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk][kl]->SetBinError(bn+1,hist_pt[fg][ij][jk][kl]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk][kl]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }//bn

    hist_pt[fg][ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)") ;
    hist_pt[fg][ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk][kl]->GetXaxis()->CenterTitle();
    hist_pt[fg][ij][jk][kl]->GetXaxis()->SetRangeUser(84,3000.);

    hist_pt[fg][ij][jk][kl]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb^{-1}GeV^{-1})");
    hist_pt[fg][ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk][kl]->GetYaxis()->CenterTitle();

   }//kl
  }//jk
 }//ij
}//fg

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<nunf; kl++){ 

   hist_radius[fg][ij][jk][kl] = (TH1D*)hist_pt_org[fg][ij][jk][kl]->Clone();
   hist_radius[fg][ij][jk][kl]->Divide(hist_pt_org[fg][ref][jk][kl]) ;

   hist_radius[fg][ij][jk][kl]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk][kl]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk][kl]->GetXaxis()->CenterTitle();
   hist_radius[fg][ij][jk][kl]->GetXaxis()->SetRangeUser(84,3000.);

   hist_radius[fg][ij][jk][kl]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[fg][ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk][kl]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk][kl]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk][kl]->SetMinimum(0);
   hist_radius[fg][ij][jk][kl]->SetMaximum(3.);

   }
  }
 }
}

TCanvas *c2[nalgo][netarange][nunf];

TLegend *leg_pt[nalgo][netarange][nunf];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
  for(int kl=0; kl<nunf; kl++){
  
   int unf_tag = kl;

 sprintf(name,"P8_Compare_Canv_%s_EtaBin%i_%s",JetRad[ij],jk+1,unf_name[kl]);
 c2[ij][jk][kl] = tdrDiCanvas(name,hist_pt[0][ij][jk][kl],hist_pt[1][ij][jk][kl],6,0);

 leg_pt[ij][jk][kl] = tdrLeg(0.57,0.7,0.77,0.95);

 c2[ij][jk][kl]->cd(1);

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
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];
  TString text2;
  text2+= unf_tech[unf_tag];

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);

  latex.SetTextSize(0.035);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1+0.15,text2);
//  hist_pt[0][ij][jk]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

      if(fg!=0){
      hist_pt_rat[fg-1][ij][jk][kl] = (TH1D*)hist_pt[fg][ij][jk][kl]->Clone();
      hist_pt_rat[fg-1][ij][jk][kl]->Divide(hist_pt[0][ij][jk][kl]);
      hist_pt_rat[fg-1][ij][jk][kl]->GetYaxis()->SetTitle("Unfolded / Unfolded by P8");
      hist_pt_rat[fg-1][ij][jk][kl]->GetYaxis()->SetTitleSize(0.04);
      hist_pt_rat[fg-1][ij][jk][kl]->GetYaxis()->CenterTitle();
        }


      tdrDraw(hist_pt[fg][ij][jk][kl],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk][kl]->AddEntry(hist_pt[fg][ij][jk][kl],model_name[fg],"l");
    }

 leg_pt[ij][jk][kl]->SetTextSize(0.03);
 c2[ij][jk][kl]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

for(int fg=0; fg<(nfiles-1); fg++){

   hist_pt_rat[fg][ij][jk][kl]->SetLineColor(col[fg+1]);
   hist_pt_rat[fg][ij][jk][kl]->SetMinimum(0.5);
   hist_pt_rat[fg][ij][jk][kl]->SetMaximum(1.5);


 if(fg==0) {  hist_pt_rat[fg][ij][jk][kl]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk][kl]->Draw("sames"); }

 }

line->Draw();

sprintf(name,"Data_Unfold_Model/TUnfold/%s/Pt_Plots/%s.eps",unf_store[unf_tag],c2[ij][jk][kl]->GetName());
c2[ij][jk][kl]->SaveAs(name);

   }//kl
  }//jk
 }//ij

TCanvas *c3[nalgo][netarange][nunf];

TLegend *leg_radius[nalgo][netarange][nunf];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
  for(int kl=0; kl<nunf; kl++){ 

    int unf_tag = kl;

 if((ij<2)&&(jk>6)) continue;

  sprintf(name,"P8_Ratio_Compare_Canv_%s_EtaBin%i_%s",JetRad[ij],jk+1,unf_name[kl]);
  c3[ij][jk][kl] = tdrDiCanvas(name,hist_radius[0][ij][jk][kl],hist_radius[1][ij][jk][kl],6,0);

  leg_radius[ij][jk][kl] = tdrLeg(0.57,0.7,0.77,0.95);

  c3[ij][jk][kl]->cd(1);

  gPad->SetLogx(1);
  gPad->SetLogy(0);

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
  TString text2;
  text2+= unf_tech[unf_tag];  

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);

  latex.SetTextSize(0.035);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1+0.15,text2);

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk][kl] = (TH1D*)hist_radius[fg][ij][jk][kl]->Clone();
      hist_radius_rat[fg-1][ij][jk][kl]->Divide(hist_radius[0][ij][jk][kl]);
      hist_radius_rat[fg-1][ij][jk][kl]->GetYaxis()->SetTitle("Unfolded / Unfolded by P8");
      hist_radius_rat[fg-1][ij][jk][kl]->GetYaxis()->SetTitleSize(0.04);
      hist_radius_rat[fg-1][ij][jk][kl]->GetYaxis()->CenterTitle();

      hist_radius_rat[fg-1][ij][jk][kl]->SetMinimum(0.5);
      hist_radius_rat[fg-1][ij][jk][kl]->SetMaximum(1.5);

        }

      tdrDraw(hist_radius[fg][ij][jk][kl],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[ij][jk][kl]->AddEntry(hist_radius[fg][ij][jk][kl],model_name[fg],"l");
    }

   leg_radius[ij][jk][kl]->SetTextSize(0.03);

   c3[ij][jk][kl]->cd(2);

   gPad->SetLogx(1);
   gPad->SetLogy(0);

   for(int fg=0; fg<(nfiles-1); fg++){
   hist_radius_rat[fg][ij][jk][kl]->SetLineColor(col[fg+1]);

   if(fg==0){
         hist_radius_rat[fg][ij][jk][kl]->Draw("e");
   }else{
         hist_radius_rat[fg][ij][jk][kl]->Draw("sames");
        }

   }

  line->Draw();

  sprintf(name,"Data_Unfold_Model/TUnfold/%s/Ratio_Plots/%s.eps",unf_store[unf_tag],c3[ij][jk][kl]->GetName());
  c3[ij][jk][kl]->SaveAs(name);

   }//kl
  }//jk
 }//ij


int unf_tag = 2;
unf_tag -= 1;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int bn=0; bn<noptbins; bn++){

    double ar[nfiles] = {0};
   double bs[nfiles] = {0};

    for(int fg=0; fg<nfiles; fg++){
                ar[fg] = hist_pt[fg][ij][jk][unf_tag]->GetBinContent(bn+1) - hist_pt[0][ij][jk][unf_tag]->GetBinContent(bn+1);
                bs[fg] = hist_radius[fg][ij][jk][unf_tag]->GetBinContent(bn+1) -  hist_radius[0][ij][jk][unf_tag]->GetBinContent(bn+1);
                }

      if(ar[1]*ar[2]>0){
        if(ar[1]>0) { unf_pt_up[ij][jk][bn] = (abs(ar[1])>abs(ar[2]))?abs(ar[1]):abs(ar[2]) ; unf_pt_dn[ij][jk][bn] = 0.;}
        else { unf_pt_dn[ij][jk][bn] = (abs(ar[1])>abs(ar[2]))?abs(ar[1]):abs(ar[2]) ; unf_pt_up[ij][jk][bn] = 0.;}
        }
        else{
        if(ar[1]>0) { unf_pt_up[ij][jk][bn] = ar[1] ;  unf_pt_dn[ij][jk][bn] = abs(ar[2]) ; }
        else { if (ar[2]>0) {  unf_pt_up[ij][jk][bn] = ar[2] ;  unf_pt_dn[ij][jk][bn] = abs(ar[1]) ; }  }
        }

        if(bs[1]*bs[2]>0){
        if(bs[1]>0) { unf_rad_up[ij][jk][bn] = (abs(bs[1])>abs(bs[2]))?abs(bs[1]):abs(bs[2]) ; unf_rad_dn[ij][jk][bn] = 0.;}
        else { unf_rad_dn[ij][jk][bn] = (abs(bs[1])>abs(bs[2]))?abs(bs[1]):abs(bs[2]) ; unf_rad_up[ij][jk][bn] = 0.;}
        }
        else{
        if(bs[1]>0) { unf_rad_up[ij][jk][bn] = bs[1] ;  unf_rad_dn[ij][jk][bn] = abs(bs[2]) ; }
        else { if (bs[2]>0) {  unf_rad_up[ij][jk][bn] = bs[2] ;  unf_rad_dn[ij][jk][bn] = abs(bs[1]) ; }  }
        }

        unf_pt_up[ij][jk][bn]*=1./max(1.e-6,hist_pt[0][ij][jk][unf_tag]->GetBinContent(bn+1));
        unf_pt_dn[ij][jk][bn]*=1./max(1.e-6,hist_pt[0][ij][jk][unf_tag]->GetBinContent(bn+1));

	unf_rad_up[ij][jk][bn]*=1./max(1.e-6,hist_radius[0][ij][jk][unf_tag]->GetBinContent(bn+1));
        unf_rad_dn[ij][jk][bn]*=1./max(1.e-6,hist_radius[0][ij][jk][unf_tag]->GetBinContent(bn+1));

	fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<max(unf_pt_up[ij][jk][bn],unf_pt_dn[ij][jk][bn])<<'\t'<<max(unf_pt_up[ij][jk][bn],unf_pt_dn[ij][jk][bn])<<endl;
        fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<max(unf_rad_up[ij][jk][bn],unf_rad_dn[ij][jk][bn])<<'\t'<<max(unf_rad_up[ij][jk][bn],unf_rad_dn[ij][jk][bn])<<endl;
   }
  }
 }


fp_pt.close();
fp_rad.close();

}

int main()
{
Compare_Data_ModelVar();
}
