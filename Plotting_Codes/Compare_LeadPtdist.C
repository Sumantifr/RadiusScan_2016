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


void Compare_LeadPtdist()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 4;

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_files_nocorN_84.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_nocorN.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_nocorN.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50_nocorN.root"};


//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_excornewx2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_newexcor2facx2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50_excor.root"};

/*
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_excor1.root"};
*/
double data_lumi = 1.;

data_lumi = 33.418;//8.762;//8.762;//8.762;//8.762;//8.762;//8.762;//8.762;//27.683;

const int ref = 3;

const char *model_name[nfiles] = {"Data","Herwig++(CUETHS1)","P8(CUETP8M1)","Madgraph"};
const int col[nfiles] = {1,4,6,2};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const char* njetname[3] = {"Leading Jet","2^{nd} Leading Jet","3^{rd} Leading Jet"};

double max_range = 3000.;
double min_range = 84.; 

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange][3];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange][3];
TH1D* hist_pt_org[nfiles][nalgo][netarange][3];

double delta_pt[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

double delta_radius[nfiles-1][nalgo][netarange];

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

TFile *file_out = new TFile("pt_spectra_2016.root","RECREATE");
TH1D *hist_pt_data[nalgo][netarange];

int plotid =  0;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   plotid++;
   if(plotid<10) {sprintf(name,"d0%i-x01-y01",plotid);}
   else { sprintf(name,"d%i-x01-y01",plotid);}
   hist_pt_data[ij][jk] = new TH1D(name,name,noptbins,ptbins);
   hist_pt_data[ij][jk]->Sumw2();
 }
}

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
   for(int nl=0; nl<3; nl++){  

     if(nl==0){
     sprintf(name,"Leading_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
	}
     if(nl==1){
     sprintf(name,"NLeading_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
	}
     if(nl==2){
     sprintf(name,"NNLeading_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
        }

     hist_pt[fg][ij][jk][nl] = (TH1D*)filein->Get(name);
     hist_pt_org[fg][ij][jk][nl] = (TH1D*)hist_pt[fg][ij][jk][nl]->Clone();

//    if(jk==5&&ij==1) { cout<<filenames[fg]<<" "<<hist_pt_org[fg][ij][jk]->GetName()<<" mean "<<hist_pt_org[fg][ij][jk]->GetMean()<<endl;}

     if(fg==0){hist_pt_org[fg][ij][jk][nl]->Scale(1./data_lumi);}

   for(int bn=0; bn<(hist_pt[fg][ij][jk][nl]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk][nl]->SetBinContent(bn+1,hist_pt_org[fg][ij][jk][nl]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk][nl]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk][nl]->SetBinError(bn+1,hist_pt_org[fg][ij][jk][nl]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk][nl]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }

    hist_pt[fg][ij][jk][nl]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk][nl]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk][nl]->GetXaxis()->CenterTitle();    

    hist_pt[fg][ij][jk][nl]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb^{-1}GeV^{-1})");
    hist_pt[fg][ij][jk][nl]->GetYaxis()->SetTitleSize(0.05);  
    hist_pt[fg][ij][jk][nl]->GetYaxis()->CenterTitle();
   
    hist_pt[fg][ij][jk][nl]->GetXaxis()->SetRangeUser(min_range,max_range);
 
   }//nl
  }//jk
 }//ij
}//fg


for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt_org[fg][ij][jk][0]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt_org[fg][ref][jk][0]) ;
   

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

TCanvas *c2[nalgo][netarange][3];

TLegend *leg_pt[nalgo][netarange][3];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
  for(int nl=0; nl<3; nl++){
  
// if((ij!=ialgo)||(jk!=ieta)) continue;

sprintf(name,"Di_Pt_Compare_Canv_%s_EtaBin%i_%iL",JetRad[ij],jk+1,nl+1);
c2[ij][jk][nl] = tdrDiCanvas(name,hist_pt[0][ij][jk][nl],hist_pt[1][ij][jk][nl],6,0);

leg_pt[ij][jk][nl] = tdrLeg(0.5,0.75,0.85,0.95);

c2[ij][jk][nl]->cd(1);

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
  TString text2;
  text2+= njetname[nl];

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.125,text1);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.175,leg_y1+0.05,text2);

