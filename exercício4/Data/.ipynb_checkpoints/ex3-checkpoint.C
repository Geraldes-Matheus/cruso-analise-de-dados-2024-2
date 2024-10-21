#include <RooGlobalFunc.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooPlot.h>
#include <RooCrystalBall.h>
#include <RooPolynomial.h>
#include <RooAddPdf.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
#include <iostream>


void ex3() {
    // Carregar o arquivo ROOT
    TFile *file = TFile::Open("DataSet_lowstat.root");
    RooDataSet *data = (RooDataSet*)file->Get("data");

    // Definir a variável de massa
    RooRealVar mass("mass", "Massa (GeV/c^2)", 2.5, 3.5);  // Ajuste os limites conforme necessário

    // Definir a PDF do sinal (Crystal Ball)
    RooRealVar mean("mean", "Média", 3.096916, 3.0, 3.2);
    RooRealVar sigma("sigma", "Desvio Padrão", 0.01, 0.001, 0.1);
    RooRealVar alpha("alpha", "Alpha", 1.0);
    RooRealVar n("n", "n", 5.0); 
    RooCrystalBall signal("signal", "Sinal J/ψ", mass, mean, sigma, alpha, n);

    // Definir a PDF do fundo 
    RooRealVar a0("a0", "a0", 1.0, -10.0, 10.0);
    RooRealVar a1("a1", "a1", 0.0, -10.0, 10.0);
    RooRealVar a2("a2", "a2", 0.0, -10.0, 10.0);
    RooPolynomial background("background", "Fundo", mass, RooArgList(a0, a1, a2));

    // Combinar as PDFs
    RooRealVar signalFrac("signalFrac", "Frações do Sinal", 0.1, 0.0, 1.0);
    RooAddPdf model("model", "Modelo Sinal + Fundo", RooArgList(signal, background), RooArgList(signalFrac));

    // Ajustar o modelo aos dados
    model.fitTo(*data);

    // Calcular χ²/ndf
    RooPlot *frame = mass.frame();
    data->plotOn(frame);
    model.plotOn(frame);
    model.paramOn(frame);

    // Exibir o resultado do ajuste
    TCanvas *c1 = new TCanvas("c1", "Ajuste J/ψ", 800, 600);
    frame->SetTitle("Mass of J/Psi");
    frame->Draw();

    // Calcular χ² e ndf
    double chi2 = frame->chiSquare();
    int ndata = data->numEntries(); // Número de eventos no dataset
    int nparams = model.getParameters(mass)->getSize(); // Número de parâmetros ajustados
    int ndf = ndata - nparams; // Calculando ndf

    // Calcular chi²/ndf
    double chi2_ndf = chi2 / ndf;

    // Adicionar os valores de χ², ndf e χ²/ndf ao gráfico usando TLegend
    TLegend *legend = new TLegend(0.15, 0.75, 0.35, 0.85); // Coordenadas ajustadas para a esquerda
    legend->AddEntry((TObject*)0, Form("#chi^{2} = %.2e", chi2), "");
    legend->AddEntry((TObject*)0, Form("ndf = %d", ndf), "");
    legend->AddEntry((TObject*)0, Form("#chi^{2}/ndf = %.2e", chi2_ndf), "");
    legend->SetHeader("Resultados do Ajuste");
    legend->SetBorderSize(1);
    legend->SetFillColor(kWhite); // Cor de fundo branca
    legend->Draw();

    std::cout << "Número de pontos de dados (ndata): " << ndata << std::endl;
    std::cout << "Número de parâmetros ajustados (nparams): " << nparams << std::endl;
   

    std::cout << "χ² = " << chi2 << std::endl;
    std::cout << "ndf = " << ndf << std::endl;
    std::cout << "chi^2 / ndf = " << chi2_ndf << std::endl;

    // Salvar o gráfico em formato PNG
    c1->SaveAs("plot_jpsi.png");

    // Fechar o arquivo
    file->Close();
}