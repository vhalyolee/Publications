{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Sep 11 22:09:31 2013) by ROOT version5.28/00h
   TCanvas *c1 = new TCanvas("c1", "c1",348,75,800,602);
   c1->Range(-2.112245,-1.634573,14.13265,4.623632);
   c1->SetFillColor(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetFrameBorderMode(0);
   
   TProfile *k20c = new TProfile("k20c","Time vs. tracks per event, 2048x2048",13,-0.5,12.5,"");
   k20c->SetBinEntries(1,10);
   k20c->SetBinEntries(2,10);
   k20c->SetBinEntries(3,10);
   k20c->SetBinEntries(4,10);
   k20c->SetBinEntries(5,10);
   k20c->SetBinEntries(6,10);
   k20c->SetBinEntries(7,10);
   k20c->SetBinEntries(8,10);
   k20c->SetBinEntries(9,10);
   k20c->SetBinEntries(10,10);
   k20c->SetBinEntries(11,10);
   k20c->SetBinEntries(12,10);
   k20c->SetBinEntries(13,10);
   k20c->SetBinContent(1,5.973099);
   k20c->SetBinContent(2,6.252767);
   k20c->SetBinContent(3,6.349326);
   k20c->SetBinContent(4,7.133007);
   k20c->SetBinContent(5,10.91101);
   k20c->SetBinContent(6,16.04603);
   k20c->SetBinContent(7,27.44008);
   k20c->SetBinContent(8,66.5369);
   k20c->SetBinContent(9,93.65606);
   k20c->SetBinContent(10,129.0416);
   k20c->SetBinContent(11,232.5018);
   k20c->SetBinContent(12,334.0642);
   k20c->SetBinContent(13,536.2031);
   k20c->SetBinError(1,1.890574);
   k20c->SetBinError(2,1.977547);
   k20c->SetBinError(3,2.008017);
   k20c->SetBinError(4,2.274318);
   k20c->SetBinError(5,3.450718);
   k20c->SetBinError(6,5.074879);
   k20c->SetBinError(7,8.677653);
   k20c->SetBinError(8,21.04115);
   k20c->SetBinError(9,29.61729);
   k20c->SetBinError(10,40.80694);
   k20c->SetBinError(11,73.52377);
   k20c->SetBinError(12,105.6408);
   k20c->SetBinError(13,169.5627);
   k20c->SetMinimum(0.1);
   k20c->SetMaximum(10000);
   k20c->SetEntries(130);
   k20c->SetStats(0);
   k20c->SetMarkerStyle(21);
   k20c->GetXaxis()->SetTitle("Tracks per Event");
   k20c->GetXaxis()->SetBinLabel(1,"1");
   k20c->GetXaxis()->SetBinLabel(2,"2");
   k20c->GetXaxis()->SetBinLabel(3,"5");
   k20c->GetXaxis()->SetBinLabel(4,"10");
   k20c->GetXaxis()->SetBinLabel(5,"50");
   k20c->GetXaxis()->SetBinLabel(6,"100");
   k20c->GetXaxis()->SetBinLabel(7,"200");
   k20c->GetXaxis()->SetBinLabel(8,"500");
   k20c->GetXaxis()->SetBinLabel(9,"700");
   k20c->GetXaxis()->SetBinLabel(10,"1000");
   k20c->GetXaxis()->SetBinLabel(11,"2000");
   k20c->GetXaxis()->SetBinLabel(12,"3000");
   k20c->GetXaxis()->SetBinLabel(13,"5000");
   k20c->GetYaxis()->SetTitle("Time (milliseconds)");
   k20c->Draw("");
   
   TProfile *c2075 = new TProfile("c2075","Tesla C2075",13,-0.5,12.5,"");
   c2075->SetBinEntries(1,10);
   c2075->SetBinEntries(2,10);
   c2075->SetBinEntries(3,10);
   c2075->SetBinEntries(4,10);
   c2075->SetBinEntries(5,10);
   c2075->SetBinEntries(6,10);
   c2075->SetBinEntries(7,10);
   c2075->SetBinEntries(8,10);
   c2075->SetBinEntries(9,10);
   c2075->SetBinEntries(10,10);
   c2075->SetBinEntries(11,10);
   c2075->SetBinEntries(12,10);
   c2075->SetBinEntries(13,10);
   c2075->SetBinContent(1,8.083583);
   c2075->SetBinContent(2,8.332013);
   c2075->SetBinContent(3,8.731603);
   c2075->SetBinContent(4,9.576321);
   c2075->SetBinContent(5,16.46781);
   c2075->SetBinContent(6,25.04014);
   c2075->SetBinContent(7,43.66183);
   c2075->SetBinContent(8,107.2419);
   c2075->SetBinContent(9,153.8389);
   c2075->SetBinContent(10,213.9756);
   c2075->SetBinContent(11,386.5031);
   c2075->SetBinContent(12,552.1151);
   c2075->SetBinContent(13,892.4102);
   c2075->SetBinError(1,2.556487);
   c2075->SetBinError(2,2.635106);
   c2075->SetBinError(3,2.76141);
   c2075->SetBinError(4,3.028374);
   c2075->SetBinError(5,5.207956);
   c2075->SetBinError(6,7.918567);
   c2075->SetBinError(7,13.80746);
   c2075->SetBinError(8,33.91341);
   c2075->SetBinError(9,48.64875);
   c2075->SetBinError(10,67.66537);
   c2075->SetBinError(11,122.2235);
   c2075->SetBinError(12,174.5953);
   c2075->SetBinError(13,282.2066);
   c2075->SetEntries(130);
   c2075->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ff0000");
   c2075->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   c2075->SetMarkerColor(ci);
   c2075->SetMarkerStyle(20);
   c2075->GetXaxis()->SetBinLabel(1,"1");
   c2075->GetXaxis()->SetBinLabel(2,"2");
   c2075->GetXaxis()->SetBinLabel(3,"5");
   c2075->GetXaxis()->SetBinLabel(4,"10");
   c2075->GetXaxis()->SetBinLabel(5,"50");
   c2075->GetXaxis()->SetBinLabel(6,"100");
   c2075->GetXaxis()->SetBinLabel(7,"200");
   c2075->GetXaxis()->SetBinLabel(8,"500");
   c2075->GetXaxis()->SetBinLabel(9,"700");
   c2075->GetXaxis()->SetBinLabel(10,"1000");
   c2075->GetXaxis()->SetBinLabel(11,"2000");
   c2075->GetXaxis()->SetBinLabel(12,"3000");
   c2075->GetXaxis()->SetBinLabel(13,"5000");
   c2075->Draw("same");
   
   TProfile *cpu = new TProfile("cpu","CPU (old)",13,-0.5,12.5,"");
   cpu->SetBinEntries(1,10);
   cpu->SetBinEntries(2,10);
   cpu->SetBinEntries(3,10);
   cpu->SetBinEntries(4,10);
   cpu->SetBinEntries(5,10);
   cpu->SetBinEntries(6,10);
   cpu->SetBinEntries(7,10);
   cpu->SetBinEntries(8,10);
   cpu->SetBinEntries(9,10);
   cpu->SetBinEntries(10,10);
   cpu->SetBinEntries(11,10);
   cpu->SetBinEntries(12,10);
   cpu->SetBinEntries(13,10);
   cpu->SetBinContent(1,100.0414);
   cpu->SetBinContent(2,119.4184);
   cpu->SetBinContent(3,182.0511);
   cpu->SetBinContent(4,282.0112);
   cpu->SetBinContent(5,960.4827);
   cpu->SetBinContent(6,1777.044);
   cpu->SetBinContent(7,3387.28);
   cpu->SetBinContent(8,8317.871);
   cpu->SetBinContent(9,11695.24);
   cpu->SetBinContent(10,16725.1);
   cpu->SetBinContent(11,32070.77);
   cpu->SetBinContent(12,48046.41);
   cpu->SetBinContent(13,80739.93);
   cpu->SetBinError(1,31.72746);
   cpu->SetBinError(2,37.76801);
   cpu->SetBinError(3,57.58514);
   cpu->SetBinError(4,89.22171);
   cpu->SetBinError(5,303.7397);
   cpu->SetBinError(6,562.0582);
   cpu->SetBinError(7,1071.25);
   cpu->SetBinError(8,2630.399);
   cpu->SetBinError(9,3698.524);
   cpu->SetBinError(10,5288.979);
   cpu->SetBinError(11,10141.68);
   cpu->SetBinError(12,15193.63);
   cpu->SetBinError(13,25532.23);
   cpu->SetEntries(130);
   cpu->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   cpu->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   cpu->SetMarkerColor(ci);
   cpu->SetMarkerStyle(24);
   cpu->GetXaxis()->SetBinLabel(1,"1");
   cpu->GetXaxis()->SetBinLabel(2,"2");
   cpu->GetXaxis()->SetBinLabel(3,"5");
   cpu->GetXaxis()->SetBinLabel(4,"10");
   cpu->GetXaxis()->SetBinLabel(5,"50");
   cpu->GetXaxis()->SetBinLabel(6,"100");
   cpu->GetXaxis()->SetBinLabel(7,"200");
   cpu->GetXaxis()->SetBinLabel(8,"500");
   cpu->GetXaxis()->SetBinLabel(9,"700");
   cpu->GetXaxis()->SetBinLabel(10,"1000");
   cpu->GetXaxis()->SetBinLabel(11,"2000");
   cpu->GetXaxis()->SetBinLabel(12,"3000");
   cpu->GetXaxis()->SetBinLabel(13,"5000");
   cpu->Draw("same");
   
   TProfile *cpu_new = new TProfile("cpu_new","CPU (new)",13,-0.5,12.5,"");
   cpu_new->SetBinEntries(1,10);
   cpu_new->SetBinEntries(2,10);
   cpu_new->SetBinEntries(3,10);
   cpu_new->SetBinEntries(4,10);
   cpu_new->SetBinEntries(5,10);
   cpu_new->SetBinEntries(6,10);
   cpu_new->SetBinEntries(7,10);
   cpu_new->SetBinEntries(8,10);
   cpu_new->SetBinEntries(9,10);
   cpu_new->SetBinEntries(10,10);
   cpu_new->SetBinEntries(11,10);
   cpu_new->SetBinEntries(12,10);
   cpu_new->SetBinEntries(13,10);
   cpu_new->SetBinContent(1,68.64116);
   cpu_new->SetBinContent(2,79.85626);
   cpu_new->SetBinContent(3,122.3753);
   cpu_new->SetBinContent(4,191.4969);
   cpu_new->SetBinContent(5,664.7559);
   cpu_new->SetBinContent(6,1213.35);
   cpu_new->SetBinContent(7,2373.952);
   cpu_new->SetBinContent(8,5656.433);
   cpu_new->SetBinContent(9,8112.645);
   cpu_new->SetBinContent(10,11509.45);
   cpu_new->SetBinContent(11,22022.13);
   cpu_new->SetBinContent(12,32872.72);
   cpu_new->SetBinContent(13,55549.94);
   cpu_new->SetBinError(1,21.76301);
   cpu_new->SetBinError(2,25.26915);
   cpu_new->SetBinError(3,38.73938);
   cpu_new->SetBinError(4,60.66488);
   cpu_new->SetBinError(5,210.3354);
   cpu_new->SetBinError(6,384.1184);
   cpu_new->SetBinError(7,751.2021);
   cpu_new->SetBinError(8,1789.348);
   cpu_new->SetBinError(9,2566.863);
   cpu_new->SetBinError(10,3641.504);
   cpu_new->SetBinError(11,6969.66);
   cpu_new->SetBinError(12,10402.48);
   cpu_new->SetBinError(13,17579.67);
   cpu_new->SetEntries(130);
   cpu_new->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   cpu_new->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   cpu_new->SetMarkerColor(ci);
   cpu_new->SetMarkerStyle(20);
   cpu_new->GetXaxis()->SetBinLabel(1,"1");
   cpu_new->GetXaxis()->SetBinLabel(2,"2");
   cpu_new->GetXaxis()->SetBinLabel(3,"5");
   cpu_new->GetXaxis()->SetBinLabel(4,"10");
   cpu_new->GetXaxis()->SetBinLabel(5,"50");
   cpu_new->GetXaxis()->SetBinLabel(6,"100");
   cpu_new->GetXaxis()->SetBinLabel(7,"200");
   cpu_new->GetXaxis()->SetBinLabel(8,"500");
   cpu_new->GetXaxis()->SetBinLabel(9,"700");
   cpu_new->GetXaxis()->SetBinLabel(10,"1000");
   cpu_new->GetXaxis()->SetBinLabel(11,"2000");
   cpu_new->GetXaxis()->SetBinLabel(12,"3000");
   cpu_new->GetXaxis()->SetBinLabel(13,"5000");
   cpu_new->Draw("same");
   
   TLegend *leg = new TLegend(0.1281407,0.6590909,0.4208543,0.8601399,NULL,"brNDC");
   leg->SetTextFont(72);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("k20c","Tesla K20c","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("c2075","Tesla C2075","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("cpu","CPU (old)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("cpu_new","CPU (new)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();
   
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
