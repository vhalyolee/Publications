void PlotEffVsCtau(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);

  const int nbins = 5;
  const char *label[nbins] = {"10", "20", "40", "50", "100"};

  const int ntrigs = 8;
  TH1F *h[ntrigs];
  const char *trignames[ntrigs] = {"L1 2 mu",
				   "HLT 2 disp mu+2 jet",
				   "L1 triple mu",
				   "HLT triple mu+jet",
				   "Any displaced L1",
				   "Any L1",
				   "Any displaced HLT",
				   "Any HLT"};

  char buf[512];
  for (int i=0; i<ntrigs; i++) {
    sprintf(buf, "h%d", i);
    h[i] = new TH1F(buf, trignames[i], nbins, -0.5, (float)nbins-0.5);
    for (int j=0; j<nbins; j++)
      h[i]->GetXaxis()->SetBinLabel(j+1, label[j]);
  };
  
  float eff_all[nbins][ntrigs] = {{3.2, 0.1, 0.0, 0.0, 16.5, 90.1, 0.8, 4.0},
				  {4.4, 0.2, 0.6, 0.1, 14.7, 87.6, 1.1, 3.3},
				  {3.3, 0.1, 0.8, 0.0, 15.1, 86.7, 1.3, 4.3},
				  {4.6, 0.2, 0.7, 0.1, 15.7, 85.7, 1.6, 4.4},
				  {4.0, 0.2, 0.2, 0.0, 15.3, 85.7, 0.9, 4.3}
  };
  
  float efferr_all[nbins][ntrigs] = {{0.6, 0.1, 0.0, 0.0, 1.2, 0.9, 0.3, 0.6},
				     {0.6, 0.1, 0.2, 0.1, 1.1, 1.0, 0.3, 0.6},
				     {0.6, 0.1, 0.3, 0.0, 1.1, 1.1, 0.4, 0.6},
				     {0.7, 0.1, 0.3, 0.1, 1.2, 1.1, 0.4, 0.6},
				     {0.6, 0.1, 0.1, 0.0, 1.1, 1.1, 0.3, 0.6}
  };
  
  const int colors[ntrigs] = {kBlue, kBlue, kRed, kRed, kBlue, kBlack, kBlue, kBlack};
  const int markers[ntrigs] = {kOpenCircle, kFullCircle, kOpenCircle, kFullCircle, kOpenCircle, kOpenCircle, kFullCircle, kFullCircle};

  for (int i=0; i<ntrigs; i++) {
    h[i]->SetLineColor(colors[i]);
    h[i]->SetMarkerColor(colors[i]);
    h[i]->SetMarkerStyle(markers[i]);
  }

  for (int i=0; i<nbins; i++) {
    for (int j=0; j<ntrigs; j++) {
      h[j]->Fill(i, eff_all[i][j]);
      h[j]->SetBinError(i+1, efferr_all[i][j]);
    }
  }

  c1 = new TCanvas("c1", "Efficiencies", 1000, 500);
  c1->Divide(2,1);
  c1->cd(1);
  gPad->SetLeftMargin(0.12);
  h[4]->SetTitle("Efficiency vs. c#tau, m_{H} = 125, m_{X} = 20");
  h[4]->GetXaxis()->SetTitle("c#tau of sample (mm)");
  h[4]->GetXaxis()->SetTitleColor(kBlack);
  h[4]->GetYaxis()->SetTitle("Trigger efficiency (%)");
  h[4]->GetYaxis()->SetTitleOffset(1.23);
  h[4]->SetMinimum(0);
  //h[4]->SetMaximum(18);
  h[4]->SetMaximum(100);
  
  h[4]->Draw("LPEX0");
  for (int i=5; i<ntrigs; i++)
    h[i]->Draw("LPEX0 same");
  
  TLegend *l = new TLegend(0.50, 0.42, 0.88, 0.63);
  l->SetFillColor(0);
  l->SetBorderSize(0);
  for (int i=4; i<ntrigs; i++) {
    l->AddEntry(h[i], trignames[i]);
  }
  l->Draw();

  c1->cd(2);
  gPad->SetLeftMargin(0.12);
  h[7]->GetXaxis()->SetTitle("c#tau of sample (mm)");
  h[7]->GetYaxis()->SetTitle("Trigger efficiency (%)");
  h[7]->GetYaxis()->SetTitleOffset(1.23);
  h[7]->SetMinimum(0);
  h[7]->SetTitle("Detail view of HLT efficiency");

  h[7]->Draw("LPEX0");
  h[6]->Draw("LPEX0 same");

  TLegend *l = new TLegend(0.50, 0.47, 0.88, 0.58);
  l->SetFillColor(0);
  l->SetBorderSize(0);
  for (int i=6; i<ntrigs; i++) {
    l->AddEntry(h[i], trignames[i]);
  }
  l->Draw();

  c1->Print("TriggerEffVsCtau.png");
}
