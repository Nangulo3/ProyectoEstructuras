#include "Grafo.h"
#include <queue>
#include <climits>
#include <fstream>

Grafo::Grafo(const std::vector<std::vector<Pixel>> &matrizPixeles, int alto, int ancho)
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
            int intensidad1 = nodos[y][x].getPixel().getIntensidad(); // Suponiendo que pixel es público

            for (int dir = 0; dir < 4; ++dir)
            {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx >= 0 && nx < ancho && ny >= 0 && ny < alto)
                {
                    int intensidad2 = nodos[ny][nx].getPixel().getIntensidad();
                    long long peso = std::abs(intensidad1 - intensidad2);
                    adyacencia[y][x].push_back({{nx, ny}, peso});
                }
            }
        }
    }
}

void Grafo::segmentar(const std::vector<std::tuple<int, int, int>> &semillas)
{
    // Paso 1: Inicializar todos los nodos
    for (int y = 0; y < alto; ++y)
    {
        for (int x = 0; x < ancho; ++x)
        {
            nodos[y][x].setDistancia(LLONG_MAX); // Infinito
            nodos[y][x].setVisitado(false);
            nodos[y][x].setEtiqueta(0); // Sin etiqueta
        }
    }

    // Paso 2: Cola de prioridad para Dijkstra (distancia, x, y, etiqueta)
    typedef std::tuple<long long, int, int, int> Estado;
    std::priority_queue<Estado, std::vector<Estado>, std::greater<Estado>> pq;

    // Paso 3: Insertar semillas en la cola
    for (const std::tuple<int, int, int> &semilla : semillas)
    {
        int x = std::get<0>(semilla);
        int y = std::get<1>(semilla);
        int etiqueta = std::get<2>(semilla);

        if (x >= 0 && x < ancho && y >= 0 && y < alto)
        {
            nodos[y][x].setDistancia(0);
            nodos[y][x].setEtiqueta(etiqueta);
            pq.emplace(0, x, y, etiqueta); // emplace es más eficiente que push
        }
    }

    // Paso 4: Ejecutar Dijkstra multi-fuente
    while (!pq.empty())
    {
        // Extraer el nodo con menor distancia (min-heap)
        Estado estadoActual = pq.top();
        pq.pop();

        long long distancia = std::get<0>(estadoActual);
        int x = std::get<1>(estadoActual);
        int y = std::get<2>(estadoActual);
        int etiqueta = std::get<3>(estadoActual);

        NodoPixel &actual = nodos[y][x];

        // Si ya fue visitado por otro camino más barato, se ignora
        if (actual.isVisitado())
            continue;

        // Se marca como visitado y se le asigna etiqueta definitiva
        actual.setVisitado(true);
        actual.setEtiqueta(etiqueta);

        // Paso 5: Explorar vecinos del nodo actual
        for (const Arista &vecino : adyacencia[y][x]) // Cada Arista (tupla) se ve {{x,y},peso}
        {
            int nx = vecino.first.first;    // El primer elemento del primer par: {{x,y},peso}--Primero:{x,y}--Primero.primero {x}
            int ny = vecino.first.second;   // Primero {x,y} --Primero.segundo {y}
            long long peso = vecino.second; // Segundo {peso}

            long long nuevoCosto = distancia + peso;

            NodoPixel &nodoVecino = nodos[ny][nx];

            // Si no ha sido visitado y encontramos un camino más barato
            if (!nodoVecino.isVisitado() && nuevoCosto < nodoVecino.getDistancia())
            {
                nodoVecino.setDistancia(nuevoCosto);
                nodoVecino.setEtiqueta(etiqueta);
                pq.push(std::make_tuple(nuevoCosto, nx, ny, etiqueta));
            }
        }
    }
}
