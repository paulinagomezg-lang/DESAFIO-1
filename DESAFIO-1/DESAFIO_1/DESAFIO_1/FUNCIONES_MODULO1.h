#ifndef FUNCIONES_MODULO1_H
#define FUNCIONES_MODULO1_H
#endif // FUNCIONES_MODULO1_H

const unsigned char ESTADO_VACIO =0;
const unsigned char ESTADO_ESPACIAL = 7;
const int BITS_POR_FICHA =3;

int calcularlosbytesnece(int filas, int columnas);
unsigned char* creaciontablero(int filas, int columnas, int &reserva_bytes);
void liberatablero(unsigned char* &PUNTERO_BLOQUE_MEMORIA);
unsigned char Obtener_Fichas(const unsigned char* PUNTERO_BLOQUE_MEMORIA, int fila, int columna, int columnas);
void Establecer_fichas(unsigned char* PUNTERO_BLOQUE_MEMORIA, int fila, int columna, int columnas, unsigned char valor);
void Resultado_PUNTERO_BLOQUE_MEMORIA_BINARIO(const unsigned char* PUNTERO_BLOQUE_MEMORIA , int reserva_bytes);
