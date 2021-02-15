#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TAxis.h"
//#include "CLHEP/Vector/LorentzVector.h"
#include "TRandom.h"

#include <string>

#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "stdio.h"

using namespace std;  

const float pival = acos(-1.);

static const int nalgo = 12 ;
const char* JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
static const int netarange = 10 ;
const char* JetEta[netarange] = {"|eta|<0.5","0.5<|eta|<1.0","1.0<|eta|<1.5","1.5<|eta|<2.0","2.0<|eta|<2.5","2.5<|eta|<3.0","3.0<|eta|<3.2","3.2<|eta|<3.7","3.7<|eta|<4.2","4.2<|eta|<4.7"} ;
double etarng[netarange+1] ={0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.2, 3.7, 4.2, 4.7};

const int noptbins = 62 ;
  
double ptbins[noptbins+1] = {/*30, 37, 43, 49, 56, 64,*/ 74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;

const int njetmx = 20;

const int refrad  = 4;
     
int main()
{
char name[100];
TH1D* hist_pt[nalgo][netarange];
TH1D *hist_radius[nalgo][netarange];

TH2D *hist_var[nalgo][netarange][noptbins][noptbins];
TH2D *hist_var2[nalgo][netarange][noptbins][noptbins];

//short nvar[nalgo][netarange][noptbins][noptbins]={{{{0}}}};
//short wsame[nalgo][netarange][noptbins][noptbins]={{{{0}}}};
//short wcross[nalgo][netarange][noptbins][noptbins]={{{{0}}}};
//float corfac[nalgo][netarange][noptbins][noptbins]={{{{0}}}};
//float vcross[nalgo][netarange][noptbins][noptbins]={{{{0}}}};
//float vsame[nalgo][netarange][noptbins][noptbins]={{{{0}}}};
//float umatrix[nalgo][netarange][noptbins][noptbins];

double ****nvar;
double ****wsame;
double ****wcross;
double ****corfac;
double ****vcross;
double ****vsame;

//vsame = (double****) calloc(nalgo * netarange * noptbins * noptbins, sizeof(double***));

nvar = (double****) calloc(nalgo, sizeof(double ***));
wsame = (double****) calloc(nalgo, sizeof(double ***));
wcross = (double****) calloc(nalgo, sizeof(double ***));
corfac = (double****) calloc(nalgo, sizeof(double ***));
vcross = (double****) calloc(nalgo, sizeof(double ***));
vsame = (double****) calloc(nalgo, sizeof(double ***));

for(int ii = 0; ii < nalgo; ii++) { 
	
   nvar[ii] = (double***) calloc(netarange, sizeof(double **));
   wsame[ii] = (double***) calloc(netarange, sizeof(double **));
   wcross[ii] = (double***) calloc(netarange, sizeof(double **));
   corfac[ii] = (double***) calloc(netarange, sizeof(double **));
   vcross[ii] = (double***) calloc(netarange, sizeof(double **));
   vsame[ii] = (double***) calloc(netarange, sizeof(double **));
   
     for(int jj=0; jj<netarange; jj++){
		  
		  nvar[ii][jj] = (double**) calloc(noptbins,sizeof(double *));
		  wsame[ii][jj] = (double**) calloc(noptbins,sizeof(double *));
		  wcross[ii][jj] = (double**) calloc(noptbins,sizeof(double *));
		  corfac[ii][jj] = (double**) calloc(noptbins,sizeof(double *));
		  vcross[ii][jj] = (double**) calloc(noptbins,sizeof(double *));
		  vsame[ii][jj] = (double**) calloc(noptbins,sizeof(double *));
		  
		  for(int kk=0; kk<noptbins; kk++){
			  nvar[ii][jj][kk] = (double*) calloc(noptbins,sizeof(double));
			  wsame[ii][jj][kk] = (double*) calloc(noptbins,sizeof(double));
			  wcross[ii][jj][kk] = (double*) calloc(noptbins,sizeof(double));
			  corfac[ii][jj][kk] = (double*) calloc(noptbins,sizeof(double));
			  vcross[ii][jj][kk] = (double*) calloc(noptbins,sizeof(double));
			  vsame[ii][jj][kk] = (double*) calloc(noptbins,sizeof(double));
			}
		 }
}

cout<<"calloc "<<vcross[4][0][12][12]<<endl;

TFile *fileout = new TFile("Error_Matrix.root","RECREATE");

TH2D *cormat[nalgo][netarange];
TH2D *umatrix[nalgo][netarange];
TH1D *cor_1D[nalgo][netarange];
TH1D *cor_1D_up2[nalgo][netarange];
TH1D *cor_1D_up1[nalgo][netarange];
TH1D *cor_1D_dn2[nalgo][netarange];
TH1D *cor_1D_dn1[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){
		
		sprintf(name,"Correlation_Matrix_%s_EtaBin%i",JetRad[ij],jk+1);
		cormat[ij][jk] = new TH2D(name,name,noptbins,ptbins,noptbins,ptbins);
		cormat[ij][jk]->Sumw2();
		  
		sprintf(name,"U_Matrix_%s_EtaBin%i",JetRad[ij],jk+1);
		umatrix[ij][jk] = new TH2D(name,name,noptbins,ptbins,noptbins,ptbins);
		umatrix[ij][jk]->Sumw2();
		
		sprintf(name,"cor_1D_%s_EtaBin%i",JetRad[ij],jk+1);
		cor_1D[ij][jk] = new TH1D(name,name,noptbins,ptbins);
		cor_1D[ij][jk]->Sumw2();
		
		sprintf(name,"cor_1D_down1_%s_EtaBin%i",JetRad[ij],jk+1);
		cor_1D_dn1[ij][jk] = new TH1D(name,name,noptbins,ptbins);
		cor_1D_dn1[ij][jk]->Sumw2();
		
		sprintf(name,"cor_1D_down2_%s_EtaBin%i",JetRad[ij],jk+1);
		cor_1D_dn2[ij][jk] = new TH1D(name,name,noptbins,ptbins);
		cor_1D_dn2[ij][jk]->Sumw2();
		
		sprintf(name,"cor_1D_up1_%s_EtaBin%i",JetRad[ij],jk+1);
		cor_1D_up1[ij][jk] = new TH1D(name,name,noptbins,ptbins);
		cor_1D_up1[ij][jk]->Sumw2();
		
		sprintf(name,"cor_1D_up2_%s_EtaBin%i",JetRad[ij],jk+1);
		cor_1D_up2[ij][jk] = new TH1D(name,name,noptbins,ptbins);
		cor_1D_up2[ij][jk]->Sumw2();
	  }
  }

TFile *filein = new TFile("Pt_1400.root","read");

for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){
		  
		  if(jk!=0) continue;
		  
		for(int pt=0; pt<noptbins; pt++){
		  for(int pt1=0; pt1<noptbins; pt1++){	
			  
		  sprintf(name,"MVar_%s_EtaBin%i_obsptbin%i_refptbin%i",JetRad[ij],jk+1,pt+1,pt1+1);
		  hist_var[ij][jk][pt][pt1] = (TH2D*)filein->Get(name);
		  
		  hist_var2[ij][jk][pt][pt1] = (TH2D*)hist_var[ij][jk][pt][pt1] ->Clone();
	  
		  for(int refjet=0; refjet<njetmx; refjet++){
		   for(int obsjet=0; obsjet<njetmx; obsjet++){
				  nvar[ij][jk][pt][pt1]+= obsjet*hist_var[ij][jk][pt][pt1]->GetBinContent(obsjet+1,refjet+1);
				  wsame[ij][jk][pt][pt1]+= obsjet*obsjet*hist_var2[ij][jk][pt][pt1]->GetBinContent(obsjet+1,refjet+1);
				  wcross[ij][jk][pt][pt1]+= obsjet*refjet*hist_var2[ij][jk][pt][pt1]->GetBinContent(obsjet+1,refjet+1);
				  }
			  }
			  
		  delete hist_var[ij][jk][pt][pt1];
		  delete hist_var2[ij][jk][pt][pt1];
		  	  
		  cout<<JetRad[ij]<<" eta"<<jk+1<<" pt "<<pt<<" pt1 "<<pt1<<" wcross "<<wcross[ij][jk][pt][pt1]<<" wsame "<<wsame[ij][jk][pt][pt1]<<endl;
	  }
    }
  }
 }
 
 filein->Close();
 
	for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){
		  if(jk!=0) continue;
		for(int pt=0; pt<noptbins; pt++){
		  for(int pt1=0; pt1<noptbins; pt1++){	
		
			corfac[ij][jk][pt][pt1] = wcross[ij][jk][pt][pt1]*1./(max(1.e+0,sqrt(1.*wsame[ij][jk][pt][pt1]*wsame[refrad][jk][pt][pt1])));
			if(abs(corfac[ij][jk][pt][pt1])>1.) { corfac[ij][jk][pt][pt1] = 0;}
			  
			  cormat[ij][jk]->Fill(ptbins[pt],ptbins[pt1],corfac[ij][jk][pt][pt1]);
			  cout<<JetRad[ij]<<" eta"<<jk+1<<" pt "<<pt<<" pt1 "<<pt1<<" correlation "<<corfac[ij][jk][pt][pt1]<<endl;
		
			  if(pt==pt1){
			  cor_1D[ij][jk]->Fill(ptbins[pt],corfac[ij][jk][pt][pt1]);
			  }
			  if(pt==(pt1-1)){
				  cor_1D_dn1[ij][jk]->Fill(ptbins[pt],corfac[ij][jk][pt][pt1]);
				  }
			  if(pt==(pt1-2)){
				  cor_1D_dn2[ij][jk]->Fill(ptbins[pt],corfac[ij][jk][pt][pt1]);
				  }
			  if(pt==(pt1+1)){
				  cor_1D_up1[ij][jk]->Fill(ptbins[pt],corfac[ij][jk][pt][pt1]);
				  }
			  if(pt==(pt1+2)){
				  cor_1D_up2[ij][jk]->Fill(ptbins[pt],corfac[ij][jk][pt][pt1]);
				  }	  	  
		  }
		}
	  }
	}
	
	
	TFile *file_unf = new TFile("Unfolded_2016_Data_MC_P8.root","read");
	
	for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){
		sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1);  
		hist_pt[ij][jk] =  (TH1D*)file_unf->Get(name);
	  }
  }
  
  for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){
		  hist_radius[ij][jk] =  (TH1D*)hist_pt[ij][jk]->Clone();
		  hist_radius[ij][jk]->Divide(hist_pt[refrad][jk]);
	  }
  }
  
 // file_unf->Close();
  
	for(int ij=0; ij<nalgo; ij++){
	  for(int jk=0; jk<netarange; jk++){
		  if(jk!=0) continue;
		for(int pt=0; pt<noptbins; pt++){
		  for(int pt1=0; pt1<noptbins; pt1++){	
		
		   for(int pttag=0; pttag<noptbins; pttag++){
			 for(int pttag1=0; pttag1<noptbins; pttag1++){
				vcross[ij][jk][pt][pt1]  += (hist_pt[ij][jk]->GetBinContent(pt+1)*1./max(1.e+0,nvar[ij][jk][pttag][pttag]*1.))*(hist_pt[refrad][jk]->GetBinContent(pt1+1)*1./max(1.e+0,nvar[ij][jk][pttag1][pttag1]*1.))*wcross[ij][jk][pttag][pttag1] ;
				vsame[ij][jk][pt][pt1]  += (hist_pt[ij][jk]->GetBinContent(pt+1)*1./max(1.e+0,nvar[ij][jk][pttag][pttag]*1.))*(hist_pt[ij][jk]->GetBinContent(pt+1)*1./max(1.e+0,nvar[ij][jk][pttag1][pttag1]*1.))*wsame[ij][jk][pttag][pttag1] ;
			   }
			}
			
			double sum=0;
			
			for(int pttag=0; pttag<2*noptbins; pttag++){
			 for(int pttag1=0; pttag1<2*noptbins; pttag1++){
				 double in1 = 0;
				 double in2 = 0;
			
				 if((abs(pt-pttag)%noptbins)==0) {in1 = pow(-1,(abs(pt-pttag)/noptbins))* hist_radius[ij][jk]->GetBinContent(pt+1)*1./(max(1.e-6,hist_pt[ij][jk]->GetBinContent(pttag+1-(abs(pt-pttag)/noptbins)*noptbins)));}
				 else {in1=0;}
				
				 if((abs(pt1-pttag1)%noptbins)==0) {in2 = pow(-1,(abs(pt1-pttag1)/noptbins))* hist_radius[ij][jk]->GetBinContent(pt1+1)*1./(max(1.e-6,hist_pt[ij][jk]->GetBinContent(pttag1+1-(abs(pt1-pttag1)/noptbins)*noptbins))); }
				 else {in2=0;}
		
				 if(pttag<noptbins&&pttag1<noptbins){sum+=(in1*in2*vsame[ij][jk][pttag][pttag1]);}
				 if(pttag<noptbins&&pttag1>noptbins){sum+=(in1*in2*vcross[ij][jk][pttag][pttag1-noptbins]);}
				 if(pttag>noptbins&&pttag1<noptbins){sum+=(in1*in2*vcross[ij][jk][pttag-noptbins][pttag1]);}
				 if(pttag>noptbins&&pttag1>noptbins){sum+=(in1*in2*vsame[ij][jk][pttag-noptbins][pttag1-noptbins]);}
			 }
			}
			
		//	umatrix[ij][jk][pt][pt1] = sum;
			umatrix[ij][jk]->Fill(ptbins[pt],ptbins[pt1],sum);
			
		  }
		}
	  }
	}
	
	fileout->cd();
	fileout->Write();
	fileout->Close();
}     
