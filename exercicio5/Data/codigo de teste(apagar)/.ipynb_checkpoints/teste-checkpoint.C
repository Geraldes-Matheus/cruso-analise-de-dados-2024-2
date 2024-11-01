#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TMath.h>
#include <iostream>
#include <vector>
#include <filesystem>

double calcular_massa_invariante(const TTreeReaderArray<float>& pt, const TTreeReaderArray<float>& eta, const TTreeReaderArray<float>& phi) {
    if (pt.GetSize() >= 2) {
        return sqrt(2 * pt[0] * pt[1] * (TMath::CosH(eta[0] - eta[1]) - TMath::Cos(phi[0] - phi[1])));
    }
    return -1.0; // Valor inválido caso não haja pelo menos dois elementos
}

void analise() {
    std::vector<std::string> diretorios = {
        "/opendata/eos/opendata/cms/mc/RunIISummer20UL16NanoAODv9/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v17-v1/2430000",
        //"/opendata/eos/opendata/cms/mc/RunIISummer20UL16NanoAODv9/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v17-v1/2520000",
        //"/opendata/eos/opendata/cms/mc/RunIISummer20UL16NanoAODv9/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v17-v1/2530000",
        //"/opendata/eos/opendata/cms/mc/RunIISummer20UL16NanoAODv9/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v17-v1/40000",
        //"/opendata/eos/opendata/cms/mc/RunIISummer20UL16NanoAODv9/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v17-v1/50000"
    };

    std::vector<double> e_massas_invariantes, m_massas_invariantes, t_massas_invariantes;

    for (const auto& dir : diretorios) {
        for (const auto& entry : std::filesystem::directory_iterator(dir)) {
            std::string file_path = entry.path();
            TFile file(file_path.c_str(), "READ");
            if (!file.IsOpen()) continue;

            TTreeReader reader("Events", &file);
            TTreeReaderArray<float> Electron_pt(reader, "Electron_pt");
            TTreeReaderArray<float> Electron_eta(reader, "Electron_eta");
            TTreeReaderArray<float> Electron_phi(reader, "Electron_phi");
            TTreeReaderArray<float> Muon_pt(reader, "Muon_pt");
            TTreeReaderArray<float> Muon_eta(reader, "Muon_eta");
            TTreeReaderArray<float> Muon_phi(reader, "Muon_phi");
            TTreeReaderArray<float> Tau_pt(reader, "Tau_pt");
            TTreeReaderArray<float> Tau_eta(reader, "Tau_eta");
            TTreeReaderArray<float> Tau_phi(reader, "Tau_phi");

            while (reader.Next()) {
                if (Electron_pt.GetSize() >= 2) {
                    e_massas_invariantes.push_back(calcular_massa_invariante(Electron_pt, Electron_eta, Electron_phi));
                }
                if (Muon_pt.GetSize() >= 2) {
                    m_massas_invariantes.push_back(calcular_massa_invariante(Muon_pt, Muon_eta, Muon_phi));
                }
                if (Tau_pt.GetSize() >= 2) {
                    t_massas_invariantes.push_back(calcular_massa_invariante(Tau_pt, Tau_eta, Tau_phi));
                }
            }
        }
    }

    // Criar canvas e histogramas
    TCanvas* canvas = new TCanvas("canvas", "Distribuições de Massas Invariantes", 800, 600);
    TH1F* hEletron = new TH1F("hEletron", "", 50, 0, 200);
    TH1F* hMuon = new TH1F("hMuon", "", 50, 0, 200);
    TH1F* hTau = new TH1F("hTau", "", 50, 0, 200);

    for (const auto& massa : e_massas_invariantes) if (massa >= 0) hEletron->Fill(massa);
    for (const auto& massa : m_massas_invariantes) if (massa >= 0) hMuon->Fill(massa);
    for (const auto& massa : t_massas_invariantes) if (massa >= 0) hTau->Fill(massa);

    // Plotar e salvar os histogramas
    hEletron->SetLineColor(kBlue);
    hEletron->SetStats(0);
    hEletron->GetXaxis()->SetTitle("e_mass (GeV/c^{2})");
    hEletron->GetYaxis()->SetTitle("Eventos");
    hEletron->Draw();
    canvas->SaveAs("e_massa_invariante.png");

    hMuon->SetLineColor(kBlue);
    hMuon->SetStats(0);
    hMuon->GetXaxis()->SetTitle("#mu_mass (GeV/c^{2})");
    hMuon->GetYaxis()->SetTitle("Eventos");
    hMuon->Draw();
    canvas->SaveAs("m_massa_invariante.png");

    hTau->SetLineColor(kBlue);
    hTau->SetStats(0);
    hTau->GetXaxis()->SetTitle("#tau_mass (GeV/c^{2})");
    hTau->GetYaxis()->SetTitle("Eventos");
    hTau->Draw();
    canvas->SaveAs("t_massa_invariante.png");

    // Limpeza
    delete hEletron;
    delete hMuon;
    delete hTau;
    delete canvas;
}
