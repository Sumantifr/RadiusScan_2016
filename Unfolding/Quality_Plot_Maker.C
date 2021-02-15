#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

void Quality_Plot_Maker()
{
const int nfiles = 1;
//const char *filenames[nfiles] = {"Unfolded_2016_P8_NTuple_MC_P8_lowptbins.root"};
const char *filenames[nfiles] = {"Unfolded_2016_Data_NTuple_MC_P8_Legacy_old_excor.root"};

static const int nalgo = 12 ;
static const int netarange = 10 ;

int eta_max = 6;
eta_max -= 1;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

//const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* jetname[nalgo] = {"R = 0.1","R = 0.2","R = 0.3","R = 0.4","R = 0.5","R = 0.6","R = 0.7","R = 0.8","R = 0.9","R = 1.0","R = 1.1","R = 1.2"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;
int col[netarange] = {1,2,3,4,5,6,7,9,12,24};

const char* qname[4] = {"Efficiency","Fake","Purity","Stability"} ;

float leg_x1 =0.2; 
float leg_x2 =0.6;
float leg_y1 =0.2;
float leg_y2 =0.5;

double pt_min = 84., pt_max = 3000.;

char name[1000];

TFile *filein;

TH1D* hist_eff[nalgo][netarange];
TH1D* hist_fake[nalgo][netarange];
TH1D* hist_purity[nalgo][netarange];
TH1D* hist_stbl[nalgo][netarange];

sprintf(name,"%s",filenames[0]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

  sprintf(name,"Efficiency_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_eff[ij][jk] = (TH1D*)filein->Get(name);

  sprintf(name,"Fake_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_fake[ij][jk] = (TH1D*)filein->Get(name);

  sprintf(name,"Purity_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_purity[ij][jk] = (TH1D*)filein->Get(name);

  sprintf(name,"Stability_%s_EtaBin%i",JetRad[ij],jk+1);
  hist_stbl[ij][jk] = (TH1D*)filein->Get(name);

 }//jk
}//ij

TCanvas *c2[nalgo][4];
TLegend *leg[nalgo][4];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<4; jk++){

sprintf(name,"QualityPlot_%s_%s",JetRad[ij],qname[jk]);
c2[ij][jk] = tdrCanvas(name,hist_eff[ij][jk],7,0);
if(jk==0){
leg[ij][jk] = tdrLeg(0.35,0.4,0.65,0.75);
}
else{
if(jk==2||jk==3){
leg[ij][jk] = tdrLeg(0.5,0.55,0.8,0.875);
}else{
leg[ij][jk] = tdrLeg(0.6,0.45,0.95,0.875);
 }
}

leg[ij][jk]->SetTextFont(42);
leg[ij][jk]->SetTextSize(0.06);

c2[ij][jk]->cd();

gPad->SetLogx(1);

TLatex latex;
latex.SetNDC();
latex.SetTextAngle(0);
latex.SetTextColor(kBlack);

latex.SetTextFont(42);
latex.SetTextAlign(31);
latex.SetTextSize(0.06);

TString text;
text+= jetname[ij];

//latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);

if(jk==0){
    for(int eta=0; eta<netarange; eta++){

    if(eta>eta_max) continue;

    hist_eff[ij][eta]->SetLineColor(col[eta]);
    hist_eff[ij][eta]->GetYaxis()->SetTitle("Efficiency(in %)");
    hist_eff[ij][eta]->GetYaxis()->SetTitleSize(0.06);
    hist_eff[ij][eta]->GetYaxis()->SetTitleOffset(0.9);
    hist_eff[ij][eta]->GetYaxis()->CenterTitle();
    hist_eff[ij][eta]->GetYaxis()->SetLabelSize(0.06);
    hist_eff[ij][eta]->GetXaxis()->SetTitle("Jet P_{T}(in GeV)");
    hist_eff[ij][eta]->GetXaxis()->SetTitleSize(0.06);
    hist_eff[ij][eta]->GetXaxis()->CenterTitle();
    hist_eff[ij][eta]->GetXaxis()->SetLabelSize(0.06);
    hist_eff[ij][eta]->GetXaxis()->SetNoExponent();
    hist_eff[ij][eta]->GetXaxis()->SetRangeUser(pt_min,pt_max);
    hist_eff[ij][eta]->SetMinimum(0);
    hist_eff[ij][eta]->SetMaximum(1.05);

    if(eta==0){
    hist_eff[ij][eta]->Draw("hist");
	}else{
	hist_eff[ij][eta]->Draw("sames");
	}
    leg[ij][jk]->AddEntry(hist_eff[ij][eta],ybinname[eta],"l") ;
   }//eta

  leg[ij][jk]->Draw();
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.125,"Anti-k_{T} CHS");
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.05,text);
 }

if(jk==1){
   for(int eta=0; eta<netarange; eta++){

     if(eta>eta_max) continue;

     hist_fake[ij][eta]->SetLineColor(col[eta]);
     hist_fake[ij][eta]->GetYaxis()->SetTitle("Fakerate(in %)");
     hist_fake[ij][eta]->GetYaxis()->SetTitleSize(0.06);
     hist_fake[ij][eta]->GetYaxis()->SetTitleOffset(0.9);
     hist_fake[ij][eta]->GetYaxis()->CenterTitle();
     hist_fake[ij][eta]->GetYaxis()->SetLabelSize(0.06);
     hist_fake[ij][eta]->GetXaxis()->SetTitle("Jet P_{T}(in GeV)");
     hist_fake[ij][eta]->GetXaxis()->SetTitleSize(0.06);
     hist_fake[ij][eta]->GetXaxis()->CenterTitle();
     hist_fake[ij][eta]->GetXaxis()->SetLabelSize(0.06);
     hist_fake[ij][eta]->GetXaxis()->SetNoExponent();
     hist_fake[ij][eta]->GetXaxis()->SetRangeUser(pt_min,pt_max);
     hist_fake[ij][eta]->SetMinimum(0);
     hist_fake[ij][eta]->SetMaximum(1.05);

    if(eta==0){
    hist_fake[ij][eta]->Draw();
        }else{
        hist_fake[ij][eta]->Draw("sames");
        }
    leg[ij][jk]->AddEntry(hist_fake[ij][eta],ybinname[eta],"l") ;
   }//eta
  leg[ij][jk]->Draw();
  
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.65,"Anti-k_{T} CHS");
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.575,text);
 }

