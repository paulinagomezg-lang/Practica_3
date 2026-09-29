#include <string>
using namespace std;
#include "RLE.h"

string ComprimirRLE(const string &texto) {
    string Comprimido = "";
    int A = texto.length();
    int G = 0;
    while (G < A) {
        char Actual = texto[G];
        int Contador = 1;
        while (G + Contador < A && texto[G + Contador] == Actual) Contador++;

        Comprimido = Comprimido + to_string(Contador) + '-' + Actual;  // <-- CON separador
        G = G + Contador;
    }
    return Comprimido;
}

string DescomprimirRLE(const string &Comprimido) {
    string Original = "";
    int A = Comprimido.length();
    int G = 0;
    while (G < A) {
        string numeroStr = "";
        while (G < A && isdigit(Comprimido[G])) {
            numeroStr += Comprimido[G];
            G++;
        }
        int Cantidad = stoi(numeroStr);
        G++; // salta el '-'   <-- este G++ SOLO es correcto si arriba SI hay separador
        char Caracter = Comprimido[G];
        G++;
        for (int P = 0; P < Cantidad; ++P) Original += Caracter;
    }
    return Original;
}