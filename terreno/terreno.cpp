#include <fstream>
#include <cstdlib>
#include <ctime>
#include "terreno.h"
#include <cmath>
#include <iostream>
#include <random>

Terreno::Terreno() {
    dimensao = 0;
    terreno = nullptr;
}

Terreno::Terreno(int n, int minimo = 80, int maximo = 120) {
    dimensao = std::pow(2, n) + 1;
    min = minimo;
    max = maximo;

    // metodo de geração de altura

    terreno = new int[dimensao*dimensao];
}

Terreno::~Terreno() {
    dimensao = 0;
    delete[] terreno;
    terreno = nullptr;
}

double Terreno::rugosidade() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distReal(min, max);
    double rug = distReal(gen);
    double accDec = (max-min)/4;
    min += accDec;
    max -= accDec;
    return rug;
}

void Terreno::gerarAltitudes(int d, int rug) {
    
}