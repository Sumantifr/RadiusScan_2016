void File_Write()
{
TFile *file = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Madgraph/NTuples_Files/Histograms_Madgraph_Summer_w50.root","read");

TFile *fileout = new TFile("Example_Data_MG.root","RECREATE");
TH1D *hist_reco, *hist_reco2;
//TH1D *hist_gen, *hist_gen2;
//TH2D *hist_recogen2d, *hist_recogen2d2;

//TFile *file = new TFile("/home/suman/CPlusPlus/CMS_Files/Jets_in_CMS/GenJets/Pythia/NTuples_Hist/Historam_P8_Noswap.root","read");
hist_reco2 = (TH1D*)file->Get("JetpT_ak4_EtaBin1");
//hist_gen2 = (TH1D*)file->Get("Gen_MC_JetpT_ak4_EtaBin1");
//hist_recogen2d2 = (TH2D*)file->Get("RecoJetvsGenJet_ak4_EtaBin1");

hist_reco = (TH1D*)hist_reco2->Clone();
//hist_gen = (TH1D*)hist_gen2->Clone();
//hist_recogen2d = (TH2D*)hist_recogen2d2->Clone();

fileout->cd();
fileout->Write();
fileout->Close();
}
