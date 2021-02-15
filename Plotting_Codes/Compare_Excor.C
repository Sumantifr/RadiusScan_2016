//winclude "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"


void Compare_Excor()
{

const int nfiles = 4;

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016CFGH_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_excor1.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016CFGH.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root"}; 
/*
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_excor1.root"};
*/
double data_lumi = 2.562+3.127+7.169+8.545;

//data_lumi = 32.882;//8.762;//8.762;//8.762;//8.762;//8.762;//8.762;//8.762;//27.683;

const int ref = 5;

const char *model_name[nfiles] = {"Data_2016+Correction","Pythia8+Correction","Data_2016","Pythia8"};
const int col[nfiles] = {1,4,6,2};

const char *model_var[2] = {"Data","Pythia8_MC"};
const char *model_com[2] = {"W Correction","W/o Correction"};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

double max_range = 3000.;
double min_range = 84.; 

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_rat[2][nalgo][netarange];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

double delta_pt[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[2][nalgo][netarange];

TH1D* hist_pt_corfac[2][nalgo][netarange];
TH1D* hist_radius_corfac[2][nalgo][netarange];

double delta_radius[nfiles-1][nalgo][netarange];

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

TLine *line = new TLine(min_range,1.,max_range,1.);
line->SetLineColor(7);

TLine *liney = new TLine(min_range,1.,max_range,1.);
liney->SetLineColor(7);

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
  
     sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
     hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
     cout<<"file "<<fg+1<<'\t'<<hist_pt[fg][ij][jk]->GetMean()<<endl;
     if(fg==0||fg==2){
     hist_pt[fg][ij][jk]->Scale(1./data_lumi);
     }
     hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();    

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);  
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();
   
    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
 
  }//jk


 }//ij
}//fg


cout<<"pt done\n";

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt_org[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt_org[fg][ref][jk]) ;
   

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK5 Jets");
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->SetMinimum(0);
   hist_radius[fg][ij][jk]->SetMaximum(3.0);

  }
 }
}

cout<<"radius done\n";

TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];
TLegend *leg_pt_rat[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

// if((ij!=ialgo)||(jk!=ieta)) continue;
     for(int fg=0; fg<2; fg++){
      hist_pt_rat[fg][ij][jk] = (TH1D*)hist_pt[2*fg+1][ij][jk]->Clone();
      hist_pt_rat[fg][ij][jk]->Divide(hist_pt[2*fg][ij][jk]);
      hist_pt_rat[fg][ij][jk]->GetYaxis()->SetTitle("MC/Data");
      hist_pt_rat[fg][ij][jk]->GetYaxis()->SetTitleSize(0.045);
      hist_pt_rat[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.8);

      hist_radius_rat[fg][ij][jk] = (TH1D*)hist_radius[2*fg+1][ij][jk]->Clone();
      hist_radius_rat[fg][ij][jk]->Divide(hist_radius[2*fg][ij][jk]);
      hist_radius_rat[fg][ij][jk]->GetYaxis()->SetTitle("MC/Data");
      hist_radius_rat[fg][ij][jk]->GetYaxis()->SetTitleSize(0.045);
      hist_radius_rat[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.8);    
      }
 
   for(int fg=0; fg<2; fg++){
     hist_pt_corfac[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
     hist_pt_corfac[fg][ij][jk]->Divide(hist_pt[fg+2][ij][jk]);
     hist_pt_corfac[fg][ij][jk]->GetYaxis()->SetTitle("Correction for P_{T} Spectra");
     hist_pt_corfac[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
     hist_pt_corfac[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.8);

     hist_radius_corfac[fg][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
     hist_radius_corfac[fg][ij][jk]->Divide(hist_radius[fg+2][ij][jk]);
     hist_radius_corfac[fg][ij][jk]->GetYaxis()->SetTitle("Correction for Xsection Ratio");
     hist_radius_corfac[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
     hist_radius_corfac[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.8);

   }
 }
}


for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

sprintf(name,"Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
c2[ij][jk] = tdrDiCanvas(name,hist_pt_corfac[0][ij][jk],hist_pt_rat[0][ij][jk],6,0);

leg_pt[ij][jk] = tdrLeg(0.6,0.75,0.95,0.95);
leg_pt_rat[ij][jk] = tdrLeg(0.6,0.1,0.95,0.2);

c2[ij][jk]->cd(1);

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

for(int fg=0; fg<2; fg++){
  hist_pt_corfac[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_pt_corfac[fg][ij][jk]->SetMinimum(0.2);
  hist_pt_corfac[fg][ij][jk]->SetMaximum(2.0);
  hist_pt_corfac[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
 /*
if(fg==0) {  hist_pt_corfac[fg][ij][jk]->Draw("e"); }
 else { hist_pt_corfac[fg][ij][jk]->Draw("sames"); }
*/
 tdrDraw(hist_pt_corfac[fg][ij][jk],kFullCircle,col[fg+1],kSolid,col[fg+1] ,1001,2); 
 leg_pt[ij][jk]->AddEntry(hist_pt_corfac[fg][ij][jk],model_var[fg],"l");
 }

 line->Draw();
 //leg_pt[ij][jk]->Draw();

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);

 c2[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

 for(int fg=0; fg<2; fg++){
  hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_pt_rat[fg][ij][jk]->SetMinimum(0.2);
  hist_pt_rat[fg][ij][jk]->SetMaximum(2.0);
  hist_pt_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
 if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
 
 leg_pt_rat[ij][jk]->AddEntry(hist_pt_rat[fg][ij][jk],model_com[fg],"l");
 }

leg_pt_rat[ij][jk]->SetTextSize(0.03);

sprintf(name,"ExtraCor/Pt_Plots/%s.eps",c2[ij][jk]->GetName());
c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij


TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];
TLegend *leg_radius_rat[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

//  if((ij!=ieta)|(jk!=ialgo)) continue;
   if((ij<2)&&(jk>6)) continue;

  sprintf(name,"Ratio_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] = tdrDiCanvas(name,hist_radius_corfac[0][ij][jk],hist_radius_rat[0][ij][jk],6,0);

  leg_radius[ij][jk] = tdrLeg(0.6,0.75,0.95,0.95);
  leg_radius_rat[ij][jk] = tdrLeg(0.6,0.1,0.95,0.2);
 
  c3[ij][jk]->cd(1);
  
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

  for(int fg=0; fg<2; fg++){
  hist_radius_corfac[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_radius_corfac[fg][ij][jk]->SetMinimum(0.2);
  hist_radius_corfac[fg][ij][jk]->SetMaximum(2.0);
  hist_radius_corfac[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
 /*
if(fg==0) {  hist_radius_corfac[fg][ij][jk]->Draw("e"); }
 else { hist_radius_corfac[fg][ij][jk]->Draw("sames"); }
*/
 tdrDraw(hist_radius_corfac[fg][ij][jk],kFullCircle,col[fg+1],kSolid,col[fg+1] ,1001,2);
 leg_radius[ij][jk]->AddEntry(hist_radius_corfac[fg][ij][jk],model_var[fg],"l");
 }
 line->Draw();

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);

 c3[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

 for(int fg=0; fg<2; fg++){
  hist_radius_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_radius_rat[fg][ij][jk]->SetMinimum(0.2);
  hist_radius_rat[fg][ij][jk]->SetMaximum(2.0);
  hist_radius_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
if(fg==0) {  hist_radius_rat[fg][ij][jk]->Draw("e"); }
 else { hist_radius_rat[fg][ij][jk]->Draw("sames"); }

 leg_radius_rat[ij][jk]->AddEntry(hist_radius_rat[fg][ij][jk],model_com[fg],"l");
 }
 
  liney->Draw();
 
  sprintf(name,"ExtraCor/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//jk
 }//ij

}

int main()
{
Compare_Excor();
}
