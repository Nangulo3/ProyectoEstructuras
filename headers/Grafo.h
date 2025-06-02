#ifndef GRAFO_H
#define GRAFO_H

#include "NodoPixel.h"
#include "Pixel.h"
#include <vector>
#include <tuple>
#include <string>

typedef std::pair<std::pair<int, int>, long long> Arista;

class Grafo
{
private:
    int ancho, alto;
    std::vector<std::vector<NodoPixel>> nodos;
    std::vector<std::vector<std::vector<Arista>>> adyacencia;

    void PixelANodoPixel(const std::vector<std::vector<Pixel>> &matrizPixeles, int alto, int ancho);
    void construirAdyacencia(int alto, int ancho);

public:
    Grafo(const std::vector<std::vector<Pixel>> &matrizPixeles, int alto, int ancho);
    Grafo();
    void segmentar(const std::vector<std::tuple<int, int, int>> &semillas);
    std::vector<std::vector<NodoPixel>> getNodoPixeles();
};

#endif
