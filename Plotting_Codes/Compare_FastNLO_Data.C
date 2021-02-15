//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_FastNLO_Data()
{
cout<<"hi"<<endl;

int ialgo = 6;
int ieta = 1;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
//ieta-=1;

const int nfiles = 7;
const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Summer_Files/Pythia_Summer16_CMSSW8X21_Run2_v2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/Summer2016_8X21/Madgraph2016Summer_Run2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/Summer2016_8X21/hist_Herwigpp_Summer16_Run2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_Pythia_Userhook2_NNPDF30.root"/*hist_Powheg_Pythia_paolo_22.root*/,"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/hist_Powheg_Herwig_NNPDF30.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/AK6_Eta1_Summary_Table.root"};

const int ref = 4;

const char *model_name[nfiles] = {"Data2016G","Pythia","Madgraph","Herwigpp","Powheg_Pythia","Powheg_Herwig","FastNLO"};
const int col[nfiles] = {1,5,2,4,3,9,12};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_y[nfiles][nalgo];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_y_rat[nfiles-1][nalgo];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

TLine *line = new TLine(74,1,6000.,1.);
line->SetLineColor(7);


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

   if(ij!=ialgo) continue ;
   if(ieta==1 && jk>=4) continue ; 
   if(ieta==2 && jk<4) continue ; 
   if(fg==0) { sprintf(name,"svd_unfold_%s_Etabin%i",JetRad[ij],jk+1) ; } 
   if(fg<4&&fg>0){ sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1); }
   if((fg>3)&&(fg<(nfiles-1))) {sprintf(name,"mcjets/Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
   if(fg==(nfiles-1)) { sprintf(name,"JetpT_%s_EtaBin%i_NLO",JetRad[ij],jk+1); }
    hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
    hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

   // if(fg==(nfiles-1)) {hist_pt[fg][ij][jk]->Sumw2();  }

   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk]))); 
    }
/*
    if(fg==(nfiles-1)){
        for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
                hist_pt[fg][ij][jk]->SetBinError(bn+1,0.);
        }
    }
*/

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
//    hist_pt[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05); 
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();    
    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(100.,3000.);        

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy (fb^{-1}GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);  
//    hist_pt[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();
    
  }//jk
 }//ij
}//fg

/*
for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   if((ij!=ialgo)||(jk!=ieta)) continue ;

   cout<<ij<<" "<<jk<<" radius mean "<<<<endl;

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
*/
TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

  if(ij!=ialgo) continue ;
   if(ieta==1 && jk>=4) continue ; 
   if(ieta==2 && jk<4) continue ; 

sprintf(name,"Di_Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
c2[ij][jk] = tdrDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],4,0);

leg_pt[ij][jk] = tdrLeg(0.6,0.7,0.95,0.95);

//c2[ij][jk]->Draw();
//c2[ij][jk]->Divide(1,3);
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

 // cout<<0.5*(leg_x1+leg_x2)<<endl;

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);


 hist_pt[0][ij][jk]->Scale(1./7.613);

 for(int fg=0; fg<nfiles; fg++){
  //  hist_pt[fg][ij][jk]->Draw("SAME");
      if(fg!=0){
      if(fg>3){
      hist_pt[fg][ij][jk]->Scale(hist_pt[0][ij][jk]->Integral()*1./hist_pt[fg][ij][jk]->Integral());
	}
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("GEN/Unfolded");
	}
      
    if(fg==(nfiles-1)){
        for(int bn=0; bn<(hist_pt_rat[fg][ij][jk]->GetNbinsX()); bn++){
               hist_pt_rat[fg-1][ij][jk]->SetBinError(bn+1,0.);
        }
    }     

      tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"l");
    }
  //leg_pt[ij][jk]->Draw();

 c2[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_pt_rat[fg][ij][jk]->SetMinimum(0.);
  hist_pt_rat[fg][ij][jk]->SetMaximum(3.);
if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
  line->Draw();
 }

sprintf(name,"ZFastNLO_Data_Pt_Plots/%s.eps",c2[ij][jk]->GetName());
c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij

/*
TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   if((ij!=ialgo)||(jk!=ieta)) continue ;
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

 // cout<<0.5*(leg_x1+leg_x2)<<endl;

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.1,text1);


  cout<<hist_radius[0][ij][jk]->GetName()<<" alive "<<endl;

  for(int fg=0; fg<nfiles; fg++){
  //  hist_pt[fg][ij][jk]->Draw("SAME");
      if(fg!=0){
    //  hist_rat[fg][ij][jk]->Scale(hist_rat[0][ij][jk]->Integral()*1./hist_rat[fg][ij][jk]->Integral());
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC/CUETP8M1");

      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(2.);

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
  
  sprintf(name,"ZFastNLO_Gen_Pt_Plots/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//jk
 }//ij
*/
}

int main()
{
Compare_FastNLO_Data();
}
