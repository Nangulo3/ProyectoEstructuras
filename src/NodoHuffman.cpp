#include "../headers/NodoHuffman.h"

// Constructor para un nodo hoja (símbolo)
NodoHuffman::NodoHuffman(int intensidad, unsigned long frecuencia)
{
    this->intensidad = intensidad;
    this->frecuencia = frecuencia;
    this->izquierda = nullptr;
    this->derecha = nullptr;
}

NodoHuffman::NodoHuffman(NodoHuffman *izquierda, NodoHuffman *derecha)
{
    this->izquierda = izquierda;
    this->derecha = derecha;
    this->frecuencia = izquierda->frecuencia + derecha->frecuencia;
    this->intensidad = -1; // Para los nodos internos, la intensidad no tiene sentido
}
