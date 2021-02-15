#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include <fstream>

void Sys_Unf()
{

ifstream fp0_pt("Unf_Files/Ex_Cor_84/Unf_Data_Pt_excor84.log");  //data unfolded by MC
ifstream fp1_pt("Unf_Files/Ex_Cor_84/Unf_Pt_Pythia_excor_84.log"); //P8 unfolded by MC
ifstream fp2_pt("Unf_Files/Ex_Cor_84/Unf_Pt_Madgraph_excor_84.log"); //MG unfolded by MC
ifstream fp3_pt("Unf_Files/Ex_Cor_84/Unf_Pt_Herwig_excor_84.log"); //Hwg unfolded by MC
//ifstream fp4_pt("RM_Unc_Pt.log"); //10% Jacknife
//ifstream fp5_pt("Unf_Pt_P8_Stat.log"); // stat error after unfolding 
ifstream fp4_pt("Unf_Files/Ex_Cor_84/Unfolding_Tech_Err_Pt_excor_84.log");//Difference btwn Bayesian, SVD, BinbyBin
ifstream fp5_pt("Unf_Files/Ex_Cor_84/Refold_Pt_excor_84.log");//contribution from refold

ifstream fp0_rad("Unf_Files/Ex_Cor_84/Unf_Data_Rad_excor84.log");  //data unfolded by MC
ifstream fp1_rad("Unf_Files/Ex_Cor_84/Unf_Rad_Pythia_excor_84.log"); //P8 unfolded by MC
ifstream fp2_rad("Unf_Files/Ex_Cor_84/Unf_Rad_Madgraph_excor_84.log"); //MG unfolded by MC
ifstream fp3_rad("Unf_Files/Ex_Cor_84/Unf_Rad_Herwig_excor_84.log"); //Hwg unfolded by MC
//ifstream fp4_rad("RM_Unc_Rad.log"); //10% Jacknife
//ifstream fp5_rad("Unf_Rad_P8_Stat.log"); // stat error after unfolding 
ifstream fp4_rad("Unf_Files/Ex_Cor_84/Unfolding_Tech_Err_Rad_excor_84.log");//Difference btwn Bayesian, SVD, BinbyBin
ifstream fp5_rad("Unf_Files/Ex_Cor_84/Refold_Rad_excor_84.log");//contribution from refold

ofstream fp_out_pt;
fp_out_pt.open("Unf_Files/Ex_Cor_84/Unf_Unc_Total_Pt_excor_84.log");
ofstream fp_out_rad;
fp_out_rad.open("Unf_Files/Ex_Cor_84/Unf_Unc_Total_Rad_excor_84.log");

const int nfiles = 6;
int col[nfiles] = {1,2,3,4,/*6,7,*/kRed-7,kGreen-1};
int sty[nfiles] = {1,2,3,4,/*5,6,*/7,8};
const char *unf_name[nfiles] = {"Data_MC","P8_MC","Madgraph_MC","Herwig_MC",/*"10% Jackknife","Stat Unc",*/"Technique Var","Refold"};

const int nalgo = 12;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};

const int netarange = 10;
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

float ptlim[netarange] = {0.2,0.2,0.2,0.2,0.25,0.3,0.3,0.3,0.35,0.35};
float radlim[netarange] = {0.2,0.2,0.2,0.2,0.25,0.3,0.3,0.3,0.35,0.35};

const int noptbins = 61;

double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64, 74,*/ 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

char name[100];

double pt_tot_err[nalgo][netarange][noptbins];
double rad_tot_err[nalgo][netarange][noptbins];

double pt_err[nfiles][nalgo][netarange][noptbins];
double rad_err[nfiles][nalgo][netarange][noptbins];

