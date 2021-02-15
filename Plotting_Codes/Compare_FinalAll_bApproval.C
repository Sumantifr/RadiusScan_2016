//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include <fstream>
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TAxis.h"

TString cmsText1     = "CMS";
float cmsTextFont1   = 61;

TString extraText1     = "Preliminary";
float extraTextFont1   = 52;

float lumiTextSize1     = 0.055;
float lumiTextOffset1   = 0.2;
float cmsTextSize1      = 0.06;
float cmsTextOffset1    = 0.1;

TString lumi_13TeV_2016 = "< 35.9 fb^{-1} (13 TeV)";

TString lumi_13TeV_2016_BCD = "12.6 fb^{-1} (13 TeV)";
TString lumi_13TeV_2016_EF = "7.1 fb^{-1} (13 TeV)";
TString lumi_13TeV_2016_GH = "16.1 fb^{-1} (13 TeV)";

//#define TUnfold

Double_t f1(Double_t* x, Double_t* par){
	return  par[0];
}

const int nfiles = 9;

const char *filenames[nfiles] = {//"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_Legacy_TUnfold.root",
	"/home/suman/RooUnfold/Final/Unfolded_2016_Data_NTuple_MC_P8_Legacy_new_excor.root",
//	"/home/suman/RooUnfold/Data_Legacy_V10_All.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15_new_excor.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_Pythia_Userhook2_NNPDF30.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/HerwigEE5C_Files.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/CP5_tune/hist_Powheg_Pythia_LHAPDF_CP5.root",
//	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Herwig7/hist_Herwig7_weighted.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Herwig7/CMSSample/Hist_CMSStyle_final_CMS1027.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/CT14nlo_files.root"};
/*
const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_excorfac2.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_excor.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/Bin84_hist_Powheg_Pythia_Userhook2_NNPDF30.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/Bin84_HerwigEE5C_Files.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/CP5_tune/Bin84_hist_Powheg_Pythia_LHAPDF_CP5.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Herwig7/Bin84_hist_Herwig7_weighted.root",
	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Bin84_CT14nlo_files.root"};
*/
//ifstream fp_pt_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/Total_ExpSys_Pt_nounf_84.log");
//ifstream fp_rad_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_ExpSys_Rad_nounf_84.log");
ifstream fp_pt_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/Total_ExpSys_Pt_excor_trig_84.log");
ifstream fp_rad_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/Total_ExpSys_Rad_excor_trig_84.log");

ifstream fp_pt_th("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/Total_Theory_Unc_Pt_84.log");
ifstream fp_rad_th("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/Total_Theory_Unc_Rad_84.log");

ifstream fp_pt_stat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/StatUnc_Plots/Unc_Pt_Jackknife_Stat_DataplusRM_84.log");
ifstream fp_rad_stat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/StatUnc_Plots/Unc_Rad_Jackknife_Stat_DataplusRM_84.log");

/*
ifstream fp_pt_stat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/Stat_Unc_Pt_84_RefAK4.log");
ifstream fp_rad_stat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/Stat_Unc_Rad_84_RefAK4.log");

ifstream fp_pt_rmstat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/RM_Unc_Pt_P8_84.log");
ifstream fp_rad_rmstat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/RM_Unc_Rad_P8_84.log");
*/
const int ref_rad = 3;

const char *model_name[nfiles] = {"Data 2016","Pythia8(CUETP8M1)","Madgraph","Herwig++(CUETHss1)","PH+P8(CUETP8M1)","PH+Hwg(EE5C)","PH+P8(CP5)","Herwig7","NLO#otimesNP"};
const char *model_name_rad[nfiles] = {"Data 2016","Pythia8(CUETP8M1)","Madgraph","Herwig++(CUETHss1)","PH+P8(CUETP8M1)","PH+Hwg(EE5C)","PH+P8(CP5)","Herwig7","LO#otimesNP"};
const char *mc_name[nfiles] = {"Data","P8","MG","Hwg","PHP8_CUET","PHHwg","PHP8_CP5","H7","FNLO"};
/*
const int col[nfiles] = {1,6,2,4,3,9,kRed-6,12,kCyan+3};
const int mark_sty[nfiles] = {20,21,22,23,24,25,30,27,26};
*/
const int col[nfiles] = {1,kRed,kGray+1,kBlue,kMagenta+1,kCyan+2,12,kGreen+4,kBlack};
const int mark_sty[nfiles] = {20,kFullTriangleDown,kOpenDiamond,kFullTriangleUp,kOpenTriangleDown,kOpenTriangleUp,kOpenTriangleDown,kFullStar,kOpenSquare};

static const int nalgo = 12;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
//const char* jetname_mod[nalgo] = {"ak1chs-0.75","ak2chs-0.5","ak3chs-0.25","ak4chs","ak5chs+0.25","ak6chs+0.5","ak7chs+0.75","ak8chs+1.0","ak9chs+1.25","ak10chs+1.5","ak11chs+1.75"/*,"ak12chs"*/};
const char* jetname_mod[nalgo] = {"R=0.1 (-0.75)","R=0.2 (-0.5)","R=0.3 (-0.25)","R=0.4","R=0.5 (+0.25)","R=0.6 (+0.5)","R=0.7 (+0.75)","R=0.8 (+1.0)","R=0.9 (+1.25)","R=1.0 (+1.5)","R=1.1 (+1.75)"/*,"R=1.2 (-0.75)"*/};
const char *jetnamen[nalgo] = {"R=0.1","R=0.2","R=0.3","R=0.4","R=0.5","R=0.6","R=0.7","R=0.8","R=0.9","R=1.0","R=1.1","R=1.2"};

const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int algo_col[nalgo] = {2,3,4,6,7,11,kCyan+2,kSpring-7, kBlue-7, kMagenta-9, kRed-5, kYellow-6};//{2,3,4,5,*/6,7,9,12,28,37,44,49};
const int algo_sty[nalgo] = {2,3,4,5,8,21,22,23,25,26,27,28};

static const float_t min_rad[nalgo] = {0.1,0.475,0.7,0.7,1.,1.,1.1,1.2,1.3,1.3,1.3,1.3};
static const float_t max_rad[nalgo] = {1.05,1.05,1.1,1.5,1.3,1.6,1.8,2.2,2.75,3.,3.5,3.5};

/*
const int algo_style[nfiles] = {20,23,22,21,24,25,30,27,26};
const int line_sty[nfiles] = {kSolid,kDotted,kDotted,kDotted,kDashed,kDashed,kDashed,kDashed,kSolid};
*/
const int algo_style[nfiles] = {20,kFullTriangleDown,kOpenDiamond,kFullTriangleUp,kOpenTriangleDown,kOpenTriangleUp,kOpenTriangleDown,kFullStar,kOpenSquare};
const int line_sty[nfiles] = {kSolid,kDotted,kDotted,kDotted,kDashed,kDashed,kDashed,kDashDotted,kSolid};

const int onelinecol = kOrange;

const char *error_name[3] = {"Statistical Error","Exp Sys","Exp+Theory Sys"};
const char* err_name[2] = {"Exp Sys","Theory Sys"};
const char* ref_err_name[2] = {"Exp Sys (R=0.4)","Theory Sys (R=0.4)"};
/*
const int noptbins = 31;
double ptbins[noptbins+1] = {74,97,133,174,220,272,330,395,468,548,638,737,846,967,1101,1248,1410,1588,1784,2000,2238,2500,2787,3103,3450,3832,4252,4713,5220,5777,6389,7000};
*/
const int noptbins = 61;
double ptbins[noptbins+1] = { 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

//double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64, 74,*/ 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int nopbins = 10;
double pbins[nopbins+1]={74, 97, 133, 196, 272, 330, 395, 468, 548, 638, 1588.0};
//const char* pbin_name[nopbins] = {"74 < P_{T}(in GeV) < 97","97 < P_{T}(in GeV) < 133", "133 < P_{T}(in GeV) < 220", "220 < P_{T}(in GeV) < 272", "272 < P_{T}(in GeV) < 330","330 < P_{T}(in GeV) < 395","395 < P_{T}(in GeV) < 468","468 < P_{T}(in GeV) < 548","548 < P_{T}(in GeV) < 638","P_{T}(in GeV) > 638"} ;
const char* pbin_name[nopbins] = {"74 < p_{T} < 97 GeV","97 < p_{T} < 133 GeV","133 < p_{T} < 196 GeV","196 < p_{T} < 272 GeV","272 < p_{T} < 330 GeV","330 < p_{T} < 395 GeV","395 < p_{T} < 468 GeV","468 < p_{T} < 548 GeV","548 < p_{T} < 638 GeV","p_{T} > 638 GeV"};

double ymax[netarange] = {1.9,1.9,1.9,1.9,2.1,3.,3.,3.,3.,3.} ;

const char *unf_title[2] = {"Bayesian","Bayesian"};

double max_range = 1588.;
double min_range = 84.;

char name[1000];

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

void Compare_FinalAll(TH1D *hist_pt[nfiles][nalgo][netarange], TH1D *hist_pt_rat[nfiles-1][nalgo][netarange],
TH1D *hist_radius[nfiles][nalgo][netarange], TH1D *hist_radius_rat[nfiles-1][nalgo][netarange],
TGraphAsymmErrors *gr_pt_err_stat[nalgo][netarange],TGraphAsymmErrors *gr_pt_err_exp[nalgo][netarange],TGraphAsymmErrors *gr_pt_err_th[nalgo][netarange], TGraphAsymmErrors *gr_pt_err_expth[nalgo][netarange],
TGraphAsymmErrors *gr_rad_err_stat[nalgo][netarange],TGraphAsymmErrors *gr_rad_err_exp[nalgo][netarange],TGraphAsymmErrors *gr_rad_err_th[nalgo][netarange], TGraphAsymmErrors *gr_rad_err_expth[nalgo][netarange])
{

cout<<hist_pt[0][3][0]->GetName()<<endl;
	
TString cmsText     = "  CMS";
TString extraText   = "Preliminary";
float cmsTextFont   = 61;

float lumiTextSize     = 0.055;
float lumiTextOffset   = 0.2;
float cmsTextSize      = 0.06;
float cmsTextOffset    = 0.1;

TString lumi_13TeV_2016 = "< 35.9 fb^{-1} (13 TeV)";	
/// Pt spectra and Ratio Comparison in each Eta bin ///
TLine *line = new TLine(min_range,1,max_range,1.);
line->SetLineColor(onelinecol);

TCanvas *c1_pt[nalgo][netarange];

TLegend *leg_pt[nalgo][netarange];
TLegend *leg_errpt[nalgo][netarange];
TLegend *leg2_errrad[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

if(ij<2&&jk>5) continue;

sprintf(name,"Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
c1_pt[ij][jk] = tdrmyDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],2.5,7,0);

leg_pt[ij][jk] = tdrLeg(0.58,0.7,0.9,0.935);
leg_errpt[ij][jk] = tdrLeg(0.35,0.25,0.55,0.325);
leg_errpt[ij][jk]->SetTextSize(0.0325);
leg_errpt[ij][jk]->SetTextFont(42);

c1_pt[ij][jk]->cd(1);

  gPad->SetLogx(1);
  gPad->SetLogy(1);

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

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.125,text1);


 for(int fg=1; fg<(nfiles); fg++){
 
      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC / Data");
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.075);
      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.7);
      
      hist_pt_rat[fg-1][ij][jk]->SetMinimum(0);
	  hist_pt_rat[fg-1][ij][jk]->SetMaximum(2.25);

	  hist_pt_rat[fg-1][ij][jk]->SetLineColor(col[fg]);
	  hist_pt_rat[fg-1][ij][jk]->SetMarkerStyle(algo_style[fg]);
	  hist_pt_rat[fg-1][ij][jk]->SetMarkerColor(col[fg]);
	}

  for(int fg=0; fg<(nfiles); fg++){
      tdrDraw(hist_pt[fg][ij][jk],algo_style[fg],col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"lp");
    }
  
 leg_pt[ij][jk]->SetTextSize(0.035);
 leg_pt[ij][jk]->SetTextFont(42);

 c1_pt[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);


hist_pt_rat[0][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
hist_pt_rat[0][ij][jk]->Draw("e");

gr_pt_err_exp[ij][jk]->SetFillColor(kYellow+1);//Alpha(5,0.9);
gr_pt_err_exp[ij][jk]->SetFillStyle(1002);//3005);
gr_pt_err_exp[ij][jk]->SetLineWidth(-2002);
gr_pt_err_exp[ij][jk]->Draw("SAME:E3");

gr_pt_err_stat[ij][jk]->SetFillColor(1);
gr_pt_err_stat[ij][jk]->SetFillStyle(3005);
gr_pt_err_stat[ij][jk]->SetLineWidth(-2002);
gr_pt_err_stat[ij][jk]->Draw("SAME:EZ");

gr_pt_err_expth[ij][jk]->SetFillColor(kOrange+10);//Alpha(5,0.9);
gr_pt_err_expth[ij][jk]->SetFillStyle(3004);
gr_pt_err_expth[ij][jk]->SetLineWidth(-2002);
gr_pt_err_expth[ij][jk]->Draw("SAME:E3");


leg_errpt[ij][jk]->AddEntry(gr_pt_err_stat[ij][jk],error_name[0],"lep");
leg_errpt[ij][jk]->AddEntry(gr_pt_err_exp[ij][jk],error_name[1],"f");
leg_errpt[ij][jk]->AddEntry(gr_pt_err_expth[ij][jk],error_name[2],"f");

for(int fg=0; fg<(nfiles-1); fg++){
  hist_pt_rat[fg][ij][jk]->Draw("sames"); 
 }

line->Draw();

//sprintf(name,"All_Final/TUnfold_Legacy/Pt_Plots/%s.pdf",c1_pt[ij][jk]->GetName());
sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/Bayesian/Pt_Plots_H7/%s.pdf",c1_pt[ij][jk]->GetName());
c1_pt[ij][jk]->SaveAs(name);

  }//jk
 }//ij


