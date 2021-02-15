#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include <fstream>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

void Sys_StatUnfold()
{
const int nalgo = 12;
const int Etabins = 10;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[Etabins] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

const int noptbins = 61;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64, 74,*/ 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};
    
double rm_err_pt[nalgo][Etabins][noptbins];
ifstream fp0_pt("RM_Unc_Pt_84.log");

int xx;
for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
   for(int bn=0; bn<noptbins; bn++){
	fp0_pt>>xx>>xx>>xx>>rm_err_pt[ij][jk][bn]>>rm_err_pt[ij][jk][bn];
  }
 }
}

fp0_pt.close();

ofstream fp_pt;
fp_pt.open("StatUnfold_Pt.log");

char name[100];

TH1D *Jet_pt[nalgo][Etabins];
TH2D *cov_pt[nalgo][Etabins];

double stat_err[nalgo][Etabins][noptbins];

TFile *file0 = new TFile("/home/suman/RooUnfold/Unfolded_2016_Data_NTuple_MC_P8_nocor_84.root","read");
file0->cd();

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<Etabins; jk++){
   sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1);
   Jet_pt[ij][jk] = (TH1D*)file0->Get(name);

   sprintf(name,"COV_Bayes_%s_EtaBin%i",JetRad[ij],jk+1);
   cov_pt[ij][jk] = (TH2D*)file0->Get(name);
   for(int bx=0; bx<(cov_pt[ij][jk]->GetNbinsX()); bx++){
    for(int by=0; by<(cov_pt[ij][jk]->GetNbinsY()); by++){
	if(cov_pt[ij][jk]->GetBinContent(bx+1,by+1)  > 0) { cov_pt[ij][jk]->SetBinContent(bx+1,by+1,pow(10,(cov_pt[ij][jk]->GetBinContent(bx+1,by+1)))-1);}
	else {cov_pt[ij][jk]->SetBinContent(bx+1,by+1,-1.*pow(10,-1.*(cov_pt[ij][jk]->GetBinContent(bx+1,by+1))+1));} 
	cov_pt[ij][jk]->SetBinError(bx+1,by+1,0); 
     }
    }

    for(int bn=0; bn<noptbins; bn++){
     if(cov_pt[ij][jk]->GetBinContent(bn+1,bn+1)<0) { cov_pt[ij][jk]->SetBinContent(bn+1,bn+1,0);}
     stat_err[ij][jk][bn]  = sqrt(cov_pt[ij][jk]->GetBinContent(bn+1,bn+1)) * 1./max(1.e-6,Jet_pt[ij][jk]->GetBinContent(bn+1));
     stat_err[ij][jk][bn] = sqrt(stat_err[ij][jk][bn]*stat_err[ij][jk][bn] + rm_err_pt[ij][jk][bn]*rm_err_pt[ij][jk][bn]);
    
     if((stat_err[ij][jk][bn] < 0)||(stat_err[ij][jk][bn] > 1.)){
	stat_err[ij][jk][bn]  = 0;
	}
     fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<stat_err[ij][jk][bn]<<'\t'<<stat_err[ij][jk][bn]<<endl;
    }
  }
 }

 fp_pt.close();

}

int main()
{
Sys_StatUnfold();
}
