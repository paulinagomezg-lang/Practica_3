#ifndef LZ78_H
#define LZ78_H

struct EntradaDiccionario {
    int Prefijo; //Indice de la entrada
    char Caracter; //caracter agregado al final de prefijo

};

struct Parejas{
    int Indice;
    char Caracter;

};

int Buscarentrada(EntradaDiccionario *Diccionario, int Cantidad, int Prefijo, char Caracter);
void AgregarlaEntrada(EntradaDiccionario *&Diccionario, int &Capacidad, int &Cantidad, int Prefijo, char Caracter);
void Agregar_Parejas(Parejas *&Salida, int &Capacidad , int &Cantidad, int Indice, char Caracter);
void ComprimirLZ78(const string &texto, Parejas *&Salida, int &CantidadParejas);
char* Reconstruit_Frase(EntradaDiccionario *Diccionario, int Indice, int &Longitud);
string Descomprimir_LZ78(Parejas *Pares , int CantidadPares );


#endif // LZ78_H
