#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include <fstream>
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"

#define AK8_by_AK4

TString cmsText1     = "CMS";
float cmsTextFont1   = 61;

float lumiTextSize1     = 0.055;
float lumiTextOffset1   = 0.2;
float cmsTextSize1      = 0.06;
float cmsTextOffset1    = 0.1;

TString lumi_13TeV_2016 = "< 35.9 fb^{-1} (13 TeV)";

//#define TUnfold

Double_t f1(Double_t* x, Double_t* par){
	return  par[0];
}

char name[1000];

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

int main()
{
	
const int nfiles = 5;

const char *filenames[nfiles]; //= {//"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_Legacy_TUnfold.root",

filenames[0] =	"/home/suman/RooUnfold/Final/Unfolded_2016_Data_NTuple_MC_P8_Legacy_new_excor.root";	
	
#ifdef AK2_by_AK4
	
filenames[1] =	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK2_NLOJet.root";
filenames[2] =	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK2_NLOJet.root";
filenames[3] =	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK2_NLOJet.root";
filenames[4] =	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK2_NLOJet.root";

#endif

#ifdef AK8_by_AK4
	
filenames[1] =	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK8_NLOJet.root";
filenames[2] =	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK8_NLOJet.root";
filenames[3] =	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK8_NLOJet.root";
filenames[4] =	"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK8_NLOJet.root";

#endif


/*
		"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK2_NLOJet.root",
        "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK2_NLOJet.root",
        "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK2_NLOJet.root",
        "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK2_NLOJet.root"};	
*/
ifstream fp_rad_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/Total_ExpSys_Rad_excor_84_wAK4.log");
ifstream fp_rad_th("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Theory_Unc_Files/NP_Total_wAK4_Rad.log");
ifstream fp_rad_stat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/StatUnc_Plots/Unc_Rad_Jackknife_Stat_DataplusRM_84.log");

int icase;
#ifdef AK2_by_AK4
icase = 1;
#endif
#ifdef AK8_by_AK4
icase = 7;
#endif

const int ref_rad = 3;

const char *model_name_rad[nfiles] = {"Data","LO","LO#otimesNP","NLO","NLO#otimesNP"};

const char *model_save_rad[nfiles] = {"Data","LO","LONP","NLO","NLONP"};

const int col[nfiles] = {1,kMagenta-7,kMagenta+3,kGreen+2,kAzure+2};
const int mark_sty[nfiles] = {20,kOpenTriangleUp,kOpenTriangleDown,kFullStar,kOpenSquare};

static const int nalgo = 12;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

static const int nalgoAK8 = 8;
static const int netarange4 = 4 ;

//const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* jetname[nalgo] = {"R = 0.1","R = 0.2","R = 0.3","R = 0.4","R = 0.5","R = 0.6","R = 0.7","R = 0.8","R = 0.9","R = 1.0","R = 1.1","R = 1.2"};
const char* jetname_mod[nalgo] = {"ak1chs-0.75","ak2chs-0.5","ak3chs-0.25","ak4chs","ak5chs+0.25","ak6chs+0.5","ak7chs+0.75","ak8chs+1.0","ak9chs+1.25","ak10chs+1.5","ak11chs+1.75"/*,"ak12chs"*/};
const char* ybinname[netarange] = {"|y| < 0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int algo_col[nalgo] = {2,3,4,6,7,11,kCyan+2,kSpring-7, kBlue-7, kMagenta-9, kRed-5, kYellow-6};//{2,3,4,5,*/6,7,9,12,28,37,44,49};
const int algo_sty[nalgo] = {2,3,4,5,8,21,22,23,25,26,27,28};

static const float_t min_rad[nalgo] = {0.1,0.475,0.7,0.7,1.,1.,1.1,0.9,1.3,1.3,1.3,1.3};
static const float_t max_rad[nalgo] = {1.05,1.1,1.1,1.5,1.3,1.6,1.8,2.2,2.75,3.,3.5,3.5};

const int algo_style[nfiles] = {20,kOpenTriangleUp,kOpenTriangleDown,kFullStar,kOpenSquare};
const int line_sty[nfiles] = {kSolid,kDashed,kDashed,kSolid,kSolid};

const int onelinecol = kOrange;

const char *error_name[3] = {"Statistical Error","Exp. sys.","Exp+Theory sys."};
const char* err_name[2] = {"Exp. sys.","Scale+NP unc."};
const char* ref_err_name[2] = {"Exp Sys (AK4 in Data)","Theory Sys (AK4 in MC)"};
/*
const int noptbins = 31;
double ptbins[noptbins+1] = {74,97,133,174,220,272,330,395,468,548,638,737,846,967,1101,1248,1410,1588,1784,2000,2238,2500,2787,3103,3450,3832,4252,4713,5220,5777,6389,7000};
*/
const int noptbins = 61;
double ptbins[noptbins+1] = { 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

//double nlo_stat_err[noptbins] = {5.31045768231E-02,4.94867281510E-02,2.84668927094E-02,2.95894728951E-02,3.14722058764E-02,2.88881052916E-02,2.81441728675E-02,3.56059049168E-02,3.00509841993E-02,2.46892171021E-02,2.95190148010E-02,2.84292493782E-02,3.13734989231E-02,3.78934135344E-02,3.84014228589E-02,2.99585355276E-02,2.89576688563E-02,3.23908869757E-02,3.49212751568E-02,3.19682402941E-02,4.00852175622E-02,3.37360662389E-02,3.99820306973E-02,3.21277007233E-02,4.07314757479E-02,3.86298385663E-02,3.66275016885E-02,4.07813639883E-02,3.52102899453E-02,3.96220277631E-02,3.81606970714E-02,4.40453764686E-02,3.00099765298E-02,3.08318040360E-02,2.86077919969E-02,2.80455251987E-02,2.93054476042E-02,3.33983715654E-02,3.27870173137E-02,2.85175194831E-02,2.80890889141E-02,2.60687370272E-02,2.66854603373E-02,2.30993771557E-02,1.91024739004E-02,2.32405212121E-02,2.27361086605E-02,1.99509577082E-02,1.83177715049E-02,1.69125555370E-02,2.26974301063E-02,3.06117017256E-02,1.82752973301E-02,2.42207692770E-02,1.66029724968E-02,2.5E-02};

#ifdef AK8_by_AK4
double nlo_stat_err[noptbins] = {3.57916196730E-02,3.47166174931E-02,2.06239618990E-02,2.07539520722E-02,2.26615676335E-02,2.04910244486E-02,2.04472792423E-02,2.54952746151E-02,2.07168483553E-02,1.85640526583E-02,2.13081408866E-02,2.23598871805E-02,2.14976236704E-02,2.55046280508E-02,2.74813160302E-02,2.15891106252E-02,2.08993090887E-02,2.33952357761E-02,2.49868355417E-02,2.40641350010E-02,2.88985326294E-02,2.23493236893E-02,2.64618911621E-02,2.33470426809E-02,2.64285738390E-02,2.44760084157E-02,2.70404218114E-02,2.85008585986E-02,2.44143245593E-02,2.74713877827E-02,2.65721608649E-02,2.80463975396E-02,2.03488477078E-02,2.16389023873E-02,2.14288017000E-02,2.11549674946E-02,2.17180835747E-02,2.27230849576E-02,2.37133653655E-02,2.00667991574E-02,2.05393664408E-02,1.90326934491E-02,2.02827239432E-02,1.59866794221E-02,1.32805075937E-02,1.66528314978E-02,1.64930044641E-02,1.43775832085E-02,1.31041387685E-02,1.23054407343E-02,1.61192056063E-02,2.08088162692E-02,1.39088587695E-02,1.75146289474E-02,1.21881853587E-02,1.65138298880E-02};
#endif
//(AK8 by AK4)

#ifdef AK2_by_AK4
double nlo_stat_err[noptbins] = {7.33486122630E-02,5.72728791787E-02,6.70036513417E-02,4.15400554768E-02,3.52223184184E-02,2.80599710277E-02,2.77454389733E-02,2.98762381917E-02,3.01141244194E-02,3.08816424425E-02,3.27510704147E-02,3.28005609709E-02,3.90826721014E-02,3.82597870895E-02,3.38042860145E-02,3.77823529332E-02,3.71959244228E-02,3.74944656138E-02,3.79462622215E-02,3.38087787824E-02,3.77348723357E-02,3.81245858528E-02,4.36104115808E-02,4.62526200172E-02,4.08793023191E-02,4.58355892497E-02,4.59041584433E-02,4.12154957059E-02,4.11985759034E-02,3.83528478327E-02,3.73695674652E-02,3.82525888566E-02,3.65875975023E-02,4.14424588355E-02,3.69833636655E-02,3.77118730012E-02,3.49373776214E-02,3.21217438769E-02,3.50309285274E-02,3.91747311942E-02,3.35477576935E-02,3.05740942131E-02,2.89473229852E-02,2.87258994258E-02,2.59984652807E-02,2.90562388853E-02,2.97109409592E-02,2.62416210278E-02,2.44309359744E-02,2.35080733672E-02,2.08788981312E-02,2.28936814584E-02,2.01351952080E-02,2.18764695354E-02,2.01178857781E-02,1.85669031626E-02,2.02419423067E-02,2.03054288364E-02};
#endif
//(AK2 by AK4)

double max_range = 2588.;
double min_range = 84.;

static const int noptbins_sven = 43;
	
	
double rad_err_exp_up[nalgo][netarange][noptbins]={{{0}}};
double rad_err_exp_dn[nalgo][netarange][noptbins]{{{0}}};

double rad_err_th_up[nalgo][netarange][noptbins+1]{{{0}}};
double rad_err_th_dn[nalgo][netarange][noptbins+1]{{{0}}};

double rad_err_stat_up[nalgo][netarange][noptbins]{{{0}}};
double rad_err_stat_dn[nalgo][netarange][noptbins]{{{0}}};

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_y[nfiles][nalgo];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_y_rat[nfiles-1][nalgo];
TH1D* hist_pt_org[nfiles][nalgo][netarange];

TH1D *hist_pt_nll[nalgoAK8][netarange4];

TH1D* hist_radius[nfiles][nalgo][netarange];
TH1D* hist_radius_rat[nfiles-1][nalgo][netarange];

TH1D* hist_radius_nll[nalgoAK8][netarange4];

TGraphAsymmErrors *gr_rad_err_stat[nalgo][netarange];
TGraphAsymmErrors *gr_rad_err_exp[nalgo][netarange];
TGraphAsymmErrors *gr_rad_err_th[nalgo][netarange];

TMultiGraph *mul_gr_rad_err[nalgo][netarange];

TFile *fileout = new TFile("Ratio_NLO_Fig5b.root","RECREATE");

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	
	int nPT = noptbins;
	#ifdef TUnfold  
	nPT = 2*noptbins - 1;
	#endif
     for(int kl=0; kl<nPT; kl++){
	     int xx1,xx2,xx3;
	
	     fp_rad_exp>>xx1>>xx2>>xx3>>rad_err_exp_up[ij][jk][kl]>>rad_err_exp_dn[ij][jk][kl];
         fp_rad_stat>>xx1>>xx2>>xx3>>rad_err_stat_up[ij][jk][kl]>>rad_err_stat_dn[ij][jk][kl];
  
		}
		for(int kl=0; kl<(nPT+1); kl++){
			int xx1,xx2,xx3;
			fp_rad_th>>xx1>>xx2>>xx3>>rad_err_th_up[ij][jk][kl]>>rad_err_th_dn[ij][jk][kl];
//			cout<<ij+1<<" "<<jk+1<<" "<<kl+1<<" "<<rad_err_th_up[ij][jk][kl]<<endl;
		}
     }
   }


TH1D *scale_up;
TH1D *scale_dn;
//TFile *file0 = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK2_NLOJet.root","read");
sprintf(name,"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK%i_NLOJet.root",icase+1);
//TFile *file0 = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Rad_Difference/RatioFile_AK8_NLOJet.root","read");
TFile *file0 = new TFile(name,"read");
sprintf(name,"Scale_Unc_JetpT_ak%i_EtaBin1_Up",icase+1);
scale_up = (TH1D*)file0->Get(name);
sprintf(name,"Scale_Unc_JetpT_ak%i_EtaBin1_Dn",icase+1);
scale_dn = (TH1D*)file0->Get(name);

scale_up->Smooth();
scale_dn->Smooth();

for(int kl=0; kl<(noptbins+1); kl++){
//	    cout<<"pt "<<kl+1<<" np unc "<<rad_err_th_up[icase][0][kl]<<" scale unc "<<scale_up->GetBinContent(kl+1)<<'\t';
		rad_err_th_up[icase][0][kl] = sqrt(pow(rad_err_th_up[icase][0][kl],2) + pow(scale_up->GetBinContent(kl+1),2));
		rad_err_th_dn[icase][0][kl] = sqrt(pow(rad_err_th_dn[icase][0][kl],2) + pow(scale_dn->GetBinContent(kl+1),2));
//		cout<<"add "<<rad_err_th_up[icase][0][kl]<<endl;
		}

TFile *filein;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

	gr_rad_err_exp[ij][jk] = new TGraphAsymmErrors();

	gr_rad_err_th[ij][jk] = new TGraphAsymmErrors();

    gr_rad_err_stat[ij][jk] = new TGraphAsymmErrors();
    

  }//jk
}//ij

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
  
     if(fg==0){ sprintf(name,"svd_unfold_%s_Etabin%i",JetRad[ij],jk+1) ; }
	 else{
		if(fg==(1)||fg==(2)) {sprintf(name,"JetpT_%s_EtaBin%i_LO",JetRad[ij],jk+1);} 
		if(fg==(3)||fg==(4)) {sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
		//if(fg==4) {sprintf(name,"JetpT_%s_EtaBin%i_Inf",JetRad[ij],jk+1);} 
       }  

    hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
    hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();    
    hist_pt[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
    hist_pt[fg][ij][jk]->GetXaxis()->SetNoExponent();
    
        
    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
  }//jk
 }//ij
 cout<<filenames[fg]<<" read!"<<endl;
}//fg	

