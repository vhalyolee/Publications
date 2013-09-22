{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Sep 21 21:50:07 2013) by ROOT version5.28/00h
   TCanvas *c1 = new TCanvas("c1", "c1",134,89,800,600);
   c1->Range(-1.625,-9.263232,9.625,83.36908);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   
   TProfile *k20c = new TProfile("k20c","Time vs. tracks per event, 2048x2048",9,-0.5,8.5,"");
   k20c->SetBinEntries(1,10);
   k20c->SetBinEntries(2,10);
   k20c->SetBinEntries(3,10);
   k20c->SetBinEntries(4,10);
   k20c->SetBinEntries(5,10);
   k20c->SetBinEntries(6,10);
   k20c->SetBinEntries(7,10);
   k20c->SetBinEntries(8,10);
   k20c->SetBinEntries(9,10);
   k20c->SetBinContent(1,14.31439);
   k20c->SetBinContent(2,20.69946);
   k20c->SetBinContent(3,35.59144);
   k20c->SetBinContent(4,86.6383);
   k20c->SetBinContent(5,122.8243);
   k20c->SetBinContent(6,167.8892);
   k20c->SetBinContent(7,303.4753);
   k20c->SetBinContent(8,435.9887);
   k20c->SetBinContent(9,701.0737);
   k20c->SetBinError(1,4.527926);
   k20c->SetBinError(2,6.547768);
   k20c->SetBinError(3,11.25773);
   k20c->SetBinError(4,27.40382);
   k20c->SetBinError(5,38.84849);
   k20c->SetBinError(6,53.0998);
   k20c->SetBinError(7,95.9909);
   k20c->SetBinError(8,137.9039);
   k20c->SetBinError(9,221.7487);
   k20c->SetEntries(90);
   k20c->SetStats(0);
   k20c->SetMarkerStyle(21);
   k20c->GetXaxis()->SetTitle("Tracks per Event");
   k20c->GetXaxis()->SetBinLabel(1,"50");
   k20c->GetXaxis()->SetBinLabel(2,"100");
   k20c->GetXaxis()->SetBinLabel(3,"200");
   k20c->GetXaxis()->SetBinLabel(4,"500");
   k20c->GetXaxis()->SetBinLabel(5,"700");
   k20c->GetXaxis()->SetBinLabel(6,"1000");
   k20c->GetXaxis()->SetBinLabel(7,"2000");
   k20c->GetXaxis()->SetBinLabel(8,"3000");
   k20c->GetXaxis()->SetBinLabel(9,"5000");
   k20c->GetYaxis()->SetTitle("Time (milliseconds)");
   k20c->Draw("");
   
   TPaveText *pt = new TPaveText(0.1,0.945,0.9,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   TText *text = pt->AddText("Time vs. tracks per event, 2048x2048");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
