void exer_4() {
    // 1. Abrir o arquivo e o TTree
    TFile *file = TFile::Open("tree.root");
    TTree *tree = (TTree*)file->Get("tree1");

    // 2. Definir variáveis
    float ebeam, px, py, pz;
    tree->SetBranchAddress("ebeam", &ebeam);
    tree->SetBranchAddress("px", &px);
    tree->SetBranchAddress("py", &py);
    tree->SetBranchAddress("pz", &pz);

    // 3. Calcular a média da energia do feixe
    double totalEnergy = 0;
    Long64_t nEntries = tree->GetEntries();

    // Loop para calcular a média
    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);
        totalEnergy += ebeam; // Soma a energia do feixe
    }

    // Verifique se  é maior que 0 
    if (nEntries > 0) {
        double meanEnergy = totalEnergy / nEntries; // Calcula a média
        double lowerCut = meanEnergy - 0.2;
        double upperCut = meanEnergy + 0.2;

        // Criar um objeto TCut para os cortes
        TCut cut = Form("ebeam < %f || ebeam > %f", upperCut, lowerCut);

        // 4. Criar o histograma
        TH1F *histogram = new TH1F("h_total_momentum", "Total Momentum Distribution", 200, 130, 160); 

        // 5. Preencher o histograma usando TTree::Draw
        tree->Draw("TMath::Sqrt(px*px + py*py + pz*pz)>>h_total_momentum", cut);

        // 6. Criar um canvas para desenhar o histograma
        TCanvas *c2 = new TCanvas("c2", "Total Momentum Distribution", 800, 600);
        histogram->Draw();

        // 7. Salvar o histograma em um arquivo PDF
        c2->SaveAs("exercício_4.png");
    }

    // 8. Fechar o arquivo original
    file->Close(); // Fecha o arquivo original
}
