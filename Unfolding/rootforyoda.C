#include "TFile.h"
#include "TH1D.h"

const int noptbins = 62 ;

double ptbins[noptbins+1] = {/*30, 37, 43, 49, 56, 64,*/ 74, 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468,
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967,
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000,
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};


void rootforyoda()
{

char name[100];

TFile *file_out = new TFile("pt_spectra_2016.root","RECREATE");
TH1D *hist_pt_data[nalgo][netarange];

int plotid =  0;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   plotid++;
   if(plotid<10) {sprintf(name,"d0%i-x01-y01",plotid);}
   else { sprintf(name,"d%i-x01-y01",plotid);}
   hist_pt_data[ij][jk] = new TH1D(name,name,noptbins,ptbins);
   hist_pt_data[ij][jk]->Sumw2();
 }
}


TFile *filein = new TFile("Unfolded_2016_Data_P8.root","read");
TH1D *hist_pt[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
  sprintf(name,"bayes_unfold_%s_Etabin%i",JetRad[ij],jk+1);
  hist_pt[ij][jk] = (TH1D*)filein->Get(name);
 
  for(int pt=0; pt<noptbins; pt++){
   hist_pt_data[ij][jk]->SetBinContent(pt+1,hist_pt[ij][jk]->GetBinContent(pt+1));
   hist_pt_data[ij][jk]->SetBinError(pt+1,hist_pt[ij][jk]->GetBinError(pt+1)); 
  }
 }
}

file_out->cd();
file_out->Write();
file_out->Close();

}

int main()
{
rootforyoda();
}
