#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include <fstream>

void TexttoHist()
{
const char *err_title[1] = {"Scale"};
ifstream fp("Theory_Unc_Files/Scale_Rad.log");

const int nalgo = 12;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};

const int netarange = 10;
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

double rad_err_up[nalgo][netarange][noptbins];
double rad_err_dn[nalgo][netarange][noptbins];

TH1D *hist_rad_err_up[nalgo][netarange];
TH1D *hist_rad_err_dn[nalgo][netarange];

char name[100];

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

    sprintf(name,"%s_rad_up_%s_EtaBin%i",err_title[0],JetRad[ij],jk+1);
    hist_rad_err_up[ij][jk] = new TH1D(name,name,noptbins,ptbins);

    sprintf(name,"%s_rad_dn_%s_EtaBin%i",err_title[0],JetRad[ij],jk+1);
    hist_rad_err_dn[ij][jk] = new TH1D(name,name,noptbins,ptbins);

    for(int kl=0; kl<noptbins; kl++){
       int xx1,xx2,xx3;
       fp>>xx1>>xx2>>xx3>>rad_err_up[ij][jk][kl]>>rad_err_dn[ij][jk][kl];
       if(rad_err_up[ij][jk][kl]>1.) {rad_err_up[ij][jk][kl] = 1.;}
       if(rad_err_dn[ij][jk][kl]>1.) {rad_err_dn[ij][jk][kl] = 1.;}

	hist_rad_err_up[ij][jk]->SetBinContent(kl+1,rad_err_up[ij][jk][kl]);
	hist_rad_err_dn[ij][jk]->SetBinContent(kl+1,rad_err_dn[ij][jk][kl]);
    }//kl

	hist_rad_err_up[ij][jk]->Scale(1.);
	hist_rad_err_dn[ij][jk]->Scale(-1.);

	hist_rad_err_up[ij][jk]->SetMinimum(-0.25);
	hist_rad_err_up[ij][jk]->SetMaximum(0.25);

	hist_rad_err_up[ij][jk]->GetXaxis()->SetRangeUser(74,3000.);
	hist_rad_err_up[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
	hist_rad_err_up[ij][jk]->GetXaxis()->SetTitleOffset(1.2);
	hist_rad_err_up[ij][jk]->GetXaxis()->SetTitleSize(0.065);
	hist_rad_err_up[ij][jk]->GetXaxis()->SetLabelSize(0.05);
	hist_rad_err_up[ij][jk]->GetXaxis()->CenterTitle();

	hist_rad_err_up[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Ratio of Xsections");
	hist_rad_err_up[ij][jk]->GetYaxis()->SetTitleOffset(5);
        hist_rad_err_up[ij][jk]->GetYaxis()->SetTitleSize(0.0475);
        hist_rad_err_up[ij][jk]->GetYaxis()->SetLabelSize(0.035);
//        hist_rad_err_up[ij][jk]->GetYaxis()->CenterTitle();
  }//jk
 }//ij

  fp.close();

  double leg_x1 = 0.45;
  double leg_y1 = 0.7;
  double leg_x2 = 0.75;
  double leg_y2 = 0.9;

  TCanvas *c3[nalgo][netarange];
  TLegend *leg_rad[nalgo][netarange];

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.065);

  for(int ij=0; ij<nalgo; ij++){
    for(int jk=0; jk<netarange; jk++){

  sprintf(name,"%s_rad_err_%s_EtaBin%i",err_title[0],JetRad[ij],jk+1);
  c3[ij][jk] =  tdrCanvas(name,hist_rad_err_up[ij][jk],6,0);

  leg_rad[ij][jk] =  new TLegend(leg_x1+0.15,leg_y1,leg_x2+0.15,leg_y2);

  c3[ij][jk]->cd();
  gPad->SetLogx(1);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.025,leg_y1-0.35,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.025,leg_y1-0.425,text1);

   hist_rad_err_up[ij][jk]->SetLineColor(2);
   hist_rad_err_dn[ij][jk]->SetLineColor(4);

   tdrDraw(hist_rad_err_up[ij][jk],kSolid,-1,kSolid,2,0,2);
   tdrDraw(hist_rad_err_dn[ij][jk],kSolid,-1,kSolid,4,0,2);

   sprintf(name,"%s Error Up",err_title[0]);
   leg_rad[ij][jk]->AddEntry(hist_rad_err_up[ij][jk],name,"l");
   sprintf(name,"%s Error Down",err_title[0]);
   leg_rad[ij][jk]->AddEntry(hist_rad_err_dn[ij][jk],name,"l");

  leg_rad[ij][jk]->SetBorderSize(0);
  leg_rad[ij][jk]->SetTextSize(0.045);
  leg_rad[ij][jk]->SetTextFont(42);
  leg_rad[ij][jk]->Draw();

  sprintf(name,"Scale_Plots/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);
  }
 }
}
