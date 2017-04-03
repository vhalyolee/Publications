void PlotTrigger(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleFillColor(0);

  TFile *f1 = new TFile("outfile_4B_H125X50.root");
  TProfile *htrig = (TProfile*)f1->Get("allTriggerEfficiency");

  TCanvas *c1 = new TCanvas("plots1", "Plots 1", 2400, 300);
  gPad->SetBottomMargin(0.6);
  for (int i=1; i<=htrig->GetXaxis()->GetNbins(); i++) {
    printf("%.04f %s\n", htrig->GetBinContent(i), htrig->GetXaxis()->GetBinLabel(i));
  }
  htrig->Draw();
  c1->Print("TriggersTest.png");
}
