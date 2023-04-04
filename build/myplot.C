{
  gROOT->Reset();
  
  // Draw histos filled by Geant4 simulation 
  //   
  //TFile f(_file0);  
  TCanvas* c1 = new TCanvas("c1", "  ");

gStyle->SetOptStat(0000);

  TH1D* hist30 = (TH1D*)_file0->Get("h30");

  double entries = hist30->GetEntries();
  double integral = hist30->Integral();
  std::cout << " entries : " << entries << std::endl;
  std::cout << " Integral : " << integral << std::endl;


  hist30->Scale(1./integral);
  hist30->SetTitle("Aluminim oxide (10nm), E_{0}^{e-}= 250 eV, entries normalized to unit area");
  hist30->GetYaxis()->SetTitle("d#delta/dE[eV^{-1}]");
  hist30->GetYaxis()->CenterTitle(true);
  hist30->GetYaxis()->SetTitleOffset(1.2);
  hist30->GetYaxis()->SetTickSize(0.009);
  hist30->GetYaxis()->SetLabelSize(0.03);
  hist30->GetXaxis()->SetTitle("Energy of secondary electrons [eV]");
  hist30->GetXaxis()->CenterTitle(true);
  hist30->Draw("HIST");
}  
