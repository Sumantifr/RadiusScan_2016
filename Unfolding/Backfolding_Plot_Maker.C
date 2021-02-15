#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

void Backfolding_Plot_Maker()
{
const int nfiles = 1;
const char *filenames[nfiles] = {"Unfolded_2016_Data.root"};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int unf_par = 3;
const char* unf_name[unf_par] = {"Bayes","SVD","BinbyBin"};
int unf_col[unf_par] = {3,2,4};
const char* unf_goodname[unf_par] = {"Bayesian","SVD","BinbyBin"};

const char* eff[2]={"Without Efficiency Correction","With  Efficiency Correction"} ;

char name[1000];

TFile *filein;

TH1D* hist_back[nalgo][netarange][unf_par];

sprintf(name,"%s",filenames[0]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
  for(int kl=0; kl<unf_par; kl++){
			sprintf(name,"%s_%s_EtaBin%i_back",unf_name[kl],JetRad[ij],jk+1);
			hist_back[ij][jk][kl] = (TH1D*)filein->Get(name);
			}//kl
		}//jk
	}//ij

TCanvas *c2[nalgo][netarange];
TLegend *leg[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

  sprintf(name,"Backfolding_%s_EtaBin%i",JetRad[ij],jk+1);
  c2[ij][jk] = tdrCanvas(name,hist_back[ij][jk][0],4,0);
  leg[ij][jk] = tdrLeg(0.35,0.65,0.65,0.9);

  c2[ij][jk]->cd();

  gPad->SetLogx(1);

  for(int kl=0; kl<unf_par; kl++){

    hist_back[ij][jk][kl]->SetLineColor(unf_col[kl]);
    hist_back[ij][jk][kl]->SetMinimum(0.);
    hist_back[ij][jk][kl]->SetMaximum(2.);

    hist_back[ij][jk][kl]->GetXaxis()->SetTitle("Jet P_{T}(in GeV)");
    hist_back[ij][jk][kl]->GetXaxis()->SetTitleSize(0.04);
    hist_back[ij][jk][kl]->GetXaxis()->SetLabelSize(0.04);
    hist_back[ij][jk][kl]->GetXaxis()->CenterTitle();
    hist_back[ij][jk][kl]->GetYaxis()->SetTitle("Backfolded/MC_RECO");
    hist_back[ij][jk][kl]->GetYaxis()->SetTitleSize(0.04);
    hist_back[ij][jk][kl]->GetYaxis()->SetLabelSize(0.04);
    hist_back[ij][jk][kl]->GetYaxis()->CenterTitle();	

    if(kl==0){ hist_back[ij][jk][kl]->Draw(); }
    else{ hist_back[ij][jk][kl]->Draw("sames"); }

    leg[ij][jk]->AddEntry(hist_back[ij][jk][kl],unf_goodname[kl],"l");
  }//kl
    leg[ij][jk]->Draw();

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
    text1+= ybinname[jk];
    TString text2;
    text2+= eff[1];
  
    latex.DrawLatex(0.5,0.35,text);
    latex.DrawLatex(0.5,0.35-0.05,text1);
    latex.DrawLatex(0.65,0.35-0.1,text2);     

    sprintf(name,"Backfolding_Plots/%s.eps",c2[ij][jk]->GetName());
    c2[ij][jk]->SaveAs(name);
 }//jk
}//ij

}

int main()
{
Backfolding_Plot_Maker();
}
