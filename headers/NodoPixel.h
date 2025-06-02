#ifndef NODO_PIXEL_H
#define NODO_PIXEL_H
#include "Pixel.h"

class NodoPixel
{
private:
    Pixel pixel;
    long long distancia;
    bool visitado;
    int etiqueta;

public:
    NodoPixel();
    NodoPixel(Pixel pixel);

    long long getDistancia() const;
    void setDistancia(long long d);

    bool isVisitado() const;
    void setVisitado(bool v);

    int getEtiqueta() const;
    void setEtiqueta(int e);

    Pixel getPixel() const;
    bool operator>(const NodoPixel &other) const;
};

#endif // NODO_PIXEL_H
