#include "/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Plot_Maker/My_Style.C"

#include "TFile.h"
#include "TH1D.h"

void Iteration_Check_Bayesian()
{

int ialgo = 4;
int ieta = 1;

ialgo-=1;

const int nfiles = 6;
//const char *filenames[nfiles] = {"Unfolded_2016_Data_n4.root","Unfolded_2016_Data_n6.root","Unfolded_2016_Data_n7.root","Unfolded_2016_Data_n8.root"};
const char *filenames[nfiles] = {
"Iteration_Files/Data_Legacy_Iter4.root",
"Iteration_Files/Data_Legacy_Iter5.root",
"Iteration_Files/Data_Legacy_Iter6.root",
"Iteration_Files/Data_Legacy_Iter7.root",
"Iteration_Files/Data_Legacy_Iter8.root",
"Iteration_Files/Data_Legacy_Iter9.root"
};

const char *model_name[nfiles] = {"4 Iterations","5 Iterations","6 Iterations","7 Iterations","8 Iterations","9 Iterations"};
const int col[nfiles] = {2,3,4,6,kCyan+2,kTeal+3};

static const int nalgo = 12 ;
static const int netarange = 10 ;

const char *JetRad[nalgo] = {"ak1","ak2","ak3","ak4","ak5","ak6","ak7","ak8","ak9","ak10","ak11","ak12"};
double ybin[netarange+1] = {0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.7,4.2,4.7};

const char* jetname[nalgo] = {"ak1chs","ak2chs","ak3chs","ak4chs","ak5chs","ak6chs","ak7chs","ak8chs","ak9chs","ak10chs","ak11chs","ak12chs"};
const char* ybinname[netarange] = {"|y|<0.5","0.5<|y|<1.0","1.0<|y|<1.5","1.5<|y|<2.0","2.0<|y|<2.5","2.5<|y|<3.0","3.0<|y|<3.2","3.2<|y|<3.7","3.7<|y|<4.2","4.2<|y|<4.7"} ;

char name[1000];

TFile *filein;
TH1D* hist_error[nfiles][nalgo][netarange];

TLine *line = new TLine(0,1,62,1.);
line->SetLineColor(7);

float leg_x1 = 0.25;
float leg_y1 = 0.2;
float leg_x2 = 0.45;
float leg_y2 = 0.5;


for(int fg=0; fg<nfiles; fg++){

sprintf(name,"%s",filenames[fg]);
filein = new TFile(name,"read");
filein->cd();

 for(int ij=0; ij<nalgo; ij++){
  for(int jk=0; jk<netarange; jk++){

   if(ij!=ialgo) continue ;

   sprintf(name,"Bayes_%s_EtaBin%i_error",JetRad[ij],jk+1);
   hist_error[fg][ij][jk] =  (TH1D*)filein->Get(name);

   hist_error[fg][ij][jk]->GetXaxis()->SetTitle("Bin No.");
   hist_error[fg][ij][jk]->GetXaxis()->SetTitleSize(0.05);
   hist_error[fg][ij][jk]->GetXaxis()->SetLabelSize(0.05);
   hist_error[fg][ij][jk]->GetXaxis()->CenterTitle(); 

   hist_error[fg][ij][jk]->GetYaxis()->SetTitle("Relative Error After / Before");
   hist_error[fg][ij][jk]->GetYaxis()->SetTitleSize(0.05);
   hist_error[fg][ij][jk]->GetYaxis()->SetLabelSize(0.05);
   hist_error[fg][ij][jk]->GetYaxis()->CenterTitle();

   hist_error[fg][ij][jk]->SetMinimum(0.5);
   hist_error[fg][ij][jk]->SetMaximum(1.5);
    }//jk
  }//ij
 }//fg


TCanvas *c2[nalgo][netarange];

TLegend *leg_err[nalgo][netarange];

for(int ij=0; ij<nalgo; ij++){
 for(int jk=0; jk<netarange; jk++){

  if(ij!=ialgo) continue ;

 sprintf(name,"Iter_Pt_Compare_Canv_%s_EtaBin%i",JetRad[ij],jk+1);
 c2[ij][jk] = tdrCanvas(name,hist_error[0][ij][jk],7,0);

 leg_err[ij][jk] = tdrLeg(0.45,0.15,0.75,0.45);

 c2[ij][jk]->cd(1);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.05);

  TString text;
  text+= jetname[ij];
  TString text1;
  text1+=  ybinname[jk];

 // cout<<0.5*(leg_x1+leg_x2)<<endl;


  for(int fg=0; fg<nfiles; fg++){

      hist_error[fg][ij][jk]->SetLineColor(col[fg]);
      if(fg==0) { hist_error[fg][ij][jk]->Draw("e"); }
	else { hist_error[fg][ij][jk]->Draw("sames");  }
//      tdrDraw(hist_error[fg][ij][jk],kFullCircle,col[fg],kSolid,col[fg] ,1001,2);
      leg_err[ij][jk]->AddEntry(hist_error[fg][ij][jk],model_name[fg],"l");

   }//fg

  leg_err[ij][jk]->SetTextFont(42);
  leg_err[ij][jk]->Draw();

  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1+0.05,text);
  latex.DrawLatex(0.5*(leg_x1+leg_x2)+0.05,leg_y1,text1);


  sprintf(name,"Error_Plots/%s.eps",c2[ij][jk]->GetName());
  c2[ij][jk]->SaveAs(name);

  }//jk
 }//ij
}

int main()
{
Iteration_Check_Bayesian();
}
