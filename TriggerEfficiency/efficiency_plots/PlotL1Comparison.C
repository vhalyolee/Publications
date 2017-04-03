void PlotL1Comparison(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleFillColor(0);

  TFile *f1 = new TFile("outfile_125X50.root");
  TCanvas *c1 = new TCanvas("plots1", "Plots 1", 1200, 800);
  c1->Divide(2,2);

  c1->cd(1);
  TProfile *h1L1 = (TProfile*)f1->Get("trigEffVsLxy1X_L1_DoubleMu_10_3p5");
  TProfile *h1HLT = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v2");
  
  h1L1->Draw();
  h1L1->SetMaximum(0.60);
  h1L1->SetMinimum(0.0);
  h1L1->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  h1L1->GetYaxis()->SetTitle("Efficiency");
  h1L1->SetLineColor(kBlack);
  h1HLT->Draw("same");
  h1HLT->SetLineColor(kRed);

  TLegend *l1 = new TLegend(0.4, 0.65, 0.88, 0.85);
  l1->AddEntry(h1L1, "Double muon L1 trigger");
  l1->AddEntry(h1HLT, "Double muon HLT trigger");
  l1->SetFillColor(0);
  l1->Draw();

  c1->cd(2);
  TProfile *h2L1 = (TProfile*)f1->Get("trigEffVsLxy1X_L1_DoubleMu0_HighQ_EtaCuts");
  TProfile *h2HLT = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v4");
  
  h2L1->Draw();
  h2L1->SetMaximum(0.80);
  h2L1->SetMinimum(0.0);
  h2L1->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  h2L1->GetYaxis()->SetTitle("Efficiency");
  h2L1->SetLineColor(kBlack);
  h2HLT->Draw("same");
  h2HLT->SetLineColor(kRed);

  TLegend *l2 = new TLegend(0.4, 0.65, 0.88, 0.85);
  l2->AddEntry(h2L1, "Double displaced muon+jet L1 trigger");
  l2->AddEntry(h2HLT, "Double displaced muon+jet HLT trigger");
  l2->SetFillColor(0);
  l2->Draw();

  c1->cd(3);
  TProfile *h3L1 = (TProfile*)f1->Get("trigEffVsLxy1X_L1_TripleMu0");
  TProfile *h3HLT = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_L2TripleMu10_0_0_NoVertex_PFJet40Neutral_v4");
  
  h3L1->Draw();
  h3L1->SetMaximum(0.25);
  h3L1->SetMinimum(0.0);
  h3L1->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  h3L1->GetYaxis()->SetTitle("Efficiency");
  h3L1->SetLineColor(kBlack);
  h3HLT->Draw("same");
  h3HLT->SetLineColor(kRed);

  TLegend *l3 = new TLegend(0.4, 0.65, 0.88, 0.85);
  l3->AddEntry(h3L1, "Triple muon L1 trigger");
  l3->AddEntry(h3HLT, "Triple muon HLT trigger");
  l3->SetFillColor(0);
  l3->Draw();

  c1->cd(4);
  TProfile *h4L1 = (TProfile*)f1->Get("trigEffVsLxy1X_L1_HTT150");
  TProfile *h4HLT = (TProfile*)f1->Get("trigEffVsLxy1X_HLT_HT300_DoubleDisplacedPFJet60_v5");
  
  h4L1->Draw();
  h4L1->SetMaximum(0.30);
  h4L1->SetMinimum(0.0);
  h4L1->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  h4L1->GetYaxis()->SetTitle("Efficiency");
  h4L1->SetLineColor(kBlack);
  h4HLT->Draw("same");
  h4HLT->SetLineColor(kRed);

  TLegend *l4 = new TLegend(0.4, 0.65, 0.88, 0.85);
  l4->AddEntry(h4L1, "Displaced jet L1 trigger (HT150)");
  l4->AddEntry(h4HLT, "Displaced jet HLT trigger");
  l4->SetFillColor(0);
  l4->Draw();

  c1->Print("L1AndHLTEfficiency_120X50.png");
}
