#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include <fstream>

void Sys_Total()
{
ifstream fp0_pt("Unc_Files/JES_Pt_2016_Legacy_wAK4.log");
ifstream fp1_pt("Unc_Files/JER_Pt_wAK4.log");
ifstream fp2_pt("PU_Pt_excor.log");
//ifstream fp3_pt("RM_Unc_Pt_84.log");
//ifstream fp3_pt("RM_Unc_Pt_P8.log");
//ifstream fp4_pt("Unf_Files/Ex_Cor_84/Unf_Unc_Total_Pt_excor_84.log");
ifstream fp3_pt("Unf_Files/P8Hwg_Unc_Pt.log");
ifstream fp4_pt("Unc_Files/ExCor_Pt.log");
ifstream fp5_pt("StatUnc_Plots/Unc_Pt_Jackknife_Stat_Data.log");//Unc_Pt_Jackknife_Stat.log");
ifstream fp6_pt("StatUnc_Plots/Unc_Pt_Jackknife_Stat_RM.log");
ifstream fp7_pt("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/MINIAOD/Trigger_2016/Trig_Unc_output.log");

/*
ifstream fp4_pt("Refold_Pt.log");
ifstream fp5_pt("Unf_Files/Unfolding_Tech_Err_Pt.log");
ifstream fp6_pt("Unf_Files/Unf_Data_Pt.log");
*/

//ifstream fp0_rad("Unc_Files/JES_Rad_wAK4.log");
ifstream fp0_rad("Unc_Files/JES_Rad_2016_Legacy_wAK4.log");
ifstream fp1_rad("Unc_Files/JER_Rad_wAK4.log");
ifstream fp2_rad("PU_Rad_excor.log");
//ifstream fp3_rad("RM_Unc_Rad_84.log");
//ifstream fp3_rad("RM_Unc_Rad_P8.log");
//ifstream fp4_rad("Unf_Files/Ex_Cor_84/Unf_Unc_Total_Rad_excor_84.log");
ifstream fp3_rad("Unf_Files/P8Hwg_Unc_Rad.log");
ifstream fp4_rad("Unc_Files/ExCor_Rad.log");
ifstream fp5_rad("StatUnc_Plots/Unc_Rad_Jackknife_Stat_Data.log");
ifstream fp6_rad("StatUnc_Plots/Unc_Rad_Jackknife_Stat_RM.log");//Unc_Rad_Jackknife_Stat.log");
ifstream fp7_rad("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/MINIAOD/Trigger_2016/Trig_Unc_output.log");
/*
ifstream fp4_rad("Refold_Rad.log");
ifstream fp5_rad("Unf_Files/Unfolding_Tech_Err_Rad.log");
ifstream fp6_rad("Unf_Files/Unf_Data_Rad.log");
*/

ofstream fptot_pt;
fptot_pt.open("Total_ExpSys_Pt_excor_84.log");
ofstream fptot_rad;
fptot_rad.open("Total_ExpSys_Rad_excor_84.log");

const int nfiles = 8;
int col[nfiles+1] = {6,2,4,/*6,*/7,9,kBlack,kCyan,kOrange+2,kYellow+2};
int sty[nfiles+1] = {1,2,3,/*4,*/5,6,9,1,4,8};
//const char *sys_name[nfiles+1] = {"JES","JER","Pileup","RM Stat","Unfolding", "ExCor"/*"Refold","Unfold Technique Var","Model Var in Unfold"*/,"Total"};
const char *sys_name[nfiles+1] = {"JES","JER","Pileup",/*"RM Stat",*/"R-dependent", "ExCor","Statistical (Data)","Statistical (RM)","Trigger","Total"};

const int nalgo = 12;
const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

//const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* jetname[nalgo] = {"R = 0.1","R = 0.2","R = 0.3","R = 0.4","R = 0.5","R = 0.6","R = 0.7","R = 0.8","R = 0.9","R = 1.0","R = 1.1","R = 1.2"};

const int netarange = 10;
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int noptbins = 62;

double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

char name[100];

float min_range = 84;
float max_range = 1588;

float ptlim[netarange] = {0.35,0.35,0.35,0.4,0.45,0.42,0.5,0.6,0.6,0.6};
float ptlimd[netarange] = {0.21,0.26,0.26,0.3,0.45,0.42,0.5,0.6,0.6,0.6};

float radlim[netarange] = {0.0505,0.0805,0.0805,0.3,0.32,0.4,0.4,0.4,0.4,0.4};
float radlimd[netarange] = {0.0505,0.055,0.055,0.3,0.32,0.4,0.4,0.4,0.4,0.4};

//float radlim[netarange] = {0.255,0.0805,0.0805,0.3,0.32,0.4,0.4,0.4,0.4,0.4};
//float radlimd[netarange] = {0.255,0.055,0.055,0.3,0.32,0.4,0.4,0.4,0.4,0.4};

double pt_err_up[nfiles][nalgo][netarange][noptbins];
double pt_err_dn[nfiles][nalgo][netarange][noptbins];
double rad_err_up[nfiles][nalgo][netarange][noptbins];
double rad_err_dn[nfiles][nalgo][netarange][noptbins];

double pt_err_up_tot[nalgo][netarange][noptbins];
double pt_err_dn_tot[nalgo][netarange][noptbins];
double rad_err_up_tot[nalgo][netarange][noptbins];
double rad_err_dn_tot[nalgo][netarange][noptbins];


TH1D *hist_pt_up[nfiles+1][nalgo][netarange];
TH1D *hist_pt_dn[nfiles+1][nalgo][netarange];
TH1D *hist_rad_up[nfiles+1][nalgo][netarange];
TH1D *hist_rad_dn[nfiles+1][nalgo][netarange];

TGraphAsymmErrors *gr_rad_tot[nalgo][netarange];

TGraphAsymmErrors *stat_pt_data[nalgo][netarange];
TGraphAsymmErrors *stat_rad_data[nalgo][netarange];

TGraphAsymmErrors *stat_pt_RM[nalgo][netarange];
TGraphAsymmErrors *stat_rad_RM[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	  stat_pt_data[ij][jk] = new TGraphAsymmErrors();
	  stat_rad_data[ij][jk] = new TGraphAsymmErrors();
	  stat_pt_RM[ij][jk] = new TGraphAsymmErrors();
	  stat_rad_RM[ij][jk] = new TGraphAsymmErrors();
  }
}

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   sprintf(name,"sys_pt_err_up_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_pt_up[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"sys_pt_err_dn_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_pt_dn[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"sys_rad_err_up_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_rad_up[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

   sprintf(name,"sys_rad_err_dn_File%i_%s_EtaBin%i",fg+1,JetRad[ij],jk+1);
   hist_rad_dn[fg][ij][jk] = new TH1D(name,name,noptbins,ptbins);

   for(int kl=0; kl<noptbins; kl++){
     int xx1,xx2,xx3;

     if(fg==0) {fp0_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl];}
     else if (fg==1) {fp1_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl];}
     else if (fg==2) {fp2_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl];}
     else if (fg==3) {fp3_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl];}      
     else if (fg==4) {fp4_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl]; //}
