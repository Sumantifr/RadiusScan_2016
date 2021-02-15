#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>

void Compare_UnfTech_Var()
{
const int nfiles = 3;
const int nmc = 3;

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8.root","/home/suman/RooUnfold/Unfolded_2016_Data_P8.root"};
//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor.root"};

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root"};

//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excor.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excor.root"};

const char *filenames[nmc][nfiles] = {{"/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_P8_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_P8_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_P8_TUnfold.root"},
									  {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_MG_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_MG_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_MG_TUnfold.root"},
									  {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_Hwg_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_Hwg_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuples_MC_Hwg_TUnfold.root"}};

const char *model_name[nfiles] = {"Bayesian","SVD",/*"BinbyBin",*/"TUnfold"};
const int col[nfiles] = {1,2,4};

const char *mc_name[nmc] = {"P8","MG","Hwg"};

/*
const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_TUnfold.root","/home/suman/RooUnfold/Unfolded_2016_Data_TUnfold.root"};

const char *model_name[nfiles] = {"Bayesian","TUnfold"};
const int col[nfiles] = {1,2};
*/
const int ref = 3;

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[1000];

const int noptbins = 31;
double model_pt_up[nmc][nalgo][netarange][noptbins];
double model_pt_dn[nmc][nalgo][netarange][noptbins];
double model_rad_up[nmc][nalgo][netarange][noptbins];
double model_rad_dn[nmc][nalgo][netarange][noptbins];

ofstream fp_pt[nmc];
ofstream fp_rad[nmc];

for(int mc=0; mc<nmc; mc++){
sprintf(name,"Unfolding_Tech_Err_Pt_TUnfold_%s.log",mc_name[mc]);
fp_pt[mc].open(name);

sprintf(name,"Unfolding_Tech_Err_Rad_TUnfold_%s.log",mc_name[mc]) ;
fp_rad[mc].open(name);
}

TFile *filein;

TH1D* hist_pt[nmc][nfiles][nalgo][netarange];
TH1D* hist_pt_rat[nmc][nfiles-1][nalgo][netarange];
TH1D* hist_pt_org[nmc][nfiles][nalgo][netarange];

TH1D* hist_radius[nmc][nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nmc][nfiles-1][nalgo][netarange];

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

TLine *line = new TLine(74,1.,3000,1.);

float data_lumi = 1.;

for(int mc=0; mc<nmc; mc++){
 for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[mc][fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

if(fg==0) {     sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1); }

if(fg==1) {     sprintf(name,"svd_unfold_%s_Etabin%i",JetRad[ij],jk+1); }
if(fg==2) {     sprintf(name,"BbB_unfold_%s_Etabin%i",JetRad[ij],jk+1); }
/*
if(fg==1) {     sprintf(name,"tuf_TUnfold_%s_EtaBin%i",JetRad[ij],jk+1); }
*/
     hist_pt[mc][fg][ij][jk] = (TH1D*)filein->Get(name);
     hist_pt_org[mc][fg][ij][jk] = (TH1D*)hist_pt[mc][fg][ij][jk]->Clone();

   for(int bn=0; bn<(hist_pt[mc][fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[mc][fg][ij][jk]->SetBinContent(bn+1,hist_pt[mc][fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[mc][fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[mc][fg][ij][jk]->SetBinError(bn+1,hist_pt[mc][fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[mc][fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));

    }//bn

    

    hist_pt[mc][fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[mc][fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[mc][fg][ij][jk]->GetXaxis()->CenterTitle();
    hist_pt[mc][fg][ij][jk]->GetXaxis()->SetRangeUser(74,3000.);

    hist_pt[mc][fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb^{-1}GeV^{-1})");
    hist_pt[mc][fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
    hist_pt[mc][fg][ij][jk]->GetYaxis()->CenterTitle();

   }//jk
  }//ij
 }//fg
}//mc

for(int mc=0; mc<nmc; mc++){
 for(int fg=0; fg<nfiles; fg++){
  for(int ij=0; ij<nalgo; ij++){
   for(int jk=0; jk<netarange; jk++){

   hist_radius[mc][fg][ij][jk] = (TH1D*)hist_pt_org[mc][fg][ij][jk]->Clone();
   hist_radius[mc][fg][ij][jk]->Divide(hist_pt_org[mc][fg][ref][jk]) ;

   hist_radius[mc][fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[mc][fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_radius[mc][fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[mc][fg][ij][jk]->GetXaxis()->CenterTitle();
   hist_radius[mc][fg][ij][jk]->GetXaxis()->SetRangeUser(74,3000.);

   hist_radius[mc][fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[mc][fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[mc][fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[mc][fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[mc][fg][ij][jk]->SetMinimum(0);
   hist_radius[mc][fg][ij][jk]->SetMaximum(3.);

   }
  }
 }
}

TCanvas *c2[nmc][nalgo][netarange];

TLegend *leg_pt[nmc][nalgo][netarange];

for(int mc=0; mc<nmc; mc++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

 sprintf(name,"Unf_Tech_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
 c2[mc][ij][jk] = tdrDiCanvas(name,hist_pt[mc][0][ij][jk],hist_pt[mc][1][ij][jk],6,0);

 leg_pt[mc][ij][jk] = tdrLeg(0.6,0.7,0.95,0.95);

 c2[mc][ij][jk]->cd(1);

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

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);

  hist_pt[mc][0][ij][jk]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

      if(fg!=0){
      hist_pt_rat[mc][fg-1][ij][jk] = (TH1D*)hist_pt[mc][fg][ij][jk]->Clone();
      hist_pt_rat[mc][fg-1][ij][jk]->Divide(hist_pt[mc][0][ij][jk]);
      hist_pt_rat[mc][fg-1][ij][jk]->GetYaxis()->SetTitle("Unfolded/Bayesian");
      hist_pt_rat[mc][fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.065);
      hist_pt_rat[mc][fg-1][ij][jk]->GetYaxis()->SetTitleOffset(1.0);
        }

      tdrDraw(hist_pt[mc][fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[mc][ij][jk]->AddEntry(hist_pt[mc][fg][ij][jk],model_name[fg],"l");

    }

 c2[mc][ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

for(int fg=0; fg<(nfiles-1); fg++){

   hist_pt_rat[mc][fg][ij][jk]->SetLineColor(col[fg+1]);
   hist_pt_rat[mc][fg][ij][jk]->SetMinimum(0.8);
   hist_pt_rat[mc][fg][ij][jk]->SetMaximum(1.2);

 if(fg==0) {  hist_pt_rat[mc][fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[mc][fg][ij][jk]->Draw("sames"); }
 }

  line->Draw();

sprintf(name,"Unfolding_Tech_Plots/TUnfold/%s/Pt_Plots/%s.eps",mc_name[mc],c2[mc][ij][jk]->GetName());
c2[mc][ij][jk]->SaveAs(name);

  }//jk
 }//ij
}//mc

TCanvas *c3[nmc][nalgo][netarange];

TLegend *leg_radius[nmc][nalgo][netarange];

for(int mc=0; mc<nmc; mc++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
 
 if((ij<2)&&(jk>6)) continue;

  sprintf(name,"Unf_Tech_Ratio_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[mc][ij][jk] = tdrDiCanvas(name,hist_radius[mc][0][ij][jk],hist_radius[mc][1][ij][jk],6,0);

  leg_radius[mc][ij][jk] = tdrLeg(0.6,0.7,0.95,0.95);

  c3[mc][ij][jk]->cd(1);

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

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[mc][fg-1][ij][jk] = (TH1D*)hist_radius[mc][fg][ij][jk]->Clone();
      hist_radius_rat[mc][fg-1][ij][jk]->Divide(hist_radius[mc][0][ij][jk]);
      hist_radius_rat[mc][fg-1][ij][jk]->GetYaxis()->SetTitle("Unfolded/Bayesian");
      hist_radius_rat[mc][fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.05);

      hist_radius_rat[mc][fg-1][ij][jk]->SetMinimum(0.8);
      hist_radius_rat[mc][fg-1][ij][jk]->SetMaximum(1.2);

        }
      tdrDraw(hist_radius[mc][fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[mc][ij][jk]->AddEntry(hist_radius[mc][fg][ij][jk],model_name[fg],"l");
    }

   c3[mc][ij][jk]->cd(2);

   gPad->SetLogx(1);
   gPad->SetLogy(0);

   for(int fg=0; fg<(nfiles-1); fg++){
   hist_radius_rat[mc][fg][ij][jk]->SetLineColor(col[fg+1]);
   if(fg==0){
         hist_radius_rat[mc][fg][ij][jk]->Draw("e");
   }else{
         hist_radius_rat[mc][fg][ij][jk]->Draw("sames");
        }
   }

  line->Draw();

  sprintf(name,"Unfolding_Tech_Plots/TUnfold/%s/Ratio_Plots/%s.eps",mc_name[mc],c3[mc][ij][jk]->GetName());
  c3[mc][ij][jk]->SaveAs(name);

  }//jk
 }//ij

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int bn=0; bn<noptbins; bn++){

    double ar[nfiles] = {0};
    double bs[nfiles] = {0};

    for(int fg=0; fg<nfiles; fg++){
                ar[fg] = hist_pt[mc][fg][ij][jk]->GetBinContent(bn+1) - hist_pt[mc][0][ij][jk]->GetBinContent(bn+1);
                bs[fg] = hist_radius[mc][fg][ij][jk]->GetBinContent(bn+1) -  hist_radius[mc][0][ij][jk]->GetBinContent(bn+1);
                }

      if(ar[1]*ar[2]>0){
        if(ar[1]>0) { model_pt_up[mc][ij][jk][bn] = (abs(ar[1])>abs(ar[2]))?abs(ar[1]):abs(ar[2]) ; model_pt_dn[mc][ij][jk][bn] = 0.;}
        else { model_pt_dn[mc][ij][jk][bn] = (abs(ar[1])>abs(ar[2]))?abs(ar[1]):abs(ar[2]) ; model_pt_up[mc][ij][jk][bn] = 0.;}
        }
        else{
        if(ar[1]>0) { model_pt_up[mc][ij][jk][bn] = ar[1] ;  model_pt_dn[mc][ij][jk][bn] = abs(ar[2]) ; }
        else { if (ar[2]>0) {  model_pt_up[mc][ij][jk][bn] = ar[2] ;  model_pt_dn[mc][ij][jk][bn] = abs(ar[1]) ; }  }
        }

        if(bs[1]*bs[2]>0){
        if(bs[1]>0) { model_rad_up[mc][ij][jk][bn] = (abs(bs[1])>abs(bs[2]))?abs(bs[1]):abs(bs[2]) ; model_rad_dn[mc][ij][jk][bn] = 0.;}
        else { model_rad_dn[mc][ij][jk][bn] = (abs(bs[1])>abs(bs[2]))?abs(bs[1]):abs(bs[2]) ; model_rad_up[mc][ij][jk][bn] = 0.;}
        }
        else{
        if(bs[1]>0) { model_rad_up[mc][ij][jk][bn] = bs[1] ;  model_rad_dn[mc][ij][jk][bn] = abs(bs[2]) ; }
        else { if (bs[2]>0) {  model_rad_up[mc][ij][jk][bn] = bs[2] ;  model_rad_dn[mc][ij][jk][bn] = abs(bs[1]) ; }  }
        }


        model_pt_up[mc][ij][jk][bn]*=1./max(1.e-6,hist_pt[mc][0][ij][jk]->GetBinContent(bn+1));
		model_pt_dn[mc][ij][jk][bn]*=1./max(1.e-6,hist_pt[mc][0][ij][jk]->GetBinContent(bn+1));

		model_rad_up[mc][ij][jk][bn]*=1./max(1.e-6,hist_radius[mc][0][ij][jk]->GetBinContent(bn+1));
		model_rad_dn[mc][ij][jk][bn]*=1./max(1.e-6,hist_radius[mc][0][ij][jk]->GetBinContent(bn+1));

		model_pt_up[mc][ij][jk][bn] = max(model_pt_up[mc][ij][jk][bn],model_pt_dn[mc][ij][jk][bn]);
		model_pt_dn[mc][ij][jk][bn] = model_pt_up[mc][ij][jk][bn];
		
		model_rad_up[mc][ij][jk][bn] = max(model_rad_up[mc][ij][jk][bn],model_rad_dn[mc][ij][jk][bn]);
		model_rad_dn[mc][ij][jk][bn] = model_rad_up[mc][ij][jk][bn];

		fp_pt[mc]<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<model_pt_up[mc][ij][jk][bn]<<'\t'<<model_pt_dn[mc][ij][jk][bn]<<endl;
		fp_rad[mc]<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<model_rad_up[mc][ij][jk][bn]<<'\t'<<model_rad_dn[mc][ij][jk][bn]<<endl;
   }
  }
 }

	fp_pt[mc].close();
	fp_rad[mc].close();
 }//mc
}

int main()
{
Compare_UnfTech_Var();
}
