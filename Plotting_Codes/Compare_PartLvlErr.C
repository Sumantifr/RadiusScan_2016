	//#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
	#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

	#include "TFile.h"
	#include "TH1D.h"
	#include <iostream>
	#include <fstream>
	#include "TGraphAsymmErrors.h"
	#include "TMultiGraph.h"

	void Compare_PartLvlErr()
	{
	int ialgo = 0;
	int ieta = 0;

	//cout<<"AK ? Etabin ?\n";
	//cin>>ialgo>>ieta;

	ialgo-=1;
	ieta-=1;

	const int nfiles = 9;
	//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_nocor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_Pythia_Userhook2_NNPDF30.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/HerwigEE5C_Files_sel.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/CP5_tune/hist_Powheg_Pythia_LHAPDF_CP5.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/CT14nlo_files.root"};

	//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_Pythia_Userhook2_NNPDF30.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/HerwigEE5C_Files_sel.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/CP5_tune/hist_Powheg_Pythia_LHAPDF_CP5.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/CT14nlo_files.root"};

	//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor_84.root"/*Unfolded_2016_Data_NTuple_MC_P8_excorfac2_84.root"*/,"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_excorfac2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/Bin84_hist_Powheg_Pythia_Userhook2_NNPDF30.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/Bin84_HerwigEE5C_Files.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/CP5_tune/Bin84_hist_Powheg_Pythia_LHAPDF_CP5.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Herwig7/Bin84_hist_Herwig7_weighted.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Bin84_CT14nlo_files.root"};

	const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor_84.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_nocorN.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50_nocorN.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_nocorN.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/Bin84_hist_Powheg_Pythia_Userhook2_NNPDF30.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/Bin84_HerwigEE5C_Files.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/CP5_tune/Bin84_hist_Powheg_Pythia_LHAPDF_CP5.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Herwig7/Bin84_hist_Herwig7_weighted.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/Bin84_CT14nlo_files.root"};

	//const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/Summer_Files/Pythia_Summer16_CMSSW8X21_Run2_v2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/hist_Powheg_Pythia_Userhook2_NNPDF30.root"};


	//ifstream fp_pt_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_ExpSys_Pt_excor_84.log");
	ifstream fp_pt_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_ExpSys_Pt_84.log");
	ifstream fp_rad_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_ExpSys_Rad_excor_84.log");

	ifstream fp_pt_th("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_Theory_Unc_Pt_84.log");
	ifstream fp_rad_th("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_Theory_Unc_Rad_84.log");

	ifstream fp_pt_stat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/StatUnfold_Pt.log");
	ifstream fp_rad_stat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/RM_Unc_Rad_84.log");

	const int ref = 3;

	const char *model_name[nfiles] = {"Data 2016","Pythia8","Madgraph","Herwig++","PH+P8(CUETP8M1)","PH+Hwg(EE5C)","PH+P8(CP5)","Herwig7","NLO#otimesNP"};
	const int col[nfiles] = {1,6,2,4,3,9,kRed-6,12,kCyan+3};
	const int mark_sty[nfiles] = {20,21,22,23,24,25,30,27,26};

	static const int nalgo = 12;
	static const int netarange = 10 ;

	const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
	double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

	const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
	const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

	const int noptbins = 61;
	double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64, 74,*/ 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

	TString cmsText     = "  CMS";
	TString extraText   = "Preliminary";
	float cmsTextFont   = 61;

	float lumiTextSize     = 0.055;
	float lumiTextOffset   = 0.2;
	float cmsTextSize      = 0.06;
	float cmsTextOffset    = 0.1;

	TString lumi_13TeV_BCDEFGH = "2016 33.4 fb^{-1} (13 TeV)";

	double pt_err_exp_up[nalgo][netarange][noptbins];
	double pt_err_exp_dn[nalgo][netarange][noptbins];
	double rad_err_exp_up[nalgo][netarange][noptbins];
	double rad_err_exp_dn[nalgo][netarange][noptbins];

	double pt_err_th_up[nalgo][netarange][noptbins];
	double pt_err_th_dn[nalgo][netarange][noptbins];
	double rad_err_th_up[nalgo][netarange][noptbins];
	double rad_err_th_dn[nalgo][netarange][noptbins];

	double pt_err_stat_up[nalgo][netarange][noptbins];
	double pt_err_stat_dn[nalgo][netarange][noptbins];
	double rad_err_stat_up[nalgo][netarange][noptbins];
	double rad_err_stat_dn[nalgo][netarange][noptbins];

	const char *error_name[3] = {"Statistical Error","Exp Sys","Exp+Theory Sys"};

	for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){
	     for(int kl=0; kl<noptbins; kl++){
		     int xx1,xx2,xx3;
		     fp_pt_exp>>xx1>>xx2>>xx3>>pt_err_exp_up[ij][jk][kl]>>pt_err_exp_dn[ij][jk][kl];
		     fp_rad_exp>>xx1>>xx2>>xx3>>rad_err_exp_up[ij][jk][kl]>>rad_err_exp_dn[ij][jk][kl];
		     fp_pt_th>>xx1>>xx2>>xx3>>pt_err_th_up[ij][jk][kl]>>pt_err_th_dn[ij][jk][kl];
		     fp_rad_th>>xx1>>xx2>>xx3>>rad_err_th_up[ij][jk][kl]>>rad_err_th_dn[ij][jk][kl];
		     fp_pt_stat>>xx1>>xx2>>xx3>>pt_err_stat_up[ij][jk][kl]>>pt_err_stat_dn[ij][jk][kl];
		     fp_rad_stat>>xx1>>xx2>>xx3>>rad_err_stat_up[ij][jk][kl]>>rad_err_stat_dn[ij][jk][kl];
	/*
		     if(ij<2 && jk>4){
			pt_err_exp_up[ij][jk][kl] *= 1./10;
			pt_err_exp_dn[ij][jk][kl] *= 1./10;
			}
	*/
		    if(pt_err_exp_up[ij][jk][kl] >0.999) { pt_err_exp_up[ij][jk][kl] = 0.;}
		    if(pt_err_exp_dn[ij][jk][kl] >0.999) { pt_err_exp_dn[ij][jk][kl] = 0.;}
		    if(rad_err_exp_up[ij][jk][kl] >0.999) { rad_err_exp_up[ij][jk][kl] = 0.;}
		    if(rad_err_exp_dn[ij][jk][kl] >0.999) { rad_err_exp_dn[ij][jk][kl] = 0.;}
		    

		     if(ij==2&&jk==4){
			cout<<"pt "<<kl+1<<" pt up "<<pt_err_stat_up[ij][jk][kl]<<" dn "<<pt_err_stat_dn[ij][jk][kl]<<endl;
			}
	/*
		     pt_err_exp_up[ij][jk][kl] = sqrt(pow(pt_err_stat_up[ij][jk][kl],2)+pow(pt_err_exp_up[ij][jk][kl],2));
		     pt_err_exp_dn[ij][jk][kl] = sqrt(pow(pt_err_stat_dn[ij][jk][kl],2)+pow(pt_err_exp_dn[ij][jk][kl],2));
		     rad_err_exp_up[ij][jk][kl] = sqrt(pow(rad_err_stat_up[ij][jk][kl],2)+pow(rad_err_exp_up[ij][jk][kl],2));
		     rad_err_exp_dn[ij][jk][kl] = sqrt(pow(rad_err_stat_dn[ij][jk][kl],2)+pow(rad_err_exp_dn[ij][jk][kl],2));
	*/
		     pt_err_th_up[ij][jk][kl] = sqrt(pow(pt_err_th_up[ij][jk][kl],2)+pow(pt_err_exp_up[ij][jk][kl],2));
		     pt_err_th_dn[ij][jk][kl] = sqrt(pow(pt_err_th_dn[ij][jk][kl],2)+pow(pt_err_exp_dn[ij][jk][kl],2));
		     rad_err_th_up[ij][jk][kl] = sqrt(pow(rad_err_th_up[ij][jk][kl],2)+pow(rad_err_exp_up[ij][jk][kl],2));
		     rad_err_th_dn[ij][jk][kl] = sqrt(pow(rad_err_th_dn[ij][jk][kl],2)+pow(rad_err_exp_dn[ij][jk][kl],2));
		}
	     }
	   }

	char name[1000];

	TFile *filein;

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

	TGraphAsymmErrors *gr_rad_err_stat[nalgo][netarange];
	TGraphAsymmErrors *gr_rad_err_exp[nalgo][netarange];
	TGraphAsymmErrors *gr_rad_err_th[nalgo][netarange];

	TMultiGraph *mul_gr_pt_err[nalgo][netarange];
	TMultiGraph *mul_gr_rad_err[nalgo][netarange];

	double max_range = 3000.;
	double min_range = 84.;

	TLine *line = new TLine(min_range,1,max_range,1.);
	line->SetLineColor(7);

	float leg_x1 = 0.25;
	float leg_y1 = 0.2;
	float leg_x2 = 0.45;
	float leg_y2 = 0.5;

	for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){

		mul_gr_pt_err[ij][jk] = new TMultiGraph();

		gr_pt_err_exp[ij][jk] = new TGraphAsymmErrors();
		gr_rad_err_exp[ij][jk] = new TGraphAsymmErrors();

		gr_pt_err_th[ij][jk] = new TGraphAsymmErrors();
		gr_rad_err_th[ij][jk] = new TGraphAsymmErrors();

		gr_pt_err_stat[ij][jk] = new TGraphAsymmErrors();
		gr_rad_err_stat[ij][jk] = new TGraphAsymmErrors();

		for(int bn=0; bn<noptbins; bn++){

		gr_pt_err_stat[ij][jk]->SetPoint(bn,ptbins[bn],1.);
		gr_pt_err_stat[ij][jk]->SetPointEYhigh(bn,pt_err_stat_up[ij][jk][bn]);
		gr_pt_err_stat[ij][jk]->SetPointEYlow(bn,pt_err_stat_dn[ij][jk][bn]);

		gr_rad_err_stat[ij][jk]->SetPoint(bn,ptbins[bn],1.);
		gr_rad_err_stat[ij][jk]->SetPointEYhigh(bn,rad_err_stat_up[ij][jk][bn]);
		gr_rad_err_stat[ij][jk]->SetPointEYlow(bn,rad_err_stat_dn[ij][jk][bn]);

		gr_pt_err_exp[ij][jk]->SetPoint(bn,ptbins[bn],1.);
		gr_pt_err_exp[ij][jk]->SetPointEYhigh(bn,pt_err_exp_up[ij][jk][bn]);
		gr_pt_err_exp[ij][jk]->SetPointEYlow(bn,pt_err_exp_dn[ij][jk][bn]);
		
		gr_rad_err_exp[ij][jk]->SetPoint(bn,ptbins[bn],1.);
		gr_rad_err_exp[ij][jk]->SetPointEYhigh(bn,rad_err_exp_up[ij][jk][bn]);
		gr_rad_err_exp[ij][jk]->SetPointEYlow(bn,rad_err_exp_dn[ij][jk][bn]);

		gr_pt_err_th[ij][jk]->SetPoint(bn,ptbins[bn],1.);
		gr_pt_err_th[ij][jk]->SetPointEYhigh(bn,pt_err_th_up[ij][jk][bn]);
		gr_pt_err_th[ij][jk]->SetPointEYlow(bn,pt_err_th_dn[ij][jk][bn]);

		gr_rad_err_th[ij][jk]->SetPoint(bn,ptbins[bn],1.);
		gr_rad_err_th[ij][jk]->SetPointEYhigh(bn,rad_err_th_up[ij][jk][bn]);
		gr_rad_err_th[ij][jk]->SetPointEYlow(bn,rad_err_th_dn[ij][jk][bn]);

		}
	  }
	}

	for(int fg=0; fg<nfiles; fg++){

	sprintf(name,"%s",filenames[fg]);
	filein = new TFile(name,"read");
	filein->cd();

	 for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){
	  
	   if(fg==0){ sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1) ;/*sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[ij],jk+1);*/}
	/*
	   if(((fg>0)&&(fg<4))) {sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
	   if(fg>3) {sprintf(name,"mcjets/Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
	   if(fg==5)  {sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
	   if(fg==(nfiles-1)) {sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
	*/

	   else{
		sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
	   }  

	    hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
	    hist_pt_org[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();

	   if(fg<(nfiles-1)){
	   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
	     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
	     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
	     }
	    }

	     if((fg>3)&&(fg<(nfiles-2))){
		hist_pt[fg][ij][jk]->Scale(1./48191.824);
		}

	    if(fg==(nfiles-2)) {
		hist_pt[fg][ij][jk]->Scale(11502051.6);
	    }

	    hist_pt[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

	    hist_pt[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
	    hist_pt[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
	//    hist_pt[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05); 
	    hist_pt[fg][ij][jk]->GetXaxis()->CenterTitle();    
		

	    hist_pt[fg][ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy (fb GeV^{-1})");
	    hist_pt[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);  
	//    hist_pt[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
	    hist_pt[fg][ij][jk]->GetYaxis()->CenterTitle();
	    
	  }//jk
	 }//ij
	}//fg

	TH1D *NP_factor[nalgo][netarange];

	TFile *file_np = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Pythia/PDF_NNPDF30/NP_Correction_Factor_Pythia.root","read");
	file_np->cd();

	if(nfiles>7){

	for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){

	   sprintf(name,"NP_Correction_%s_EtaBin%i",JetRad[ij],jk+1);
	   NP_factor[ij][jk] = (TH1D*)file_np->Get(name);
	   for(int bn=0; bn<(hist_pt[nfiles-1][ij][jk]->GetNbinsX()); bn++){
		hist_pt[nfiles-1][ij][jk]->SetBinContent(bn+1,hist_pt[nfiles-1][ij][jk]->GetBinContent(bn+1)* NP_factor[ij][jk]->GetBinContent(bn+1));
		}
		hist_pt[nfiles-1][ij][jk]->Scale(1./(ybin[jk+1]-ybin[jk]));//hist_pt[4][ij][jk]->Integral()*1./hist_pt[nfiles-1][ij][jk]->Integral());
	  }
	 }
	}

	for(int fg=0; fg<nfiles; fg++){
	 for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){

	//   if(fg==(nfiles-1)) { cout<<"comp "<<ij+1<<'\t'<<jk+1<<'\t'<<hist_pt[nfiles-1][ij][jk]->Integral()*1./hist_pt[4][ij][jk]->Integral()<<endl; }

	//  hist_pt[fg][ij][jk]->Scale(1./max(1.e-6,hist_pt[fg][ij][jk]->Integral()));

	   hist_radius[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
	   hist_radius[fg][ij][jk]->Divide(hist_pt[fg][ref][jk]) ;

	   hist_radius[fg][ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
	   hist_radius[fg][ij][jk]->GetXaxis()->SetTitleSize(0.06);
	   hist_radius[fg][ij][jk]->GetXaxis()->SetLabelSize(0.055);
	   hist_radius[fg][ij][jk]->GetXaxis()->CenterTitle();

	   hist_radius[fg][ij][jk]->GetYaxis()->SetTitle("Ratio of d^{2}#sigma / dp_{T}dy w.r.t. AK4 Jets");
	   hist_radius[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
	   hist_radius[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
	   hist_radius[fg][ij][jk]->GetYaxis()->CenterTitle();

	   hist_radius[fg][ij][jk]->SetMinimum(0);
	   hist_radius[fg][ij][jk]->SetMaximum(3.);

	  }
	 }
	}

	TCanvas *c2[nalgo][netarange];

	TLegend *leg_pt[nalgo][netarange];
	TLegend *leg_errpt[nalgo][netarange];

	for(int ij=0; ij<nalgo; ij++){
	 for(int jk=0; jk<netarange; jk++){
	// if((ij!=ialgo)||(jk!=ieta)) continue;

	if(ij<2&&jk>5) continue;

	sprintf(name,"Di_Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
	c2[ij][jk] = tdrmyDiCanvas(name,hist_pt[0][ij][jk],hist_pt[1][ij][jk],2.5,6,0);

	leg_pt[ij][jk] = tdrLeg(0.58,0.7,0.9,0.935);
	leg_errpt[ij][jk] = tdrLeg(0.35,0.215,0.55,0.325);
	leg_errpt[ij][jk]->SetTextSize(0.035);
	leg_errpt[ij][jk]->SetTextFont(42);

	//c2[ij][jk]->Draw();
	//c2[ij][jk]->Divide(1,3);
	c2[ij][jk]->cd(1);

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

	 // cout<<0.5*(leg_x1+leg_x2)<<endl;

	  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.05,text);
	  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.125,text1);


	 for(int fg=0; fg<nfiles; fg++){
	  //  hist_pt[fg][ij][jk]->Draw("SAME");

	      hist_pt_rat[fg-1][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
	      hist_pt_rat[fg-1][ij][jk]->Divide(hist_pt[0][ij][jk]);
	      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC / Data");
	      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.1);
	      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetLabelSize(0.075);
	      hist_pt_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.7);

	//      if(fg>1) {continue;}

      tdrDraw(hist_pt[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_pt[ij][jk]->AddEntry(hist_pt[fg][ij][jk],model_name[fg],"l");
    }
  //leg_pt[ij][jk]->Draw();

 leg_pt[ij][jk]->SetTextSize(0.035);
 leg_pt[ij][jk]->SetTextFont(42);

 c2[ij][jk]->cd(2);

 gPad->SetLogx(1);
 gPad->SetLogy(0);


hist_pt_rat[0][ij][jk]->Draw("e");

gr_pt_err_exp[ij][jk]->SetFillColor(kYellow+1);//Alpha(5,0.9);
gr_pt_err_exp[ij][jk]->SetFillStyle(1002);//3005);
gr_pt_err_exp[ij][jk]->SetLineWidth(-2002);
gr_pt_err_exp[ij][jk]->Draw("SAME:E3");

gr_pt_err_stat[ij][jk]->SetFillColor(1);
gr_pt_err_stat[ij][jk]->SetFillStyle(3005);
gr_pt_err_stat[ij][jk]->SetLineWidth(-2002);
gr_pt_err_stat[ij][jk]->Draw("SAME:EZ");


gr_pt_err_th[ij][jk]->SetFillColor(kOrange+10);//Alpha(5,0.9);
gr_pt_err_th[ij][jk]->SetFillStyle(3004);
gr_pt_err_th[ij][jk]->SetLineWidth(-2002);
gr_pt_err_th[ij][jk]->Draw("SAME:E3");


leg_errpt[ij][jk]->AddEntry(gr_pt_err_stat[ij][jk],error_name[0],"lep");
leg_errpt[ij][jk]->AddEntry(gr_pt_err_exp[ij][jk],error_name[1],"f");
leg_errpt[ij][jk]->AddEntry(gr_pt_err_th[ij][jk],error_name[2],"f");

for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
  hist_pt_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
  hist_pt_rat[fg][ij][jk]->SetMinimum(0.3);
  hist_pt_rat[fg][ij][jk]->SetMaximum(2.5);

  hist_pt_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

//   if(fg>0) {continue;}

if(fg==0) {  hist_pt_rat[fg][ij][jk]->Draw("sames"); }
 else { hist_pt_rat[fg][ij][jk]->Draw("sames"); }

 }

/*
gr_pt_err_th[ij][jk]->SetFillColor(kOrange+10);//Alpha(5,0.9);
gr_pt_err_th[ij][jk]->SetFillStyle(3004);
gr_pt_err_th[ij][jk]->SetLineWidth(-2002);
gr_pt_err_th[ij][jk]->Draw("SAME:E3");

gr_pt_err_exp[ij][jk]->SetFillColor(kYellow+1);//Alpha(5,0.9);
gr_pt_err_exp[ij][jk]->SetFillStyle(3002);//3005);
gr_pt_err_exp[ij][jk]->SetLineWidth(-2002);
gr_pt_err_exp[ij][jk]->Draw("SAME:E3");
*/
/*
mul_gr_pt_err[ij][jk]->Add(gr_pt_err_th[ij][jk]);
mul_gr_pt_err[ij][jk]->Add(gr_pt_err_exp[ij][jk]);
mul_gr_pt_err[ij][jk]->Draw("SAME:E3");
*/
line->Draw();

sprintf(name,"PartLevel_Pt_Plots/No_Cor/%s.eps",c2[ij][jk]->GetName());
c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij


TCanvas *c3[nalgo][netarange];

TLegend *leg_radius[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

//  if((ij!=ieta)|(jk!=ialgo)) continue;
   if((ij<2)&&(jk>6)) continue;

  sprintf(name,"Di_Ratio_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
  c3[ij][jk] = tdrDiCanvas(name,hist_radius[0][ij][jk],hist_radius[1][ij][jk],6,0);

  leg_radius[ij][jk] = tdrLeg(0.55,0.65,0.925,0.925);
 
  c3[ij][jk]->cd(1);
  
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
  //  hist_pt[fg][ij][jk]->Draw("SAME");
      if(fg!=0){
      hist_radius_rat[fg-1][ij][jk] = (TH1D*)hist_radius[fg][ij][jk]->Clone();
      hist_radius_rat[fg-1][ij][jk]->Divide(hist_radius[0][ij][jk]);

      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitle("MC / Data");
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleSize(0.075);
      hist_radius_rat[fg-1][ij][jk]->GetYaxis()->SetTitleOffset(0.8);

      hist_radius_rat[fg-1][ij][jk]->SetMinimum(0.3);
      hist_radius_rat[fg-1][ij][jk]->SetMaximum(1.8);

        }

      hist_radius[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);

      tdrDraw(hist_radius[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_radius[ij][jk]->AddEntry(hist_radius[fg][ij][jk],model_name[fg],"l");
    }

   leg_radius[ij][jk]->SetTextSize(0.035);
   leg_radius[ij][jk]->SetTextFont(42);
 // leg_radius[ij][jk]->Draw();

   c3[ij][jk]->cd(2);

   gPad->SetLogx(1);
   gPad->SetLogy(0);

  hist_radius_rat[0][ij][jk]->Draw("e");

  gr_rad_err_stat[ij][jk]->SetFillColor(5);
  gr_rad_err_stat[ij][jk]->SetFillStyle(3010);
  gr_rad_err_stat[ij][jk]->Draw("SAME:E3");


  gr_rad_err_exp[ij][jk]->SetFillColor(5);
  gr_rad_err_exp[ij][jk]->SetFillStyle(3010);
  gr_rad_err_exp[ij][jk]->Draw("SAME:E3");

  gr_rad_err_th[ij][jk]->SetFillColor(kOrange+10);
  gr_rad_err_th[ij][jk]->SetFillStyle(3010);
  gr_rad_err_th[ij][jk]->Draw("SAME:E3");


   for(int fg=0; fg<(nfiles-1); fg++){
//tdrDraw(hist_pt_rat[fg-1][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
   hist_radius_rat[fg][ij][jk]->SetLineColor(col[fg+1]);
   hist_radius_rat[fg][ij][jk]->GetXaxis()->SetRangeUser(min_range,max_range);   

   if(fg==0){
         hist_radius_rat[fg][ij][jk]->Draw("sames");
   }else{
         hist_radius_rat[fg][ij][jk]->Draw("sames");
	}
   }

  line->Draw();

  sprintf(name,"PartLevel_Rat_Plots/No_Cor/%s.eps",c3[ij][jk]->GetName());
  c3[ij][jk]->SaveAs(name);

  }//jk
 }//ij

TCanvas *c4[nalgo][netarange];
TLegend *leg4[nalgo][netarange];
TLegend *leg4_err[nalgo][netarange];

TLatex cms_latex;
TLatex cms_latex1;
TLatex cms_lumi;

cms_latex.SetNDC();
cms_latex.SetTextFont(cmsTextFont);
cms_latex.SetTextAlign(31);
cms_latex.SetTextSize(cmsTextSize);
cms_latex.SetTextAngle(0);

cms_latex1.SetNDC();
cms_latex1.SetTextFont(52);
cms_latex1.SetTextAlign(21);
cms_latex1.SetTextSize(cmsTextSize);
cms_latex1.SetTextAngle(0);

cms_lumi.SetNDC();
cms_lumi.SetTextFont(42);
cms_lumi.SetTextAlign(31);
cms_lumi.SetTextSize(lumiTextSize);
cms_lumi.SetTextAngle(0);

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

 if(ij<2&&jk>5) continue;
  
  sprintf(name,"Canv_Pt_Ratio_%s_EtaBin%i",JetRad[ij],jk+1);
  c4[ij][jk] = tdrCanvas(name,hist_pt_rat[1][ij][jk],6,0);
 
  leg4[ij][jk] = tdrLeg(0.15,0.55,0.45,0.875);
  leg4[ij][jk]->SetTextFont(42);
  leg4[ij][jk]->SetTextSize(0.045); 
 
  leg4_err[ij][jk] = tdrLeg(0.5,0.6,0.7,0.75);
  leg4_err[ij][jk]->SetTextFont(42);
  leg4_err[ij][jk]->SetTextSize(0.035);

  c4[ij][jk]->cd();
  gPad->SetLogx(1);

  hist_pt_rat[0][ij][jk]->Draw("e");
 
  gr_pt_err_exp[ij][jk]->Draw("SAME:E3");

  gr_pt_err_stat[ij][jk]->Draw("SAME:EZ");

  gr_pt_err_th[ij][jk]->Draw("SAME:E3");

  leg4_err[ij][jk]->AddEntry(gr_pt_err_stat[ij][jk],error_name[0],"lep");
  leg4_err[ij][jk]->AddEntry(gr_pt_err_exp[ij][jk],error_name[1],"f");
  leg4_err[ij][jk]->AddEntry(gr_pt_err_th[ij][jk],error_name[2],"f");

  for(int fg=0; fg<(nfiles-1); fg++){

   hist_pt_rat[fg][ij][jk]->SetStats(0);
   hist_pt_rat[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_pt_rat[fg][ij][jk]->GetYaxis()->SetTitleSize(0.06);
   hist_pt_rat[fg][ij][jk]->GetYaxis()->SetTitleOffset(0.9);

//   hist_pt_rat[fg][ij][jk]->Draw("sames"); 
   tdrDraw(hist_pt_rat[fg][ij][jk],mark_sty[fg+1],col[fg+1],kSolid,col[fg+1] ,1001,2);
   leg4[ij][jk]->AddEntry(hist_pt_rat[fg][ij][jk],model_name[fg+1],"lp");
   }

  line->Draw();

  leg4[ij][jk]->Draw();
  leg4_err[ij][jk]->Draw();

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

 // cout<<0.5*(leg_x1+leg_x2)<<endl;

  latex.DrawLatex(0.8,0.845,text);
  latex.DrawLatex(0.8,0.775,text1);

  float l = gPad->GetLeftMargin();
  float t = gPad->GetTopMargin();
  float r = gPad->GetRightMargin();

  cms_latex.DrawLatex(l+0.02,1-t+0.025,cmsText);
  cms_lumi.DrawLatex(1-r,1-t+0.025,lumi_13TeV_BCDEFGH);
  cms_latex1.DrawLatex(l+0.14,1-t+0.025,extraText);

  sprintf(name,"ParLevel_PtRatio_Plots/No_Cor/Bayesian/%s.eps",c4[ij][jk]->GetName());
  c4[ij][jk]->SaveAs(name);

  }
 }

}

int main()
{
Compare_PartLvlErr();
}
