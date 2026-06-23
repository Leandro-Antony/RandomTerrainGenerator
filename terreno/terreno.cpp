#include <fstream>
#include <cstdlib>
#include <ctime>
#include "terreno.h"
#include <cmath>
#include <iostream>
#include <random>
#include <iomanip>

Terreno::Terreno() {
    dimensao = 0;
    terreno = nullptr;
    std::random_device rd;
    gen.seed(rd());
}

Terreno::Terreno(int n) {
    std::random_device rd;
    gen.seed(rd());
    rugosidade = 0.5;
    dimensao = std::pow(2, n) + 1;

    terreno = nullptr;
     
    min = 80;
    max = 120;

    gerarAltitudes(n, rugosidade);
}

Terreno::~Terreno() {
    dimensao = 0;
    delete[] terreno;
    terreno = nullptr;
}

int Terreno::obterAltitude(int l, int c) {
    if (l >= 0 and l < dimensao and c >= 0 and c < dimensao) {
        return terreno[l * dimensao + c];
    }
    return -1; 
}

int Terreno::obterLinhas() {
    return dimensao;
}

int Terreno::obterColunas() {
    return dimensao;
}

void Terreno::reduzirIntervalo(double rugosidade) {
    double tamanho_atual = max - min;
    
    if (tamanho_atual <= 1.0) return;

    double novo_tamanho = tamanho_atual * rugosidade;
    double diferenca = (tamanho_atual - novo_tamanho) / 2.0;

    min += (int)diferenca;
    max -= (int)diferenca;
}

double Terreno::gerarPorcentagemDeslocamento() {
    if (min >= max) return min / 100.0;

    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen) / 100.0;
}

void Terreno::executarDiamond(int l, int c, int lado) {
    int metade = lado / 2;
    int alvo_l = l + metade;
    int alvo_c = c + metade;

    int sup_esq = terreno[l * dimensao + c];
    int sup_dir = terreno[l * dimensao + (c + lado)];
    int inf_esq = terreno[(l + lado) * dimensao + c];
    int inf_dir = terreno[(l + lado) * dimensao + (c + lado)];

    double media = (sup_esq + sup_dir + inf_esq + inf_dir) / 4.0;

    double porcentagem = gerarPorcentagemDeslocamento();

    terreno[alvo_l * dimensao + alvo_c] = (int)(media * porcentagem);
}

void Terreno::executarSquare(int l, int c, int metade) {
    double soma = 0.0;
    int vizinhos = 0;

    if (l - metade >= 0) { 
        soma += terreno[(l - metade) * dimensao + c]; 
        vizinhos++; 
    }

    if (l + metade < dimensao) {
        soma += terreno[(l + metade) * dimensao + c]; 
        vizinhos++; 
    }

    if (c - metade >= 0) {
        soma += terreno[l * dimensao + (c - metade)]; 
        vizinhos++; 
    }

    if (c + metade < dimensao) { 
        soma += terreno[l * dimensao + (c + metade)]; 
        vizinhos++; 
    }

    double media = soma / vizinhos;

    double porcentagem = gerarPorcentagemDeslocamento();

    terreno[l * dimensao + c] = (int)(media * porcentagem);
}