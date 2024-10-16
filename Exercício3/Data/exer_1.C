void exer_1() {
    // Definindo a função com parâmetros p0 e p1
    auto sine_function = [](double x, double p0, double p1) {
        return p0 * sin(p1 * x) / x;
    };

    // Valores dos parâmetros
    std::vector<std::pair<double, double>> parameters = {
        {0.5, 0.1},
        {2.0, 5.0},
        {10.0, 15.0},
        {1.0, 2.0} // Adicionando o novo par de parâmetros
    };

    // Intervalo de x
    const int nPoints = 1000;
    double x[nPoints];
    double y[nPoints];

    // Criar e salvar os gráficos
    for (size_t i = 0; i < parameters.size(); ++i) {
        double p0 = parameters[i].first;
        double p1 = parameters[i].second;

        // Preencher os valores de x e y
        for (int j = 0; j < nPoints; ++j) {
            x[j] = j / 100.0; // de 0 a 10
            if (x[j] != 0) {
                y[j] = sine_function(x[j], p0, p1);
            } else {
                y[j] = 0; // Para evitar divisão por zero
            }
        }

        // Criar o gráfico
        TGraph *graph = new TGraph(nPoints, x, y);
        graph->SetTitle(Form("p0 = %.1f, p1 = %.1f", p0, p1));
        graph->GetXaxis()->SetTitle("x");
        graph->GetYaxis()->SetTitle("f(x)");
        graph->SetLineColor(kBlue); // Definindo a cor do gráfico para azul

        // Adicionar legenda com a função para todos os gráficos
        auto legend = new TLegend(0.7, 0.7, 0.9, 0.9); // Canto superior direito
        legend->AddEntry(graph, Form("f(x) = %.1f * sin(%.1f * x) / x", p0, p1), "l");

        // Verificar se p0=1 e p1=2 para cálculos adicionais
        if (p0 == 1.0 && p1 == 2.0) {
            double x_value = 1.0;
            double function_value = sine_function(x_value, p0, p1);
            
            // Definindo a função para a derivada
            TF1 *f = new TF1("f", [&](double *x, double *par) {
                return sine_function(x[0], par[0], par[1]);
            }, 0, 10, 2);
            f->SetParameters(p0, p1);
            double derivative_value = f->Derivative(x_value);

            // Definindo a função para a integral
            double integral_value = f->Integral(0, 3);

            // Adicionar resultados adicionais à legenda
            legend->AddEntry((TObject*)0, Form("f(1) = %.3f", function_value), "");
            legend->AddEntry((TObject*)0, Form("f'(1) = %.3f", derivative_value), "");
            legend->AddEntry((TObject*)0, Form("Integral(0 to 3) = %.3f", integral_value), "");

            delete f; // Limpar a função
        }

        // Salvar gráfico em PNG
        TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600);
        graph->Draw("AL");
        legend->Draw(); // Desenhar a legenda após o gráfico
        canvas->SaveAs(Form("grafico_%lu.png", i + 1)); // Corrigido para %lu
        delete canvas; // Limpar o canvas após o uso

        // Limpar o gráfico para o próximo
        delete graph;
    }
}
