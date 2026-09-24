#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

unsigned char Rotar_Izquierda(unsigned char Byte, int A);
unsigned char Rotar_Derecha(unsigned char Byte, int A);
unsigned char Encriptar_Byte(unsigned char Byte, int A, unsigned char S);
unsigned char Desencriptar_Byte(unsigned char Byte, int A, unsigned char S);
unsigned char Encriptar_Datos( const unsigned char *Datos, int Cantidad, int A , unsigned char S);
unsigned char Desencriptar_Datos(const unsigned char *Datos, int Cantidad, int A, unsigned char S);

#endif // ENCRIPTACION_H
