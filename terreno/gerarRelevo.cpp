#include "../paleta/paleta.h"
#include "../imagem/imagem.h"
#include "terreno.h"
#include <iostream>

void Terreno::gerarRelevoPPM(const std::string arquivo_cores, const std::string arquivo_salvar) {
    Paleta cores(arquivo_cores);

    int numCores = cores.obterTamanho();
    int divisor = 260/numCores;
    
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

int main() {

    int n = 0;
    std::cin >> n;
    Terreno t(n);
    t.salvarTerreno("terreno.txt");
    t.gerarRelevoPPM("../paleta/cores.hex", "./mapa.ppm");

    return 0;
}