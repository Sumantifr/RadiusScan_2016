#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

TString cmsText     = "CMS";
float cmsTextFont   = 61;

float lumiTextSize     = 0.055;
float lumiTextOffset   = 0.2;
float cmsTextSize      = 0.06;
float cmsTextOffset    = 0.1;

TString lumi_13TeV_BCDEFGH = "2016 35.9 fb^{-1} (13 TeV)";


Double_t Loss_Fraction(Double_t* x, Double_t* par)
{
double pt = x[0];	
double C = par[0];
double mu = par[1];
double S = par[2];
double xx = (pt-mu)*1./(sqrt(pt)*S);
return 0.5*C*(1+TMath::Erf(xx));
}

void Compare_TPCor()
{
  // gStyle->SetPadTopMargin(.02); //0.09
 // gStyle->SetPadBottomMargin(0.17);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadRightMargin(0.02);
  
  gStyle->SetStatX(.99);
  gStyle->SetStatY(.99);
  gStyle->SetStatW(.30);
  gStyle->SetStatH(.24);
  gStyle->SetOptStat(1100);
  gStyle->SetOptFit(101);
  gStyle->SetHistLineWidth(2);
  gStyle->SetFuncWidth(3);

  gStyle->SetLabelSize(0.06,"XYZ");
  gStyle->SetTitleSize(0.06,"XYZ");
  gStyle->SetTitleOffset(1.,"X");
  gStyle->SetTitleOffset(1.,"Y");
  gStyle->SetNdivisions(406, "XYZ");
  

TLatex cms_latex;
TLatex cms_lumi;
TLatex eta_tex;

cms_latex.SetNDC();
cms_latex.SetTextFont(cmsTextFont);
cms_latex.SetTextAlign(31);
cms_latex.SetTextSize(cmsTextSize);
cms_latex.SetTextAngle(0);

cms_lumi.SetNDC();
cms_lumi.SetTextFont(42);
cms_lumi.SetTextAlign(31);
cms_lumi.SetTextSize(lumiTextSize);
cms_lumi.SetTextAngle(0);

eta_tex.SetNDC();
eta_tex.SetTextFont(42);
eta_tex.SetTextAlign(31);
eta_tex.SetTextSize(0.05);
eta_tex.SetTextAngle(0);


const int nera = 3;
const int neta = 2;

float C_val[neta][nera] = {{0.134,0.248,0.297},{0.432,0.509,0.721}};
float mu_val[neta][nera] = {{174.5,181.5,185.9},{187.7,198.8,164.0}};
float S_val[neta][nera] = {{10.5,12.8,13.8},{7.0,8.3,8.3}};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

TF1 *func[nera][neta];
char name[100];

int iera;
const char *Run_name[nera] = {"2016BCD","2016EF","2016GH"};

TCanvas *c1[2];
TLegend *leg1[2];

for(int ieta=0; ieta<neta; ieta++){
	for(iera=0; iera<nera; iera++){
		sprintf(name,"Func_Period%i_Eta%i",iera+1,ieta+1);
		func[iera][ieta] = new TF1(name,Loss_Fraction,35,1100,3);
		func[iera][ieta]->SetParameter(0,C_val[ieta][iera]);
		func[iera][ieta]->SetParameter(1,mu_val[ieta][iera]);
		func[iera][ieta]->SetParameter(2,S_val[ieta][iera]);
		
		func[iera][ieta]->GetHistogram()->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
		func[iera][ieta]->GetHistogram()->GetXaxis()->CenterTitle();
		
		func[iera][ieta]->GetHistogram()->GetYaxis()->SetTitle("Fraction of Jets Lost");
		func[iera][ieta]->GetHistogram()->GetYaxis()->CenterTitle();
		
		func[iera][ieta]->GetHistogram()->SetLineColor(1+iera);
		
		func[iera][ieta]->GetHistogram()->SetTitle("");//"ECAL Prefire Fraction");
		
		func[iera][ieta]->GetHistogram()->SetMaximum(1);
	}
}

for(int ieta=0; ieta<neta; ieta++){
	
	sprintf(name,"Canv_LossFraction_Eta%i",ieta+1);
	c1[ieta] = new TCanvas(name,name,50,50,800,600);
	leg1[ieta] = new TLegend(0.7,0.7,0.875,0.875);

	c1[ieta]->SetTopMargin(0.1);
	c1[ieta]->SetBottomMargin(0.15);
	c1[ieta]->SetLeftMargin(0.13);
	
	leg1[ieta]->SetBorderSize(0);
	leg1[ieta]->SetTextFont(42);
	leg1[ieta]->SetTextSize(0.045);
	
	for(iera=0; iera<nera; iera++){
		gPad->SetLogx(1);
		
		func[iera][ieta]->GetHistogram()->GetXaxis()->CenterTitle();
		
		if(iera==0) { func[iera][ieta]->GetHistogram()->Draw("CP");
					}
		else{func[iera][ieta]->GetHistogram()->Draw("sames:CP");}
		
		
		c1[ieta]->Modified();
		
		leg1[ieta]->AddEntry(func[iera][ieta]->GetHistogram(),Run_name[iera],"l");
	}
		leg1[ieta]->Draw();
	
		float l = 0.25;//pad->GetLeftMargin();
		float t = 0.075;//pad->GetTopMargin();
		float r = 0.1;//pad->GetRightMargin();

		cms_latex.DrawLatex(l,1-t-0.15,cmsText);
		cms_lumi.DrawLatex(1-r,1-t,lumi_13TeV_BCDEFGH);
		sprintf(name,"%s",ybinname[ieta+4]);
		eta_tex.DrawLatex(0.45,0.5,name);
	
		sprintf(name,"TP_Cor_Plots/%s.eps",c1[ieta]->GetName());
		c1[ieta]->SaveAs(name);
  }

}