TH1D *hist_pt[nfiles][nalgo][netarange];
TH1D *hist_rad[nfiles][nalgo][netarange];

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   sprintf(name,"unf_pt_err_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_pt[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"unf_rad_err_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_rad[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

    for(int kl=0; kl<noptbins; kl++){
     int xx;

     if(fg==0) {fp0_pt>>xx>>xx>>xx>>pt_err[fg][ij][jk][kl]>>pt_err[fg][ij][jk][kl];}
     else if (fg==1) {fp1_pt>>xx>>xx>>xx>>pt_err[fg][ij][jk][kl]>>pt_err[fg][ij][jk][kl];}
     else if (fg==2) {fp2_pt>>xx>>xx>>xx>>pt_err[fg][ij][jk][kl]>>pt_err[fg][ij][jk][kl];}
     else if (fg==3) {fp3_pt>>xx>>xx>>xx>>pt_err[fg][ij][jk][kl]>>pt_err[fg][ij][jk][kl];}
     else if (fg==4) {fp4_pt>>xx>>xx>>xx>>pt_err[fg][ij][jk][kl]>>pt_err[fg][ij][jk][kl];}
     else if (fg==5) {fp5_pt>>xx>>xx>>xx>>pt_err[fg][ij][jk][kl]>>pt_err[fg][ij][jk][kl];}
                     //pt_err[fg][ij][jk][kl] = sqrt(max(0.,pow(pt_err[fg][ij][jk][kl],2.)-pow(pt_err[4][ij][jk][kl],2.))) ; 
/*		     }
     else if (fg==6) {fp6_pt>>xx>>xx>>xx>>pt_err[fg][ij][jk][kl]>>pt_err[fg][ij][jk][kl];}
     else if (fg==7) {fp7_pt>>xx>>xx>>xx>>pt_err[fg][ij][jk][kl]>>pt_err[fg][ij][jk][kl];}
*/

     if(pt_err[fg][ij][jk][kl]>(1.-1.e-9)) {pt_err[fg][ij][jk][kl] = 0;}
     hist_pt[fg][ij][jk]->SetBinContent(kl+1,pt_err[fg][ij][jk][kl]);

     if(fg==0) {fp0_rad>>xx>>xx>>xx>>rad_err[fg][ij][jk][kl]>>rad_err[fg][ij][jk][kl];}
     else if (fg==1) {fp1_rad>>xx>>xx>>xx>>rad_err[fg][ij][jk][kl]>>rad_err[fg][ij][jk][kl];}
     else if (fg==2) {fp2_rad>>xx>>xx>>xx>>rad_err[fg][ij][jk][kl]>>rad_err[fg][ij][jk][kl];}
     else if (fg==3) {fp3_rad>>xx>>xx>>xx>>rad_err[fg][ij][jk][kl]>>rad_err[fg][ij][jk][kl];}
     else if (fg==4) {fp4_rad>>xx>>xx>>xx>>rad_err[fg][ij][jk][kl]>>rad_err[fg][ij][jk][kl];}
     else if (fg==5) {fp5_rad>>xx>>xx>>xx>>rad_err[fg][ij][jk][kl]>>rad_err[fg][ij][jk][kl];}
/*
     else if (fg==6) {fp6_rad>>xx>>xx>>xx>>rad_err[fg][ij][jk][kl]>>rad_err[fg][ij][jk][kl];}
     else if (fg==7) {fp7_rad>>xx>>xx>>xx>>rad_err[fg][ij][jk][kl]>>rad_err[fg][ij][jk][kl];}
*/
  //   if(fg==3) { cout<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<rad_err[fg][ij][jk][kl]<<endl;}

     if(rad_err[fg][ij][jk][kl]>(1.-1.e-9)) {rad_err[fg][ij][jk][kl] = 0;}
     hist_rad[fg][ij][jk]->SetBinContent(kl+1,rad_err[fg][ij][jk][kl]);
  
   }
     hist_pt[fg][ij][jk]->SetMinimum(0.);
     hist_pt[fg][ij][jk]->SetMaximum(ptlim[jk]);
     hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(74,3000.);
/*
     if(fg==0&&ij==7&&jk==0){
	for(int kl=0; kl<noptbins; kl++){
	cout<<"bin "<<kl+1<<" err "<<rad_err[fg][ij][jk][kl]<<endl;
	}
     }
*/
     hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
     hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
     hist_pt[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
     hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();

     hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("Rel Unc in Xsection");
     hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.06);
     hist_pt[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
     hist_pt[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.09);
     hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();


     hist_rad[fg][ij][jk]->SetMinimum(0.);
     hist_rad[fg][ij][jk]->SetMaximum(radlim[jk]);
     hist_rad[fg][ij][jk]->GetXaxis()->SetRangeUser(74,3000.);

     hist_rad[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
     hist_rad[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
     hist_rad[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
     hist_rad[fg][ij][jk]->GetXaxis()->CenterTitle();

     hist_rad[fg][ij][jk]->GetYaxis()->SetTitle("Rel Unc in Ratio of Xsections");
     hist_rad[fg][ij][jk]->GetYaxis()->SetTitleSize(0.06);
     hist_rad[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
     hist_rad[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.09);
     hist_rad[fg][ij][jk]->GetYaxis()->CenterTitle();


  }
 }
}

TCanvas *c2[nalgo][netarange];
TLegend *leg_pt[nalgo][netarange];

TCanvas *c3[nalgo][netarange];
TLegend *leg_rad[nalgo][netarange];

double leg_x1 = 0.3;
double leg_y1 = 0.6;
double leg_x2 = 0.6;
double leg_y2 = 0.9;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

  sprintf(name,"Unf_pt_err_%s_EtaBin%i",JetRad[ij],jk+1);
  c2[ij][jk] =  tdrCanvas(name,hist_pt[0][ij][jk],6,0); 

  leg_pt[ij][jk] =  new TLegend(leg_x1,leg_y1,leg_x2,leg_y2);   
  leg_pt[ij][jk]->SetBorderSize(0);
  leg_pt[ij][jk]->SetTextSize(0.05);  
  leg_pt[ij][jk]->SetTextFont(42);

  c2[ij][jk]->cd();
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

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1-0.1,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1-0.175,text1);
  
  for(int fg=0; fg<nfiles; fg++){

//   if(fg==4||fg==5) continue;

   hist_pt[fg][ij][jk]->SetLineColor(col[fg]);
//   hist_pt[fg][ij][jk]->SetLineWidth(2);
//   if(fg<4) continue;
   tdrDraw(hist_pt[fg][ij][jk],sty[fg],-1,kSolid,col[fg],0,2);   
   leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],unf_name[fg],"l");
  } 

  leg_pt[ij][jk]->Draw();

  sprintf(name,"Unfolding_Plots/Ex_Cor_84/Pt_Plots/%s.eps",c2[ij][jk]->GetName());
  c2[ij][jk]->SaveAs(name);

 }
}

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

  sprintf(name,"Unf_rad_err_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] =  tdrCanvas(name,hist_rad[0][ij][jk],6,0);

  leg_rad[ij][jk] =  new TLegend(leg_x1+0.3,leg_y1,leg_x2+0.3,leg_y2);
  leg_rad[ij][jk]->SetBorderSize(0);
  leg_rad[ij][jk]->SetTextSize(0.05);
  leg_rad[ij][jk]->SetTextFont(42);

  c3[ij][jk]->cd();
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

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1-0.1,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1-0.175,text1);

  for(int fg=0; fg<nfiles; fg++){

//   if(fg==4||fg==5) continue;

   hist_rad[fg][ij][jk]->SetLineColor(col[fg]);
  
   tdrDraw(hist_rad[fg][ij][jk],sty[fg],-1,kSolid,col[fg],0,2);
   leg_rad[ij][jk]->AddEntry(hist_rad[fg][ij][jk],unf_name[fg],"l");
  }

  leg_rad[ij][jk]->Draw();

  sprintf(name,"Unfolding_Plots/Ex_Cor_84/Ratio_Plots/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);
  }
 }


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
 
   fp_out_pt<<ij+1<<'\t'<<jk+1<<'\t'<<1<<'\t'<<0<<'\t'<<0<<endl;
   fp_out_rad<<ij+1<<'\t'<<jk+1<<'\t'<<1<<'\t'<<0<<'\t'<<0<<endl;

   for(int bn=0; bn<noptbins; bn++){

	double ptmax = -1.;
	double radmax = -1.;

	for(int fg=0; fg<nfiles; fg++){
	// if(fg==4||fg==5) continue;

	if(abs(pt_err[fg][ij][jk][bn]) > ptmax) { ptmax = abs(pt_err[fg][ij][jk][bn]); }
	if(abs(rad_err[fg][ij][jk][bn]) > radmax) { radmax = abs(rad_err[fg][ij][jk][bn]); }
	}

	pt_tot_err[ij][jk][bn] = ptmax;
	rad_tot_err[ij][jk][bn] = radmax;	

        fp_out_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+2<<'\t'<<pt_tot_err[ij][jk][bn]<<'\t'<<pt_tot_err[ij][jk][bn]<<endl;
	fp_out_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+2<<'\t'<<rad_tot_err[ij][jk][bn]<<'\t'<<rad_tot_err[ij][jk][bn]<<endl;	
      }
   }
}


}

int main()
{
Sys_Unf();
}
