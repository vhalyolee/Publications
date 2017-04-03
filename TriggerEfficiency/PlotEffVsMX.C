void PlotEffVsMX(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);

  const int nmx = 6;
  const int ntrigs = 5;

  // efficiency vs. mx, mH = 125, ctau = 40 mm
  float eff_all[nmx][ntrigs] = {
    {10.0, 91.9, 1.3, 5.7, 0.8}, // mx=10
    {15.7, 86.2, 1.0, 3.6, 0.8}, // mx=20
    {12.8, 83.2, 0.8, 3.2, 0.6}, // mx=30
    {12.1, 80.6, 0.5, 3.2, 0.4}, // mx=40
    {12.2, 76.4, 0.6, 4.0, 0.4}, // mx=50
    {16.6, 78.8, 0.7, 5.8, 0.4}, // mx=60
  };

  // uncertainty on efficiency
  float efferr_all[nmx][ntrigs] = {
    {0.3, 0.3, 0.1, 0.2, 0.1}, // mx=10
    {0.4, 0.3, 0.1, 0.2, 0.1}, // mx=20
    {0.3, 0.4, 0.1, 0.2, 0.1}, // mx=30
    {0.3, 0.4, 0.1, 0.2, 0.1}, // mx=40
    {0.3, 0.4, 0.1, 0.2, 0.1}, // mx=50
    {0.4, 0.4, 0.1, 0.2, 0.1}, // mx=60
  };

  const char *label[nmx] = {"10", "20", "30", "40", "50", "60"};
  TH1F *h[ntrigs];
  const char *trignames[ntrigs] = {"Any displaced L1",
				   "Any L1",
				   "Any displaced HLT",
				   "Any HLT",
				   "Best single HLT"};

  char buf[512];
  for (int i=0; i<ntrigs; i++) {
    sprintf(buf, "h%d", i);
    h[i] = new TH1F(buf, trignames[i], nmx, -0.5, (float)nmx-0.5);
    for (int j=0; j<nmx; j++)
      h[i]->GetXaxis()->SetBinLabel(j+1, label[j]);
  };
  
  const int colors[ntrigs] = {kBlue, kBlue, kBlack, kBlack, kBlack};
  const int markers[ntrigs] = {kOpenCircle, kFullCircle, kOpenCircle, kFullCircle, kPlus};

  for (int i=0; i<ntrigs; i++) {
    h[i]->SetLineColor(colors[i]);
    h[i]->SetMarkerColor(colors[i]);
    h[i]->SetMarkerStyle(markers[i]);
  }

  for (int i=0; i<nmx; i++) {
    for (int j=0; j<ntrigs; j++) {
      h[j]->Fill(i, eff_all[i][j]);
      h[j]->SetBinError(i+1, efferr_all[i][j]);
    }
  }

  c1 = new TCanvas("c1", "Efficiencies", 1000, 500);
  c1->Divide(2,1);
  c1->cd(1);
  gPad->SetLeftMargin(0.12);
  h[0]->SetTitle("Efficiency vs. m_{X}, m_{H} = 125, c#tau = 40mm");
  h[0]->GetXaxis()->SetTitle("m_{X} (GeV/c^{2})");
  h[0]->GetXaxis()->SetTitleColor(kBlack);
  h[0]->GetYaxis()->SetTitle("Trigger efficiency (%)");
  h[0]->GetYaxis()->SetTitleOffset(1.23);
  h[0]->SetMinimum(0);
  //h[0]->SetMaximum(18);
  h[0]->SetMaximum(100);
  
  h[0]->Draw("LPEX0");
  for (int i=1; i<ntrigs; i++)
    h[i]->Draw("LPEX0 same");
  
  TLegend *l = new TLegend(0.50, 0.42, 0.88, 0.63);
  l->SetFillColor(0);
  l->SetBorderSize(0);
  for (int i=0; i<ntrigs; i++) {
    l->AddEntry(h[i], trignames[i]);
  }
  l->Draw();

  c1->cd(2);
  gPad->SetLeftMargin(0.12);
  h[3]->GetXaxis()->SetTitle("m_{X} of sample (GeV/c^{2})");
  h[3]->GetYaxis()->SetTitle("Trigger efficiency (%)");
  h[3]->GetYaxis()->SetTitleOffset(1.23);
  h[3]->SetMinimum(0);
  h[3]->SetTitle("Detail view of HLT efficiency");

  h[3]->Draw("LPEX0");
  h[2]->Draw("LPEX0 same");
  h[4]->Draw("LPEX0 same");

  TLegend *l = new TLegend(0.50, 0.32, 0.88, 0.43);
  l->SetFillColor(0);
  l->SetBorderSize(0);
  for (int i=2; i<ntrigs; i++) {
    l->AddEntry(h[i], trignames[i]);
  }
  l->Draw();

  c1->Print("TriggerEffVsMX.png");
}
