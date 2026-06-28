#ifndef IMAGEM_H
#define IMAGEM_H
#include <string>
#include "../paleta/cor.h"


class Imagem {
    int colunas;
    int linhas;
    Cor* matriz;
    
    public:
        Imagem();
        Imagem(int c, int l);
        ~Imagem();

        Cor& operator()(int c, int l);
        Cor& operator()(int c, int l) const;

        int obterLargura();
        int obterAltura();
        
        Cor getPixel(int c, int l);
        void setPixel(int c, int l, const Cor& pixel);
        bool lerPPM(const std::string& nome_arquivo);
        bool salvarPPM(const std::string& nome_arquivo);
};

#endif