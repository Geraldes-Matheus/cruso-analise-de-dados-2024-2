#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>

void plotGraphs() {
    // Criação do canvas
    TCanvas *canvas = new TCanvas("canvas", "Graph with Errors", 800, 600);

    // Criar TGraph para os dados
    TGraph *graph = new TGraph("graphdata.txt");
    if (!graph) {
        std::cerr << "Erro ao carregar graphdata.txt" << std::endl;
        return;
    }

    // Criar TGraphErrors para os dados de erro
    TGraphErrors *graphErrors = new TGraphErrors("graphdata_error.txt");
    if (!graphErrors) {
        std::cerr << "Erro ao carregar graphdata_error.txt" << std::endl;
        return;
    }

    // Configurações do gráfico
    graph->SetMarkerStyle(22); // Estilo do marcador: caixa preta
    graph->SetMarkerColor(kBlack);
    graph->SetTitle("Grafico com Erros;eixo-X;eixo-Y");
    graph->Draw("ALP"); // Desenha os pontos do TGraph com linhas

    // Desenha o gráfico com erro
    graphErrors->SetMarkerStyle(21); // Estilo do marcador: círculo
    graphErrors->SetMarkerColor(kRed);
    graphErrors->Draw("P"); // Desenha os pontos do TGraphErrors

    // Salva o gráfico em PNG
    canvas->Print("exercício_2.png");

    // Limpa a memória
    delete canvas;
    delete graph;
    delete graphErrors;
}

void exer_2() {
    plotGraphs();
}