TFile *filesven = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/Sven/R2/numbers/xsec/Output_NLLNLO_AllpT.root","read");

for(int ij=0; ij<nalgoAK8; ij++){
  for(int jk=0; jk<netarange4; jk++){
	  sprintf(name,"Xsec_Sven_%s_Eta%i",JetRad[ij],jk+1) ; 
	  hist_pt_nll[ij][jk] = (TH1D*)filesven->Get(name);
  }
}


TH1D *NP_factor[nalgo][netarange];

//TFile *file_np = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/NP_Correction_Factor_Pythia.root","read");
TFile *file_np = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/NP_Fig2_Final.root","read");
file_np->cd();

if(nfiles>1){

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

//   sprintf(name,"NP_Correction_radius_%s_EtaBin%i",JetRad[ij],jk+1);
	 sprintf(name,"NP_Cor_Full_AK%i_Eta%i",ij+1,jk+1);
	 
     NP_factor[ij][jk] = (TH1D*)file_np->Get(name);
   
   for(int bn=0; bn<(hist_pt[nfiles-1][ij][jk]->GetNbinsX()); bn++){
        
        hist_pt[nfiles-1][ij][jk]->SetBinContent(bn+1,hist_pt[nfiles-1][ij][jk]->GetBinContent(bn+1)* NP_factor[ij][jk]->GetBinContent(bn+1));
        hist_pt[nfiles-3][ij][jk]->SetBinContent(bn+1,hist_pt[nfiles-3][ij][jk]->GetBinContent(bn+1)* NP_factor[ij][jk]->GetBinContent(bn+1));
        
        if(bn>=6 && bn<=50 && (ij<8 && jk<4)){
			hist_pt_nll[ij][jk]->SetBinContent(bn+1-6,hist_pt_nll[ij][jk]->GetBinContent(bn+1-6)* NP_factor[ij][jk]->GetBinContent(bn+1));
			}
        }
  }
 }
}

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	for(int fg=0; fg<nfiles; fg++){
	  
   hist_radius[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
   if(fg==0){
   hist_radius[fg][ij][jk]->Divide(hist_pt[fg][ref_rad][jk]) ;
	}
	if(fg==(nfiles-1)){
   for(int bn=0; bn<(hist_radius[fg][ij][jk]->GetNbinsX()); bn++){
	   hist_radius[fg][ij][jk]->SetBinError(bn+1,nlo_stat_err[bn]*hist_radius[fg][ij][jk]->GetBinContent(bn+1));
	 }
	 hist_radius[fg][ij][jk]->SetMarkerSize(0);
	}

   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)") ;
   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.055);
   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelOffset(0.015);
   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

   sprintf(name,"Ratio of d^{ 2}#sigma / dp_{T}dy w.r.t. AK4 jets");
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle(name);
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.06);
   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleOffset(1.1);
   hist_radius[fg][ij][jk]->GetYaxis()->SetNdivisions(406);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.055);
   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelOffset(0.015);
   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_radius[fg][ij][jk]->SetMinimum(0);
   hist_radius[fg][ij][jk]->SetMaximum(3.);
  
   }
  }
}
  
  TGraphAsymmErrors *gr_radius_nll[nalgoAK8][netarange4];
  
  for(int ij=0; ij<nalgoAK8; ij++){
	for(int jk=0; jk<netarange4; jk++){
		
		hist_radius_nll[ij][jk] = (TH1D*)hist_pt_nll[ij][jk]->Clone();
		hist_radius_nll[ij][jk]->Divide(hist_pt_nll[ref_rad][jk]);
		
		double xval[noptbins_sven], yval[noptbins_sven], yerr[noptbins_sven];
		
		for(int bn=0; bn<(hist_radius_nll[ij][jk]->GetNbinsX()); bn++){
			hist_radius_nll[ij][jk]->SetBinError(bn+1,0);
			xval[bn] = hist_radius_nll[ij][jk]->GetBinCenter(bn+1);
			yval[bn] = hist_radius_nll[ij][jk]->GetBinContent(bn+1);
			yerr[bn] = fabs(hist_pt_nll[ij][jk]->GetBinError(bn+1)*1./hist_pt_nll[ij][jk]->GetBinContent(bn+1) - hist_pt_nll[ref_rad][jk]->GetBinError(bn+1)*1./hist_pt_nll[ref_rad][jk]->GetBinContent(bn+1));
			yerr[bn] *= yval[bn];
		}
   
		gr_radius_nll[ij][jk] = new TGraphAsymmErrors(noptbins_sven,xval,yval,NULL,NULL,yerr,yerr);
   
		hist_radius_nll[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)") ;
		hist_radius_nll[ij][jk]->GetXaxis()->SetTitleSize(0.06);
		hist_radius_nll[ij][jk]->GetXaxis()->SetLabelSize(0.055);
		hist_radius_nll[ij][jk]->GetXaxis()->CenterTitle();

		sprintf(name,"Ratio of d^{ 2}#sigma / dp_{T}dy w.r.t. AK4 jets");
		hist_radius_nll[ij][jk]->GetYaxis()->SetTitle(name);
		hist_radius_nll[ij][jk]->GetYaxis()->SetTitleSize(0.05);
		hist_radius_nll[ij][jk]->GetYaxis()->SetNdivisions(406);
		hist_radius_nll[ij][jk]->GetYaxis()->SetLabelSize(0.05);
		hist_radius_nll[ij][jk]->GetYaxis()->CenterTitle();

		hist_radius_nll[ij][jk]->SetMinimum(0);
		hist_radius_nll[ij][jk]->SetMaximum(3.);
		
		hist_radius_nll[ij][jk]->SetLineWidth(2);
		
		gr_radius_nll[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (GeV)") ;
		gr_radius_nll[ij][jk]->GetXaxis()->SetTitleSize(0.06);
		gr_radius_nll[ij][jk]->GetXaxis()->SetLabelSize(0.055);
		gr_radius_nll[ij][jk]->GetXaxis()->CenterTitle();

		sprintf(name,"Ratio of d^{ 2}#sigma / dp_{T}dy w.r.t. AK4 jets");
		gr_radius_nll[ij][jk]->GetYaxis()->SetTitle(name);
		gr_radius_nll[ij][jk]->GetYaxis()->SetTitleSize(0.05);
		gr_radius_nll[ij][jk]->GetYaxis()->SetNdivisions(406);
		gr_radius_nll[ij][jk]->GetYaxis()->SetLabelSize(0.05);
		gr_radius_nll[ij][jk]->GetYaxis()->CenterTitle();

		gr_radius_nll[ij][jk]->SetMinimum(0);
		gr_radius_nll[ij][jk]->SetMaximum(3.);
		
		gr_radius_nll[ij][jk]->SetMarkerStyle(kMultiply);
		gr_radius_nll[ij][jk]->SetMarkerColor(kOrange+7);
		gr_radius_nll[ij][jk]->SetLineColor(kOrange+7);
  }
}

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	 
	for(int bn=0; bn<noptbins; bn++){
		
		gr_rad_err_stat[ij][jk]->SetPoint(bn+1,hist_radius[0][ij][jk]->GetBinCenter(bn+2),hist_radius[0][ij][jk]->GetBinContent(bn+2));
		gr_rad_err_stat[ij][jk]->SetPointEYhigh(bn+1,hist_radius[0][ij][jk]->GetBinContent(bn+2)*rad_err_stat_up[ij][jk][bn]);
        gr_rad_err_stat[ij][jk]->SetPointEYlow(bn+1,hist_radius[0][ij][jk]->GetBinContent(bn+2)*rad_err_stat_dn[ij][jk][bn]);
		
		gr_rad_err_exp[ij][jk]->SetPoint(bn+1,hist_radius[0][ij][jk]->GetBinCenter(bn+2),hist_radius[0][ij][jk]->GetBinContent(bn+2));
		gr_rad_err_exp[ij][jk]->SetPointEYhigh(bn+1,hist_radius[0][ij][jk]->GetBinContent(bn+2)*rad_err_exp_up[ij][jk][bn]);
		gr_rad_err_exp[ij][jk]->SetPointEYlow(bn+1,hist_radius[0][ij][jk]->GetBinContent(bn+2)*rad_err_exp_dn[ij][jk][bn]);
		gr_rad_err_exp[ij][jk]->SetPointEXhigh(bn+1,0.5*(ptbins[bn+1]-ptbins[bn]));
		gr_rad_err_exp[ij][jk]->SetPointEXlow(bn+1,0.5*(ptbins[bn+1]-ptbins[bn]));

        gr_rad_err_th[ij][jk]->SetPoint(bn+1,hist_radius[nfiles-1][ij][jk]->GetBinCenter(bn+2),hist_radius[nfiles-1][ij][jk]->GetBinContent(bn+2));
        gr_rad_err_th[ij][jk]->SetPointEYhigh(bn+1,hist_radius[nfiles-1][ij][jk]->GetBinContent(bn+2)*rad_err_th_up[ij][jk][bn+1]);
        gr_rad_err_th[ij][jk]->SetPointEYlow(bn+1,hist_radius[nfiles-1][ij][jk]->GetBinContent(bn+2)*rad_err_th_dn[ij][jk][bn+1]);
		gr_rad_err_th[ij][jk]->SetPointEXhigh(bn+1,0.5*(ptbins[bn+1]-ptbins[bn]));
		gr_rad_err_th[ij][jk]->SetPointEXlow(bn+1,0.5*(ptbins[bn+1]-ptbins[bn]));

//		if(ij==icase && jk==0){
//			cout<<"bin "<<bn+1<<" ratio "<<hist_radius[0][ij][jk]->GetBinContent(bn+2)<<" rad up "<<rad_err_exp_up[ij][jk][bn]<<" rad dn "<<rad_err_exp_dn[ij][jk][bn]<<" tot up "<<hist_radius[0][ij][jk]->GetBinContent(bn+2)*rad_err_exp_up[ij][jk][bn]<<" tot dn "<<hist_radius[0][ij][jk]->GetBinContent(bn+2)*rad_err_exp_dn[ij][jk][bn]<<endl;
//			}
		
		}
		
		gr_rad_err_stat[ij][jk]->SetPoint(0,hist_radius[0][ij][jk]->GetBinCenter(1),hist_radius[0][ij][jk]->GetBinContent(2));
		gr_rad_err_stat[ij][jk]->SetPointEYhigh(0,hist_radius[0][ij][jk]->GetBinContent(2)*rad_err_stat_up[ij][jk][0]);
		gr_rad_err_stat[ij][jk]->SetPointEYlow(0,hist_radius[0][ij][jk]->GetBinContent(2)*rad_err_stat_up[ij][jk][0]);
		
		gr_rad_err_exp[ij][jk]->SetPoint(0,hist_radius[0][ij][jk]->GetBinCenter(1),hist_radius[0][ij][jk]->GetBinContent(2));
		gr_rad_err_exp[ij][jk]->SetPointEYhigh(0,hist_radius[0][ij][jk]->GetBinContent(2)*rad_err_exp_up[ij][jk][0]);
		gr_rad_err_exp[ij][jk]->SetPointEYlow(0,hist_radius[0][ij][jk]->GetBinContent(2)*rad_err_exp_dn[ij][jk][0]);
		
		gr_rad_err_th[ij][jk]->SetPoint(0,hist_radius[0][ij][jk]->GetBinCenter(1),hist_radius[nfiles-1][ij][jk]->GetBinContent(2));
		gr_rad_err_th[ij][jk]->SetPointEYhigh(0,hist_radius[0][ij][jk]->GetBinContent(2)*rad_err_th_up[ij][jk][0]);
		gr_rad_err_th[ij][jk]->SetPointEYlow(0,hist_radius[0][ij][jk]->GetBinContent(2)*rad_err_th_dn[ij][jk][0]);
		
	}
} 

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

