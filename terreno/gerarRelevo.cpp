#include "../paleta/paleta.h"
#include "../imagem/imagem.h"
#include "terreno.h"
#include <iostream>

void Terreno::gerarRelevoPPM(const std::string arquivo_cores, const std::string arquivo_salvar) {
    Paleta cores(arquivo_cores);

    int numCores = cores.obterTamanho();
    int divisor = 140/numCores;
    
    int lado = dimensao;

    Imagem mapa(lado, lado);
    

    for (int i = 0; i < lado; i++) {
        for (int j = 0; j < lado; j++) {
            int altitude = obterAltitude(i, j);
            int indice = altitude / divisor - 1;

            if (indice < 0) indice = 0;
            if (indice >= numCores) indice = numCores - 1;
            
            Cor corAltitude = cores.obterCor(indice);
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
    t.gerarRelevoPPM("./paleta/cores.hex", "./mapa.ppm");

    return 0;
}