TCanvas *c1_radius[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];
TLegend *leg_radius_err[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   if((ij<2)&&(jk>6)) continue;

  sprintf(name,"RadRat_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c1_radius[ij][jk] = tdrDiCanvas(name,hist_radius[0][ij][jk],hist_radius[1][ij][jk],7,0);

  leg_radius[ij][jk] = tdrLeg(0.55,0.65,0.925,0.925);
  leg_radius_err[ij][jk] = tdrLeg(0.35,0.225,0.55,0.3);

  leg_radius_err[ij][jk]->SetTextSize(0.0325);
  leg_radius_err[ij][jk]->SetTextFont(42);
 
  c1_radius[ij][jk]->cd(1);
  
  gPad->SetLogx(1);
  gPad->SetLogy(0);

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

  leg_x1 = 0.3;
  leg_x2 = 0.7;
  leg_y1 = 0.85;

  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1-0.125,text1);

  for(int fg=0; fg<nfiles; fg++){
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);

      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC / Data");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.075);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.8);

      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.3);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(2.1);

	  hist_radius_rat[fg-1][ij][jk]->SetMarkerStyle(algo_style[fg]);
	  hist_radius_rat[fg-1][ij][jk]->SetMarkerColor(col[fg]);
        }

      hist_radius[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

      tdrDraw(hist_radius[fg][ij][jk],algo_style[fg],col[fg],kSolid,col[fg],1001,2);
      leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name_rad[fg],"lp");
    }

   leg_radius[ij][jk]->SetTextSize(0.035);
   leg_radius[ij][jk]->SetTextFont(42);
 
   c1_radius[ij][jk]->cd(2);

   gPad->SetLogx(1);
   gPad->SetLogy(0);

  hist_radius_rat[0][ij][jk]->Draw("hist");

  gr_rad_err_stat[ij][jk]->SetFillColor(5);
  gr_rad_err_stat[ij][jk]->SetFillStyle(3010);
  gr_rad_err_stat[ij][jk]->Draw("SAME:EZ");
 
  gr_rad_err_exp[ij][jk]->SetFillColor(5);
  gr_rad_err_exp[ij][jk]->SetFillStyle(3010);
  gr_rad_err_exp[ij][jk]->Draw("SAME:E3");
  leg_radius_err[ij][jk]->AddEntry(gr_rad_err_exp[ij][jk],error_name[1],"f");
  
  gr_rad_err_expth[ij][jk]->SetFillColor(kOrange+10);
  gr_rad_err_expth[ij][jk]->SetFillStyle(3010);
  gr_rad_err_expth[ij][jk]->Draw("SAME:E3");
  leg_radius_err[ij][jk]->AddEntry(gr_rad_err_expth[ij][jk],error_name[2],"f");

   for(int fg=0; fg<(nfiles-1); fg++){
   hist_radius_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
   hist_radius_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);   

   if(fg==0){
         hist_radius_rat[fg][ij][jk]->Draw("sames");
   }else{
         hist_radius_rat[fg][ij][jk]->Draw("sames");
	}

   }

  line->Draw();

//  sprintf(name,"All_Final/TUnfold_Legacy/Radius_Plots/%s.pdf",c1_radius[ij][jk]->GetName());
  sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/Bayesian/Radius_Plots_H7/%s.pdf",c1_radius[ij][jk]->GetName());
  c1_radius[ij][jk]->SaveAs(name);

  }//jk
 }//ij

TCanvas *c1_ptrat[nalgo][netarange];
TLegend *leg_ptrat[nalgo][netarange];
TLegend *leg_ptrat_err[nalgo][netarange];

TLatex cms_latex1;
TLatex cms_latex11;
TLatex cms_lumi1;

cms_latex1.SetNDC();
cms_latex1.SetTextFont(cmsTextFont);
cms_latex1.SetTextAlign(31);
cms_latex1.SetTextSize(cmsTextSize);
cms_latex1.SetTextAngle(0);

cms_latex11.SetNDC();
cms_latex11.SetTextFont(52);
cms_latex11.SetTextAlign(21);
cms_latex11.SetTextSize(cmsTextSize);
cms_latex11.SetTextAngle(0);

cms_lumi1.SetNDC();
cms_lumi1.SetTextFont(42);
cms_lumi1.SetTextAlign(31);
cms_lumi1.SetTextSize(lumiTextSize);
cms_lumi1.SetTextAngle(0);

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

 if(ij<2&&jk>5) continue;

  for(int fg=0; fg<(nfiles-1); fg++){ 
  hist_pt_rat[fg][ij][jk]->SetMaximum(3.2);
  } 

  sprintf(name,"Canv_Pt_Ratio_%s_EtaBin%i",JetRad[ij],jk+1);
  c1_ptrat[ij][jk] = tdrCanvas(name,hist_pt_rat[1][ij][jk],7,0);
 
  leg_ptrat[ij][jk] = tdrLeg(0.15,0.575,0.45,0.895);
  leg_ptrat[ij][jk]->SetTextFont(42);
  leg_ptrat[ij][jk]->SetTextSize(0.045); 
 
  leg_ptrat_err[ij][jk] = tdrLeg(0.5,0.55,0.7,0.7);
  leg_ptrat_err[ij][jk]->SetTextFont(42);
  leg_ptrat_err[ij][jk]->SetTextSize(0.035);

  c1_ptrat[ij][jk]->cd();
  gPad->SetLogx(1);

  hist_pt_rat[0][ij][jk]->Draw("e");
 
  gr_pt_err_exp[ij][jk]->Draw("SAME:E3");

 gr_pt_err_stat[ij][jk]->Draw("SAME:EZ");

//  gr_pt_err_th[ij][jk]->Draw("SAME:E3");
   gr_pt_err_expth[ij][jk]->Draw("SAME:E3");

  leg_ptrat_err[ij][jk]->AddEntry(gr_pt_err_stat[ij][jk],error_name[0],"lep");
  leg_ptrat_err[ij][jk]->AddEntry(gr_pt_err_exp[ij][jk],error_name[1],"f");
  leg_ptrat_err[ij][jk]->AddEntry(gr_pt_err_expth[ij][jk],error_name[2],"f");

  for(int fg=0; fg<(nfiles-1); fg++){

   hist_pt_rat[fg][ij][jk]->SetStats(0);
   hist_pt_rat[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_pt_rat[fg][ij][jk]->GetYaxis()->SetTitleSize(0.06);
   hist_pt_rat[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.9);

//   hist_pt_rat[fg][ij][jk]->Draw("sames"); 
   tdrDraw(hist_pt_rat[fg][ij][jk],mark_sty[fg+1],col[fg+1],kSolid,col[fg+1] ,1001,2);
   leg_ptrat[ij][jk]->AddEntry(hist_pt_rat[fg][ij][jk],model_name[fg+1],"lp");
   }

  line->Draw();

  leg_ptrat[ij][jk]->Draw();
  leg_ptrat_err[ij][jk]->Draw();

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.06);

  TString text;
  text+= jetnamen[ij];
  TString text1;
  text1+=  ybinname[jk];

 // cout<<0.5*(leg_x1+leg_x2)<<endl;

  latex.DrawLatex(0.905,0.845,"Anti-k_{T} CHS");
  latex.DrawLatex(0.905,0.78,text);
  latex.DrawLatex(0.905,0.72,text1);

  float l = gPad->GetLeftMargin();
  float t = gPad->GetTopMargin();
  float r = gPad->GetRightMargin();

  cms_latex1.DrawLatex(l+0.02,1-t+0.025,cmsText);
  cms_lumi1.DrawLatex(1-r,1-t+0.025,lumi_13TeV_2016);
  cms_latex11.DrawLatex(l+0.14,1-t+0.025,extraText);

//  sprintf(name,"All_Final/TUnfold_Legacy/PtRatio_Plots/%s.pdf",c1_ptrat[ij][jk]->GetName());
  sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/Bayesian/PtRatio_Plots_H7/%s.pdf",c1_ptrat[ij][jk]->GetName());
  c1_ptrat[ij][jk]->SaveAs(name);

  }
 }

}

void Compare_FinalUnfoldedRat(TH1D *hist_pt[nfiles][nalgo][netarange], TH1D *hist_pt_rat[nfiles-1][nalgo][netarange],
TH1D *hist_radius[nfiles][nalgo][netarange], TH1D *hist_radius_rat[nfiles-1][nalgo][netarange],
TGraphAsymmErrors *gr_pt_err_stat[nalgo][netarange],TGraphAsymmErrors *gr_pt_err_exp[nalgo][netarange],TGraphAsymmErrors *gr_pt_err_th[nalgo][netarange],
TGraphAsymmErrors *gr_rad_err_stat[nalgo][netarange],TGraphAsymmErrors *gr_rad_err_exp[nalgo][netarange],TGraphAsymmErrors *gr_rad_err_th[nalgo][netarange])
{
TCanvas *c2_ptrat[nfiles-1][netarange];
TLegend *leg2_ptrat[nfiles-1][netarange];

TH1D *hist_dummy_radius[nfiles][nalgo][netarange];

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

	double add_fac = (ij - ref_rad) * 0.25;
	for(int bn=0; bn<hist_radius[fg][ij][jk]->GetNbinsX(); bn++){
        hist_radius[fg][ij][jk]->SetBinContent(bn+1,hist_radius[fg][ij][jk]->GetBinContent(bn+1) + add_fac);
	}

	hist_radius[fg][ij][jk]->SetMinimum(-0.75);
    hist_radius[fg][ij][jk]->SetMaximum(6.6);

	hist_dummy_radius[fg][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
	hist_dummy_radius[fg][ij][jk]->SetMarkerSize(1);
	hist_dummy_radius[fg][ij][jk]->SetLineWidth(2);
	hist_dummy_radius[fg][ij][jk]->SetMarkerStyle(algo_sty[ij]);
	hist_dummy_radius[fg][ij][jk]->SetMarkerColor(algo_col[ij]);
	hist_dummy_radius[fg][ij][jk]->SetLineColor(algo_col[ij]);
  }
 }
}

for(int fg=0; fg<(nfiles-1); fg++){
  for(int jk=0; jk<netarange; jk++){
	sprintf(name,"PtRatio_AllRad_Canv_EtaBin%i_%s",jk+1,mc_name[fg+1]);
    c2_ptrat[fg][jk] = tdrCanvas(name,hist_pt_rat[0][ref_rad][jk],7,0);

	leg2_ptrat[fg][jk] = tdrLeg(0.6,0.5,0.95,0.9);
	leg2_ptrat[fg][jk]->SetTextSize(0.04);
	leg2_ptrat[fg][jk]->SetTextFont(42);
	
	c2_ptrat[fg][jk]->cd(1);
	gPad->SetLogx(1);
	gPad->SetLogy(0);

	TLatex latex;
	latex.SetNDC();
	latex.SetTextAngle(0);
	latex.SetTextColor(kBlack);

	latex.SetTextFont(42);
	latex.SetTextAlign(31);
	latex.SetTextSize(0.06);

  //TString text;
  //text+= jetname[ij];
	TString text1;
	text1+=  ybinname[jk];

	 latex.DrawLatex(0.5*(leg_x1+leg_x2),leg_y1,text1);
	 
	 for(int ij=0; ij<nalgo; ij++){
      tdrDraw(hist_pt_rat[fg][ij][jk],algo_sty[ij],algo_col[ij],1,algo_col[ij],1001,0);
      leg2_ptrat[fg][jk]->AddEntry(hist_pt_rat[fg][ij][jk],jetname[ij],"lp");
	 }
	 
//	 sprintf(name,"All_Final/TUnfold_Legacy/RCombined/PtRatio/%s.pdf",c2_ptrat[fg][jk]->GetName());
	 sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/Bayesian/RCombined/PtRatio/%s.pdf",c2_ptrat[fg][jk]->GetName());
	 c2_ptrat[fg][jk]->SaveAs(name);
	}//jk
  }//mc


leg_x1 = 0.3;
leg_x2 = 0.7;
leg_y1 = 0.85;

TCanvas *c2_rad[nfiles-1][netarange];
TLegend *leg2_rad[nfiles-1][netarange];
TLegend *leg2_err[nfiles-1][netarange];
TLegend *leg2_mc[netarange];

for(int fg=0; fg<(nfiles-1); fg++){
  for(int jk=0; jk<netarange; jk++){
	sprintf(name,"RadRatio_AllRad_Canv_EtaBin%i_%s",jk+1,mc_name[fg+1]);
    c2_rad[fg][jk] = tdrCanvas(name,hist_radius[0][ref_rad][jk],7,0);

	leg2_rad[fg][jk] = tdrLeg(0.38,0.625,0.78,0.9);
	leg2_rad[fg][jk]->SetTextSize(0.035);
	leg2_rad[fg][jk]->SetTextFont(42);
	leg2_rad[fg][jk]->SetNColumns(2);
	
//	if(jk==0){
	leg2_err[fg][jk] = tdrLeg(0.5*(leg_x1+leg_x2)+0.275,0.75,0.5*(leg_x1+leg_x2)+0.475,0.9);//(0.7,0.75,0.9,0.9);
//	}else{
//		leg2_err[fg][jk] = tdrLeg(0.5*(leg_x1+leg_x2)+0.275,0.75,0.5*(leg_x1+leg_x2)+0.5,0.9);
//		}
	leg2_err[fg][jk]->SetTextFont(42);
	leg2_err[fg][jk]->SetTextSize(0.0375);
	
	if(jk==0) { cout<<"file "<<fg+1<<" x1 x2  "<<0.5*(leg_x1+leg_x2)<<'\t'<<0.5*(leg_x1+leg_x2)+0.6<<endl; }

	c2_rad[fg][jk]->cd(1);

	gPad->SetLogx(1);
	gPad->SetLogy(0);

	TLatex latex;
	latex.SetNDC();
	latex.SetTextAngle(0);
	latex.SetTextColor(kBlack);

	latex.SetTextFont(42);
	latex.SetTextAlign(31);
	latex.SetTextSize(0.06);

	TString text1;
	text1+=  ybinname[jk];

	leg_x1 = 0.3;
	leg_x2 = 0.7;
	leg_y1 = 0.85;

    if(jk==0){
	latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.2,leg_y1,text1);
	}else{
		 latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.15,leg_y1,text1);
		 }

	TLatex latex1;
	latex1.SetNDC();
	latex1.SetTextAngle(0);
	latex1.SetTextColor(kBlack);

	latex1.SetTextFont(42);
	latex1.SetTextAlign(31);
	latex1.SetTextSize(0.0375);

	 for(int ij=0; ij<(nalgo-1); ij++){
      
				hist_radius[0][ij][jk]->SetMarkerSize(1);
				tdrDraw(hist_radius[0][ij][jk],algo_sty[ij],algo_col[ij],kSolid,algo_col[ij],1001,2);
				hist_radius[fg+1][ij][jk]->SetLineWidth(2);
                tdrDraw(hist_radius[fg+1][ij][jk],1,0,1,algo_col[ij] ,1001,0);
                
//				leg2_rad[fg][jk]->AddEntry(hist_radius[fg+1][ij][jk],jetname_mod[ij],"l"); 
				leg2_rad[fg][jk]->AddEntry(hist_dummy_radius[fg+1][ij][jk],jetname_mod[ij],"lp");
		
				gr_rad_err_stat[ij][jk]->SetLineColor(algo_col[ij]);
				gr_rad_err_stat[ij][jk]->SetLineWidth(2);
				gr_rad_err_stat[ij][jk]->SetFillColor(5);
				gr_rad_err_stat[ij][jk]->SetFillStyle(1005);
				gr_rad_err_stat[ij][jk]->Draw("SAME:EZ");
				
				gr_rad_err_exp[ij][jk]->SetFillColor(algo_col[ij]);
				gr_rad_err_exp[ij][jk]->SetFillStyle(3005);
				gr_rad_err_exp[ij][jk]->Draw("SAME:E3");

				for(int bn=0; bn<(noptbins); bn++){
					gr_rad_err_th[ij][jk]->SetPoint(bn,hist_radius[fg+1][ij][jk]->GetBinCenter(bn+1),hist_radius[fg+1][ij][jk]->GetBinContent(bn+1));
				}

				gr_rad_err_th[ij][jk]->SetFillColor(algo_col[ij]);
				gr_rad_err_th[ij][jk]->SetFillStyle(3004);
				gr_rad_err_th[ij][jk]->Draw("SAME:E3");

		}//ij
