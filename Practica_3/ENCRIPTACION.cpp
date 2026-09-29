#include <iostream>
#include <string>
using namespace std;
#include "ENCRIPTACION.h"

unsigned char Rotar_Izquierda(unsigned char Byte, int A){
    return (unsigned char)((Byte << A) | (Byte >>(8 - A)));

}

unsigned char Rotar_Derecha(unsigned char Byte, int A){
    //oPERACION INVERSA DE ROTAR IZQUIERDA
    return (unsigned char)((Byte >>A) | (Byte <<(8 - A)));
}

unsigned char Encriptar_Byte(unsigned char Byte, int A, unsigned char S){
    unsigned char Rotado = Rotar_Izquierda(Byte, A);
    return Rotado ^ S; //APLICACION EXOR
}

unsigned char Desencriptar_Byte(unsigned char Byte, int A, unsigned char S){
    unsigned char sinXor = Byte ^ S; //hacemos la rotación hacia la derecha para deshacer la rotación izquierda.
    // Se revierte la rotacion con la rotacion opuesta
    return Rotar_Derecha(sinXor, A);
}

unsigned char* Encriptar_Datos( const unsigned char *Datos, int Cantidad, int A , unsigned char S){ //Aplicar todo lo de byte desde la memoria dinamica
    unsigned char *Resultado = new unsigned char[Cantidad];
    for (int G = 0; G < Cantidad; ++G) {
        Resultado[G] = Encriptar_Byte(Datos[G], A, S); //toma un byte y lo encripta.
    }
    return Resultado; //Devuelve el arreglo encriptado
}

unsigned char* Desencriptar_Datos(const unsigned char *Datos, int Cantidad, int A, unsigned char S){
    unsigned char *Resultado = new unsigned char[Cantidad];
    for (int G = 0; G < Cantidad; ++G) {
        Resultado[G] = Desencriptar_Byte(Datos[G], A, S);
    }
    return Resultado;
}

