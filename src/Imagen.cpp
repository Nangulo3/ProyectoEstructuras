#include "../headers/Imagen.h"
#include <fstream>
#include <iostream>
#include <sstream>

Imagen::Imagen() : nombreImagen(""), ancho(0), alto(0), maxIntensidad(255), matrizPixeles(1, std::vector<Pixel>(1, Pixel(0, 255))) {}

Imagen::Imagen(int ancho, int alto, int maxIntensidad, const std::string &nombreImagen)
{
    this->ancho = ancho;
    this->alto = alto;
    this->maxIntensidad = maxIntensidad;
    this->nombreImagen = nombreImagen;

    if (ancho <= 0 || alto <= 0 || maxIntensidad <= 0 || maxIntensidad > 255)
    {
        throw std::invalid_argument("Error: Dimensiones o intensidad máxima inválidas.");
    }

    matrizPixeles = std::vector<std::vector<Pixel>>(alto, std::vector<Pixel>(ancho, Pixel(0, maxIntensidad)));
    setMaxIntensidad(maxIntensidad);
}

Imagen::Imagen(const std::string &nombreImagen)
{
    cargarDesdeArchivo(nombreImagen);
}

int Imagen::getAncho() const
{
    return ancho;
}

int Imagen::getAlto() const
{
    return alto;
}

int Imagen::getMaxIntensidad() const
{
    return maxIntensidad;
}

std::string Imagen::getNombreImagen() const
{
    return nombreImagen;
}

void Imagen::setMaxIntensidad(int intensidad)
{
    if (intensidad < 0 || intensidad > 255)
    {
        throw std::out_of_range("Error: Intensidad máxima fuera de rango.");
    }
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            matrizPixeles[i][j].setMaxIntensidad(intensidad);
        }
    }
}

void Imagen::setNombreImagen(const std::string &nombre)
{
    nombreImagen = nombre;
}

int Imagen::getPixel(int x, int y) const
{
    if (x < 0 || x >= ancho || y < 0 || y >= alto)
    {
        throw std::out_of_range("Error: Coordenadas fuera de los límites de la imagen.");
    }
    return matrizPixeles[y][x].getIntensidad();
}

void Imagen::setPixel(int x, int y, int intensidad)
{
    if (x < 0 || x >= ancho || y < 0 || y >= alto)
    {
        throw std::out_of_range("Error: Coordenadas fuera de los límites de la imagen.");
    }
    matrizPixeles[y][x].setIntensidad(intensidad);
}

void Imagen::cargarDesdeArchivo(const std::string &nombreArchivo)
{
    std::ifstream archivo(nombreArchivo);

    if (!archivo)
    {
        throw std::runtime_error("Error: No se pudo abrir el archivo " + nombreArchivo);
    }

    std::string tipo;
    archivo >> tipo;

    if (tipo != "P2")
    {
        throw std::runtime_error("Error: Formato de imagen no soportado.");
    }

    std::string linea;
    while (archivo.peek() == '#')
    {
        std::getline(archivo, linea);
    }

    int w, h, mI;
    if (!(archivo >> w >> h >> mI))
    {
        throw std::runtime_error("Error: No se pudieron leer las dimensiones o la intensidad máxima.");
    }

    if (w <= 0 || h <= 0 || mI < 0 || mI > 255)
    {
        throw std::runtime_error("Error: Dimensiones o intensidad máxima inválidas.");
    }

    this->ancho = w;
    this->alto = h;
    this->maxIntensidad = mI;
    this->nombreImagen = nombreArchivo;
    this->matrizPixeles = std::vector<std::vector<Pixel>>(alto, std::vector<Pixel>(ancho, Pixel(0)));

    for (int y = 0; y < alto; ++y)
    {
        for (int x = 0; x < ancho; ++x)
        {
            int intensidad;
            if (!(archivo >> intensidad))
            {
                throw std::runtime_error("Error: El archivo no tiene suficientes datos.");
            }
            if (intensidad < 0 || intensidad > maxIntensidad)
            {
                throw std::runtime_error("Error: Intensidad de píxel fuera de rango.");
            }
            matrizPixeles[y][x] = Pixel(intensidad);
        }
    }

    archivo.close();
}

