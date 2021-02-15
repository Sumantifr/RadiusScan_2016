//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>
#include "TF1.h"

double MikkoFunc1(double *x, double *par){
return (par[3]+par[0]*pow(x[0],par[1])+par[2]*log(x[0])/x[0]);
}

double LogLin(double *x, double *par){
return (par[0]+par[1]*log(x[0])/x[0]);
}

void Compare_PHP8_PS()
{

const int nfiles = 9;
//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF_CT14nlo/FastNLO_PDFCT14nlo_out.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF_MMHT2014nlo/FastNLO_PDFMMHT2014nlo68cl_out.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF_NNPDF30nlo/FastNLO_PDFNNPDF30_nlo_as_0118_out.root"};

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PSVar_Files/hist_Powheg_Pythia_CUET_ISR1_FSR1.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PSVar_Files/hist_Powheg_Pythia_CUET_ISR1_FSR2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PSVar_Files/hist_Powheg_Pythia_CUET_ISR1_FSRp5.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PSVar_Files/hist_Powheg_Pythia_CUET_ISR2_FSR1.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PSVar_Files/hist_Powheg_Pythia_CUET_ISRp5_FSR1.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PSVar_Files/hist_Powheg_Pythia_CUET_ISR2_FSR2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PSVar_Files/hist_Powheg_Pythia_CUET_ISRp5_FSRp5.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PSVar_Files/hist_Powheg_Pythia_CUET_ISR2_FSRp5.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PSVar_Files/hist_Powheg_Pythia_CUET_ISRp5_FSR2.root"};

const int ref = 3;

const char *model_name[nfiles] = {"ISR=1 FSR=1","ISR=1 FSR=2","ISR=1 FSR=0.5","ISR=2 FSR=1","ISR=0.5 FSR=1","ISR=2 FSR=2","ISR=0.5 FSR=0.5","ISR=2 FSR=0.5","ISR=0.5 FSR=2"};
const char *model_des[2] = {"ISR = #mu_{R}^{ISR} / (#mu_{R}^{ISR})_{nominal}","FSR = #mu_{R}^{FSR} / (#mu_{R}^{FSR})_{nominal}"};
const int col[nfiles] = {1,2,3,4,6,7,9,kOrange+8,kViolet-8};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int noptbins = 62;

double max_range = 3000.;
double min_range = 74.;

double PS_rad_err_up[nalgo][netarange][noptbins];
double PS_rad_err_dn[nalgo][netarange][noptbins];

TGraph *tg_up[nalgo][netarange];
TGraph *tg_dn[nalgo][netarange];
TF1 *fit_up[nalgo][netarange];
TF1 *fit_dn[nalgo][netarange];

char name[1000];

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	  tg_up[ij][jk] = new TGraph();
	  tg_dn[ij][jk] = new TGraph();
	  sprintf(name,"Fit_%s_EtaBin%i_Up",JetRad[ij],jk+1);
//	  fit_up[ij][jk] = new TF1(name,MikkoFunc1,84,1588,4);
//	  fit_up[ij][jk]->SetParameters(-1,-1,1,1);
	  fit_up[ij][jk] = new TF1(name,LogLin,84,1588,2);
	  fit_up[ij][jk]->SetParameters(1,1);
	  sprintf(name,"Fit_%s_EtaBin%i_Dn",JetRad[ij],jk+1);
	  fit_dn[ij][jk] = new TF1(name,LogLin,84,1588,2);
	  fit_dn[ij][jk]->SetParameters(1,1);
  }
}


ofstream fp_pt;
fp_pt.open("PSVar_PHP8_Pt.log");

ofstream fp_rad;
fp_rad.open("PSVar_PHP8_Rad.log");

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

   sprintf(name,"mcjets/Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
 
    for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }

  if(fg==0&&jk==1) {
   cout<<ij+1<<" integral "<<hist_pt[fg][ij][jk-1]->Integral()<<"  "<<hist_pt[fg][ij][jk]->Integral()<<endl ;
   }

   // hist_pt[fg][ij][jk]->Scale(1./hist_pt[fg][ij][jk]->Integral());

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();
    hist_pt[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();

    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
    hist_pt[fg][ij][jk]->Smooth(2);

	}//jk
      }//ij
   }//fg


  for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt[fg][ref][jk]) ;


   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->SetMinimum(-0.1);
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

