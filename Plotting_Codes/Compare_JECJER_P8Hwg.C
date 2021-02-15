#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "TFile.h"
#include <TStyle.h>
#include <TPaveStats.h>
#include <TF1.h>
#include <TPostScript.h>

double MikkoFunc1(double *x, double *par){
return (par[3]+par[0]*pow(x[0],par[1])+par[2]*log(x[0])/x[0]);	
}

double MikkoFunc2(double *x, double *par){
//return (par[3]+par[0]*pow(x[0],par[1])+par[2]/x[0]);	
//return (par[1]+par[0]*log(x[0])/x[0]);	
 return (par[2]+par[0]*pow(x[0],par[1]));
}

void Compare_JECJER_P8Hwg()
{

const int nalgo = 12;
const char* JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
//const char* JetRad[nalgo] = {"ak4","ak8"};///*,"ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"*/};
const int Etarange = 10;
const char* ybinname[Etarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;
const int col[nalgo] = {1,kRed+2,3,4,6,7,11,kCyan+2,kCyan-1, kBlue-7, kMagenta-7, kRed-5};
const int algo_sty[nalgo] = {2,3,4,5,8,21,22,23,25,26,27,28};
const int lsty[nalgo] = {kSolid,kDashed,kDotted,kSolid,kDashed,kDotted,kSolid,kDashed,kDotted,kSolid,kDashed,kDotted,};

const int noptbins = 62;

const int refrad = 3;

TH1D *hist_pt[nalgo][Etarange];
TH1D *hist_radius[nalgo][Etarange];

char name[100];

TFile *file0 = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_JER_nocor.root","read");

for(int ij=0; ij<nalgo; ij++){
	for(int jk=0; jk<Etarange; jk++){
		
		sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
		hist_pt[ij][jk] = (TH1D*)file0->Get(name);
		
	}
}

for(int ij=0; ij<nalgo; ij++){
	for(int jk=0; jk<Etarange; jk++){
	hist_radius[ij][jk] = (TH1D*)hist_pt[ij][jk]->Clone();
	hist_radius[ij][jk]->Divide(hist_pt[refrad][jk]);
	}
}

const int nfiles = 2;
const char *filenames[nfiles]={
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/JEC_Output_P8.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/JEC_Output_Hwg.root"
	};

TH1D *Reso_pt[nalgo][Etarange][nfiles];
TH1D *excor_pt[nalgo][Etarange][nfiles];

TH1D *Rat_Reso_pt[nalgo][Etarange];
TH1D *Rat_excor_pt[nalgo][Etarange];
TH1D *DoubleRat_excor_pt[nalgo][Etarange];

for(int fg=0; fg<nfiles; fg++){
	for(int ij=0; ij<nalgo; ij++){
		for(int jk=0; jk<Etarange; jk++){

		sprintf(name,"%s",filenames[fg]);
		TFile *filein = new TFile(name,"read");

		sprintf(name,"Resolution_pt_%s_EtaBin%i",JetRad[ij],jk+1);
		Reso_pt[ij][jk][fg] = (TH1D*)filein->Get(name);

		sprintf(name,"ExCor_pt_%s_EtaBin%i",JetRad[ij],jk+1);
		excor_pt[ij][jk][fg] = (TH1D*)filein->Get(name);
//		excor_pt[ij][jk][fg]->Sumw2(1);
		}
	}
}

for(int jk=0; jk<Etarange; jk++){
	for(int ij=0; ij<nalgo; ij++){
		
		Rat_Reso_pt[ij][jk] = (TH1D*)Reso_pt[ij][jk][1]->Clone();
		Rat_Reso_pt[ij][jk]->Sumw2(1);
		Rat_Reso_pt[ij][jk]->Divide(Reso_pt[ij][jk][0]);
		
		Rat_excor_pt[ij][jk] = (TH1D*)excor_pt[ij][jk][1]->Clone();
		Rat_excor_pt[ij][jk]->Sumw2(1);
		Rat_excor_pt[ij][jk]->Divide(excor_pt[ij][jk][0]);
		/*
		if(ij==7&&jk==2){
			for(int bn=0; bn<(Rat_excor_pt[ij][jk]->GetNbinsX()); bn++){
				cout<<"P8 err "<<excor_pt[ij][jk][0]->GetBinError(bn+1)<<" Hwg error "<<excor_pt[ij][jk][1]->GetBinError(bn+1)<<" ratio error "<<Rat_excor_pt[ij][jk]->GetBinError(bn+1)<<endl;
				}
			}
		*/
		}
		
		for(int ij=0; ij<nalgo; ij++){
			
			TH1D *h1 = (TH1D*)excor_pt[ij][jk][0]->Clone();
			h1->Divide(excor_pt[refrad][jk][0]);
			
			double correlation = 1;
			
			for(int bn=0; bn<(h1->GetNbinsX()); bn++){
				
				if(ij<refrad) { correlation = hist_radius[ij][jk]->GetBinContent(bn+1); }
				if(ij>refrad) { correlation = 2.- hist_radius[ij][jk]->GetBinContent(bn+1); }
				correlation *= 0.5;
			
				double err1 = (excor_pt[ij][jk][0]->GetBinError(bn+1)) *1./(excor_pt[ij][jk][0]->GetBinContent(bn+1));
				double err2 = (excor_pt[refrad][jk][0]->GetBinError(bn+1)) *1./(excor_pt[refrad][jk][0]->GetBinContent(bn+1));
				double errf = h1->GetBinContent(bn+1) * sqrt(fabs(err1*err1 + err2*err2 -2*correlation*err1*err2)) ;
				if(ij==3) { errf = 1.e-6; }
				if(isnan(errf)) continue;
				h1->SetBinError(bn+1,errf);
				}
			
			TH1D *h2 = (TH1D*)excor_pt[ij][jk][1]->Clone();
			h2->Divide(excor_pt[refrad][jk][1]);
			for(int bn=0; bn<(h2->GetNbinsX()); bn++){
				
				if(ij<refrad) { correlation = hist_radius[ij][jk]->GetBinContent(bn+1); }
				if(ij>refrad) { correlation = 2.- hist_radius[ij][jk]->GetBinContent(bn+1); }
				correlation *= 0.5;
			
				double err1 = (excor_pt[ij][jk][1]->GetBinError(bn+1)) *1./(excor_pt[ij][jk][1]->GetBinContent(bn+1));
				double err2 = (excor_pt[refrad][jk][1]->GetBinError(bn+1)) *1./(excor_pt[refrad][jk][1]->GetBinContent(bn+1));
				double errf = h2->GetBinContent(bn+1) * sqrt(fabs(err1*err1 + err2*err2 -2*correlation*err1*err2)) ;
				if(ij==3) { errf = 1.e-6; }
				if(isnan(errf)) continue;
				h2->SetBinError(bn+1,errf);
				}
			
			DoubleRat_excor_pt[ij][jk] = (TH1D*)h2->Clone();
			DoubleRat_excor_pt[ij][jk]->Divide(h1);
			
	}
}

TF1 *FitFunc_excor[nalgo][Etarange];
TF1 *FitFunc_doublecor[nalgo][Etarange];

double uplim[Etarange] = {3000,3000,2200,1700,1200,800};
for(int jk=0; jk<Etarange; jk++){
	
	for(int ij=0; ij<nalgo; ij++){
	sprintf(name,"Fit_Func_%s_EtaBin%i",JetRad[ij],jk+1);
	FitFunc_excor[ij][jk] = new TF1(name,MikkoFunc1,74,uplim[jk],4);
	if(ij>5){
	FitFunc_excor[ij][jk]->SetParameters(-1,-1,1,1);
	}else{
		  FitFunc_excor[ij][jk]->SetParameters(-1,-0.2,0.5,1);
		 }	
			   FitFunc_excor[ij][jk]->SetParLimits(3,0.995,1.005);		
//			   FitFunc_excor[ij][jk]->SetParLimits(1,-100,0);
			   
			   if(ij!=11){
				   FitFunc_excor[ij][jk]->SetParLimits(0,-100,100);
				   }
			  
	Rat_excor_pt[ij][jk]->Fit(FitFunc_excor[ij][jk],"MR");
	}
	
	
	for(int ij=0; ij<nalgo; ij++){
	sprintf(name,"Fit_Func_DoubleRatio_%s_EtaBin%i",JetRad[ij],jk+1);
	/*
	FitFunc_doublecor[ij][jk] = new TF1(name,MikkoFunc1,74,uplim[jk],4);
	if(ij>5){
	FitFunc_doublecor[ij][jk]->SetParameters(-1,-1,0,1);
//	FitFunc_doublecor[ij][jk]->SetParLimits(1,-100,0);
	}else{
		  FitFunc_doublecor[ij][jk]->SetParameters(-1,-0.2,0,1);
		 }
	FitFunc_doublecor[ij][jk]->FixParameter(3,1);

//	FitFunc_doublecor[ij][jk]->SetParLimits(3,0.999,1.001);
	FitFunc_doublecor[ij][jk]->SetParLimits(1,-1,0);
//	if(ij!=11){
	FitFunc_doublecor[ij][jk]->SetParLimits(0,-20,20.);
//	}
	
	DoubleRat_excor_pt[ij][jk]->Fit(FitFunc_doublecor[ij][jk],"MR");
	*/ 
	
	FitFunc_doublecor[ij][jk] = new TF1(name,MikkoFunc1,74,uplim[jk],4);
	if(ij>6){
	FitFunc_doublecor[ij][jk]->SetParameters(-1,-1,-1,1);
//	FitFunc_doublecor[ij][jk]->SetParLimits(1,-100,0);
	}else{
		  FitFunc_doublecor[ij][jk]->SetParameters(-1,-0.2,-1,1);
		 }
//	}
	
	FitFunc_doublecor[ij][jk]->SetParLimits(3,0.995,1.005);
	FitFunc_doublecor[ij][jk]->SetParLimits(1,-1,0);
	
	DoubleRat_excor_pt[ij][jk]->Fit(FitFunc_doublecor[ij][jk],"MR");
	
	}
}

TCanvas *Canv_JECRat[Etarange];
TCanvas *Canv_JEC_doubleRat[Etarange];
TCanvas *Canv_JERRat[Etarange];

TLegend *leg_JECRat[Etarange];
TLegend *leg_JEC_doubleRat[Etarange];
TLegend *leg_JERRat[Etarange];

gStyle->SetOptLogx(1);

TLatex latex;
latex.SetNDC();
latex.SetTextAngle(0);
latex.SetTextColor(kBlack);

latex.SetTextFont(42);
latex.SetTextAlign(31);
latex.SetTextSize(0.065);

for(int jk=0; jk<Etarange; jk++){
	
	sprintf(name,"ExCor_Ratio_P8Hwg_EtaBin%i",jk+1);
	Canv_JECRat[jk] = tdrCanvas(name,Rat_excor_pt[0][jk],7,0);
	leg_JECRat[jk] = tdrLeg(0.65,0.2,0.875,0.475);
	leg_JECRat[jk]->SetNColumns(2);
	
	TString text1;
    text1+=  ybinname[jk];
    	
	for(int ij=0; ij<nalgo; ij++){
		
		Rat_excor_pt[ij][jk]->GetXaxis()->SetRangeUser(74,2500);
		
		Rat_excor_pt[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
		Rat_excor_pt[ij][jk]->GetXaxis()->SetTitleSize(0.06);
		Rat_excor_pt[ij][jk]->GetXaxis()->SetLabelSize(0.06);
		Rat_excor_pt[ij][jk]->GetXaxis()->CenterTitle();
		
		Rat_excor_pt[ij][jk]->GetYaxis()->SetTitle("Correction in Hwg++ / Correction in P8");
		Rat_excor_pt[ij][jk]->GetYaxis()->SetTitleSize(0.05);
		Rat_excor_pt[ij][jk]->GetYaxis()->SetLabelSize(0.06);
		Rat_excor_pt[ij][jk]->GetYaxis()->SetTitleOffset(1.4);
		Rat_excor_pt[ij][jk]->GetYaxis()->CenterTitle();
		Rat_excor_pt[ij][jk]->GetYaxis()->SetNdivisions(406);
		
		Rat_excor_pt[ij][jk]->SetMinimum(0.95);
		Rat_excor_pt[ij][jk]->SetMaximum(1.01);
		
		gPad->SetLogx(1);
		
		tdrDraw(Rat_excor_pt[ij][jk],algo_sty[ij],col[ij],lsty[ij],col[ij],1001,2);
		leg_JECRat[jk]->AddEntry(Rat_excor_pt[ij][jk],JetRad[ij],"p");
		}
		
		latex.DrawLatex(0.65,0.85,text1);
		
	    sprintf(name,"Ratio_JECJER/%s.eps",Canv_JECRat[jk]->GetName());
	    Canv_JECRat[jk]->SaveAs(name);
	    
	sprintf(name,"Resolution_Ratio_P8Hwg_EtaBin%i",jk+1);
	Canv_JERRat[jk] = tdrCanvas(name,Rat_Reso_pt[0][jk],7,0);
	leg_JERRat[jk] = tdrLeg(0.65,0.625,0.875,0.875);
	leg_JERRat[jk]->SetNColumns(2);
    	
	for(int ij=0; ij<nalgo; ij++){
		
		Rat_Reso_pt[ij][jk]->GetXaxis()->SetRangeUser(74,2500);
		
		Rat_Reso_pt[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
		Rat_Reso_pt[ij][jk]->GetXaxis()->SetTitleSize(0.06);
		Rat_Reso_pt[ij][jk]->GetXaxis()->SetLabelSize(0.06);
		Rat_Reso_pt[ij][jk]->GetXaxis()->CenterTitle();
		
		Rat_Reso_pt[ij][jk]->GetYaxis()->SetTitle("Resolution in Hwg++ / Resolution in P8");
		Rat_Reso_pt[ij][jk]->GetYaxis()->SetTitleSize(0.05);
		Rat_Reso_pt[ij][jk]->GetYaxis()->SetLabelSize(0.06);
		Rat_Reso_pt[ij][jk]->GetYaxis()->SetTitleOffset(1.3);
		Rat_Reso_pt[ij][jk]->GetYaxis()->CenterTitle();
		
		Rat_Reso_pt[ij][jk]->SetMinimum(0.95);
		Rat_Reso_pt[ij][jk]->SetMaximum(1.4);
		
		gPad->SetLogx(1);
		tdrDraw(Rat_Reso_pt[ij][jk],algo_sty[ij],col[ij],lsty[ij],col[ij],1001,2);
		leg_JERRat[jk]->AddEntry(Rat_excor_pt[ij][jk],JetRad[ij],"p");
		}
	
	    latex.DrawLatex(0.65,0.85,text1);
	
	    sprintf(name,"Ratio_JECJER/%s.eps",Canv_JERRat[jk]->GetName());
	    Canv_JERRat[jk]->SaveAs(name);   
	    
		sprintf(name,"ExCor_DoubleRatio_P8Hwg_EtaBin%i",jk+1);
		Canv_JEC_doubleRat[jk] = tdrCanvas(name,DoubleRat_excor_pt[11][jk],7,0);
		leg_JEC_doubleRat[jk] = tdrLeg(0.65,0.2,0.875,0.475);
		leg_JEC_doubleRat[jk]->SetNColumns(2);
    
		Canv_JEC_doubleRat[jk]->cd();
    	
		for(int ij=0; ij<nalgo; ij++){
			
			DoubleRat_excor_pt[ij][jk]->GetXaxis()->SetRangeUser(74,2500);
		
			DoubleRat_excor_pt[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
			DoubleRat_excor_pt[ij][jk]->GetXaxis()->SetTitleSize(0.06);
			DoubleRat_excor_pt[ij][jk]->GetXaxis()->SetLabelSize(0.06);
			DoubleRat_excor_pt[ij][jk]->GetXaxis()->CenterTitle();
		
			sprintf(name,"C(AK%i)/C(AK4) in Hwg++ / C(AK%i)/C(AK4) in P8",ij+1,ij+1);
			DoubleRat_excor_pt[ij][jk]->GetYaxis()->SetTitle(name);
			DoubleRat_excor_pt[ij][jk]->GetYaxis()->SetTitleSize(0.045);
			DoubleRat_excor_pt[ij][jk]->GetYaxis()->SetLabelSize(0.045);
			DoubleRat_excor_pt[ij][jk]->GetYaxis()->CenterTitle();
			DoubleRat_excor_pt[ij][jk]->GetYaxis()->SetTitleOffset(1.5);
		
			DoubleRat_excor_pt[ij][jk]->SetMinimum(0.95);
			DoubleRat_excor_pt[ij][jk]->SetMaximum(1.01);
		
			gPad->SetLogx(1);
			gPad->SetLogy(0);
		
			tdrDraw(DoubleRat_excor_pt[ij][jk],algo_sty[ij],col[ij],lsty[ij],col[ij],1001,2);
			leg_JEC_doubleRat[jk]->AddEntry(DoubleRat_excor_pt[ij][jk],JetRad[ij],"p");
		}
	
		latex.DrawLatex(0.65,0.85,text1);
	
	    sprintf(name,"Ratio_JECJER/%s.eps",Canv_JEC_doubleRat[jk]->GetName());
	    Canv_JEC_doubleRat[jk]->SaveAs(name);       
	}
	
	
	TCanvas *Canv_JEC_Rat_allRad[nalgo];
	TLegend *leg_JEC_Rat_allRad[nalgo];
	
	TPostScript *ps_rat = new TPostScript("ExCorRatio_Plots.ps", 111);
    ps_rat->Range(18,24);
    
	for(int ij=0; ij<nalgo; ij++){
		
		ps_rat->NewPage();
		sprintf(name,"ExCor_Ratio_P8Hwg_%s",JetRad[ij]);
		Canv_JEC_Rat_allRad[ij] = new TCanvas(name,name,50,50,600,800);
		Canv_JEC_Rat_allRad[ij]->Divide(2,3);
		
		for(int jk=0; jk<Etarange; jk++){
			
			if(jk>5) break;
			
				Canv_JEC_Rat_allRad[ij]->cd(jk+1);
				TString text1;
				text1+=  ybinname[jk];
				TString text2;
				text2+=  JetRad[ij];
			
				gPad->SetLogx(1);
				gPad->SetLogy(0);
				
				tdrDraw(Rat_excor_pt[ij][jk],algo_sty[ij],col[ij],lsty[ij],col[ij],1001,2);
				
				gPad->Modified(); gPad->Update();
				
				TPaveStats *st = (TPaveStats*)Rat_excor_pt[ij][jk]->FindObject("stats");
			
				st->SetX1NDC(0.575);
				st->SetX2NDC(0.95);
				st->SetY1NDC(0.2);
				st->SetY2NDC(0.6);
		
				st->Draw();
				gPad->Modified(); gPad->Update();
			
				latex.DrawLatex(0.55,0.45,text2);
				latex.DrawLatex(0.55,0.35,text1);
			
			}
			Canv_JEC_Rat_allRad[ij]->Update();
			sprintf(name,"Ratio_JECJER/%s.eps",Canv_JEC_Rat_allRad[ij]->GetName());
			Canv_JEC_Rat_allRad[ij]->SaveAs(name);
	}
	
	ps_rat->Close();
	
	TCanvas *Canv_JEC_doubleRat_allRad[nalgo];
	TLegend *leg_JEC_doubleRat_allRad[nalgo];
	
	TPostScript *ps_drat = new TPostScript("DoubleRatio_Plots.ps", 111);
    ps_drat->Range(18,24);

		for(int ij=0; ij<nalgo; ij++){
			
			ps_drat->NewPage();
			sprintf(name,"ExCor_DoubleRatio_P8Hwg_%s",JetRad[ij]);
			Canv_JEC_doubleRat_allRad[ij] = new TCanvas(name,name,50,50,600,800);//tdrCanvas(name,DoubleRat_excor_pt[11][0],7,0);
			Canv_JEC_doubleRat_allRad[ij]->Divide(2,3);
			
			for(int jk=0; jk<Etarange; jk++){	
				
				if(jk>5) break;
				
				Canv_JEC_doubleRat_allRad[ij]->cd(jk+1);
				TString text1;
				text1+=  ybinname[jk];
				TString text2;
				text2+=  JetRad[ij];
			
				gPad->SetLogx(1);
				gPad->SetLogy(0);
		
				tdrDraw(DoubleRat_excor_pt[ij][jk],algo_sty[ij],col[ij],lsty[ij],col[ij],1001,2);
			
				gPad->Modified(); gPad->Update();
			
				TPaveStats *st = (TPaveStats*)DoubleRat_excor_pt[ij][jk]->FindObject("stats");
						
				st->SetX1NDC(0.575);
				st->SetX2NDC(0.95);
				st->SetY1NDC(0.2);
				st->SetY2NDC(0.6);
		
				st->Draw();
				gPad->Modified(); gPad->Update();
			
				latex.DrawLatex(0.55,0.45,text2);
				latex.DrawLatex(0.55,0.35,text1);
			
			}
			Canv_JEC_doubleRat_allRad[ij]->Update();
			sprintf(name,"Ratio_JECJER/%s.eps",Canv_JEC_doubleRat_allRad[ij]->GetName());
			Canv_JEC_doubleRat_allRad[ij]->SaveAs(name);
			
			}
			
	ps_drat->Close();
	
	/*
	  for(int jk=0; jk<6; jk++){
		  cout<<"{";
		  for(int ij=0; ij<nalgo; ij++){
			   cout<<"{";
			   for(int bn=0; bn<(Rat_Reso_pt[ij][jk]->GetNbinsX()); bn++){
				   cout<<Rat_Reso_pt[ij][jk]->GetBinContent(bn+1);
				   if(bn<(Rat_Reso_pt[ij][jk]->GetNbinsX()-1)){cout<<",";}
				   }
			   cout<<"}";
			   if(ij<(nalgo-1)) { cout<<","<<endl; }
			  }
			  if(jk<5){
			  cout<<"},"<<endl;
				}else{
					 cout<<"}"<<endl;
					 }
			  
		  }
*/ 

ofstream fp_pt;
fp_pt.open("P8Hwg_Unc_Pt.log");

ofstream fp_rad;
fp_rad.open("P8Hwg_Unc_Rad.log");

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etarange; jk++){
	for(int pt=0; pt<noptbins; pt++){
	fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<fabs(1-FitFunc_excor[ij][jk]->Eval(Rat_excor_pt[ij][jk]->GetBinCenter(pt+1)))<<'\t'<<fabs(1-FitFunc_excor[ij][jk]->Eval(Rat_excor_pt[ij][jk]->GetBinCenter(pt+1)))<<endl;
	fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<pt+1<<'\t'<<fabs(1-FitFunc_doublecor[ij][jk]->Eval(DoubleRat_excor_pt[ij][jk]->GetBinCenter(pt+1)))<<'\t'<<fabs(1-FitFunc_doublecor[ij][jk]->Eval(DoubleRat_excor_pt[ij][jk]->GetBinCenter(pt+1)))<<endl;
	}
  }
}


}
