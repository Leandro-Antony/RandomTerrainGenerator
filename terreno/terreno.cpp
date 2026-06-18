#include <fstream>
#include <cstdlib>
#include <ctime>
#include "terreno.h"
#include <cmath>

Terreno::Terreno() {
    dimensao = 0;
    terreno = nullptr;
}

Terreno::Terreno(int n) {
    dimensao = std::pow(2, n) + 1;

    // metodo de geração de altura

    terreno = new int[dimensao*dimensao];
}

Terreno::~Terreno() {
    dimensao = 0;
    delete[] terreno;
    terreno = nullptr;
}

int randomize(int media = 0) {
    srand(time(0));
    int min, max, rnd;
    if(media = 0){
        min = 1;
        max = 100;
    } else {
        min = -0.5;
        max = 0.5;
    }
    rnd = (rand() % (max - min + 1)) + min;
    return media + rnd;
}

void Terreno::gerarAltitudes(int d, int rug) {
    
    terreno[0] = 
}