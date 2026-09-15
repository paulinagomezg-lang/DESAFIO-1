#include "PRUEBAFUNCIONES.h"
#include <iostream>
using namespace std;

//GESTIÓN DINAMICA DE MEMORIA

int calcularlosbytesnece(int filas, int columnas){
    int totalbits = bits_por_ficha*filas*columnas;
    int bytes = (totalbits+7)/8; //Se calcula con esta forma cuantos byte utiliza
    return bytes;
}

unsigned char* creaciontablero(int filas, int columnas, int &reserva_bytes){
    reserva_bytes = calcularlosbytesnece(filas,columnas);
    unsigned char* BUFFER = new unsigned char[reserva_bytes];

    for (int i = 0; i < reserva_bytes; ++i) {
        BUFFER[i] = 0;

    }
    return BUFFER;
}

void liberatablero(unsigned char* &BUFFER){
    delete[] BUFFER;
    BUFFER = nullptr; //evita ue al volver a ser llamado coja un valor anterior o basura

}

//FUNCIÓN ACCESO A BITS

unsigned char Obtener_Fichas(const unsigned char* BUFFER, int fila, int columna, int columnas){
    int INDICE = fila*columnas*columna;
    int BIT_INICIAL = INDICE * BIT_POR_FICHA;
    int BYTE_INICIO = BIT_INICIAL/8;
    int POS_DENTRO_BYTE = BIT_INICIAL%8;

    if (POS_DENTRO_BYTE <=5){ //Cuando se utiliza menos de 5 bits ya que no comparten
        unsigned char BYTE_ACTUAL = BUFFER[BYTE_INICIO];
        unsigned char valor = (BYTE_ACTUAL >> POS_DENTRO_BYTE) & 0X07;
        return valor;
    }
    else{
        //caso donde es 6 o 7, la ficha se reparte entre el primer byte y la qeu sigue

    }
}