TCanvas *c2_rad[1][netarange];
TLegend *leg2_rad[1][netarange];
TLegend *leg2_err[1][netarange];

gStyle->SetErrorX(0);


for(int ij=0; ij<(nalgo); ij++){
  for(int jk=0; jk<1; jk++){
	  
     if(!(ij==icase && jk==0)) continue;	 
  
//	 int ij=1; int jk=0;
     int hh=0; 
	  
	sprintf(name,"RadRatio_NLO_Canv_EtaBin%i_JetRadReg%i",jk+1,ij+1);
    c2_rad[ij][jk] = tdrCanvas(name,hist_radius[0][ij][jk],7,0);

	leg2_rad[hh][jk] = tdrLeg(0.43,0.625,0.9,0.9);
	leg2_rad[hh][jk]->SetTextSize(0.04);
	leg2_rad[hh][jk]->SetTextFont(42);
	
	if(ij<0){
	leg2_err[hh][jk] = tdrLeg(0.15,0.75,0.3,0.9);
	}
	else{
		leg2_err[hh][jk] = tdrLeg(0.7,0.75,0.9,0.9);
		}
	
	leg2_err[hh][jk]->SetTextFont(42);
	leg2_err[hh][jk]->SetTextSize(0.04);

	c2_rad[ij][jk]->cd(1);
	
	
	gPad->SetLogx(1);
	gPad->SetLogy(0);

	TLatex latex;
	latex.SetNDC();
	latex.SetTextAngle(0);
	latex.SetTextColor(kBlack);

	latex.SetTextFont(42);
	latex.SetTextAlign(31);
	latex.SetTextSize(0.05);

    TString text0;
	text0+=  jetname[ij];
	TString text1;
	text1+=  ybinname[jk];
	TString text2;
    text2+= "Anti-k_{T}";

	leg_x1 = 0.3;
	leg_x2 = 0.7;
	leg_y1 = 0.85;

	latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.16,leg_y1,text2);
	latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.16,leg_y1-0.06,text0);
	latex.DrawLatex(0.5*(leg_x1+leg_x2)-0.16,leg_y1-0.12,text1);
  
	hist_radius[0][ij][jk]->SetMarkerSize(1.35);
	tdrDraw(hist_radius[0][ij][jk],"][ : E: X0",algo_style[0],col[0],line_sty[0],col[0],1001,0);
	leg2_rad[hh][jk]->AddEntry(hist_radius[0][ij][jk],model_name_rad[0],"p"); 

	gr_rad_err_th[ij][jk]->SetFillColorAlpha(kBlue-10,0.8);//kAzure-9,0.75);//kBlue-10,0.85);
	gr_rad_err_th[ij][jk]->SetLineColor(kBlue-10);
	gr_rad_err_th[ij][jk]->SetFillStyle(1002);
	gr_rad_err_th[ij][jk]->Draw("SAME:E3");
	/*
	for(int bn=0; bn<(noptbins); bn++){
		gr_rad_err_exp[ij][jk]->SetPoint(bn,hist_radius[0][ij][jk]->GetBinCenter(bn+1),hist_radius[0][ij][jk]->GetBinContent(bn+1));
	}
	*/	
	gr_rad_err_exp[ij][jk]->SetFillColorAlpha(kYellow-3,0.7);
	gr_rad_err_exp[ij][jk]->SetLineColor(kYellow-3);
	gr_rad_err_exp[ij][jk]->SetFillStyle(1001);
	gr_rad_err_exp[ij][jk]->SetLineWidth(-2002);
	gr_rad_err_exp[ij][jk]->Draw("SAME:E3");
	
	hist_radius[0][ij][jk]->GetXaxis()->SetTitleOffset(0.8);
	hist_radius[0][ij][jk]->GetYaxis()->SetTitleOffset(1.15);
	
    tdrDraw(hist_radius[0][ij][jk],"][ : E : X0",algo_style[0],col[0],line_sty[0],col[0],1001,0);
    
    for(int bn=0; bn<(noptbins); bn++){
		gr_rad_err_stat[ij][jk]->SetPoint(bn,hist_radius[0][ij][jk]->GetBinCenter(bn+1),hist_radius[0][ij][jk]->GetBinContent(bn+1));
	}   
    gr_rad_err_stat[ij][jk]->SetLineColor(kBlack);
	gr_rad_err_stat[ij][jk]->SetFillColor(5);
	gr_rad_err_stat[ij][jk]->SetFillStyle(3010);
	gr_rad_err_stat[ij][jk]->Draw("SAME:EZ");

	
	tdrDraw(hist_radius_nll[ij][jk],"][",kMultiply,kOrange+7,kSolid,kOrange+7,1001,0);
	gr_radius_nll[ij][jk]->SetFillColorAlpha(kOrange+7,0.5);
