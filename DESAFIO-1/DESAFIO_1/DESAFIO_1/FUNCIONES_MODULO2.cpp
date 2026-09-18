#include "FUNCIONES_MODULO2.h"
#include <iostream>
#include <cstdlib> //para poder utilizar la funcion aleatoria
using namespace std;

//OPERACIONES ESTRUCTURALES Y LOGICA DEL TABLERO.

const double Ocupacion_total_debajo = 0.65; //permite guardar numeros con decii¿males

//FUNCION DE AGREGAR FILA

void Agregar_fila(unsigned char* &PUNTERO_BLOQUE_MEMORIA, int &filas, int&columnas,int &reserva_bytes, int posicion){

    int Filas_nuevas = filas+1;
    int Bytes_necesarios = calcularlosbytesnece(Filas_nuevas,columnas);
    unsigned char* NUEVO_PUNTERO_BLOQUE_MEMORIA = new unsigned char[Bytes_necesarios];
    for (int i = 0; i < Bytes_necesarios; ++i) {
        NUEVO_PUNTERO_BLOQUE_MEMORIA[i] = 0; //Se debe iniciar vacio antes de rellenar
    }
    //las fichas qeu ya estaban en posiciono despues se recorren una hacia abajo para darle espacio a las nuevas

    for (int Fila_vieja = 0; Fila_vieja < filas; ++Fila_vieja) {
        int Fila_nueva = Fila_vieja + (Fila_vieja >= posicion);
        for (int columna = 0; columna < columnas; ++columna) {
            unsigned char valor = Obtener_Fichas(PUNTERO_BLOQUE_MEMORIA,Fila_vieja,columna,columnas);
            Establecer_fichas(NUEVO_PUNTERO_BLOQUE_MEMORIA,Fila_nueva, columna,columnas,valor);
        }
    }
    //La fila de posicion queda vacia proqeu el nuevaposiciondentro de byte ya se inicio en 000
    liberatablero(PUNTERO_BLOQUE_MEMORIA);
    PUNTERO_BLOQUE_MEMORIA = NUEVO_PUNTERO_BLOQUE_MEMORIA;
    filas = Filas_nuevas;
    reserva_bytes = Bytes_necesarios;

}

//FUNCION DE ELIMINAR FILA

void Eliminar_fila(unsigned char* &PUNTERO_BLOQUE_MEMORIA, int &filas, int columnas, int &reserva_bytes, int posicion){
    int Filas_nuevas = filas-1;
    int Byte_necesarios = calcularlosbytesnece(Filas_nuevas,columnas);
    //Regla de 65%= solo se reduce cuando el resultante cae debajo de ese, sino seguimos.
    //Recordar lo nombrado por el profe en la clase: evitar reservar y liberar en cada eliminacion.

    int Bytes_reservados_final = reserva_bytes;
    double Parte_de_uso = (double)Byte_necesarios / (double)reserva_bytes; //partedeuso:variable decimal donde se guarda el resultado porcentual final.
    if (Parte_de_uso < Ocupacion_total_debajo ){
        Bytes_reservados_final = Byte_necesarios;
    }
    unsigned char* NUEVO_PUNTERO_BLOQUE_MEMORIA = new unsigned char[Bytes_reservados_final];
    for (int i = 0; i < Bytes_reservados_final; ++i) {
        NUEVO_PUNTERO_BLOQUE_MEMORIA[i] = 0;
    }
    for (int Fila_vieja = 0; Fila_vieja < filas; ++Fila_vieja) {
        if (Fila_vieja ==posicion) continue; //salta directamente a la siguiente sin ejecutar el resto del código que viene después y esa es la que se elimina
        int Fila_nueva = Fila_vieja - (Fila_vieja >= posicion);
        for (int columna = 0; columna < columnas; ++columna) {
            unsigned char valor = Obtener_Fichas(PUNTERO_BLOQUE_MEMORIA, Fila_vieja, columna, columnas);
            Establecer_fichas(NUEVO_PUNTERO_BLOQUE_MEMORIA,Fila_nueva,columna,columnas,valor);
        }
    }
    liberatablero(PUNTERO_BLOQUE_MEMORIA);
    PUNTERO_BLOQUE_MEMORIA = NUEVO_PUNTERO_BLOQUE_MEMORIA;
    filas = Filas_nuevas;
    reserva_bytes = Bytes_reservados_final;
}

