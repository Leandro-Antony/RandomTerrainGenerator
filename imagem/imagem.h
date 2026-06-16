#ifndef IMAGEM_H
#define IMAGEM_H
#include "../paleta/cor.h"


class Imagem {
    int linhas;
    int colunas;
    Cor* matriz;
    
    public:
        Imagem();
        Imagem(int l, int c);
        
        Cor getPixel(int linha, int coluna);
        void setPixel(int linha, int coluna, const Cor& pixel);
        int readFile(std::string& nome_arquivo);
        void saveImage(std::string& nome_arquivo);

        void liberaMatriz(int **matriz, int linha);

    
};

#endif