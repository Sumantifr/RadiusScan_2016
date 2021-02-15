//void ChiPlotter(){
void Chisquare_niter(){
const int niter = 13;
//AK2
double chi2_AK2[niter] = {5.68404,4.06072,3.56289,3.31198,3.15092,3.03444,2.94465,2.87303,2.81496,2.76769,2.72954,2.69942,2.67658};

//AK4
double chi2_AK4[niter] = {8.22696,6.85531,6.64393,6.55322,6.50005,6.47028,6.45797,6.45936,6.47227,6.49561,6.52893,6.57214,6.6253};

//AK8
double chi2_AK8[niter] = {6.56169,4.29292,3.68975,3.37539,3.17466,3.03951,2.94566,2.87858,2.82929,2.79222,2.764,2.74262,2.72696};

TH1D *h1[3];
const char *model[3] = {"AK2 (|y|<0.5)","AK4 (|y|<0.5)","AK8 (|y|<0.5)"};
int col[3] = {kRed,kBlue,kMagenta};

char name[100];

for(int ik=0; ik<3; ik++){

sprintf(name,"Chisquare_AK%i",int(pow(2,ik+1)));
h1[ik] = new TH1D(name,name,niter,-0.1,niter-0.1);

for(int bn=0; bn<niter; bn++){
  if(ik==0) {h1[ik]->SetBinContent(bn+1,chi2_AK2[bn]);}
  if(ik==1) {h1[ik]->SetBinContent(bn+1,chi2_AK4[bn]);}
  if(ik==2) {h1[ik]->SetBinContent(bn+1,chi2_AK8[bn]);}
  h1[ik]->SetBinError(bn+1,0);
 }

 h1[ik]->SetStats(0);
 h1[ik]->SetTitle(0);
 h1[ik]->SetMarkerColor(col[ik]);
 h1[ik]->SetLineColor(col[ik]);
 h1[ik]->SetMarkerStyle(21+ik);

 h1[ik]->GetXaxis()->SetTitle("# of iterations");
 h1[ik]->GetYaxis()->SetTitle("#chi^{2} / NDF");

 h1[ik]->SetMinimum(0); h1[ik]->SetMaximum(9);
}

TCanvas *c1 = new TCanvas("Canv_ChiSquare","Canv_ChiSquare",800,600);
TLegend *leg1 = new TLegend(0.7,0.78,0.88,0.88);

leg1->SetBorderSize(0); leg1->SetTextFont(42); 

c1->cd();
h1[1]->Draw("p");
h1[0]->Draw("p,sames");
h1[2]->Draw("p,sames");

leg1->AddEntry(h1[0],model[0],"lp");
leg1->AddEntry(h1[1],model[1],"lp");
leg1->AddEntry(h1[2],model[2],"lp");

leg1->Draw();

c1->SaveAs("Canv_ChiSquare.pdf");
}
