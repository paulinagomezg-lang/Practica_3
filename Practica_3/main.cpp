#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

#include "RLE.h"
#include "LZ78.h"
#include "ENCRIPTACION.h"

// ---------- Prueba del modulo RLE ----------
void probarRLE() {
    cout << "===== PRUEBA RLE =====" << endl;

    string texto;
    cout << "Ingrese un texto para probar RLE: ";
    getline(cin, texto);

    // Tipo 1: invalid_argument (el dato de entrada no es valido)
    if (texto.empty()) {
        throw invalid_argument("Error en RLE: el texto no puede estar vacio.");
    }

    string comprimido = ComprimirRLE(texto);
    cout << "Comprimido: " << comprimido << endl;

    string descomprimido = DescomprimirRLE(comprimido);
    cout << "Descomprimido: " << descomprimido << endl;

    if (descomprimido == texto) {
        cout << "RLE: OK, coincide con el original." << endl;
    } else {
        cout << "RLE: ERROR, no coincide." << endl;
    }
    cout << endl;
}

// ---------- Prueba del modulo LZ78 ----------
void probarLZ78() {
    cout << "===== PRUEBA LZ78 =====" << endl;

    string texto;
    cout << "Ingrese un texto para probar LZ78: ";
    getline(cin, texto);

    // Tipo 2: length_error (problema relacionado con el tamanio/longitud del dato)
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
        cout << "LZ78: OK, coincide con el original." << endl;
    } else {
        cout << "LZ78: ERROR, no coincide." << endl;
    }

    delete[] pares;
    cout << endl;
}

// ---------- Prueba del modulo de Encriptacion ----------
void probarEncriptacion() {
    cout << "===== PRUEBA ENCRIPTACION =====" << endl;

    string texto;
    cout << "Ingrese un texto para probar encriptacion: ";
    getline(cin, texto);

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
    }

    try {
        probarLZ78();
    } catch (const length_error &error) {
        cout << "Excepcion capturada (length_error): " << error.what() << endl << endl;
    }

    try {
        probarEncriptacion();
    } catch (const out_of_range &error) {
        cout << "Excepcion capturada (out_of_range): " << error.what() << endl << endl;
    }

    return 0;
}