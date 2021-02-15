//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"

//#define RunEF
#define RunG

void Compare_EffecUnfold()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

int un_model = 2;
un_model-=1;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 2;
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/RootFiles/hist_RecoJetchs_PU_Data_JetHT2016G_JECor.root"/*AJEC/hist_RecoJetchs_PU_Data_JetHT2016EF_CMSSW8X21.root"*/,"/home/suman/RooUnfold/Unfolded_2016_Data.root"};

double data_lumi = 1.;

#ifdef RunG
data_lumi = 7.16;
#elif defined (RunEF)
data_lumi = 7.2;
#endif

const int ref = 4;

const char *model_name[nfiles] = {"Data Before Unfolding","Data After Unfolding"};
const int col[nfiles] = {1,2};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;
const char* unf_model[3] = {"Bayesian","SVD","BinbyBin"};
const char* unf_name[3] = {"bayes","svd","BbB"};

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

double delta_pt[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

double delta_radius[nfiles-1][nalgo][netarange];

TLine *line = new TLine(74,1,6000.,1.);
line->SetLineColor(7);

TLine *liney = new TLine(-5.,1.,5.,1.);
liney->SetLineColor(7);

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
  
   if((fg==0)){ sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;/*sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[ij],jk+1);*/}
   if((fg>0)) {sprintf(name,"%s_unfold_%s_Etabin%i",unf_name[un_model],JetRad[ij],jk+1);}

     hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
     hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();    

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb^{-1}GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);  
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();

//    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(200.,3000.);
    
  }//jk


 }//ij
}//fg


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
   hist_radius[fg][ij][jk]->SetMaximum(3.);

  }
 }
}

TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

// if((ij!=ialgo)||(jk!=ieta)) continue;

sprintf(name,"Di_Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
c2[ij][jk] = tdrDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],4,0);

leg_pt[ij][jk] = tdrLeg(0.6,0.7,0.95,0.95);

c2[ij][jk]->cd(1);

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
  text2+= unf_model[un_model] ;

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);
   latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1,text2);


 for(int fg=0; fg<nfiles; fg++){

      if(fg!=0){
//      hist_pt[fg][ij][jk]->Scale(hist_pt[0][ij][jk]->Integral()*1./hist_pt[fg][ij][jk]->Integral());
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("After/Before");
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.075);
//      cout<<model_name[fg]<<" "<<ij<<" "<<jk<<" delta "<<Delta(hist_pt[0][ij][jk],hist_pt[fg][ij][jk])<<endl ;
      delta_pt[fg-1][ij][jk] = Delta(hist_pt[0][ij][jk],hist_pt[fg][ij][jk]) ;
	}
//      hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(0,2000.);
      tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"l");
    }

 c2[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);


for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_pt_rat[fg][ij][jk]->SetMinimum(0.);
  hist_pt_rat[fg][ij][jk]->SetMaximum(2.);
//  hist_pt_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(0,2000.);
if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
  line->Draw();
 }

sprintf(name,"Pt_Plots_UnfoldEffect/%s.eps",c2[ij][jk]->GetName());
c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij


TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

//  if((ij!=ieta)|(jk!=ialgo)) continue;
   if((ij<2)&&(jk>6)) continue;

  sprintf(name,"Di_Ratio_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] = tdrDiCanvas(name,hist_radius[0][ij][jk],hist_radius[1][ij][jk],4,0);

  leg_radius[ij][jk] = tdrLeg(0.6,0.7,0.95,0.95);
 
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

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);



  cout<<hist_radius[0][ij][jk]->GetName()<<" alive "<<endl;

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("After/Data");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.075);

      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(2.);

      delta_radius[fg-1][ij][jk] = Delta(hist_radius[0][ij][jk],hist_radius[fg][ij][jk]);
      cout<<model_name[fg]<<" "<<ij<<" "<<jk<<" delta "<<delta_radius[fg-1][ij][jk]<<endl; 
        }
      tdrDraw(hist_radius[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"l");
    }
 // leg_radius[ij][jk]->Draw();

   c3[ij][jk]->cd(2);

   gPad->SetLogx(1);
   gPad->SetLogy(0);

   for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
   hist_radius_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
   if(fg==0){
         hist_radius_rat[fg][ij][jk]->Draw("e");
   }else{
         hist_radius_rat[fg][ij][jk]->Draw("sames");
	}
   line->Draw();
   }
  
  sprintf(name,"Ratio_Plots_UnfoldEffect/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//jk
 }//ij

}

int main()
{
Compare_EffecUnfold();
}
