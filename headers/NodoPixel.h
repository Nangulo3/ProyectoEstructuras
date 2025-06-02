#ifndef NODO_PIXEL_H
#define NODO_PIXEL_H
#include "../headers/Pixel.h"

class NodoPixel
{
public:
    Pixel pixel;
    int etiqueta;  // Etiqueta (valor entre 1 y 255)
    int distancia; // Distancia mínima desde una semilla
    bool visitado; // Ya fue visitado por Dijkstra

    NodoPixel(Pixel pixel);
    NodoPixel();
    bool operator>(const NodoPixel &other) const;
    Pixel getPixel();
};

#endif
