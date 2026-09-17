#include <iostream>
#include "FUNCIONES_MODULO1.h"
using namespace std;

int main()
{
    int filas = 3;
    int columnas = 3;
    int reserva_bytes = 0;

    unsigned char* Tablerito = creaciontablero(filas, columnas, reserva_bytes);
    cout <<"tablero "<<filas<<" x"<<columnas<<endl;
    cout <<"Bytes reservados: "<<reserva_bytes<<endl;
    Resultado_PUNTERO_BLOQUE_MEMORIA_BINARIO(Tablerito , reserva_bytes);
    cout <<endl;

    unsigned char valores[9] ={1, 2, 3, 4, 5, 6, 1, 3, 1}; //Valores aleatorios para mirar si algunas funciones cumplen
    int Contador =0;

    for (int fila = 0; fila < filas; ++fila) {
        for (int columna = 0; columna < columnas; ++columna) {
            Establecer_fichas( Tablerito,fila,columna,columnas,valores[Contador]);
            Contador ++;
        }
    }

    cout<<"PUNTERO_BLOQUE_MEMORIA despues de escribir valores de prueba: "<<endl;
    Resultado_PUNTERO_BLOQUE_MEMORIA_BINARIO(Tablerito , reserva_bytes);
    cout <<endl;

}