//	gr_radius_nll[ij][jk]->Draw("E3");

	 for(int fg=1; fg<(nfiles); fg++){
        //    if(fg<(nfiles-1)) continue;	
			hist_radius[fg][ij][jk]->SetLineWidth(2);
            tdrDraw(hist_radius[fg][ij][jk],"][",algo_style[fg],col[fg],line_sty[fg],col[fg] ,1001,0);
            if(fg<(nfiles-1)){
            leg2_rad[hh][jk]->AddEntry(hist_radius[fg][ij][jk],model_name_rad[fg],"l"); 
				}
				else{
					leg2_rad[hh][jk]->AddEntry(hist_radius[fg][ij][jk],model_name_rad[fg],"lp"); 
					}
			}//fg

		hist_radius[nfiles-1][ij][jk]->Draw("hist:SAME,][");
		
		leg2_rad[hh][jk]->AddEntry(hist_radius_nll[ij][jk],"(NLO+NLL)#otimesNP","l"); 

		leg2_err[hh][jk]->AddEntry(gr_rad_err_exp[icase][jk],err_name[0],"f");
		leg2_err[hh][jk]->AddEntry(gr_rad_err_th[icase][jk],err_name[1],"f");
		
		
		leg2_err[hh][jk]->Draw();
		
		gPad->RedrawAxis();
		
