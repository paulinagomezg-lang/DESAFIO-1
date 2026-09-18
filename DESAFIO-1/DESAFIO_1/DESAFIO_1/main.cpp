#include <iostream>
#include "FUNCIONES_MODULO2.h"
using namespace std;

int main()
{
    // MODULO 1: Acceso a Bits y Gestion Dinamica de Memoria.
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

    //MODULO 2: Operaciones Estructurales y Lógica del Tablero.

    cout <<"Tablero antes de inicializar sus secuencias"<<endl;
    Imprimir_Tablero_Legible(Tablerito, filas, columnas);
    cout <<endl;

    Agregar_fila(Tablerito, filas,columnas, reserva_bytes, 1);
    cout <<"Despues de agregar fila en pos 1 "<<"("<<filas<<"x"<<columnas<<")"<<endl;
    Imprimir_Tablero_Legible(Tablerito, filas, columnas);
    cout << "Los bytes reservados: "<<reserva_bytes<<endl;

    Agregar_Columna(Tablerito, filas,columnas,reserva_bytes,2);
    cout << "Despues de agregar columna en pos 2 "<<"("<<filas<<"x"<<columnas<<")"<<endl;
    Imprimir_Tablero_Legible(Tablerito, filas, columnas);
    cout << "Los bytes reservados: "<<reserva_bytes<<endl;

    Eliminar_fila(Tablerito, filas,columnas, reserva_bytes, 1);
    Eliminar_columnas(Tablerito, filas,columnas, reserva_bytes, 2);
    cout <<"Al eliminar la fila y columna que desea , quedara como la original"<<"("<<filas<<"x"<<columnas<<endl;
    Imprimir_Tablero_Legible(Tablerito, filas, columnas);
    cout <<"Los bytes reservados: "<<reserva_bytes<<endl;





}
