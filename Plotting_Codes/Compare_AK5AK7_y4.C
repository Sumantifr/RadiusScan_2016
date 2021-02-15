void Compare_AK5AK7_y4()
{

  gROOT->SetStyle("Plain");

  // Plot: p8810_d16x1y2
  double p8810_d16x1y1_xval[] = { 60.0, 69.0, 79.0, 90.5, 105.5, 123.5, 143.0, 163.5, 185.0, 
    208.0, 232.5, 258.5, 286.0, 315.0, 346.0, 378.5, 412.5, 449.0, 487.5, 
    527.5, 570.0, 615.0, 662.0, 711.5, 763.5, 818.0 };
  double p8810_d16x1y1_xerrminus[] = { 4.0, 5.0, 5.0, 6.5, 8.5, 9.5, 10.0, 10.5, 11.0, 
    12.0, 12.5, 13.5, 14.0, 15.0, 16.0, 16.5, 17.5, 19.0, 19.5, 
    20.5, 22.0, 23.0, 24.0, 25.5, 26.5, 28.0 };
  double p8810_d16x1y1_xerrplus[] = { 4.0, 5.0, 5.0, 6.5, 8.5, 9.5, 10.0, 10.5, 11.0, 
    12.0, 12.5, 13.5, 14.0, 15.0, 16.0, 16.5, 17.5, 19.0, 19.5, 
    20.5, 22.0, 23.0, 24.0, 25.5, 26.5, 28.0 };
  double p8810_d16x1y1_yval[] = { 0.7001, 0.7137, 0.7253, 0.7725, 0.7597, 0.7678, 0.7799, 0.8084, 0.815, 
    0.8088, 0.8336, 0.8312, 0.8187, 0.8424, 0.8491, 0.852, 0.8538, 0.8739, 0.8527, 
    0.8649, 0.8547, 0.8816, 0.8585, 0.8449, 0.8634, 0.8635 };
  double p8810_d16x1y1_yerrminus[] = { 0.026688966882402927, 0.01798748278024471, 0.018737104228775586, 0.02045608706717881, 0.014691834650202813, 0.012579346467161957, 0.013304884590690744, 0.01662708506901014, 0.011676043121781454, 
    0.010641425611641515, 0.011596118417332586, 0.01308818733865007, 0.016769905400257926, 0.009712878877001401, 0.009394146739592692, 0.00977138801839841, 0.010075714078838284, 0.010264011868903895, 0.012563807871819753, 
    0.010282999295891253, 0.011649034377599716, 0.012570628441685007, 0.016096583092072677, 0.0224231852620095, 0.032976962473120534, 0.05800586206610846 };
  double p8810_d16x1y1_yerrplus[] = { 0.02624714155446265, 0.017555628364134393, 0.018531007697370372, 0.020355138844282052, 0.014573612423791845, 0.012497203204753454, 0.013237067776350623, 0.016576487209104346, 0.011606467451386748, 
    0.010547510779122247, 0.01153776176105227, 0.01308818733865007, 0.016769905400257926, 0.009712878877001401, 0.009394146739592692, 0.00977138801839841, 0.010018981896026163, 0.010264011868903895, 0.012517158088483983, 
    0.01027327073082862, 0.011597840951060676, 0.012570628441685007, 0.01605895310361482, 0.022392840061521896, 0.032960885222875914, 0.05799491375965999 };
  double p8810_d16x1y1_ystatminus[] = { 0.0201547, 0.00971236, 0.0131548, 0.0159531, 0.00960417, 0.00743303, 0.00971854, 0.0142088, 0.00804301, 
    0.00738241, 0.00886848, 0.0110073, 0.0153013, 0.00707248, 0.00687095, 0.00748131, 0.00786448, 0.00807527, 0.0109018, 
    0.00802808, 0.00969381, 0.0106283, 0.0147, 0.0214674, 0.0323, 0.0576 };
  double p8810_d16x1y1_ystatplus[] = { 0.0201547, 0.00971236, 0.0131548, 0.0159531, 0.00960417, 0.00743303, 0.00971854, 0.0142088, 0.00804301, 
    0.00738241, 0.00886848, 0.0110073, 0.0153013, 0.00707248, 0.00687095, 0.00748131, 0.00786448, 0.00807527, 0.0109018, 
    0.00802808, 0.00969381, 0.0106283, 0.0147, 0.0214674, 0.0323, 0.0576 };
  int p8810_d16x1y1_numpoints = 26;
  p8810_d16x1y1 = TGraphAsymmErrors(p8810_d16x1y1_numpoints, p8810_d16x1y1_xval, p8810_d16x1y1_yval, p8810_d16x1y1_xerrminus, p8810_d16x1y1_xerrplus, p8810_d16x1y1_yerrminus, p8810_d16x1y1_yerrplus);
  p8810_d16x1y1.SetName("/HepData/8810/d16x1y1");
  p8810_d16x1y1.SetTitle("/HepData/8810/d16x1y1");
  p8810_d16x1y1.Draw("AP");

  
  TFile *file_2 = new TFile("/home/suman/RooUnfold/Final/Unfolded_2016_Data_NTuple_MC_P8_Legacy_new_excor.root","read");
  
  TH1D *h_AK5_svd = (TH1D*)file_2->Get("svd_unfold_ak5_Etabin4");
  TH1D *h_AK7_svd = (TH1D*)file_2->Get("svd_unfold_ak7_Etabin4");
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
	  my_rad_err_up[kl] = max(rad_dem_exp_up[irad][3][kl],rad_dem_exp_dn[irad][0][kl]);
	  my_rad_err_dn[kl] = max(rad_dem_exp_up[irad][3][kl],rad_dem_exp_dn[irad][0][kl]);

	  my_rad_err_up[kl] = sqrt(pow(my_rad_err_up[kl],2) + pow(rad_dem_stat_up[irad][0][kl],2));
	  my_rad_err_dn[kl] = sqrt(pow(my_rad_err_dn[kl],2) + pow(rad_dem_stat_dn[irad][0][kl],2));
	 
// 	  cout<<kl+1<<" up "<<my_rad_err_up[kl]<<" down "<<my_rad_err_dn[kl]<<endl;
 /*
	  if(kl==3){
		  my_rad_err_up[kl] *= 1.75;
		  my_rad_err_dn[kl] *= 1.75;
		  }
	  
	  if(kl==4){
                  my_rad_err_up[kl] *= 1.5;
                  my_rad_err_dn[kl] *= 1.5;
                  }
*/
      }

	for(int kl=0; kl<(noptbins+1); kl++){

      if(kl==0) { my_rad_err_up[kl]  = my_rad_err_up[kl+1];  my_rad_err_dn[kl]  = my_rad_err_dn[kl+1];   }
      cout<<"pt "<<kl+1<<" err "<<my_rad_err_up[kl]<<endl;
   
	  my_ak7_ak5_rat[kl] = h_rat_AK5byAK7_svd->GetBinContent(kl+1);
	  my_gr_ak7_ak5->SetPoint(kl,h_rat_AK5byAK7_svd->GetBinCenter(kl+1),my_ak7_ak5_rat[kl]);
	  my_gr_ak7_ak5->SetPointEYhigh(kl,my_rad_err_up[kl]);
	  my_gr_ak7_ak5->SetPointEYlow(kl,my_rad_err_dn[kl]);
  }
  
  my_gr_ak7_ak5->SetLineColor(kRed);
  my_gr_ak7_ak5->SetMarkerColor(kRed);
  my_gr_ak7_ak5->SetMarkerStyle(kFullTriangleUp);
  p8810_d16x1y1.SetMarkerStyle(kFullTriangleDown);
 
  
  TCanvas *c1 = new TCanvas("c1","c1",50,50,800,600);
  TLegend *leg1 = new TLegend(0.15,0.7,0.375,0.875);
  leg1->SetTextFont(42); leg1->SetBorderSize(0);
  c1->cd();
  gPad->SetLogx(1);
  
  p8810_d16x1y1.GetXaxis()->SetRangeUser(85,1588);
  p8810_d16x1y1.GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  p8810_d16x1y1.GetXaxis()->CenterTitle();
  p8810_d16x1y1.GetYaxis()->SetTitle("#sigma (AK5) / #sigma (AK7)");
  p8810_d16x1y1.GetYaxis()->CenterTitle();
  
  p8810_d16x1y1.Draw("AP");
//  h_rat_AK5byAK7_svd->Draw("sames");
  my_gr_ak7_ak5->Draw("P,sames");

  leg1->AddEntry(&p8810_d16x1y1,"SMP-13-002","lpe");
  leg1->AddEntry(my_gr_ak7_ak5,"SMP-19-003","lpe");
  leg1->Draw();
  c1->SaveAs("Crosscheck_AK5AK7_y4.pdf");

  
}

int main()
{
Compare_AK5AK7_y4();
}