leg_pt[ij][jk] = tdrLeg(0.55,0.7,0.875,0.925);
leg_pt[ij][jk]->SetTextSize(0.035);
leg_pt[ij][jk]->SetTextFont(42);

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

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.075,text1);

  TLatex latex1;
  latex1.SetNDC();
  latex1.SetTextAngle(0);
  latex1.SetTextColor(kGreen+3);

  latex1.SetTextFont(62);
  latex1.SetTextAlign(31);
  latex1.SetTextSize(0.045);

  
  latex1.DrawLatex(0.5*(leg_x1+leg_x2)+0.15,leg_y1+0.175,model_des[0]);
  latex1.DrawLatex(0.5*(leg_x1+leg_x2)+0.175,leg_y1+0.1,model_des[1]);

  for(int fg=0; fg<nfiles; fg++){

//      hist_pt[fg][ij][jk]->Scale(1./hist_pt[fg][ij][jk]->Integral());

      if(fg!=0){
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Ratio to Nominal");
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.09);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.8);
        }
      tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"lp");
    }

 leg_pt[ij][jk]->SetTextSize(0.035);

 c2[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);

  for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_pt_rat[fg][ij][jk]->SetMinimum(0.8);
  hist_pt_rat[fg][ij][jk]->SetMaximum(1.2);
  hist_pt_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
  if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("e"); }
   else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }
  }

 line->Draw();

  sprintf(name,"PS_Var/Pt_Plots/%s.png",c2[ij][jk]->GetName());
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

  leg_radius[ij][jk] = tdrLeg(0.5,0.7,0.9,0.925);
  leg_radius[ij][jk]->SetTextSize(0.035);
  leg_radius[ij][jk]->SetTextFont(42);

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

  TLatex latex1;
  latex1.SetNDC();
  latex1.SetTextAngle(0);
  latex1.SetTextColor(kGreen+3);

  latex1.SetTextFont(62);
  latex1.SetTextAlign(31);
  latex1.SetTextSize(0.05);

//  latex1.DrawLatex(0.5*(leg_x1+leg_x2)+0.2,leg_y1+0.125,model_des[0]);
//  latex1.DrawLatex(0.5*(leg_x1+leg_x2)+0.225,leg_y1+0.05,model_des[1]);

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("Ratio to Nominal");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.09);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.8);

      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.8);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(1.2);
        }
      tdrDraw(hist_radius[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"lp");
    }

     leg_radius[ij][jk]->SetTextSize(0.035);
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

  sprintf(name,"PS_Var/Ratio_Plots/%s.png",c3[ij][jk]->GetName());
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
/*
	if(maxd_up<(2*hist_pt[0][ij][jk]->GetBinError(kl+1))) { maxd_up = 1.e-6; }
    if(maxd_dn<(2*hist_pt[0][ij][jk]->GetBinError(kl+1))) { maxd_dn = 1.e-6; }
*/    
    maxd_up -= hist_pt[0][ij][jk]->GetBinError(kl+1);
    maxd_dn -= hist_pt[0][ij][jk]->GetBinError(kl+1);
    if(maxd_up<0) { maxd_up = 1.e-6; }
    if(maxd_dn<0) { maxd_dn = 1.e-6; }

	maxd_up*=1./max(1.e-6, hist_pt[0][ij][jk]->GetBinContent(kl+1));
	maxd_dn*=1./max(1.e-6, hist_pt[0][ij][jk]->GetBinContent(kl+1));	

	fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<maxd_up<<'\t'<<maxd_dn<<endl;

	maxd_up = 0.; maxd_dn = 0.; double max_staterr = 0.;

    max_staterr =  hist_radius[0][ij][jk]->GetBinError(kl+1);

       for(int fg=1; fg<nfiles; fg++){

        double diff = hist_radius[fg][ij][jk]->GetBinContent(kl+1) - hist_radius[0][ij][jk]->GetBinContent(kl+1) ;
        if((diff > 0)&&(diff>maxd_up)) { maxd_up = diff; }
        if((diff < 0)&&(abs(diff)>maxd_dn)) { maxd_dn = abs(diff);  }
        if(hist_radius[fg][ij][jk]->GetBinError(kl+1) > max_staterr) { max_staterr = hist_radius[fg][ij][jk]->GetBinError(kl+1); }
        }

	maxd_up*=1./max(1.e-6, hist_radius[0][ij][jk]->GetBinContent(kl+1));
    maxd_dn*=1./max(1.e-6, hist_radius[0][ij][jk]->GetBinContent(kl+1));

	int nfac = 2;
    if(ij==0) { nfac = 4; }
    /*
	if(maxd_up<(nfac*max_staterr)) { maxd_up = 1.e-6; }
    if(maxd_dn<(nfac*max_staterr)) { maxd_dn = 1.e-6; }
    */
   /* 
    double coreff = hist_radius[0][ij][jk]->GetBinContent(kl+1);
    if(coreff > 1) { coreff = 2.-coreff; }
    max_staterr = pow(hist_pt[0][ij][jk]->GetBinError(kl+1)*1./hist_pt[0][ij][jk]->GetBinContent(kl+1),2) + pow(hist_pt[0][ref][jk]->GetBinError(kl+1)*1./hist_pt[ref][ij][jk]->GetBinContent(kl+1),2) - 2*hist_radius[0][ij][jk]->GetBinContent(kl+1)*(hist_pt[0][ij][jk]->GetBinError(kl+1)*1./hist_pt[0][ij][jk]->GetBinContent(kl+1))*(hist_pt[0][ref][jk]->GetBinError(kl+1)*1./hist_pt[ref][ij][jk]->GetBinContent(kl+1));
    max_staterr = sqrt(max_staterr);
    */
    
 //   maxd_up = maxd_up - max_staterr;
 //   maxd_dn = maxd_dn - max_staterr;
    if(maxd_up<0) { maxd_up = 1.e-6; }
    if(maxd_dn<0) { maxd_dn = 1.e-6; }
    
