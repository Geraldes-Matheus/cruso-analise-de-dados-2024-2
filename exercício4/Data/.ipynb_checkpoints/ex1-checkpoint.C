void ex1() {
    // Criar uma variável observável
    RooRealVar x("x", "x", -10, 10);

    // Parâmetros da Crystal Ball
    RooRealVar mean("mean", "mean", 0, -10, 10);
    RooRealVar sigma("sigma", "sigma", 1, 0.1, 10);
    RooRealVar alpha("alpha", "alpha", 1, 0, 5);
    RooRealVar n("n", "n", 1, 0, 10);

    // Criar a função Crystal Ball
    RooCrystalBall cb("cb", "Crystal Ball PDF", x, mean, sigma, alpha, n);

    // Gerar dados simulados
    RooDataSet* data = cb.generate(RooArgSet(x), 1000);

    // Criar um canvas para plotar
    TCanvas* canvas = new TCanvas("canvas", "Canvas", 800, 600);

    // Criar um RooPlot para a variável x
    RooPlot* frame = x.frame();
    data->plotOn(frame);
    cb.plotOn(frame);

    // Ajuste da função aos dados
    cb.fitTo(*data);

    // Adicionar caixa de informação estatística
    TPaveText* statsBox = new TPaveText(0.15, 0.6, 0.35, 0.85, "NDC");
    statsBox->SetBorderSize(1);
    statsBox->SetFillColor(0);
    statsBox->SetTextAlign(12); 
    statsBox->AddText("Adjusted Parameters:");
    statsBox->AddText(Form("Mean: %.2f ± %.2f", mean.getVal(), mean.getError()));
    statsBox->AddText(Form("Sigma: %.2f ± %.2f", sigma.getVal(), sigma.getError()));
    statsBox->AddText(Form("Alpha: %.2f ± %.2f", alpha.getVal(), alpha.getError()));
    statsBox->AddText(Form("n: %.2f ± %.2f", n.getVal(), n.getError()));

    // Adicionar a caixa ao frame
    frame->addObject(statsBox);

    // Mostrar o resultado
    frame->Draw();
    canvas->SaveAs("ex1.png");

    // Limpar
    delete canvas;
    delete data;
}