//		sprintf(name,"All_Final/TUnfold_Legacy/RCombined/Radius/%s.eps",c2_rad[fg][jk]->GetName());
		sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/SVD/RadiusRatio/NLL/%s.pdf",c2_rad[ij][jk]->GetName());
		c2_rad[ij][jk]->SaveAs(name);
		sprintf(name,"All_Final/RooUnfold_Legacy_Excor_new/SVD/RadiusRatio/NLL/%s.png",c2_rad[ij][jk]->GetName());
		c2_rad[ij][jk]->SaveAs(name);
		
		fileout->cd();
		
		sprintf(name,"Cross_section_ratio_%s_by_%s_ybin%i_Data",JetRad[ij],JetRad[3],jk+1);
		hist_radius[0][ij][jk]->SetName(name);
		sprintf(name,"Cross section ratio %s/%s %s %s",JetRad[ij],JetRad[3],ybinname[jk],model_name_rad[0]);
		hist_radius[0][ij][jk]->SetTitle(name);
		hist_radius[0][ij][jk]->Write();
		
		sprintf(name,"Cross_section_ratio_%s_by_%s_ybin%i_NLONLLNP",JetRad[ij],JetRad[3],jk+1);
		hist_radius_nll[ij][jk]->SetName(name);
		sprintf(name,"Cross section ratio %s/%s %s (NLO+NLL)#otimesNP",JetRad[ij],JetRad[3],ybinname[jk]);
		hist_radius_nll[ij][jk]->SetTitle(name);
		hist_radius_nll[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
		hist_radius_nll[ij][jk]->Write();
		
		sprintf(name,"Cross_section_ratio_with_theory_sys_%s_by_%s_ybin%i",JetRad[ij],JetRad[3],jk+1);
		gr_rad_err_th[ij][jk]->SetName(name);
		sprintf(name,"Cross section ratio %s/%s %s %s with theoretical systematic uncertainty",JetRad[ij],JetRad[3],ybinname[jk],model_name_rad[4]);
		gr_rad_err_exp[ij][jk]->SetTitle(name);
		gr_rad_err_th[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
		gr_rad_err_th[ij][jk]->Write();
		sprintf(name,"Cross_section_ratio_with_exp_sys_%s_by_%s_ybin%i",JetRad[ij],JetRad[3],jk+1);
		gr_rad_err_exp[ij][jk]->SetName(name);
		sprintf(name,"Cross section ratio %s/%s %s %s with experimental systematic uncertainty",JetRad[ij],JetRad[3],ybinname[jk],model_name_rad[0]);
		gr_rad_err_exp[ij][jk]->SetTitle(name);
		gr_rad_err_exp[ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);
		gr_rad_err_exp[ij][jk]->Write();
		
		for(int fg=1; fg<(nfiles); fg++){
        
            sprintf(name,"Cross_section_ratio_%s_by_%s_ybin%i_%s",JetRad[ij],JetRad[3],jk+1,model_save_rad[fg]);
			hist_radius[fg][ij][jk]->SetName(name);
			sprintf(name,"Cross section ratio %s/%s %s %s",JetRad[ij],JetRad[3],ybinname[jk],model_name_rad[fg]);
			hist_radius[fg][ij][jk]->SetTitle(name);
			hist_radius[fg][ij][jk]->SetLineWidth(2);
            hist_radius[fg][ij][jk]->Write();
            
		}//fg
	 
	 
	  }//jk
	}//ij

fileout->Write();
fileout->Close();

}
