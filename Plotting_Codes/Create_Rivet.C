void Create_Rivet()
{

static const int nalgo = 12 ;
static const int netarange = 4 ;
static const int nopbins = 10;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0};
double algo_Rval[nalgo+1] = {0.05,0.15,0.25,0.35,0.45,0.55,0.65,0.75,0.85,0.95,1.05,1.15,1.25};

char name[1000];

TFile *filein;
TH1D* hist_pt[nalgo][netarange];
TH1D* hist_pt_svd[nalgo][netarange];
TH1D* hist_pt_mc[nalgo][netarange];

sprintf(name,"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Pythia_NTuples_LegacyCor_JECv15_new_excor.root");
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

     sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
     hist_pt_mc[ij][jk] = (TH1D*)filein->Get(name);
     
     for(int bn=0; bn<(hist_pt_mc[ij][jk]->GetNbinsX()); bn++){
     	 hist_pt_mc[ij][jk]->SetBinContent(bn+1,hist_pt_mc[ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt_mc[ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
    	 hist_pt_mc[ij][jk]->SetBinError(bn+1,hist_pt_mc[ij][jk]->GetBinError(bn+1)*1.0/(hist_pt_mc[ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
    }
  }
}

sprintf(name,"/home/suman/RooUnfold/Final/Unfolded_2016_Data_NTuple_MC_P8_Legacy_new_excor.root");
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

//     sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
     sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1) ; 
     hist_pt[ij][jk] = (TH1D*)filein->Get(name);
     hist_pt[ij][jk]->Scale(34.67*1./33.9);
     
     sprintf(name,"svd_unfold_%s_Etabin%i",JetRad[ij],jk+1) ; 
     hist_pt_svd[ij][jk] = (TH1D*)filein->Get(name);
     hist_pt_svd[ij][jk]->Scale(34.67*1./33.9);
     
///     hist_pt[ij][jk]->Scale(1./1000);  // from fb to pb conversion

     for(int bn=0; bn<(hist_pt[ij][jk]->GetNbinsX()); bn++){

     	 hist_pt[ij][jk]->SetBinContent(bn+1,hist_pt[ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
    	 hist_pt[ij][jk]->SetBinError(bn+1,hist_pt[ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
		
         hist_pt_svd[ij][jk]->SetBinContent(bn+1,hist_pt_svd[ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt_svd[ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
    	 hist_pt_svd[ij][jk]->SetBinError(bn+1,hist_pt_svd[ij][jk]->GetBinError(bn+1)*1.0/(hist_pt_svd[ij][jk]->GetBinWidth(bn+1)*2*(ybin[jk+1]-ybin[jk])));
		
    }

    hist_pt[ij][jk]->GetXaxis()->SetTitle("Jet p_{T} (in GeV)") ;
    hist_pt[ij][jk]->GetXaxis()->SetTitleSize(0.05);
    hist_pt[ij][jk]->GetXaxis()->CenterTitle();

    hist_pt[ij][jk]->GetYaxis()->SetTitle("d^{2}#sigma / dp_{T}dy(fb GeV^{-1})");
    hist_pt[ij][jk]->GetYaxis()->SetTitleSize(0.05);
    hist_pt[ij][jk]->GetYaxis()->CenterTitle();

  }
}


const int noptbins_1 = 62 ;

double ptbins_1[noptbins_1+1] = {/*30, 37, 43, 49, 56, 64,*/ 74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468,
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967,
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000,
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;
     
     
const int noptbins = 33 ;

double ptbins[noptbins+1] = {/*30, 37, 43, 49, 56, 64, 74,*/ 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468,
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967,
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588} ;

TH1D *hist_pt_data[nalgo][netarange];
TH1D *hist_rat_data[nalgo][netarange];
TH1D *gr_sig_rat_data[netarange][nopbins];

double pbins[nopbins+1]={84, 97, 133, 196, 272, 330, 395, 468, 548, 638, 1588.0};
double xsection[nalgo][netarange][nopbins]={{{0}}};
double xsection_mc[nalgo][netarange][nopbins]={{{0}}};

//TFile *file_out = new TFile("pt_spectra_unfolded_2016.root","RECREATE");
/*
file_out->cd();
TDirectory *dir;
dir = file_out->mkdir("CMS_2020_PAS_SMP_19_003");
dir->cd();
*/
int plotid =  0;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   plotid++;
   
	  if(plotid<10) {sprintf(name,"d0%i-x01-y01",plotid);}
	  else{
	  sprintf(name,"d%i-x01-y01",plotid);
		}
	 
   hist_pt_data[ij][jk] = new TH1D(name,name,noptbins,ptbins);
   hist_pt_data[ij][jk]->Sumw2();
 }
}

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
    for(int pt=0; pt<noptbins; pt++){
     hist_pt_data[ij][jk]->SetBinContent(pt+1,hist_pt_svd[ij][jk]->GetBinContent(pt+2));
     hist_pt_data[ij][jk]->SetBinError(pt+1,hist_pt_svd[ij][jk]->GetBinError(pt+2));
    }
  }
}


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

  hist_rat_data[ij][jk] = (TH1D*)hist_pt_data[ij][jk]->Clone();
  hist_rat_data[ij][jk]->Divide(hist_pt_data[3][jk]);
  plotid++;
   
  if(plotid<10) {sprintf(name,"d0%i-x01-y01",plotid);}
  else{
	  sprintf(name,"d%i-x01-y01",plotid);
  }
	
  hist_rat_data[ij][jk]->SetName(name);
  hist_rat_data[ij][jk]->SetTitle(name);
 }
}

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
    for(int pt=0; pt<noptbins; pt++){
     hist_pt_data[ij][jk]->SetBinContent(pt+1,hist_pt[ij][jk]->GetBinContent(pt+2));
     hist_pt_data[ij][jk]->SetBinError(pt+1,hist_pt[ij][jk]->GetBinError(pt+2));
    }
  }
}


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	  
	TAxis *axis = hist_pt[ij][jk]->GetXaxis();
    int amin =0, amax =0;
	  
	for(int kl=0; kl<nopbins; kl++){
        amin = axis->FindBin(pbins[kl]);
        amax = axis->FindBin(pbins[kl+1]);
        xsection[ij][jk][kl] = hist_pt[ij][jk]->Integral(amin,amax,"width");
        xsection_mc[ij][jk][kl] = hist_pt_mc[ij][jk]->Integral(amin,amax,"width"); //MC
	}
  }
}


