#include <fstream>
#include "../paleta/cor.h"
#include "../paleta/paleta.h"
#include "./imagem.h"

Imagem::Imagem() {
}

Imagem::Imagem(int l, int c) {
    linhas = l;
    colunas = c;

    matriz = new Cor[linhas*colunas];
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            Cor preto = {0,0,0};
            matriz[i*colunas + j] = preto;
        }
    }
};

Cor Imagem::getPixel(int linha, int coluna) {
    return matriz[linha * colunas + coluna];
}

void Imagem::setPixel(int linha, int coluna, const Cor& pixel) {
    matriz[linha*coluna + coluna] = pixel;
}


int Imagem::readFile(std::string& nome_arquivo) {
    std::ifstream arquivo(nome_arquivo);
    if(!arquivo.is_open()) {
        return 1;
    }

    //std::string txt;
    //
    //while(arquivo>>txt) {
    //    
    //}

}