/*
		leg2_err[fg][jk]->AddEntry(gr_rad_err_exp[0][jk],err_name[0],"f");
		leg2_err[fg][jk]->AddEntry(gr_rad_err_th[0][jk],err_name[1],"f");
*/		
		
		TGraphAsymmErrors *gr_exp = (TGraphAsymmErrors*)gr_rad_err_exp[0][jk]->Clone();
		TGraphAsymmErrors *gr_th = (TGraphAsymmErrors*)gr_rad_err_th[0][jk]->Clone();
		gr_exp->SetLineColor(kBlack); gr_exp->SetFillColor(kBlack); gr_exp->SetLineWidth(2);
		gr_th->SetLineColor(kBlack); gr_th->SetFillColor(kBlack); gr_th->SetLineWidth(2);
		
		leg2_err[fg][jk]->AddEntry(gr_exp,err_name[0],"f");
		leg2_err[fg][jk]->AddEntry(gr_th,err_name[1],"f");
		
		/*
		latex1.SetTextSize(0.032);
		latex1.DrawLatex(0.5*(leg_x1+leg_x2)+0.435,leg_y1-0.2,"Lines : MC");
		latex1.DrawLatex(0.5*(leg_x1+leg_x2)+0.435,leg_y1-0.15,"Markers : Data");
		*/
		
		TH1D *hd1 = (TH1D*)hist_radius[0][3][jk]->Clone();
		TH1D *hd2 = (TH1D*)hist_radius[0][3][jk]->Clone();
		hd1->SetFillColor(algo_col[3]);	hd1->SetFillStyle(3005); hd1->SetMarkerColor(kBlack); hd1->SetMarkerStyle(31); hd1->SetMarkerSize(2);
		hd2->SetFillColor(algo_col[3]);	hd2->SetFillStyle(3006); hd2->SetLineColor(kBlack); hd2->SetLineWidth(2);
		leg2_mc[jk] = tdrLeg(0.5*(leg_x1+leg_x2)+0.325,leg_y1-0.225,0.5*(leg_x1+leg_x2)+0.45,leg_y1-0.125);
		leg2_mc[jk]->SetTextSize(0.0375);
		leg2_mc[jk]->SetTextFont(42);
		leg2_mc[jk]->AddEntry(hd1,"Data","P");
		leg2_mc[jk]->AddEntry(hd2,"MC","L");
//		leg2_mc[jk]->Draw("sames");
		
		latex1.SetTextColor(kBlack);
		if((fg+1)==1||((fg+1)==3)||((fg+1)==4)){
			latex1.DrawLatex(0.375,0.8,model_name_rad[fg+1]);
		}
		if(((fg+1)==5)||((fg+1)==6)){
			latex1.DrawLatex(0.325,0.8,model_name_rad[fg+1]);
		}
		if(((fg+1)==2)||((fg+1)==8)){
			 latex1.DrawLatex(0.3,0.8,model_name_rad[fg+1]);
			 }
		if((fg+1)==7){
			latex1.DrawLatex(0.285,0.8,model_name_rad[fg+1]);
			}
		
//		sprintf(name,"All_Final/TUnfold_Legacy/RCombined/Radius/%s.pdf",c2_rad[fg][jk]->GetName());
		sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/Bayesian/RCombined/Radius/%s.pdf",c2_rad[fg][jk]->GetName());
		c2_rad[fg][jk]->SaveAs(name);
	 
	  }//jk
	}//fg

}


void Compare_FinalUnfoldedRat_MC(TH1D *hist_pt[nfiles][nalgo][netarange], TH1D *hist_pt_rat[nfiles-1][nalgo][netarange],
TH1D *hist_radius[nfiles][nalgo][netarange], TH1D *hist_radius_rat[nfiles-1][nalgo][netarange],
TGraphAsymmErrors *gr_pt_err_stat[nalgo][netarange],TGraphAsymmErrors *gr_pt_err_exp[nalgo][netarange],TGraphAsymmErrors *gr_pt_err_th[nalgo][netarange],
TGraphAsymmErrors *gr_rad_err_stat[nalgo][netarange],TGraphAsymmErrors *gr_rad_err_exp[nalgo][netarange],TGraphAsymmErrors *gr_rad_err_th[nalgo][netarange], TGraphAsymmErrors *gr_rad_err_expth[nalgo][netarange])
{
TCanvas *c2_ptrat[4][netarange];
TLegend *leg2_ptrat[4][netarange];

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

	hist_radius[fg][ij][jk]->SetMinimum(min_rad[ij]);
    hist_radius[fg][ij][jk]->SetMaximum(max_rad[ij]);

  }
 }
}

TCanvas *c2_rad[4][netarange];
TLegend *leg2_rad[4][netarange];
TLegend *leg2_err[4][netarange];

for(int ij=0; ij<(nalgo); ij++){
  for(int jk=0; jk<netarange; jk++){
	sprintf(name,"RadRatio_MCCombined_Canv_EtaBin%i_JetRadReg%i",jk+1,ij+1);
    c2_rad[ij][jk] = tdrCanvas(name,hist_radius[0][ij][jk],7,0);

	leg2_rad[ij][jk] = tdrLeg(0.43,0.625,0.9,0.9);
	leg2_rad[ij][jk]->SetTextSize(0.0325);
	leg2_rad[ij][jk]->SetTextFont(42);
	
	if(ij<3){
	leg2_err[ij][jk] = tdrLeg(0.15,0.6,0.3,0.75);
	}
	else{
		leg2_err[ij][jk] = tdrLeg(0.7,0.55,0.9,0.7);
		}
	leg2_err[ij][jk]->SetTextFont(42);
	leg2_err[ij][jk]->SetTextSize(0.038);

	c2_rad[ij][jk]->cd(1);

	gPad->SetLogx(1);
	gPad->SetLogy(0);

	TLatex latex;
	latex.SetNDC();
	latex.SetTextAngle(0);
	latex.SetTextColor(kBlack);

	latex.SetTextFont(42);
	latex.SetTextAlign(31);
	latex.SetTextSize(0.06);

    TString text0;
	text0+=  jetname[ij];
	TString text1;
	text1+=  ybinname[jk];

	leg_x1 = 0.3;
	leg_x2 = 0.7;
	leg_y1 = 0.85;

	latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.1,leg_y1,text0);
	latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.1,leg_y1-0.06,text1);

	TLatex latex1;
	latex1.SetNDC();
	latex1.SetTextAngle(0);
	latex1.SetTextColor(kRed);

	latex1.SetTextFont(42);
	latex1.SetTextAlign(31);
	latex1.SetTextSize(0.035);

	hist_radius[0][ij][jk]->SetMarkerSize(1);
	tdrDraw(hist_radius[0][ij][jk],algo_style[0],col[0],line_sty[0],col[0],1001,0);
	leg2_rad[ij][jk]->AddEntry(hist_radius[0][ij][jk],model_name_rad[0],"lp"); 
		

	for(int bn=0; bn<(noptbins); bn++){
		gr_rad_err_expth[ij][jk]->SetPoint(bn,hist_radius[0][ij][jk]->GetBinCenter(bn+1),hist_radius[0][ij][jk]->GetBinContent(bn+1));
	}

	gr_rad_err_expth[ij][jk]->SetFillColor(kBlue-10);
	gr_rad_err_expth[ij][jk]->SetFillStyle(1001);
	gr_rad_err_expth[ij][jk]->Draw("SAME:E3");
	
	for(int bn=0; bn<(noptbins); bn++){
		gr_rad_err_exp[ij][jk]->SetPoint(bn,hist_radius[0][ij][jk]->GetBinCenter(bn+1),hist_radius[0][ij][jk]->GetBinContent(bn+1));
	}
		
	gr_rad_err_exp[ij][jk]->SetFillColor(kYellow-3);
	gr_rad_err_exp[ij][jk]->SetFillStyle(1002);
	gr_rad_err_exp[ij][jk]->Draw("SAME:E3");

    tdrDraw(hist_radius[0][ij][jk],algo_style[0],col[0],line_sty[0],col[0],1001,0);
    
    for(int bn=0; bn<(noptbins); bn++){
		gr_rad_err_stat[ij][jk]->SetPoint(bn,hist_radius[0][ij][jk]->GetBinCenter(bn+1),hist_radius[0][ij][jk]->GetBinContent(bn+1));
	}   
	
    gr_rad_err_stat[ij][jk]->SetLineColor(kBlack);
	gr_rad_err_stat[ij][jk]->SetFillColor(5);
	gr_rad_err_stat[ij][jk]->SetFillStyle(1005);
	gr_rad_err_stat[ij][jk]->Draw("SAME:EZ");

	 for(int fg=1; fg<(nfiles-1); fg++){
            if(fg==6) continue;	
     //       hist_radius[fg][ij][jk]->SetMarkerSize(0); // plot w/o symbol
			hist_radius[fg][ij][jk]->SetLineWidth(2);
            tdrDraw(hist_radius[fg][ij][jk],algo_style[fg],col[fg],line_sty[fg],col[fg] ,1001,0);
            leg2_rad[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name_rad[fg],"lp"); 
        
			}//fg
		
		leg2_err[ij][jk]->AddEntry(gr_rad_err_exp[0][jk],err_name[0],"f");
		leg2_err[ij][jk]->AddEntry(gr_rad_err_expth[0][jk],error_name[2],"f");
		
		/*
		sprintf(name,"%s",model_name_rad[fg+1]);
		latex1.SetTextColor(kBlack);
		latex1.DrawLatex(0.425,0.765,name);
		*/
//		sprintf(name,"All_Final/TUnfold_Legacy/RCombined/Radius/%s.pdf",c2_rad[fg][jk]->GetName());
		sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/Bayesian/RadiusRatio/%s.pdf",c2_rad[ij][jk]->GetName());
		c2_rad[ij][jk]->SaveAs(name);
	 
	  }//jk
	}//fg

}

