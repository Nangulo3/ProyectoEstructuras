#include "../headers/ArbolHuffman.h"
#include <iostream>

ArbolHuffman::ArbolHuffman(const std::map<int, unsigned long> &frecuencias)
{
  //(min-heap)
  std::priority_queue<NodoHuffman *, std::vector<NodoHuffman *>,
                      bool (*)(NodoHuffman *, NodoHuffman *)>
      colaPrioridad(compararPorFrecuencia);

  std::map<int, unsigned long>::const_iterator it;
  for (it = frecuencias.begin(); it != frecuencias.end(); it++)
  {
    colaPrioridad.push(new NodoHuffman(it->first, it->second));
  }

  while (colaPrioridad.size() > 1)
  {
    NodoHuffman *izquierda = colaPrioridad.top();
    colaPrioridad.pop();
    NodoHuffman *derecha = colaPrioridad.top();
    colaPrioridad.pop();

    // Crear un nuevo nodo interno con las dos menores frecuencias
    NodoHuffman *nodoInterno = new NodoHuffman(izquierda, derecha);
    colaPrioridad.push(nodoInterno);
  }

  raiz = colaPrioridad.top();
}

ArbolHuffman::~ArbolHuffman() { delete raiz; }

bool ArbolHuffman::compararPorFrecuencia(NodoHuffman *a, NodoHuffman *b)
{
  bool aEsMayor = (a->frecuencia) > (b->frecuencia);
  return aEsMayor; // Ordena de menor a mayor frecuencia
}

void ArbolHuffman::generarCodigos(NodoHuffman *nodo, const std::string &codigo,
                                  std::map<int, std::string> &codigos)
{
  if (nodo == nullptr)
  {
    return; // Es necesario verificar porque puede que haya nodos con un solo
            // hijo y no por eso es un nodo hoja.
  }

  if (nodo->izquierda == nullptr && nodo->derecha == nullptr)
  {
    codigos[nodo->intensidad] =
        codigo; // Cuando es un nodo hoja, se asigna el código
  }

  // Llamadas recursivas para los nodos izquierdo y derecho
  generarCodigos(nodo->izquierda, codigo + "0", codigos);
  generarCodigos(nodo->derecha, codigo + "1", codigos);
}

NodoHuffman *ArbolHuffman::obtenerRaiz() { return raiz; }
