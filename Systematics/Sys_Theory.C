#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include <fstream>

void Sys_Theory()
{
const int nfiles = 7;
const char *filenames_pt[nfiles] = 
   {"Theory_Unc_Files/Scale_Pt_AK4.log",
	"Theory_Unc_Files/PDFFac_Pt.log"
	,"Theory_Unc_Files/PDFVar_PDF4LHC_AK4_Pt.log",
	"Theory_Unc_Files/Alphas_AK4_Pt.log",
	"Theory_Unc_Files/MPI_Pt.log",
	"Theory_Unc_Files/NP_Pt.log",
//	"Theory_Unc_Files/PSVar_PHP8_Pt.log"};
	"Theory_Unc_Files/PS/PSVar_PHP8_Pt.log"};
const char *filenames_rad[nfiles] = 
{"Theory_Unc_Files/Scale_wAK4_Rad.log",//Scale_Rad_AK4.log",
	"Theory_Unc_Files/PDFFac_Rad.log",
	"Theory_Unc_Files/PDFVar_PDF4LHC_AK4_Rad.log",
	"Theory_Unc_Files/Alphas_AK4_Rad.log",
	"Theory_Unc_Files/MPI_Rad.log",
//	"Theory_Unc_Files/NP_Rad.log",
	"Theory_Unc_Files/NP_Total_wAK4_Rad.log",
	"Theory_Unc_Files/PS/PSVar_PHP8_Rad.log"};
	

ofstream fp_pt_tot;
fp_pt_tot.open("Total_Theory_Unc_Pt_84.log");

ofstream fp_rad_tot;
fp_rad_tot.open("Total_Theory_Unc_Rad_84.log");

int col[nfiles] = {1,2,4,6,7,9,kYellow+3};
int sty[nfiles] = {1,2,3,4,5,9,7};
const char *sys_name[nfiles] = {"Scale","PDF","PDF Choice","#alpha_{s}","MPI","NP Correction","Parton Shower"};

double min_range = 84;
double max_range = 1588;


const int nalgo = 12;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

//const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* jetname[nalgo] = {"R = 0.1","R = 0.2","R = 0.3","R = 0.4","R = 0.5","R = 0.6","R = 0.7","R = 0.8","R = 0.9","R = 1.0","R = 1.1","R = 1.2"};

const int netarange = 10;
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

float radlim[netarange] = {0.175,0.175,0.175,0.3,0.32,0.4,0.4,0.4,0.4,0.4};
float radlimd[netarange] = {0.1,0.1,0.1,0.3,0.32,0.4,0.4,0.4,0.4,0.4};

const int noptbins = 62;

double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

char name[1000];

double pt_err_up[nfiles][nalgo][netarange][noptbins];
double pt_err_dn[nfiles][nalgo][netarange][noptbins];
double rad_err_up[nfiles][nalgo][netarange][noptbins];
double rad_err_dn[nfiles][nalgo][netarange][noptbins];

double pt_err_up_tot[nalgo][netarange][noptbins];
double pt_err_dn_tot[nalgo][netarange][noptbins];
double rad_err_up_tot[nalgo][netarange][noptbins];
double rad_err_dn_tot[nalgo][netarange][noptbins];

TH1D *hist_pt_up[nfiles][nalgo][netarange];
TH1D *hist_pt_dn[nfiles][nalgo][netarange];
TH1D *hist_rad_up[nfiles][nalgo][netarange];
TH1D *hist_rad_dn[nfiles][nalgo][netarange];

TGraphAsymmErrors *gr_rad_tot[nalgo][netarange];

for(int fg=0; fg<nfiles; fg++){
 
 sprintf(name,"%s",filenames_pt[fg]);
 ifstream fp_pt(name);

 sprintf(name,"%s",filenames_rad[fg]);
 ifstream fp_rad(name);

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   sprintf(name,"theory_sys_pt_err_up_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_pt_up[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"theory_sys_pt_err_dn_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_pt_dn[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"theory_sys_rad_err_up_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_rad_up[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"theory_sys_rad_err_dn_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_rad_dn[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

   for(int kl=0; kl<noptbins; kl++){
     int xx1,xx2,xx3;

	fp_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl];

    fp_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];
//	if(fg==6&&ij==0&&jk==0) { cout<<xx1<<'\t'<<xx2<<'\t'<<xx3<<'\t'<<rad_err_up[fg][ij][jk][kl]<<'\t'<<rad_err_dn[fg][ij][jk][kl]<<endl;}

	if(fg==3) { pt_err_up[fg][ij][jk][kl]*=1.5; pt_err_dn[fg][ij][jk][kl]*=1.5;
		    rad_err_up[fg][ij][jk][kl]*=1.5; rad_err_dn[fg][ij][jk][kl]*=1.5; }

	if(pt_err_up[fg][ij][jk][kl]>0.9999) {pt_err_up[fg][ij][jk][kl] = 0.;}
        if(pt_err_dn[fg][ij][jk][kl]>0.9999) {pt_err_dn[fg][ij][jk][kl] = 0.;}

        pt_err_up_tot[ij][jk][kl]+=pow(pt_err_up[fg][ij][jk][kl],2);
        pt_err_dn_tot[ij][jk][kl]+=pow(pt_err_dn[fg][ij][jk][kl],2);

        hist_pt_up[fg][ij][jk]->SetBinContent(kl+1,pt_err_up[fg][ij][jk][kl]);
        hist_pt_dn[fg][ij][jk]->SetBinContent(kl+1,pt_err_dn[fg][ij][jk][kl]);

	if(rad_err_up[fg][ij][jk][kl]>0.9999) {rad_err_up[fg][ij][jk][kl] = 0.;}
        if(rad_err_dn[fg][ij][jk][kl]>0.9999) {rad_err_dn[fg][ij][jk][kl] = 0.;}

        rad_err_up_tot[ij][jk][kl]+=pow(rad_err_up[fg][ij][jk][kl],2);
        rad_err_dn_tot[ij][jk][kl]+=pow(rad_err_dn[fg][ij][jk][kl],2);

        hist_rad_up[fg][ij][jk]->SetBinContent(kl+1,rad_err_up[fg][ij][jk][kl]);
        hist_rad_dn[fg][ij][jk]->SetBinContent(kl+1,rad_err_dn[fg][ij][jk][kl]);

     }

      hist_pt_dn[fg][ij][jk]->Scale(-1.);
      hist_rad_dn[fg][ij][jk]->Scale(-1.);

      hist_pt_up[fg][ij][jk]->SetMaximum(0.25);
      hist_pt_up[fg][ij][jk]->SetMinimum(-0.25);
      hist_pt_dn[fg][ij][jk]->SetMinimum(-0.25);

      hist_pt_up[fg][ij][jk]->GetXaxis()->SetRangeUser(74,1500.);

      hist_pt_up[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
      hist_pt_up[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
      hist_pt_up[fg][ij][jk]->GetXaxis()->SetLabelSize(0.055);
      hist_pt_up[fg][ij][jk]->GetXaxis()->SetTitleOffset(0.9);
      hist_pt_up[fg][ij][jk]->GetXaxis()->CenterTitle();
      hist_pt_up[fg][ij][jk]->GetXaxis()->SetNoExponent();

      hist_pt_up[fg][ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection");
      hist_pt_up[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
      hist_pt_up[fg][ij][jk]->GetYaxis()->SetLabelSize(0.055);
      hist_pt_up[fg][ij][jk]->GetYaxis()->CenterTitle();
      hist_pt_up[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.05);
      hist_pt_up[fg][ij][jk]->GetYaxis()->SetNdivisions(406);

      hist_rad_up[fg][ij][jk]->SetMinimum(-radlimd[jk]);
      hist_rad_up[fg][ij][jk]->SetMaximum(radlim[jk]);
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

      hist_rad_up[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetLabelSize(0.055);
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetTitleOffset(0.9);
      hist_rad_up[fg][ij][jk]->GetXaxis()->CenterTitle();
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetNoExponent();
//      hist_rad_up[fg][ij][jk]->GetXaxis()->SetMoreLogLabels();

      hist_rad_up[fg][ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty");// in Ratio of Xsections");
      hist_rad_up[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
      hist_rad_up[fg][ij][jk]->GetYaxis()->SetTitleOffset(5.5);
      hist_rad_up[fg][ij][jk]->GetYaxis()->SetLabelSize(0.055);
      hist_rad_up[fg][ij][jk]->GetYaxis()->CenterTitle();
//      hist_rad_up[fg][ij][jk]->GetYaxis()->SetNdivisions(406);
      hist_rad_dn[fg][ij][jk]->GetYaxis()->SetTitleOffset(5.5);
	
	  
		}//jk
      } //ij

	fp_pt.close();
	fp_rad.close();
   }//fg

 TCanvas *c2[nalgo][netarange];
 TLegend *leg_pt[nalgo][netarange];

 TCanvas *c3[nalgo][netarange];
 TLegend *leg_rad[nalgo][netarange];

 double leg_x1 = 0.45;
 double leg_y1 = 0.65;
 double leg_x2 = 0.7;
 double leg_y2 = 0.9;

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   for(int bn=1; bn<noptbins; bn++){
        rad_err_up_tot[ij][jk][bn] = sqrt(rad_err_up_tot[ij][jk][bn]);
        rad_err_dn_tot[ij][jk][bn] = sqrt(rad_err_dn_tot[ij][jk][bn]);
        pt_err_up_tot[ij][jk][bn] = sqrt(pt_err_up_tot[ij][jk][bn]);
        pt_err_dn_tot[ij][jk][bn] = sqrt(pt_err_dn_tot[ij][jk][bn]);

	fp_pt_tot<<ij+1<<'\t'<<jk+1<<'\t'<<bn<<'\t'<<pt_err_up_tot[ij][jk][bn]<<'\t'<<pt_err_dn_tot[ij][jk][bn]<<endl;
	fp_rad_tot<<ij+1<<'\t'<<jk+1<<'\t'<<bn<<'\t'<<rad_err_up_tot[ij][jk][bn]<<'\t'<<rad_err_dn_tot[ij][jk][bn]<<endl;
        }

  for(int fg=0; fg<nfiles; fg++){
	  
   hist_rad_up[fg][ij][jk]->SetLineColor(col[fg]);
   hist_rad_dn[fg][ij][jk]->SetLineColor(col[fg]);
 
   hist_rad_up[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.25);
 
   hist_rad_up[fg][ij][jk]->SetLineWidth(2);
   hist_rad_dn[fg][ij][jk]->SetLineWidth(2);

   hist_rad_up[fg][ij][jk]->Smooth();
   hist_rad_dn[fg][ij][jk]->Smooth();

   if(fg==6) { hist_rad_up[fg][ij][jk]->Smooth(5); hist_rad_dn[fg][ij][jk]->Smooth(5); }
   
   }

   gr_rad_tot[ij][jk] = new TGraphAsymmErrors();
  
   for(int bn=0; bn<(noptbins); bn++){
	   
	   double raderr_sum_up = 0;
	   double raderr_sum_dn = 0;
	   
	   for(int fg=0; fg<nfiles; fg++){
		   raderr_sum_up += pow(hist_rad_up[fg][ij][jk]->GetBinContent(bn+1),2);
		   raderr_sum_dn += pow(hist_rad_dn[fg][ij][jk]->GetBinContent(bn+1),2);
	   }
	   
	   raderr_sum_up = sqrt(raderr_sum_up);
	   raderr_sum_dn = sqrt(raderr_sum_dn);
	   
	  
		gr_rad_tot[ij][jk]->SetPoint(bn,hist_rad_up[0][ij][jk]->GetBinCenter(bn+1),0);
		gr_rad_tot[ij][jk]->SetPointEYhigh(bn,raderr_sum_up);
		gr_rad_tot[ij][jk]->SetPointEYlow(bn,raderr_sum_dn);

		}
	

  sprintf(name,"Tot_pt_err_%s_EtaBin%i",JetRad[ij],jk+1);
  c2[ij][jk] =  tdrCanvas(name,hist_pt_up[0][ij][jk],2,0);

  leg_pt[ij][jk] =  new TLegend(leg_x1-0.25,leg_y1,leg_x2,leg_y2);
  leg_pt[ij][jk]->SetBorderSize(0);
  leg_pt[ij][jk]->SetTextSize(0.05);
  leg_pt[ij][jk]->SetTextFont(42);
  leg_pt[ij][jk]->SetNColumns(2);

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
  TString text1;
  text1+=  ybinname[jk];
  TString text2;
  text2+= "Anti-k_{T} CHS";

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.375,text2);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.435,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.495,text1);

  for(int fg=0; fg<nfiles; fg++){

   hist_pt_up[fg][ij][jk]->Smooth();
   hist_pt_dn[fg][ij][jk]->Smooth();

   hist_pt_up[fg][ij][jk]->SetLineColor(col[fg]);
   hist_pt_up[fg][ij][jk]->SetLineWidth(2);
   tdrDraw(hist_pt_up[fg][ij][jk],"][",sty[fg],-1,sty[fg],col[fg],0,2);

   hist_pt_dn[fg][ij][jk]->SetLineColor(col[fg]);
   hist_pt_dn[fg][ij][jk]->SetLineWidth(2);
   tdrDraw(hist_pt_dn[fg][ij][jk],"][",sty[fg],-1,sty[fg],col[fg],0,2);

   leg_pt[ij][jk]->AddEntry(hist_pt_up[fg][ij][jk],sys_name[fg],"l");
   }

  leg_pt[ij][jk]->Draw();

  sprintf(name,"Theory_Sys_Plots_PS/Pt_Plots/%s.png",c2[ij][jk]->GetName());
  c2[ij][jk]->SaveAs(name);

  sprintf(name,"Tot_rad_err_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] =  tdrCanvas(name,hist_rad_up[0][ij][jk],2,0);

  leg_rad[ij][jk] =  new TLegend(leg_x1-0.305,leg_y1,leg_x2+0.011,leg_y2);
  leg_rad[ij][jk]->SetBorderSize(0);
  leg_rad[ij][jk]->SetTextSize(0.05);
  leg_rad[ij][jk]->SetTextFont(42);
  leg_rad[ij][jk]->SetNColumns(2);

  c3[ij][jk]->cd();
  gPad->SetLogx(1);

//  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.325,leg_y1+0.2,text);
//  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.325,leg_y1+0.125,text1);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.35,leg_y1+0.2,text2);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.29,leg_y1+0.125,text);
  if(jk==0){
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.29,leg_y1+0.05,text1);
  }else{
   	latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.35,leg_y1+0.05,text1);
       }
   
   
  tdrDraw(hist_rad_up[0][ij][jk],"][",sty[0],-1,sty[0],col[0],0,2); 

  gr_rad_tot[ij][jk]->SetFillColorAlpha(kPink+2,0.5);
  gr_rad_tot[ij][jk]->SetLineWidth(-2002);
  gr_rad_tot[ij][jk]->SetLineColor(-1);
  gr_rad_tot[ij][jk]->SetFillStyle(1005);
  gr_rad_tot[ij][jk]->SetMaximum(radlim[jk]);
  gr_rad_tot[ij][jk]->SetMinimum(-radlimd[jk]);
  gr_rad_tot[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
  gr_rad_tot[ij][jk]->GetYaxis()->SetLabelSize(0);
  gr_rad_tot[ij][jk]->GetYaxis()->SetTickLength(0);
  gr_rad_tot[ij][jk]->Draw("SAME:E3");
  

  for(int fg=0; fg<nfiles; fg++){

   tdrDraw(hist_rad_up[fg][ij][jk],"][",sty[fg],-1,sty[fg],col[fg],0,2);
   tdrDraw(hist_rad_dn[fg][ij][jk],"][",sty[fg],-1,sty[fg],col[fg],0,2);

   leg_rad[ij][jk]->AddEntry(hist_rad_up[fg][ij][jk],sys_name[fg],"l");
  }

  leg_rad[ij][jk]->AddEntry(gr_rad_tot[ij][jk],"Total","f");

  leg_rad[ij][jk]->Draw();
  gPad->RedrawAxis();

  sprintf(name,"Theory_Sys_Plots_PS/Ratio_Plots/%s.png",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

    }//jk
  }//ij

fp_pt_tot.close();
fp_rad_tot.close();

}
