void Compare_AK5AK7()
{

  gROOT->SetStyle("Plain");

  // Plot: p8810_d13x1y2
  double p8810_d13x1y1_xval[] = { 60.0, 69.0, 79.0, 90.5, 105.5, 123.5, 143.0, 163.5, 185.0, 
    208.0, 232.5, 258.5, 286.0, 315.0, 346.0, 378.5, 412.5, 449.0, 487.5, 
    527.5, 570.0, 615.0, 662.0, 711.5, 763.5, 818.0, 875.5, 936.0, 999.5, 
    1066.5, 1136.5, 1210.0, 1287.5 };
  double p8810_d13x1y1_xerrminus[] = { 4.0, 5.0, 5.0, 6.5, 8.5, 9.5, 10.0, 10.5, 11.0, 
    12.0, 12.5, 13.5, 14.0, 15.0, 16.0, 16.5, 17.5, 19.0, 19.5, 
    20.5, 22.0, 23.0, 24.0, 25.5, 26.5, 28.0, 29.5, 31.0, 32.5, 
    34.5, 35.5, 38.0, 39.5 };
  double p8810_d13x1y1_xerrplus[] = { 4.0, 5.0, 5.0, 6.5, 8.5, 9.5, 10.0, 10.5, 11.0, 
    12.0, 12.5, 13.5, 14.0, 15.0, 16.0, 16.5, 17.5, 19.0, 19.5, 
    20.5, 22.0, 23.0, 24.0, 25.5, 26.5, 28.0, 29.5, 31.0, 32.5, 
    34.5, 35.5, 38.0, 39.5 };
  double p8810_d13x1y1_yval[] = { 0.6964, 0.7085, 0.7171, 0.7401, 0.76, 0.7858, 0.8064, 0.8004, 0.811, 
    0.8165, 0.8158, 0.8189, 0.8473, 0.8376, 0.8431, 0.8519, 0.8491, 0.8516, 0.8582, 
    0.8639, 0.8681, 0.8674, 0.8632, 0.8684, 0.8829, 0.881, 0.8645, 0.8771, 0.877, 
    0.8895, 0.8815, 0.8745, 0.8983 };
  double p8810_d13x1y1_yerrminus[] = { 0.016312568045234323, 0.015217722484905553, 0.01561280958988484, 0.016719121612393396, 0.013180287715410464, 0.01088255757083784, 0.011215166873662648, 0.01253397713896112, 0.010866923472666955, 
    0.008245601947929575, 0.008608134785863893, 0.009483140780759295, 0.011233878129746647, 0.011635738954187654, 0.0071937431075900955, 0.011509555117536038, 0.007269115424128303, 0.006408586764997413, 0.006462977093081794, 
    0.014300741493534523, 0.009620289881890254, 0.009002223425293332, 0.006766829172987893, 0.0062128910887685775, 0.006987842366489101, 0.008204268625014664, 0.009738581885084707, 0.012099578804822094, 0.01555246420667799, 
    0.019758839100972002, 0.024991398543997092, 0.029574481920060746, 0.04422047027802848 };
  double p8810_d13x1y1_yerrplus[] = { 0.015984701064155064, 0.015054576306811162, 0.015440174773946052, 0.016607507056749966, 0.013082428994471937, 0.010763827156035162, 0.011136426060958694, 0.01253397713896112, 0.010866923472666955, 
    0.00816516963060168, 0.008512925582313051, 0.009424433243224763, 0.011185257533490233, 0.01163445198763139, 0.007128812347901998, 0.011509555117536038, 0.007268429341253858, 0.006408586764997413, 0.006462977093081794, 
    0.014300741493534523, 0.009620289881890254, 0.009002223425293332, 0.006766829172987893, 0.0062128910887685775, 0.006987842366489101, 0.008204268625014664, 0.009738581885084707, 0.012067305831796094, 0.015553427621990594, 
    0.019758078598540396, 0.024991398543997092, 0.029574481920060746, 0.04422047027802848 };
  double p8810_d13x1y1_ystatminus[] = { 0.00786448, 0.00841724, 0.0106677, 0.012839, 0.00894427, 0.00577235, 0.00752396, 0.0101124, 0.00822922, 
    0.00503289, 0.00591354, 0.00746726, 0.00970464, 0.0104695, 0.00530754, 0.0105019, 0.00571402, 0.00466154, 0.00480521, 
    0.0136624, 0.0086977, 0.00811542, 0.00566392, 0.004998, 0.00600083, 0.00750067, 0.00920706, 0.0116155, 0.0152003, 
    0.0195003, 0.0248, 0.0294, 0.0441 };
  double p8810_d13x1y1_ystatplus[] = { 0.00786448, 0.00841724, 0.0106677, 0.012839, 0.00894427, 0.00577235, 0.00752396, 0.0101124, 0.00822922, 
    0.00503289, 0.00591354, 0.00746726, 0.00970464, 0.0104695, 0.00530754, 0.0105019, 0.00571402, 0.00466154, 0.00480521, 
    0.0136624, 0.0086977, 0.00811542, 0.00566392, 0.004998, 0.00600083, 0.00750067, 0.00920706, 0.0116155, 0.0152003, 
    0.0195003, 0.0248, 0.0294, 0.0441 };
  int p8810_d13x1y1_numpoints = 33;
  p8810_d13x1y1 = TGraphAsymmErrors(p8810_d13x1y1_numpoints, p8810_d13x1y1_xval, p8810_d13x1y1_yval, p8810_d13x1y1_xerrminus, p8810_d13x1y1_xerrplus, p8810_d13x1y1_yerrminus, p8810_d13x1y1_yerrplus);
  p8810_d13x1y1.SetName("/HepData/8810/d13x1y1");
  p8810_d13x1y1.SetTitle("/HepData/8810/d13x1y1");
  p8810_d13x1y1.Draw("AP");

  double p8810_d13x1y2_xval[] = { 60.0, 69.0, 79.0, 90.5, 105.5, 123.5, 143.0, 163.5, 185.0, 
    208.0, 232.5, 258.5, 286.0, 315.0, 346.0, 378.5, 412.5, 449.0, 487.5, 
    527.5, 570.0, 615.0, 662.0, 711.5, 763.5, 818.0, 875.5, 936.0, 999.5, 
    1066.5, 1136.5, 1210.0, 1287.5 };
  double p8810_d13x1y2_xerrminus[] = { 4.0, 5.0, 5.0, 6.5, 8.5, 9.5, 10.0, 10.5, 11.0, 
    12.0, 12.5, 13.5, 14.0, 15.0, 16.0, 16.5, 17.5, 19.0, 19.5, 
    20.5, 22.0, 23.0, 24.0, 25.5, 26.5, 28.0, 29.5, 31.0, 32.5, 
    34.5, 35.5, 38.0, 39.5 };
  double p8810_d13x1y2_xerrplus[] = { 4.0, 5.0, 5.0, 6.5, 8.5, 9.5, 10.0, 10.5, 11.0, 
    12.0, 12.5, 13.5, 14.0, 15.0, 16.0, 16.5, 17.5, 19.0, 19.5, 
    20.5, 22.0, 23.0, 24.0, 25.5, 26.5, 28.0, 29.5, 31.0, 32.5, 
    34.5, 35.5, 38.0, 39.5 };
  double p8810_d13x1y2_yval[] = { 0.8493, 0.8702, 0.8903, 0.9079, 0.9241, 0.9375, 0.9478, 0.9555, 0.9615, 
    0.9663, 0.9702, 0.9733, 0.9759, 0.978, 0.9797, 0.9812, 0.9825, 0.9836, 0.9845, 
    0.9852, 0.9859, 0.9865, 0.987, 0.9875, 0.9879, 0.9882, 0.9885, 0.9888, 0.989, 
    0.9892, 0.9894, 0.9896, 0.9897 };
  double p8810_d13x1y2_yerrminus[] = { 0.0157, 0.015, 0.0143, 0.0135, 0.0123, 0.011, 0.0098, 0.0087, 0.0076, 
    0.0067, 0.0059, 0.0051, 0.0044, 0.0038, 0.0033, 0.0028, 0.0023, 0.0019, 0.0016, 
    0.0012, 9.0E-4, 6.0E-4, 4.0E-4, 2.0E-4, 0.0, 2.0E-4, 4.0E-4, 6.0E-4, 7.0E-4, 
    9.0E-4, 0.001, 0.0011, 0.0012 };
  double p8810_d13x1y2_yerrplus[] = { 0.0157, 0.015, 0.0143, 0.0135, 0.0123, 0.011, 0.0098, 0.0087, 0.0076, 
    0.0067, 0.0059, 0.0051, 0.0044, 0.0038, 0.0033, 0.0028, 0.0023, 0.0019, 0.0016, 
    0.0012, 9.0E-4, 6.0E-4, 4.0E-4, 2.0E-4, 0.0, 2.0E-4, 4.0E-4, 6.0E-4, 7.0E-4, 
    9.0E-4, 0.001, 0.0011, 0.0012 };
  double p8810_d13x1y2_ystatminus[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0 };
  double p8810_d13x1y2_ystatplus[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0 };
  int p8810_d13x1y2_numpoints = 33;
  p8810_d13x1y2 = TGraphAsymmErrors(p8810_d13x1y2_numpoints, p8810_d13x1y2_xval, p8810_d13x1y2_yval, p8810_d13x1y2_xerrminus, p8810_d13x1y2_xerrplus, p8810_d13x1y2_yerrminus, p8810_d13x1y2_yerrplus);
  p8810_d13x1y2.SetName("/HepData/8810/d13x1y2");
  p8810_d13x1y2.SetTitle("/HepData/8810/d13x1y2");
  p8810_d13x1y2.Draw("AP");
  
  TFile *file_2 = new TFile("/home/suman/RooUnfold/Final/Unfolded_2016_Data_NTuple_MC_P8_Legacy_new_excor.root","read");
  
  TH1D *h_AK5_svd = (TH1D*)file_2->Get("svd_unfold_ak5_Etabin1");
  TH1D *h_AK7_svd = (TH1D*)file_2->Get("svd_unfold_ak7_Etabin1");
  TH1D *h_rat_AK5byAK7_svd = (TH1D*)h_AK5_svd->Clone(); h_rat_AK5byAK7_svd->Divide(h_AK7_svd);
  h_rat_AK5byAK7_svd->SetLineColor(kBlue);
  h_rat_AK5byAK7_svd->SetMarkerColor(kBlue);
  h_rat_AK5byAK7_svd->SetStats(0);
  
  TH1D *h_AK5_bayes = (TH1D*)file_2->Get("bayes_unfold_ak5_Etabin1");
  TH1D *h_AK7_bayes = (TH1D*)file_2->Get("bayes_unfold_ak7_Etabin1");
  TH1D *h_rat_AK5byAK7_bayes = (TH1D*)h_AK5_bayes->Clone(); h_rat_AK5byAK7_bayes->Divide(h_AK7_bayes);
  h_rat_AK5byAK7_bayes->SetLineColor(kRed);
  h_rat_AK5byAK7_bayes->SetMarkerColor(kRed);
  h_rat_AK5byAK7_bayes->SetStats(0);
  
  ifstream fp_rad_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Final_Files/Total_ExpSys_Rad_excor_trig_84.log");
//  ifstream fp_rad_exp("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/Total_ExpSys_Rad_excor_84_wAK5.log");
  ifstream fp_rad_stat("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/Systematics/StatUnc_Plots/Unc_Rad_Jackknife_Stat_DataplusRM_84.log");
  const int nalgo = 10;
  const int netarange = 10;
  const int noptbins = 61;
  
  double rad_dem_exp_up[nalgo][netarange][noptbins+1]={0}, rad_dem_stat_up[nalgo][netarange][noptbins+1]={0};
  double rad_dem_exp_dn[nalgo][netarange][noptbins+1]={0}, rad_dem_stat_dn[nalgo][netarange][noptbins+1]={0};
  
  for(int ij=0; ij<nalgo; ij++){
    for(int jk=0; jk<netarange; jk++){
     for(int kl=0; kl<noptbins; kl++){
	     int xx1,xx2,xx3;
	     fp_rad_exp>>xx1>>xx2>>xx3>>rad_dem_exp_up[ij][jk][kl+1]>>rad_dem_exp_dn[ij][jk][kl+1];

	     rad_dem_exp_up[ij][jk][kl+1] *= h_rat_AK5byAK7_svd->GetBinContent(kl+2);
	     rad_dem_exp_dn[ij][jk][kl+1] *= h_rat_AK5byAK7_svd->GetBinContent(kl+2);
	 }
     for(int kl=0; kl<(noptbins+1); kl++){
	     int xx1,xx2,xx3;
	     fp_rad_stat>>xx1>>xx2>>xx3>>rad_dem_stat_up[ij][jk][kl+1]>>rad_dem_stat_dn[ij][jk][kl+1];

	     rad_dem_stat_up[ij][jk][kl+1] *= h_rat_AK5byAK7_svd->GetBinContent(kl+2);
             rad_dem_stat_dn[ij][jk][kl+1] *= h_rat_AK5byAK7_svd->GetBinContent(kl+2);

		}
	}
  }
  
  double my_rad_err_up[noptbins+1];
  double my_rad_err_dn[noptbins+1];
  double my_ak7_ak5_rat[noptbins+1];
  TGraphAsymmErrors *my_gr_ak7_ak5 = new TGraphAsymmErrors();
   
   
  int irad = 5; 
  for(int kl=0; kl<(noptbins+1); kl++){
	  my_rad_err_up[kl] = max(rad_dem_exp_up[irad][0][kl],rad_dem_exp_dn[irad][0][kl]);
	  my_rad_err_dn[kl] = max(rad_dem_exp_up[irad][0][kl],rad_dem_exp_dn[irad][0][kl]);
/*
	  my_rad_err_up[kl] = sqrt(pow(my_rad_err_up[kl],2) + pow(rad_dem_stat_up[irad][0][kl],2));
	  my_rad_err_dn[kl] = sqrt(pow(my_rad_err_dn[kl],2) + pow(rad_dem_stat_dn[irad][0][kl],2));
*/	 
// 	  cout<<kl+1<<" up "<<my_rad_err_up[kl]<<" down "<<my_rad_err_dn[kl]<<endl;
 
	  if(kl==3){
		  my_rad_err_up[kl] *= 1.75;
		  my_rad_err_dn[kl] *= 1.75;
		  }
	  
	  if(kl==4){
                  my_rad_err_up[kl] *= 1.5;
                  my_rad_err_dn[kl] *= 1.5;
                  }


	  my_ak7_ak5_rat[kl] = h_rat_AK5byAK7_svd->GetBinContent(kl+1);
	  my_gr_ak7_ak5->SetPoint(kl,h_rat_AK5byAK7_svd->GetBinCenter(kl+1),my_ak7_ak5_rat[kl]);
	  my_gr_ak7_ak5->SetPointEYhigh(kl,my_rad_err_up[kl]);
	  my_gr_ak7_ak5->SetPointEYlow(kl,my_rad_err_dn[kl]);
  }
  
  my_gr_ak7_ak5->SetLineColor(kRed);
  my_gr_ak7_ak5->SetMarkerColor(kRed);
  my_gr_ak7_ak5->SetMarkerStyle(kFullTriangleUp);
  p8810_d13x1y1.SetMarkerStyle(kFullTriangleDown);
 
  
  TCanvas *c1 = new TCanvas("c1","c1",50,50,800,600);
  TLegend *leg1 = new TLegend(0.15,0.7,0.375,0.875);
  leg1->SetTextFont(42); leg1->SetBorderSize(0);
  c1->cd();
  gPad->SetLogx(1);
  
  p8810_d13x1y1.GetXaxis()->SetRangeUser(80,1588);
  p8810_d13x1y1.GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  p8810_d13x1y1.GetXaxis()->CenterTitle();
  p8810_d13x1y1.GetYaxis()->SetTitle("#sigma (AK5) / #sigma (AK7)");
  p8810_d13x1y1.GetYaxis()->CenterTitle();
  
  p8810_d13x1y1.Draw("AP");
//  h_rat_AK5byAK7_svd->Draw("sames");
  my_gr_ak7_ak5->Draw("P,sames");

  leg1->AddEntry(&p8810_d13x1y1,"SMP-13-002","lpe");
  leg1->AddEntry(my_gr_ak7_ak5,"SMP-19-003","lpe");
  leg1->Draw();
  c1->SaveAs("Crosscheck_AK5AK7_wAK5error.pdf");

  
}

int main()
{
Compare_AK5AK7();
}
