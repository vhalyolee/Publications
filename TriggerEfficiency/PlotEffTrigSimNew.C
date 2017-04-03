void PlotEffTrigSimNew(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);

  const int nctau = 12;
  const int ntrigs = 2;

  const char *label[nctau] = {"50", "100", "150", "200", "250", "300",
			      "350", "400", "450", "500", "550", "600"};
  TH1F *h[ntrigs];
  const char *trignames[ntrigs] = {"Actual efficiency", "Simulated efficiency"};

  char buf[512];
  for (int i=0; i<ntrigs; i++) {
    sprintf(buf, "h%d", i);
    h[i] = new TH1F(buf, trignames[i], nctau, -0.5, (float)nctau-0.5);
    for (int j=0; j<nctau; j++)
      h[i]->GetXaxis()->SetBinLabel(j+1, label[j]);
  };

  // efficiency vs. ctau, mH=125, mX=20
  float eff_all[nctau][ntrigs] = {
    // First try with new method
    // {36.7, 48.6}, {24.9, 27.8}, {17.9, 18.4}, {10.8, 12.0}, {8.5, 6.6}, {8.7, 8.5},
    // {5.9, 6.4}, {6.0, 6.4}, {3.5, 3.2}, {4.7, 4.2}, {4.7, 3.0}, {2.9, 3.3}
    // Second try with new method (including loose prompt track cut)
    {36.7, 42.1}, {24.9, 26.6}, {17.9, 17.9}, {10.8, 12.3}, {8.5, 7.8}, {8.7, 8.6},
    {5.9, 5.7}, {6.0, 6.2}, {3.5, 3.5}, {4.7, 4.0}, {4.7, 3.7}, {2.9, 3.1}
    // Same but with prompt track cut of 7 instead
    // {36.7, 38.8}, {24.9, 24.5}, {17.9, 17.1}, {10.8, 10.2}, {8.5, 6.7}, {8.7, 7.9},
    // {5.9, 4.8}, {6.0, 6.0}, {3.5, 3.2}, {4.7, 3.2}, {4.7, 3.0}, {2.9, 2.6}
  };

  // uncertainty on efficiency
  float efferr_all[nctau][ntrigs] = {
    {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0},
    {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0},
    {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0},
  };
  
  const int colors[ntrigs] = {kBlue, kRed};
  const int markers[ntrigs] = {kFullCircle, kFullCircle};

  for (int i=0; i<ntrigs; i++) {
    h[i]->SetLineColor(colors[i]);
    h[i]->SetMarkerColor(colors[i]);
    h[i]->SetMarkerStyle(markers[i]);
  }

  for (int i=0; i<nctau; i++) {
    for (int j=0; j<ntrigs; j++) {
      h[j]->Fill(i, eff_all[i][j]);
      h[j]->SetBinError(i+1, efferr_all[i][j]);
    }
  }

  c1 = new TCanvas("c1", "Efficiencies", 500, 500);
  gPad->SetLeftMargin(0.12);
  h[0]->SetTitle("Efficiency vs. c#tau, m_{H} = 400, m_{X} = 20");
  h[0]->GetXaxis()->SetTitle("c#tau of sample (mm)");
  h[0]->GetXaxis()->SetTitleColor(kBlack);
  h[0]->GetYaxis()->SetTitle("Trigger efficiency (%)");
  h[0]->GetYaxis()->SetTitleOffset(1.23);
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(50);
  
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
  c1->Print("TriggerSimNew8.png");
}
