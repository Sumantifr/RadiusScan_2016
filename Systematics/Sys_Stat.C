#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"
#include <fstream>

void Sys_Stat()
{

const int nfiles = 1;

const char *filenames[nfiles] = {"/home/suman/RooUnfold/Unfolded_2016_Data_P8_MC_P8.root"};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const int noptbins = 62;
int ref = 4;

char name[100];

double stat_pt[nalgo][netarange][noptbins];
double stat_rad[nalgo][netarange][noptbins];

ofstream fp_pt;
fp_pt.open("Unf_Pt_P8_Stat.log") ;

ofstream fp_rad;
fp_rad.open("Unf_Rad_P8_Stat.log") ;

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_radius[nfiles][nalgo][netarange];

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   sprintf(name,"svd_unfold_%s_Etabin%i",JetRad[ij],jk+1); 
   hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
     }
   }
 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   hist_radius[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
   hist_radius[fg][ij][jk]->Divide(hist_pt[fg][ref][jk]) ;
   if(fg==0){
   for(int kl=0; kl<noptbins; kl++){
   stat_pt[ij][jk][kl] = hist_pt[fg][ij][jk]->GetBinError(kl+1) / max(1.e-6,hist_pt[fg][ij][jk]->GetBinContent(kl+1)) ;
   stat_rad[ij][jk][kl] = sqrt(pow(stat_pt[ij][jk][kl],2.)+pow(stat_pt[ref][jk][kl],2.)) ;

   fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<stat_pt[ij][jk][kl]<<'\t'<<stat_pt[ij][jk][kl]<<endl;
   fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<kl+1<<'\t'<<stat_rad[ij][jk][kl]<<'\t'<<stat_rad[ij][jk][kl]<<endl;
	}
    }

  }
 }
}

 fp_pt.close();
 fp_rad.close();

}
