#include "../headers/NodoPixel.h"
#include <climits> // Para LLONG_MAX

NodoPixel::NodoPixel()
    : pixel(Pixel(0, 255))
{
    etiqueta = -1;
    distancia = LLONG_MAX;
    visitado = false;
}

NodoPixel::NodoPixel(Pixel pixel)
    : pixel(pixel)
{
    etiqueta = -1;
    distancia = LLONG_MAX;
    visitado = false;
}

long long NodoPixel::getDistancia() const
{
    return distancia;
}

void NodoPixel::setDistancia(long long d)
{
    distancia = d;
}

bool NodoPixel::isVisitado() const
{
    return visitado;
}

void NodoPixel::setVisitado(bool v)
{
    visitado = v;
}

int NodoPixel::getEtiqueta() const
{
    return etiqueta;
}

void NodoPixel::setEtiqueta(int e)
{
    etiqueta = e;
}

Pixel NodoPixel::getPixel() const
{
    return pixel;
}

bool NodoPixel::operator>(const NodoPixel &other) const
{
    return distancia > other.distancia;
}
