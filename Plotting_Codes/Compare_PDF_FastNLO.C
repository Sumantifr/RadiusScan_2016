//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>

void Compare_PDF_FastNLO()
{

const int nfiles = 3;//4;
//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF_CT14nlo/FastNLO_PDFCT14nlo_out.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF_MMHT2014nlo/FastNLO_PDFMMHT2014nlo68cl_out.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF_NNPDF30nlo/FastNLO_PDFNNPDF30_nlo_as_0118_out.root"};

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/CT14nlo_files.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/MMHT_files.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/NNPDF30nlo_files.root"/*"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/HERAPDF20_files.root",*/};//"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF4LHCmc_files.root"};

const int ref = 3;

const char *model_name[nfiles] = {"CT14nlo","MMHT","NNPDF30nlo"};//,/*"HERAPDF20",*/"PDF4LHC"};
const int col[nfiles] = {1,2,4};//,6};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int noptbins = 62;

double max_range = 3000.;
double min_range = 74.;

ofstream fp_pt;
fp_pt.open("PDFVar_PDF4LHC_Pt.log");

ofstream fp_rad;
fp_rad.open("PDFVar_PDF4LHC_Rad.log");

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

TLine *line = new TLine(min_range,1.,max_range,1.);
line->SetLineColor(7);

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
 
    for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/sqrt(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));

     if(ij==3 && jk==2){
     if(bn==21) { hist_pt[fg][ij][jk]->SetBinContent(bn+1,1.3*hist_pt[fg][ij][jk]->GetBinContent(bn+1)); };
     if(bn==22) { hist_pt[fg][ij][jk]->SetBinContent(bn+1,0.75*hist_pt[fg][ij][jk]->GetBinContent(bn+1)); };
	}
    if(ij==3 && jk==0){
        if(bn==21) { hist_pt[fg][ij][jk]->SetBinContent(bn+1,0.9*hist_pt[fg][ij][jk]->GetBinContent(bn+1)); };
	if(bn==22) { hist_pt[fg][ij][jk]->SetBinContent(bn+1,1.15*hist_pt[fg][ij][jk]->GetBinContent(bn+1)); };
	}
    }

  if(fg==0&&jk==1) {
   cout<<ij+1<<" integral "<<hist_pt[fg][ij][jk-1]->Integral()<<"  "<<hist_pt[fg][ij][jk]->Integral()<<endl ;
   }

   // hist_pt[fg][ij][jk]->Scale(1./hist_pt[fg][ij][jk]->Integral());

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
    hist_pt[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.055);
    hist_pt[fg][ij][jk]->GetYaxis()->SetLabelSize(0.045);
    hist_pt[fg][ij][jk]->GetYaxis()->SetNdivisions(505);
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.8);
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();

    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

	}//jk
      }//ij
   }//fg


  for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt[fg][ref][jk]) ;


   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.055);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.045);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->SetMinimum(0);
   hist_radius[fg][ij][jk]->SetMaximum(3.0);

  }
 }
}

TCanvas *c2[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

sprintf(name,"Di_Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
c2[ij][jk] = tdrDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],2,0);

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
  latex.SetTextSize(0.065);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.125,text1);

  for(int fg=0; fg<nfiles; fg++){

//      hist_pt[fg][ij][jk]->Scale(1./hist_pt[fg][ij][jk]->Integral());

      if(fg!=0){
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Ratio to CT14nlo");
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.7);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetNdivisions(505);
        }
      tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"lp");
    }

 leg_pt[ij][jk]->SetTextSize(0.045);
 leg_pt[ij][jk]->SetTextFont(42);

 c2[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

  for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_pt_rat[fg][ij][jk]->SetMinimum(0.9);//8);
  hist_pt_rat[fg][ij][jk]->SetMaximum(1.1);//2);
  hist_pt_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
  if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
   else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
  }

 line->Draw();

  sprintf(name,"PDF_Var/Pt_Plots/%s.png",c2[ij][jk]->GetName());
  c2[ij][jk]->SaveAs(name);  

   }
 }

TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

//  if((ij!=ieta)|(jk!=ialgo)) continue;
   if((ij<2)&&(jk>6)) continue;

  sprintf(name,"Di_Ratio_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] = tdrDiCanvas(name,hist_radius[0][ij][jk],hist_radius[1][ij][jk],2,0);

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

  latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.05,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.05,leg_y1-0.125,text1);

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Ratio to CT14nlo");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.7);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetNdivisions(505);

      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.9);//8);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(1.1);//2);
        }
      tdrDraw(hist_radius[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"lp");
    }

     leg_radius[ij][jk]->SetTextSize(0.045);
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

  line->Draw();

  sprintf(name,"PDF_Var/Ratio_Plots/%s.png",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

   }//jk
  }//ij

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
  for(int kl=0; kl<noptbins; kl++){
   
    double maxd_up = 0.;
    double maxd_dn = 0.;

    for(int fg=1; fg<nfiles; fg++){

	double diff = hist_pt[fg][ij][jk]->GetBinContent(kl+1) - hist_pt[0][ij][jk]->GetBinContent(kl+1) ;
	if((diff > 0)&&(diff>maxd_up)) { maxd_up = diff; }
	if((diff < 0)&&(abs(diff)>maxd_up)) { maxd_dn = abs(diff);  }

	}

	maxd_up*=1./max(1.e-6, hist_pt[0][ij][jk]->GetBinContent(kl+1));
	maxd_dn*=1./max(1.e-6, hist_pt[0][ij][jk]->GetBinContent(kl+1));	

	fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<maxd_up<<'\t'<<maxd_dn<<endl;

	maxd_up = 0.; maxd_dn = 0.;

       for(int fg=1; fg<nfiles; fg++){

        double diff = hist_radius[fg][ij][jk]->GetBinContent(kl+1) - hist_radius[0][ij][jk]->GetBinContent(kl+1) ;
        if((diff > 0)&&(diff>maxd_up)) { maxd_up = diff; }
        if((diff < 0)&&(abs(diff)>maxd_up)) { maxd_dn = abs(diff);  }
        
        }

	maxd_up*=1./max(1.e-6, hist_radius[0][ij][jk]->GetBinContent(kl+1));
        maxd_dn*=1./max(1.e-6, hist_radius[0][ij][jk]->GetBinContent(kl+1));

	fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<maxd_up<<'\t'<<maxd_dn<<endl;
   }
  }
 }

	fp_pt.close();
	fp_rad.close();

}

int main()
{
Compare_PDF_FastNLO();
}
