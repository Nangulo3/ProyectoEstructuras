#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "NodoHuffman.h"
#include <vector>
#include <queue>
#include <map>

class ArbolHuffman {
private:
    NodoHuffman* raiz; 

public:
    ArbolHuffman(const std::map<int, unsigned long>& frecuencias); 
    ~ArbolHuffman();  // Destructor para liberar la memoria del árbol

    void generarCodigos(NodoHuffman* nodo, const std::string& codigo, std::map<int,std::string>& codigos);
    static bool compararPorFrecuencia(NodoHuffman* a, NodoHuffman* b); // Requiere ser estatica para que se pueda usar como comparador en la cola de prioridad                                                                                   // Se usa como alternativa a una función lambda(Lo encontre mas legible)

    NodoHuffman* obtenerRaiz();
};

#endif 
