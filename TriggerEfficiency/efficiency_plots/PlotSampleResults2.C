void PlotSampleResults2(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleFillColor(0);

  TFile *f1 = new TFile("outfile_125X50.root");
  TProfile *h11 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v4");
  TProfile *h21 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_L2TripleMu10_0_0_NoVertex_PFJet40Neutral_v4");
  TProfile *h31 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v3");
  TProfile *h41 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_HT300_DoubleDisplacedPFJet60_v5");
  TProfile *h51 = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v2");
  h11->Scale(100.0);
  h21->Scale(100.0);
  h31->Scale(100.0);
  h41->Scale(100.0);
  h51->Scale(100.0);
  
  TCanvas *c1 = new TCanvas("plots1", "Plots 1", 800, 600);

  h11->Draw();
  h11->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  h11->GetYaxis()->SetTitle("Efficiency (%)");
  h11->SetLineColor(kBlack);
  h21->Draw("same");
  h21->SetLineColor(kRed);
  h31->Draw("same");
  h31->SetLineColor(kBlue);
  h41->Draw("same");
  h41->SetLineColor(kGreen);
  //h51->Draw("same");
  //h51->SetLineColor(9);

  TLegend *l1 = new TLegend(0.5, 0.5, 0.88, 0.8);
  l1->AddEntry(h11, "2 disp. #mu + 2 disp. jet");
  l1->AddEntry(h21, "3 L2 #mu + 1 disp. jet");
  l1->AddEntry(h31, "1 muon + 2 b-tags");
  l1->AddEntry(h41, "Disp. jet trigger (2 disp. jets)");
  //l1->AddEntry(h51, "Disp. muon trigger (2 L2 muons)");
  l1->SetFillColor(0);
  l1->Draw();

  c1->Print("TriggerEfficiency1X125X50.png");
}