//FUNCION DE AGREGAR COLUMNA QUE SE LE BRINDA AL USUSARIO

void Agregar_Columna(unsigned char* &PUNTERO_BLOQUE_MEMORIA, int filas, int&columnas, int &reserva_bytes, int posicion){
    int Columnas_viejas = columnas;
    int Columnas_Nuevas = columnas+1;
    int Byte_necesarios = calcularlosbytesnece(filas, Columnas_Nuevas);

    unsigned char* NUEVO_PUNTERO_BLOQUE_MEMORIA = new unsigned char[Byte_necesarios];
    for (int i = 0; i < Byte_necesarios; ++i) {
        NUEVO_PUNTERO_BLOQUE_MEMORIA[i] = 0;
    }
    //Columnas cambia y leemos unicamente el de columnas viejas y el mejor es columnasnuevas al escribir ya que el columnas viejas guarda el numero que no necesitamos
    for (int fila = 0; fila < filas; ++fila) {
        for (int Columna_vieja = 0; Columna_vieja < Columnas_viejas; ++Columna_vieja) {
            int Columna_nueva = (Columna_vieja = Columna_vieja + (Columna_vieja >= posicion);
            unsigned char valor = Obtener_Fichas(PUNTERO_BLOQUE_MEMORIA, fila,  Columna_vieja, Columnas_viejas);
            Establecer_fichas(NUEVO_PUNTERO_BLOQUE_MEMORIA, fila,Columna_nueva,Columnas_Nuevas, valor);
        }
        //La columna en posicion de esta fila queda vacia (000)
    }
    liberatablero(PUNTERO_BLOQUE_MEMORIA);
    PUNTERO_BLOQUE_MEMORIA = NUEVO_PUNTERO_BLOQUE_MEMORIA;
    columnas = Columnas_Nuevas;
    reserva_bytes = Byte_necesarios;
}

//FUNCION PARA CUANDO SE DESEE ELIMINAR COLUMNAS

void Eliminar_columnas(unsigned char* &PUNTERO_BLOQUE_MEMORIA, int filas, int &Columnas, int &reserva_bytes, int posicion){
    int Columnas_viejas = columnas;
    int Columnas_Nuevas = columnas - 1;
    int Byte_necesarios = calcularlosbytesnece(filas, Columnas_Nuevas);

    int Bytes_Reservados_Final = reserva_bytes;
    double Parte_de_uso = (double)Byte_necesarios /(double)reserva_bytes;
    if (Parte_de_uso < Ocupacion_total_debajo){
        Bytes_Reservados_Final = Byte_necesarios;
    }

    unsigned char* NUEVO_PUNTERO_BLOQUE_MEMORIA = new unsigned char[Bytes_Reservados_Final];
    for (int i = 0; i < Bytes_Reservados_Final; ++i) {
        NUEVO_PUNTERO_BLOQUE_MEMORIA = 0;
    }
    for (int fila = 0; fila < filas; ++fila) {
        for (int Columna_vieja = 0; Columna_vieja < Columnas_viejas; ++Columna_vieja) {
            if (Columna_vieja == posicion) continue; //Esta es la columna que se elimina y Cancela únicamente la vuelta actual del bucle y pasa a la siguiente
            int Columna_nueva = (Columna_vieja = Columna_vieja - (Columna_vieja >= posicion));
            unsigned char valor = Obtener_Fichas(PUNTERO_BLOQUE_MEMORIA, fila, Columna_vieja, Columnas_viejas);
            Establecer_fichas(NUEVO_PUNTERO_BLOQUE_MEMORIA, fila, Columna_nueva, Columnas_Nuevas, valor);
        }
    }
    liberatablero(PUNTERO_BLOQUE_MEMORIA);
    PUNTERO_BLOQUE_MEMORIA = NUEVO_PUNTERO_BLOQUE_MEMORIA;
    Columnas = Columnas_Nuevas;
    reserva_bytes = Byte_necesarios;
}

