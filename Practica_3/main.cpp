#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
using namespace std;

#include "RLE.h"
#include "LZ78.h"
#include "ENCRIPTACION.h"


// Lee todo el contenido de un archivo de texto y lo devuelve como string
string leerArchivoTxt(const string &ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo.");
    }

    string contenido = "";
    string linea;
    bool primeraLinea = true;
    while (getline(archivo, linea)) {
        if (!primeraLinea) contenido += '\n';
        contenido += linea;
        primeraLinea = false;
    }

    archivo.close();
    return contenido;
}

// Pregunta al usuario si quiere ingresar el texto por teclado o desde un archivo (version RLE, con string)
string obtenerTexto() {
    int opcion;
    cout << "Como desea ingresar el texto?" << endl;
    cout << "1. Escribirlo por teclado" << endl;
    cout << "2. Leerlo desde un archivo .txt" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cin.ignore();

    if (opcion == 1) {
        string texto;
        cout << "Ingrese el texto: ";
        getline(cin, texto);
        return texto;
    } else if (opcion == 2) {
        string rutaArchivo;
        cout << "Ingrese la ruta del archivo .txt: ";
        getline(cin, rutaArchivo);
        string texto = leerArchivoTxt(rutaArchivo);
        cout << "Texto leido: " << texto << endl;
        return texto;
    } else {
        throw invalid_argument("Opcion de entrada invalida.");
    }
}


// Lee una linea desde teclado caracter por caracter, sin usar string, en un arreglo dinamico
char* leerLineaTeclado(int &Longitud) {
    int capacidad = 0, cantidad = 0;
    char *buffer = nullptr;
    char c;

    while (cin.get(c)) {
        if (c == '\n') break;
        if (cantidad == capacidad) {
            int nuevaCapacidad = (capacidad == 0) ? 32 : capacidad * 2;
            char *nuevo = new char[nuevaCapacidad];
            for (int i = 0; i < cantidad; ++i) nuevo[i] = buffer[i];
            delete[] buffer;
            buffer = nuevo;
            capacidad = nuevaCapacidad;
        }
        buffer[cantidad] = c;
        cantidad++;
    }

    char *conNulo = new char[cantidad + 1];
    for (int i = 0; i < cantidad; ++i) conNulo[i] = buffer[i];
    conNulo[cantidad] = '\0';
    delete[] buffer;

    Longitud = cantidad;
    return conNulo;
}

// Lee un archivo completo en un arreglo dinamico de char, sin usar string
char* leerArchivoCharArray(const char *ruta, int &Longitud) {
    ifstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo.");
    }

    int capacidad = 0, cantidad = 0;
    char *buffer = nullptr;
    char c;
    while (archivo.get(c)) {
        if (cantidad == capacidad) {
            int nuevaCapacidad = (capacidad == 0) ? 64 : capacidad * 2;
            char *nuevo = new char[nuevaCapacidad];
            for (int i = 0; i < cantidad; ++i) nuevo[i] = buffer[i];
            delete[] buffer;
            buffer = nuevo;
            capacidad = nuevaCapacidad;
        }
        buffer[cantidad] = c;
        cantidad++;
    }

    char *conNulo = new char[cantidad + 1];
    for (int i = 0; i < cantidad; ++i) conNulo[i] = buffer[i];
    conNulo[cantidad] = '\0';
    delete[] buffer;

    Longitud = cantidad;
    return conNulo;
}

// Menu de entrada (teclado o archivo), version sin string, para LZ78 y Encriptacion
char* obtenerTextoChar(int &Longitud) {
    int opcion;
    cout << "Como desea ingresar el texto?" << endl;
    cout << "1. Escribirlo por teclado" << endl;
    cout << "2. Leerlo desde un archivo .txt" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cin.ignore();

    if (opcion == 1) {
        cout << "Ingrese el texto: ";
        return leerLineaTeclado(Longitud);
    } else if (opcion == 2) {
        char rutaArchivo[300];
        cout << "Ingrese la ruta del archivo .txt: ";
        cin.getline(rutaArchivo, 300);
        char *texto = leerArchivoCharArray(rutaArchivo, Longitud);
        cout << "Texto leido: " << texto << endl;
        return texto;
    } else {
        throw invalid_argument("Opcion de entrada invalida.");
    }
}

