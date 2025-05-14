#ifndef VOLUMEN_H
#define VOLUMEN_H

#include "Imagen.h"
#include <stdexcept>
#include <string>
#include <vector>

class Volumen {
private:
  std::string nombreBase;
  int nImagenes;
  std::vector<Imagen> imagenes;

public:

  Volumen(const std::string& nombreBase, int nImagenes);


  std::vector<Imagen> getImagenes() const;  
  std::string getNombre() const;            
  int getNumI() const;                      


  void setImagenes(const std::vector<Imagen>& nuevasImagenes);
  void setNombre(const std::string& nombre);
  void setNum(int numero);

  void info_volumen() const;
  void cargarVolumen();

  Imagen getImagen(int numero) const;
};

#endif
