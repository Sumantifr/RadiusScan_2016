//winclude "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/tdrstyle_mod14.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"
#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/Comparison_plot/Delta_Calculator.C"

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TMath.h"

const int noptbins = 61 ;
  
double ptbins[noptbins+1] = {/*30, 37, 43, 49, 56, 64, 74,*/ 84,
     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 
     507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 
     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 
     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;


Double_t gausX(Double_t* x, Double_t* par){
  return par[0]*(TMath::Gaus(x[0], par[1], par[2], kTRUE));
}

void Compare_ScaleMC()
{
cout<<"hi"<<endl;

int ialgo = 0;
int ieta = 0;

//cout<<"AK ? Etabin ?\n";
//cin>>ialgo>>ieta;

ialgo-=1;
ieta-=1;

const int nfiles = 3;

const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Bin84_Herwig_Flat_TwoReso_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Bin84_P8_FullPU_tworeso_excorfac2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Bin84_Histograms_Madgraph_Summer_w50.root"};


//const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Data_2016/NTuples/2016BCDEFGH_ntuple_excornewx2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Herwig/NTuples_Hist/Herwig_Flat_TwoReso_excor.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_newexcor2facx2.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50_excor.root"};

/*
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/P8_FullPU_tworeso_excor1.root"};
*/
double data_lumi = 1.;

data_lumi = 33.418;//8.762;//8.762;//8.762;//8.762;//8.762;//8.762;//8.762;//27.683;

const int ref = 3;

const char *model_name[nfiles] = {"Herwig++(CUETHS1)","P8(CUETP8M1)","Madgraph"};
const int col[nfiles] = {4,6,2};
const int sty[nfiles] = {22,20,21};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

double max_range = 3000.;
double min_range = 84.; 

char name[1000];

TFile *filein;

TH1D* Resolution_pt[nfiles][nalgo][netarange][noptbins];
TH1D* JetpT;
TF1 *fitfunc[nfiles][nalgo][netarange][noptbins];

double resolution[nfiles][nalgo][netarange][noptbins];
double median[nfiles][nalgo][netarange][noptbins];
double median_err[nfiles][nalgo][netarange][noptbins];
double bincentre[noptbins];

float leg_x1 = 0.25;
float leg_y1 = 0.35;
float leg_x2 = 0.45;
float leg_y2 = 0.5;

int plotid =  0;

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){
   for(int kl=0; kl<noptbins; kl++){ 
 
	sprintf(name,"Resolution_%s_EtaBin%i_PtBin%i",JetRad[ij],jk+1,kl+1);
        Resolution_pt[fg][ij][jk][kl] = (TH1D*)filein->Get(name);
  	 if(Resolution_pt[fg][ij][jk][kl]->GetEntries()<3) continue ;
    	double q[3] = {0.,0.,0.}; ;
    	double prob[3] = {0.2,0.8,0.5};

	sprintf(name,"fit_%i_%i_%i",ij+1,jk+1,kl+1) ;
   	double amn = Resolution_pt[fg][ij][jk][kl]->GetXaxis()->GetXmin();
   	double amx = Resolution_pt[fg][ij][jk][kl]->GetXaxis()->GetXmax();
   	fitfunc[fg][ij][jk][kl] = new TF1(name,gausX,/*-0.5,0.5*/amn,amx,3);

    	double tmpbinwd = 0.25*Resolution_pt[fg][ij][jk][kl]->GetStdDev();
    	double par[3] = {Resolution_pt[fg][ij][jk][kl]->GetMaximum(),Resolution_pt[fg][ij][jk][kl]->GetMean(),Resolution_pt[fg][ij][jk][kl]->GetRMS()}  ;
    	fitfunc[fg][ij][jk][kl]->SetParameters(par);

	Resolution_pt[fg][ij][jk][kl]->Fit(name,"BQ");

        resolution[fg][ij][jk][kl] = fitfunc[fg][ij][jk][kl]->GetParameter(2);
        median[fg][ij][jk][kl] = fitfunc[fg][ij][jk][kl]->GetParameter(1);
	median_err[fg][ij][jk][kl] = fitfunc[fg][ij][jk][kl]->GetParError(1);

    }//kl 

  }//jk
 }//ij
}//fg

sprintf(name,"%s",filenames[0]);
filein = new TFile(name,"read");
sprintf(name,"JetpT_ak4_EtaBin1");
JetpT =  (TH1D*)filein->Get(name);
 for(int kl=0; kl<noptbins; kl++){
   bincentre[kl] = JetpT->GetBinCenter(kl+1) ;
   }//kl

TCanvas *c2[nalgo][netarange];
TMultiGraph *mul[nalgo][netarange];
TLegend *leg[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

// if((ij!=ialgo)||(jk!=ieta)) continue;

sprintf(name,"ScaleMC_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
c2[ij][jk] = new TCanvas(name,name,50,50,800,600);

leg[ij][jk] = tdrLeg(0.5,0.65,0.85,0.85);

mul[ij][jk] = new TMultiGraph();
/*
sprintf(name,"%s %s",JetRad[ij],ybinname[jk]);
mul[ij][jk]->SetTitle(name);
*/
TGraphErrors *dataplot[nfiles];
for(int fg=0; fg<nfiles; fg++){

double xval[noptbins];
double yval[noptbins];
double yerr[noptbins];
for(int kl=0; kl<noptbins; kl++){
   xval[kl] = bincentre[kl] ;
   yval[kl] = median[fg][ij][jk][kl] ;
   yerr[kl] = median_err[fg][ij][jk][kl] ;
 }

dataplot[fg] = new TGraphErrors(noptbins,xval,yval,NULL,yerr);
dataplot[fg]->SetLineColor(col[fg]);
dataplot[fg]->SetMarkerColor(col[fg]);
dataplot[fg]->SetMarkerStyle(sty[fg]);

leg[ij][jk]->AddEntry(dataplot[fg],model_name[fg],"lp");
mul[ij][jk]->Add(dataplot[fg]);
}

c2[ij][jk]->cd(1);

mul[ij][jk]->Draw("ALP");

mul[ij][jk]->GetXaxis()->SetTitle("Jet P_{T} (in GeV)");
mul[ij][jk]->GetXaxis()->SetRangeUser(74.,2500.);
mul[ij][jk]->GetXaxis()->CenterTitle();
mul[ij][jk]->GetXaxis()->SetLabelSize(0.04);
mul[ij][jk]->GetXaxis()->SetTitleSize(0.05);

mul[ij][jk]->GetYaxis()->SetTitle("JES - 1");
mul[ij][jk]->GetYaxis()->CenterTitle();
mul[ij][jk]->GetYaxis()->SetTitleOffset(0.9);
mul[ij][jk]->GetYaxis()->SetLabelSize(0.04);
mul[ij][jk]->GetYaxis()->SetTitleSize(0.05);

mul[ij][jk]->SetMinimum(-0.11);
mul[ij][jk]->SetMaximum(0.11);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.065);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.1,leg_y1-0.125,text1);
 
 leg[ij][jk]->SetTextSize(0.04);
 leg[ij][jk]->SetTextFont(42);
 leg[ij][jk]->Draw(); 
 
sprintf(name,"JES_MC_Plots/%s.eps",c2[ij][jk]->GetName());
c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij


}

int main()
{
Compare_ScaleMC();
}
