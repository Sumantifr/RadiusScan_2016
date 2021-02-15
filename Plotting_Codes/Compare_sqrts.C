#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "TFile.h"
#include <TStyle.h>
#include <TPaveStats.h>
#include <TF1.h>
#include <TPostScript.h>

void Compare_sqrts()
{

static const int nfiles = 2;
const char* filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Rivet/pythia8_mc_7TeV_50to500.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Rivet/pythia8_mc_13TeV_50to500.root"};
int col[3] = {kRed,kBlue};
int sty[3] = {22,23};
const char *sqrts_name[nfiles] = {"#sqrt{s} = 7 TeV","#sqrt{s} = 13 TeV"};

TH1D *h_AK5[nfiles];
TH1D *h_AK7[nfiles];
TH1D *h_rat[nfiles];


char name[1000];

for(int fg=0; fg<nfiles; fg++){
	sprintf(name,"%s",filenames[fg]);
	TFile *filein = new TFile(name,"read");
	
	sprintf(name,"CMS_SMP_19_0xx/d41-x01-y01");
	h_AK5[fg] = (TH1D*)filein->Get(name);
	
	sprintf(name,"CMS_SMP_19_0xx/d61-x01-y01");
	h_AK7[fg] = (TH1D*)filein->Get(name);
	
	h_rat[fg] = (TH1D*)h_AK5[fg]->Clone();
	h_rat[fg]->Divide(h_AK7[fg]);
	
	h_rat[fg]->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
	h_rat[fg]->GetXaxis()->SetTitleSize(0.05);
	h_rat[fg]->GetXaxis()->SetLabelSize(0.05);
	h_rat[fg]->GetXaxis()->CenterTitle();
	h_rat[fg]->GetXaxis()->SetRangeUser(84,400);
	h_rat[fg]->GetXaxis()->SetNoExponent();
	h_rat[fg]->GetXaxis()->SetMoreLogLabels();
	
	h_rat[fg]->GetYaxis()->SetTitle("#sigma (AK5) / #sigma (AK7)");
	h_rat[fg]->GetYaxis()->SetTitleSize(0.05);
	h_rat[fg]->GetYaxis()->SetLabelSize(0.05);
	h_rat[fg]->GetYaxis()->CenterTitle();
	
	h_rat[fg]->SetMinimum(0.395);
	h_rat[fg]->SetMaximum(1.25);
	h_rat[fg]->SetStats(0);
	
	}
	
TCanvas *c1;
TLegend *leg1;
c1 = tdrCanvas("Canv_Compare_sqrts",h_rat[0],2,0);
leg1 = tdrLeg(0.175,0.75,0.375,0.875);
leg1->SetTextFont(42);
c1->cd();
for(int fg=0; fg<nfiles; fg++){

 gPad->SetLogx(1);

 h_rat[fg]->Smooth();
 
 tdrDraw(h_rat[fg],sty[fg],col[fg],1,col[fg],1001,2); leg1->AddEntry(h_rat[fg],sqrts_name[fg],"lp");
 
}

sprintf(name,"Sqrts/%s.pdf",c1->GetName());
c1->SaveAs(name);
}
