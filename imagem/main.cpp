#include <iostream>
#include "imagem.h"

int main() {
    int colunas = 200;
    int linhas = 100;
    Imagem img(colunas, linhas);

    Cor branco = {255, 255, 255};
    Cor vermelho = {255, 0, 0};

    for (int l = 0; l < 50; ++l) {
        for (int c = 0; c < colunas; ++c) {
            img(c, l) = branco;
        }
    }

    for (int l = 50; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            img(c, l) = vermelho;
        }
    }

    std::string nomeArquivo = "bandeira_polonia.ppm";
    if (img.salvarPPM(nomeArquivo)) {
        std::cout << "Sucesso: Bandeira salva em '" << nomeArquivo << "'!" << std::endl;
    } else {
        std::cerr << "Erro ao salvar a imagem." << std::endl;
        return 1;
    }

    Imagem novaImg;
    if (novaImg.lerPPM(nomeArquivo)) {
        std::cout << "Sucesso: Arquivo lido de volta com sucesso!" << std::endl;
        std::cout << "Dimensoes da imagem lida: " 
                  << novaImg.obterLargura() << "x" << novaImg.obterAltura() << "\n" << std::endl;
    } else {
        std::cerr << "Erro ao ler o arquivo PPM." << std::endl;
        return 1;
    }

    return 0;
}