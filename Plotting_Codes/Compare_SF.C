#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Compare_SF()
{
const int nfiles = 1;
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Hist_Pythia_ntuple_OneReso.root"};

const int nvar = 3;
const char *model_name[nvar] = {"JER Nominal","JER Up","JER Down"};
int col[nvar] = {2,6,4};
int sty[nvar] = {1,2,3};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[1000];

TFile *filein;

TH1D *hist_JERSF[nalgo][netarange][nvar];

sprintf(name,"%s",filenames[0]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<nvar; kl++){

	if(kl==0){sprintf(name,"JER_SF_%s_EtaBin%i",JetRad[ij],jk+1);}
	if(kl==1){sprintf(name,"JER_SFup_%s_EtaBin%i",JetRad[ij],jk+1);}
	if(kl==2){sprintf(name,"JER_SFdn_%s_EtaBin%i",JetRad[ij],jk+1);}

	hist_JERSF[ij][jk][kl] = (TH1D*)filein->Get(name);
	if(hist_JERSF[ij][jk][kl]->Integral()>1.e-6){
	hist_JERSF[ij][jk][kl]->Scale(1./hist_JERSF[ij][jk][kl]->Integral());
	}

	hist_JERSF[ij][jk][kl]->GetXaxis()->SetTitle("Additional Smearing");
	hist_JERSF[ij][jk][kl]->GetXaxis()->SetTitleSize(0.05);
	hist_JERSF[ij][jk][kl]->GetXaxis()->SetLabelSize(0.045);
	
	hist_JERSF[ij][jk][kl]->GetYaxis()->SetTitle("A. U.");
        hist_JERSF[ij][jk][kl]->GetYaxis()->SetTitleSize(0.05);
        hist_JERSF[ij][jk][kl]->GetYaxis()->SetLabelSize(0.045);

	hist_JERSF[ij][jk][kl]->SetLineColor(col[kl]);
	hist_JERSF[ij][jk][kl]->SetLineStyle(sty[kl]);

    }
  }
 }

TCanvas *c2[nalgo][netarange];
TLegend *leg2[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

	sprintf(name,"Canv_JERSF_%s_EtaBin%i",JetRad[ij],jk+1);
	c2[ij][jk] = tdrCanvas(name,hist_JERSF[ij][jk][1],6,0);

	leg2[ij][jk] = tdrLeg(0.68,0.65,0.88,0.88);

	c2[ij][jk]->cd();
	gPad->SetLogy(1);

	for(int kl=0; kl<nvar; kl++){
        if(kl==0){ hist_JERSF[ij][jk][kl]->Draw("");    }
        else {hist_JERSF[ij][jk][kl]->Draw("sames");}
	leg2[ij][jk]->AddEntry(hist_JERSF[ij][jk][kl],model_name[kl],"l");
        }

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

  	latex.DrawLatex(0.55,0.35,text);
  	latex.DrawLatex(0.55,0.28,text1);

	leg2[ij][jk]->SetTextFont(42);
	leg2[ij][jk]->SetTextSize(0.045);
	leg2[ij][jk]->Draw();

	sprintf(name,"JERSF_Plots/%s.eps",c2[ij][jk]->GetName());
	c2[ij][jk]->SaveAs(name);

  }
 }

}

int main()
{
Compare_SF();
}
