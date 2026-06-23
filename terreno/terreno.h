#ifndef TERRENO_H
#define TERRENO_H
#include <string>
#include <random>

class Terreno {
    int dimensao;
    int* terreno;
    int min, max;
    std::mt19937 gen;
    double rugosidade;

    void executarDiamond(int l, int c, int lado);
    void executarSquare(int l, int c, int metade);
    void reduzirIntervalo(double rugosidade);
    double gerarPorcentagemDeslocamento();

    public:
        Terreno();
        Terreno(int n);
        ~Terreno();

        int obterAltitude(int l, int c);
        int obterLinhas();
        int obterColunas();

        void gerarAltitudes(int n, double rugosidade);
        
        void salvarTerreno(const std::string& nome_arquivo);
        void lerTerreno(const std::string& nome_arquivo);
};

#endif