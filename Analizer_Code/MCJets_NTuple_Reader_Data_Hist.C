#include "MCJets_NTuple_Reader_Data.h"
				

int main()
{
  // bool isMC;	
  int nevent_total = 0;
   	
  char rootfiles[100];
  
  char outfile[100];
  char outfilx[100];
  char infile[200];
  char datafile[100];
 /* 
  cout <<"Give the input file name"<<endl;
  cin>> rootfiles;
 */
  sprintf(rootfiles,"2016G_OneFile.log");

  int len = strlen(rootfiles);
  strncpy(outfilx, rootfiles, len-4);
  outfilx[len-4]='\0';

  sprintf (outfile,"%s.root",outfilx);
  TFile* fileOut = new TFile(outfile, "recreate"); 

  char text_file[100];
  sprintf(text_file,"%s.txt",outfilx);

  ofstream fp ;
  fp.open(text_file) ;
		
  TH1F* hist_pfmet;
  TH1F* hist_SumEt;
  TH1F* hist_METbyET;

  TH1F* hist_PV_all;
  TH1F* hist_PV_sel;
  TH1F* hist_PU;

  TH2F* PU_vs_PV_all;
  TH2F* PU_vs_PV_sel;
  TH2F* PU_vs_PV_sel_rewt;

  TH1F* NJets[nalgo][netarange];
  TH1F* JetpT[nalgo][netarange];
  TH1F* JetpT_up[nalgo][netarange];
  TH1F* JetpT_dn[nalgo][netarange];
  TH1F* LeadJetpT[nalgo][netarange];
  TH1F* DiJet_Mass[nalgo][netarange];
  TH1F* Jeteta[nalgo];
  TH1F* LeadJeteta[nalgo];
  TH1F* Leading2JetsDeltaR[nalgo];
  TH1F* Leading2JetsDeltaPhi[nalgo] ;
  TH1F* Prescale_JetpT[nalgo][netarange][nHLTmx] ;
  TH1F* Prescale_JetpT_all[nalgo][netarange][nHLTmx] ;  
  TH1F* JetWidth[nalgo][netarange];

  TH1F* LeadJetRatio[nalgo][netarange];									    

  TH1F* NGenJets[nalgo][netarange];
  TH1F* GenJetpT[nalgo][netarange];
  TH1F* GenLeadJetpT[nalgo][netarange];
  TH1F* GenMCJetpT[nalgo][netarange];
  TH1F* GenMCJetpT_pow[nalgo][netarange];
  TH1F* GenMCLeadJetpT[nalgo][netarange];
  TH1F* Gen_DiJet_Mass[nalgo][netarange];
  TH1F* GenJeteta[nalgo];
  TH1F* GenLeadJeteta[nalgo];
  TH1F* GenLeading2JetsDeltaR[nalgo];
  TH1F* GenLeading2JetsDeltaPhi[nalgo] ;
  TH1F* DeltaR_RecoGen[nalgo][netarange][noptbins] ;
  TH1F* DeltaR_RecoGen_mat[nalgo][netarange][noptbins] ;
  TH1F* Resolution[nalgo][netarange][noptbins];
  TH2F* Pt_Ratio[nalgo][netarange];
  TH2F* Pt_Ratio_nomatch[nalgo][netarange];
  TH2F* JetPt_vs_JEC[nalgo][netarange];
  TH2F* JetPt_vs_JECL1[nalgo][netarange];

  const int npu_bin = 3;

  TH2F* RecoVsGenJetpT[nalgo][netarange] ;
  TH2F* RecoVsGenJetNo[nalgo][netarange] ;
  TH2F* JEC_fac[nalgo][netarange] ;
  TH2F* Response_y[nalgo];
  TH2F* Pthat_vs_LeadPt[nalgo];
  TH2F* Mes_Cov[nalgo][netarange];

  TH1F* y_Reso[nalgo];
  TH1F* phi_Reso[nalgo];

  TH1F* PileupVertices[nHLTmx] ;

  char name[100];
  char title[100];

  hist_pfmet = new TH1F("MET_Value","MET Value",1000,0.0,2000.0) ; 
  hist_SumEt = new TH1F("Sum_Et","Sum_Et",3500,0,3500.);
  hist_METbyET = new TH1F("METbyEt","MET Value by pT Sum",100,0.0,1.0) ; 
  hist_PV_all = new TH1F("nprimall_rewt_trigset","All PV",60, -0.5, 59.5);
  hist_PV_sel = new TH1F("nprimsel_rewt_trigset","Selected PV",60, -0.5, 59.5);
  hist_PU     = new TH1F("pu_vertices","# of PU Vertices",80,-0.5,79.5);

  PU_vs_PV_all = new TH2F("pileup_vs_nprimall","PU vs PV all",80,-0.5,79.5,80,-0.5,79.5);
  PU_vs_PV_sel = new TH2F("pileup_vs_nprimsel","PU vs PV sel",80,-0.5,79.5,80,-0.5,79.5);
  PU_vs_PV_sel_rewt = new TH2F("pileup_vs_nprimsel_reweighted","PU vs PV sel Weighted",80,-0.5,79.5,80,-0.5,79.5);



  for(int ij=0;ij<nalgo;ij++){
    for (int jk=0;jk<netarange;jk++){	
	
      sprintf(name,"NJets_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"NJets for %s %s",JetRad[ij],JetEta[jk]);

      NJets[ij][jk] = new TH1F(name,title,20,0,20);
      NJets[ij][jk]->Sumw2();

      sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"JetpT for %s %s",JetRad[ij],JetEta[jk]);
      
      JetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      JetpT[ij][jk]->Sumw2();
      
      sprintf(name,"JetpT_%s_EtaBin%i_JES_up",JetRad[ij],jk+1);
      sprintf(title,"JetpT for %s %s JES Up",JetRad[ij],JetEta[jk]);
      
      JetpT_up[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      JetpT_up[ij][jk]->Sumw2();
      
      sprintf(name,"JetpT_%s_EtaBin%i_JES_dn",JetRad[ij],jk+1);
      sprintf(title,"JetpT for %s %s JES Down",JetRad[ij],JetEta[jk]);
      
      JetpT_dn[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      JetpT_dn[ij][jk]->Sumw2();
      
      sprintf(name,"Leading_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Leading JetpT for %s %s" ,JetRad[ij],JetEta[jk]);
      
      LeadJetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      LeadJetpT[ij][jk]->Sumw2();
      
      sprintf(name,"DiJet_Mass_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"DiJet Mass for %s %s",JetRad[ij],JetEta[jk]);
    
      DiJet_Mass[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      DiJet_Mass[ij][jk]->Sumw2();

      sprintf(name,"NGenJets_%s_EtaBin%i",JetRad[ij],jk+1) ;
      sprintf(title,"NJets %s EtaBin %i",JetRad[ij],jk+1) ;
      
      sprintf(name,"Jet_Width_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Jet Width for %s %s",JetRad[ij],JetEta[jk]);

      JetWidth[ij][jk] = new TH1F(name,title,100,0,2.);
      JetWidth[ij][jk]->Sumw2();

      sprintf(name,"JetPt_vs_JEC_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Pt vs JEC %s EtaBin%i",JetRad[ij],jk+1);
      JetPt_vs_JEC[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      JetPt_vs_JEC[ij][jk]->Sumw2();

      sprintf(name,"JetPt_vs_JECL1_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Pt vs JEC L1 %s EtaBin%i",JetRad[ij],jk+1);
      JetPt_vs_JECL1[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      JetPt_vs_JECL1[ij][jk]->Sumw2();

      sprintf(name,"Measured_Cov_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Measured Cov %s EtaBin%i",JetRad[ij],jk+1);
      Mes_Cov[ij][jk] = new TH2F(name,title,noptbins,ptbins,noptbins,ptbins);
      Mes_Cov[ij][jk]->Sumw2();

      for(int hl=0 ; hl<nHLTmx; hl++){
      sprintf(name,"JetpT_%s_EtaBin%i_HLT%i",JetRad[ij],jk+1,hl+1);
      sprintf(title,"JetpT for %s %s %s",JetRad[ij],JetEta[jk],jethlt_name[hl]);
      Prescale_JetpT[ij][jk][hl] = new TH1F(name,title,noptbins,ptbins);
      Prescale_JetpT[ij][jk][hl]->Sumw2();
      }

     if(isMC){

      NGenJets[ij][jk] = new TH1F(name,title,20,0,20);
      NGenJets[ij][jk]->Sumw2();
      
      sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;
      sprintf(title,"Gen MC Jet pT %s for %s",JetRad[ij],JetEta[jk]) ;
      
      GenMCJetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      GenMCJetpT[ij][jk]->Sumw2();
			
      sprintf(name,"Gen_MC_JetpT_Pow_%s_EtaBin%i",JetRad[ij],jk+1) ;
      sprintf(title,"Gen MC Jet pT Pow %s for %s",JetRad[ij],JetEta[jk]) ;
      
      GenMCJetpT_pow[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      GenMCJetpT_pow[ij][jk]->Sumw2();
      
      sprintf(name,"Leading_Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;
      sprintf(title,"Leading Gen MC Jet pT %s for %s",JetRad[ij],JetEta[jk]) ;
      
      GenMCLeadJetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      GenMCLeadJetpT[ij][jk]->Sumw2();
			
      sprintf(name,"Gen_DiJet_Mass_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Gen_DiJet Mass for %s %s",JetRad[ij],JetEta[jk]);
    
      Gen_DiJet_Mass[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      Gen_DiJet_Mass[ij][jk]->Sumw2();
			
      sprintf(name,"LeadJetRaio_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Leading Jet Pt Ratio for %s EtaBin%i",JetRad[ij],jk+1);

      LeadJetRatio[ij][jk] = new TH1F(name,title,500,-0.01,5.);
      LeadJetRatio[ij][jk]->Sumw2();
	 
      sprintf(name,"RecoJetvsGenJet_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"RecoJetvsGenJet %s EtaBin%i",JetRad[ij],jk+1);
      RecoVsGenJetpT[ij][jk] = new TH2F(name,title,noptbins,ptbins,noptbins,ptbins);
      RecoVsGenJetpT[ij][jk]->Sumw2();
	
      RecoVsGenJetpT[ij][jk]->GetXaxis()->SetTitle("RECO Jet pT (in GeV)");
      RecoVsGenJetpT[ij][jk]->GetYaxis()->SetTitle("Gen Jet pT (in GeV)") ;
	
      sprintf(name,"RecoJetvsGenJet_Number_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"RecoJetvsGenJet Number %s EtaBin%i",JetRad[ij],jk+1);
      RecoVsGenJetNo[ij][jk] = new TH2F(name,title,njetmx,-0.5,19.5,njetmx,-0.5,19.5);
      RecoVsGenJetNo[ij][jk]->Sumw2();
	
      sprintf(name,"Pt_Ratio_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Pt Ratio %s EtaBin%i",JetRad[ij],jk+1);
      Pt_Ratio[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      Pt_Ratio[ij][jk]->Sumw2();
	
      sprintf(name,"Pt_Ratio_nomatch_%s_EtaBin%i",JetRad[ij],jk+1);
      sprintf(title,"Pt Ratio nomatch %s EtaBin%i",JetRad[ij],jk+1);
      Pt_Ratio_nomatch[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      Pt_Ratio_nomatch[ij][jk]->Sumw2();
      
      for(int kl=0; kl<noptbins; kl++){
			
	sprintf(name,"Resolution_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
	sprintf(title,"Resolution %s EtaBin%i PtBin%i",JetRad[ij],jk+1,kl+1);
	Resolution[ij][jk][kl] = new TH1F(name,title,200,-2.0,2.0);
	Resolution[ij][jk][kl]->Sumw2();
	
	sprintf(name,"DeltaR_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
	sprintf(title,"DeltaR %s EtaBin%i PtBin%i",JetRad[ij],jk+1,kl+1);
	DeltaR_RecoGen[ij][jk][kl] = new TH1F(name,title,360,0,3.6);
	DeltaR_RecoGen[ij][jk][kl]->Sumw2();
	
	sprintf(name,"DeltaR_Matrix_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
	sprintf(title,"DeltaR Matrix %s EtaBin%i PtBin%i",JetRad[ij],jk+1,kl+1);
	DeltaR_RecoGen_mat[ij][jk][kl] = new TH1F(name,title,360,0,3.6);
	DeltaR_RecoGen_mat[ij][jk][kl]->Sumw2();
      }//kl
     }//isMC
    }//jk
	
	
    sprintf(name,"Jety_%s",JetRad[ij]);
    sprintf(title,"Jet Rapidity for %s",JetRad[ij]);
    
    Jeteta[ij] = new TH1F(name,title,200,-5.0,5.0);
    Jeteta[ij]->Sumw2();
    
    sprintf(name,"Leading_Jety_%s",JetRad[ij]);
    sprintf(title,"Leading Jet Rapidity for %s",JetRad[ij]);
    
    LeadJeteta[ij] = new TH1F(name,title,100,-5.0,5.0);
    LeadJeteta[ij]->Sumw2();
    
    sprintf(name,"Leading2Jets_deltaR_%s",JetRad[ij]);
    sprintf(title,"Leading 2 Jets deltaR for %s",JetRad[ij]);
    
    Leading2JetsDeltaR[ij] = new TH1F(name,title,100,0,8.0);
    Leading2JetsDeltaR[ij]->Sumw2();
    
    sprintf(name,"Leading2Jets_deltaPhi_%s",JetRad[ij]);
    sprintf(title,"Leading 2 Jets deltaPhi for %s",JetRad[ij]);
    
    Leading2JetsDeltaPhi[ij] = new TH1F(name,title,75,0,2*M_PI);
    Leading2JetsDeltaPhi[ij]->Sumw2();
	
    if(isMC){
      
      sprintf(name,"GenJety_%s",JetRad[ij]);
      sprintf(title,"GenJet Rapidity for %s",JetRad[ij]);
      
      GenJeteta[ij] = new TH1F(name,title,200,-5.0,5.0);
      GenJeteta[ij]->Sumw2();
      
      sprintf(name,"Leading_GenJety_%s",JetRad[ij]);
      sprintf(title,"Leading GenJet Rapidity for %s",JetRad[ij]);
      
      GenLeadJeteta[ij] = new TH1F(name,title,100,-5.0,5.0);
      GenLeadJeteta[ij]->Sumw2();
      
      sprintf(name,"Leading2GenJets_deltaR_%s",JetRad[ij]);
      sprintf(title,"Leading 2 GenJets deltaR for %s",JetRad[ij]);
      
      GenLeading2JetsDeltaR[ij] = new TH1F(name,title,100,0,8.0);
      GenLeading2JetsDeltaR[ij]->Sumw2();
      
      sprintf(name,"Leading2GenJets_deltaPhi_%s",JetRad[ij]);
      sprintf(title,"Leading 2 GenJets deltaPhi for %s",JetRad[ij]);
      
      GenLeading2JetsDeltaPhi[ij] = new TH1F(name,title,75,0,2*M_PI);
      GenLeading2JetsDeltaPhi[ij]->Sumw2();
      
      sprintf(name,"Response_y_%s", JetRad[ij]);
      sprintf(title,"Response Matrix in y for %s Jets",JetRad[ij]);
	  
      Response_y[ij] = new TH2F(name,title,netarange,etarng,netarange,etarng);
      Response_y[ij]->Sumw2();
	  
      sprintf(name,"Resolution_y_%s", JetRad[ij]);
      sprintf(title,"Resolution in y for %s Jets",JetRad[ij]);
	  
      y_Reso[ij] = new TH1F(name,title,100,-10.,10.);
      y_Reso[ij]->Sumw2();
	  
      sprintf(name,"Resolution_phi_%s", JetRad[ij]);
      sprintf(title,"Resolution in phi for %s Jets",JetRad[ij]);
	  
      phi_Reso[ij] = new TH1F(name,title,100,-M_PI,M_PI);
      phi_Reso[ij]->Sumw2();
      
      sprintf(name,"Pthat_vs_LeadingJet_Pt_%s",JetRad[ij]);
      sprintf(title,"Pthat vs LeadingJet Pt %s",JetRad[ij]);
      
      Pthat_vs_LeadPt[ij] = new TH2F(name,title,noptbins,ptbins,noptbins,ptbins);
      Pthat_vs_LeadPt[ij]->Sumw2();
    }
  }//ij

PileUpGenerator(datpileup,mcpileup,rat_pileup);

for(int ix=0; ix<nalgo; ix++){

if(ix==0){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
  
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc1[isrc] = unc;
  } // for isrc
}

if(ix==1){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc2[isrc] = unc;
  } // for isrc
}

if(ix==2){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc3[isrc] = unc;
  } // for isrc
}

if(ix==3){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc4[isrc] = unc;
  } // for isrc
}

if(ix==4){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc5[isrc] = unc;
  } // for isrc
}

if(ix==5){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc6[isrc] = unc;
  } // for isrc
}

if(ix==6){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc7[isrc] = unc;
  } // for isrc
}

if(ix==7){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc8[isrc] = unc;
  } // for isrc
}

if(ix==8){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc9[isrc] = unc;
  } // for isrc
}

if(ix==9){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc10[isrc] = unc;
  } // for isrc
}

if(ix==10){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc11[isrc] = unc;
  } // for isrc
}

if(ix==11){
  sprintf(name,"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc12[isrc] = unc;
  } // for isrc
}

}


ifstream file_db;
file_db.open(rootfiles); 

 while(!(file_db.eof())){
   file_db >> datafile;
   cout <<"datafile name is "<<datafile/*<<" with weight "<<weight<<" "<<weight2*/<<endl;
   if (strstr(datafile,"#")) continue;
    
   if(file_db.eof()) break;
    
   sprintf(infile, "%s", datafile);

//   TFile* fileIn = new TFile(infile, "read");
   TFile* fileIn = TFile::Open(infile);

   if ( fileIn->IsZombie() ) continue;
   if ( fileIn->Recover() == 0 ) continue; 

   TTree* Tin;
   Tin = (TTree*)fileIn->Get("T1");
   
   nevent_total+=Tin->GetEntries(); 
    
   Tin->SetBranchAddress("Rho", &Rho) ;
 
  
   Tin->SetBranchAddress("PFMET",&miset) ;
   Tin->SetBranchAddress("PFMETPhi",&misphi) ;
   Tin->SetBranchAddress("sumEt",&sumEt) ;

   Tin->SetBranchAddress("nvert",&nvert);
   Tin->SetBranchAddress("nchict",&nchict);

   if(!isMC){
   Tin->SetBranchAddress("trig_value",&trig_value);
   }

   if(isMC){
     Tin->SetBranchAddress("npu_vert",&npu_vert);
     Tin->SetBranchAddress("pthat",&pthat);
     Tin->SetBranchAddress("event_weight", &event_weight);
    }

   if(!isMC){
   Tin->SetBranchAddress("ihlt01",&ihlt01);
   Tin->SetBranchAddress("ihlt02",&ihlt02);
   Tin->SetBranchAddress("ihlt03",&ihlt03);
   Tin->SetBranchAddress("ihlt04",&ihlt04);
   Tin->SetBranchAddress("ihlt05",&ihlt05);
   Tin->SetBranchAddress("ihlt06",&ihlt06);
   Tin->SetBranchAddress("ihlt07",&ihlt07);
   Tin->SetBranchAddress("ihlt08",&ihlt08);
   Tin->SetBranchAddress("ihlt09",&ihlt09);
   Tin->SetBranchAddress("ihlt10",&ihlt10);
   }

   Tin->SetBranchAddress("npfjets01",&npfjets01); 
   Tin->SetBranchAddress("pfjetpT01",pfjetpT01);
   Tin->SetBranchAddress("pfjetarea01",pfjetarea01);
   Tin->SetBranchAddress("pfjety01",pfjety01); 
   Tin->SetBranchAddress("pfjetphi01",pfjetphi01) ;
   Tin->SetBranchAddress("pfjetenr01",pfjetenr01) ;
   Tin->SetBranchAddress("pfjettightID01",pfjettightID01);
   Tin->SetBranchAddress("pfjetlooseID01",pfjetlooseID01);
//   Tin->SetBranchAddress("pfjetpTup01",pfjetpTup01);
//   Tin->SetBranchAddress("pfjetpTdn01",pfjetpTdn01);
   Tin->SetBranchAddress("pfjetJEC01",pfjetJEC01);
   Tin->SetBranchAddress("pfjetJECL101",pfjetJECL101);
   Tin->SetBranchAddress("pfjetJECL201",pfjetJECL201);
   Tin->SetBranchAddress("pfjetJECL2L301",pfjetJECL2L301);
   Tin->SetBranchAddress("pfjetwidth01",pfjetwidth01);
   Tin->SetBranchAddress("trig_weight01", &trig_weight01);

   Tin->SetBranchAddress("npfjets02", &npfjets02); 
   Tin->SetBranchAddress("pfjetpT02",pfjetpT02);
   Tin->SetBranchAddress("pfjetarea02",pfjetarea02);
   Tin->SetBranchAddress("pfjety02",pfjety02); 
   Tin->SetBranchAddress("pfjetphi02",pfjetphi02) ;
   Tin->SetBranchAddress("pfjetenr02",pfjetenr02) ;
   Tin->SetBranchAddress("pfjettightID02",pfjettightID02);
   Tin->SetBranchAddress("pfjetlooseID02",pfjetlooseID02);
//   Tin->SetBranchAddress("pfjetpTup02",pfjetpTup02);
//   Tin->SetBranchAddress("pfjetpTdn02",pfjetpTdn02);
   Tin->SetBranchAddress("pfjetJEC02",pfjetJEC02);
   Tin->SetBranchAddress("pfjetJECL102",pfjetJECL102);
   Tin->SetBranchAddress("pfjetJECL202",pfjetJECL202);
   Tin->SetBranchAddress("pfjetJECL2L302",pfjetJECL2L302);
   Tin->SetBranchAddress("pfjetwidth02",pfjetwidth02);
   Tin->SetBranchAddress("trig_weight02", &trig_weight02);

   Tin->SetBranchAddress("npfjets03", &npfjets03);
   Tin->SetBranchAddress("pfjetpT03",pfjetpT03);
   Tin->SetBranchAddress("pfjetarea03",pfjetarea03);
   Tin->SetBranchAddress("pfjety03",pfjety03);
   Tin->SetBranchAddress("pfjetphi03",pfjetphi03) ;
   Tin->SetBranchAddress("pfjetenr03",pfjetenr03) ;
   Tin->SetBranchAddress("pfjettightID03",pfjettightID03);
   Tin->SetBranchAddress("pfjetlooseID03",pfjetlooseID03);
//   Tin->SetBranchAddress("pfjetpTup03",pfjetpTup03);
//   Tin->SetBranchAddress("pfjetpTdn03",pfjetpTdn03);
   Tin->SetBranchAddress("pfjetJEC03",pfjetJEC03);
   Tin->SetBranchAddress("pfjetJECL103",pfjetJECL103);
   Tin->SetBranchAddress("pfjetJECL203",pfjetJECL203);
   Tin->SetBranchAddress("pfjetJECL2L303",pfjetJECL2L303);
   Tin->SetBranchAddress("pfjetwidth03",pfjetwidth03);
   Tin->SetBranchAddress("trig_weight03", &trig_weight03); 

   Tin->SetBranchAddress("npfjets04", &npfjets04);
   Tin->SetBranchAddress("pfjetpT04",pfjetpT04);
   Tin->SetBranchAddress("pfjetarea04",pfjetarea04);
   Tin->SetBranchAddress("pfjety04",pfjety04);
   Tin->SetBranchAddress("pfjetphi04",pfjetphi04) ;
   Tin->SetBranchAddress("pfjetenr04",pfjetenr04) ;
   Tin->SetBranchAddress("pfjettightID04",pfjettightID04);
   Tin->SetBranchAddress("pfjetlooseID04",pfjetlooseID04);
//   Tin->SetBranchAddress("pfjetpTup04",pfjetpTup04);
//   Tin->SetBranchAddress("pfjetpTdn04",pfjetpTdn04);
   Tin->SetBranchAddress("pfjetJEC04",pfjetJEC04);
   Tin->SetBranchAddress("pfjetJECL104",pfjetJECL104);
   Tin->SetBranchAddress("pfjetJECL204",pfjetJECL204);
   Tin->SetBranchAddress("pfjetJECL2L304",pfjetJECL2L304);
   Tin->SetBranchAddress("pfjetwidth04",pfjetwidth04);
   Tin->SetBranchAddress("trig_weight04", &trig_weight04);

   Tin->SetBranchAddress("npfjets05", &npfjets05);
   Tin->SetBranchAddress("pfjetpT05",pfjetpT05);
   Tin->SetBranchAddress("pfjetarea05",pfjetarea05);
   Tin->SetBranchAddress("pfjety05",pfjety05);
   Tin->SetBranchAddress("pfjetphi05",pfjetphi05) ;
   Tin->SetBranchAddress("pfjetenr05",pfjetenr05) ;
   Tin->SetBranchAddress("pfjettightID05",pfjettightID05);
   Tin->SetBranchAddress("pfjetlooseID05",pfjetlooseID05);
//   Tin->SetBranchAddress("pfjetpTup05",pfjetpTup05);
//   Tin->SetBranchAddress("pfjetpTdn05",pfjetpTdn05);
   Tin->SetBranchAddress("pfjetJEC05",pfjetJEC05);
   Tin->SetBranchAddress("pfjetJECL105",pfjetJECL105);
   Tin->SetBranchAddress("pfjetJECL205",pfjetJECL205);
   Tin->SetBranchAddress("pfjetJECL2L306",pfjetJECL2L305);
   Tin->SetBranchAddress("pfjetwidth05",pfjetwidth05);
   Tin->SetBranchAddress("trig_weight05", &trig_weight05);

   Tin->SetBranchAddress("npfjets06", &npfjets06);
   Tin->SetBranchAddress("pfjetpT06",pfjetpT06);
   Tin->SetBranchAddress("pfjetarea06",pfjetarea06);
   Tin->SetBranchAddress("pfjety06",pfjety06);
   Tin->SetBranchAddress("pfjetphi06",pfjetphi06) ;
   Tin->SetBranchAddress("pfjetenr06",pfjetenr06) ;
   Tin->SetBranchAddress("pfjettightID06",pfjettightID06);
   Tin->SetBranchAddress("pfjetlooseID06",pfjetlooseID06); 
//   Tin->SetBranchAddress("pfjetpTup06",pfjetpTup06);
//   Tin->SetBranchAddress("pfjetpTdn06",pfjetpTdn06);
   Tin->SetBranchAddress("pfjetJEC06",pfjetJEC06);
   Tin->SetBranchAddress("pfjetJECL106",pfjetJECL106);
   Tin->SetBranchAddress("pfjetJECL206",pfjetJECL206);
   Tin->SetBranchAddress("pfjetJECL2L306",pfjetJECL2L306);
   Tin->SetBranchAddress("pfjetwidth06",pfjetwidth06);
   Tin->SetBranchAddress("trig_weight06", &trig_weight06);

   Tin->SetBranchAddress("npfjets07", &npfjets07);
   Tin->SetBranchAddress("pfjetpT07",pfjetpT07);
   Tin->SetBranchAddress("pfjetarea07",pfjetarea07);
   Tin->SetBranchAddress("pfjety07",pfjety07);
   Tin->SetBranchAddress("pfjetphi07",pfjetphi07) ; 
   Tin->SetBranchAddress("pfjetenr07",pfjetenr07) ;
   Tin->SetBranchAddress("pfjettightID07",pfjettightID07);
   Tin->SetBranchAddress("pfjetlooseID07",pfjetlooseID07); 
//   Tin->SetBranchAddress("pfjetpTup07",pfjetpTup07);
//   Tin->SetBranchAddress("pfjetpTdn07",pfjetpTdn07);
   Tin->SetBranchAddress("pfjetJEC07",pfjetJEC07);
   Tin->SetBranchAddress("pfjetJECL107",pfjetJECL107);
   Tin->SetBranchAddress("pfjetJECL207",pfjetJECL207);
   Tin->SetBranchAddress("pfjetJECL2L307",pfjetJECL2L307);
   Tin->SetBranchAddress("pfjetwidth07",pfjetwidth07);
   Tin->SetBranchAddress("trig_weight07", &trig_weight07);

   Tin->SetBranchAddress("npfjets08", &npfjets08);
   Tin->SetBranchAddress("pfjetpT08",pfjetpT08);
   Tin->SetBranchAddress("pfjetarea08",pfjetarea08);
   Tin->SetBranchAddress("pfjety08",pfjety08);
   Tin->SetBranchAddress("pfjetphi08",pfjetphi08) ;
   Tin->SetBranchAddress("pfjetenr08",pfjetenr08) ;
   Tin->SetBranchAddress("pfjettightID08",pfjettightID08);
   Tin->SetBranchAddress("pfjetlooseID08",pfjetlooseID08); 
//   Tin->SetBranchAddress("pfjetpTup08",pfjetpTup08);
//   Tin->SetBranchAddress("pfjetpTdn08",pfjetpTdn08);
   Tin->SetBranchAddress("pfjetJEC08",pfjetJEC08);
   Tin->SetBranchAddress("pfjetJECL108",pfjetJECL108);
   Tin->SetBranchAddress("pfjetJECL208",pfjetJECL208);
   Tin->SetBranchAddress("pfjetJECL2L308",pfjetJECL2L308);
   Tin->SetBranchAddress("pfjetwidth08",pfjetwidth08);
   Tin->SetBranchAddress("trig_weight08", &trig_weight08);

   Tin->SetBranchAddress("npfjets09", &npfjets09);
   Tin->SetBranchAddress("pfjetpT09",pfjetpT09);
   Tin->SetBranchAddress("pfjetarea09",pfjetarea09);
   Tin->SetBranchAddress("pfjety09",pfjety09);
   Tin->SetBranchAddress("pfjetphi09",pfjetphi09) ;
   Tin->SetBranchAddress("pfjetenr09",pfjetenr09) ;
   Tin->SetBranchAddress("pfjettightID09",pfjettightID09);
   Tin->SetBranchAddress("pfjetlooseID09",pfjetlooseID09);
//   Tin->SetBranchAddress("pfjetpTup09",pfjetpTup09);
//   Tin->SetBranchAddress("pfjetpTdn09",pfjetpTdn09);
   Tin->SetBranchAddress("pfjetJEC09",pfjetJEC09);
   Tin->SetBranchAddress("pfjetJECL109",pfjetJECL109);
   Tin->SetBranchAddress("pfjetJECL209",pfjetJECL209);
   Tin->SetBranchAddress("pfjetJECL2L309",pfjetJECL2L309);
   Tin->SetBranchAddress("pfjetwidth09",pfjetwidth09);
   Tin->SetBranchAddress("trig_weight09", &trig_weight09); 

   Tin->SetBranchAddress("npfjets10", &npfjets10);
   Tin->SetBranchAddress("pfjetpT10",pfjetpT10);
   Tin->SetBranchAddress("pfjetarea10",pfjetarea10);
   Tin->SetBranchAddress("pfjety10",pfjety10);
   Tin->SetBranchAddress("pfjetphi10",pfjetphi10) ;
   Tin->SetBranchAddress("pfjetenr10",pfjetenr10) ;
   Tin->SetBranchAddress("pfjettightID10",pfjettightID10);
   Tin->SetBranchAddress("pfjetlooseID10",pfjetlooseID10); 
//   Tin->SetBranchAddress("pfjetpTup10",pfjetpTup10);
//   Tin->SetBranchAddress("pfjetpTdn10",pfjetpTdn10);
   Tin->SetBranchAddress("pfjetJEC10",pfjetJEC10);
   Tin->SetBranchAddress("pfjetJECL110",pfjetJECL110);
   Tin->SetBranchAddress("pfjetJECL210",pfjetJECL210);
   Tin->SetBranchAddress("pfjetJECL2L310",pfjetJECL2L310);
   Tin->SetBranchAddress("pfjetwidth10",pfjetwidth10);
   Tin->SetBranchAddress("trig_weight10", &trig_weight10);

   Tin->SetBranchAddress("npfjets11", &npfjets11);
   Tin->SetBranchAddress("pfjetpT11",pfjetpT11);
   Tin->SetBranchAddress("pfjetarea11",pfjetarea11);
   Tin->SetBranchAddress("pfjety11",pfjety11);
   Tin->SetBranchAddress("pfjetphi11",pfjetphi11) ; 
   Tin->SetBranchAddress("pfjetenr11",pfjetenr11) ;
   Tin->SetBranchAddress("pfjettightID11",pfjettightID11);
   Tin->SetBranchAddress("pfjetlooseID11",pfjetlooseID11);
//   Tin->SetBranchAddress("pfjetpTup11",pfjetpTup11);
//   Tin->SetBranchAddress("pfjetpTdn11",pfjetpTdn11);
   Tin->SetBranchAddress("pfjetJEC11",pfjetJEC11);
   Tin->SetBranchAddress("pfjetJECL111",pfjetJECL111);
   Tin->SetBranchAddress("pfjetJECL211",pfjetJECL211);
   Tin->SetBranchAddress("pfjetJECL2L311",pfjetJECL2L311);
   Tin->SetBranchAddress("pfjetwidth11",pfjetwidth11);
   Tin->SetBranchAddress("trig_weight11", &trig_weight11);  

   Tin->SetBranchAddress("npfjets12", &npfjets12);
   Tin->SetBranchAddress("pfjetpT12",pfjetpT12);
   Tin->SetBranchAddress("pfjetarea12",pfjetarea12);
   Tin->SetBranchAddress("pfjety12",pfjety12);
   Tin->SetBranchAddress("pfjetphi12",pfjetphi12) ; 
   Tin->SetBranchAddress("pfjetenr12",pfjetenr12) ;
   Tin->SetBranchAddress("pfjettightID12",pfjettightID12);
   Tin->SetBranchAddress("pfjetlooseID12",pfjetlooseID12);
//   Tin->SetBranchAddress("pfjetpTup12",pfjetpTup12);
//   Tin->SetBranchAddress("pfjetpTdn12",pfjetpTdn12);
   Tin->SetBranchAddress("pfjetJEC12",pfjetJEC12);
   Tin->SetBranchAddress("pfjetJECL112",pfjetJECL112);
   Tin->SetBranchAddress("pfjetJECL212",pfjetJECL212);
   Tin->SetBranchAddress("pfjetJECL2L312",pfjetJECL2L312);
   Tin->SetBranchAddress("pfjetwidth12",pfjetwidth12);
   Tin->SetBranchAddress("trig_weight12", &trig_weight12);

   if(isMC){
 
     Tin->SetBranchAddress("ngenjets01", &ngenjets01);
     Tin->SetBranchAddress("genjetpT01",genjetpT01);
     Tin->SetBranchAddress("genjetarea01",genjetarea01);
     Tin->SetBranchAddress("genjety01",genjety01);
     Tin->SetBranchAddress("genjetphi01",genjetphi01) ;
     Tin->SetBranchAddress("genjetenr01",genjetenr01) ;
     
     Tin->SetBranchAddress("ngenjets02", &ngenjets02);
     Tin->SetBranchAddress("genjetpT02",genjetpT02);
     Tin->SetBranchAddress("genjetarea02",genjetarea02);
     Tin->SetBranchAddress("genjety02",genjety02);
     Tin->SetBranchAddress("genjetphi02",genjetphi02) ;
     Tin->SetBranchAddress("genjetenr02",genjetenr02) ;
     
     Tin->SetBranchAddress("ngenjets03", &ngenjets03);
     Tin->SetBranchAddress("genjetpT03",genjetpT03);
     Tin->SetBranchAddress("genjetarea03",genjetarea03);
     Tin->SetBranchAddress("genjety03",genjety03);
     Tin->SetBranchAddress("genjetphi03",genjetphi03) ;
     Tin->SetBranchAddress("genjetenr03",genjetenr03) ;
     
     Tin->SetBranchAddress("ngenjets04", &ngenjets04);
     Tin->SetBranchAddress("genjetpT04",genjetpT04);
     Tin->SetBranchAddress("genjetarea04",genjetarea04);
     Tin->SetBranchAddress("genjety04",genjety04);
     Tin->SetBranchAddress("genjetphi04",genjetphi04) ;
     Tin->SetBranchAddress("genjetenr04",genjetenr04) ;
     
     Tin->SetBranchAddress("ngenjets05", &ngenjets05);
     Tin->SetBranchAddress("genjetpT05",genjetpT05);
     Tin->SetBranchAddress("genjetarea05",genjetarea05);
     Tin->SetBranchAddress("genjety05",genjety05);
     Tin->SetBranchAddress("genjetphi05",genjetphi05) ;
     Tin->SetBranchAddress("genjetenr05",genjetenr05) ;
     
     Tin->SetBranchAddress("ngenjets06", &ngenjets06);
     Tin->SetBranchAddress("genjetpT06",genjetpT06);
     Tin->SetBranchAddress("genjetarea06",genjetarea06);
     Tin->SetBranchAddress("genjety06",genjety06);
     Tin->SetBranchAddress("genjetphi06",genjetphi06) ;
     Tin->SetBranchAddress("genjetenr06",genjetenr06) ;
     
     Tin->SetBranchAddress("ngenjets07", &ngenjets07);
     Tin->SetBranchAddress("genjetpT07",genjetpT07);
     Tin->SetBranchAddress("genjetarea07",genjetarea07);
     Tin->SetBranchAddress("genjety07",genjety07);
     Tin->SetBranchAddress("genjetphi07",genjetphi07) ;
     Tin->SetBranchAddress("genjetenr07",genjetenr07) ;
     
     Tin->SetBranchAddress("ngenjets08", &ngenjets08);
     Tin->SetBranchAddress("genjetpT08",genjetpT08);
     Tin->SetBranchAddress("genjetarea08",genjetarea08);
     Tin->SetBranchAddress("genjety08",genjety08);
     Tin->SetBranchAddress("genjetphi08",genjetphi08) ;
     Tin->SetBranchAddress("genjetenr08",genjetenr08) ;
     
     Tin->SetBranchAddress("ngenjets09", &ngenjets09);
     Tin->SetBranchAddress("genjetpT09",genjetpT09);
     Tin->SetBranchAddress("genjetarea09",genjetarea09);
     Tin->SetBranchAddress("genjety09",genjety09);
     Tin->SetBranchAddress("genjetphi09",genjetphi09) ;
     Tin->SetBranchAddress("genjetenr09",genjetenr09) ;
     
     Tin->SetBranchAddress("ngenjets10", &ngenjets10);
     Tin->SetBranchAddress("genjetpT10",genjetpT10);
     Tin->SetBranchAddress("genjetarea10",genjetarea10);
     Tin->SetBranchAddress("genjety10",genjety10);
     Tin->SetBranchAddress("genjetphi10",genjetphi10) ;
     Tin->SetBranchAddress("genjetenr10",genjetenr10) ;
    
     Tin->SetBranchAddress("ngenjets11", &ngenjets11);
     Tin->SetBranchAddress("genjetpT11",genjetpT11);
     Tin->SetBranchAddress("genjetarea11",genjetarea11);
     Tin->SetBranchAddress("genjety11",genjety11);
     Tin->SetBranchAddress("genjetphi11",genjetphi11) ;
     Tin->SetBranchAddress("genjetenr11",genjetenr11) ;
     
     Tin->SetBranchAddress("ngenjets12", &ngenjets12);
     Tin->SetBranchAddress("genjetpT12",genjetpT12);
     Tin->SetBranchAddress("genjetarea12",genjetarea12);
     Tin->SetBranchAddress("genjety12",genjety12);
     Tin->SetBranchAddress("genjetphi12",genjetphi12) ;
     Tin->SetBranchAddress("genjetenr12",genjetenr12) ;
     
   } //isMC
 /* 
   ifstream fp("correction_factors_hpp.log");
   
   for(int ij=0; ij<nalgo; ij++){
	   for(int jk=0; jk<netarange; jk++){
		   for(int kl=0; kl<noptbins1; kl++){
			   fp>>ex_cor[ij][jk][kl];
		   }
	   }
   }
  
  fp.close();
  */
   int nentries = Tin->GetEntries();
    
   //cout <<"file "<<datafile<<" entries "<<nentries<< endl;

   for (int ij=0; ij<nentries; ij++) {
       
     fileIn->cd();
      
     Tin->GetEntry(ij);
       
     fillarray();
       
     weight = 0; //event_weight;
//     weight*=rat_pileup[0][npu_vert];
 
     for (int ij=0; ij<nHLTmx; ij++) {
          weighttrg[ij] = 1.0;
           weighttrg[ij] *=compres[ij];
     }

     int ihlttrg[nHLTmx+1]= {0,0,0,0,0,0,0,0,0,0,0};

     if(trig_value>1){
//     ihlttrg[nHLTmx-int(log2(trig_value))] = 1;
     ihlttrg[nHLTmx] = 1;
   //  cout<<"trig_value "<<trig_value<<endl;
     for (int ij=0; ij<nHLTmx; ij++) {
     ihlttrg[ij] = *(dec2bin(trig_value)+ij);
 //    cout<<"trig "<<ij+1<<" value "<<ihlttrg[ij]<<endl;
 //    cout<<"ihlt "<<ij+1<<"org "<<ihlt[ij]<<endl;
		if(abs(ihlttrg[ij]-ihlt[ij])>0) { cout<<"alert "<<endl;}
      }
     }      

   if(ihlttrg[nHLTmx] ==0) continue;

    if(getbinid(pfjetpT[7][0],nHLTmx, leadingPtThreshold)>=0){
    weight = weighttrg[getbinid(pfjetpT[7][0],nHLTmx, leadingPtThreshold)];
    }
    else {continue;}

     hist_pfmet->Fill(miset,weight);
     hist_SumEt->Fill(sumEt,weight);
     hist_METbyET->Fill(miset*1./sumEt,weight);

     if(miset*1./sumEt > 0.3) continue;
            
     hist_PV_all->Fill(nvert,weight);     
     hist_PV_sel->Fill(nchict,weight);   
     hist_PU->Fill(npu_vert,weight); 
       
     PU_vs_PV_all->Fill(npu_vert,nvert);
     PU_vs_PV_sel->Fill(npu_vert,nchict);
     PU_vs_PV_sel_rewt->Fill(npu_vert,nchict,weight);
              
     for(int ix=0; ix<nalgo; ix++){
		
       iRecoPTbin[ix] = -1;
       iGenPTbin[ix] = -1;
		
       int njet_count[netarange] = {0};

	int bincount[netarange][noptbins] = {0};
	int bincount2d[netarange][noptbins][noptbins] = {{0}};
 
       for(int jet=0; jet<njets[ix]; jet++){
			  
	  if(jet==0){
          iRecoPTbin[ix] = getbinid(pfjetpT[ix][jet],nHLTmx, leadingPtThreshold);
          
          if ((iRecoPTbin[ix]<0) || (iRecoPTbin[ix]>=(nHLTmx)) || (ihlttrg[iRecoPTbin[ix]]==0)) break;

		  weight =  weighttrg[iRecoPTbin[ix]]; // trig_weight[ix];
	   }

	 int etatag = getbinid(abs(pfjety[ix][jet]),netarange,etarng);
	 
	 if(etatag>=0) {
	   njet_count[etatag]++;
	   
	   int ptbin_tag = getbinid(pfjetpT[ix][jet],noptbins1,ptbins1);

/*	   if(ptbin_tag>=0){
       if(ex_cor[ix][etatag][ptbin_tag]<1.e-3) { ex_cor[ix][etatag][ptbin_tag] = 1.; }
	   pfjetpT[ix][jet]*=ex_cor[ix][etatag][ptbin_tag];
	   pfjetpTup[ix][jet]*=ex_cor[ix][etatag][ptbin_tag];
	   pfjetpTdn[ix][jet]*=ex_cor[ix][etatag][ptbin_tag];
		}
*/
	   JetpT[ix][etatag]->Fill(pfjetpT[ix][jet],weight);
	   
	   for (int isrc = 0; isrc < nsrc; isrc++) {
				 double ptup, ptdn;
                 JetCorrectionUncertainty *unc;
                 
                 if(ix==0){unc = vsrc1[isrc];}
                 if(ix==1){unc = vsrc2[isrc];}
                 if(ix==2){unc = vsrc3[isrc];}
                 if(ix==3){unc = vsrc4[isrc];}
                 if(ix==4){unc = vsrc5[isrc];}
                 if(ix==5){unc = vsrc6[isrc];}
                 if(ix==6){unc = vsrc7[isrc];}
                 if(ix==7){unc = vsrc8[isrc];}
                 if(ix==8){unc = vsrc9[isrc];}
                 if(ix==9){unc = vsrc10[isrc];}
                 if(ix==10){unc = vsrc11[isrc];}
                 if(ix==11){unc = vsrc12[isrc];}
                 
                 unc->setJetPt(pfjetpT[ix][jet]);
                 unc->setJetEta(pfjety[ix][jet]);
                 double sup = unc->getUncertainty(true); // up variation
                 ptup = (1.+sup)*pfjetpT[ix][jet];
                 unc->setJetPt(pfjetpT[ix][jet]);
                 unc->setJetEta(pfjety[ix][jet]);
                 double sdw = unc->getUncertainty(false); // down variation
                 ptdn = (1.-sdw)*pfjetpT[ix][jet];
                 JetpT_up[ix][etatag]->Fill(ptup,weight);
				 JetpT_dn[ix][etatag]->Fill(ptdn,weight);

           } // for isrc
	   
	
	   JetWidth[ix][etatag]->Fill(pfjetwidth[ix][jet],weight);	

	   if (pfjetpT[ix][jet]>leadingPtThreshold[0]) { Jeteta[ix]->Fill(pfjety[ix][jet],weight); }

       if(jet==0&&isMC) { Pthat_vs_LeadPt[ix]->Fill(pthat,pfjetpT[ix][jet]); }

	   JetPt_vs_JEC[ix][etatag]->Fill(pfjetpT[ix][jet],pfjetJEC[ix][jet],weight);
	   JetPt_vs_JECL1[ix][etatag]->Fill(pfjetpT[ix][jet],pfjetJECL1[ix][jet],weight);
	  
	   int ptbin_tag_cov = getbinid(pfjetpT[ix][jet],noptbins,ptbins);
	   if(ptbin_tag_cov>=0 && etatag>=0) { bincount[etatag][ptbin_tag_cov] += 1; }
 
	   if(jet==0){
	     Prescale_JetpT[ix][etatag][iRecoPTbin[ix]]->Fill(pfjetpT[ix][jet]);
	     LeadJetpT[ix][etatag]->Fill(pfjetpT[ix][jet],weight);
	     if (pfjetpT[ix][jet]>leadingPtThreshold[0]) { LeadJeteta[ix]->Fill(pfjety[ix][jet],weight);}
	   }
	 }
       } //jet
      

       for(int eta=0; eta<netarange; eta++){

	 NJets[ix][eta]->Fill(njet_count[eta],weight) ;
/*
		for(int pti=0; pti<noptbins; pti++){
		   for(int ptj=0; ptj<noptbins; ptj++){
				bincount2d[eta][pti][ptj] = bincount[eta][pti] * bincount[eta][ptj];
				Mes_Cov[ix][eta]->SetBinContent(pti+1,ptj+1,Mes_Cov[ix][eta]->GetBinContent(pti+1,ptj+1) + bincount2d[eta][pti][ptj]);
			}
		}*/
       }

       if(njets[ix]>=2){
	 Leading2JetsDeltaR[ix]->Fill(delta2R(pfjety[ix][0],pfjetphi[ix][0],pfjety[ix][1],pfjetphi[ix][1]),weight);
	 Leading2JetsDeltaPhi[ix]->Fill(PhiInRange(pfjetphi[ix][0]-pfjetphi[ix][1]),weight);

	 if((njets[ix]==2)||((njets[ix]>2)&&(pfjetpT[ix][2]<50.))){
	   double p4[3]={0};
		
	   if(abs(PhiInRange(pfjetphi[ix][0]-pfjetphi[ix][1]))>(2*M_PI/3.)){
	     for(int jt=0; jt<2; jt++){
	       p4[0]+=pfjetenr[ix][jt];
	       p4[1]+=pfjetpT[ix][jt];
	       p4[2]+=pfjetenr[ix][jt]*tanh(pfjety[ix][jt]);
	     }
				    
	     double refy ;
	     if(abs(pfjety[ix][0])>abs(pfjety[ix][1])){ refy = abs(pfjety[ix][0]);}
	     else { refy = abs(pfjety[ix][1]); }
	     int etatag = getbinid(refy,netarange,etarng)  ; 
			
	     if(etatag>=0) {
	       double mass = sqrt(pow(p4[0],2.)-pow(p4[1],2.)-pow(p4[2],2.));
	       DiJet_Mass[ix][etatag]->Fill(mass,weight);	
	     }
	   }//phi condn
	 }//dijet cond
       }//npfjets[ix]>=2	  
			
if(isMC) {
				 
	 int ngenjet_count[netarange] = {0};
				
	 for(int jet=0; jet<ngenjets[ix]; jet++){
	   int etatag = getbinid(abs(genjety[ix][jet]),netarange,etarng);
	   if(etatag>=0){
	     ngenjet_count[etatag]++;
	     GenMCJetpT[ix][etatag]->Fill(genjetpT[ix][jet],weight);
	     GenMCJetpT_pow[ix][etatag]->Fill(genjetpT[ix][jet],genjetpT[ix][jet]*weight);
	     if (genjetpT[ix][jet]>leadingPtThreshold[0]) { GenJeteta[ix]->Fill(genjety[ix][jet],weight); }
	     
	     if(jet==0){
	       //	       iGenPTbin[ix] = getbinid(genjetpT[ix][jet],nHLTmx, leadingPtThreshold);
	       GenMCLeadJetpT[ix][etatag]->Fill(genjetpT[ix][jet],weight);
	       if (genjetpT[ix][jet]>leadingPtThreshold[0]) {GenLeadJeteta[ix]->Fill(genjety[ix][jet],weight);}
	     }
	   }
	 }//jet
				  
	 for(int eta=0; eta<netarange; eta++){
	   NGenJets[ix][eta]->Fill(ngenjet_count[eta],weight);
	 }

	 if(ngenjets[ix]>=2){
	   GenLeading2JetsDeltaR[ix]->Fill(delta2R(genjety[ix][0],genjetphi[ix][0],genjety[ix][1],genjetphi[ix][1]),weight);
	   GenLeading2JetsDeltaPhi[ix]->Fill(PhiInRange(genjetphi[ix][0]-genjetphi[ix][1]),weight);
			
	   if((ngenjets[ix]==2)||((ngenjets[ix]>2)&&(genjetpT[ix][2]<50.))){
			
	     double p4[3]={0};
			
	     if(abs(PhiInRange(genjetphi[ix][0]-genjetphi[ix][1]))>(2*M_PI/3.)) {
	       for(int jt=0; jt<2; jt++){
		 p4[0]+=genjetenr[ix][jt];
		 p4[1]+=genjetpT[ix][jt];
		 p4[2]+=genjetenr[ix][jt]*tanh(genjety[ix][jt]);
	       }
	       double refy ;
	       if(abs(genjety[ix][0])>abs(genjety[ix][1])){ refy = abs(genjety[ix][0]);}
	       else { refy = abs(genjety[ix][1]); }
	       int etatag = getbinid(refy,netarange,etarng)  ; 
			
	       if(etatag>=0){
		 double mass = sqrt(pow(p4[0],2.)-pow(p4[1],2.)-pow(p4[2],2.));
		 Gen_DiJet_Mass[ix][etatag]->Fill(mass,weight);		
	       }
	     }//phi condn
	   }//dijet 
	 }	  
	
			
	 //// ====== Resolution ==============

	 double deltaR_min = 0.05*(ix+1);
 
	 for(int reco = 0; reco<njets[ix]; reco++){
		
	   deltaR_min = 0.05*(ix+1);
		
	   int recoeta_tag = getbinid(abs(pfjety[ix][reco]),netarange,etarng);
	   if ((recoeta_tag<0)||(recoeta_tag>=netarange)) continue;
	    
	   int recopttag = getbinid(pfjetpT[ix][reco],noptbins,ptbins);
	   //	if(recopttag<0) continue ;
		
	   int match_gen = -1;
	   bool ismatched = false;
		
	   for(int gen = 0; gen<ngenjets[ix]; gen++){
			
	     int geneta_tag = -1;
	     geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
	     int genpt_tag = -1;
	     genpt_tag = getbinid(genjetpT[ix][gen],noptbins,ptbins);

	     if((recoeta_tag==geneta_tag)&&(recopttag==genpt_tag)&&geneta_tag>=0){ Pt_Ratio_nomatch[ix][geneta_tag]->Fill(genjetpT[ix][gen],pfjetpT[ix][reco]*1./genjetpT[ix][gen],weight);}
			
	     //	if(geneta_tag<0||genpt_tag<0) continue;
			
	     double delR_rg = delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen],genjetphi[ix][gen]);
			
	     if((genjetpT[ix][gen]>0.5*(pfjetpT[ix][reco]))&&(genjetpT[ix][gen]<2.*(pfjetpT[ix][reco]))){
	       if((geneta_tag>=0)&&(genpt_tag>=0)){
		 DeltaR_RecoGen[ix][geneta_tag][genpt_tag]->Fill(delR_rg) ;
	       }
	     }
			
	     double pt_rat = pfjetpT[ix][reco]*1./genjetpT[ix][gen] ;
			
	     if((delR_rg < deltaR_min)&&((pt_rat>0.25)&&(pt_rat<4.))) { 
	       deltaR_min = delR_rg ; 
	       match_gen = gen;
	       ismatched = true;
	     }
	   }//gen
			
			   
	   if(match_gen>=0){
				
	     int gen = match_gen;
					
	     int geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
	     int genpt_tag =  getbinid(genjetpT[ix][gen],noptbins,ptbins);	
				
	     int recomin = -1;
	     deltaR_min = 0.05*(ix+1);
				
	     for(int reco2=0; reco2<njets[ix]; reco2++){
	       double delR_rg = delta2R(pfjety[ix][reco2],pfjetphi[ix][reco2],genjety[ix][gen],genjetphi[ix][gen]) ;
	       if(delR_rg < deltaR_min){
		 deltaR_min = delta2R(pfjety[ix][reco2],pfjetphi[ix][reco2],genjety[ix][gen],genjetphi[ix][gen]);
		 recomin = reco2;
	       }
	     }//reco2
					
	     if(recomin==reco) {
				
	       if((geneta_tag>=0)&&(genpt_tag>=0)) {
						
		 double res_pt = 0;
		 res_pt = (pfjetpT[ix][reco] - genjetpT[ix][gen])*1.0/genjetpT[ix][gen]; // (RecopT[ix] - GenpT[ix])*1.0/(GenpT[ix]) ;
		 int nbins = Resolution[ix][geneta_tag][genpt_tag]->GetNbinsX();
		 if(res_pt<(Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(1))) {
		   res_pt = (Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(1))+0.0001;
		 }else {
		   if(res_pt>(Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(nbins+1))) {
		     res_pt = Resolution[ix][geneta_tag][genpt_tag]->GetBinLowEdge(nbins+1) -0.0001;
		   }
		 }
				
		 Resolution[ix][geneta_tag][genpt_tag]->Fill(res_pt) ;
	       } //if((geneta_tag>=0)&&(genpt_tag>=0))
			
	       if(geneta_tag==recoeta_tag){
		 RecoVsGenJetpT[ix][geneta_tag]->Fill(pfjetpT[ix][reco],genjetpT[ix][gen],weight);
		 Pt_Ratio[ix][geneta_tag]->Fill(genjetpT[ix][gen],pfjetpT[ix][reco]*1./genjetpT[ix][gen],weight);
	       } else {
		 if(recoeta_tag>=0){
		   RecoVsGenJetpT[ix][recoeta_tag]->Fill(pfjetpT[ix][reco],-1,weight);
		 }
		 if(geneta_tag>=0){
		   RecoVsGenJetpT[ix][geneta_tag]->Fill(-1,genjetpT[ix][gen],weight);
		 }	
	       }
	     } else { //if(recomin==reco) 
	       RecoVsGenJetpT[ix][recoeta_tag]->Fill(pfjetpT[ix][reco],-1,weight);
	     }
	   }//if(match_gen>=0)
	   else{
	     if(!ismatched){
	       if(recoeta_tag>=0){
		 RecoVsGenJetpT[ix][recoeta_tag]->Fill(pfjetpT[ix][reco],-1,weight);
	       }
	     }
	   }
	 }//reco
	
	 
	 for(int gen = 0; gen<ngenjets[ix]; gen++){
		  
	   int geneta_tag = getbinid(abs(genjety[ix][gen]),netarange,etarng);
	   int genpt_tag = getbinid(genjetpT[ix][gen],noptbins,ptbins);
	   
	   //	   if(geneta_tag<0||genpt_tag<0) continue ; 
	   
	   deltaR_min = 0.05*(ix+1);
	   
	   bool ismatched =false;
	   for(int reco = 0; reco<njets[ix]; reco++) { 
	     int receta_tag = getbinid(abs(pfjety[ix][reco]),netarange,etarng);
	     int recpt_tag = getbinid(abs(pfjetpT[ix][reco]),noptbins,ptbins);
	  
	     double delR_rg = delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen],genjetphi[ix][gen]);
	     double pt_rat = pfjetpT[ix][reco]*1./genjetpT[ix][gen];
			
	     if((delR_rg < deltaR_min)&&(pt_rat>0.25)&&(pt_rat<4.0)) { 
	      
	       int match_gen = -1;
	       
	       for(int gen2=0; gen2<ngenjets[ix] ; gen2++){
			   if(delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen2],genjetphi[ix][gen2])<deltaR_min){
				   deltaR_min = delta2R(pfjety[ix][reco],pfjetphi[ix][reco],genjety[ix][gen2],genjetphi[ix][gen2]);
				   match_gen = gen2;
				   }
			   }
			   
			   if(gen==match_gen) {
				   ismatched =true; 
				   break;
				   }
	     }	
	   }//reco
	    
	   if (!ismatched) { 
	     if(geneta_tag>=0) {
	       RecoVsGenJetpT[ix][geneta_tag]->Fill(-1, genjetpT[ix][gen],weight) ;
	     }
	   }
	 }//gen
				 
	 //// ====== Resolution End ==========	
			
	 ////======Response Matrix for y ==============
			
	 double y_matrix[njetmx][njetmx] = {{0.}};
			
	 for(int reco = 0; reco<njets[ix]; reco++) { 
	   for(int gen=0; gen<ngenjets[ix]; gen++){
	     y_matrix[reco][gen] =  abs(pfjety[ix][reco]-genjety[ix][gen]) ;
	   }
	 }
			
	 for(int gen=0; gen<ngenjets[ix]; gen++){
	   double miny = 100;
	   int recmin_indx = -1;
	   for(int reco = 0; reco<njets[ix]; reco++){
	     if(y_matrix[reco][gen]<miny){
	       miny = y_matrix[reco][gen];
	       recmin_indx = reco;
	     }
	   }
					
	   if(recmin_indx>=0){
						
	     miny = 100;
	     int genmin_index = -1;
						
	     for(int gen2=0; gen2<ngenjets[ix]; gen2++){
	       if(y_matrix[recmin_indx][gen2]<miny){
		 miny = y_matrix[recmin_indx][gen2];
		 genmin_index = gen2;
	       }
	     }//gen2
							
	     if(genmin_index==gen) {
							
	       double pt_rat = pfjetpT[ix][recmin_indx]*1./genjetpT[ix][gen] ;
							
	       if(((pt_rat>0.5)&&(pt_rat<2.))&&(abs(PhiInRange(pfjetphi[ix][recmin_indx]-genjetphi[ix][gen]))<0.075*(ix+1))){
		 Response_y[ix]->Fill(abs(pfjety[ix][recmin_indx]),abs(genjety[ix][gen]),weight) ;
		 y_Reso[ix]->Fill(pfjety[ix][recmin_indx]-genjety[ix][gen]) ;
	       }
	     }
	     else {continue;}
	   }
	   else {continue;}
	 }//gen
					
	 //============= Response Matrix for y Ends =======================		

	 //======= Resolution in Phi Starts ====================

	 for(int reco = 0; reco<njets[ix]; reco++){
	   for(int gen=0; gen<ngenjets[ix]; gen++){
		
	     double minphi = 100;
	     double pseudo_pfphi = 100;
	     double pseudo_genphi = 100;
	     double pt_rat = pfjetpT[ix][reco]*1./genjetpT[ix][gen];
	     double del_y = abs(pfjety[ix][reco]-genjety[ix][gen]) ;
	     bool isMatched = false;
		
	     if(((pt_rat>0.5)&&(pt_rat<2.))&&(del_y<0.05*(ix+1))){
			
	       isMatched = true;
			
	       if(abs(PhiInRange(pfjetphi[ix][reco]-genjetphi[ix][gen])) < minphi){
		 pseudo_pfphi = pfjetphi[ix][reco];
		 pseudo_genphi = genjetphi[ix][gen];
		 minphi = abs(PhiInRange(pfjetphi[ix][reco]-genjetphi[ix][gen]));
	       }
	     }
			
	     if(isMatched){
	       phi_Reso[ix]->Fill(PhiInRange(pseudo_pfphi-pseudo_genphi));
	     }
	   }//gen
	 }//reco

	 //======= Resolution in Phi Ends ====================
				
	 for(int jk=0; jk<netarange; jk++){
	   RecoVsGenJetNo[ix][jk]->Fill(njet_count[jk],ngenjet_count[jk], weight) ;
	 }//jk
					
       } //isMC
     }//ix 
       
   }//ij

    fileIn->cd();
    delete Tin;
    delete fileIn;
 
 }
 
 file_db.close();
 
  fileOut->cd();
  fileOut->Write();
  fileOut->Close();
 
  fp<<"Total Number of events in "<<fileOut->GetName()<<" is "<<nevent_total<<endl;
  fp<<"Total Weight is "<<tot_weight<<endl;
}
