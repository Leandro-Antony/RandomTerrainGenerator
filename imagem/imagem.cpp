#include <fstream>
#include <iostream>
#include "../paleta/cor.h"
#include "../paleta/paleta.h"
#include "./imagem.h"

Imagem::Imagem() {
    colunas = 0;
    linhas = 0;
    matriz = nullptr;
}

Imagem::Imagem(int c, int l) {
    colunas = c;
    linhas = l;

    matriz = new Cor[linhas*colunas];
    for (int lin = 0; lin < linhas; ++lin) {
        for (int col = 0; col < colunas; ++col) {
            Cor preto = {0 ,0, 0};
            matriz[lin*colunas + col] = preto;
        }
    }
};

Imagem::~Imagem() {
    if (matriz != nullptr) {
        delete [] matriz;
        matriz = nullptr;
    }
}

Cor& Imagem::operator()(int c, int l) {
    return matriz[l*colunas + c];
}

Cor& Imagem::operator()(int c, int l) const{
    return matriz[l*colunas + c];
}

int Imagem::obterAltura() {
    return linhas;
}

int Imagem::obterLargura() {
    return colunas;
}

Cor Imagem::getPixel(int c, int l) {
    return matriz[l * colunas + c];
}

void Imagem::setPixel(int c, int l, const Cor& pixel) {
    matriz[l*colunas + c] = pixel;
}


bool Imagem::lerPPM(const std::string& nome_arquivo) {
    std::ifstream arquivo(nome_arquivo);
    if(!arquivo.is_open()) {
        return false;
    }

    std::string formato;

    arquivo >> formato;

    if (formato != "P3") {
        std::cerr << "Formato de arquivo inválido" << std::endl;
        return false;
    }

    int novasColunas, novasLinhas, maxRGB;
    arquivo >> novasColunas >> novasLinhas;
    arquivo >> maxRGB; 

    delete[] matriz;

    colunas = novasColunas;
    linhas = novasLinhas;

    matriz = new Cor[linhas * colunas];

    for (int lin = 0; lin < linhas; ++lin) {
        for (int col = 0; col < colunas; ++col) {
            int r, g, b;
            arquivo >> r >> g >> b;

            Cor novaCor = {r, g, b};

            setPixel(col, lin, novaCor);
        }
    }

    return true;
}

bool Imagem::salvarPPM(const std::string& nome_arquivo) {
    std::ofstream arquivo(nome_arquivo);

    arquivo << "P3\n";
    arquivo << colunas << " " << linhas << "\n";
    arquivo << "255\n";

    for (int lin = 0; lin < linhas; ++lin) {
        for (int col = 0; col < colunas; ++col) {
            Cor c = getPixel(col, lin);

            arquivo << c.r << " " << c.g << " " << c.b << "\n";
        }
    }

    return true;
}