void XSectionvsR(TH1D *hist_pt[nfiles][nalgo][netarange],TH1D *hist_pt_org[nfiles][nalgo][netarange],
double pt_err_stat_up[nalgo][netarange][noptbins],double pt_err_exp_up[nalgo][netarange][noptbins],double pt_err_th_up[nalgo][netarange][noptbins],
double pt_err_stat_dn[nalgo][netarange][noptbins],double pt_err_exp_dn[nalgo][netarange][noptbins],double pt_err_th_dn[nalgo][netarange][noptbins])
{

TLatex cms_latex1;
TLatex cms_lumi1;

cms_latex1.SetNDC();
cms_latex1.SetTextFont(cmsTextFont1);
cms_latex1.SetTextAlign(31);
cms_latex1.SetTextSize(cmsTextSize1);
cms_latex1.SetTextAngle(0);

cms_lumi1.SetNDC();
cms_lumi1.SetTextFont(42);
cms_lumi1.SetTextAlign(31);
cms_lumi1.SetTextSize(lumiTextSize1);
cms_lumi1.SetTextAngle(0);


double xsection[nfiles][nalgo][netarange][nopbins];

double stat_error_up[nalgo][netarange][nopbins] = {{{0}}};
double stat_error_dn[nalgo][netarange][nopbins] = {{{0}}};
double exp_error_up[nalgo][netarange][nopbins] = {{{0}}};
double exp_error_dn[nalgo][netarange][nopbins] = {{{0}}};
double th_error_up[nalgo][netarange][nopbins] = {{{0}}};
double th_error_dn[nalgo][netarange][nopbins] = {{{0}}};


for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
   for(int jk=0; jk<netarange; jk++){

     TAxis *axis = hist_pt[fg][ij][jk]->GetXaxis();

     int amin =0, amax =0;

     for(int kl=0; kl<nopbins; kl++){
        amin = axis->FindBin(pbins[kl]);
        amax = axis->FindBin(pbins[kl+1]);

//	   cout<<kl+1<<" amin "<<amin<<" amax "<<amax<<endl;

        xsection[fg][ij][jk][kl]=0;
/*
        for(int abin=amin; abin<amax; abin++){
        xsection[fg][ij][jk][kl]+= hist_pt[fg][ij][jk]->GetBinContent(abin+1) * hist_pt[fg][ij][jk]->GetBinWidth(abin+1);
        }
*/
        xsection[fg][ij][jk][kl] = hist_pt[fg][ij][jk]->Integral(amin,amax,"width");

		if(fg==0 && ij==3 && jk==0){
			cout<<kl+1<<" "<<pbins[kl]<<" "<<pbins[kl+1]<<" "<<amin<<" "<<amax<<endl;
			}

		 if(fg==0){

                stat_error_up[ij][jk][kl] = stat_error_dn[ij][jk][kl] = exp_error_up[ij][jk][kl] = exp_error_dn[ij][jk][kl] = 0;

                for(int abin=amin; abin<amax; abin++){

                stat_error_up[ij][jk][kl] += pow(pt_err_stat_up[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                stat_error_dn[ij][jk][kl] += pow(pt_err_stat_dn[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                exp_error_up[ij][jk][kl] += pow(pt_err_exp_up[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                exp_error_dn[ij][jk][kl] += pow(pt_err_exp_dn[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                th_error_up[ij][jk][kl] += pow(pt_err_th_up[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                th_error_dn[ij][jk][kl] += pow(pt_err_th_dn[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                
                        }

				th_error_up[ij][jk][kl] += exp_error_up[ij][jk][kl];
                th_error_dn[ij][jk][kl] += exp_error_dn[ij][jk][kl];

                stat_error_up[ij][jk][kl] = sqrt(stat_error_up[ij][jk][kl]);
                stat_error_dn[ij][jk][kl] = sqrt(stat_error_dn[ij][jk][kl]);
                exp_error_up[ij][jk][kl] = sqrt(exp_error_up[ij][jk][kl]);
                exp_error_dn[ij][jk][kl] = sqrt(exp_error_dn[ij][jk][kl]);

                th_error_up[ij][jk][kl] = sqrt(th_error_up[ij][jk][kl]);
                th_error_dn[ij][jk][kl] = sqrt(th_error_dn[ij][jk][kl]);
				}//fg==0
			}
	    }
	  }
	}	

xsection[0][8][2][2] = (xsection[1][8][2][2]*1./xsection[1][7][2][2])*xsection[0][7][2][2];
xsection[0][8][2][1] = (xsection[1][8][2][1]*1./xsection[1][7][2][1])*xsection[0][7][2][1];

xsection[8][3][4][7] = 0.98*xsection[8][3][4][7];
xsection[8][3][4][8] = 0.98*xsection[8][3][4][8];
 

TH1D *sigmaR[nfiles][netarange][nopbins];
TH1D *sigmaR_rat[nfiles-1][netarange][nopbins];

for(int fg=0; fg<nfiles; fg++){	
 for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<nopbins; kl++){
        sprintf(name,"histRad_EtaBin%i_ptbin%i_File%i",jk+1,kl+1,fg+1);
        sigmaR[fg][jk][kl] = new TH1D(name,name,nalgo,0.05,1.25);
        for(int ij=0; ij<nalgo; ij++){
        sigmaR[fg][jk][kl]->SetBinContent(ij+1,xsection[fg][ij][jk][kl]);
        }
        if(fg>0){
        sigmaR_rat[fg-1][jk][kl] = (TH1D*)sigmaR[fg][jk][kl]->Clone();
        sigmaR_rat[fg-1][jk][kl]->Divide(sigmaR[0][jk][kl]);

        sigmaR_rat[fg-1][jk][kl]->SetLineColor(col[fg]);
        sigmaR_rat[fg-1][jk][kl]->SetLineStyle(line_sty[fg]);
        sigmaR_rat[fg-1][jk][kl]->SetMaximum(ymax[jk]);
        sigmaR_rat[fg-1][jk][kl]->SetMinimum(0.25);

        sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetTitle("Jet Radius");
        sigmaR_rat[fg-1][jk][kl]->GetXaxis()->CenterTitle();
        sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetTitleSize(0.1);
        sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetLabelSize(0.1);
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitle("Ratio to Data");
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->CenterTitle();
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitleSize(0.1);
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetLabelSize(0.085);
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitleOffset(0.7);
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetNdivisions(505);

        sigmaR_rat[fg-1][jk][kl]->SetMarkerSize(1);
        sigmaR_rat[fg-1][jk][kl]->SetMarkerStyle(algo_style[fg]);
        sigmaR_rat[fg-1][jk][kl]->SetMarkerColor(col[fg]);
        }
    }
  }
}

TGraph *gr_pt[nfiles][netarange][nopbins];
TMultiGraph *mul_gr[netarange][nopbins];
TMultiGraph *mul_gr_err[netarange][nopbins];

TLegend *leg[netarange][nopbins];
TLegend *leg_err[netarange][nopbins];

TGraphAsymmErrors *tg_error[netarange][nopbins];
TGraphAsymmErrors *tg_th_error[netarange][nopbins];

for(int jk=0; jk<netarange; jk++){
  for(int kl=0; kl<nopbins; kl++){

        if(jk<6){
        leg[jk][kl] = new TLegend(0.17,0.625,0.4,0.9);
        leg_err[jk][kl] = new TLegend(0.17,0.535,0.4,0.625);
        }
        else{
        leg[jk][kl] = new TLegend(0.6,0.15,0.8,0.4);
        leg_err[jk][kl] = new TLegend(0.6,0.125,0.8,0.15);
        }

        leg_err[jk][kl]->SetTextSize(0.03);
        leg_err[jk][kl]->SetTextFont(42);
        leg_err[jk][kl]->SetBorderSize(0);

        mul_gr[jk][kl] = new TMultiGraph();
        mul_gr_err[jk][kl] = new TMultiGraph();

     for(int fg=0; fg<nfiles; fg++){
		if(fg==6) continue;	
		
        gr_pt[fg][jk][kl] = new TGraph();

        for(int ij=0; ij<nalgo; ij++){
        gr_pt[fg][jk][kl]->SetPoint(ij,0.1*(ij+1),xsection[fg][ij][jk][kl]) ;
        }

        gr_pt[fg][jk][kl]->SetLineColor(col[fg]);
        gr_pt[fg][jk][kl]->GetXaxis()->SetTitle("Jet Radius");
        gr_pt[fg][jk][kl]->GetXaxis()->SetTitleSize(0.05);
        gr_pt[fg][jk][kl]->GetXaxis()->SetLabelSize(0.035);

        gr_pt[fg][jk][kl]->SetMarkerColor(col[fg]);
        gr_pt[fg][jk][kl]->SetMarkerSize(1);
        gr_pt[fg][jk][kl]->SetMarkerStyle(algo_style[fg]);
        gr_pt[fg][jk][kl]->SetLineStyle(line_sty[fg]);

        mul_gr[jk][kl]->Add(gr_pt[fg][jk][kl]);
        leg[jk][kl]->AddEntry(gr_pt[fg][jk][kl],model_name[fg],"lp");
  }

 double xval[nalgo], yval[nalgo], yerr_up[nalgo], yerr_dn[nalgo], yerr_th_up[nalgo], yerr_th_dn[nalgo];
        for(int ij=0; ij<nalgo; ij++){

                xval[ij] = 0.1*(ij+1);
                yval[ij] = xsection[0][ij][jk][kl];
                yerr_up[ij] = exp_error_up[ij][jk][kl];//stat_error_up[ij][jk][kl];     
                yerr_dn[ij] = exp_error_dn[ij][jk][kl];//stat_error_dn[ij][jk][kl];

                yerr_th_up[ij] = th_error_up[ij][jk][kl];
                yerr_th_dn[ij] = th_error_dn[ij][jk][kl];

      //          if(jk==0&&kl==(nopbins-2)){
      //          cout<<"READ "<<jk<<" "<<kl<<" "<<ij<<" "<<xval[ij]<<" "<<yval[ij]<<" "<<yerr_up[ij]<<" "<<yerr_th_up[ij]<<endl;
      //            }
                }

                tg_error[jk][kl] = new TGraphAsymmErrors(nalgo,xval,yval,NULL,NULL,yerr_up,yerr_dn);
                tg_th_error[jk][kl] = new TGraphAsymmErrors(nalgo,xval,yval,NULL,NULL,yerr_th_up,yerr_th_dn);
                mul_gr_err[jk][kl]->Add(tg_error[jk][kl]);
                leg_err[jk][kl]->AddEntry(tg_error[jk][kl],error_name[1],"f");
                leg_err[jk][kl]->AddEntry(tg_th_error[jk][kl],error_name[2],"f");

 }
}

TLine *line = new TLine(0.05,1,0.1*nalgo+0.05,1.);
line->SetLineColor(onelinecol);

TCanvas *c3_sig[netarange][nopbins];

for(int jk=0; jk<netarange; jk++){
 for(int kl=0; kl<nopbins; kl++){

   sprintf(name,"Xsection_EtaBin%i_PtBin%i",jk+1,kl+1);
   c3_sig[jk][kl] = tdrDiCanvas(name,sigmaR[2][jk][kl],sigmaR[0][jk][kl],7,0);
   c3_sig[jk][kl]->cd(1);
   gPad->SetLogy(0);
   gPad->SetLogx(0);

   TLatex latex;
   latex.SetNDC();
   latex.SetTextAngle(0);
   latex.SetTextColor(kBlack);

   latex.SetTextFont(42);
   latex.SetTextAlign(31);
   latex.SetTextSize(0.055);

   TString text;
   text+= ybinname[jk];
   TString text1;
   text1+= pbin_name[kl] ;

   mul_gr[jk][kl]->Draw("ALP");

   tg_error[jk][kl]->SetFillColor(kViolet+3);
   tg_error[jk][kl]->SetFillStyle(3005);
   tg_error[jk][kl]->Draw("SAME:E3");

   tg_th_error[jk][kl]->SetFillColor(kPink-7);
   tg_th_error[jk][kl]->SetFillStyle(3004);
   tg_th_error[jk][kl]->Draw("SAME:E3");

   mul_gr[jk][kl]->GetYaxis()->SetTitle("Integrated Cross Section (in fb)");
   mul_gr[jk][kl]->GetYaxis()->SetTitleSize(0.055);
   mul_gr[jk][kl]->GetYaxis()->CenterTitle();
   mul_gr[jk][kl]->GetYaxis()->SetTitleOffset(1.3);

   leg[jk][kl]->SetBorderSize(0);
   leg[jk][kl]->SetTextSize(0.04);
   leg[jk][kl]->SetTextFont(42);
   leg[jk][kl]->Draw();
   leg_err[jk][kl]->Draw("sames");

   if(jk<6){
   latex.DrawLatex(0.75,0.85,text);
   latex.SetTextSize(0.05);
   latex.DrawLatex(0.875,0.075,text1);
        }else{
           latex.DrawLatex(0.75,0.45,text);
           latex.DrawLatex(0.78,0.38,text1);
        }

  cms_latex1.DrawLatex(c3_sig[jk][kl]->GetPad(1)->GetLeftMargin(),0.95,cmsText);
  cms_lumi1.DrawLatex(1-c3_sig[jk][kl]->GetPad(1)->GetRightMargin(),0.95,lumi_13TeV_2016);

   c3_sig[jk][kl]->cd(2);
   gPad->SetLogx(0);

	TF1 *fnl = new TF1("line",f1,0.05,0.1*nalgo+0.05,1); 
	fnl->SetParameter(0,1);
	fnl->SetLineColor(kYellow+2);

   for(int fg=0; fg<(nfiles-1); fg++){

	if(fg==5) continue;

  if(fg==0) {    sigmaR_rat[fg][jk][kl]->Draw("CP"); fnl->Draw("L:sames");}
        else {  sigmaR_rat[fg][jk][kl]->Draw("CPSAME"); }
   }

//   line->Draw();
	
//   sprintf(name,"All_Final/TUnfold_Legacy/Integrated_Xsec/XsectionR_EtaBin%i_PtBin%i.pdf",jk+1,kl+1);
   sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/Bayesian/Integrated_Xsec/XsectionR_EtaBin%i_PtBin%i.pdf",jk+1,kl+1);

 
   c3_sig[jk][kl]->SaveAs(name);

 }
}

}

void XSectionvsR_Ratio(TH1D *hist_pt[nfiles][nalgo][netarange],TH1D *hist_pt_org[nfiles][nalgo][netarange],TH1D *hist_radius[nfiles][nalgo][netarange],
double pt_err_stat_up[nalgo][netarange][noptbins],double pt_err_exp_up[nalgo][netarange][noptbins],double pt_err_th_up[nalgo][netarange][noptbins],
double pt_err_stat_dn[nalgo][netarange][noptbins],double pt_err_exp_dn[nalgo][netarange][noptbins],double pt_err_th_dn[nalgo][netarange][noptbins])
{

TLatex cms_latex1;
TLatex cms_latex11;
TLatex cms_lumi1;

cms_latex1.SetNDC();
cms_latex1.SetTextFont(cmsTextFont1);
cms_latex1.SetTextAlign(31);
cms_latex1.SetTextSize(cmsTextSize1);
cms_latex1.SetTextAngle(0);

cms_latex11.SetNDC();
cms_latex11.SetTextFont(52);
cms_latex11.SetTextAlign(23);
cms_latex11.SetTextSize(0.76*cmsTextSize1);
cms_latex11.SetTextAngle(0);

cms_lumi1.SetNDC();
cms_lumi1.SetTextFont(42);
cms_lumi1.SetTextAlign(31);
cms_lumi1.SetTextSize(lumiTextSize1);
cms_lumi1.SetTextAngle(0);


double xsection[nfiles][nalgo][netarange][nopbins];

double stat_error_up[nalgo][netarange][nopbins] = {{{0}}};
double stat_error_dn[nalgo][netarange][nopbins] = {{{0}}};
double exp_error_up[nalgo][netarange][nopbins] = {{{0}}};
double exp_error_dn[nalgo][netarange][nopbins] = {{{0}}};
double th_error_up[nalgo][netarange][nopbins] = {{{0}}};
double th_error_dn[nalgo][netarange][nopbins] = {{{0}}};


for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
   for(int jk=0; jk<netarange; jk++){

     TAxis *axis = hist_pt[fg][ij][jk]->GetXaxis();

     int amin =0, amax =0;

     for(int kl=0; kl<nopbins; kl++){
        amin = axis->FindBin(pbins[kl]);
        amax = axis->FindBin(pbins[kl+1]);

//	   cout<<kl+1<<" amin "<<amin<<" amax "<<amax<<endl;

        xsection[fg][ij][jk][kl]=0;
/*
        for(int abin=amin; abin<amax; abin++){
        xsection[fg][ij][jk][kl]+= hist_pt[fg][ij][jk]->GetBinContent(abin+1) * hist_pt[fg][ij][jk]->GetBinWidth(abin+1);
        }
*/
        xsection[fg][ij][jk][kl] = hist_pt[fg][ij][jk]->Integral(amin,amax,"width");

		 if(fg==0){

                stat_error_up[ij][jk][kl] = stat_error_dn[ij][jk][kl] = exp_error_up[ij][jk][kl] = exp_error_dn[ij][jk][kl] = 0;

                for(int abin=amin; abin<amax; abin++){

                stat_error_up[ij][jk][kl] += pow(pt_err_stat_up[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                stat_error_dn[ij][jk][kl] += pow(pt_err_stat_dn[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                exp_error_up[ij][jk][kl] += pow(pt_err_exp_up[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                exp_error_dn[ij][jk][kl] += pow(pt_err_exp_dn[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                th_error_up[ij][jk][kl] += pow(pt_err_th_up[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                th_error_dn[ij][jk][kl] += pow(pt_err_th_dn[ij][jk][abin]/*(ptbins[abin+1]-ptbins[abin])*/*hist_pt_org[fg][ij][jk]->GetBinContent(abin+1),2);
                
                        }
/*
				th_error_up[ij][jk][kl] += exp_error_up[ij][jk][kl];
                th_error_dn[ij][jk][kl] += exp_error_dn[ij][jk][kl];
*/
                stat_error_up[ij][jk][kl] = sqrt(stat_error_up[ij][jk][kl]);
                stat_error_dn[ij][jk][kl] = sqrt(stat_error_dn[ij][jk][kl]);
                exp_error_up[ij][jk][kl] = sqrt(exp_error_up[ij][jk][kl]);
                exp_error_dn[ij][jk][kl] = sqrt(exp_error_dn[ij][jk][kl]);
                th_error_up[ij][jk][kl] = sqrt(th_error_up[ij][jk][kl]);
                th_error_dn[ij][jk][kl] = sqrt(th_error_dn[ij][jk][kl]);

				th_error_up[ij][jk][kl] *= 1./xsection[fg][ij][jk][kl];
				th_error_dn[ij][jk][kl] *= 1./xsection[fg][ij][jk][kl];
				exp_error_up[ij][jk][kl] *= 1./xsection[fg][ij][jk][kl];
				exp_error_dn[ij][jk][kl] *= 1./xsection[fg][ij][jk][kl];
				stat_error_up[ij][jk][kl] *= 1./xsection[fg][ij][jk][kl];
				stat_error_dn[ij][jk][kl] *= 1./xsection[fg][ij][jk][kl];
				}//fg==0
			}
	    }
	  }
	}	

xsection[0][8][2][2] = (xsection[1][8][2][2]*1./xsection[1][7][2][2])*xsection[0][7][2][2];
xsection[0][8][2][1] = (xsection[1][8][2][1]*1./xsection[1][7][2][1])*xsection[0][7][2][1];

xsection[8][3][4][7] = 0.98*xsection[8][3][4][7];
xsection[8][3][4][8] = 0.98*xsection[8][3][4][8];

double org_exp_error_up[nalgo][netarange][nopbins]; double org_exp_error_dn[nalgo][netarange][nopbins];
double org_th_error_up[nalgo][netarange][nopbins]; double org_th_error_dn[nalgo][netarange][nopbins];

for(int jk=0; jk<netarange; jk++){
 for(int kl=0; kl<nopbins; kl++){ 
	
	double refx = xsection[7][3][jk][kl];
	double referr_up = th_error_up[ref_rad][jk][kl];// exp_error_up[ref_rad][jk][kl];
	double referr_dn = th_error_dn[ref_rad][jk][kl];// exp_error_dn[ref_rad][jk][kl];
	double refstat = stat_error_up[ref_rad][jk][kl];
	
for(int ij=0; ij<nalgo; ij++){ 
	for(int fg=0; fg<nfiles; fg++){  
		xsection[fg][ij][jk][kl]  = xsection[fg][ij][jk][kl]*1./refx;
	 }
	 
	 org_exp_error_up[ij][jk][kl] = exp_error_up[ij][jk][kl];
	 org_exp_error_dn[ij][jk][kl] = exp_error_dn[ij][jk][kl];
	 org_th_error_up[ij][jk][kl] = th_error_up[ij][jk][kl];
	 org_th_error_dn[ij][jk][kl] = th_error_dn[ij][jk][kl];
	 /*
	 org_th_error_up[ij][jk][kl] = sqrt(pow(org_th_error_up[ij][jk][kl],2) - pow(org_exp_error_up[ij][jk][kl],2));
	 org_th_error_dn[ij][jk][kl] = sqrt(pow(org_th_error_dn[ij][jk][kl],2) - pow(org_exp_error_dn[ij][jk][kl],2));
	 */
	 double corcoeff = ((xsection[7][ij][jk][kl]*1./xsection[7][ref_rad][jk][kl])>1.)?(2.-(xsection[7][ij][jk][kl]*1./xsection[7][ref_rad][jk][kl])):(xsection[7][ij][jk][kl]*1./xsection[7][ref_rad][jk][kl]);
//	 double corcoeff = (min(ij+1,4)*1./max(ij+1,4));
	 
	 th_error_up[ij][jk][kl] = sqrt(th_error_up[ij][jk][kl]*th_error_up[ij][jk][kl] + referr_up*referr_up -2*corcoeff*th_error_up[ij][jk][kl]*referr_up);
	 th_error_dn[ij][jk][kl] = sqrt(th_error_dn[ij][jk][kl]*th_error_dn[ij][jk][kl] + referr_dn*referr_dn -2*corcoeff*th_error_dn[ij][jk][kl]*referr_dn);
	 
	 exp_error_up[ij][jk][kl] = sqrt(exp_error_up[ij][jk][kl]*exp_error_up[ij][jk][kl] + referr_up*referr_up);
	 exp_error_dn[ij][jk][kl] = sqrt(exp_error_dn[ij][jk][kl]*exp_error_dn[ij][jk][kl] + referr_dn*referr_dn);
	 
	 th_error_up[ij][jk][kl] += exp_error_up[ij][jk][kl];
	 th_error_dn[ij][jk][kl] += exp_error_dn[ij][jk][kl];
	 
	 stat_error_up[7][jk][kl] = sqrt(stat_error_up[7][jk][kl]*stat_error_up[7][jk][kl] + refstat*refstat);
	 stat_error_dn[7][jk][kl] = sqrt(stat_error_dn[7][jk][kl]*stat_error_dn[7][jk][kl] + refstat*refstat);
	 
   }
  }
}

TH1D *sigmaR[nfiles][netarange][nopbins];
TH1D *sigmaR_rat_hist[nfiles-1][netarange][nopbins];
TGraph *sigmaR_rat[nfiles-1][netarange][nopbins];

for(int fg=0; fg<nfiles; fg++){	
 for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<nopbins; kl++){
        sprintf(name,"histRad_EtaBin%i_ptbin%i_File%i",jk+1,kl+1,fg+1);
        sigmaR[fg][jk][kl] = new TH1D(name,name,nalgo,0.04,1.26);
        for(int ij=0; ij<nalgo; ij++){
        sigmaR[fg][jk][kl]->SetBinContent(ij+1,xsection[fg][ij][jk][kl]);
        }
        if(fg>0){
        sigmaR_rat_hist[fg-1][jk][kl] = (TH1D*)sigmaR[fg][jk][kl]->Clone();
        sigmaR_rat_hist[fg-1][jk][kl]->Divide(sigmaR[0][jk][kl]);
        
        sigmaR_rat[fg-1][jk][kl] = new TGraph();      
        for(int bn=0; bn< sigmaR_rat_hist[fg-1][jk][kl]->GetNbinsX(); bn++){
			sigmaR_rat[fg-1][jk][kl]->SetPoint(bn,0.1*(bn+1),sigmaR_rat_hist[fg-1][jk][kl]->GetBinContent(bn+1));
			}
/*
		sprintf(name,"histRad_Ratio_EtaBin%i_ptbin%i_File%i",jk+1,kl+1,fg+1);
		sigmaR_rat[fg-1][jk][kl] = new TH1D(name,name,nalgo,0.05,1.25);
		for(int bn=0; bn< sigmaR_rat[fg-1][jk][kl]->GetNbinsX(); bn++){
			sigmaR_rat[fg-1][jk][kl]->SetBinContent(bn+1,sigmaR_rat_hist[fg-1][jk][kl]->GetBinContent(bn+1));
		}
*/
        sigmaR_rat[fg-1][jk][kl]->SetLineColor(col[fg]);
        sigmaR_rat[fg-1][jk][kl]->SetLineStyle(line_sty[fg]);
        sigmaR_rat[fg-1][jk][kl]->SetMaximum(1.71);//ymax[jk]);
        sigmaR_rat[fg-1][jk][kl]->SetMinimum(0.29);

        sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetTitle("Jet Radius");
        sigmaR_rat[fg-1][jk][kl]->GetXaxis()->CenterTitle();
        sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetTitleSize(0.1);
        sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetLabelSize(0.1);
        sigmaR_rat[fg-1][jk][kl]->GetXaxis()->SetRangeUser(0.05,1.25);
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitle("Ratio to Data");
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->CenterTitle();
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitleSize(0.1);
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetLabelSize(0.1);
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetTitleOffset(0.7);
        sigmaR_rat[fg-1][jk][kl]->GetYaxis()->SetNdivisions(505);
		if(fg==7){
			sigmaR_rat[fg-1][jk][kl]->SetMarkerSize(1.5);
		}else{
			sigmaR_rat[fg-1][jk][kl]->SetMarkerSize(1);
			 }
        sigmaR_rat[fg-1][jk][kl]->SetMarkerStyle(algo_style[fg]);
        sigmaR_rat[fg-1][jk][kl]->SetMarkerColor(col[fg]);
        }
    }
  }
}

TGraph *gr_pt[nfiles][netarange][nopbins];
TMultiGraph *mul_gr[netarange][nopbins];
TMultiGraph *mul_gr_err[netarange][nopbins];

TLegend *leg[netarange][nopbins];
TLegend *leg_err[netarange][nopbins];
TLegend *leg_err_ref[netarange][nopbins];

TGraphAsymmErrors *tg_error[netarange][nopbins];
TGraphAsymmErrors *tg_th_error[netarange][nopbins];

TGraphAsymmErrors *tg_error_rel[netarange][nopbins];
TGraphAsymmErrors *tg_th_error_rel[netarange][nopbins];

TGraphAsymmErrors *tg_error_ref[netarange][nopbins];
TGraphAsymmErrors *tg_th_error_ref[netarange][nopbins];

TGraphAsymmErrors *tg_error_ref_rel[netarange][nopbins];
TGraphAsymmErrors *tg_th_error_ref_rel[netarange][nopbins];

for(int jk=0; jk<netarange; jk++){
  for(int kl=0; kl<nopbins; kl++){

        if(jk<6){
        leg[jk][kl] = new TLegend(0.17,0.625,0.4,0.9);
        leg_err[jk][kl] = new TLegend(0.17,0.535,0.4,0.625);
        leg_err_ref[jk][kl] = new TLegend(0.17,0.45,0.4,0.525); //(0.58,0.075,0.72,0.175);
        }
        else{
        leg[jk][kl] = new TLegend(0.6,0.15,0.8,0.4);
        leg_err[jk][kl] = new TLegend(0.6,0.125,0.8,0.15);
        leg_err_ref[jk][kl] = new TLegend(0.68,0.175,0.75,0.25);
        }

        leg_err[jk][kl]->SetTextSize(0.0325);
        leg_err[jk][kl]->SetTextFont(42);
        leg_err[jk][kl]->SetBorderSize(0);

        mul_gr[jk][kl] = new TMultiGraph();
        mul_gr_err[jk][kl] = new TMultiGraph();

     for(int fg=0; fg<nfiles; fg++){
		if(fg==6) continue;	
		
        gr_pt[fg][jk][kl] = new TGraph();

        for(int ij=0; ij<nalgo; ij++){
		if(fg==5){	
			gr_pt[fg][jk][kl]->SetPoint(ij,0.1*(ij+1)-0.005,xsection[fg][ij][jk][kl]) ;
			}
		else{
			gr_pt[fg][jk][kl]->SetPoint(ij,0.1*(ij+1),xsection[fg][ij][jk][kl]) ;
			}	
        }

        gr_pt[fg][jk][kl]->SetLineColor(col[fg]);
        gr_pt[fg][jk][kl]->GetXaxis()->SetTitle("Jet Radius");
        gr_pt[fg][jk][kl]->GetXaxis()->SetTitleSize(0.1);
        gr_pt[fg][jk][kl]->GetXaxis()->SetLabelSize(0.1);

        gr_pt[fg][jk][kl]->SetMarkerColor(col[fg]);
        gr_pt[fg][jk][kl]->SetMarkerSize(1);
        if(fg==7){ gr_pt[fg][jk][kl]->SetMarkerSize(2); }
        gr_pt[fg][jk][kl]->SetMarkerStyle(algo_style[fg]);
        gr_pt[fg][jk][kl]->SetLineStyle(line_sty[fg]);

        mul_gr[jk][kl]->Add(gr_pt[fg][jk][kl]);
        leg[jk][kl]->AddEntry(gr_pt[fg][jk][kl],model_name[fg],"lp");
  }

 double xval[nalgo], yval[nalgo], yerr_up[nalgo], yerr_dn[nalgo], yerr_th_up[nalgo], yerr_th_dn[nalgo];
 double yerr_up_rel[nalgo], yerr_dn_rel[nalgo], yerr_th_up_rel[nalgo], yerr_th_dn_rel[nalgo];
 double y1[nalgo];
 
        for(int ij=0; ij<nalgo; ij++){

                xval[ij] = 0.1*(ij+1);
                yval[ij] = xsection[0][ij][jk][kl];
                yerr_up[ij] = exp_error_up[ij][jk][kl];//stat_error_up[ij][jk][kl];     
                yerr_dn[ij] = exp_error_dn[ij][jk][kl];//stat_error_dn[ij][jk][kl];

                yerr_th_up[ij] = th_error_up[ij][jk][kl];
                yerr_th_dn[ij] = th_error_dn[ij][jk][kl];

      //          if(jk==0&&kl==(nopbins-2)){
      //          cout<<"READ "<<jk<<" "<<kl<<" "<<ij<<" "<<xval[ij]<<" "<<yval[ij]<<" "<<yerr_up[ij]<<" "<<yerr_th_up[ij]<<endl;
      //            }
                yerr_up_rel[ij] = yerr_up[ij]*1./yval[ij];
                yerr_dn_rel[ij] = yerr_dn[ij]*1./yval[ij];
                yerr_th_up_rel[ij] = yerr_th_up[ij]*1./yval[ij];
                yerr_th_dn_rel[ij] = yerr_th_dn[ij]*1./yval[ij];
                y1[ij] = 1;
                }

                tg_error[jk][kl] = new TGraphAsymmErrors(nalgo,xval,yval,NULL,NULL,yerr_up,yerr_dn);
                tg_th_error[jk][kl] = new TGraphAsymmErrors(nalgo,xval,yval,NULL,NULL,yerr_th_up,yerr_th_dn);
                mul_gr_err[jk][kl]->Add(tg_error[jk][kl]);
                leg_err[jk][kl]->AddEntry(tg_error[jk][kl],error_name[1],"f");
                leg_err[jk][kl]->AddEntry(tg_th_error[jk][kl],error_name[2],"f");
                
                tg_error_rel[jk][kl] = new TGraphAsymmErrors(nalgo,xval,y1,NULL,NULL,yerr_up_rel,yerr_dn_rel);
                tg_th_error_rel[jk][kl] = new TGraphAsymmErrors(nalgo,xval,y1,NULL,NULL,yerr_th_up_rel,yerr_th_dn_rel);

//				double xval2[3] = {0.185,0.19,0.195};
//				double yval2[3] = {xsection[0][3][jk][kl]*0.5,xsection[0][3][jk][kl]*0.5,xsection[0][3][jk][kl]*0.5};
				double xval2[3] = {0.065,0.0675,0.07};
				double yval2[3] = {1.0,1.0,1.0};
				double yerrup2[3] = {org_exp_error_up[3][jk][kl],org_exp_error_up[3][jk][kl],org_exp_error_up[3][jk][kl]};
				double yerrdn2[3] = {org_exp_error_dn[3][jk][kl],org_exp_error_dn[3][jk][kl],org_exp_error_dn[3][jk][kl]};
	
				tg_error_ref[jk][kl] = new TGraphAsymmErrors(3,xval2,yval2,NULL,NULL,yerrup2,yerrdn2);
			
				tg_th_error_ref[jk][kl] = new TGraphAsymmErrors();
				tg_th_error_ref_rel[jk][kl] = new TGraphAsymmErrors();
				tg_error_ref_rel[jk][kl] = new TGraphAsymmErrors();
				/*
				tg_th_error_ref[jk][kl]->SetPoint(0,0.41,xsection[0][3][jk][kl]*0.5);
				tg_th_error_ref[jk][kl]->SetPoint(1,0.405,xsection[0][3][jk][kl]*0.5);
				tg_th_error_ref[jk][kl]->SetPoint(2,0.415,xsection[0][3][jk][kl]*0.5);
				*/ 
				tg_th_error_ref[jk][kl]->SetPoint(0,075,1.0); tg_th_error_ref_rel[jk][kl]->SetPoint(0,0.075,1.0); tg_error_ref_rel[jk][kl]->SetPoint(0,0.0675,1.0);
				tg_th_error_ref[jk][kl]->SetPoint(1,0.0725,1.0); tg_th_error_ref_rel[jk][kl]->SetPoint(1,0.0725,1.0); tg_error_ref_rel[jk][kl]->SetPoint(1,0.065,1.0);
				tg_th_error_ref[jk][kl]->SetPoint(2,0.0775,1.0); tg_th_error_ref_rel[jk][kl]->SetPoint(2,0.0775,1.0); tg_error_ref_rel[jk][kl]->SetPoint(2,0.07,1.0);
				for(int ipr=0; ipr<3; ipr++){
					tg_th_error_ref[jk][kl]->SetPointEYhigh(ipr,org_th_error_up[3][jk][kl]);
					tg_th_error_ref[jk][kl]->SetPointEYlow(ipr,org_th_error_dn[3][jk][kl]);
					tg_th_error_ref_rel[jk][kl]->SetPointEYhigh(ipr,org_th_error_up[3][jk][kl]*1./yval[3]);
					tg_th_error_ref_rel[jk][kl]->SetPointEYlow(ipr,org_th_error_dn[3][jk][kl]*1./yval[3]);
					if(jk==4){
						cout<<kl+1<<" therr up "<<org_th_error_up[3][jk][kl]<<" up "<<org_th_error_dn[3][jk][kl]<<endl;
						}
					tg_error_ref_rel[jk][kl]->SetPointEYhigh(ipr,org_exp_error_up[3][jk][kl]*1./yval[3]);
					tg_error_ref_rel[jk][kl]->SetPointEYlow(ipr,org_exp_error_up[3][jk][kl]*1./yval[3]);
				}
				
//				leg_err_ref[jk][kl]->AddEntry(tg_error_ref[jk][kl],ref_err_name[0],"f");
//                leg_err_ref[jk][kl]->AddEntry(tg_th_error_ref[jk][kl],ref_err_name[1],"f");
	}
}

TLine *line = new TLine(0.05,1,0.1*nalgo+0.05,1.);
line->SetLineColor(onelinecol);

TCanvas *c3_sig[netarange][nopbins];

for(int jk=0; jk<netarange; jk++){
 for(int kl=0; kl<nopbins; kl++){

   sprintf(name,"Xsection_EtaBin%i_PtBin%i",jk+1,kl+1);
   c3_sig[jk][kl] = tdrDiCanvas(name,sigmaR[2][jk][kl],sigmaR[0][jk][kl],7,0);
   c3_sig[jk][kl]->cd(1);
   gPad->SetLogy(0);
   gPad->SetLogx(0);

   TLatex latex;
   latex.SetNDC();
   latex.SetTextAngle(0);
   latex.SetTextColor(kBlack);

   latex.SetTextFont(42);
   latex.SetTextAlign(31);
   latex.SetTextSize(0.055);

   TString text;
   text+= ybinname[jk];
   TString text1;
   text1+= pbin_name[kl] ;

//   mul_gr[jk][kl]->Draw("ALP:SAME");

   for(int fg=0;fg<nfiles; fg++){

   if(fg==6) continue;

   gr_pt[fg][jk][kl]->GetYaxis()->SetTitle("(d#sigma/dy) / (d#sigma/dy of AK4 Jets Herwig7)");
   gr_pt[fg][jk][kl]->GetYaxis()->SetTitleSize(0.05);
   gr_pt[fg][jk][kl]->GetYaxis()->SetLabelSize(0.05);
   gr_pt[fg][jk][kl]->GetYaxis()->CenterTitle();
   gr_pt[fg][jk][kl]->GetYaxis()->SetTitleOffset(1.3);
   
   gr_pt[fg][jk][kl]->SetMinimum(-0.1);
   gr_pt[fg][jk][kl]->SetMaximum(3.751);
   
   }

   gr_pt[3][jk][kl]->GetXaxis()->SetRangeUser(0.05,1.25); 
   gr_pt[3][jk][kl]->GetXaxis()->SetNdivisions(406);
   gr_pt[3][jk][kl]->Draw("ALP");

   tg_th_error[jk][kl]->SetFillColorAlpha(kOrange+2,0.75);//(kPink-7,0.75);
//   tg_th_error[jk][kl]->SetFillStyle(3004);
   tg_th_error[jk][kl]->Draw("E3:SAME");
   
   tg_error[jk][kl]->SetFillColorAlpha(kViolet-7,0.75);//kViolet+3,0.75);
//   tg_error[jk][kl]->SetFillStyle(3005);
   tg_error[jk][kl]->Draw("E3:SAME");
   
//   mul_gr[jk][kl]->Draw("ALP:SAME");
   
   tg_error_ref[jk][kl]->SetLineColor(kYellow+3);//kOrange-2);
   tg_error_ref[jk][kl]->SetFillColor(kYellow+3);//kOrange-2);
   tg_error_ref[jk][kl]->SetFillStyle(1002);
   tg_error_ref[jk][kl]->SetLineWidth(-2002);
//   tg_error_ref[jk][kl]->Draw("SAME:E5");
   
   tg_th_error_ref[jk][kl]->SetLineColor(kPink-4);
   tg_th_error_ref[jk][kl]->SetFillColor(kPink-4);
   tg_th_error_ref[jk][kl]->SetFillStyle(1002);
   tg_th_error_ref[jk][kl]->SetLineWidth(-2002);
//   tg_th_error_ref[jk][kl]->Draw("SAME:E5");
   /*
   mul_gr[jk][kl]->GetYaxis()->SetTitle("(d#sigma/dy) / (d#sigma/dy of AK4 Jets Herwig7)");
   mul_gr[jk][kl]->GetYaxis()->SetTitleSize(0.055);
   mul_gr[jk][kl]->GetYaxis()->CenterTitle();
   mul_gr[jk][kl]->GetYaxis()->SetTitleOffset(1.3);
   
   mul_gr[jk][kl]->SetMinimum(-0.1);
   mul_gr[jk][kl]->SetMaximum(3.751);
*/
   for(int fg=0;fg<nfiles; fg++){
	if(fg==6||fg==3) continue;	
	gr_pt[fg][jk][kl]->Draw("SAME:LP");
   }

   leg[jk][kl]->SetBorderSize(0);
   leg[jk][kl]->SetTextSize(0.04);
   leg[jk][kl]->SetTextFont(42);
   leg[jk][kl]->Draw();
   leg_err[jk][kl]->Draw("sames");
   
   leg_err_ref[jk][kl]->SetBorderSize(0);
   leg_err_ref[jk][kl]->SetTextSize(0.03);
   leg_err_ref[jk][kl]->Draw("sames");

   if(jk<6){
   latex.DrawLatex(0.8,0.85,text);
   latex.SetTextSize(0.05);
   latex.DrawLatex(0.91,0.105,text1);
        }else{
           latex.DrawLatex(0.75,0.45,text);
           latex.DrawLatex(0.78,0.38,text1);
        }

   cms_latex1.DrawLatex(c3_sig[jk][kl]->GetPad(1)->GetLeftMargin(),0.95,cmsText);
   cms_lumi1.DrawLatex(1-c3_sig[jk][kl]->GetPad(1)->GetRightMargin(),0.95,lumi_13TeV_2016);
   cms_latex11.DrawLatex(c3_sig[jk][kl]->GetPad(1)->GetLeftMargin()+0.105,0.985,extraText1);

   c3_sig[jk][kl]->cd(2);
   gPad->SetLogx(0);

	TF1 *fnl = new TF1("line",f1,0.05,0.1*nalgo+0.05,1); 
	fnl->SetParameter(0,1);
	fnl->SetLineColor(kYellow+2);

   for(int fg=0; fg<(nfiles-1); fg++){

	if(fg==5) continue;
	
	 sigmaR_rat[fg][jk][kl]->SetMaximum(1.71);
	 sigmaR_rat[fg][jk][kl]->GetXaxis()->SetNdivisions(406);

	if(fg==0) {    sigmaR_rat[fg][jk][kl]->Draw("ALPP"); fnl->Draw("L:sames");}
        else {  sigmaR_rat[fg][jk][kl]->Draw("ALPSAME"); }
   }
   
   
   tg_th_error_rel[jk][kl]->SetFillColorAlpha(kOrange+2,0.75);
   tg_error_rel[jk][kl]->SetFillColorAlpha(kViolet-7,0.75);
   
   tg_th_error_rel[jk][kl]->Draw("E3");
   tg_error_rel[jk][kl]->Draw("SAME:E3");
   
   tg_error_ref_rel[jk][kl]->SetLineColor(kYellow+3);
   tg_error_ref_rel[jk][kl]->SetFillColor(kYellow+3);
   tg_error_ref_rel[jk][kl]->SetFillStyle(1002);
   tg_error_ref_rel[jk][kl]->SetLineWidth(-2002);
//   tg_error_ref_rel[jk][kl]->Draw("SAME:E5");
   
   tg_th_error_ref_rel[jk][kl]->SetLineColor(kPink-4);
   tg_th_error_ref_rel[jk][kl]->SetFillColor(kPink-4);
   tg_th_error_ref_rel[jk][kl]->SetFillStyle(1002);
   tg_th_error_ref_rel[jk][kl]->SetLineWidth(-2002);
//   tg_th_error_ref_rel[jk][kl]->Draw("SAME:E5");
   
   fnl->Draw("L:sames");
   
   for(int fg=0; fg<(nfiles-1); fg++){
	sigmaR_rat[fg][jk][kl]->Draw("CPSAME"); 
   } 
   
//   line->Draw();
   sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/Bayesian/Integrated_Xsec_Ratio_H7/XsectionR_EtaBin%i_PtBin%i.pdf",jk+1,kl+1);

   c3_sig[jk][kl]->SaveAs(name);

  }
 }
 
   TCanvas *cmultipad = new TCanvas("Canv_Combined_Integrated_Xsection","Canv_Combined_Integrated_Xsection",50,50,800,600);
   
   TPad *p1 = new TPad("p1", "p1", 0.05, 0.5, 0.35, 0.95, 0, 0, 0);
   p1->SetTopMargin(0);
   
   TPad *p2 = new TPad("p2", "p2", 0.35, 0.5, 0.65, 0.95, 0, 0, 0);
   p2->SetBottomMargin(0);
   
   p1->cd();
   gr_pt[3][0][3]->Draw("AP");
   p2->cd();
   gr_pt[3][0][7]->Draw("AP");
   
   sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/Bayesian/Integrated_Xsec_Ratio_H7/%s.pdf",cmultipad->GetName());
   cmultipad->SaveAs(name);
}

int main()
{

double pt_err_exp_up[nalgo][netarange][noptbins]={{{0}}};
double pt_err_exp_dn[nalgo][netarange][noptbins]={{{0}}};
double rad_err_exp_up[nalgo][netarange][noptbins]={{{0}}};
double rad_err_exp_dn[nalgo][netarange][noptbins]{{{0}}};

double pt_err_th_up[nalgo][netarange][noptbins]{{{0}}};
double pt_err_th_dn[nalgo][netarange][noptbins]{{{0}}};
double rad_err_th_up[nalgo][netarange][noptbins]{{{0}}};
double rad_err_th_dn[nalgo][netarange][noptbins]{{{0}}};

double pt_err_stat_up[nalgo][netarange][noptbins]{{{0}}};
double pt_err_stat_dn[nalgo][netarange][noptbins]{{{0}}};
double rad_err_stat_up[nalgo][netarange][noptbins]{{{0}}};
double rad_err_stat_dn[nalgo][netarange][noptbins]{{{0}}};

double pt_err_rmstat_up[nalgo][netarange][noptbins]{{{0}}};
double pt_err_rmstat_dn[nalgo][netarange][noptbins]{{{0}}};
double rad_err_rmstat_up[nalgo][netarange][noptbins]{{{0}}};
double rad_err_rmstat_dn[nalgo][netarange][noptbins]{{{0}}};

double pt_err_expth_up[nalgo][netarange][noptbins]{{{0}}};
double pt_err_expth_dn[nalgo][netarange][noptbins]{{{0}}};
double rad_err_expth_up[nalgo][netarange][noptbins]{{{0}}};
double rad_err_expth_dn[nalgo][netarange][noptbins]{{{0}}};
/////
double pt_dem_exp_up[nalgo][netarange][2*noptbins]={{{0}}};
double pt_dem_exp_dn[nalgo][netarange][2*noptbins]={{{0}}};
double rad_dem_exp_up[nalgo][netarange][2*noptbins]={{{0}}};
double rad_dem_exp_dn[nalgo][netarange][2*noptbins]{{{0}}};

double pt_dem_th_up[nalgo][netarange][2*noptbins]{{{0}}};
double pt_dem_th_dn[nalgo][netarange][2*noptbins]{{{0}}};
double rad_dem_th_up[nalgo][netarange][2*noptbins]{{{0}}};
double rad_dem_th_dn[nalgo][netarange][2*noptbins]{{{0}}};

double pt_dem_stat_up[nalgo][netarange][2*noptbins]{{{0}}};
double pt_dem_stat_dn[nalgo][netarange][2*noptbins]{{{0}}};
double rad_dem_stat_up[nalgo][netarange][2*noptbins]{{{0}}};
double rad_dem_stat_dn[nalgo][netarange][2*noptbins]{{{0}}};
////

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_y[nfiles][nalgo];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_y_rat[nfiles-1][nalgo];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

TGraphAsymmErrors *gr_pt_err_stat[nalgo][netarange];
TGraphAsymmErrors *gr_pt_err_exp[nalgo][netarange];
TGraphAsymmErrors *gr_pt_err_th[nalgo][netarange];
TGraphAsymmErrors *gr_pt_err_expth[nalgo][netarange];

TGraphAsymmErrors *gr_rad_err_stat[nalgo][netarange];
TGraphAsymmErrors *gr_rad_err_exp[nalgo][netarange];
TGraphAsymmErrors *gr_rad_err_th[nalgo][netarange];
TGraphAsymmErrors *gr_rad_err_expth[nalgo][netarange];

TMultiGraph *mul_gr_pt_err[nalgo][netarange];
TMultiGraph *mul_gr_rad_err[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	
	int nPT = noptbins;
	#ifdef TUnfold  
	nPT = 2*noptbins - 1;
	#endif
     for(int kl=0; kl<nPT; kl++){
	     int xx1,xx2,xx3;
	 
	 #ifdef TUnfold  
		 fp_pt_exp>>xx1>>xx2>>xx3>>pt_dem_exp_up[ij][jk][kl+1]>>pt_dem_exp_dn[ij][jk][kl+1];
	     fp_rad_exp>>xx1>>xx2>>xx3>>rad_dem_exp_up[ij][jk][kl+1]>>rad_dem_exp_dn[ij][jk][kl+1];
	     fp_pt_th>>xx1>>xx2>>xx3>>pt_dem_th_up[ij][jk][kl+1]>>pt_dem_th_dn[ij][jk][kl+1];
         fp_rad_th>>xx1>>xx2>>xx3>>rad_dem_th_up[ij][jk][kl+1]>>rad_dem_th_dn[ij][jk][kl+1];
	     fp_pt_stat>>xx1>>xx2>>xx3>>pt_dem_stat_up[ij][jk][kl+1]>>pt_dem_stat_dn[ij][jk][kl+1];
         fp_rad_stat>>xx1>>xx2>>xx3>>rad_dem_stat_up[ij][jk][kl+1]>>rad_dem_stat_dn[ij][jk][kl+1];
 /*
         fp_pt_rmstat>>xx1>>xx2>>xx3>>pt_err_rmstat_up[ij][jk][kl+1]>>pt_err_rmstat_dn[ij][jk][kl+1];
         fp_rad_rmstat>>xx1>>xx2>>xx3>>rad_err_rmstat_up[ij][jk][kl+1]>>rad_err_rmstat_dn[ij][jk][kl+1];
         
         pt_err_stat_up[ij][jk][kl+1] = sqrt(pt_err_stat_up[ij][jk][kl+1]*pt_err_stat_up[ij][jk][kl+1]  + pt_err_rmstat_up[ij][jk][kl+1]*pt_err_rmstat_up[ij][jk][kl+1]);
		 pt_err_stat_dn[ij][jk][kl+1] = sqrt(pt_err_stat_dn[ij][jk][kl+1]*pt_err_stat_dn[ij][jk][kl+1]  + pt_err_rmstat_dn[ij][jk][kl+1]*pt_err_rmstat_dn[ij][jk][kl+1]);
*/		 
	 #else 
	     fp_pt_exp>>xx1>>xx2>>xx3>>pt_err_exp_up[ij][jk][kl]>>pt_err_exp_dn[ij][jk][kl];
	     fp_rad_exp>>xx1>>xx2>>xx3>>rad_err_exp_up[ij][jk][kl]>>rad_err_exp_dn[ij][jk][kl];
	     fp_pt_th>>xx1>>xx2>>xx3>>pt_err_th_up[ij][jk][kl]>>pt_err_th_dn[ij][jk][kl];
         fp_rad_th>>xx1>>xx2>>xx3>>rad_err_th_up[ij][jk][kl]>>rad_err_th_dn[ij][jk][kl];
	     fp_pt_stat>>xx1>>xx2>>xx3>>pt_err_stat_up[ij][jk][kl]>>pt_err_stat_dn[ij][jk][kl];
         fp_rad_stat>>xx1>>xx2>>xx3>>rad_err_stat_up[ij][jk][kl]>>rad_err_stat_dn[ij][jk][kl];
         
/*
         fp_pt_rmstat>>xx1>>xx2>>xx3>>pt_err_rmstat_up[ij][jk][kl]>>pt_err_rmstat_dn[ij][jk][kl];
         fp_rad_rmstat>>xx1>>xx2>>xx3>>rad_err_rmstat_up[ij][jk][kl]>>rad_err_rmstat_dn[ij][jk][kl];
         
         pt_err_stat_up[ij][jk][kl] = sqrt(pt_err_stat_up[ij][jk][kl]*pt_err_stat_up[ij][jk][kl]  + pt_err_rmstat_up[ij][jk][kl]*pt_err_rmstat_up[ij][jk][kl]);
		 pt_err_stat_dn[ij][jk][kl] = sqrt(pt_err_stat_dn[ij][jk][kl]*pt_err_stat_dn[ij][jk][kl]  + pt_err_rmstat_dn[ij][jk][kl]*pt_err_rmstat_dn[ij][jk][kl]);
		 
		 rad_err_stat_up[ij][jk][kl] = sqrt(rad_err_stat_up[ij][jk][kl]*rad_err_stat_up[ij][jk][kl]  + rad_err_rmstat_up[ij][jk][kl]*rad_err_rmstat_up[ij][jk][kl]);
		 rad_err_stat_dn[ij][jk][kl] = sqrt(rad_err_stat_dn[ij][jk][kl]*rad_err_stat_dn[ij][jk][kl]  + rad_err_rmstat_dn[ij][jk][kl]*rad_err_rmstat_dn[ij][jk][kl]);
*/		 
    #endif

/*
			 pt_err_exp_up[ij][jk][kl] = sqrt(pow(pt_err_stat_up[ij][jk][kl],2)+pow(pt_err_exp_up[ij][jk][kl],2));
             pt_err_exp_dn[ij][jk][kl] = sqrt(pow(pt_err_stat_dn[ij][jk][kl],2)+pow(pt_err_exp_dn[ij][jk][kl],2));
             rad_err_exp_up[ij][jk][kl] = sqrt(pow(rad_err_stat_up[ij][jk][kl],2)+pow(rad_err_exp_up[ij][jk][kl],2));
             rad_err_exp_dn[ij][jk][kl] = sqrt(pow(rad_err_stat_dn[ij][jk][kl],2)+pow(rad_err_exp_dn[ij][jk][kl],2));
*/
		}
		
		#ifdef TUnfold
		for(int kl=0; kl<noptbins; kl++){
			pt_err_exp_up[ij][jk][kl] = sqrt(pow(pt_dem_exp_up[ij][jk][2*kl],2) + pow(pt_dem_exp_up[ij][jk][2*kl+1],2));
			pt_err_exp_dn[ij][jk][kl] = sqrt(pow(pt_dem_exp_dn[ij][jk][2*kl],2) + pow(pt_dem_exp_dn[ij][jk][2*kl+1],2));
			pt_err_th_up[ij][jk][kl] = sqrt(pow(pt_dem_th_up[ij][jk][2*kl],2) + pow(pt_dem_th_up[ij][jk][2*kl+1],2));
			pt_err_th_dn[ij][jk][kl] = sqrt(pow(pt_dem_th_dn[ij][jk][2*kl],2) + pow(pt_dem_th_dn[ij][jk][2*kl+1],2));
			pt_err_stat_up[ij][jk][kl] = sqrt(pow(pt_dem_stat_up[ij][jk][2*kl],2) + pow(pt_dem_stat_up[ij][jk][2*kl+1],2));
			pt_err_stat_dn[ij][jk][kl] = sqrt(pow(pt_dem_stat_dn[ij][jk][2*kl],2) + pow(pt_dem_stat_dn[ij][jk][2*kl+1],2));
		}		
		#endif
		
	 
//		cout<<"AK "<<ij+1<<" Eta "<<jk+1<<endl;
	 
		for(int kl=0; kl<noptbins; kl++){
	     pt_err_expth_up[ij][jk][kl] = sqrt(pow(pt_err_th_up[ij][jk][kl],2)+pow(pt_err_exp_up[ij][jk][kl],2));
	     pt_err_expth_dn[ij][jk][kl] = sqrt(pow(pt_err_th_dn[ij][jk][kl],2)+pow(pt_err_exp_dn[ij][jk][kl],2));
	     rad_err_expth_up[ij][jk][kl] = sqrt(pow(rad_err_th_up[ij][jk][kl],2)+pow(rad_err_exp_up[ij][jk][kl],2));
	     rad_err_expth_dn[ij][jk][kl] = sqrt(pow(rad_err_th_dn[ij][jk][kl],2)+pow(rad_err_exp_dn[ij][jk][kl],2));
		
//		  cout<<"bin "<<kl+1<<" staterr "<<rad_err_stat_up[ij][jk][kl]<<endl;
		
		}
     }
   }

//char name[1000];

TFile *filein;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

	mul_gr_pt_err[ij][jk] = new TMultiGraph();

	gr_pt_err_exp[ij][jk] = new TGraphAsymmErrors();
	gr_rad_err_exp[ij][jk] = new TGraphAsymmErrors();

	gr_pt_err_th[ij][jk] = new TGraphAsymmErrors();
	gr_rad_err_th[ij][jk] = new TGraphAsymmErrors();

	gr_pt_err_stat[ij][jk] = new TGraphAsymmErrors();
    gr_rad_err_stat[ij][jk] = new TGraphAsymmErrors();
    
    gr_pt_err_expth[ij][jk] = new TGraphAsymmErrors();
	gr_rad_err_expth[ij][jk] = new TGraphAsymmErrors();

	for(int bn=0; bn<noptbins; bn++){

		gr_pt_err_stat[ij][jk]->SetPoint(bn,ptbins[bn]+1.,1.);
        gr_pt_err_stat[ij][jk]->SetPointEYhigh(bn,pt_err_stat_up[ij][jk][bn]);
        gr_pt_err_stat[ij][jk]->SetPointEYlow(bn,pt_err_stat_dn[ij][jk][bn]);
/*
        gr_rad_err_stat[ij][jk]->SetPoint(bn,ptbins[bn]+1,1.);
        gr_rad_err_stat[ij][jk]->SetPointEYhigh(bn,rad_err_stat_up[ij][jk][bn]);
        gr_rad_err_stat[ij][jk]->SetPointEYlow(bn,rad_err_stat_dn[ij][jk][bn]);
*/
		gr_pt_err_exp[ij][jk]->SetPoint(bn,ptbins[bn]+1,1.);
		gr_pt_err_exp[ij][jk]->SetPointEYhigh(bn,pt_err_exp_up[ij][jk][bn]);
		gr_pt_err_exp[ij][jk]->SetPointEYlow(bn,pt_err_exp_dn[ij][jk][bn]);
	/*
		gr_rad_err_exp[ij][jk]->SetPoint(bn,ptbins[bn]+1,1.);
		gr_rad_err_exp[ij][jk]->SetPointEYhigh(bn,rad_err_exp_up[ij][jk][bn]);
		gr_rad_err_exp[ij][jk]->SetPointEYlow(bn,rad_err_exp_dn[ij][jk][bn]);
	*/
		gr_pt_err_th[ij][jk]->SetPoint(bn,ptbins[bn]+1,1.);
        gr_pt_err_th[ij][jk]->SetPointEYhigh(bn,pt_err_th_up[ij][jk][bn]);
        gr_pt_err_th[ij][jk]->SetPointEYlow(bn,pt_err_th_dn[ij][jk][bn]);
/*
        gr_rad_err_th[ij][jk]->SetPoint(bn,ptbins[bn]+1,1.);
        gr_rad_err_th[ij][jk]->SetPointEYhigh(bn,rad_err_th_up[ij][jk][bn]);
        gr_rad_err_th[ij][jk]->SetPointEYlow(bn,rad_err_th_dn[ij][jk][bn]);
*/
		gr_pt_err_expth[ij][jk]->SetPoint(bn,ptbins[bn]+1,1.);
        gr_pt_err_expth[ij][jk]->SetPointEYhigh(bn,pt_err_expth_up[ij][jk][bn]);
        gr_pt_err_expth[ij][jk]->SetPointEYlow(bn,pt_err_expth_dn[ij][jk][bn]);
/*
        gr_rad_err_expth[ij][jk]->SetPoint(bn,ptbins[bn]+1,1.);
        gr_rad_err_expth[ij][jk]->SetPointEYhigh(bn,rad_err_expth_up[ij][jk][bn]);
        gr_rad_err_expth[ij][jk]->SetPointEYlow(bn,rad_err_expth_dn[ij][jk][bn]);
*/
	}//bn
  }//jk
}//ij

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
  
     if(fg==0){ sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1) ; }
//	 if(fg==0){ sprintf(name,"tuf_TUnfold_%s_Etabin%i",JetRad[ij],jk+1) ; }
   else{
	sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);

	if(fg==4||fg==6) { sprintf(name,"mcjets/Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1); }
	if(fg==(nfiles-1)) {sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
       }  

    hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
    hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
    
   if(fg<(nfiles-1)){
   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/sqrt(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
     }
    }


   // trigger efficiency correction
   if(fg==0){

	hist_pt[fg][ij][jk]->Scale(34.67*1./33.9);
	
   ifstream eff_cor_file("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/MINIAOD/Trigger_2016/Trig_Cor_output.log");
   double eff_cor[nalgo][netarange][noptbins];
   int xy1, xy2, xy3;
				int ptbin62 = 62;
                for(int kl=0; kl<ptbin62; kl++){
					eff_cor[ij][jk][kl] = 1.;
					eff_cor_file>>xy1>>xy2>>xy3>>eff_cor[ij][jk][kl]>>eff_cor[ij][jk][kl];
			//		cout<<ij+1<<" "<<jk+1<<" "<<kl+1<<" "<<eff_cor[ij][jk][kl]<<endl;
					hist_pt[0][ij][jk]->SetBinContent(kl+1,hist_pt[0][ij][jk]->GetBinContent(kl+1)*eff_cor[ij][jk][kl]);
					hist_pt[0][ij][jk]->SetBinError(kl+1,hist_pt[0][ij][jk]->GetBinError(kl+1)*eff_cor[ij][jk][kl]);
				}
	}

// trigger efficiency correction ends
  

     if((fg>3)&&(fg<(nfiles-2))){
        hist_pt[fg][ij][jk]->Scale(1./48191.824);
        }

    if(fg==(nfiles-2)) {
//	hist_pt[fg][ij][jk]->Scale(2054709090909.906*1./256644);
	hist_pt[fg][ij][jk]->Scale(1363000000000*1./293228);
//	hist_pt[fg][ij][jk]->Scale(1363000000000*1./77507.3);
    }

	

//    if(fg>0) { hist_pt[fg][ij][jk]->Scale(hist_pt[0][ij][jk]->Integral()*1./hist_pt[fg][ij][jk]->Integral()); }


    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
//    hist_pt[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05); 
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();    
    hist_pt[fg][ij][jk]->GetXaxis()->SetNoExponent();  

    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy (fb GeV^{-1})");
    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);  
//    hist_pt[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();
    
  }//jk
 }//ij


 cout<<filenames[fg]<<" read!"<<endl;
}//fg

TH1D *NP_factor[nalgo][netarange];

TFile *file_np = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/NP_Correction_Factor_Pythia.root","read");
file_np->cd();

if(nfiles>7){

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   sprintf(name,"NP_Correction_%s_EtaBin%i",JetRad[ij],jk+1);
   NP_factor[ij][jk] = (TH1D*)file_np->Get(name);
   NP_factor[ij][jk]->Smooth(5);
   for(int bn=0; bn<(hist_pt[nfiles-1][ij][jk]->GetNbinsX()); bn++){
        hist_pt[nfiles-1][ij][jk]->SetBinContent(bn+1,hist_pt[nfiles-1][ij][jk]->GetBinContent(bn+1)* NP_factor[ij][jk]->GetBinContent(bn+1));
        }
        hist_pt[nfiles-1][ij][jk]->Scale(1./(2*(ybin[jk+1]-ybin[jk])));//hist_pt[4][ij][jk]->Integral()*1./hist_pt[nfiles-1][ij][jk]->Integral());
  }
 }
}

for(int fg=0; fg<nfiles; fg++){
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

#ifdef TUnfold

   if(fg!=0) { 
			   hist_pt[fg][ij][jk]->Rebin(2); hist_pt[fg][ij][jk]->Scale(1./2);
			   hist_pt_org[fg][ij][jk]->Rebin(2); hist_pt_org[fg][ij][jk]->Scale(1./2);
			  }

#endif

   hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
   
//   if(fg>0) { hist_pt[fg][ij][jk]->Scale(hist_pt[0][ij][jk]->Integral()*1./hist_pt[fg][ij][jk]->Integral()); }
  }
 }
}

// Haate Kolome //

for(int fg=0; fg<nfiles; fg++){
   for(int jk=0; jk<netarange; jk++){

if(fg==2) {  
         for(int bn=0; bn<noptbins; bn++){
                float kfac = (hist_pt[1][nalgo-2][jk]->GetBinContent(bn+1) > 1.e-9) ? hist_pt[1][nalgo-1][jk]->GetBinContent(bn+1) *1./ hist_pt[1][nalgo-2][jk]->GetBinContent(bn+1) : 1;
                if(kfac > 1.e-6){
                hist_pt[fg][nalgo-1][jk]->SetBinContent(bn+1,kfac*hist_pt[fg][nalgo-1][jk]->GetBinContent(bn+1));
                        }                
                }
        }

if(fg==5||fg==7) {
         for(int bn=0; bn<noptbins; bn++){
                float kfac = (hist_pt[fg][nalgo-3][jk]->GetBinContent(bn+1) > 1.e-9) ? hist_pt[fg][nalgo-2][jk]->GetBinContent(bn+1) *1./ hist_pt[fg][nalgo-3][jk]->GetBinContent(bn+1) : 1;
                if(kfac > 1.e-6){
				  hist_pt[fg][nalgo-1][jk]->SetBinContent(bn+1,kfac*hist_pt[fg][nalgo-2][jk]->GetBinContent(bn+1));
                        }
					}
			}

if(fg==5 && jk==3)	{
		hist_pt[fg][nalgo-3][jk]->SetBinContent(13,hist_pt[fg][nalgo-3][jk]->GetBinContent(11)*hist_pt[1][nalgo-3][jk]->GetBinContent(13)/hist_pt[1][nalgo-3][jk]->GetBinContent(11));
		hist_pt[fg][nalgo-2][jk]->SetBinContent(13,hist_pt[fg][nalgo-2][jk]->GetBinContent(11)*hist_pt[1][nalgo-2][jk]->GetBinContent(13)/hist_pt[1][nalgo-2][jk]->GetBinContent(11));
		hist_pt[fg][nalgo-1][jk]->SetBinContent(13,hist_pt[fg][nalgo-1][jk]->GetBinContent(11)*hist_pt[1][nalgo-1][jk]->GetBinContent(13)/hist_pt[1][nalgo-1][jk]->GetBinContent(11));
		
		hist_pt[fg][nalgo-2][jk]->SetBinContent(15,hist_pt[fg][nalgo-2][jk]->GetBinContent(11)*hist_pt[1][nalgo-2][jk]->GetBinContent(15)/hist_pt[1][nalgo-2][jk]->GetBinContent(11));
		hist_pt[fg][nalgo-1][jk]->SetBinContent(15,hist_pt[fg][nalgo-1][jk]->GetBinContent(11)*hist_pt[1][nalgo-1][jk]->GetBinContent(15)/hist_pt[1][nalgo-1][jk]->GetBinContent(11));
		
		}	
		
if(fg==(nfiles-1) && jk==4)	{
		hist_pt[fg][3][jk]->SetBinContent(13,1.05*hist_pt[fg][3][jk]->GetBinContent(11)*hist_pt[1][3][jk]->GetBinContent(13)/hist_pt[1][3][jk]->GetBinContent(11));
		hist_pt[fg][3][jk]->SetBinContent(11,1.05*hist_pt[fg][3][jk]->GetBinContent(11)*hist_pt[1][3][jk]->GetBinContent(11)/hist_pt[1][3][jk]->GetBinContent(11));
//		hist_pt[fg][3][jk]->SetBinContent(10,0.95*hist_pt[fg][3][jk]->GetBinContent(10)*hist_pt[1][3][jk]->GetBinContent(10)/hist_pt[1][3][jk]->GetBinContent(9));

		hist_pt[fg][0][jk]->SetBinContent(3,0.7*hist_pt[fg][1][jk]->GetBinContent(3)*hist_pt[fg][1][jk]->GetBinContent(3)*1./hist_pt[fg][1][jk]->GetBinContent(3));
	//    hist_pt[fg][0][jk]->SetBinContent(5,hist_pt[fg][1][jk]->GetBinContent(5)*hist_pt[fg][1][jk]->GetBinContent(5)*1./hist_pt[fg][1][jk]->GetBinContent(5));
		hist_pt[fg][0][jk]->SetBinContent(15,hist_pt[fg][1][jk]->GetBinContent(15)*hist_pt[fg][1][jk]->GetBinContent(15)*1./hist_pt[fg][1][jk]->GetBinContent(15));
		hist_pt[fg][0][jk]->SetBinContent(16,0.5*hist_pt[fg][1][jk]->GetBinContent(16)*hist_pt[fg][1][jk]->GetBinContent(16)*1./hist_pt[fg][1][jk]->GetBinContent(16));

		}				
    }  
    
}

// Hate Kolome end //

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	for(int fg=0; fg<nfiles; fg++){
	  
   hist_radius[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt[fg][ref_rad][jk]) ;
   
   for(int bn=0; bn<(hist_radius[fg][ij][jk]->GetNbinsX()); bn++){
	//   if(fg!=(nfiles-2)){
	   if(fg>0){
	   hist_radius[fg][ij][jk]->SetBinError(bn+1,1.e-9); // plot w/o symbol
			}
			else{
				hist_radius[fg][ij][jk]->SetBinError(bn+1,1.e-9);
				}
	//   }
   }

   hist_radius[fg][ij][jk]->SetStats(0);

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.055);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();
   hist_radius[fg][ij][jk]->GetXaxis()->SetNoExponent();

   sprintf(name,"Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle(name);
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->SetNdivisions(406);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->SetMinimum(0);
   hist_radius[fg][ij][jk]->SetMaximum(3.);
   
   if(fg>0){
   hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
   hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
   hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC / Data");
   hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
   hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.075);
   hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.7);
   hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetTitleOffset(0.5);
   
   hist_pt_rat[fg-1][ij][jk]->SetLineColor(col[fg]);
   hist_pt_rat[fg-1][ij][jk]->SetMinimum(0.3);
   hist_pt_rat[fg-1][ij][jk]->SetMaximum(2.5);

   hist_pt_rat[fg-1][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
		}
   }
 }
}

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	  
	  double add_fac = (ij - ref_rad) * 0.25;
	  
	for(int bn=0; bn<noptbins; bn++){
		
		gr_rad_err_stat[ij][jk]->SetPoint(bn,hist_radius[0][ij][jk]->GetBinCenter(bn+1),hist_radius[0][ij][jk]->GetBinContent(bn+1)+add_fac);
		gr_rad_err_stat[ij][jk]->SetPointEYhigh(bn,hist_radius[0][ij][jk]->GetBinContent(bn+1)*rad_err_stat_up[ij][jk][bn]);
        gr_rad_err_stat[ij][jk]->SetPointEYlow(bn,hist_radius[0][ij][jk]->GetBinContent(bn+1)*rad_err_stat_dn[ij][jk][bn]);
		
		gr_rad_err_exp[ij][jk]->SetPoint(bn,hist_radius[0][ij][jk]->GetBinCenter(bn+1),hist_radius[0][ij][jk]->GetBinContent(bn+1)+add_fac);
		gr_rad_err_exp[ij][jk]->SetPointEYhigh(bn,hist_radius[0][ij][jk]->GetBinContent(bn+1)*rad_err_exp_up[ij][jk][bn]);
		gr_rad_err_exp[ij][jk]->SetPointEYlow(bn,hist_radius[0][ij][jk]->GetBinContent(bn+1)*rad_err_exp_dn[ij][jk][bn]);

        gr_rad_err_th[ij][jk]->SetPoint(bn,hist_radius[0][ij][jk]->GetBinCenter(bn+1),hist_radius[0][ij][jk]->GetBinContent(bn+1)+add_fac);
        gr_rad_err_th[ij][jk]->SetPointEYhigh(bn,hist_radius[0][ij][jk]->GetBinContent(bn+1)*rad_err_th_up[ij][jk][bn]);
        gr_rad_err_th[ij][jk]->SetPointEYlow(bn,hist_radius[0][ij][jk]->GetBinContent(bn+1)*rad_err_th_dn[ij][jk][bn]);

        gr_rad_err_expth[ij][jk]->SetPoint(bn,hist_radius[0][ij][jk]->GetBinCenter(bn+1),hist_radius[0][ij][jk]->GetBinContent(bn+1)+add_fac);
        gr_rad_err_expth[ij][jk]->SetPointEYhigh(bn,hist_radius[0][ij][jk]->GetBinContent(bn+1)*rad_err_expth_up[ij][jk][bn]);
        gr_rad_err_expth[ij][jk]->SetPointEYlow(bn,hist_radius[0][ij][jk]->GetBinContent(bn+1)*rad_err_expth_dn[ij][jk][bn]);

		}
	}
}

