#ifndef PALETA_H
#define PALETA_H
#include "cor.h"
#include <vector>

class Paleta {
    std::vector<Cor> cores;

    public:
        Paleta();
        Paleta(const std::string& nome_arquivo);

        void adicionarCor(Cor& cor);

        int obterTamanho();

        Cor obterCor(int index);
};

#endif