//  hist_pt[0][ij][jk]->Scale(1./data_lumi);

 for(int fg=0; fg<nfiles; fg++){

//	hist_pt[fg][ij][jk]->Scale(1./hist_pt[fg][ij][jk]->Integral());

      if(fg!=0){
      if(ij<2&&jk>4) { hist_pt[fg][ij][jk][nl]-> SetMinimum(1.e-3); }
      hist_pt_rat[fg-1][ij][jk][nl] = (TH1D*)hist_pt[fg][ij][jk][nl]->Clone();
      hist_pt_rat[fg-1][ij][jk][nl]->Divide(hist_pt[0][ij][jk][nl]);
      hist_pt_rat[fg-1][ij][jk][nl]->GetYaxis()->SetTitle("MC/Data");
      hist_pt_rat[fg-1][ij][jk][nl]->GetYaxis()->SetTitleSize(0.1);
      hist_pt_rat[fg-1][ij][jk][nl]->GetYaxis()->SetLabelSize(0.075);
      hist_pt_rat[fg-1][ij][jk][nl]->GetYaxis()->SetTitleOffset(0.7);
      hist_pt_rat[fg-1][ij][jk][nl]->GetXaxis()->SetTitleSize(0.115);
      hist_pt_rat[fg-1][ij][jk][nl]->GetXaxis()->SetLabelSize(0.085);
      hist_pt_rat[fg-1][ij][jk][nl]->GetXaxis()->SetTitleOffset(0.9);
//      cout<<model_name[fg]<<" "<<ij<<" "<<jk<<" delta "<<Delta(hist_pt[0][ij][jk],hist_pt[fg][ij][jk])<<endl ;
//      delta_pt[fg-1][ij][jk] = Delta(hist_pt[0][ij][jk],hist_pt[fg][ij][jk]) ;
	}
      tdrDraw(hist_pt[fg][ij][jk][nl],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk][nl]->AddEntry(hist_pt[fg][ij][jk][nl],model_name[fg],"l");
    }

 leg_pt[ij][jk][nl]->SetTextSize(0.04);
 leg_pt[ij][jk][nl]->SetTextFont(42);
  
 c2[ij][jk][nl]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);


for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_pt_rat[fg][ij][jk][nl]->SetLineColor(col[fg+1]);
  hist_pt_rat[fg][ij][jk][nl]->SetMinimum(0.2);
  hist_pt_rat[fg][ij][jk][nl]->SetMaximum(2.0);
  hist_pt_rat[fg][ij][jk][nl]->GetXaxis()->SetRangeUser(min_range,max_range);
if(fg==0) {  hist_pt_rat[fg][ij][jk][nl]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk][nl]->Draw("sames"); }
 }

 line->Draw();

if(nl==0){
sprintf(name,"SingleJetPlots/Leading_Pt_Plots/%s.eps",c2[ij][jk][nl]->GetName());
}
else if(nl==1){
sprintf(name,"SingleJetPlots/NLeading_Pt_Plots/%s.eps",c2[ij][jk][nl]->GetName());
}
else{
sprintf(name,"SingleJetPlots/NNLeading_Pt_Plots/%s.eps",c2[ij][jk][nl]->GetName());
}

c2[ij][jk][nl]->SaveAs(name);

   }//nl
  }//jk
 }//ij


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
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC/Data");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.075);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.7);
      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetTitleSize(0.115);
      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetLabelSize(0.085);
      hist_radius_rat[fg-1][ij][jk]->GetXaxis()->SetTitleOffset(0.9);


      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.2);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(2.0);

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
 
  sprintf(name,"SingleJetPlots/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//jk
 }//ij

file_out->cd();
file_out->Write();
file_out->Close();

}

int main()
{
Compare_LeadPtdist();
}
