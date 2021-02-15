#include <iostream>
#include <TFile.h>
#include <TH1F.h>

void EnginFile_Converter()
{

static const int nalgo = 12 ;
static const int netarange = 5 ;

//const int noptbins = 61 ;

//double ptbins[noptbins+1] = {/*30, 37, 43, 49, 56, 64, 74,*/ 84,
//     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468,
//     507, 548, 592, 638, 686, 737, 790, 846, 905, 967,
//     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000,
//     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
//     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;

const int noptbins = 50;

double ptbins[noptbins+1] = {/*64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832};

char name[1000];
char title[100];

const char *filenames[1]  = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_TPCor_EraGH.root"};

sprintf(name,"%s","CommonBin_ak4_Suman_JECv17_2016GH_MINIAOD_hist_v18.root"/*,filenames[0]*/);
TFile *fileout = new TFile(name,"recreate");
TH1D *hist_out[netarange];

for(int jk=0; jk<netarange; jk++){
   sprintf(name,"JetpT_ak4_EtaBin%i",jk+1);
   sprintf(title,"JetpT ak4 EtaBin%i",jk+1);
   hist_out[jk] = new TH1D(name,title,noptbins,ptbins);
}

sprintf(name,"%s",filenames[0]);
TFile *filein = new TFile(name,"read");

for(int jk=0; jk<netarange; jk++){
   if(jk>0) continue;
   TH1D *hist_in;

   sprintf(name,"JetpT_ak4_EtaBin%i",jk+1);
//   sprintf(name,"ak4/y_0.0-0.5/hptData_GH2016_detector_%ibin",jk+1);
   cout<<name<<endl;
   hist_in = (TH1D*)filein->Get(name);
   cout<<hist_in->GetName()<<" "<<hist_in->GetMean()<<endl; 
  
    for(int kl=0; kl<noptbins; kl++){
 	hist_out[jk]->SetBinContent(kl+1,hist_in->GetBinContent(kl+1)*1./(ptbins[kl+1]-ptbins[kl]));
	hist_out[jk]->SetBinError(kl+1,hist_in->GetBinError(kl+1)*1./(ptbins[kl+1]-ptbins[kl]));
    }
}

fileout->cd();
fileout->Write();
fileout->Close();

}

int main()
{
EnginFile_Converter();
}
