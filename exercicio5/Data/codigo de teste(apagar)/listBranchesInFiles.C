#include <iostream>
#include "TFile.h"
#include "TTree.h"

void listBranchesInFiles() {
    const char* directory = "/opendata/eos/opendata/cms/mc/RunIISummer20UL16NanoAODv9/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v17-v1/2430000/";

    const char* files[] = {
        "051E9D22-4F30-8E49-8477-644E65768282.root",
        "62AB4A36-86C6-CF48-81A5-3AEC926D349B.root",
        "05E26D0E-E9D4-854B-B6AC-45B436A83F07.root",
        "656B8DB4-AD62-024B-A729-E9D5CAD38CCC.root",
        "08A210AE-81AD-484E-8127-C088C63BA62A.root",
        "6972D919-B1FB-AD4C-8F03-8E93B2C29372.root",
        "357B04FF-8C8C-4241-8DB2-B336F45CEAFE.root",
        "69DA545E-63C1-8146-A9A5-333EC6E8F2D8.root",
        "5EF92F30-4FEF-9B49-9438-E4B24D8B5517.root",
        "A2E55423-6843-8946-830F-A52ACC06155A.root"
    };

    // Loop sobre os arquivos
    for (const char* fileName : files) {
        // Formar o caminho completo
        std::string fullPath = std::string(directory) + std::string(fileName);

        // Abrir o arquivo ROOT
        TFile *file = TFile::Open(fullPath.c_str());
        if (!file || file->IsZombie()) {
            std::cerr << "Error opening file: " << fullPath << std::endl;
            continue;
        }

        // Obter a árvore
        TTree *tree = (TTree*)file->Get("Events");
        if (!tree) {
            std::cerr << "Error getting tree 'Events' from file: " << fullPath << std::endl;
            file->Close();
            continue;
        }

        // Variáveis para armazenar os nomes das branches
        std::vector<std::string> ptBranches;
        std::vector<std::string> etaBranches;
        std::vector<std::string> phiBranches;

        // Filtrar branches
        TObjArray *branches = tree->GetListOfBranches();
        for (int i = 0; i < branches->GetEntries(); ++i) {
            TBranch *branch = (TBranch*)branches->At(i);
            std::string branchName = branch->GetName();
            
            // Verificar se a branch contém "pT", "eta" ou "phi"
            if (branchName.find("pt") != std::string::npos) {
                ptBranches.push_back(branchName);
            } else if (branchName.find("eta") != std::string::npos) {
                etaBranches.push_back(branchName);
            } else if (branchName.find("phi") != std::string::npos) {
                phiBranches.push_back(branchName);
            }
        }

        // Imprimir branches na tela, lado a lado
        std::cout << "Branches in file: " << fullPath << std::endl;
        std::cout << "pT: ";
        for (const auto& name : ptBranches) {
            std::cout << name << " ";
        }
        std::cout << "\nEta: ";
        for (const auto& name : etaBranches) {
            std::cout << name << " ";
        }
        std::cout << "\nPhi: ";
        for (const auto& name : phiBranches) {
            std::cout << name << " ";
        }
        std::cout << "\n" << std::endl; // Nova linha após todas as branches

        // Fechar o arquivo
        file->Close();
    }
}
