#include <iostream>
#include <TH1D.h>
#include <TCanvas.h>
#include <TFile.h>
#include <fstream>

#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

using namespace std;

const int nalgo = 12;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
const char *jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};

const int netarange = 10;
const char *ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"};

const int ncomb = 10;

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int ref_rad = 3;

char name[100];

float leg_x1 = 0.25;
float leg_y1 = 0.6;
float leg_x2 = 0.45;
float leg_y2 = 0.85;

void Sys_RM()
{

//TFile *filein = new TFile("/home/suman/RooUnfold/Unfolded2016_DataStat10.root","read");
//TFile *filein = new TFile("/home/suman/RooUnfold/Unfolded2016_RM10.root","read");
TFile *filein = new TFile("/home/suman/RooUnfold/Stat_Unc_Files/Unfolded_Data_NTuple_MC_P8_Stat.root","read");

TH1D *hist_pt[nalgo][netarange][ncomb];
TH1D *hist_rad[nalgo][netarange][ncomb];

TH1D *hist_pt_nom[nalgo][netarange];
TH1D *hist_rad_nom[nalgo][netarange];

double pt_points[nalgo][netarange][ncomb][noptbins];
double pt_mean[nalgo][netarange][noptbins];
double pt_rms[nalgo][netarange][noptbins];
double pt_stdev[nalgo][netarange][noptbins];

double rad_points[nalgo][netarange][ncomb][noptbins];
double rad_mean[nalgo][netarange][noptbins];
double rad_rms[nalgo][netarange][noptbins];
double rad_stdev[nalgo][netarange][noptbins];

TH1D *rm_unc[nalgo][netarange];
TH1D *rm_rad_unc[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

  sprintf(name,"RM_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
  rm_unc[ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"RM_Rad_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
  rm_rad_unc[ij][jk] = new TH1D(name,name,noptbins,ptbins);

 }
}

ofstream fp_pt;
//fp_pt.open("RM_Unc_Pt_84.log");
fp_pt.open("RM_Unc_Pt_P8_84.log");

ofstream fp_rad;
//fp_rad.open("RM_Unc_Rad_84.log");
fp_rad.open("RM_Unc_Rad_P8_84.log");

filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<ncomb; kl++){
//	sprintf(name,"svd_SVD_unfold_%s_Etabin%i_Comb%i",JetRad[ij],jk+1,kl+1);
//	sprintf(name,"svd_SVD_%s_EtaBin%i_Comb%i",JetRad[ij],jk+1,kl+1);
//	sprintf(name,"bayes_Bayes_%s_EtaBin%i_Comb%i",JetRad[ij],jk+1,kl+1);
	sprintf(name,"svd_unfold_%s_Etabin%i_comb%i",JetRad[ij],jk+1,kl+1);
	hist_pt[ij][jk][kl] = (TH1D*)filein->Get(name);
	for(int bn=0; bn<(hist_pt[ij][jk][kl]->GetNbinsX()); bn++){
		pt_points[ij][jk][kl][bn] = hist_pt[ij][jk][kl]->GetBinContent(bn+1);
	}//bn
   }//kl
  }//jk
 }//ij


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<ncomb; kl++){
        hist_rad[ij][jk][kl] = (TH1D*)hist_pt[ij][jk][kl]->Clone();
	hist_rad[ij][jk][kl]->Divide(hist_pt[ref_rad][jk][kl]);

        for(int bn=0; bn<(hist_rad[ij][jk][kl]->GetNbinsX()); bn++){
                rad_points[ij][jk][kl][bn] = hist_rad[ij][jk][kl]->GetBinContent(bn+1);
        }//bn
   }//kl
  }//jk
 }//ij

