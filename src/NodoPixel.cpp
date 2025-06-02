#include "../headers/NodoPixel.h"
#include <climits>

NodoPixel::NodoPixel()
    : pixel(Pixel(0, 255)) // Se inicializa con coordenada 0 y valor máximo (por defecto seguro)
{
    etiqueta = 0;
    distancia = INT_MAX;
    visitado = false;
}

NodoPixel::NodoPixel(Pixel pixel)
    : pixel(pixel)
{
    etiqueta = 0;
    distancia = INT_MAX;
    visitado = false;
}

bool NodoPixel::operator>(const NodoPixel &other) const
{
    return distancia > other.distancia; // Para usar en priority_queue (menor distancia = mayor prioridad)
}

Pixel NodoPixel::getPixel()
{
    return this->pixel;
}
