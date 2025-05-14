#ifndef NODOHUFMANN_H
#define NODOHUFMANN_H

#include <string>

class NodoHuffman {
public:
    unsigned long frecuencia;          
    int intensidad;          // Valor de la intensidad (símbolo a codificar)
    NodoHuffman* izquierda;  
    NodoHuffman* derecha;    

    // Constructor para un nodo hoja (símbolo)
    NodoHuffman(int intensidad, unsigned long frecuencia);

    // Constructor para un nodo interno
    NodoHuffman(NodoHuffman* izquierda, NodoHuffman* derecha);
    
};

#endif // HUFFMANNODE_H
