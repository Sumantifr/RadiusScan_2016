//winclude "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"

const int noptbins = 62 ;
  
double ptbins[noptbins+1] = {/*30, 37, 43, 49, 56, 64,*/ 74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;


void Compare_VChange()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 2;

//const char *filenames[nfiles] = {"RootFiles/CommonBin_ak4_Suman_Legacy_2016All.root","RootFiles/CommonBin_ak4_Suman_23SepV4_2016All.root"};
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/AOD/Legacy_PROOF_2016H_wJEC_METFilter_AOD.root",
				"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/AOD/Legacy_PROOF_2016H_wJEC_METFilter.root"};

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/hist_Legacy_2016_withMETcut.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_nocor.root"};
/*
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root"};
*/
/*
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_excor1.root"};
*/
//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/MET/hist_Legacy_2016_nometcut.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/MET/hist_Legacy_2016_withMETcut.root"};

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/MET/2016B/Legacy_PROOF_2016B_metcut0.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/MET/2016B/Legacy_PROOF_2016B_metcutp3.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/MET/2016B/Legacy_PROOF_2016B_metcutp1.root"};

//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/MET/hist_Legacy_2016_nometcut.root",
//"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/MET/hist_Legacy_2016_withMETcut.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/MET/hist_Legacy_2016_withMETcutp1.root"};

double data_lumi = 1.;

data_lumi = 1;//8.762;//8.762;//8.762;//8.762;//8.762;//8.762;//8.762;//27.683;

const int ref = 3;

const char *model_name[nfiles] = {"2016H (AOD)","2016H (MINIAOD)"};
//const char *model_name[nfiles] = {"Data (Engin)","Data (Suman)"};
//const char *model_name[nfiles] = {"P8 CUETP8M1 (Legacy)","P8 CUETP8M1"};
//const char *model_name[nfiles] = {"no MET/sumEt cut","MET/sumEt < 0.3"};
//const char *model_name[nfiles] = {"no MET/sumEt cut","MET/sumEt < 0.3","MET/sumEt < 0.1"};
const int col[nfiles] = {1,4};

/*
static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;
*/

static const int nalgo = 1 ;
static const int netarange = 5 ;
const char *JetRad[nalgo] = {"ak8"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5};

const char* jetname[nalgo] = {"ak8chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5"} ;

double max_range = 4000.;
double min_range = 74.; 

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

double delta_pt[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

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
cout<<filenames[fg]<<endl;
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
  
   if((fg<1)){ sprintf(name,/*mcjets*/"JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;/*sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[ij],jk+1);*/}
   if((fg>0)) {sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
     hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
     hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

//    if(jk==5&&ij==1) { cout<<filenames[fg]<<" "<<hist_pt_org[fg][ij][jk]->GetName()<<" mean "<<hist_pt_org[fg][ij][jk]->GetMean()<<endl;}

//     if(fg==0){hist_pt_org[fg][ij][jk]->Scale(1./data_lumi);} 
//     if(fg!=0) {hist_pt_org[fg][ij][jk]->Scale(hist_pt_org[0][ij][jk]->Integral()*1./hist_pt_org[fg][ij][jk]->Integral()); }

   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt_org[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt_org[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();    

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);  
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();
   
    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

   if(fg==0){hist_pt_org[fg][ij][jk]->Scale(1./33.6); }
   else {hist_pt_org[fg][ij][jk]->Scale(1./33.6);}

  }//jk


 }//ij
}//fg

/*
for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt_org[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt_org[fg][ref][jk]) ;
   

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->SetMinimum(0);
   hist_radius[fg][ij][jk]->SetMaximum(3.0);

   hist_radius[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

  }
 }
}
*/
TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

// if((ij!=ialgo)||(jk!=ieta)) continue;

sprintf(name,"Di_Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
c2[ij][jk] = tdrDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],0,0);

leg_pt[ij][jk] = tdrLeg(0.5,0.75,0.85,0.95);

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

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.125,text1);

//  hist_pt[0][ij][jk]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

//	hist_pt[fg][ij][jk]->Scale(1./hist_pt[fg][ij][jk]->Integral());

      if(fg!=0){
      if(ij<2&&jk>4) { hist_pt[fg][ij][jk]-> SetMinimum(1.e-3); }
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
      for(int bn=0; bn<(hist_pt_rat[fg-1][ij][jk]->GetNbinsX()); bn++){
	float err = sqrt(1./max(1.e-7,hist_pt[fg][ij][jk]->GetBinContent(bn+1)) + 1./max(1.e-7,hist_pt[0][ij][jk]->GetBinContent(bn+1)));
	err *= hist_pt_rat[fg-1][ij][jk]->GetBinContent(bn+1);
        if(err < hist_pt_rat[fg-1][ij][jk]->GetBinContent(bn+1)){
		hist_pt[fg][ij][jk]->SetBinError(bn+1,err);
		}
	}
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MINIAOD/AOD");
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.075);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.7);
      hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetTitleSize(0.115);
      hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetLabelSize(0.085);
      hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetTitleOffset(0.9);
      cout<<model_name[fg]<<" "<<ij<<" "<<jk<<" delta "<<Delta(hist_pt[0][ij][jk],hist_pt[fg][ij][jk])<<endl ;
      delta_pt[fg-1][ij][jk] = Delta(hist_pt[0][ij][jk],hist_pt[fg][ij][jk]) ;
	}
      tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"l");
    }

 leg_pt[ij][jk]->SetTextSize(0.04);
 leg_pt[ij][jk]->SetTextFont(42);
  
 c2[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);


for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_pt_rat[fg][ij][jk]->SetMinimum(0.825);
  hist_pt_rat[fg][ij][jk]->SetMaximum(1.115);
  hist_pt_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
 }

 line->Draw();

sprintf(name,"Legacy_Cor/AOD_Compare/%s.pdf",c2[ij][jk]->GetName());
c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij
/*

TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

//  if((ij!=ieta)|(jk!=ialgo)) continue;
   if((ij<2)&&(jk>6)) continue;

  sprintf(name,"Di_Ratio_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] = tdrDiCanvas(name,hist_radius[0][ij][jk],hist_radius[1][ij][jk],6,0);

  leg_radius[ij][jk] = tdrLeg(0.5,0.7,0.85,0.95);
 
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

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.125,text1);

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("reReco/Legacy");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.075);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.7);
      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetTitleSize(0.115);
      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetLabelSize(0.085);
      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetTitleOffset(0.9);


      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.5);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(1.5);

      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

      delta_radius[fg-1][ij][jk] = Delta(hist_radius[0][ij][jk],hist_radius[fg][ij][jk]);
      cout<<model_name[fg]<<" "<<ij<<" "<<jk<<" delta "<<delta_radius[fg-1][ij][jk]<<endl; 
        }
      tdrDraw(hist_radius[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"l");
    }

     leg_radius[ij][jk]->SetTextSize(0.04);
     leg_radius[ij][jk]->SetTextFont(42);
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
   }
 
  liney->Draw();
 
  sprintf(name,"Legacy_Cor/Data_Only/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//jk
 }//ij
*/

}

int main()
{
Compare_VChange();
}
