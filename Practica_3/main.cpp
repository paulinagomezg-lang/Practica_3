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
        throw runtime_error("No se pudo abrir el archivo: " + ruta);
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

// Pregunta al usuario si quiere ingresar el texto por teclado o desde un archivo,
// y devuelve el texto ya obtenido por el metodo elegido.
string obtenerTexto() {
    int opcion;
    cout << "Como desea ingresar el texto?" << endl;
    cout << "1. Escribirlo por teclado" << endl;
    cout << "2. Leerlo desde un archivo .txt" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cin.ignore(); // limpia el salto de linea pendiente en el buffer

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

void probarRLE() {
    cout << "PRUEBA RLE " << endl;

    string texto = obtenerTexto();

    // Tipo 1: invalid_argument (el dato de entrada no es valido)
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

    string texto = obtenerTexto();

    // Tipo 2: length_error (problema relacionado con el tamaño/longitud del dato)
    if (texto.empty()) {
        throw length_error("Error en LZ78: el texto no puede tener longitud cero.");
    }

    Parejas *pares;
    int cantidadPares;
    ComprimirLZ78(texto, pares, cantidadPares);

    cout << "Pares generados: ";
    for (int i = 0; i < cantidadPares; ++i) {
        char c = pares[i].Caracter;
        cout << "(" << pares[i].Indice << ","
             << (c == '\0' ? "FIN" : string(1, c)) << ") ";
    }
    cout << endl;

    string descomprimido = Descomprimir_LZ78(pares, cantidadPares);
    cout << "Descomprimido: " << descomprimido << endl;

    if (descomprimido == texto) {
        cout << "OK, coincide con el original." << endl;
    } else {
        cout << "ERROR, no coincide." << endl;
    }

    delete[] pares;
    cout << endl;
}

void probarEncriptacion() {
    cout << " PRUEBA ENCRIPTACION " << endl;

    string texto = obtenerTexto();

    int n;
    cout << "Ingrese el valor de rotacion n (0 < n < 8): ";
    cin >> n;
    cin.ignore();

    int claveEntera;
    cout << "Ingrese la clave K (0-255): ";
    cin >> claveEntera;
    cin.ignore();

    // Tipo 3: out_of_range (un valor se sale del rango permitido)
    if (n <= 0 || n >= 8 || claveEntera < 0 || claveEntera > 255) {
        throw out_of_range("Error en Encriptacion: parametros fuera de rango.");
    }
    unsigned char K = (unsigned char)claveEntera;

    int cantidad = texto.length();
    unsigned char *datos = new unsigned char[cantidad];
    for (int i = 0; i < cantidad; ++i) {
        datos[i] = (unsigned char)texto[i];
    }

    unsigned char *encriptado = Encriptar_Datos(datos, cantidad, n, K);

    cout << "Encriptado (hex): " << hex;
    for (int i = 0; i < cantidad; ++i) cout << (int)encriptado[i] << " ";
    cout << dec << endl;

    unsigned char *desencriptado = Desencriptar_Datos(encriptado, cantidad, n, K);

    string recuperado = "";
    for (int i = 0; i < cantidad; ++i) recuperado += (char)desencriptado[i];

    cout << "Desencriptado: " << recuperado << endl;

    if (recuperado == texto) {
        cout << "Encriptacion: OK, coincide con el original." << endl;
    } else {
        cout << "Encriptacion: ERROR, no coincide." << endl;
    }

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