//     else if (fg==5) {fp5_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl];}
		   //  cout<<xx1<<'\t'<<xx2<<'\t'<<xx3<<'\t'<<pt_err_up[fg][ij][jk][kl]<<endl;
		     if(pt_err_up[fg][ij][jk][kl] > 0.15) { pt_err_up[fg][ij][jk][kl] = 0.15; }
		     if(pt_err_dn[fg][ij][jk][kl] > 0.15) { pt_err_dn[fg][ij][jk][kl] = 0.15; } 
	       	}
	else if (fg==5) {
		fp5_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl];
		stat_pt_data[ij][jk]->SetPoint(kl,1.01*hist_rad_dn[fg][ij][jk]->GetBinCenter(kl+1),0);
		stat_pt_data[ij][jk]->SetPointEYhigh(kl,pt_err_up[fg][ij][jk][kl]);
		stat_pt_data[ij][jk]->SetPointEYlow(kl,pt_err_dn[fg][ij][jk][kl]);
		}
	else if (fg==6) {
		fp6_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl];
		stat_pt_RM[ij][jk]->SetPoint(kl,0.99*hist_rad_dn[fg][ij][jk]->GetBinCenter(kl+1),0);
		stat_pt_RM[ij][jk]->SetPointEYhigh(kl,pt_err_up[fg][ij][jk][kl]);
		stat_pt_RM[ij][jk]->SetPointEYlow(kl,pt_err_dn[fg][ij][jk][kl]);
		}	
	
	else if(fg==7) {fp7_pt>>xx1>>xx2>>xx3>>pt_err_up[fg][ij][jk][kl]>>pt_err_dn[fg][ij][jk][kl];}

      if(pt_err_up[fg][ij][jk][kl]>0.9999) {pt_err_up[fg][ij][jk][kl] = 0.;}
      if(pt_err_dn[fg][ij][jk][kl]>0.9999) {pt_err_dn[fg][ij][jk][kl] = 0.;}

	  if(fg<5||fg>7){
		pt_err_up_tot[ij][jk][kl]+=pow(pt_err_up[fg][ij][jk][kl],2);
		pt_err_dn_tot[ij][jk][kl]+=pow(pt_err_dn[fg][ij][jk][kl],2);
	  }
	  
      hist_pt_up[fg][ij][jk]->SetBinContent(kl+1,pt_err_up[fg][ij][jk][kl]);
      hist_pt_dn[fg][ij][jk]->SetBinContent(kl+1,pt_err_dn[fg][ij][jk][kl]);

     if(fg==0) {fp0_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];}
     else if (fg==1) {fp1_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];}
     else if (fg==2) {fp2_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];}
     else if (fg==3) {fp3_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];}
     else if (fg==4) {fp4_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];//}
					  if(rad_err_up[fg][ij][jk][kl] > 0.15) { rad_err_up[fg][ij][jk][kl] = 0.15; }
					  if(rad_err_dn[fg][ij][jk][kl] > 0.15) { rad_err_dn[fg][ij][jk][kl] = 0.15; }
					  
		     }
	else if (fg==5) {
		fp5_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];
		stat_rad_data[ij][jk]->SetPoint(kl,1.01*hist_rad_dn[fg][ij][jk]->GetBinCenter(kl+1),0);
		stat_rad_data[ij][jk]->SetPointEYhigh(kl,rad_err_up[fg][ij][jk][kl]);
		stat_rad_data[ij][jk]->SetPointEYlow(kl,rad_err_up[fg][ij][jk][kl]);
		stat_rad_data[ij][jk]->SetPointEXhigh(kl,0);
		stat_rad_data[ij][jk]->SetPointEXlow(kl,0);
		 }
	else if (fg==6) {
		fp6_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];
		stat_rad_RM[ij][jk]->SetPoint(kl,0.99*hist_rad_dn[fg][ij][jk]->GetBinCenter(kl+1),0);
		stat_rad_RM[ij][jk]->SetPointEYhigh(kl,rad_err_up[fg][ij][jk][kl]);
		stat_rad_RM[ij][jk]->SetPointEYlow(kl,rad_err_up[fg][ij][jk][kl]);
		stat_rad_RM[ij][jk]->SetPointEXhigh(kl,0);
		stat_rad_RM[ij][jk]->SetPointEXlow(kl,0);
		 }	 
		 
	else if(fg==7) {fp7_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];}	 
		 