if(jk==2){
  for(int eta=0; eta<netarange; eta++){

    if(eta>eta_max) continue;

    hist_purity[ij][eta]->SetLineColor(col[eta]);
    hist_purity[ij][eta]->GetYaxis()->SetTitle("Purity(in %)");
    hist_purity[ij][eta]->GetYaxis()->SetTitleSize(0.06);
    hist_purity[ij][eta]->GetYaxis()->CenterTitle();
    hist_purity[ij][eta]->GetYaxis()->SetLabelSize(0.06);
    hist_purity[ij][eta]->GetXaxis()->SetTitle("Jet P_{T}(in GeV)");
    hist_purity[ij][eta]->GetXaxis()->SetTitleSize(0.06);
    hist_purity[ij][eta]->GetXaxis()->CenterTitle();
    hist_purity[ij][eta]->GetXaxis()->SetLabelSize(0.06);
    hist_purity[ij][eta]->GetXaxis()->SetNoExponent();
    hist_purity[ij][eta]->GetXaxis()->SetRangeUser(pt_min,pt_max);
    hist_purity[ij][eta]->SetMinimum(0);
    hist_purity[ij][eta]->SetMaximum(1.05);   
 
    if(eta==0){
    hist_purity[ij][eta]->Draw();
        }else{
        hist_purity[ij][eta]->Draw("sames");
        }
   leg[ij][jk]->AddEntry(hist_purity[ij][eta],ybinname[eta],"l") ;
   }//eta
  leg[ij][jk]->Draw();
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.65,"Anti-k_{T} CHS");
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.575,text);
  }

if(jk==3){
 for(int eta=0; eta<netarange; eta++){

    if(eta>eta_max) continue;

    hist_stbl[ij][eta]->SetLineColor(col[eta]);
    hist_stbl[ij][eta]->GetYaxis()->SetTitle("Stability(in %)");
    hist_stbl[ij][eta]->GetYaxis()->SetTitleSize(0.06);
    hist_stbl[ij][eta]->GetYaxis()->SetTitleOffset(0.9);
    hist_stbl[ij][eta]->GetYaxis()->CenterTitle();
    hist_stbl[ij][eta]->GetYaxis()->SetLabelSize(0.06);
    hist_stbl[ij][eta]->GetXaxis()->SetTitle("Jet P_{T}(in GeV)");
    hist_stbl[ij][eta]->GetXaxis()->SetTitleSize(0.06);
    hist_stbl[ij][eta]->GetXaxis()->CenterTitle();
    hist_stbl[ij][eta]->GetXaxis()->SetLabelSize(0.06);
    hist_stbl[ij][eta]->GetXaxis()->SetNoExponent();
    hist_stbl[ij][eta]->GetXaxis()->SetRangeUser(pt_min,pt_max);
    hist_stbl[ij][eta]->SetMinimum(0);
    hist_stbl[ij][eta]->SetMaximum(1.05);

    if(eta==0){
    hist_stbl[ij][eta]->Draw();
        }else{
        hist_stbl[ij][eta]->Draw("sames");
        }
   leg[ij][jk]->AddEntry(hist_stbl[ij][eta],ybinname[eta],"l") ;
   }//eta
  leg[ij][jk]->Draw(); 
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.65,"Anti-k_{T} CHS");
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1+0.575,text);
  }

   sprintf(name,"Quality_Plots/Legacy/%s.png",c2[ij][jk]->GetName());
   c2[ij][jk]->SaveAs(name);
   }//jk
 }//ij

}

int main()
{
Quality_Plot_Maker();
}
