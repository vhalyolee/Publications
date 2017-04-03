void PlotSampleResults(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleFillColor(0);

  TFile *f1 = new TFile("outfile_400X50.root");
  TProfile *h11 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v4");
  TProfile *h21 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_L2TripleMu10_0_0_NoVertex_PFJet40Neutral_v4");
  TProfile *h31 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v3");
  TProfile *h41 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_HT300_DoubleDisplacedPFJet60_v5");
  TProfile *h51 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v2");

  TCanvas *c1 = new TCanvas("plots1", "Plots 1", 800, 600);

  h11->Draw();
  h11->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  h11->GetYaxis()->SetTitle("Efficiency");
  h11->SetLineColor(kBlack);
  h21->Draw("same");
  h21->SetLineColor(kRed);
  h31->Draw("same");
  h31->SetLineColor(kBlue);
  //h41->Draw("same");
  //h41->SetLineColor(33);
  //h51->Draw("same");
  //h51->SetLineColor(9);

  TLegend *l1 = new TLegend(0.5, 0.5, 0.88, 0.8);
  l1->AddEntry(h11, "2 disp. #mu + 2 disp. jet");
  l1->AddEntry(h21, "3 L2 #mu + 1 disp. jet");
  l1->AddEntry(h31, "1 muon + 2 b-tags");
  //l1->AddEntry(h41, "Disp. jet trigger (2 disp. jets)");
  //l1->AddEntry(h51, "Disp. muon trigger (2 L2 muons)");
  l1->SetFillColor(0);
  l1->Draw();
  
  TProfile *h12 = (TProfile*)f1->Get("trigEffVsLxy2X_HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v4");
  TProfile *h22 = (TProfile*)f1->Get("trigEffVsLxy2X_HLT_L2TripleMu10_0_0_NoVertex_PFJet40Neutral_v4");
  TProfile *h32 = (TProfile*)f1->Get("trigEffVsLxy2X_HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v3");
  TProfile *h42 = (TProfile*)f1->Get("trigEffVsLxy2X_HLT_HT300_DoubleDisplacedPFJet60_v5");
  TProfile *h52 = (TProfile*)f1->Get("trigEffVsLxy2X_HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v2");

  TCanvas *c2 = new TCanvas("plots2", "Plots 2", 800, 600);

  h12->Draw();
  h12->GetXaxis()->SetTitle("Generator-level L_{xy} of both X");
  h12->GetYaxis()->SetTitle("Efficiency");
  h12->SetLineColor(kBlack);
  h22->Draw("same");
  h22->SetLineColor(kRed);
  h32->Draw("same");
  h32->SetLineColor(kBlue);
  //h42->Draw("same");
  //h42->SetLineColor(33);
  //h52->Draw("same");
  //h52->SetLineColor(9);

  TLegend *l2 = new TLegend(0.5, 0.5, 0.88, 0.8);
  l2->AddEntry(h12, "2 disp. #mu + 2 disp. jet");
  l2->AddEntry(h22, "3 L2 #mu + 1 disp. jet");
  l2->AddEntry(h32, "1 muon + 2 b-tags");
  //l2->AddEntry(h42, "Disp. jet trigger (2 disp. jets)");
  //l2->AddEntry(h52, "Disp. muon trigger (2 L2 muons)");
  l2->SetFillColor(0);
  l2->Draw();

  c1->Print("TriggerEfficiency1X400X50.png");
  c2->Print("TriggerEfficiency2X400X50.png");
}
