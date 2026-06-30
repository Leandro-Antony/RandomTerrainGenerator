#include <iostream>
#include "./terreno/terreno.cpp"
#include "./paleta/paleta.cpp"
#include "./imagem/imagem.cpp"


int main() {
    
    Terreno t(10);
    t.gerarRelevoPPM("./paleta/cores.hex", "./mapa.ppm");

    return 0;
}