void Imagen::guardarImagen(const std::string &nombreArchivo) const
{
    std::ofstream archivo(nombreArchivo);
    if (!archivo)
    {
        std::cerr << "Error: No se pudo crear el archivo " << nombreArchivo << std::endl;
    }

    archivo << "P2\n";
    archivo << ancho << " " << alto << "\n";
    archivo << maxIntensidad << "\n";

    for (int y = 0; y < alto; y++)
    {
        for (int x = 0; x < ancho; x++)
        {
            archivo << matrizPixeles[y][x].getIntensidad() << " ";
        }
        archivo << "\n";
    }
}

void Imagen::guardarImagen(const std::string &nombreArchivo, std::vector<std::vector<NodoPixel>> matriz) const
{
    std::ofstream archivo(nombreArchivo);
    if (!archivo)
    {
        std::cerr << "Error: No se pudo crear el archivo " << nombreArchivo << std::endl;
    }

    archivo << "P2\n";
    archivo << ancho << " " << alto << "\n";
    archivo << maxIntensidad << "\n";

    for (int y = 0; y < alto; y++)
    {
        for (int x = 0; x < ancho; x++)
        {
            archivo << matriz[y][x].getEtiqueta() << " "; // Las etiquetas fueron llenadas a la hora de segmentar
        }
        archivo << "\n";
    }
}

void Imagen::infoImagen() const
{
    std::cout << "Imagen: " << nombreImagen << "\n";
    std::cout << "Dimensiones: " << ancho << "x" << alto << "\n";
    std::cout << "Intensidad máxima: " << maxIntensidad << "\n";
}

void Imagen::contarFrecuencias(std::map<int, unsigned long> &frecuencias) const
{
    for (int y = 0; y < alto; y++)
    {
        for (int x = 0; x < ancho; x++)
        {
            int valor = matrizPixeles[y][x].getIntensidad();
            frecuencias[valor]++; // El mapa encuentra el "valor" de intensidad (Llave) e incrementa la frecuencia (el dato).
        }
    }
}

void Imagen::codificarImagen(const std::string &archivoSalida)
{

    std::map<int, unsigned long> frecuencias;
    contarFrecuencias(frecuencias);         // LLenar mapa de frecuencias, llave intensidad, dato frecuencia
    ArbolHuffman arbolHuffman(frecuencias); // Crear el árbol de Huffman con el mapa de frecuencias
    std::map<int, std::string> codigos;
    arbolHuffman.generarCodigos(arbolHuffman.obtenerRaiz(), "", codigos); // Crear mapa de codigos con la función generarCodigos recursiva del arbol, llave intensidad, dato código

    std::ofstream archivoSalidaBinario(archivoSalida, std::ios::binary);
    if (!archivoSalidaBinario)
    {
        throw std::runtime_error("Error al abrir el archivo de salida.");
    }

    unsigned short ancho = this->ancho;                                            // W
    unsigned short alto = this->alto;                                              // H
    unsigned char maxIntensidad = static_cast<unsigned char>(this->maxIntensidad); // MaxIntensidad

    archivoSalidaBinario.write(reinterpret_cast<const char *>(&ancho), sizeof(ancho));                 // W
    archivoSalidaBinario.write(reinterpret_cast<const char *>(&alto), sizeof(alto));                   // H
    archivoSalidaBinario.write(reinterpret_cast<const char *>(&maxIntensidad), sizeof(maxIntensidad)); // M

    // F0, F1, ..., FM
    for (int i = 0; i <= maxIntensidad; ++i)
    {
        unsigned long frecuencia = 0; // Por defecto es 0 por si no hay esa en el mapa (en la imagen)

        std::map<int, unsigned long>::iterator it = frecuencias.find(i);

        if (it != frecuencias.end())
        {
            frecuencia = it->second;
        }
        archivoSalidaBinario.write(reinterpret_cast<const char *>(&frecuencia), sizeof(frecuencia)); // Para cada intensidad de 0 a M, se escribe la frecuencia (Si no se encuentra el valor frecuencia no cambia y queda en 0)
    }

    unsigned char buffer = 0;
    int bitCount = 0;

    for (int y = 0; y < alto; ++y)
    {
        for (int x = 0; x < ancho; ++x)
        {
            int intensidad = this->matrizPixeles[y][x].getIntensidad();
            std::string codigo = codigos.at(intensidad); // El segundo mapa tiene como llave la intensidad y como dato el código

            for (int i = 0; i < codigo.length(); ++i)
            {
                char bit = codigo[i];
                if (bit == '1')
                {
                    buffer |= (1 << (7 - bitCount));
                }
                bitCount++;
                if (bitCount == 8)
                {
                    archivoSalidaBinario.put(buffer);
                    buffer = 0;
                    bitCount = 0;
                }
            }
        }
    }

    if (bitCount > 0)
    {
        archivoSalidaBinario.put(buffer);
    }
    archivoSalidaBinario.close();
}

