{
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleFont(42, "");
  gStyle->SetTitleFont(42, "X");
  gStyle->SetTitleFont(42, "Y");
  gStyle->SetErrorX(0);

//=========Macro generated from canvas: c1/c1
//=========  (Sat Sep 21 22:34:25 2013) by ROOT version5.28/00h
   TCanvas *c1 = new TCanvas("c1", "c1",41,31,800,600);
   c1->Range(-1.25,0.6144232,6.25,1.042842);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   
   TProfile *k20c = new TProfile("k20c","Efficiency vs. tracks per jet",6,-0.5,5.5,"");
   k20c->SetBinEntries(1,2);
   k20c->SetBinEntries(2,2);
   k20c->SetBinEntries(3,2);
   k20c->SetBinEntries(4,2);
   k20c->SetBinEntries(5,2);
   k20c->SetBinEntries(6,2);
   k20c->SetBinContent(1,1.35);
   k20c->SetBinContent(2,1.433);
   k20c->SetBinContent(3,1.692);
   k20c->SetBinContent(4,1.735);
   k20c->SetBinContent(5,1.844);
   k20c->SetBinContent(6,1.854);
   k20c->SetBinError(1,0.9545983);
   k20c->SetBinError(2,1.013286);
   k20c->SetBinError(3,1.196478);
   k20c->SetBinError(4,1.226832);
   k20c->SetBinError(5,1.303912);
   k20c->SetBinError(6,1.310988);
   k20c->SetMaximum(1);
   k20c->SetEntries(12);
   k20c->SetStats(0);
   k20c->SetMarkerStyle(21);
   k20c->GetXaxis()->SetTitle("Tracks per jet");
   k20c->GetXaxis()->SetBinLabel(1,"1");
   k20c->GetXaxis()->SetBinLabel(2,"2");
   k20c->GetXaxis()->SetBinLabel(3,"5");
   k20c->GetXaxis()->SetBinLabel(4,"10");
   k20c->GetXaxis()->SetBinLabel(5,"25");
   k20c->GetXaxis()->SetBinLabel(6,"50");
   k20c->GetYaxis()->SetTitle("Efficiency");
   k20c->Draw("");
   
   TPaveText *pt = new TPaveText(0.1,0.945,0.9,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   TText *text = pt->AddText("Efficiency vs. tracks per jet");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);

   pt->SetTextFont(42);
   pt->SetTextColor(kBlack);
   k20c->GetXaxis()->SetTitleColor(kBlack);
   k20c->SetLineColor(kBlack);
   k20c->GetYaxis()->SetTitleOffset(1.15);
   
   c1->Print("eff_num_tracks_per_singularity.pdf");
}
