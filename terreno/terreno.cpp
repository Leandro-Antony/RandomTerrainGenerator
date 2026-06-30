#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <random>
#include <iomanip>
#include "terreno.h"
#include "../paleta/paleta.h"
#include "../imagem/imagem.h"

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
     
    min = -80;
    max = 80;

    minAltitude = 1000;
    maxAltitude = -1000;

    gerarAltitudes();
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

void Terreno::setAltitude(int l, int c, int valor){
    terreno[l*dimensao + c] = valor;
}

void Terreno::gerarAltitudes(){
    terreno = new int[dimensao*dimensao];
    std::uniform_int_distribution<int> dist(0,255);
    setAltitude(0,0,dist(gen));
    setAltitude(0,dimensao-1,dist(gen));
    setAltitude(dimensao-1,0,dist(gen));
    setAltitude(dimensao-1,dimensao-1,dist(gen));

    for (int lado = dimensao-1; lado > 1; lado /= 2) {
        int metade = lado / 2;

        for (int l = 0; l < dimensao-1; l += lado) {
            for (int c = 0; c < dimensao-1; c += lado) {
                executarDiamond(l, c, lado);
            }
        }

        for (int l = 0; l < dimensao; l += metade) {
            for (int c = (l/metade % 2 == 0) ? metade : 0; c < dimensao; c += lado) {
                executarSquare(l, c, metade);
            }
        }

        reduzirIntervalo();
    }
}


void Terreno::reduzirIntervalo() {
    min = (int)(min * rugosidade);
    max = (int)(max * rugosidade);
}

int Terreno::gerarDeslocamento() {
    if (min >= max) return 0;
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void Terreno::executarDiamond(int l, int c, int lado) {
    int metade = lado / 2;
    int alvo_l = l + metade;
    int alvo_c = c + metade;

    int sup_esq = obterAltitude(l, c);
    int sup_dir = obterAltitude(l, c+lado);
    int inf_esq = obterAltitude(l+lado, c);
    int inf_dir = obterAltitude(l+lado, c+lado);

    double media = (sup_esq + sup_dir + inf_esq + inf_dir) / 4.0;

    double deslocamento = gerarDeslocamento();

    setAltitude(alvo_l, alvo_c, (int)(media + deslocamento));
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

    double deslocamento = gerarDeslocamento();

    setAltitude(l,c,(int)(media + deslocamento));
}

void Terreno::showTerreno() {
    for (int i = 0; i < dimensao; i++) {
        for(int j = 0; j < dimensao; j++) {
            std::cout << obterAltitude(i, j) << " ";
        }
        std::cout << std::endl;
    }
}


int Terreno::terrenoMax() {
    for (int i = 0; i < dimensao*dimensao; i++) {
        if (terreno[i] > maxAltitude) maxAltitude = terreno[i];
    }
    return maxAltitude;
}

int Terreno::terrenoMin() {
    for (int i = 0; i < dimensao*dimensao; i++) {
        if (terreno[i] < minAltitude) minAltitude = terreno[i];
    }
    return minAltitude;
}


void Terreno::salvarTerreno(const std::string& nome_arquivo) {
    std::ofstream arquivo(nome_arquivo);

    if (arquivo.is_open()) {
        arquivo << dimensao << std::endl;
        for (int i = 0; i < dimensao; i++) {
            for(int j = 0; j < dimensao; j++) {
                arquivo << obterAltitude(i, j) << " ";
            }
            arquivo << std::endl;
        }
    }
}

void Terreno::lerTerreno(const std::string& nome_arquivo) {
    std::ifstream arquivo(nome_arquivo);

    if (arquivo.is_open()) {
        arquivo >> dimensao;
        if (terreno != nullptr) {
            delete[] terreno;
        }
        terreno = new int[dimensao*dimensao];
        int valor, i = 0;
        while (arquivo >> valor) {
            terreno[i] = valor;
            i++;
        }
        
    }
}

void Terreno::gerarRelevoPPM(const std::string arquivo_cores, const std::string arquivo_salvar) {
    Paleta cores(arquivo_cores);

    int numCores = cores.obterTamanho();
    
    int divisor = 280/numCores;
    
    int lado = dimensao;

    Imagem mapa(lado, lado);
    
    for (int i = 0; i < lado; i++) {
        for (int j = 0; j < lado; j++) {
            int altitude = obterAltitude(i, j);
            int indice = altitude / divisor - 1;

            if (indice < 0) indice = 0;
            if (indice >= numCores) indice = numCores - 1;
            
            Cor corAltitude = cores.obterCor(indice);

            bool deveSombrear = false;

            if (i > 0 && j > 0) {
                if (altitude < obterAltitude(i - 1, j - 1)) {
                    deveSombrear = true;
                }
            } else if (i == 0 && j > 0) {
                if (altitude < obterAltitude(i, j - 1)) {
                    deveSombrear = true;
                }
            } else if (i > 0 && j == 0) {
                if (altitude < obterAltitude(i - 1, j)) {
                    deveSombrear = true;
                }
            }

            if (deveSombrear) {
                corAltitude.r = (int)(corAltitude.r * 0.7);
                corAltitude.g = (int)(corAltitude.g * 0.7);
                corAltitude.b = (int)(corAltitude.b * 0.7);
            }

            mapa.setPixel(i, j, corAltitude);
        }
    }

    mapa.salvarPPM(arquivo_salvar);
}