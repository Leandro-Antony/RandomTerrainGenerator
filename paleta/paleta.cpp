#include <fstream>
#include "cor.h"
#include "paleta.h"

Paleta::Paleta(){
}

Cor static hexParaCor(const std::string hex) {
    int r = std::stoi(hex.substr(1, 2), nullptr, 16);
    int g = std::stoi(hex.substr(3, 2), nullptr, 16);
    int b = std::stoi(hex.substr(5, 2), nullptr, 16);

    Cor corConvertida = {r, g, b};

    return corConvertida;
}

Paleta::Paleta(const std::string& nome_arquivo) {
    std::ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        
    }

    std::string linha;

    while(std::getline(arquivo, linha)) {
        if (!linha.empty()) {
            cores.push_back(hexParaCor(linha));
        }
    };
}

void Paleta::adicionarCor(Cor& cor) {
    cores.push_back(cor);
}

Cor Paleta::obterCor(int index) {
    return cores[index];
}

int Paleta::obterTamanho(){
    return cores.size();
}