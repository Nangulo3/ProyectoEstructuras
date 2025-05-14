#include "../headers/Volumen.h"
#include <iostream>

Volumen::Volumen(const std::string &nombreBase, int nImagenes)
{
  this->nombreBase = nombreBase;
  this->nImagenes = nImagenes;

  if (nImagenes <= 0 || nImagenes > 99)
  {
    throw std::invalid_argument(
        "Error: El número de imágenes debe estar entre 1 y 99.");
  }
}

std::vector<Imagen> Volumen::getImagenes() const
{
  return imagenes;
}

void Volumen::setImagenes(const std::vector<Imagen> &nuevasImagenes)
{
  imagenes = nuevasImagenes;
  setNum(nImagenes);
}

std::string Volumen::getNombre() const
{
  return nombreBase;
}

void Volumen::setNombre(const std::string &nombre)
{
  nombreBase = nombre;
}

int Volumen::getNumI() const
{
  return nImagenes;
}

void Volumen::setNum(int numero)
{
  if (numero <= 0 || numero > 99)
  {
    throw std::invalid_argument(
        "Error: El número de imágenes debe estar entre 1 y 99.");
  }
  nImagenes = numero;
}

void Volumen::cargarVolumen()
{
  imagenes.clear(); // Limpia el vector para cargar nuevas imágene
  for (int i = 0; i < nImagenes; i++)
  {
    std::string nombreImagen = nombreBase + std::to_string(i) + ".pgm";
    Imagen imagen(nombreImagen);
    imagenes.push_back(imagen);
  }
}

void Volumen::info_volumen() const
{
  if (imagenes.empty())
  {
    std::cout << "El volumen no tiene imágenes cargadas." << std::endl;
    return;
  }

  std::cout << "Nombre base: " << nombreBase << std::endl;
  std::cout << "Número de imágenes: " << nImagenes << std::endl;
  std::cout << "Dimensiones: " << imagenes[0].getAncho() << "x"
            << imagenes[0].getAlto() << std::endl;
}

Imagen Volumen::getImagen(int indice) const
{
  if (indice < 0 || indice >= imagenes.size())
  {
    throw std::out_of_range("Índice fuera de rango en getImagen");
  }
  return imagenes[indice];
}