//    if(ij==1&jk==0){
		tg_up[ij][jk]->SetPoint(kl,hist_radius[0][ij][jk]->GetBinCenter(kl+1),maxd_up);
		tg_dn[ij][jk]->SetPoint(kl,hist_radius[0][ij][jk]->GetBinCenter(kl+1),maxd_dn);
//		}
    
    PS_rad_err_up[ij][jk][kl] = maxd_up;
    PS_rad_err_dn[ij][jk][kl] = maxd_dn;
    
//	fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<maxd_up<<'\t'<<maxd_dn<<endl;
   }
  }
 }

	fp_pt.close();
	
	for(int ij=0; ij<nalgo; ij++){
		for(int jk=0; jk<netarange; jk++){
			tg_up[ij][jk]->Fit(fit_up[ij][jk],"M","",84,700);
			tg_dn[ij][jk]->Fit(fit_dn[ij][jk],"M","",84,700);
		}
	}
	
	
	for(int ij=0; ij<nalgo; ij++){
		for(int jk=0; jk<netarange; jk++){
			for(int kl=0; kl<noptbins; kl++){
				
				double err_up = 0; double err_dn = 0;

				err_up = fit_up[ij][jk]->Eval(hist_radius[0][ij][jk]->GetBinCenter(kl+1));
				err_dn = fit_dn[ij][jk]->Eval(hist_radius[0][ij][jk]->GetBinCenter(kl+1));
				
				if(err_up<0) { err_up = 1.e-6; }
				if(err_dn<0) { err_dn = 1.e-6; }
				
				fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<err_up<<'\t'<<err_dn<<endl;
			}
		}
	}

	fp_rad.close();

TCanvas *c1[nalgo];
for(int ij=0; ij<nalgo; ij++){
	sprintf(name,"FitPS_%s",JetRad[ij]);
	c1[ij] = new TCanvas(name,name,800,600);
	c1[ij]->Divide(2,4);
	for(int jk=0; jk<4; jk++){
	c1[ij]->cd(2*jk+1); gPad->SetLogx(1); tg_up[ij][jk]->SetMarkerStyle(24); tg_up[ij][jk]->SetMaximum(0.05); tg_up[ij][jk]->SetMinimum(0); tg_up[ij][jk]->Draw("AP");
	c1[ij]->cd(2*jk+2); gPad->SetLogx(1); tg_dn[ij][jk]->SetMarkerStyle(24); tg_dn[ij][jk]->SetMaximum(0.05); tg_dn[ij][jk]->SetMinimum(0); tg_dn[ij][jk]->Draw("AP");
		}
	sprintf(name,"PS_Var/Ratio_Plots/%s.png",c1[ij]->GetName());
	c1[ij]->SaveAs(name);	
	}
	
}

int main()
{
Compare_PHP8_PS();
}
