#ifndef TERRENO_H
#define TERRENO_H
#include <string>

class Terreno {
    int dimensao;
    int* terreno;
    
    public:
        Terreno();
        Terreno(int n);
        ~Terreno();

        void gerarAltitudes(int n, int rug);
        int obterAltitude(int l, int c);
        int obterLinhas();
        int obterColunas();

        void salvarTerreno(const std::string& nome_arquivo);
        void lerTerreno(const std::string& nome_arquivo);
};

#endif