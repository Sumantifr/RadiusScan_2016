#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TFile.h>
#include <fstream>
#include <TGraphErrors.h>
#include "TPaletteAxis.h"
#include "TStyle.h"
#include "TPaletteAxis.h"
#include "TStyle.h"

#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

void Stat_Unc_Adder()
{

const int nalgo = 12;
const int netarange = 10;
const int noptbins = 62;

ofstream fp_pt;
fp_pt.open("Unc_Pt_Jackknife_Stat_DataplusRM_84.log");

ofstream fp_rad;
fp_rad.open("Unc_Rad_Jackknife_Stat_DataplusRM_84.log");	

ifstream fp0_pt("StatUnc_Plots/Unc_Pt_Jackknife_Stat_Data.log");
ifstream fp1_pt("StatUnc_Plots/Unc_Pt_Jackknife_Stat_RM.log");

ifstream fp0_rad("StatUnc_Plots/Unc_Rad_Jackknife_Stat_Data.log");
ifstream fp1_rad("StatUnc_Plots/Unc_Rad_Jackknife_Stat_RM.log");

double pt_err_i[2][nalgo][netarange][noptbins];
double rad_err_i[2][nalgo][netarange][noptbins];

double pt_err[nalgo][netarange][noptbins];
double rad_err[nalgo][netarange][noptbins];

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	for(int kl=0; kl<noptbins; kl++){
     int xx1,xx2,xx3;

     fp0_pt>>xx1>>xx2>>xx3>>pt_err_i[0][ij][jk][kl]>>pt_err_i[0][ij][jk][kl];
	 fp1_pt>>xx1>>xx2>>xx3>>pt_err_i[1][ij][jk][kl]>>pt_err_i[1][ij][jk][kl];

	 fp0_rad>>xx1>>xx2>>xx3>>rad_err_i[0][ij][jk][kl]>>rad_err_i[0][ij][jk][kl];
	 fp1_rad>>xx1>>xx2>>xx3>>rad_err_i[1][ij][jk][kl]>>rad_err_i[1][ij][jk][kl];

//	 pt_err[ij][jk][kl] = sqrt(pt_err_i[0][ij][jk][kl]*pt_err_i[0][ij][jk][kl] + pt_err_i[1][ij][jk][kl]*pt_err_i[1][ij][jk][kl]) ;
//	 rad_err[ij][jk][kl] = sqrt(rad_err_i[0][ij][jk][kl]*rad_err_i[0][ij][jk][kl] + rad_err_i[1][ij][jk][kl]*rad_err_i[1][ij][jk][kl]) ;
	 

//	 fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<pt_err[ij][jk][kl]<<'\t'<<pt_err[ij][jk][kl]<<endl;
//	 fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<rad_err[ij][jk][kl]<<'\t'<<rad_err[ij][jk][kl]<<endl;

	}
      for(int kl=1; kl<noptbins; kl++){

	 pt_err[ij][jk][kl] = sqrt(pt_err_i[0][ij][jk][kl]*pt_err_i[0][ij][jk][kl] + pt_err_i[1][ij][jk][kl]*pt_err_i[1][ij][jk][kl]) ;
	 rad_err[ij][jk][kl] = sqrt(rad_err_i[0][ij][jk][kl]*rad_err_i[0][ij][jk][kl] + rad_err_i[1][ij][jk][kl]*rad_err_i[1][ij][jk][kl]) ;

	 fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<kl<<'\t'<<pt_err[ij][jk][kl]<<'\t'<<pt_err[ij][jk][kl]<<endl;
         fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<kl<<'\t'<<rad_err[ij][jk][kl]<<'\t'<<rad_err[ij][jk][kl]<<endl;

	}
  }
 }


}
