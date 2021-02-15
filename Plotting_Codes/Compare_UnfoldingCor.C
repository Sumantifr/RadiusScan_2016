# include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_UnfoldingCor()
{
const int nfiles = 4;
//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_files_excornewx2_84.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root"};

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_Legacy.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_Legacy.root","/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_Legacy.root"};

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor_excor.root","/home/suman/RooUnfold/Final/Unfolded_2016_Data_NTuple_MC_P8_Legacy_new_excor.root","/home/suman/RooUnfold/Final/Unfolded_2016_Data_NTuple_MC_P8_Legacy_new_excor.root","/home/suman/RooUnfold/Final/Unfolded_2016_Data_NTuple_MC_P8_Legacy_new_excor.root"};

double data_lumi = 33.418;
const int ref = 3;

const char *model_name[nfiles-1] = {"D'Agostini","SVD","Bin by Bin"};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

int col[nfiles] = {1,1,2,4};

double max_range = 3000.;
double min_range = 84.;

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

TLine *line = new TLine(min_range,1.,max_range,1.);
line->SetLineColor(7);

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
  
   if(fg==0) { sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1); }
   else if (fg==1) {sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1);}
   else if (fg==2) {sprintf(name,"svd_unfold_%s_Etabin%i",JetRad[ij],jk+1);}
   else if (fg==3) {sprintf(name,"BbB_unfold_%s_Etabin%i",JetRad[ij],jk+1);}

    hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
    if(fg==0){hist_pt[fg][ij][jk]->Scale(1./data_lumi);}
    cout<<name<<" mean "<<hist_pt[fg][ij][jk]->GetMean()<<endl;
   }
  }
 }

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt[fg][ref][jk]) ;

   }
  }
 } 


TCanvas *c1[nalgo][netarange];
TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];
TLegend *leg_rad[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int fg=0; fg<nfiles; fg++){

   if(fg!=0){
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);

      hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
      hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetTitleSize(0.05);
      hist_pt_rat[fg-1][ij][jk]->GetXaxis()->CenterTitle();

      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Unfolding Correction for Cross Section");
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.04);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->CenterTitle();

      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);

      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetTitleSize(0.035);
      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->CenterTitle();

      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Unfolding Correction for Cross Section Ratio");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.05);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->CenterTitle();
     }//fg!=0
  }//fg

  sprintf(name,"PtCor_%s_EtaBin%i",JetRad[ij],jk+1);
  c1[ij][jk] = tdrCanvas(name,hist_pt_rat[0][ij][jk],6,0);
  
  leg_pt[ij][jk] = tdrLeg(0.55,0.65,0.9,0.9);

  c1[ij][jk]->cd();
  gPad->SetLogx(1);

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

  for(int fg=0; fg<(nfiles-1); fg++){
     hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
     hist_pt_rat[fg][ij][jk]->SetMinimum(0.2);
     hist_pt_rat[fg][ij][jk]->SetMaximum(2.0);
     hist_pt_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

     if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
	 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }

     leg_pt[ij][jk]->AddEntry(hist_pt_rat[fg][ij][jk],model_name[fg],"l");
    }

  leg_pt[ij][jk]->Draw();

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.5,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.4,text1);

  sprintf(name,"Unfolding_Correction/Pt_Plots/%s.png",c1[ij][jk]->GetName());
  c1[ij][jk]->SaveAs(name);

  sprintf(name,"RadCor_%s_EtaBin%i",JetRad[ij],jk+1);
  c2[ij][jk] = tdrCanvas(name,hist_radius_rat[0][ij][jk],6,0);

  leg_rad[ij][jk] = tdrLeg(0.55,0.65,0.9,0.9);

  c2[ij][jk]->cd();
  gPad->SetLogx(1);

  for(int fg=0; fg<(nfiles-1); fg++){
     hist_radius_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
     hist_radius_rat[fg][ij][jk]->SetMinimum(0.2);
     hist_radius_rat[fg][ij][jk]->SetMaximum(2.0);
     hist_radius_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

     if(fg==0) {  hist_radius_rat[fg][ij][jk]->Draw("e"); }
         else { hist_radius_rat[fg][ij][jk]->Draw("sames"); }

    leg_rad[ij][jk]->AddEntry(hist_radius_rat[fg][ij][jk],model_name[fg],"l");
    }

  leg_rad[ij][jk]->Draw();

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.5,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.4,text1);

  sprintf(name,"Unfolding_Correction/Ratio_Plots/%s.png",c2[ij][jk]->GetName());
  c2[ij][jk]->SaveAs(name);

 }//jk
}//ij

}

int main()
{
Compare_UnfoldingCor();
}
