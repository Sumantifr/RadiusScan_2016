#include "My_Style.C"
void Check_me()
{
cout<<"check me\n";
const int nfiles = 2;
const char *filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Control_Plots/hist_RecoJetchs_PU_Data_2016G_JetHTMETFilters.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pure_Gen/RootFiles/hist_Powheg_Pythia_paolo1000events.root"};

const char *model_name[nfiles] = {"Data","Powheg_Pythia"};
const int col[nfiles] = {1,2};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

char name[1000];

TFile *filein;

TH1D* hist_pt[nfiles][nalgo][netarange];
TH1D* hist_y[nfiles][nalgo];
TH1D* hist_pt_rat[nfiles-1][nalgo][netarange];
TH1D* hist_y_rat[nfiles-1][nalgo];

for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

    sprintf(name,"mcjets/JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
   if(fg==1) {sprintf(name,"mcjets/Gen_MC_JetpT_%s_EtaBin%i",JetRad[ij],jk+1);}
    hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);

   for(int bn=0; bn<(hist_pt[fg][ij][jk]->GetNbinsX()); bn++){
     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
     hist_pt[fg][ij][jk]->SetBinError(bn+1,hist_pt[fg][ij][jk]->GetBinError(bn+1)*1.0/(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));
    }
   }//jk
 }//ij
}//fg

TPad *main_pad;
TPad *sub_pad[2];

TCanvas *c1;
sprintf(name,"%s","canvsname");
c1 = CMS_Canvas(name,2,0,1);
//c1->Draw();
c1->cd(1);
/*
sprintf(name,"pad_Compare_Canv_ak1_EtaBin1");
main_pad = new TPad(name,name,0.,0.,1.,0.85);

main_pad->Draw();
*/
//main_pad->cd();
/*main_pad->Divide(1,2,-1.e-40,-1.e-40,0);

sub_pad[0] = (TPad*)main_pad->GetPad(1);
sub_pad[0]->SetPad(0.01,0.4,0.985,0.8);
sub_pad[0]->SetTopMargin(0.01);
sub_pad[0]->SetBottomMargin(0.015);
sub_pad[0]->SetRightMargin(0.01);
sub_pad[0]->cd() ;
*/

gPad->SetLogx(1);
gPad->SetLogy(1);

for(int fg=0; fg<nfiles; fg++){
hist_pt[fg][0][0]->Draw("SAME"); 
}

}
