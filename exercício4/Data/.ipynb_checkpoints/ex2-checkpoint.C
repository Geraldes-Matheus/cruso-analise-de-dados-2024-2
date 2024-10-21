#include "RooFit.h"
#include "RooRealVar.h"
#include "RooExponential.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TPaveText.h"

using namespace RooFit;

void ex2() {
    //  variável contínua x
    RooRealVar x("x", "x", 0, 10);

    //  parâmetro lambda
    RooRealVar lambda("lambda", "Taxa de Decaimento", 1, 0.1, 2);

    //  função exponencial decrescente
    RooExponential expFunc("expFunc", "Função Exponencial", x, lambda);

    // Gerar dados simulados
    RooDataSet* data = expFunc.generate(RooArgSet(x), 1500); // 1500 eventos

    //  canvas para plotar
    TCanvas* canvas = new TCanvas("canvas", "Ajuste Exponencial", 800, 600);

    //  RooPlot para a variável x
    RooPlot* frame = x.frame();
    data->plotOn(frame);

    // Ajuste  da função exponencial
    expFunc.fitTo(*data);

    //  função ajustada
    expFunc.plotOn(frame);

    //  caixa de informação estatística
    TPaveText* statsBox = new TPaveText(0.15, 0.6, 0.35, 0.85, "NDC");
    statsBox->SetBorderSize(1);
    statsBox->SetFillColor(0);
    statsBox->SetTextAlign(12); // Alinhamento do texto
    statsBox->AddText("Parâmetros Ajustados:");
    statsBox->AddText(Form("Lambda: %.2f ± %.2f", lambda.getVal(), lambda.getError()));
    statsBox->AddText(Form("Total de Eventos: %d", (int)data->numEntries())); 

    // Adicionar a caixa ao frame
    frame->addObject(statsBox);

    
    frame->Draw();
    canvas->SaveAs("ex2.png");

    
    delete canvas;
    delete data;
}