/*
     else if (fg==6) {fp6_rad>>xx1>>xx2>>xx3>>rad_err_up[fg][ij][jk][kl]>>rad_err_dn[fg][ij][jk][kl];}
*/

      if(rad_err_up[fg][ij][jk][kl]>0.999) {rad_err_up[fg][ij][jk][kl] = 0.;}
      if(rad_err_dn[fg][ij][jk][kl]>0.999) {rad_err_dn[fg][ij][jk][kl] = 0.;}

	  if(fg<5||fg>6){
       rad_err_up_tot[ij][jk][kl]+=pow(rad_err_up[fg][ij][jk][kl],2);
       rad_err_dn_tot[ij][jk][kl]+=pow(rad_err_dn[fg][ij][jk][kl],2);
	  }
       hist_rad_up[fg][ij][jk]->SetBinContent(kl+1,rad_err_up[fg][ij][jk][kl]);
       hist_rad_dn[fg][ij][jk]->SetBinContent(kl+1,rad_err_dn[fg][ij][jk][kl]);

   }

      hist_pt_dn[fg][ij][jk]->Scale(-1.);
      hist_rad_dn[fg][ij][jk]->Scale(-1.);

      hist_pt_up[fg][ij][jk]->SetMaximum(ptlim[jk]);
      hist_pt_up[fg][ij][jk]->SetMinimum(-ptlimd[jk]);
      hist_pt_dn[fg][ij][jk]->SetMinimum(-ptlimd[jk]);

      hist_pt_up[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

      hist_pt_up[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
      hist_pt_up[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
      hist_pt_up[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
      hist_pt_up[fg][ij][jk]->GetXaxis()->CenterTitle();
      hist_pt_up[fg][ij][jk]->GetXaxis()->SetNoExponent();

      hist_pt_up[fg][ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty in Xsection");
      hist_pt_up[fg][ij][jk]->GetYaxis()->SetTitleSize(0.06);
      hist_pt_up[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.9);
      hist_pt_up[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
      hist_pt_up[fg][ij][jk]->GetYaxis()->CenterTitle();
      hist_pt_up[fg][ij][jk]->GetYaxis()->SetNdivisions(406);

      hist_rad_up[fg][ij][jk]->SetMinimum(-radlimd[jk]);
      hist_rad_up[fg][ij][jk]->SetMaximum(radlim[jk]);
      hist_rad_dn[fg][ij][jk]->SetMinimum(-radlimd[jk]);
      hist_rad_dn[fg][ij][jk]->SetMaximum(radlim[jk]);
      
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
	  hist_rad_dn[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

      hist_rad_up[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)");
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetLabelSize(0.055);
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetTitleOffset(0.9);
      hist_rad_up[fg][ij][jk]->GetXaxis()->CenterTitle();
      hist_rad_up[fg][ij][jk]->GetXaxis()->SetNoExponent();

      hist_rad_up[fg][ij][jk]->GetYaxis()->SetTitle("Relative Uncertainty");// in Ratio of Xsections");
      hist_rad_up[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
      hist_rad_up[fg][ij][jk]->GetYaxis()->SetTitleOffset(5.5);
      hist_rad_up[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
      hist_rad_up[fg][ij][jk]->GetYaxis()->CenterTitle();
      hist_rad_dn[fg][ij][jk]->GetYaxis()->SetTitleOffset(5.5);
      
      hist_rad_up[fg][ij][jk]->GetYaxis()->SetNdivisions(406);
	  hist_rad_dn[fg][ij][jk]->GetYaxis()->SetNdivisions(406);
   }
  }
 }


 TCanvas *c2[nalgo][netarange];
 TLegend *leg_pt[nalgo][netarange];
 TLegend *leg_pt_err[nalgo][netarange];

 TCanvas *c3[nalgo][netarange];
 TLegend *leg_rad[nalgo][netarange];
 TLegend *leg_rad_err[nalgo][netarange];

 double leg_x1 = 0.45;
 double leg_y1 = 0.64;
 double leg_x2 = 0.7;
 double leg_y2 = 0.9;
 
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

  sprintf(name,"sys_pt_err_up_File%i_%s_EtaBin%i",nfiles+1,JetRad[ij],jk+1);
  hist_pt_up[nfiles][ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"sys_pt_err_dn_File%i_%s_EtaBin%i",nfiles+1,JetRad[ij],jk+1);
  hist_pt_dn[nfiles][ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"sys_rad_err_up_File%i_%s_EtaBin%i",nfiles+1,JetRad[ij],jk+1);
  hist_rad_up[nfiles][ij][jk] = new TH1D(name,name,noptbins,ptbins);

  sprintf(name,"sys_rad_err_dn_File%i_%s_EtaBin%i",nfiles+1,JetRad[ij],jk+1);
  hist_rad_dn[nfiles][ij][jk] = new TH1D(name,name,noptbins,ptbins);


  for(int bn=0; bn<noptbins; bn++){
        
        pt_err_up_tot[ij][jk][bn] = sqrt(pt_err_up_tot[ij][jk][bn]);
        pt_err_dn_tot[ij][jk][bn] = sqrt(pt_err_dn_tot[ij][jk][bn]);
        rad_err_up_tot[ij][jk][bn] = sqrt(rad_err_up_tot[ij][jk][bn]);
        rad_err_dn_tot[ij][jk][bn] = sqrt(rad_err_dn_tot[ij][jk][bn]);
        
		hist_pt_up[nfiles][ij][jk]->SetBinContent(bn+1,pt_err_up_tot[ij][jk][bn]);
		hist_pt_dn[nfiles][ij][jk]->SetBinContent(bn+1,pt_err_dn_tot[ij][jk][bn]);
		hist_rad_up[nfiles][ij][jk]->SetBinContent(bn+1,rad_err_up_tot[ij][jk][bn]);
		hist_rad_dn[nfiles][ij][jk]->SetBinContent(bn+1,rad_err_dn_tot[ij][jk][bn]);

      }


  hist_rad_dn[nfiles][ij][jk]->Scale(-1.);
 
  sprintf(name,"Tot_pt_err_%s_EtaBin%i",JetRad[ij],jk+1);
  c2[ij][jk] =  tdrCanvas(name,hist_pt_up[0][ij][jk],7,0);

  if(jk<5){
  leg_pt[ij][jk] =  new TLegend(leg_x1-0.3,leg_y1-0.1,leg_x2,leg_y2);
  }else{
   leg_pt[ij][jk] =  new TLegend(leg_x1+0.3,leg_y1-0.1,leg_x2+0.3,leg_y2);
  }
  leg_pt[ij][jk]->SetBorderSize(0);
  leg_pt[ij][jk]->SetTextSize(0.045);
  leg_pt[ij][jk]->SetTextFont(42);
  if(jk<5){
  leg_pt[ij][jk]->SetTextSize(0.05);
  leg_pt[ij][jk]->SetNColumns(2);
  }

  leg_pt_err[ij][jk] =  new TLegend(leg_x1+0.2,leg_y1+0.05,leg_x2+0.1,leg_y2-0.05);
  leg_pt_err[ij][jk]->SetBorderSize(0);
  leg_pt_err[ij][jk]->SetTextSize(0.05);
  leg_pt_err[ij][jk]->SetTextFont(42);

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

  if(jk<5){
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.025,leg_y1-0.5,text1);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.025,leg_y1-0.425,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.025,leg_y1-0.35,text2);
  }else{
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.4,leg_y1-0.4,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.4,leg_y1-0.475,text1);
  }

  for(int fg=0; fg<(nfiles); fg++){

   hist_pt_up[fg][ij][jk]->Smooth();
   hist_pt_dn[fg][ij][jk]->Smooth();
   
   }

  for(int bn=0; bn<noptbins; bn++){
	
	double errsum_up = 0; double errsum_dn = 0;
	
	for(int fg=0; fg<(nfiles); fg++){
		if(fg>=5 && fg<=6) continue;
		errsum_up += pow(hist_pt_up[fg][ij][jk]->GetBinContent(bn+1),2);
		errsum_dn += pow(hist_pt_dn[fg][ij][jk]->GetBinContent(bn+1),2);
		}
		errsum_up = sqrt(errsum_up);
		errsum_dn = sqrt(errsum_dn);
		hist_pt_up[nfiles][ij][jk]->SetBinContent(bn+1,errsum_up);
		hist_pt_dn[nfiles][ij][jk]->SetBinContent(bn+1,errsum_dn);

	}
  
  hist_pt_dn[nfiles][ij][jk]->Scale(-1.);
  
  for(int fg=0; fg<(1+nfiles); fg++){

   hist_pt_up[fg][ij][jk]->GetYaxis()->SetNdivisions(406);
   hist_pt_dn[fg][ij][jk]->GetYaxis()->SetNdivisions(406);

   hist_pt_up[fg][ij][jk]->SetLineColor(col[fg]);
   hist_pt_up[fg][ij][jk]->SetLineWidth(2);

   hist_pt_dn[fg][ij][jk]->SetLineColor(col[fg]);
   hist_pt_dn[fg][ij][jk]->SetLineWidth(2);

   if(fg<5||fg>6){
   if(fg==7&&ij<8) continue;	   
   tdrDraw(hist_pt_up[fg][ij][jk],"][",sty[fg],-1,sty[fg],col[fg],0,2);
   tdrDraw(hist_pt_dn[fg][ij][jk],"][",sty[fg],-1,sty[fg],col[fg],0,2);
   leg_pt[ij][jk]->AddEntry(hist_pt_up[fg][ij][jk],sys_name[fg],"l");
   }else{
	    if(fg==5){
//		tdrDraw(stat_pt_data[ij][jk],sty[fg],col[fg],sty[fg],col[fg],0,2);
		stat_pt_data[ij][jk]->SetLineWidth(2);
		stat_pt_data[ij][jk]->Draw("SAME:e ][");
        leg_pt_err[ij][jk]->AddEntry(stat_pt_data[ij][jk],sys_name[fg],"e");
		}
		if(fg==6){
        stat_pt_RM[ij][jk]->SetLineWidth(2);
		tdrDraw(stat_pt_RM[ij][jk],"][",sty[fg],col[fg],sty[fg],kRed-2,0,2);
        leg_pt_err[ij][jk]->AddEntry(stat_pt_RM[ij][jk],sys_name[fg],"e");
		}
      }

  }

  leg_pt[ij][jk]->Draw();
  leg_pt_err[ij][jk]->Draw();

  gPad->RedrawAxis();

  sprintf(name,"Total_Sys_Plots/Ex_Cor_84/Pt_Plots/%s.pdf",c2[ij][jk]->GetName());
  c2[ij][jk]->SaveAs(name);

  sprintf(name,"Tot_rad_err_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] =  tdrCanvas(name,hist_rad_up[0][ij][jk],7,0);

  if(jk<5){
  leg_rad[ij][jk] =  new TLegend(leg_x1-0.175,leg_y1,leg_x2,leg_y2);
  leg_rad[ij][jk]->SetNColumns(2);
  
  }else{
  leg_rad[ij][jk] =  new TLegend(leg_x1-0.2,leg_y1-0.1,leg_x2+0.05,leg_y2);
  }
 
  leg_rad[ij][jk]->SetBorderSize(0);
  leg_rad[ij][jk]->SetTextSize(0.05);
  leg_rad[ij][jk]->SetTextFont(42);
  
  leg_rad_err[ij][jk] =  new TLegend(leg_x1+0.05,leg_y1-0.45,leg_x2+0.05,leg_y2-0.55);
  leg_rad_err[ij][jk]->SetBorderSize(0);
  leg_rad_err[ij][jk]->SetTextSize(0.05);
  leg_rad_err[ij][jk]->SetTextFont(42);

  c3[ij][jk]->cd();
  gPad->SetLogx(1);
/*
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
  text1+=  ybinname[jk];
*/

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.35,leg_y1+0.2,text2);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.29,leg_y1+0.125,text);
  if(jk==0){
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.29,leg_y1+0.05,text1);
  }else{
		latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.35,leg_y1+0.05,text1);
	   }


  for(int fg=0; fg<(nfiles+1); fg++){
	  
   hist_rad_up[fg][ij][jk]->SetLineColor(col[fg]);
   hist_rad_dn[fg][ij][jk]->SetLineColor(col[fg]);

   hist_rad_up[fg][ij][jk]->SetLineWidth(2);
   hist_rad_dn[fg][ij][jk]->SetLineWidth(2);
   
   hist_rad_up[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.25);
   hist_rad_dn[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.25);
  
   hist_rad_up[fg][ij][jk]->Smooth();
   hist_rad_dn[fg][ij][jk]->Smooth();
    
  }
  
  for(int bn=0; bn<noptbins; bn++){
	
	double errsum_up = 0; double errsum_dn = 0;
	
	for(int fg=0; fg<(nfiles); fg++){
		if(fg>=5&& fg<=6) continue;
		errsum_up += pow(hist_rad_up[fg][ij][jk]->GetBinContent(bn+1),2);
		errsum_dn += pow(hist_rad_dn[fg][ij][jk]->GetBinContent(bn+1),2);
		}
		errsum_up = sqrt(errsum_up);
		errsum_dn = sqrt(errsum_dn);
		hist_rad_up[nfiles][ij][jk]->SetBinContent(bn+1,errsum_up);
		hist_rad_dn[nfiles][ij][jk]->SetBinContent(bn+1,errsum_dn);

	}

  
  gr_rad_tot[ij][jk] = new TGraphAsymmErrors();
  
  for(int bn=0; bn<(hist_rad_up[nfiles][ij][jk]->GetNbinsX()); bn++){
	  
	  gr_rad_tot[ij][jk]->SetPoint(bn,hist_rad_up[nfiles][ij][jk]->GetBinCenter(bn+1),0);
	  gr_rad_tot[ij][jk]->SetPointEYhigh(bn,hist_rad_up[nfiles][ij][jk]->GetBinContent(bn+1));
	  gr_rad_tot[ij][jk]->SetPointEYlow(bn,fabs(hist_rad_dn[nfiles][ij][jk]->GetBinContent(bn+1)));
	  
	  }
  
  tdrDraw(hist_rad_up[0][ij][jk],"][",-1,-1,sty[0],col[0],0,2);
  
  gr_rad_tot[ij][jk]->SetFillColorAlpha(col[nfiles],0.5);
  gr_rad_tot[ij][jk]->SetLineWidth(-2002);
  gr_rad_tot[ij][jk]->SetLineColor(-1);
  gr_rad_tot[ij][jk]->SetFillStyle(1005);
  gr_rad_tot[ij][jk]->SetMaximum(radlim[jk]);
  gr_rad_tot[ij][jk]->SetMinimum(-radlimd[jk]);
  gr_rad_tot[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
  gr_rad_tot[ij][jk]->GetYaxis()->SetLabelSize(0);
  gr_rad_tot[ij][jk]->GetYaxis()->SetTickLength(0);
  gr_rad_tot[ij][jk]->Draw("SAME:E3");

  gStyle->SetEndErrorSize(0);

  for(int fg=0; fg<(nfiles); fg++){

   if(fg<5||fg>6){
   if(fg==7&&ij<8) continue;
   tdrDraw(hist_rad_up[fg][ij][jk],"][",-1,-1,sty[fg],col[fg],0,2);
   tdrDraw(hist_rad_dn[fg][ij][jk],"][",-1,-1,sty[fg],col[fg],0,2);
   leg_rad[ij][jk]->AddEntry(hist_rad_up[fg][ij][jk],sys_name[fg],"l");  
	}else{
		 if(fg==5){
		 stat_rad_data[ij][jk]->SetLineWidth(2);
		 stat_rad_data[ij][jk]->Draw("SAME:e ][");
		 leg_rad_err[ij][jk]->AddEntry(stat_rad_data[ij][jk],sys_name[fg],"e");
		 }
		 if(fg==6){
		 stat_rad_RM[ij][jk]->SetLineWidth(2);
		 tdrDraw(stat_rad_RM[ij][jk],"][",sty[fg],col[fg],sty[fg],kRed-2,0,2);
		 leg_rad_err[ij][jk]->AddEntry(stat_rad_RM[ij][jk],sys_name[fg],"e");
		 }
	 }
 
  }
  
  leg_rad[ij][jk]->AddEntry(gr_rad_tot[ij][jk],sys_name[nfiles],"f");
  
  leg_rad[ij][jk]->Draw();
  leg_rad_err[ij][jk]->Draw();
  
  gPad->RedrawAxis();

  sprintf(name,"Total_Sys_Plots/Ex_Cor_84/Ratio_Plots/%s.pdf",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//ij
 }//jk

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	for(int bn=1; bn<noptbins; bn++){
	fptot_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn<<'\t'<<pt_err_up_tot[ij][jk][bn]<<'\t'<<pt_err_dn_tot[ij][jk][bn]<<endl;
	fptot_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn<<'\t'<<rad_err_up_tot[ij][jk][bn]<<'\t'<<rad_err_dn_tot[ij][jk][bn]<<endl;
  }
 }
}

fptot_pt.close();
fptot_rad.close();

}

int main()
{
Sys_Total();
}
