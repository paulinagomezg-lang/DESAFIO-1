#ifndef FUNCIONES_MODULO3_H
#define FUNCIONES_MODULO3_H
#include "FUNCIONES_MODULO1.h"
#include "FUNCIONES_MODULO2.h"
#include"SIMBOLOGIA_FICHAS.h"
void detectarCombis(const unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas, int columnas,unsigned char* marcas, int& Combos_Encontrados) ;
void revisarCombis(unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas, int columnas,const unsigned char* marcas,int& puntuacion, int& fichasEliminadasTotal);
void ejecutarCicloCascada(unsigned char*& PUNTERO_BLOQUE_MEMORIA, int& filas, int& columnas, int& reserva_bytes,int& puntuacion, int& cascadasActuales,  int& fichasEliminadasTotal, int& combinacionesDetectadas);

#endif // FUNCIONES_MODULO3_H