xsection[8][2][2] = (xsection_mc[8][2][2]*1./xsection_mc[7][2][2])*xsection[7][2][2];
xsection[8][2][1] = (xsection_mc[8][2][1]*1./xsection_mc[7][2][1])*xsection[7][2][1];
xsection[8][2][0] = (xsection_mc[8][2][0]*1./xsection_mc[7][2][0])*xsection[7][2][0];
xsection[9][3][1] = (xsection_mc[9][3][1]*1./xsection_mc[8][3][1])*xsection[8][3][1];
xsection[7][3][1] = (xsection_mc[7][3][1]*1./xsection_mc[6][3][1])*xsection[6][3][1];
xsection[10][3][0] = (xsection_mc[10][3][0]*1./xsection_mc[9][3][0])*xsection[9][3][0];


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	for(int kl=0; kl<nopbins; kl++){
	
	  if(ij!=3){
	  xsection[ij][jk][kl] *= 1./xsection[3][jk][kl];
	  }
	  if(jk==0){
	//	  cout<<"ak"<<ij+1<<" pt"<<kl+1<<" rat "<<xsection[ij][jk][kl]<<endl;
		  }
	
	}
  }
}

for(int jk=0; jk<netarange; jk++){
	for(int kl=0; kl<nopbins; kl++){
		xsection[3][jk][kl] = 1;
	}
}


for(int jk=0; jk<netarange; jk++){
	for(int kl=0; kl<nopbins; kl++){
		plotid++;
		
		if(plotid<10) {sprintf(name,"d0%i-x01-y01",plotid);}
		else{
			sprintf(name,"d%i-x01-y01",plotid);
		}
		
		gr_sig_rat_data[jk][kl] = new TH1D(name,name,nalgo,algo_Rval);
		for(int ij=0; ij<nalgo; ij++){
			gr_sig_rat_data[jk][kl]->SetBinContent(ij+1,xsection[ij][jk][kl]);
		}
	}
}


for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
    for(int pt=0; pt<noptbins; pt++){
     hist_pt_data[ij][jk]->SetBinContent(pt+1,hist_pt_mc[ij][jk]->GetBinContent(pt+2) * hist_pt_mc[ij][jk]->GetBinWidth(pt+2));  //MC
     hist_pt_data[ij][jk]->SetBinError(pt+1,hist_pt_mc[ij][jk]->GetBinError(pt+2) * hist_pt_mc[ij][jk]->GetBinWidth(pt+2));	//MC
    }
    hist_pt_data[ij][jk]->Scale(1./1000); // fb to pb
  }
}

TFile *file_out = new TFile("pt_spectra_unfolded_2016.root","RECREATE");

file_out->cd();
TDirectory *dir;
dir = file_out->mkdir("CMS_2020_PAS_SMP_19_003");
dir->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
     hist_pt_data[ij][jk]->Write();
  }
}
for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
     hist_rat_data[ij][jk]->Write();
  }
}

for(int jk=0; jk<netarange; jk++){
  for(int kl=0; kl<nopbins; kl++){
		gr_sig_rat_data[jk][kl]->Write();
	}
}



file_out->Write();
file_out->Close();

}
