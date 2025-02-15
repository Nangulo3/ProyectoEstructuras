#include <iostream>
#include <string>
#include <vector>

using namespace std;

void mostrar_ayuda(string comando = "") {
    vector<pair<string, string>> comandos = {
        {"ayuda", "Muestra la lista de comandos disponibles. Uso: ayuda [comando]"},
        {"salir", "Cierra la aplicación. Uso: salir"},
        {"cargar_imagen", "Carga una imagen PGM en memoria. Uso: cargar_imagen nombre.pgm"},
        {"info_imagen", "Muestra información de la imagen cargada. Uso: info_imagen"},
        {"cargar_volumen", "Carga en memoria la serie ordenada de imagenes. Uso: cargar_volumen nombre_basexx.pgm n_im"},
        {"proyeccion2D", "Genera una proyección 2D. Uso: proyeccion2D dirección criterio archivo.pgm"},
        {"codificar_imagen", "Codifica la imagen usando Huffman. Uso: codificar_imagen archivo.huf"},
        {"decodificar_archivo", "Decodifica un archivo Huffman. Uso: decodificar_archivo archivo.huf salida.pgm"},
        {"segmentar", "Segmenta una imagen. Uso: segmentar salida.pgm sx1 sy1 sl1 ..."}
    };

    if (!comando.empty()) {
        for (int i = 0; i < comandos.size(); i++) {
            if (comandos[i].first == comando) {
                cout << comandos[i].first << ": " << comandos[i].second << endl;
                return;
            }
        }
        cout << "Error: Comando no encontrado. Use 'ayuda' para ver los disponibles." << endl;
    } else {
        cout << "Lista de comandos disponibles:" << endl;
        for (int i = 0; i < comandos.size(); i++) {
            cout << "  " << comandos[i].first << ": " << comandos[i].second << endl;
        }
    }
}

void ejecutar_comando(string entrada) {
    vector<string> partes;
    string palabra;
    for (char c : entrada) {
        if (c == ' ') {
            if (!palabra.empty()) {
                partes.push_back(palabra);
                palabra.clear();
            }
        } else {
            palabra += c;
        }
    }
    if (!palabra.empty()) partes.push_back(palabra);
    if (partes.empty()) return;

    string comando = partes[0];
    partes.erase(partes.begin());

    if (comando == "ayuda") {
        mostrar_ayuda(partes.empty() ? "" : partes[0]);
    } else if (comando == "salir") {
        cout << "Saliendo..." << endl;
        exit(0);
    } else if (comando == "cargar_imagen" && partes.size() != 1) {
        cout << "Para cargar una imagen, use el formato cargar_imagen nombre_imagen.pgm" << endl;
    } else if (comando == "cargar_imagen" && partes.size() == 1) {
        cout << "Cargando imagen: " << partes[0] << endl;        
    } else if (comando == "info_imagen" && partes.size()!=0) {
        cout << "Recuerde usar el comando info_imagen de la forma info_imagen." << endl;  
    } else if (comando == "info_imagen") {
            cout << "Mostrando información de la imagen." << endl;  
    } else if (comando == "proyeccion2D" && partes.size() != 3) {
        cout << "Recuerde, para usar el comando proyeccion2D, se debe usar el formato: proyeccion2D dirección criterio archivo.pgm" << endl;
    } else if (comando == "proyeccion2D" && partes.size() == 3) {
        cout << "Generando proyección 2D y guardando en: " << partes[2] << endl;    
    } else if (comando == "codificar_imagen" && partes.size() != 1) {
        cout << "Recuerde, para usar el comando codificar_imagen, se debe usar el formato: codificar_imagen archivo.huf" << endl;
    } else if (comando == "codificar_imagen" && partes.size() == 1) {
        cout << "Codificando imagen y guardando en: " << partes[0] << endl;        
    } else if (comando == "decodificar_archivo" && partes.size() != 2) {
        cout << "Recuerde, para usar el comando decodificar_archivo, se debe usar el formato: decodificar_archivo archivo.huf salida.pgm" << endl;
    } else if (comando == "decodificar_archivo" && partes.size() == 2) {
        cout << "Decodificando " << partes[0] << " y guardando en " << partes[1] << endl;
    } else if (comando == "segmentar" && (partes.size() < 4 || partes.size() % 3 != 1)) {
        cout << "Recuerde que para usar el comando segmentar, se debe usar el formato: segmentar salida.pgm sx1 sy1 sl1 (para s múltiplos del 3) "<< endl;
    } else if (comando == "segmentar" && partes.size() >= 4 && partes.size() % 3 == 1) {
        cout << "Segmentando imagen y guardando en: " << partes[0] << endl;
        
    
    } else if (comando == "cargar_volumen" && partes.size() != 2) {
            cout << "Recuerde que para usar el comando cargar_volumen, se debe usar el formato: cargar_volumen nombre_basexx.pgm n_im"<< endl;
    } else if (comando == "cargar_volumen" && partes[0].size() > 17) {
            cout << "Recuerde que el numero de imagen debe estar entre 1 y 99"<< endl;     
        } else if (comando == "cargar_volumen" && partes.size() == 2) {
            cout << "El volumen "<< partes[0] << " ha sido cargado "  << endl;
    } else {
        cout << "Error: Comando no reconocido o mal uso. Use 'ayuda' para más detalles." << endl;
    }
}

int main() {
    cout << "Sistema de procesamiento de imágenes. Use 'ayuda' para ver los comandos." << endl;
    while (true) {
        cout << "$ ";
        string entrada;
        getline(cin, entrada);
        ejecutar_comando(entrada);
    }
    return 0;
}