// Compara dos arreglos de char por contenido y longitud (reemplaza el "==" de string)
bool compararArreglos(const char *a, int longA, const char *b, int longB) {
    if (longA != longB) return false;
    for (int i = 0; i < longA; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}


void probarRLE() {
    cout << "PRUEBA RLE " << endl;

    string texto = obtenerTexto();

    if (texto.empty()) {
        throw invalid_argument("Error en RLE: el texto no puede estar vacio.");
    }

    string comprimido = ComprimirRLE(texto);
    cout << "Comprimido: " << comprimido << endl;

    string descomprimido = DescomprimirRLE(comprimido);
    cout << "Descomprimido: " << descomprimido << endl;

    if (descomprimido == texto) {
        cout << "OK, coincide con el original." << endl;
    } else {
        cout << "ERROR, no coincide." << endl;
    }
    cout << endl;
}

void probarLZ78() {
    cout << " PRUEBA LZ78 " << endl;

    int longitudTexto;
    char *texto = obtenerTextoChar(longitudTexto);

    if (longitudTexto == 0) {
        delete[] texto;
        throw length_error("Error en LZ78: el texto no puede tener longitud cero.");
    }

    Parejas *pares;
    int cantidadPares;
    ComprimirLZ78(texto, pares, cantidadPares);

    cout << "Pares generados: ";
    for (int i = 0; i < cantidadPares; ++i) {
        char c = pares[i].Caracter;
        cout << "(" << pares[i].Indice << ",";
        if (c == '\0') cout << "FIN";
        else cout << c;
        cout << ") ";
    }
    cout << endl;

    int longitudResultado;
    char *descomprimido = Descomprimir_LZ78(pares, cantidadPares, longitudResultado);

    cout << "Descomprimido: ";
    for (int i = 0; i < longitudResultado; ++i) cout << descomprimido[i];
    cout << endl;

    if (compararArreglos(descomprimido, longitudResultado, texto, longitudTexto)) {
        cout << "OK, coincide con el original." << endl;
    } else {
        cout << "ERROR, no coincide." << endl;
    }

    delete[] texto;
    delete[] pares;
    delete[] descomprimido;
    cout << endl;
}

void probarEncriptacion() {
    cout << " PRUEBA ENCRIPTACION " << endl;

    int cantidad;
    char *texto = obtenerTextoChar(cantidad);

    int n;
    cout << "Ingrese el valor de rotacion n (0 < n < 8): ";
    cin >> n;
    cin.ignore();

    int claveEntera;
    cout << "Ingrese la clave K (0-255): ";
    cin >> claveEntera;
    cin.ignore();

    if (n <= 0 || n >= 8 || claveEntera < 0 || claveEntera > 255) {
        delete[] texto;
        throw out_of_range("Error en Encriptacion: parametros fuera de rango.");
    }
    unsigned char K = (unsigned char)claveEntera;

    unsigned char *datos = new unsigned char[cantidad];
    for (int i = 0; i < cantidad; ++i) {
        datos[i] = (unsigned char)texto[i];
    }

    unsigned char *encriptado = Encriptar_Datos(datos, cantidad, n, K);

    cout << "Encriptado (hex): " << hex;
    for (int i = 0; i < cantidad; ++i) cout << (int)encriptado[i] << " ";
    cout << dec << endl;

    unsigned char *desencriptado = Desencriptar_Datos(encriptado, cantidad, n, K);

    cout << "Desencriptado: ";
    for (int i = 0; i < cantidad; ++i) cout << (char)desencriptado[i];
    cout << endl;

    bool coincide = true;
    for (int i = 0; i < cantidad; ++i) {
        if ((char)desencriptado[i] != texto[i]) { coincide = false; break; }
    }

    if (coincide) {
        cout << "Encriptacion: OK, coincide con el original." << endl;
    } else {
        cout << "Encriptacion: ERROR, no coincide." << endl;
    }

    delete[] texto;
    delete[] datos;
    delete[] encriptado;
    delete[] desencriptado;
    cout << endl;
}

int main() {
    try {
        probarRLE();
    } catch (const invalid_argument &error) {
        cout << "Excepcion capturada (invalid_argument): " << error.what() << endl << endl;
    } catch (const runtime_error &error) {
        cout << "Excepcion capturada (runtime_error): " << error.what() << endl << endl;
    }

    try {
        probarLZ78();
    } catch (const length_error &error) {
        cout << "Excepcion capturada (length_error): " << error.what() << endl << endl;
    } catch (const invalid_argument &error) {
        cout << "Excepcion capturada (invalid_argument): " << error.what() << endl << endl;
    } catch (const runtime_error &error) {
        cout << "Excepcion capturada (runtime_error): " << error.what() << endl << endl;
    }

    try {
        probarEncriptacion();
    } catch (const out_of_range &error) {
        cout << "Excepcion capturada (out_of_range): " << error.what() << endl << endl;
    } catch (const invalid_argument &error) {
        cout << "Excepcion capturada (invalid_argument): " << error.what() << endl << endl;
    } catch (const runtime_error &error) {
        cout << "Excepcion capturada (runtime_error): " << error.what() << endl << endl;
    }

    return 0;
}