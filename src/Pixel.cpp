#include "../headers/Pixel.h"
#include <stdexcept>

Pixel::Pixel(int intensidad, int maxIntensidad) : maxIntensidad(maxIntensidad)
{
    if (maxIntensidad < 0 || maxIntensidad > 255)
    {
        throw std::out_of_range("Error: Intensidad máxima inválida.");
    }
    if (intensidad < 0 || intensidad > maxIntensidad)
    {
        throw std::out_of_range("La intensidad del píxel debe estar entre 0 y el máximo permitido por la imagen.");
    }
    this->intensidad = intensidad;
}

Pixel::Pixel(int intensidad) : maxIntensidad(255)
{
    if (intensidad < 0 || intensidad > this->maxIntensidad)
    {
        throw std::out_of_range("Error: La intensidad del pixel está fuera de los parámetros.");
    }
    this->intensidad = intensidad;
}

int Pixel::getIntensidad() const
{
    return intensidad;
}

void Pixel::setIntensidad(int intensidad)
{
    if (intensidad < 0 || intensidad > 255)
    {
        throw std::out_of_range("La intensidad del píxel debe estar entre 0 y el máximo permitido por la imagen.");
    }
    this->intensidad = intensidad;
}

void Pixel::setMaxIntensidad(int maxIntensidad)
{
    if (maxIntensidad < 0 || maxIntensidad > 255)
    {
        throw std::out_of_range("La intensidad máxima debe estar entre 0 y 255");
    }
    this->maxIntensidad = maxIntensidad;
}

int Pixel::getMaxIntensidad() const
{
    return maxIntensidad;
}
