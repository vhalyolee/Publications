void PlotEffVsCtau(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);

  const int nctau = 15;
  const int ntrigs = 5;

  const char *label[nctau] = {"10", "20", "40", "50", "100", "150", "200", "250", "300",
			      "350", "400", "450", "500", "550", "600"};
  TH1F *h[ntrigs];
  const char *trignames[ntrigs] = {"Any displaced L1",
				   "Any L1",
				   "Any displaced HLT",
				   "Any HLT",
				   "Best single HLT"};

  char buf[512];
  for (int i=0; i<ntrigs; i++) {
    sprintf(buf, "h%d", i);
    h[i] = new TH1F(buf, trignames[i], nctau, -0.5, (float)nctau-0.5);
    for (int j=0; j<nctau; j++)
      h[i]->GetXaxis()->SetBinLabel(j+1, label[j]);
  };

  // efficiency vs. ctau, mH=125, mX=20
  float eff_all[nctau][ntrigs] = {
    {15.5, 88.8, 0.9, 4.1, 0.6}, // ctau=10
    {15.5, 86.8, 0.9, 3.7, 0.7}, // ctau=20
    {15.7, 86.2, 1.0, 3.6, 0.8}, // ctau=40
    {14.6, 85.9, 0.7, 3.2, 0.5}, // ctau=50
    {15.0, 85.1, 0.7, 3.9, 0.6}, // ctau=100
    {13.8, 82.9, 0.5, 3.9, 0.4}, // ctau=150
    {12.9, 81.3, 0.5, 4.4, 0.4}, // ctau=200
    {12.2, 79.3, 0.6, 4.6, 0.5}, // ctau=250
    {11.4, 77.0, 0.4, 4.9, 0.3}, // ctau=300
    {10.3, 75.0, 0.4, 4.9, 0.4}, // ctau=350
    {10.2, 73.6, 0.3, 4.8, 0.3}, // ctau=400
    {9.7, 71.5, 0.3, 5.3, 0.3}, // ctau=450
    {9.1, 69.5, 0.2, 5.2, 0.2}, // ctau=500
    {8.8, 68.6, 0.2, 5.0, 0.1}, // ctau=550
    {8.2, 67.0, 0.2, 5.4, 0.1}, // ctau=600
  };

  // uncertainty on efficiency
  float efferr_all[nctau][ntrigs] = {
    {0.4, 0.3, 0.1, 0.2, 0.1}, // ctau=10
    {0.4, 0.3, 0.1, 0.2, 0.1}, // ctau=20
    {0.4, 0.3, 0.1, 0.2, 0.1}, // ctau=40
    {0.4, 0.3, 0.1, 0.2, 0.1}, // ctau=50
    {0.4, 0.4, 0.1, 0.2, 0.1}, // ctau=100
    {0.3, 0.4, 0.1, 0.2, 0.1}, // ctau=150
    {0.3, 0.4, 0.1, 0.2, 0.1}, // ctau=200
    {0.3, 0.4, 0.1, 0.2, 0.1}, // ctau=250
    {0.3, 0.4, 0.1, 0.2, 0.1}, // ctau=300
    {0.3, 0.4, 0.1, 0.2, 0.1}, // ctau=350
    {0.3, 0.4, 0.1, 0.2, 0.1}, // ctau=400
    {0.3, 0.5, 0.1, 0.2, 0.1}, // ctau=450
    {0.3, 0.5, 0.0, 0.2, 0.0}, // ctau=500
    {0.3, 0.5, 0.0, 0.2, 0.0}, // ctau=550
    {0.3, 0.5, 0.0, 0.2, 0.0}, // ctau=600
  };
  
  const int colors[ntrigs] = {kBlue, kBlue, kBlack, kBlack, kBlack};
  const int markers[ntrigs] = {kOpenCircle, kFullCircle, kOpenCircle, kFullCircle, kPlus};

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

  c1 = new TCanvas("c1", "Efficiencies", 1000, 500);
  c1->Divide(2,1);
  c1->cd(1);
  gPad->SetLeftMargin(0.12);
  h[0]->SetTitle("Efficiency vs. c#tau, m_{H} = 125, m_{X} = 20");
  h[0]->GetXaxis()->SetTitle("c#tau of sample (mm)");
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
  h[3]->GetXaxis()->SetTitle("c#tau of sample (mm)");
  h[3]->GetYaxis()->SetTitle("Trigger efficiency (%)");
  h[3]->GetYaxis()->SetTitleOffset(1.23);
  h[3]->SetMinimum(0);
  h[3]->SetTitle("Detail view of HLT efficiency");

  h[3]->Draw("LPEX0");
  h[2]->Draw("LPEX0 same");
  h[4]->Draw("LPEX0 same");

  TLegend *l = new TLegend(0.50, 0.37, 0.88, 0.48);
  l->SetFillColor(0);
  l->SetBorderSize(0);
  for (int i=2; i<ntrigs; i++) {
    l->AddEntry(h[i], trignames[i]);
  }
  l->Draw();

  c1->Print("TriggerEffVsCtau.png");
}
