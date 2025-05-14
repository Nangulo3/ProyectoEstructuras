#include "../headers/Proyeccion2D.h"
#include <iostream>

// Constructor vacío
Proyeccion2D::Proyeccion2D() : imagenProyectada(1, 1, 255, "proyeccion.pgm") {}

void Proyeccion2D::generarProyeccion(Volumen &volumen, const std::string &criterio, char direccion, const std::string &archivoSalida)
{
    if (criterio != "promedio" && criterio != "minimo" && criterio != "maximo")
    {
        throw std::invalid_argument("Error: Criterio de proyección no válido.");
    }

    Imagen imagenProyectada = Imagen();

    if (direccion == 'x')
    {
        imagenProyectada = proyeccionX(volumen, criterio);
    }
    else if (direccion == 'y')
    {
        imagenProyectada = proyeccionY(volumen, criterio);
    }
    else if (direccion == 'z')
    {
        imagenProyectada = proyeccionZ(volumen, criterio);
    }
    else
    {
        throw std::invalid_argument("Dirección inválida");
    }

    this->imagenProyectada = imagenProyectada;
    imagenProyectada.guardarImagen(archivoSalida);
}

// Proyección en X
Imagen Proyeccion2D::proyeccionX(Volumen &volumen, const std::string &criterio) const
{
    int alto = volumen.getNumI();
    int ancho = volumen.getImagen(0).getAncho();
    int alturaPuntos = volumen.getImagen(0).getAlto();

    Imagen imProyectada(ancho, alto, volumen.getImagen(0).getMaxIntensidad(), "proyeccionX.pgm");

    if (criterio == "maximo")
    {
        for (int i = 0; i < alto; i++)
        {
            for (int x = 0; x < ancho; x++)
            {
                int puntoProyectado = volumen.getImagen(i).getPixel(x, 0);
                for (int p = 1; p < alturaPuntos; p++)
                {
                    if (puntoProyectado < volumen.getImagen(i).getPixel(x, p))
                    {
                        puntoProyectado = volumen.getImagen(i).getPixel(x, p);
                    }
                }
                imProyectada.setPixel(x, i, puntoProyectado);
            }
        }
    }

    if (criterio == "minimo")
    {
        for (int i = 0; i < alto; i++)
        {
            for (int x = 0; x < ancho; x++)
            {
                int puntoProyectado = volumen.getImagen(i).getPixel(x, 0);
                for (int p = 1; p < alturaPuntos; p++)
                {
                    if (puntoProyectado > volumen.getImagen(i).getPixel(x, p))
                    {
                        puntoProyectado = volumen.getImagen(i).getPixel(x, p);
                    }
                }
                imProyectada.setPixel(x, i, puntoProyectado);
            }
        }
    }

    if (criterio == "promedio")
    {
        for (int x = 0; x < ancho; x++)
        {
            for (int y = 0; y < alturaPuntos; y++)
            {
                int suma = 0;
                for (int i = 0; i < alto; i++)
                {
                    suma += volumen.getImagen(i).getPixel(x, y);
                }
                int puntoProyectado = suma / alto;
                imProyectada.setPixel(x, y, puntoProyectado);
            }
        }
    }

    return imProyectada;
}

// Proyección en Y
Imagen Proyeccion2D::proyeccionY(Volumen &volumen, const std::string &criterio) const
{
    int alto = volumen.getImagen(0).getAlto();
    int ancho = volumen.getNumI();
    int anchoFila = volumen.getImagen(0).getAncho();

    Imagen imProyectada(ancho, alto, volumen.getImagen(0).getMaxIntensidad(), "proyeccionY.pgm");

    if (criterio == "maximo")
    {
        for (int i = 0; i < volumen.getNumI(); i++)
        {
            for (int y = 0; y < alto; y++)
            {
                int max = volumen.getImagen(i).getPixel(0, y);
                for (int x = 1; x < anchoFila; x++)
                {
                    if (volumen.getImagen(i).getPixel(x, y) > max)
                    {
                        max = volumen.getImagen(i).getPixel(x, y);
                    }
                }
                imProyectada.setPixel(i, y, max);
            }
        }
    }

    if (criterio == "minimo")
    {
        for (int i = 0; i < volumen.getNumI(); i++)
        {
            for (int y = 0; y < alto; y++)
            {
                int min = volumen.getImagen(i).getPixel(0, y);
                for (int x = 1; x < anchoFila; x++)
                {
                    if (volumen.getImagen(i).getPixel(x, y) < min)
                    {
                        min = volumen.getImagen(i).getPixel(x, y);
                    }
                }
                imProyectada.setPixel(i, y, min);
            }
        }
    }

    if (criterio == "promedio")
    {
        for (int i = 0; i < volumen.getNumI(); i++)
        {
            for (int y = 0; y < alto; y++)
            {
                int suma = 0;
                for (int x = 0; x < anchoFila; x++)
                {
                    suma += volumen.getImagen(i).getPixel(x, y);
                }
                int puntoProyectado = suma / anchoFila;
                imProyectada.setPixel(i, y, puntoProyectado);
            }
        }
    }

    return imProyectada;
}

// Proyección en Z
Imagen Proyeccion2D::proyeccionZ(Volumen &volumen, const std::string &criterio) const
{
    int alto = volumen.getImagen(0).getAlto();
    int ancho = volumen.getImagen(0).getAncho();
    int profundidadPuntos = volumen.getNumI();

    Imagen imProyectada(ancho, alto, volumen.getImagen(0).getMaxIntensidad(), "proyeccionZ.pgm");

    if (criterio == "maximo")
    {
        for (int y = 0; y < alto; y++)
        {
            for (int x = 0; x < ancho; x++)
            {
                int max = volumen.getImagen(0).getPixel(x, y);
                for (int i = 1; i < profundidadPuntos; i++)
                {
                    if (volumen.getImagen(i).getPixel(x, y) > max)
                    {
                        max = volumen.getImagen(i).getPixel(x, y);
                    }
                }
                imProyectada.setPixel(x, y, max);
            }
        }
    }

    return imProyectada;
}

// Método para obtener la imagen proyectada
Imagen Proyeccion2D::getImagenProyectada() const
{
    return this->imagenProyectada;
}
