#ifndef FUNCIONES_MODULO2_H
#define FUNCIONES_MODULO2_H
#include "FUNCIONES_MODULO1.h"
void Agregar_fila(unsigned char* &PUNTERO_BLOQUE_MEMORIA, int &filas, int&columnas,int &reserva_bytes, int posicion);
void Eliminar_fila(unsigned char* &PUNTERO_BLOQUE_MEMORIA, int &filas, int columnas, int &reserva_bytes, int posicion);
void Agregar_Columna(unsigned char* &PUNTERO_BLOQUE_MEMORIA, int filas, int&columnas, int &reserva_bytes, int posicion);
void Eliminar_columnas(unsigned char* &PUNTERO_BLOQUE_MEMORIA, int filas, int &Columnas, int &reserva_bytes, int posicion);
void Hacer_vivo_el_tablero(unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas , int Columnas);
void Llenar_espacios_vacios(unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas , int Columnas);
void Imprimir_Tablero_Legible(unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas, int columnas);

#endif // FUNCIONES_MODULO2_H
