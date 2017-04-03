void PlotMoreResults(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleFillColor(0);

  TFile *f1 = new TFile("outfile_125X50.root");
  TProfile *hLxy1 = (TProfile*)f1->Get("Lxy1X");
  TProfile *hLxyM = (TProfile*)f1->Get("LxyMinX");

  TCanvas *c1 = new TCanvas("plots1", "Plots 1", 1200, 500);
  c1->Divide(2,1);
  c1->cd(1);
  hLxy1->Draw();
  hLxy1->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  hLxy1->GetYaxis()->SetTitle("Number of events");
  c1->cd(2);
  hLxyM->Draw();
  hLxyM->GetXaxis()->SetTitle("Minimum generator-level L_{xy} of two Xs");
  hLxyM->GetYaxis()->SetTitle("Number of events");

  c1->Print("LxyDistributions.png");
  return;
  
  TProfile *h1Disp = (TProfile*)f1->Get("trigEffVsLxy1X_AnyDisplacedHLTTrigger");
  TProfile *h1Any = (TProfile*)f1->Get("trigEffVsLxy1X_AnyHLTTrigger");
  TProfile *hMDisp = (TProfile*)f1->Get("trigEffVsLxyMinX_AnyDisplacedHLTTrigger");
  TProfile *hMAny = (TProfile*)f1->Get("trigEffVsLxyMinX_AnyHLTTrigger");

  TCanvas *c2 = new TCanvas("plots2", "Plots 2", 1200, 500);
  c2->Divide(2,1);
  c2->cd(1);
  h1Any->Draw();
  h1Any->SetMinimum(0.0);
  h1Any->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  h1Any->GetYaxis()->SetTitle("Efficiency");
  h1Any->SetLineColor(kBlack);
  h1Disp->Draw("same");
  h1Disp->SetLineColor(kRed);

  TLegend *l11 = new TLegend(0.5, 0.5, 0.88, 0.8);
  l11->AddEntry(h1Disp, "Any displaced trigger");
  l11->AddEntry(h1Any, "Any unprescaled trigger");
  l11->SetFillColor(0);
  l11->Draw();
 
  c2->cd(2);
  hMAny->Draw();
  hMAny->SetMinimum(0.0);
  hMAny->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  hMAny->GetYaxis()->SetTitle("Efficiency");
  hMAny->SetLineColor(kBlack);
  hMDisp->Draw("same");
  hMDisp->SetLineColor(kRed);

  TLegend *lM1 = new TLegend(0.5, 0.5, 0.88, 0.8);
  lM1->AddEntry(hMDisp, "Any displaced trigger");
  lM1->AddEntry(hMAny, "Any unprescaled trigger");
  lM1->SetFillColor(0);
  lM1->Draw();

  // L1

  TProfile *h1L11 = (TProfile*)f1->Get("trigEffVsLxy1X_L1_DoubleMu_10_3p5");
  TProfile *h1L12 = (TProfile*)f1->Get("trigEffVsLxy1X_L1_DoubleMu0_HighQ_EtaCuts");
  TProfile *h1L13 = (TProfile*)f1->Get("trigEffVsLxy1X_L1_TripleMu0");
  TProfile *h1L14 = (TProfile*)f1->Get("trigEffVsLxy1X_L1_HTT150");

  TProfile *hML11 = (TProfile*)f1->Get("trigEffVsLxyMinX_L1_DoubleMu_10_3p5");
  TProfile *hML12 = (TProfile*)f1->Get("trigEffVsLxyMinX_L1_DoubleMu0_HighQ_EtaCuts");
  TProfile *hML13 = (TProfile*)f1->Get("trigEffVsLxyMinX_L1_TripleMu0");
  TProfile *hML14 = (TProfile*)f1->Get("trigEffVsLxyMinX_L1_HTT150");

  TCanvas *c3 = new TCanvas("plots3", "Plots 3", 1200, 500);
  c3->Divide(2,1);
  c3->cd(1);
  h1L11->SetMaximum(1.0);
  h1L11->SetMinimum(0.0);
  h1L11->Draw();
  h1L11->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
  h1L11->GetYaxis()->SetTitle("Efficiency");
  h1L11->SetLineColor(kBlack);
  h1L12->Draw("same");
  h1L12->SetLineColor(kRed);
  h1L13->Draw("same");
  h1L13->SetLineColor(kBlue);
  h1L14->Draw("same");
  h1L14->SetLineColor(kGreen);

  TLegend *l12 = new TLegend(0.5, 0.5, 0.88, 0.8);
  l12->AddEntry(h1L11, "L1_DoubleMu_10_3p5");
  l12->AddEntry(h1L12, "L1_DoubleMu0er_HighQ");
  l12->AddEntry(h1L13, "L1_TripleMu0");
  l12->AddEntry(h1L14, "L1_HTT150");
  l12->SetFillColor(0);
  l12->Draw();
 
  c3->cd(2);
  hML11->SetMaximum(1.0);
  hML11->SetMinimum(0.0);
  hML11->Draw();
  hML11->GetXaxis()->SetTitle("Minimum generator-level L_{xy} of two Xs");
  hML11->GetYaxis()->SetTitle("Efficiency");
  hML11->SetLineColor(kBlack);
  hML12->Draw("same");
  hML12->SetLineColor(kRed);
  hML13->Draw("same");
  hML13->SetLineColor(kBlue);
  hML14->Draw("same");
  hML14->SetLineColor(kGreen);

  TLegend *lM2 = new TLegend(0.5, 0.5, 0.88, 0.8);
  lM2->AddEntry(hML11, "L1_DoubleMu_10_3p5");
  lM2->AddEntry(hML12, "L1_DoubleMu0er_HighQ");
  lM2->AddEntry(hML13, "L1_TripleMu0");
  lM2->AddEntry(hML14, "L1_HTT150");
  lM2->SetFillColor(0);
  lM2->Draw();

  c1->Print("LxyDistributions.png");
  c2->Print("EfficiencyHLT.png");
  c3->Print("EfficiencyL1.png");
}
