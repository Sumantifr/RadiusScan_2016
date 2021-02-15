ntotjobs=$1
Era=$2

temp=Job_submit.sh

echo "#!/bin/sh "  | cat >>$temp

njobs=0
while [ ${njobs} -lt ${ntotjobs} ] 
do
njobs=`expr $njobs + 1`
printf "njobs = $njobs \n"
fil1=Anal_Data_${Era}_${njobs}

echo "#include \"MCJets_NTuple_Reader_Data.h\"				

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
  cout <<\"Give the input file name\"<<endl;
  cin>> rootfiles;
 */
  sprintf(rootfiles,\"2016$Era$njobs.log\");

  int len = strlen(rootfiles);
  strncpy(outfilx, rootfiles, len-4);
  outfilx[len-4]='\0';

  sprintf (outfile,\"%s.root\",outfilx);
  TFile* fileOut = new TFile(outfile, \"recreate\"); 

  char text_file[100];
  sprintf(text_file,\"%s.txt\",outfilx);

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
  TH1F* JetpT_up[nalgo][netarange][nsrc];
  TH1F* JetpT_dn[nalgo][netarange][nsrc];
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

  hist_pfmet = new TH1F(\"MET_Value\",\"MET Value\",1000,0.0,2000.0) ; 
  hist_SumEt = new TH1F(\"Sum_Et\",\"Sum_Et\",3500,0,3500.);
  hist_METbyET = new TH1F(\"METbyEt\",\"MET Value by pT Sum\",100,0.0,1.0) ; 
  hist_PV_all = new TH1F(\"nprimall_rewt_trigset\",\"All PV\",60, -0.5, 59.5);
  hist_PV_sel = new TH1F(\"nprimsel_rewt_trigset\",\"Selected PV\",60, -0.5, 59.5);
  
  for(int ij=0; ij<nHLTmx; ij++){
          compres[ij] = compres$Era[ij];
        }


  for(int ij=0;ij<nalgo;ij++){
    for (int jk=0;jk<netarange;jk++){	
	
      sprintf(name,\"NJets_%s_EtaBin%i\",JetRad[ij],jk+1);
      sprintf(title,\"NJets for %s %s\",JetRad[ij],JetEta[jk]);

      NJets[ij][jk] = new TH1F(name,title,20,0,20);
      NJets[ij][jk]->Sumw2();

      sprintf(name,\"JetpT_%s_EtaBin%i\",JetRad[ij],jk+1);
      sprintf(title,\"JetpT for %s %s\",JetRad[ij],JetEta[jk]);
      
      JetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      JetpT[ij][jk]->Sumw2();
      
      for(int isrc=0; isrc<nsrc; isrc++){
		  
	  sprintf(name,\"JetpT_%s_EtaBin%i_%s_up\",JetRad[ij],jk+1,srcnames[isrc]);
      sprintf(title,\"JetpT for %s %s %s Up\",JetRad[ij],JetEta[jk],srcnames[isrc]);	  
      
      JetpT_up[ij][jk][isrc] = new TH1F(name,title,noptbins,ptbins);
      JetpT_up[ij][jk][isrc]->Sumw2();
      
      sprintf(name,\"JetpT_%s_EtaBin%i_%s_dn\",JetRad[ij],jk+1,srcnames[isrc]);
      sprintf(title,\"JetpT for %s %s %s Down\",JetRad[ij],JetEta[jk],srcnames[isrc]);
      
      JetpT_dn[ij][jk][isrc] = new TH1F(name,title,noptbins,ptbins);
      JetpT_dn[ij][jk][isrc]->Sumw2();
      
	  }
      
      sprintf(name,\"Leading_JetpT_%s_EtaBin%i\",JetRad[ij],jk+1);
      sprintf(title,\"Leading JetpT for %s %s\" ,JetRad[ij],JetEta[jk]);
      
      LeadJetpT[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      LeadJetpT[ij][jk]->Sumw2();
      
      sprintf(name,\"DiJet_Mass_%s_EtaBin%i\",JetRad[ij],jk+1);
      sprintf(title,\"DiJet Mass for %s %s\",JetRad[ij],JetEta[jk]);
    
      DiJet_Mass[ij][jk] = new TH1F(name,title,noptbins,ptbins);
      DiJet_Mass[ij][jk]->Sumw2();

      sprintf(name,\"NGenJets_%s_EtaBin%i\",JetRad[ij],jk+1) ;
      sprintf(title,\"NJets %s EtaBin %i\",JetRad[ij],jk+1) ;
      
      sprintf(name,\"Jet_Width_%s_EtaBin%i\",JetRad[ij],jk+1);
      sprintf(title,\"Jet Width for %s %s\",JetRad[ij],JetEta[jk]);

      JetWidth[ij][jk] = new TH1F(name,title,100,0,2.);
      JetWidth[ij][jk]->Sumw2();

      sprintf(name,\"JetPt_vs_JEC_%s_EtaBin%i\",JetRad[ij],jk+1);
      sprintf(title,\"Pt vs JEC %s EtaBin%i\",JetRad[ij],jk+1);
      JetPt_vs_JEC[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      JetPt_vs_JEC[ij][jk]->Sumw2();

      sprintf(name,\"JetPt_vs_JECL1_%s_EtaBin%i\",JetRad[ij],jk+1);
      sprintf(title,\"Pt vs JEC L1 %s EtaBin%i\",JetRad[ij],jk+1);
      JetPt_vs_JECL1[ij][jk] = new TH2F(name,title,noptbins,ptbins,500,0,5.);
      JetPt_vs_JECL1[ij][jk]->Sumw2();

      sprintf(name,\"Measured_Cov_%s_EtaBin%i\",JetRad[ij],jk+1);
      sprintf(title,\"Measured Cov %s EtaBin%i\",JetRad[ij],jk+1);
      Mes_Cov[ij][jk] = new TH2F(name,title,noptbins,ptbins,noptbins,ptbins);
      Mes_Cov[ij][jk]->Sumw2();

      for(int hl=0 ; hl<nHLTmx; hl++){
      sprintf(name,\"JetpT_%s_EtaBin%i_HLT%i\",JetRad[ij],jk+1,hl+1);
      sprintf(title,\"JetpT for %s %s %s\",JetRad[ij],JetEta[jk],jethlt_name[hl]);
      Prescale_JetpT[ij][jk][hl] = new TH1F(name,title,noptbins,ptbins);
      Prescale_JetpT[ij][jk][hl]->Sumw2();
      }
    }//jk
	
	
    sprintf(name,\"Jety_%s\",JetRad[ij]);
    sprintf(title,\"Jet Rapidity for %s\",JetRad[ij]);
    
    Jeteta[ij] = new TH1F(name,title,200,-5.0,5.0);
    Jeteta[ij]->Sumw2();
    
    sprintf(name,\"Leading_Jety_%s\",JetRad[ij]);
    sprintf(title,\"Leading Jet Rapidity for %s\",JetRad[ij]);
    
    LeadJeteta[ij] = new TH1F(name,title,100,-5.0,5.0);
    LeadJeteta[ij]->Sumw2();
    
    sprintf(name,\"Leading2Jets_deltaR_%s\",JetRad[ij]);
    sprintf(title,\"Leading 2 Jets deltaR for %s\",JetRad[ij]);
    
    Leading2JetsDeltaR[ij] = new TH1F(name,title,100,0,8.0);
    Leading2JetsDeltaR[ij]->Sumw2();
    
    sprintf(name,\"Leading2Jets_deltaPhi_%s\",JetRad[ij]);
    sprintf(title,\"Leading 2 Jets deltaPhi for %s\",JetRad[ij]);
    
    Leading2JetsDeltaPhi[ij] = new TH1F(name,title,75,0,2*M_PI);
    Leading2JetsDeltaPhi[ij]->Sumw2();
	
  }//ij

//PileUpGenerator(datpileup,mcpileup,rat_pileup);

for(int ix=0; ix<nalgo; ix++){

if(ix==0){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
  
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc1[isrc] = unc;
  } // for isrc
}

if(ix==1){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc2[isrc] = unc;
  } // for isrc
}

if(ix==2){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc3[isrc] = unc;
  } // for isrc
}

if(ix==3){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc4[isrc] = unc;
  } // for isrc
}

if(ix==4){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc5[isrc] = unc;
  } // for isrc
}

if(ix==5){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc6[isrc] = unc;
  } // for isrc
}

if(ix==6){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc7[isrc] = unc;
  } // for isrc
}

if(ix==7){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc8[isrc] = unc;
  } // for isrc
}

if(ix==8){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc9[isrc] = unc;
  } // for isrc
}

if(ix==9){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc10[isrc] = unc;
  } // for isrc
}

if(ix==10){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
for (int isrc = 0; isrc < nsrc; isrc++) {
   const char *name11 = srcnames[isrc];
   JetCorrectorParameters *p = new JetCorrectorParameters(name, name11);
   JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
   vsrc11[isrc] = unc;
  } // for isrc
}

if(ix==11){
  sprintf(name,\"/home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/AK8L1Base/Summer16_03Feb2017_V9_DATA_UncertaintySources_AK%iPFchs.txt\",ix+1);
 
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
   cout <<\"datafile name is \"<<datafile<<endl;
   if (strstr(datafile,\"#\")) continue;
    
   if(file_db.eof()) break;
    
   sprintf(infile, \"%s\", datafile);

   TFile* fileIn = TFile::Open(infile);

   if ( fileIn->IsZombie() ) continue;
   if ( fileIn->Recover() == 0 ) continue; 

   TTree* Tin;
   Tin = (TTree*)fileIn->Get(\"T1\");
   
   nevent_total+=Tin->GetEntries(); 
    
   Tin->SetBranchAddress(\"Rho\", &Rho) ;
 
  
   Tin->SetBranchAddress(\"PFMET\",&miset) ;
   Tin->SetBranchAddress(\"PFMETPhi\",&misphi) ;
   Tin->SetBranchAddress(\"sumEt\",&sumEt) ;

   Tin->SetBranchAddress(\"nvert\",&nvert);
   Tin->SetBranchAddress(\"nchict\",&nchict);

   if(!isMC){
   Tin->SetBranchAddress(\"trig_value\",&trig_value);
   }

   if(isMC){
     Tin->SetBranchAddress(\"npu_vert\",&npu_vert);
     Tin->SetBranchAddress(\"pthat\",&pthat);
     Tin->SetBranchAddress(\"event_weight\", &event_weight);
    }

   if(!isMC){
   Tin->SetBranchAddress(\"ihlt01\",&ihlt01);
   Tin->SetBranchAddress(\"ihlt02\",&ihlt02);
   Tin->SetBranchAddress(\"ihlt03\",&ihlt03);
   Tin->SetBranchAddress(\"ihlt04\",&ihlt04);
   Tin->SetBranchAddress(\"ihlt05\",&ihlt05);
   Tin->SetBranchAddress(\"ihlt06\",&ihlt06);
   Tin->SetBranchAddress(\"ihlt07\",&ihlt07);
   Tin->SetBranchAddress(\"ihlt08\",&ihlt08);
   Tin->SetBranchAddress(\"ihlt09\",&ihlt09);
   Tin->SetBranchAddress(\"ihlt10\",&ihlt10);
   }

   Tin->SetBranchAddress(\"npfjets01\",&npfjets01); 
   Tin->SetBranchAddress(\"pfjetpT01\",pfjetpT01);
   Tin->SetBranchAddress(\"pfjetarea01\",pfjetarea01);
   Tin->SetBranchAddress(\"pfjety01\",pfjety01); 
   Tin->SetBranchAddress(\"pfjetphi01\",pfjetphi01) ;
   Tin->SetBranchAddress(\"pfjetenr01\",pfjetenr01) ;
   Tin->SetBranchAddress(\"pfjettightID01\",pfjettightID01);
   Tin->SetBranchAddress(\"pfjetlooseID01\",pfjetlooseID01);
   Tin->SetBranchAddress(\"pfjetJEC01\",pfjetJEC01);
   Tin->SetBranchAddress(\"pfjetJECL101\",pfjetJECL101);
   Tin->SetBranchAddress(\"pfjetJECL201\",pfjetJECL201);
   Tin->SetBranchAddress(\"pfjetJECL2L301\",pfjetJECL2L301);
   Tin->SetBranchAddress(\"pfjetwidth01\",pfjetwidth01);
   Tin->SetBranchAddress(\"trig_weight01\", &trig_weight01);

   Tin->SetBranchAddress(\"npfjets02\", &npfjets02); 
   Tin->SetBranchAddress(\"pfjetpT02\",pfjetpT02);
   Tin->SetBranchAddress(\"pfjetarea02\",pfjetarea02);
   Tin->SetBranchAddress(\"pfjety02\",pfjety02); 
   Tin->SetBranchAddress(\"pfjetphi02\",pfjetphi02) ;
   Tin->SetBranchAddress(\"pfjetenr02\",pfjetenr02) ;
   Tin->SetBranchAddress(\"pfjettightID02\",pfjettightID02);
   Tin->SetBranchAddress(\"pfjetlooseID02\",pfjetlooseID02);
   Tin->SetBranchAddress(\"pfjetJEC02\",pfjetJEC02);
   Tin->SetBranchAddress(\"pfjetJECL102\",pfjetJECL102);
   Tin->SetBranchAddress(\"pfjetJECL202\",pfjetJECL202);
   Tin->SetBranchAddress(\"pfjetJECL2L302\",pfjetJECL2L302);
   Tin->SetBranchAddress(\"pfjetwidth02\",pfjetwidth02);
   Tin->SetBranchAddress(\"trig_weight02\", &trig_weight02);

   Tin->SetBranchAddress(\"npfjets03\", &npfjets03);
   Tin->SetBranchAddress(\"pfjetpT03\",pfjetpT03);
   Tin->SetBranchAddress(\"pfjetarea03\",pfjetarea03);
   Tin->SetBranchAddress(\"pfjety03\",pfjety03);
   Tin->SetBranchAddress(\"pfjetphi03\",pfjetphi03) ;
   Tin->SetBranchAddress(\"pfjetenr03\",pfjetenr03) ;
   Tin->SetBranchAddress(\"pfjettightID03\",pfjettightID03);
   Tin->SetBranchAddress(\"pfjetlooseID03\",pfjetlooseID03);
   Tin->SetBranchAddress(\"pfjetJEC03\",pfjetJEC03);
   Tin->SetBranchAddress(\"pfjetJECL103\",pfjetJECL103);
   Tin->SetBranchAddress(\"pfjetJECL203\",pfjetJECL203);
   Tin->SetBranchAddress(\"pfjetJECL2L303\",pfjetJECL2L303);
   Tin->SetBranchAddress(\"pfjetwidth03\",pfjetwidth03);
   Tin->SetBranchAddress(\"trig_weight03\", &trig_weight03); 

   Tin->SetBranchAddress(\"npfjets04\", &npfjets04);
   Tin->SetBranchAddress(\"pfjetpT04\",pfjetpT04);
   Tin->SetBranchAddress(\"pfjetarea04\",pfjetarea04);
   Tin->SetBranchAddress(\"pfjety04\",pfjety04);
   Tin->SetBranchAddress(\"pfjetphi04\",pfjetphi04) ;
   Tin->SetBranchAddress(\"pfjetenr04\",pfjetenr04) ;
   Tin->SetBranchAddress(\"pfjettightID04\",pfjettightID04);
   Tin->SetBranchAddress(\"pfjetlooseID04\",pfjetlooseID04);
   Tin->SetBranchAddress(\"pfjetJEC04\",pfjetJEC04);
   Tin->SetBranchAddress(\"pfjetJECL104\",pfjetJECL104);
   Tin->SetBranchAddress(\"pfjetJECL204\",pfjetJECL204);
   Tin->SetBranchAddress(\"pfjetJECL2L304\",pfjetJECL2L304);
   Tin->SetBranchAddress(\"pfjetwidth04\",pfjetwidth04);
   Tin->SetBranchAddress(\"trig_weight04\", &trig_weight04);

   Tin->SetBranchAddress(\"npfjets05\", &npfjets05);
   Tin->SetBranchAddress(\"pfjetpT05\",pfjetpT05);
   Tin->SetBranchAddress(\"pfjetarea05\",pfjetarea05);
   Tin->SetBranchAddress(\"pfjety05\",pfjety05);
   Tin->SetBranchAddress(\"pfjetphi05\",pfjetphi05) ;
   Tin->SetBranchAddress(\"pfjetenr05\",pfjetenr05) ;
   Tin->SetBranchAddress(\"pfjettightID05\",pfjettightID05);
   Tin->SetBranchAddress(\"pfjetlooseID05\",pfjetlooseID05);
   Tin->SetBranchAddress(\"pfjetJEC05\",pfjetJEC05);
   Tin->SetBranchAddress(\"pfjetJECL105\",pfjetJECL105);
   Tin->SetBranchAddress(\"pfjetJECL205\",pfjetJECL205);
   Tin->SetBranchAddress(\"pfjetJECL2L306\",pfjetJECL2L305);
   Tin->SetBranchAddress(\"pfjetwidth05\",pfjetwidth05);
   Tin->SetBranchAddress(\"trig_weight05\", &trig_weight05);

   Tin->SetBranchAddress(\"npfjets06\", &npfjets06);
   Tin->SetBranchAddress(\"pfjetpT06\",pfjetpT06);
   Tin->SetBranchAddress(\"pfjetarea06\",pfjetarea06);
   Tin->SetBranchAddress(\"pfjety06\",pfjety06);
   Tin->SetBranchAddress(\"pfjetphi06\",pfjetphi06) ;
   Tin->SetBranchAddress(\"pfjetenr06\",pfjetenr06) ;
   Tin->SetBranchAddress(\"pfjettightID06\",pfjettightID06);
   Tin->SetBranchAddress(\"pfjetlooseID06\",pfjetlooseID06); 
   Tin->SetBranchAddress(\"pfjetJEC06\",pfjetJEC06);
   Tin->SetBranchAddress(\"pfjetJECL106\",pfjetJECL106);
   Tin->SetBranchAddress(\"pfjetJECL206\",pfjetJECL206);
   Tin->SetBranchAddress(\"pfjetJECL2L306\",pfjetJECL2L306);
   Tin->SetBranchAddress(\"pfjetwidth06\",pfjetwidth06);
   Tin->SetBranchAddress(\"trig_weight06\", &trig_weight06);

   Tin->SetBranchAddress(\"npfjets07\", &npfjets07);
   Tin->SetBranchAddress(\"pfjetpT07\",pfjetpT07);
   Tin->SetBranchAddress(\"pfjetarea07\",pfjetarea07);
   Tin->SetBranchAddress(\"pfjety07\",pfjety07);
   Tin->SetBranchAddress(\"pfjetphi07\",pfjetphi07) ; 
   Tin->SetBranchAddress(\"pfjetenr07\",pfjetenr07) ;
   Tin->SetBranchAddress(\"pfjettightID07\",pfjettightID07);
   Tin->SetBranchAddress(\"pfjetlooseID07\",pfjetlooseID07); 
   Tin->SetBranchAddress(\"pfjetJEC07\",pfjetJEC07);
   Tin->SetBranchAddress(\"pfjetJECL107\",pfjetJECL107);
   Tin->SetBranchAddress(\"pfjetJECL207\",pfjetJECL207);
   Tin->SetBranchAddress(\"pfjetJECL2L307\",pfjetJECL2L307);
   Tin->SetBranchAddress(\"pfjetwidth07\",pfjetwidth07);
   Tin->SetBranchAddress(\"trig_weight07\", &trig_weight07);

   Tin->SetBranchAddress(\"npfjets08\", &npfjets08);
   Tin->SetBranchAddress(\"pfjetpT08\",pfjetpT08);
   Tin->SetBranchAddress(\"pfjetarea08\",pfjetarea08);
   Tin->SetBranchAddress(\"pfjety08\",pfjety08);
   Tin->SetBranchAddress(\"pfjetphi08\",pfjetphi08) ;
   Tin->SetBranchAddress(\"pfjetenr08\",pfjetenr08) ;
   Tin->SetBranchAddress(\"pfjettightID08\",pfjettightID08);
   Tin->SetBranchAddress(\"pfjetlooseID08\",pfjetlooseID08); 
   Tin->SetBranchAddress(\"pfjetJEC08\",pfjetJEC08);
   Tin->SetBranchAddress(\"pfjetJECL108\",pfjetJECL108);
   Tin->SetBranchAddress(\"pfjetJECL208\",pfjetJECL208);
   Tin->SetBranchAddress(\"pfjetJECL2L308\",pfjetJECL2L308);
   Tin->SetBranchAddress(\"pfjetwidth08\",pfjetwidth08);
   Tin->SetBranchAddress(\"trig_weight08\", &trig_weight08);

   Tin->SetBranchAddress(\"npfjets09\", &npfjets09);
   Tin->SetBranchAddress(\"pfjetpT09\",pfjetpT09);
   Tin->SetBranchAddress(\"pfjetarea09\",pfjetarea09);
   Tin->SetBranchAddress(\"pfjety09\",pfjety09);
   Tin->SetBranchAddress(\"pfjetphi09\",pfjetphi09) ;
   Tin->SetBranchAddress(\"pfjetenr09\",pfjetenr09) ;
   Tin->SetBranchAddress(\"pfjettightID09\",pfjettightID09);
   Tin->SetBranchAddress(\"pfjetlooseID09\",pfjetlooseID09);
   Tin->SetBranchAddress(\"pfjetJEC09\",pfjetJEC09);
   Tin->SetBranchAddress(\"pfjetJECL109\",pfjetJECL109);
   Tin->SetBranchAddress(\"pfjetJECL209\",pfjetJECL209);
   Tin->SetBranchAddress(\"pfjetJECL2L309\",pfjetJECL2L309);
   Tin->SetBranchAddress(\"pfjetwidth09\",pfjetwidth09);
   Tin->SetBranchAddress(\"trig_weight09\", &trig_weight09); 

   Tin->SetBranchAddress(\"npfjets10\", &npfjets10);
   Tin->SetBranchAddress(\"pfjetpT10\",pfjetpT10);
   Tin->SetBranchAddress(\"pfjetarea10\",pfjetarea10);
   Tin->SetBranchAddress(\"pfjety10\",pfjety10);
   Tin->SetBranchAddress(\"pfjetphi10\",pfjetphi10) ;
   Tin->SetBranchAddress(\"pfjetenr10\",pfjetenr10) ;
   Tin->SetBranchAddress(\"pfjettightID10\",pfjettightID10);
   Tin->SetBranchAddress(\"pfjetlooseID10\",pfjetlooseID10); 
   Tin->SetBranchAddress(\"pfjetJEC10\",pfjetJEC10);
   Tin->SetBranchAddress(\"pfjetJECL110\",pfjetJECL110);
   Tin->SetBranchAddress(\"pfjetJECL210\",pfjetJECL210);
   Tin->SetBranchAddress(\"pfjetJECL2L310\",pfjetJECL2L310);
   Tin->SetBranchAddress(\"pfjetwidth10\",pfjetwidth10);
   Tin->SetBranchAddress(\"trig_weight10\", &trig_weight10);

   Tin->SetBranchAddress(\"npfjets11\", &npfjets11);
   Tin->SetBranchAddress(\"pfjetpT11\",pfjetpT11);
   Tin->SetBranchAddress(\"pfjetarea11\",pfjetarea11);
   Tin->SetBranchAddress(\"pfjety11\",pfjety11);
   Tin->SetBranchAddress(\"pfjetphi11\",pfjetphi11) ; 
   Tin->SetBranchAddress(\"pfjetenr11\",pfjetenr11) ;
   Tin->SetBranchAddress(\"pfjettightID11\",pfjettightID11);
   Tin->SetBranchAddress(\"pfjetlooseID11\",pfjetlooseID11);
   Tin->SetBranchAddress(\"pfjetJEC11\",pfjetJEC11);
   Tin->SetBranchAddress(\"pfjetJECL111\",pfjetJECL111);
   Tin->SetBranchAddress(\"pfjetJECL211\",pfjetJECL211);
   Tin->SetBranchAddress(\"pfjetJECL2L311\",pfjetJECL2L311);
   Tin->SetBranchAddress(\"pfjetwidth11\",pfjetwidth11);
   Tin->SetBranchAddress(\"trig_weight11\", &trig_weight11);  

   Tin->SetBranchAddress(\"npfjets12\", &npfjets12);
   Tin->SetBranchAddress(\"pfjetpT12\",pfjetpT12);
   Tin->SetBranchAddress(\"pfjetarea12\",pfjetarea12);
   Tin->SetBranchAddress(\"pfjety12\",pfjety12);
   Tin->SetBranchAddress(\"pfjetphi12\",pfjetphi12) ; 
   Tin->SetBranchAddress(\"pfjetenr12\",pfjetenr12) ;
   Tin->SetBranchAddress(\"pfjettightID12\",pfjettightID12);
   Tin->SetBranchAddress(\"pfjetlooseID12\",pfjetlooseID12);
   Tin->SetBranchAddress(\"pfjetJEC12\",pfjetJEC12);
   Tin->SetBranchAddress(\"pfjetJECL112\",pfjetJECL112);
   Tin->SetBranchAddress(\"pfjetJECL212\",pfjetJECL212);
   Tin->SetBranchAddress(\"pfjetJECL2L312\",pfjetJECL2L312);
   Tin->SetBranchAddress(\"pfjetwidth12\",pfjetwidth12);
   Tin->SetBranchAddress(\"trig_weight12\", &trig_weight12);

 /* 
   ifstream fp(\"correction_factors_hpp.log\");
   
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
    
   //cout <<\"file \"<<datafile<<\" entries \"<<nentries<< endl;

   for (int ij=0; ij<nentries; ij++) {
       
     fileIn->cd();
      
     Tin->GetEntry(ij);
       
     fillarray();
       
     weight = 0; 
 
     for (int ij=0; ij<nHLTmx; ij++) {
          weighttrg[ij] = 1.0;
           weighttrg[ij] *=compres[ij];
     }

     int ihlttrg[nHLTmx+1]= {0,0,0,0,0,0,0,0,0,0,0};

     if(trig_value>1){
     ihlttrg[nHLTmx] = 1;
     for (int ij=0; ij<nHLTmx; ij++) {
     ihlttrg[ij] = *(dec2bin(trig_value)+ij);
		if(abs(ihlttrg[ij]-ihlt[ij])>0) { cout<<\"alert \"<<endl;}
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
                 JetpT_up[ix][etatag][isrc]->Fill(ptup,weight);
				 JetpT_dn[ix][etatag][isrc]->Fill(ptdn,weight);

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
 
}  " | cat >>${fil1}.C

./Makefile ${fil1}

echo "#!/bin/sh
cd /home/chatterj/t3store/JetsinCMS/Analyzer/Data_2016/LegacyReReco_2016_new/Offline/
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
export SCRAM_ARCH=slc6_amd64_gcc530
export X509_USER_PROXY=/home/chatterj/x509up_u56530
./${fil1}.exe"| cat >>${fil1}.csh

echo "Executable = ${fil1}.csh
Universe=vanilla
Arguments = 4 10
Log = ${fil1}.log
Output = ${fil1}.out
Error = ${fil1}.error
notification=never
should_transfer_files=YES
when_to_transfer_output = ON_EXIT
queue"| cat >>${fil1}.sh

chmod 744 ${fil1}.csh
chmod 744 ${fil1}.sh

echo "condor_submit testmatch ${fil1}.sh "  | cat >>$temp

done

chmod 755 $temp