for(int fg=0; fg<nfiles; fg++){
cout<<filenames[fg]<<" nbins "<<hist_pt[fg][3][0]->GetNbinsX()<<endl;
}
	
//Compare_FinalAll(hist_pt,hist_pt_rat,hist_radius,hist_radius_rat,gr_pt_err_stat,gr_pt_err_exp,gr_pt_err_th,gr_pt_err_expth,gr_rad_err_stat,gr_rad_err_exp,gr_rad_err_th,gr_rad_err_expth);
//Compare_FinalUnfoldedRat(hist_pt,hist_pt_rat,hist_radius,hist_radius_rat,gr_pt_err_stat,gr_pt_err_exp,gr_pt_err_th,gr_rad_err_stat,gr_rad_err_exp,gr_rad_err_th);
//Compare_FinalUnfoldedRat_MC(hist_pt,hist_pt_rat,hist_radius,hist_radius_rat,gr_pt_err_stat,gr_pt_err_exp,gr_pt_err_th,gr_rad_err_stat,gr_rad_err_exp,gr_rad_err_th,gr_rad_err_expth);

//XSectionvsR(hist_pt,hist_pt_org,pt_err_stat_up,pt_err_exp_up,pt_err_th_up,pt_err_stat_dn,pt_err_exp_dn,pt_err_th_dn);
XSectionvsR_Ratio(hist_pt,hist_pt_org,hist_radius,pt_err_stat_up,pt_err_exp_up,pt_err_th_up,pt_err_stat_dn,pt_err_exp_dn,pt_err_th_dn);

}
