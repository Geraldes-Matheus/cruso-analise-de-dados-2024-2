#define ex1_cxx
#include "ex1.h"
#include <TH1F.h>
#include <TCanvas.h>

void ex1::Loop()
{
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();
    TH1F *histo1 = new TH1F("histo1", "Muon PT;PT (GeV/c);Counts", 200, 0, 150);
    TH1F *histo2 = new TH1F("histo2", "Muon Mass;Mass (GeV/c^2);Counts", 100, 0, 0.2); 
    TH1F *histo3 = new TH1F("histo3", "Electron Mass;Mass (GeV/c^2);Counts", 100, 0, 0.1); 

    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        fChain->GetEntry(jentry);

        for (UInt_t i = 0; i < nMuon; i++) {
            histo1->Fill(Muon_pt[i]); 
            histo2->Fill(Muon_mass[i]); 
        }

        for (UInt_t j = 0; j < nElectron; j++) {
            histo3->Fill(Electron_mass[j]); 
        }
    }

    TCanvas *canvas1 = new TCanvas("canvas1", "Histograma de Muon PT", 800, 600);
    histo1->Draw(); 
    canvas1->Print("histograma_muon_pt.png");

    TCanvas *canvas2 = new TCanvas("canvas2", "Histograma de Muon Mass", 800, 600);
    histo2->Draw();
    canvas2->Print("histograma_muon_mass.png");

    TCanvas *canvas3 = new TCanvas("canvas3", "Histograma de Electron Mass", 800, 600);
    histo3->Draw();
    canvas3->Print("histograma_electron_mass.png");

    delete canvas1; 
    delete canvas2; 
    delete canvas3; 

    delete histo1; 
    delete histo2; 
    delete histo3; 
}
