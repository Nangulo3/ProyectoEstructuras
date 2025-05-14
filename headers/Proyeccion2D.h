#ifndef PROYECCION2D_H
#define PROYECCION2D_H

#include "Volumen.h"

class Proyeccion2D {
private:
    Imagen imagenProyectada; 

public:
    Proyeccion2D();

    void generarProyeccion(Volumen& volumen, const std::string& criterio, char direccion, const std::string& archivoSalida);

    Imagen proyeccionX(Volumen& volumen, const std::string& criterio) const;
    Imagen proyeccionY(Volumen& volumen, const std::string& criterio) const;
    Imagen proyeccionZ(Volumen& volumen, const std::string& criterio) const;

    Imagen getImagenProyectada() const;
};

#endif // PROYECCION2D_H

