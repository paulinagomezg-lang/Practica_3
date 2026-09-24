#include <iostream>
#include <string>
using namespace std;

#include "LZ78.h"


int Buscarentrada(EntradaDiccionario *Diccionario, int Cantidad, int Prefijo, char Caracter){
    for (int G = 0; G < Cantidad; ++G) {
        if (Diccionario[G].Prefijo == Prefijo && Diccionario[G].Caracter == Caracter){
            return G +1;  //
        }
    }
    return -1;
}

void AgregarlaEntrada(EntradaDiccionario *&Diccionario, int &Capacidad, int &Cantidad, int Prefijo, char Caracter){
    if (Cantidad == Capacidad){
        int NuevaCapacidad;
        if (Capacidad == 0){
            NuevaCapacidad = 8;
        }
        else{
            NuevaCapacidad = Capacidad * 2;
        }
        EntradaDiccionario *Nuevo = new EntradaDiccionario[NuevaCapacidad];
        for (int G = 0; G < Cantidad; ++G) Nuevo[G] = Diccionario[G] ;
        delete[] Diccionario;
        Diccionario = Nuevo;
        Capacidad = NuevaCapacidad;
        }
    Diccionario[Cantidad].Prefijo = Prefijo;
    Diccionario[Cantidad].Caracter = Caracter;
    Cantidad++;
}

void Agregar_Parejas(Parejas *&Salida, int &Capacidad , int &Cantidad, int Indice, char Caracter){
    if (Cantidad == Capacidad){
        int NuevaCapacidad;
        if (Capacidad == 0){
            NuevaCapacidad = 8;
        }
        else{
            NuevaCapacidad = Capacidad * 2;
        }

        Parejas *Nuevo = new Parejas[NuevaCapacidad];
        for (int G = 0; G < Cantidad; ++G) Nuevo[G] = Salida[G];
        delete[] Salida;
        Salida = Nuevo;
        Capacidad = NuevaCapacidad;
        }
    Salida[Cantidad].Indice = Indice;
    Salida [Cantidad].Caracter = Caracter;
    Cantidad++;
}

void ComprimirLZ78(const string &texto, Parejas *&Salida, int &CantidadParejas){
    int CapacidadDiccionario = 0, CantidadDiccionario = 0;
    EntradaDiccionario *Diccionario = nullptr;

    int CapacidadSalida = 0;
    CantidadParejas = 0;
    Salida = nullptr;

    int A = texto.length();
    int PrefijoActual = 0;
    int G = 0;

    while(G < A){
        char P = texto[G];
        int Encontrado = Buscarentrada(Diccionario, CantidadDiccionario, PrefijoActual, P);

        if (Encontrado != -1){
            PrefijoActual = Encontrado;
            G++;
        }
        else{
            AgregarlaEntrada(Diccionario, CapacidadDiccionario, CantidadDiccionario, PrefijoActual, P);
            Agregar_Parejas(Salida, CapacidadSalida,CantidadParejas, PrefijoActual, P );
            PrefijoActual = 0;
            G++;
        }
    }
    if (PrefijoActual !=0){
        Agregar_Parejas(Salida, CapacidadSalida, CantidadParejas, PrefijoActual, '\0' );
    }

    delete[] Diccionario;
}

char* Reconstruit_Frase(EntradaDiccionario *Diccionario, int Indice, int &Longitud){
    if (Indice == 0){
        Longitud = 0;
        return new char[0];
    }

    int Len = 0;
    int Actual = Indice;
    while(Actual != 0){
        Len++;
        Actual = Diccionario[Actual - 1].Prefijo;
    }

    char *Frase = new char[Len];
    Actual = Indice;
    int Posicion = Len -1;
    while(Actual != 0){
        Frase[Posicion] = Diccionario[Actual - 1].Caracter;
        Posicion--;
        Actual = Diccionario[Actual - 1].Prefijo;
    }

    Longitud = Len;
    return Frase;
}

string Descomprimir_LZ78(Parejas *Pares , int CantidadPares ){
    int CapacidadDiccionario = 0, CantidadDiccionario = 0;
    EntradaDiccionario *Diccionario = nullptr;

    string Resultado = "";

    for (int P = 0; P < CantidadPares; ++P) {
        int Indice = Pares[P].Indice;
        char Caracter = Pares[P].Caracter;

        int LongitudFrase;
        char *Frase = Reconstruit_Frase(Diccionario, Indice, LongitudFrase);
        for (int S = 0; S < LongitudFrase; ++S) Resultado = Resultado + Frase[S];
        delete[] Frase;

        bool Es_Centinela = (Caracter == '\0');
        if (!Es_Centinela){
            Resultado = Resultado + Caracter;
            AgregarlaEntrada(Diccionario, CapacidadDiccionario, CantidadDiccionario, Indice, Caracter);
        }
    }

    delete[]Diccionario;
    return Resultado;
}