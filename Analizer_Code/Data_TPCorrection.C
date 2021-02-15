#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>

#define Run2016BCD
//#define Run2016EF
//#define Run2016GH

Double_t Loss_Fraction(Double_t* x, Double_t* par)
{
double pt = x[0];	
double C = par[0];
double mu = par[1];
double S = par[2];
double xx = (pt-mu)*1./(sqrt(pt)*S);
return 0.5*C*(1+TMath::Erf(xx));
}

void TP_Cor()
{

const int nera = 3;
const int neta = 2;

float C_val[neta][nera] = {{0.134,0.248,0.297},{0.432,0.509,0.721}};
float mu_val[neta][nera] = {{174.5,181.5,185.9},{187.7,198.8,164.0}};
float S_val[neta][nera] = {{10.5,12.8,13.8},{7.0,8.3,8.3}};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

TH1D* hist_pt[nalgo][netarange];
TF1 *func[nalgo][netarange];
char name[100];

TFile *file = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/Legacy/JECv18/Legacy2016_07Aug_JECV18_excor_B.root","read");

TFile *fileout;
//sprintf(name,"TPCor_%s",file->GetName());
fileout = new TFile("Legacy2016_07Aug_JECV18_TPCor_excor_B.root","RECREATE");
TH1D* hist_pt_out[nalgo][netarange];

int iera;
#ifdef Run2016BCD
iera = 1;
#elif defined(Run2016EF)
iera=2;
#elif defined(Run2016GH)
iera=3;
#endif
iera -= 1;
int ieta;

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
	sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1) ;
	hist_pt[ij][jk] = (TH1D*)file->Get(name);

	hist_pt_out[ij][jk] = (TH1D*)hist_pt[ij][jk]->Clone();
	
	if(jk!=4&&jk!=5) continue;
	if(jk==4) { ieta = 0; }
	if(jk==5) { ieta = 1; }

	sprintf(name,"Func_%s",hist_pt[ij][jk]->GetName());
	func[ij][jk] = new TF1(name,Loss_Fraction,35,7000,3);
	func[ij][jk]->SetParameter(0,C_val[ieta][iera]);
	func[ij][jk]->SetParameter(1,mu_val[ieta][iera]);
	func[ij][jk]->SetParameter(2,S_val[ieta][iera]);

	for(int bn=0; bn<(hist_pt[ij][jk]->GetNbinsX()); bn++){
	float ptt = hist_pt[ij][jk]->GetBinCenter(bn+1);
	float correction = func[ij][jk]->Eval(ptt);
	cout<<"ak"<<ij+1<<" eta"<<jk+1<<" pt "<<hist_pt[ij][jk]->GetBinCenter(bn+1)<<" fraction "<<correction<<endl;
	correction = 1./(1-correction);
	hist_pt_out[ij][jk]->SetBinContent(bn+1,correction*(hist_pt[ij][jk]->GetBinContent(bn+1)));
	hist_pt_out[ij][jk]->SetBinError(bn+1,sqrt(correction)*hist_pt[ij][jk]->GetBinError(bn+1));
		}
	}
}

fileout->cd();
fileout->Write();
fileout->Close();

}

