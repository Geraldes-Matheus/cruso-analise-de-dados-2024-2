#include <TH1F.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TApplication.h>

void exer_3() {
    // Cria o gerador de números aleatórios
    TRandom3 random;

    // Cria um histograma com 50 bins entre 0 e 10
    TH1F *hist = new TH1F("hist", "Histogram of Gaussian Random Numbers;Value;Entries", 50, 0, 10);

    // Preenche o histograma com 10000 números aleatórios com distribuição gaussiana
    for (int i = 0; i < 10000; i++) {
        double value = random.Gaus(5, 2); // Média 5 e sigma 2
        hist->Fill(value);
    }

    // Cria um canvas para desenhar o histograma
    TCanvas *canvas = new TCanvas("canvas", "Gaussian Histogram", 800, 600);

    // Define o modo da caixa de estatísticas
    gStyle->SetOptStat("kseiorum"); // k: kurtosis, s: skewness, i: integral, o: overflows, u: underflows, r: RMS, m: mean, e: number of entries

    // Desenha o histograma
    hist->Draw();

    // Salva o gráfico em PDF
    canvas->Print("exercício_3.png");

    // Limpa a memória
    delete canvas;
    delete hist;
}

