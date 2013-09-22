{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Sep 21 22:40:37 2013) by ROOT version5.28/00h
   TCanvas *c1 = new TCanvas("c1", "c1",0,22,800,600);
   c1->Range(-1.25,0.7861098,6.25,1.023766);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   
   TProfile *k20c = new TProfile("k20c","Efficiency vs. number of displaced jets",6,-0.5,5.5,"");
   k20c->SetBinEntries(1,2);
   k20c->SetBinEntries(2,2);
   k20c->SetBinEntries(3,2);
   k20c->SetBinEntries(4,2);
   k20c->SetBinEntries(5,2);
   k20c->SetBinEntries(6,2);
   k20c->SetBinContent(1,1.711);
   k20c->SetBinContent(2,1.652);
   k20c->SetBinContent(3,1.714);
   k20c->SetBinContent(4,1.676);
   k20c->SetBinContent(5,1.685);
   k20c->SetBinContent(6,1.677);
   k20c->SetBinError(1,1.21001);
   k20c->SetBinError(2,1.168226);
   k20c->SetBinError(3,1.2121);
   k20c->SetBinError(4,1.185141);
   k20c->SetBinError(5,1.191828);
   k20c->SetBinError(6,1.18593);
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