/*
TFile *file2 = new TFile("/home/suman/RooUnfold/Unfolded_2016_Data_P8.root","read");
file2->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1);
   hist_pt_nom[ij][jk] = (TH1D*)file2->Get(name);
 }
}

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
  hist_rad_nom[ij][jk] = (TH1D*)hist_pt_nom[ij][jk]->Clone();
  hist_rad_nom[ij][jk]->Divide(hist_pt_nom[ref_rad][jk]);
 }
}
*/
for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
  for(int bn=0; bn<noptbins; bn++){
  
   double sum = 0;
   double sq_sum = 0;

   double rad_sum = 0;  
   double rad_sq_sum = 0;

    for(int kl=0; kl<ncomb; kl++){
  
      sum += pt_points[ij][jk][kl][bn];
      sq_sum += (pt_points[ij][jk][kl][bn]*pt_points[ij][jk][kl][bn]);

      rad_sum += rad_points[ij][jk][kl][bn];
      rad_sq_sum += (rad_points[ij][jk][kl][bn]*rad_points[ij][jk][kl][bn]);
      if(ij==0&&jk==0 && bn==25){
	 cout<<"comb "<<kl+1<<" cont "<<pt_points[ij][jk][kl][bn]<<endl;
	}
     }//kl
   
    pt_mean[ij][jk][bn] = sum*1./(ncomb);
    pt_rms[ij][jk][bn] = sq_sum*1./(ncomb);
    pt_stdev[ij][jk][bn] = sqrt(pt_rms[ij][jk][bn] - (pt_mean[ij][jk][bn]*pt_mean[ij][jk][bn])) ;
    pt_stdev[ij][jk][bn] = sqrt(10./9)*pt_stdev[ij][jk][bn];
    pt_stdev[ij][jk][bn] *= 1./sqrt(2.5);
    if(ij==0&&jk==0 && bn==25){
	cout<<"bin "<<bn+1<<" mean "<<pt_mean[ij][jk][bn]<<" rms "<<pt_rms[ij][jk][bn]<<" stdev "<<pt_stdev[ij][jk][bn]<<" avg stdev "<<pt_stdev[ij][jk][bn]*1./max(1.e-19,pt_mean[ij][jk][bn])<<endl;
	}
      rm_unc[ij][jk]->SetBinContent(bn+1,pt_stdev[ij][jk][bn]*1./max(1.e-19,pt_mean[ij][jk][bn]));

      if(rm_unc[ij][jk]->GetBinContent(bn+1) > (1. - 1.e-6)) {rm_unc[ij][jk]->SetBinContent(bn+1,(1. - 1.e-6)); }

//      if(bn<5) { if(rm_unc[ij][jk]->GetBinContent(bn+1) > 0.2) { rm_unc[ij][jk]->SetBinContent(bn+1,0.2);} }

    if(bn!=0){
//    fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<max(0.,rm_unc[ij][jk]->GetBinContent(bn+1))<<'\t'<<max(0.,rm_unc[ij][jk]->GetBinContent(bn+1))<<endl;
      fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn<<'\t'<<max(0.,rm_unc[ij][jk]->GetBinContent(bn+1))<<'\t'<<max(0.,rm_unc[ij][jk]->GetBinContent(bn+1))<<endl;
    }
//      fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn/*+1*/<<'\t'<<max(0.,rm_unc[ij][jk]->GetBinContent(bn+1))<<'\t'<<max(0.,rm_unc[ij][jk]->GetBinContent(bn+1))<<endl;

    rad_mean[ij][jk][bn] = rad_sum*1./(ncomb);
    rad_rms[ij][jk][bn] = rad_sq_sum*1./(ncomb);
    rad_stdev[ij][jk][bn] = sqrt(rad_rms[ij][jk][bn] - (rad_mean[ij][jk][bn]*rad_mean[ij][jk][bn])) ;//
    rad_stdev[ij][jk][bn] = sqrt(10./9) * rad_stdev[ij][jk][bn];
    rad_stdev[ij][jk][bn] *= 1./sqrt(2.5);    

//    rm_rad_unc[ij][jk]->SetBinContent(bn+1,rad_stdev[ij][jk][bn]*0.9/max(1.e-6,hist_rad[ij][jk]->GetBinContent(bn+1)));
    rm_rad_unc[ij][jk]->SetBinContent(bn+1,rad_stdev[ij][jk][bn]*1./max(1.e-19,rad_mean[ij][jk][bn]));

    if(rm_rad_unc[ij][jk]->GetBinContent(bn+1) > (1. - 1.e-6)) {rm_rad_unc[ij][jk]->SetBinContent(bn+1,(1. - 1.e-6)); }
    if(bn!=0){
//    fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<max(0.,rm_rad_unc[ij][jk]->GetBinContent(bn+1))<<'\t'<<max(0.,rm_rad_unc[ij][jk]->GetBinContent(bn+1))<<endl;
	fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn<<'\t'<<max(0.,rm_rad_unc[ij][jk]->GetBinContent(bn+1))<<'\t'<<max(0.,rm_rad_unc[ij][jk]->GetBinContent(bn+1))<<endl;
	}
    }
    rm_unc[ij][jk]->Scale(100);
    rm_rad_unc[ij][jk]->Scale(100);
   }
 }

fp_pt.close();
fp_rad.close();

