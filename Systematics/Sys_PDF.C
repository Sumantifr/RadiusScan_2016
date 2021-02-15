#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include <iostream>
#include <fstream>
#include <TH1D.h>
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

void Sys_PDF()
{

const int nalgo = 12;
const int Etabins = 10;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[Etabins] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

double ybin[Etabins+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const int nfiles = 3;
const char* pdfset[nfiles]={"CT14nlo","MMHT2014","NNPDF_nlo_alphas118"};

const int noptbins = 62;
double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};

const int ref = 4;

int col[2] = {2,4};

const char* filenames[nfiles] = {"/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF_CT14nlo/FastNLO_PDFCT14nlo_out.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF_MMHT2014nlo/FastNLO_PDFMMHT2014nlo68cl_out.root","/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/NLOJet++/FastNLO_Files/FastNLO_Convert/PDF_NNPDF30nlo/FastNLO_PDFNNPDF30_nlo_as_0118_out.root"};

TFile *filein;

TH1D *hist_pt[nfiles][nalgo][Etabins];
TH1D *hist_rad[nfiles][nalgo][Etabins];

double err_pt_up[nalgo][Etabins][noptbins];
double err_pt_dn[nalgo][Etabins][noptbins];

double err_rad_up[nalgo][Etabins][noptbins];
double err_rad_dn[nalgo][Etabins][noptbins];

char name[100];

for(int fg=0; fg<nfiles; fg++){
sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
//filein->cd();

for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<Etabins; jk++){
 
   sprintf(name,"JetpT_%s_EtaBin%i",JetRad[ij],jk+1);
   hist_pt[fg][ij][jk] = (TH1D*)filein->Get(name);
  }
 }
}

//filein->Close();

/*
for(int fg=0; fg<nfiles; fg++){
for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<Etabins; jk++){

    hist_rad[fg][ij][jk] = (TH1D*)hist_pt[fg][ij][jk]->Clone();
    hist_rad[fg][ij][jk]->Divide(hist_rad[fg][ref][jk]);

  }
 }
}
*/
for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<Etabins; jk++){
    for(int bn=0; bn<noptbins; bn++){

    double maxdiff = 1.e-10;
     for(int fg=0; fg<nfiles; fg++){

     hist_pt[fg][ij][jk]->SetBinContent(bn+1,hist_pt[fg][ij][jk]->GetBinContent(bn+1)*1./(hist_pt[fg][ij][jk]->GetBinWidth(bn+1)*(ybin[jk+1]-ybin[jk])));

     double diff = abs( hist_pt[fg][ij][jk]->GetBinContent(bn+1) - hist_pt[0][ij][jk]->GetBinContent(bn+1)) ;
     if(diff>maxdiff) { maxdiff = diff ;}
	}
     err_pt_up[ij][jk][bn] = maxdiff/max(1.e-6,hist_pt[0][ij][jk]->GetBinContent(bn+1));
     err_pt_dn[ij][jk][bn] = maxdiff/max(1.e-6,hist_pt[0][ij][jk]->GetBinContent(bn+1));
  }
 }
}

/*
for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<Etabins; jk++){
    for(int bn=0; bn<noptbins; bn++){

    double maxdiff = 1.e-10;
     for(int fg=1; fg<nfiles; fg++){
     double diff = abs( hist_rad[fg][ij][jk]->GetBinContent(bn+1) - hist_rad[0][ij][jk]->GetBinContent(bn+1)) ;
     if(diff<maxdiff) { maxdiff = diff ;}
        }
     err_rad_up[ij][jk][bn] = maxdiff/max(1.e-6,hist_rad[0][ij][jk]->GetBinContent(bn+1));
     err_rad_dn[ij][jk][bn] = maxdiff/max(1.e-6,hist_rad[0][ij][jk]->GetBinContent(bn+1));
     
     fp_rad<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<err_rad_up[ij][jk][bn]<<'\t'<<err_rad_dn[ij][jk][bn]<<endl;
  }
 }
}
*/

ofstream fp_pt;
fp_pt.open("PDF_Pt.log");
for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<Etabins; jk++){
    for(int bn=0; bn<noptbins; bn++){
    fp_pt<<ij+1<<'\t'<<jk+1<<'\t'<<bn+1<<'\t'<<err_pt_up[ij][jk][bn]<<'\t'<<err_pt_dn[ij][jk][bn]<<endl;
 }
}
}
fp_pt.close();


}

int main()
{
Sys_PDF();
}
