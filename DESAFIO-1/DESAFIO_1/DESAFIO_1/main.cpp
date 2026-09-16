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

    //Verificamos si cumpleo no lo esperado
    bool Correcto = true;
    Contador = 0;
    for (int fila = 0; fila < filas; ++fila) {
        for (int columna = 0; columna < columnas; ++columna) {
            unsigned char Leido = Obtener_Fichas(Tablerito,fila,columna,columnas);
            unsigned char Esperado = valores[Contador];
            int INDICE = fila*columnas+columna;
            int BIT_INICIAL = INDICE * BITS_POR_FICHA;
            int POS_DENTRO_BYTE = BIT_INICIAL%8;
            cout << "("<< fila<<","<< columna<<") INDICE = "<<INDICE<<"POS_DENTRO_BYTE"<<POS_DENTRO_BYTE<<"esperado = "<<(int) Esperado<<"leido = "<<(int) Leido;

            if (Leido != Esperado){
                cout<< "ERROR"<<endl;
                Correcto = false;
            }
            cout <<endl;
            Contador ++;
        }
    }
    cout <<endl;
    if (Correcto){
        cout<< "Todas las fichas se leyeron correctamente."<<endl;
        cout<< "Acceso a Bits y Gestion Dinamica de Memoria cumple"<<endl;
    }
    else{
        cout<<"Hay inconsistencias revisar funciones establecer fichas y obtener"<<endl;
    }
    liberatablero(Tablerito);
    // confirmacion de que la funcion dejo el puntero en null
    if (Tablerito == nullptr){
        cout<<"La memoria se libero correctamente"<<endl;
    }
    return 0;






}
