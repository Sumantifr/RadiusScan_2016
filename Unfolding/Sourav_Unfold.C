#include "TH1.h"
#include "TH2F.h"
#include "TF1.h"

#include "TFile.h"

#include "TMath.h"

#include "RooUnfold.h"
#include "RooUnfoldBayes.h"

using namespace std;
//gSystem->Load("/home/suman/RooUnfold/libRooUnfold.so");



void Sourav_Unfold() {


// get MC


const char* rootfiles[3] = {"../CPlusPlus/CMS_Files/Jets_in_CMS/Data_2015D/hist_RecoJetchs_PU_Data_2015D_JetHTCHS_NewPrescale_v2.root", "../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root", /*"../CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/hist_Pythia_pTBinnedCHS_LumiWeighted_syst.root"*/"Response_Matrix/Spline_output_ak4.root"}   ;

char name[100];

TH1F *hist_data;
TH1F *hist_reco;
TH1F *hist_gen;
TH2F *mat_rm;
TH2F *mat_rm_b;
TH1F *hist_bayes;
TH1F* hist_svd;
TH1F* hist_BbB;

int ialgo = 4;
int ieta = 1;

for(int ij=0; ij<3; ij++){
sprintf(name,"%s",rootfiles[ij]);
TFile *file1 = new TFile(name,"read");
file1->cd();
if(ij==0) {
        sprintf(name,"mcjets/JetpT_ak%i_EtaBin%i",ialgo,ieta);
//        hist_data = rebin_hist((TH1F*)file1->Get(name),ieta-1);
      hist_data = (TH1F*)file1->Get(name);
        }
if(ij==1) {
        sprintf(name,"JetpT_ak%i_EtaBin%i",ialgo,ieta);
//        hist_reco = rebin_hist((TH1F*)file1->Get(name),ieta-1);
      hist_reco = (TH1F*)file1->Get(name); 
        sprintf(name,"Gen_MC_JetpT_ak%i_EtaBin%i",ialgo,ieta);
//        hist_gen = rebin_hist((TH1F*)file1->Get(name),ieta-1);
      hist_gen = (TH1F*)file1->Get(name); 
        }
if(ij==2) {
//      sprintf(name,"RecoJetvsGenJet_Algo%i_EtabBin%i",ialgo-1,ieta+1);
        sprintf(name,"Response_Matrix_ak%i_EtaBin%i",ialgo,ieta);
        mat_rm = (TH2F*)file1->Get(name);
        cout<<"nxbisn "<<mat_rm->GetNbinsX()<<" ybins "<<mat_rm->GetNbinsY()<<endl;
        mat_rm_b = (TH2F*)mat_rm->Clone();
        mat_rm_b->Scale(1./mat_rm_b->Integral());
        }
}


// ~~~~~ unfolding ~~~~~~

// reco and gen matrices below are used for fake events subtraction. One can also use argument (0, 0, rmatrix)

// for RooUnfoldResponse object -- then fakes will not be taken into account.


 RooUnfoldResponse resp_matr_obj_mc(hist_reco, hist_gen, mat_rm);


 RooUnfoldBayes unfold_theor(&resp_matr_obj_mc, hist_data, 4);


 TH1D*  result = (TH1D*)unfold_theor.Hreco();

 result->DrawCopy();


}

int main()
{
 Sourav_Unfold();
}
