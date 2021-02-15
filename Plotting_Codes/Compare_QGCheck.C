#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "TFile.h"
#include <TStyle.h>
#include <TPaveStats.h>
#include <TF1.h>
#include <TPostScript.h>

void Compare_QGCheck()
{

const int nfiles = 1;
const char* filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/QGCheck/hist_Powheg_Pythia_QGCheck.root"};
int col[3] = {kBlack,kRed,kBlue};
int sty[3] = {kFullCircle,22,23};

TH1D *h_AK5[nfiles];
TH1D *h_AK7[nfiles];
TH1D *h_rat[nfiles];

TH1D *hq_AK5[nfiles];
TH1D *hq_AK7[nfiles];
TH1D *hq_rat[nfiles];

TH1D *hg_AK5[nfiles];
TH1D *hg_AK7[nfiles];
TH1D *hg_rat[nfiles];

char name[1000];

for(int fg=0; fg<nfiles; fg++){
	sprintf(name,"%s",filenames[fg]);
	TFile *filein = new TFile(name,"read");
	
	sprintf(name,"mcjets/Gen_MC_JetpT_ak5_EtaBin1");
	h_AK5[fg] = (TH1D*)filein->Get(name);
	
	sprintf(name,"mcjets/Gen_MC_JetpT_ak7_EtaBin1");
	h_AK7[fg] = (TH1D*)filein->Get(name);
	
	h_rat[fg] = (TH1D*)h_AK5[fg]->Clone();
	h_rat[fg]->Divide(h_AK7[fg]);
	
	sprintf(name,"mcjets/Gen_MC_Quark_JetpT_ak5_EtaBin1");
	hq_AK5[fg] = (TH1D*)filein->Get(name);
	
	sprintf(name,"mcjets/Gen_MC_Quark_JetpT_ak7_EtaBin1");
	hq_AK7[fg] = (TH1D*)filein->Get(name);
	
	hq_rat[fg] = (TH1D*)hq_AK5[fg]->Clone();
	hq_rat[fg]->Divide(hq_AK7[fg]);
	
	sprintf(name,"mcjets/Gen_MC_Gluon_JetpT_ak5_EtaBin1");
	hg_AK5[fg] = (TH1D*)filein->Get(name);
	
	sprintf(name,"mcjets/Gen_MC_Gluon_JetpT_ak7_EtaBin1");
	hg_AK7[fg] = (TH1D*)filein->Get(name);
	
	hg_rat[fg] = (TH1D*)hg_AK5[fg]->Clone();
	hg_rat[fg]->Divide(hg_AK7[fg]);
	
	h_rat[fg]->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
	h_rat[fg]->GetXaxis()->SetTitleSize(0.05);
	h_rat[fg]->GetXaxis()->SetLabelSize(0.05);
	h_rat[fg]->GetXaxis()->CenterTitle();
	h_rat[fg]->GetXaxis()->SetRangeUser(84,1588);
	h_rat[fg]->GetXaxis()->SetNoExponent();
	
	h_rat[fg]->GetYaxis()->SetTitle("#sigma (AK5) / #sigma (AK7)");
	h_rat[fg]->GetYaxis()->SetTitleSize(0.05);
	h_rat[fg]->GetYaxis()->SetLabelSize(0.05);
	h_rat[fg]->GetYaxis()->CenterTitle();
	
	h_rat[fg]->SetMinimum(0.395);
	h_rat[fg]->SetMaximum(1.25);
	h_rat[fg]->SetStats(0);
	
	hq_rat[fg]->GetXaxis()->SetRangeUser(84,1588);
	hg_rat[fg]->GetXaxis()->SetRangeUser(84,1588);
	}
	
TCanvas *c1;
TLegend *leg1;
c1 = tdrCanvas("Canv_Compare_QG_PHP8",h_rat[0],2,0);
leg1 = tdrLeg(0.175,0.75,0.375,0.875);
leg1->SetTextFont(42);
c1->cd();
for(int fg=0; fg<nfiles; fg++){

 gPad->SetLogx(1);

 h_rat[fg]->Smooth();
 hq_rat[fg]->Smooth();
 hg_rat[fg]->Smooth();
 
 tdrDraw(h_rat[fg],sty[0],col[0],1,col[0],1001,2); leg1->AddEntry(h_rat[fg],"All Jets","lp");
 tdrDraw(hq_rat[fg],sty[1],col[1],1,col[1],1001,2); leg1->AddEntry(hq_rat[fg],"Quark Jets","lp");
 tdrDraw(hg_rat[fg],sty[2],col[2],1,col[2],1001,2); leg1->AddEntry(hg_rat[fg],"Gluon Jets","lp");

}

sprintf(name,"QGCheck/%s.pdf",c1->GetName());
c1->SaveAs(name);
}
