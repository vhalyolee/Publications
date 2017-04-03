void PlotEverything(int whichSample = 0) {
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleFillColor(0);

  const char *id[12] = {"H1000X150", "H1000X20", "H1000X350", "H1000X50",
			"H125X20", "H125X50", "H200X20", "H200X50",
			"H300X125", "H400X150", "H400X20", "H400X50"};
  const char *title[12] = {"Trigger efficiency, m_{H} = 1000 GeV/c^{2}, m_{X} = 150 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 1000 GeV/c^{2}, m_{X} = 20 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 1000 GeV/c^{2}, m_{X} = 350 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 1000 GeV/c^{2}, m_{X} = 50 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 125 GeV/c^{2}, m_{X} = 20 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 125 GeV/c^{2}, m_{X} = 50 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 200 GeV/c^{2}, m_{X} = 20 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 200 GeV/c^{2}, m_{X} = 50 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 300 GeV/c^{2}, m_{X} = 125 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 400 GeV/c^{2}, m_{X} = 150 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 400 GeV/c^{2}, m_{X} = 20 GeV/c^{2}",
			   "Trigger efficiency, m_{H} = 400 GeV/c^{2}, m_{X} = 50 GeV/c^{2}"};
  char buf[512];

  const int nTrigs = 7;
  const char *L1Trigs[nTrigs] = {"AnyDisplacedTriggerL1", "L1_DoubleMu_10_3p5", "L1_DoubleMu0_HighQ_EtaCuts",
				 "L1_TripleMu0", "L1_HTT150", "L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12", "AnyTriggerL1"};
  const char *HLTrigs[nTrigs] = {"AnyDisplacedTriggerHLT", "HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v2",
				 "HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v4", "HLT_L2TripleMu10_0_0_NoVertex_PFJet40Neutral_v4",
				 "HLT_HT300_DoubleDisplacedPFJet60_v5", "HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v3",
				 "AnyTriggerHLT"};
  const char *label[nTrigs] = {"For any displaced trigger:", "Two L2 muons pt>23:",
			       "Two displaced muons pt>4 + two displaced jets:", "Three L2 muons and one displaced jet:",
			       "Two displaced jets pt>60:", "Muon + two b-tagged jets:", "Any trigger:"};

  sprintf(buf, "outfile_4B_%s.root", id[whichSample]);
  TFile *f1 = new TFile(buf);

  TH1F *dummy = new TH1F("dummy", "dummy", 5, 0, 5);
  dummy->SetLineColor(0);
  dummy->SetFillColor(0);
  dummy->SetMarkerColor(0);
  
  for (int i=0; i<nTrigs; i++) {
    sprintf(buf, "c%d", i);
    TCanvas *c = new TCanvas(buf, buf, 800, 600);
    sprintf(buf, "trigEffVsLxy1X_%s", L1Trigs[i]);
    TProfile *h1L1 = (TProfile*)f1->Get(buf);
    sprintf(buf, "trigEffVsLxy1X_%s", HLTrigs[i]);
    TProfile *h1HLT = (TProfile*)f1->Get(buf);
    sprintf(buf, "L1PassTrigEffVsLxy1X_%s", HLTrigs[i]);
    TProfile *h1HLTPassL1 = (TProfile*)f1->Get(buf);

    h1L1->Scale(100.0);
    h1HLT->Scale(100.0);
    h1HLTPassL1->Scale(100.0);

    h1L1->SetTitle(title[whichSample]);
    h1L1->Draw();
    float ymax = 1.5*h1L1->GetMaximum();
    if (1.5*h1HLTPassL1->GetMaximum() > ymax)
      ymax = 1.5*h1HLTPassL1->GetMaximum();
    h1L1->SetMaximum(ymax);
    h1L1->SetMinimum(0.0);
    h1L1->GetXaxis()->SetTitle("Generator-level L_{xy} of either X");
    h1L1->GetYaxis()->SetTitle("Efficiency (%)");
    h1L1->SetLineColor(kBlack);
    h1L1->SetMarkerColor(kBlack);
    h1HLT->Draw("same");
    h1HLT->SetLineColor(kRed);
    h1HLT->SetMarkerColor(kRed);
    h1HLTPassL1->Draw("same");
    h1HLTPassL1->SetLineColor(kBlue);
    h1HLTPassL1->SetMarkerColor(kBlue);

    if (i==0) {
      TProfile *h1All = (TProfile*)f1->Get("trigEffVsLxy1X_AnyTriggerHLT");
      TProfile *dupe1 = h1All->Clone("dupe1");
      dupe1->Scale(100.0);
      dupe1->SetLineColor(kGreen);
      dupe1->SetMarkerColor(kGreen);
      dupe1->Draw("same");
    }
    
    TLegend *l1 = new TLegend(0.4, 0.65, 0.88, 0.85);
    if (i==0) {
      l1->AddEntry(dupe1, "Efficiency for any HLT trigger");
    }
    l1->AddEntry(dummy, label[i]);
    l1->AddEntry(h1L1, "Efficiency to pass L1");
    l1->AddEntry(h1HLTPassL1, "Efficiency to pass HLT given passing L1");
    l1->AddEntry(h1HLT, "Efficiency to pass L1 and HLT");
    l1->SetFillColor(0);
    l1->Draw();

    if (i==0) {
      sprintf(buf, "TriggerEfficiency_%s.pdf(", id[whichSample]);
      c->Print(buf);
    } else if (i==nTrigs-1) {
      sprintf(buf, "TriggerEfficiency_%s.pdf)", id[whichSample]);
      c->Print(buf);
    } else {
      sprintf(buf, "TriggerEfficiency_%s.pdf", id[whichSample]);
      c->Print(buf);
    }
  }

}