TCanvas *c2[nalgo][netarange];
TGraphErrors *gr_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   rm_unc[ij][jk]->Smooth();

   sprintf(name,"Canvas_RM_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
   c2[ij][jk] = tdrCanvas(name,rm_unc[ij][jk],7,0);

   double yy[noptbins] = {0};
   double yyerr[noptbins] = {0};

   for(int bn=0; bn<(rm_unc[ij][jk]->GetNbinsX()); bn++){
	yyerr[bn] = rm_unc[ij][jk]->GetBinContent(bn+1);
   }

   sprintf(name,"Pt_Error_%s_EtaBin%i",JetRad[ij],jk+1);
   gr_pt[ij][jk] = new TGraphErrors(noptbins,ptbins,yy,NULL,yyerr);

   c2[ij][jk]->cd();

   gPad->SetLogx(1);

   gr_pt[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
   gr_pt[ij][jk]->GetXaxis()->SetTitleSize(0.06);
   gr_pt[ij][jk]->GetXaxis()->CenterTitle();
   gr_pt[ij][jk]->GetXaxis()->SetLabelSize(0.05);
   gr_pt[ij][jk]->GetXaxis()->SetNdivisions(510);

   gr_pt[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection(in %)");
   gr_pt[ij][jk]->GetYaxis()->SetTitleSize(0.06);
   gr_pt[ij][jk]->GetYaxis()->CenterTitle();
   gr_pt[ij][jk]->GetYaxis()->SetLabelSize(0.05);
   gr_pt[ij][jk]->GetYaxis()->SetTitleOffset(1.05);

   gr_pt[ij][jk]->SetMaximum(10.1);
   gr_pt[ij][jk]->SetMinimum(-10.1);

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

   gr_pt[ij][jk]->GetXaxis()->SetRangeUser(84,1500.);
//   tdrDraw(rm_unc[ij][jk],kLine,5,kSolid,kYellow+2,4005,kYellow+2);

   gr_pt[ij][jk]->SetMarkerStyle(kFullCircle);
   gr_pt[ij][jk]->SetMarkerColor(kBlack);
   gr_pt[ij][jk]->SetLineColor(kBlue);
   gr_pt[ij][jk]->SetLineWidth(-2002);
   gr_pt[ij][jk]->SetFillStyle(3004);
   gr_pt[ij][jk]->SetFillColor(kBlue);

   gr_pt[ij][jk]->Draw("AP");
   gr_pt[ij][jk]->Draw("SAME:E3");

   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.125,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.05,text1);

   sprintf(name,"RM_Plots/Pt_Plots/%s.png",c2[ij][jk]->GetName());
   c2[ij][jk]->SaveAs(name);
 }
}

TCanvas *c3[nalgo][netarange];
TGraphAsymmErrors *gr_rad[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   rm_rad_unc[ij][jk]->Smooth();
 
   sprintf(name,"Canvas_Rad_RM_Unc_%s_EtaBin%i",JetRad[ij],jk+1);
   c3[ij][jk] = tdrCanvas(name,rm_rad_unc[ij][jk],7,0);

   double yy[noptbins] = {0};
   double yyerr[noptbins] = {0};
   double yyerrl[noptbins] = {0};

   for(int bn=0; bn<(rm_rad_unc[ij][jk]->GetNbinsX()); bn++){
        yyerr[bn] = rm_rad_unc[ij][jk]->GetBinContent(bn+1);
        yyerrl[bn] = -1.*yyerr[bn];
   }

   sprintf(name,"Rad_Error_%s_EtaBin%i",JetRad[ij],jk+1);
   gr_rad[ij][jk] = new TGraphAsymmErrors(noptbins,ptbins,yy,NULL,NULL,yyerr,yyerr);

   c3[ij][jk]->cd();

   gPad->SetLogx(1);

   gr_rad[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
   gr_rad[ij][jk]->GetXaxis()->SetTitleSize(0.05);
   gr_rad[ij][jk]->GetXaxis()->CenterTitle();
   gr_rad[ij][jk]->GetXaxis()->SetLabelSize(0.05);

   gr_rad[ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection Ratio (in %)");
   gr_rad[ij][jk]->GetYaxis()->SetTitleSize(0.05);
   gr_rad[ij][jk]->GetYaxis()->CenterTitle();
   gr_rad[ij][jk]->GetYaxis()->SetLabelSize(0.05);
   gr_rad[ij][jk]->GetYaxis()->SetTitleOffset(1.05);

   gr_rad[ij][jk]->SetMaximum(10.1);
   gr_rad[ij][jk]->SetMinimum(-10.1);

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
   text1+= ybinname[jk];

   gr_rad[ij][jk]->GetXaxis()->SetRangeUser(80,1500.);
//   tdrDraw(rm_rad_unc[ij][jk],kLine,5,kSolid,kYellow+2,4005,kYellow+2);

   gr_rad[ij][jk]->SetMarkerStyle(kFullSquare);
   gr_rad[ij][jk]->SetMarkerColor(kBlack);
   gr_rad[ij][jk]->SetLineColor(kRed);
   gr_rad[ij][jk]->SetFillStyle(3005);
   gr_rad[ij][jk]->SetLineWidth(-2002);
   gr_rad[ij][jk]->SetFillColor(kRed);

   gr_rad[ij][jk]->Draw("AP");
   gr_rad[ij][jk]->Draw("SAME:E3");

   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.125,text);
   latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.05,text1);

   sprintf(name,"RM_Plots/Ratio_Plots/%s.png",c3[ij][jk]->GetName());
   c3[ij][jk]->SaveAs(name);
 }
}

}

int main()
{
Sys_RM();
}
