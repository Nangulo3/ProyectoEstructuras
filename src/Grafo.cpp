#include "Grafo.h"
#include <queue>
#include <climits>
#include <fstream>

Grafo::Grafo(const std::vector<std::vector<Pixel>> &matrizPixeles, int alto_, int ancho_)
{
    this->alto = alto;
    this->ancho = ancho;
    PixelANodoPixel(matrizPixeles, alto, ancho);
    construirAdyacencia(alto, ancho);
}

void Grafo::PixelANodoPixel(const std::vector<std::vector<Pixel>> &matrizPixeles, int alto, int ancho)
{
    nodos.resize(alto, std::vector<NodoPixel>(ancho));
    for (int y = 0; y < alto; y++)
    {
        for (int x = 0; x < ancho; x++)
        {
            nodos[y][x] = NodoPixel(matrizPixeles[y][x]);
        }
    }
}

void Grafo::construirAdyacencia(int alto, int ancho)
{
    adyacencia.resize(alto, std::vector<std::vector<Arista>>(ancho));

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int y = 0; y < alto; ++y)
    {
        for (int x = 0; x < ancho; ++x)
        {
            int intensidad1 = nodos[y][x].pixel.getIntensidad(); // Suponiendo que pixel es público

            for (int dir = 0; dir < 4; ++dir)
            {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx >= 0 && nx < ancho && ny >= 0 && ny < alto)
                {
                    int intensidad2 = nodos[ny][nx].pixel.getIntensidad();
                    long long peso = std::abs(intensidad1 - intensidad2);
                    adyacencia[y][x].push_back({{nx, ny}, peso});
                }
            }
        }
    }
}
