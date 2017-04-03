void PlotEffL1TrigSim(void) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);

  const int nctau = 12;
  const int ntrigs = 4;

  const char *label[nctau] = {"50", "100", "150", "200", "250", "300",
			      "350", "400", "450", "500", "550", "600"};
  TH1F *h[ntrigs];
  const char *trignames[ntrigs] = {"Actual efficiency, m_{H}=125", "Simulated efficiency, m_{H}=125",
				   "Actual efficiency, m_{H}=400", "Simulated efficiency, m_{H}=400"};

  char buf[512];
  for (int i=0; i<ntrigs; i++) {
    sprintf(buf, "h%d", i);
    h[i] = new TH1F(buf, trignames[i], nctau, -0.5, (float)nctau-0.5);
    for (int j=0; j<nctau; j++)
      h[i]->GetXaxis()->SetBinLabel(j+1, label[j]);
  };

  // efficiency vs. ctau (mX=20)
  // first try, no correction for jets out of calorimeter
//   float eff_all[nctau][ntrigs] = {
//     {42.8,42.2,97.3,95.3},
//     {44.5,41.9,92.9,96.7},
//     {43.4,40.5,91.0,96.3},
//     {43.5,41.1,85.1,96.6},
//     {43.2,42.7,81.3,96.3},
//     {42.2,40.9,78.3,96.1},
//     {41.7,41.3,75.9,96.1},
//     {40.4,42.3,73.3,95.4},
//     {39.2,41.5,73.2,95.7},
//     {38.2,40.9,70.1,95.3},
//     {37.9,40.5,69.6,96.3},
//     {37.0,40.9,71.9,94.4},
//   };
  // second try, corrected for jets leaving calo but no MET correction
//   float eff_all[nctau][ntrigs] = {
//     {42.8,53.0,97.3,95.6},
//     {44.5,53.0,92.9,96.2},
//     {43.4,50.9,91.0,94.7},
//     {43.5,50.3,85.1,92.3},
//     {43.2,50.2,81.3,88.6},
//     {42.2,47.3,78.3,84.7},
//     {41.7,45.8,75.9,81.3},
//     {40.4,44.1,73.3,81.3},
//     {39.2,41.6,73.2,79.6},
//     {38.2,39.7,70.1,76.0},
//     {37.9,38.0,69.6,75.9},
//     {37.0,37.3,71.9,76.3},
//   };
  // third try, includes correction to MET
  float eff_all[nctau][ntrigs] = {
    {42.8,52.6,97.3,95.4},
    {44.5,52.2,92.9,94.0},
    {43.4,48.8,91.0,92.0},
    {43.5,46.8,85.1,86.2},
    {43.2,45.7,81.3,82.1},
    {42.2,42.1,78.3,79.4},
    {41.7,40.7,75.9,76.8},
    {40.4,39.0,73.3,75.0},
    {39.2,36.4,73.2,74.1},
    {38.2,35.5,70.1,72.0},
    {37.9,34.0,69.6,71.0},
    {37.0,33.6,71.9,73.2},
  };

  // uncertainty on efficiency
  float efferr_all[nctau][ntrigs] = {
    {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0},
  };
  
  const int colors[ntrigs] = {kBlue, kRed, kBlue, kRed};
  const int markers[ntrigs] = {kFullCircle, kFullCircle, kOpenCircle, kOpenCircle};

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
  h[0]->SetTitle("Efficiency vs. c#tau, m_{X} = 20");
  h[0]->GetXaxis()->SetTitle("c#tau of sample (mm)");
  h[0]->GetXaxis()->SetTitleColor(kBlack);
  h[0]->GetYaxis()->SetTitle("Trigger efficiency (%)");
  h[0]->GetYaxis()->SetTitleOffset(1.23);
  h[0]->SetMinimum(30);
  h[0]->SetMaximum(100);
  
  h[0]->Draw("LPEX0");
  for (int i=1; i<ntrigs; i++)
    h[i]->Draw("LPEX0 same");
  
  TLegend *l = new TLegend(0.17, 0.37, 0.55, 0.58);
  l->SetFillColor(0);
  l->SetBorderSize(0);
  for (int i=0; i<ntrigs; i++) {
    l->AddEntry(h[i], trignames[i]);
  }
  l->Draw();
  c1->Print("L1TriggerSimNewest.png");
}
