#include <iostream>
#include <TFile.h>
#include <TH1F.h>

void Bin_Converter()
{

static const int nalgo = 12 ;
static const int netarange = 10 ;

//const int noptbins = 61 ;

//double ptbins[noptbins+1] = {/*30, 37, 43, 49, 56, 64, 74,*/ 84,
//     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468,
//     507, 548, 592, 638, 686, 737, 790, 846, 905, 967,
//     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000,
//     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
//     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;

const int noptbins = 51;

double ptbins[noptbins+1] = {64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832};

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[1000];
char title[100];
//const char *filenames[1]  = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/CT14nlo_files.root"};
//const char *filenames[1]  = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Powheg/Powheg_Herwig/PH_Hwg_CUETHppS1_updated.root"};
const char *filenames[1]  = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/Herwig7/hist_Herwig7_weighted.root"};

sprintf(name,"%s","Bin84_hist_Herwig7_weighted.root"/*,filenames[0]*/);
TFile *fileout = new TFile(name,"recreate");
TH1D *hist_out[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){
   sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
   sprintf(title,"Gen MC JetpT_%s EtaBin%i",JetRad[ij],jk+1);
   hist_out[ij][jk] = new TH1D(name,title,noptbins,ptbins);
   }
 }

sprintf(name,"%s",filenames[0]);
TFile *filein = new TFile(name,"read");

//TH1D *hist_in[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

   TH1D *hist_in;

   sprintf(name,"Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_in/*[ij][jk]*/ = (TH1D*)filein->Get(name);
/*
   sprintf(name,"%s",hist_in->GetName());
   sprintf(title,"%s",hist_in->GetTitle());
   hist_out[ij][jk] = new TH1D(name,title,noptbins,ptbins);
*/
   for(int kl=0; kl<noptbins; kl++){
 	hist_out[ij][jk]->SetBinContent(kl+1,hist_in->GetBinContent(kl+2));
	hist_out[ij][jk]->SetBinError(kl+1,hist_in->GetBinError(kl+2));
    }

 }
}

fileout->cd();
fileout->Write();
fileout->Close();

}

int main()
{
Bin_Converter();
}
