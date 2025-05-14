#ifndef IMAGEN_H
#define IMAGEN_H

#include "Pixel.h"
#include <stdexcept>
#include <string>
#include <vector>
#include "ArbolHuffman.h"
#include <map>

class Imagen {
private:
  std::string nombreImagen;
  int ancho;
  int alto;
  int maxIntensidad;
  std::vector<std::vector<Pixel>> matrizPixeles;

public:
  Imagen(int ancho, int alto, int maxIntensidad,
         const std::string &nombreImagen);
  Imagen(const std::string &nombreImagen);
  Imagen();

// Todo se maneja con constantes y referencia porque habian problemas a la hora de generar las proyecciones. 
  int getAncho() const;
  int getAlto() const;
  int getMaxIntensidad() const;
  std::string getNombreImagen() const;

  void setMaxIntensidad(int intensidad);
  void setNombreImagen(const std::string &nombre);

  int getPixel(int x, int y) const;
  void setPixel(int x, int y, int intensidad);

  // Archivos
  void cargarDesdeArchivo(const std::string &nombreArchivo);
  void guardarImagen(const std::string &nombreArchivo) const;

  void infoImagen() const;

 // Huffman
  void contarFrecuencias(std::map<int, unsigned long>& frecuencias) const;
  void codificarImagen(const std::string& archivoSalida);
  void decodificarImagen(const std::string& archivoEntrada, const std::string& archivoSalida); // .huff a .pgm
};

#endif