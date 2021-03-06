{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Sep 21 22:44:46 2013) by ROOT version5.28/00h
   TCanvas *c1 = new TCanvas("c1", "c1",0,22,800,600);
   c1->Range(-1.25,0.9176585,6.25,1.009149);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   
   TProfile *k20c = new TProfile("k20c","Efficiency vs. number of displaced jets",6,-0.5,5.5,"");
   k20c->SetBinEntries(1,2);
   k20c->SetBinEntries(2,2);
   k20c->SetBinEntries(3,2);
   k20c->SetBinEntries(4,2);
   k20c->SetBinEntries(5,2);
   k20c->SetBinEntries(6,2);
   k20c->SetBinContent(1,1.958);
   k20c->SetBinContent(2,1.951);
   k20c->SetBinContent(3,1.934);
   k20c->SetBinContent(4,1.862);
   k20c->SetBinContent(5,1.873);
   k20c->SetBinContent(6,1.879);
   k20c->SetBinError(1,1.384518);
   k20c->SetBinError(2,1.379566);
   k20c->SetBinError(3,1.367547);
   k20c->SetBinError(4,1.316634);
   k20c->SetBinError(5,1.324413);
   k20c->SetBinError(6,1.328658);
   k20c->SetMaximum(1);
   k20c->SetEntries(12);
   k20c->SetStats(0);
   k20c->SetMarkerStyle(21);
   k20c->GetXaxis()->SetTitle("Number of Displaced Jets");
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
   TText *text = pt->AddText("Efficiency vs. number of displaced jets");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