void Imagen::decodificarImagen(const std::string &archivoEntrada, const std::string &archivoSalida)
{

    std::ifstream archivoEntradaBinario(archivoEntrada, std::ios::binary);
    if (!archivoEntradaBinario)
    {
        throw std::runtime_error("El archivo no ha podido ser decodificado");
    }

    unsigned short ancho, alto;  // W H
    unsigned char maxIntensidad; // M

    archivoEntradaBinario.read(reinterpret_cast<char *>(&ancho), sizeof(ancho));
    archivoEntradaBinario.read(reinterpret_cast<char *>(&alto), sizeof(alto));
    archivoEntradaBinario.read(reinterpret_cast<char *>(&maxIntensidad), sizeof(maxIntensidad));

    this->ancho = static_cast<unsigned short>(ancho);
    this->alto = static_cast<unsigned short>(alto);
    this->maxIntensidad = maxIntensidad;

    std::map<int, unsigned long> frecuencias;
    for (int i = 0; i <= maxIntensidad; ++i)
    {
        unsigned long frecuencia = 0;
        archivoEntradaBinario.read(reinterpret_cast<char *>(&frecuencia), sizeof(frecuencia));
        frecuencias[i] = frecuencia;
    }

    ArbolHuffman arbolHuffman(frecuencias); // Crear el árbol de Huffman con el mapa de frecuencias
    std::map<int, std::string> codigos;
    arbolHuffman.generarCodigos(arbolHuffman.obtenerRaiz(), "", codigos); // Llenar mapa de codigos

    // Crear la matriz de píxeles
    std::vector<std::vector<Pixel>> matrizPixeles(this->alto, std::vector<Pixel>(this->ancho, Pixel(0, maxIntensidad)));

    std::string codigoActual = "";
    int pixelCount = 0;

    unsigned char buffer = 0;

    while (archivoEntradaBinario.read(reinterpret_cast<char *>(&buffer), sizeof(buffer)))
    {
        for (int i = 7; i >= 0; --i)
        {
            bool bit = (buffer >> i) & 1;
            codigoActual += bit ? '1' : '0';

            // Buscar en el árbol de Huffman si tenemos un código completo
            for (std::map<int, std::string>::iterator it = codigos.begin(); it != codigos.end(); ++it)
            {
                if (codigoActual == it->second)
                {
                    // Buscar codigo completo en el mapa de codigos
                    int intensidad = it->first;
                    int y = pixelCount / ancho; // Calcular la fila
                    int x = pixelCount % ancho; // Calcular la columna

                    // LLenar matriz
                    matrizPixeles[y][x] = Pixel(intensidad, maxIntensidad);
                    pixelCount++;

                    codigoActual = "";
                    break;
                }
            }

            // Cuando se decodifican todos los pixeles se sale de ambos bucles
            if (pixelCount == ancho * alto)
            {
                break;
            }
        }
        if (pixelCount == ancho * alto)
        {
            break;
        }
    }

    archivoEntradaBinario.close();

    guardarImagen(archivoSalida); // Se guarda la imagen decodificada en el archivo de salida
}

void Imagen::segmentacion(std::vector<std::tuple<int, int, int>> Semillas, const std::string &nombreArchivo)
{
    Grafo g = Grafo(matrizPixeles, alto, ancho); // Crea el grafo, aqui se genera la matriz de NodoPixeles y ademas se crea la lista de adyacencia
    this->grafo = g;
    grafo.segmentar(Semillas); // Se llenan los atributos etiqueta para despues ser escritos en el archivo
    guardarImagen(nombreArchivo, grafo.getNodoPixeles());
}