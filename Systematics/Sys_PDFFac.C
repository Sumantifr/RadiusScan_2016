#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include <fstream>
#include <TH1D.h>
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

void Sys_PDFFac()
{
const int nalgo = 12;
const int Etabins = 10;
const int nscale = 2;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[Etabins] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const char* scale_dir[2] = {"+ Unc","- Unc"};

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int ref = 3;

ofstream fp_pt;
fp_pt.open("PDFFac_Pt.log");

ofstream fp_rad;
fp_rad.open("PDFFac_Rad.log");

char name[100];

TH1D *pt_unc[nalgo][Etabins][nscale];
TH1D *rad_unc[nalgo][Etabins][nscale];

TH1D *pt_unc_tot[nalgo][Etabins];

double pt_unc_up[nalgo][Etabins][noptbins];
double pt_unc_dn[nalgo][Etabins][noptbins];
double rad_unc_up[nalgo][Etabins][noptbins];
double rad_unc_dn[nalgo][Etabins][noptbins];

TFile *file0 = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/CT14nlo_L6_files.root","read");
file0->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

   sprintf(name,"Tot_PDFFac_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
   pt_unc_tot[ij][jk] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"PDF_Unc_JetpT_%s_EtaBin%i_Up",JetRad[ij],jk+1);
   pt_unc[ij][jk][0] = (TH1D*)file0->Get(name);
   sprintf(name,"PDF_Unc_JetpT_%s_EtaBin%i_Dn",JetRad[ij],jk+1);
   pt_unc[ij][jk][1] = (TH1D*)file0->Get(name);  
   
   for(int bn=0; bn<noptbins; bn++){

	pt_unc_up[ij][jk][bn] = max(0.,fabs(pt_unc[ij][jk][0]->GetBinContent(bn+1)));
	pt_unc_dn[ij][jk][bn] = max(0.,fabs(pt_unc[ij][jk][1]->GetBinContent(bn+1)));
/*
	pt_unc_tot[ij][jk]->SetBinErrorUp(bn+1,pt_unc_up[ij][jk][bn]);
        pt_unc_tot[ij][jk]->SetBinErrorDown(bn+1,pt_unc_dn[ij][jk][bn]);
*/	pt_unc_tot[ij][jk]->SetBinContent(bn+1,0);
	
	}
 }
}

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
   for(int bn=0; bn<noptbins; bn++){
/*
    rad_unc_up[ij][jk][bn] = sqrt(pow(pt_unc_up[ij][jk][bn],2.)+pow(pt_unc_up[ref][jk][bn],2.));
    rad_unc_dn[ij][jk][bn] = sqrt(pow(pt_unc_dn[ij][jk][bn],2.)+pow(pt_unc_dn[ref][jk][bn],2.));
*/
    rad_unc_up[ij][jk][bn] = (pt_unc_up[ij][jk][bn] - pt_unc_up[ref][jk][bn])*1./(1.+max(0.,fabs(pt_unc_up[ref][jk][bn])));
    rad_unc_up[ij][jk][bn] = (pt_unc_dn[ij][jk][bn] - pt_unc_dn[ref][jk][bn])*1./(1.+max(0.,fabs(pt_unc_dn[ref][jk][bn])));

    fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<pt_unc_up[ij][jk][bn]<<'\t'<<pt_unc_dn[ij][jk][bn]<<endl;
    fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<rad_unc_up[ij][jk][bn]<<'\t'<<rad_unc_dn[ij][jk][bn]<<endl;
   }
  }
 }

fp_pt.close();
fp_rad.close();

TCanvas *c2[nalgo][Etabins];
TLegend *leg[nalgo][Etabins];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){

  pt_unc[ij][jk][1]->SetMinimum(-0.2);
  pt_unc[ij][jk][1]->SetMaximum(+0.2);

  sprintf(name,"Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c2[ij][jk] = tdrCanvas(name,pt_unc[ij][jk][1],2,0);

  leg[ij][jk] = new TLegend(0.4,0.7,0.7,0.9);
  leg[ij][jk]->SetBorderSize(0);  
  leg[ij][jk]->SetTextSize(0.05);
  leg[ij][jk]->SetTextFont(42);

  c2[ij][jk]->cd();

  pt_unc[ij][jk][1]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
  pt_unc[ij][jk][1]->GetXaxis()->CenterTitle();
  pt_unc[ij][jk][1]->GetXaxis()->SetTitleSize(0.06);
  pt_unc[ij][jk][1]->GetXaxis()->SetLabelSize(0.05);
  pt_unc[ij][jk][1]->GetXaxis()->SetTitleOffset(0.85);
  pt_unc[ij][jk][1]->GetXaxis()->SetRangeUser(84,3000);

  pt_unc[ij][jk][1]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection");
  pt_unc[ij][jk][1]->GetYaxis()->CenterTitle();
  pt_unc[ij][jk][1]->GetYaxis()->SetTitleSize(0.055);
  pt_unc[ij][jk][1]->GetYaxis()->SetLabelSize(0.05);
  pt_unc[ij][jk][1]->GetYaxis()->SetTitleOffset(1.1);

  gPad->SetLogx(1);

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

  latex.DrawLatex(0.4,0.4,text);
  latex.DrawLatex(0.4,0.325,text1);
 
  tdrDraw(pt_unc[ij][jk][0],"][",kFullCircle,-1,kSolid,kRed,0,2);
  tdrDraw(pt_unc[ij][jk][1],"][",kFullCircle,-1,kSolid,kBlue,0,2);

  leg[ij][jk]->AddEntry(pt_unc[ij][jk][0],"PDF Error Up","l");
  leg[ij][jk]->AddEntry(pt_unc[ij][jk][1],"PDF Error Down","l");

  leg[ij][jk]->Draw();

  sprintf(name,"PDFFac_Plots/%s.pdf",c2[ij][jk]->GetName());
  c2[ij][jk]->SaveAs(name);
 }
}

}

int main()
{
Sys_PDFFac();
}
