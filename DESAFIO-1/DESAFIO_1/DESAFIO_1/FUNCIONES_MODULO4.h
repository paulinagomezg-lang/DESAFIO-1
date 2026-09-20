#ifndef FUNCIONES_MODULO4_H
#define FUNCIONES_MODULO4_H
#include "FUNCIONES_MODULO1.h"
#include "FUNCIONES_MODULO2.h"
#include"SIMBOLOGIA_FICHAS.h"
#include "FUNCIONES_MODULO3.h"

void dibujarFichas(const unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas, int columnas);
void dibujarBinario(const unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas, int columnas);
void mostrarProgreso(int puntuacion, int eliminacionesUsuario, int fichasEliminadasTotal,int combinacionesDetectadas, int cascadasActuales);
int menuPrincipal();
bool seleccionUsuario(int filas, int columnas, int& Fila_Seleccionada, int& Columna_Seleccionada);
int seleccionIndice(const char* mensaje, int Limite_Inclusive);
void dimensionesIni(int& filas, int& columnas);

#endif // FUNCIONES_MODULO4_H
