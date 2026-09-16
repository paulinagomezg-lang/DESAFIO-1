#include "FUNCIONES_MODULO1.h"
#include <iostream> // solo para imprimirPUNTERO_BLOQUE_MEMORIABinario (herramienta de depuracion)
using namespace std;

//GESTIÓN DINAMICA DE MEMORIA

int calcularlosbytesnece(int filas, int columnas){
    int totalbits = BITS_POR_FICHA*filas*columnas;
    int bytes = (totalbits+7)/8; //Se calcula con esta forma cuantos byte utiliza
    return bytes;
}

unsigned char* creaciontablero(int filas, int columnas, int &reserva_bytes){
    reserva_bytes = calcularlosbytesnece(filas,columnas);
    unsigned char* PUNTERO_BLOQUE_MEMORIA = new unsigned char[reserva_bytes];

    for (int i = 0; i < reserva_bytes; ++i) {
         PUNTERO_BLOQUE_MEMORIA[i] = 0;

    }
    return  PUNTERO_BLOQUE_MEMORIA;
}

void liberatablero(unsigned char* &PUNTERO_BLOQUE_MEMORIA){
    delete[] PUNTERO_BLOQUE_MEMORIA;
    PUNTERO_BLOQUE_MEMORIA= nullptr; //evita ue al volver a ser llamado coja un valor anterior o basura

}

//FUNCIÓN ACCESO A BITS

unsigned char Obtener_Fichas(const unsigned char* PUNTERO_BLOQUE_MEMORIA, int fila, int columna, int columnas){
    int INDICE = fila*columnas+columna;
    int BIT_INICIAL = INDICE * BITS_POR_FICHA;
    int BYTE_INICIO = BIT_INICIAL/8;
    int POS_DENTRO_BYTE = BIT_INICIAL%8;

    if (POS_DENTRO_BYTE <= 5){ //Cuando se utiliza menos de 5 bits ya que no comparten
        unsigned char BYTE_ACTUAL = PUNTERO_BLOQUE_MEMORIA[BYTE_INICIO];
        unsigned char valor = (BYTE_ACTUAL >> POS_DENTRO_BYTE) & 0x07; //0x07:0x es que trabajaremos en hexadecimal que el 7 es 111 y saber que esta mirando o 0b111
        return valor;
    }
    else{
        //caso donde es 6 o 7, la ficha se reparte entre el primer byte y la qeu sigue
        int BITS_EN_PRIMERBYTE = 8-POS_DENTRO_BYTE;
        int BITS_EN_SEGUNBYTE = BITS_POR_FICHA - BITS_EN_PRIMERBYTE;

        unsigned char mascara_PRIMERBYTE = (unsigned char) ((1 << BITS_EN_PRIMERBYTE)-1); //<<: ES DESAPLAZAMIENTO
        unsigned char PARTE_MENOS_SIGNIFICATIVA= (PUNTERO_BLOQUE_MEMORIA[BYTE_INICIO]>>POS_DENTRO_BYTE) & mascara_PRIMERBYTE;  //fragmento menos significativo de una ficha partida

        unsigned char mascara_SEGUNDOBYTE = (unsigned char) ((1 << BITS_EN_SEGUNBYTE)-1);
        unsigned char PARTE_MAS_SIGNIFICATIVA = (PUNTERO_BLOQUE_MEMORIA[BYTE_INICIO+1] & mascara_SEGUNDOBYTE); //fragmento mas significativo de una ficha partida

        unsigned char valor = PARTE_MENOS_SIGNIFICATIVA | (PARTE_MAS_SIGNIFICATIVA << BITS_EN_PRIMERBYTE); //Trabaja con los bits de números (operación matemática interna)
        return valor;
    }
}


void Establecer_fichas(unsigned char* PUNTERO_BLOQUE_MEMORIA, int fila, int columna, int columnas, unsigned char valor){
    int INDICE = fila*columnas+columna;
    int BIT_INICIAL = INDICE * BITS_POR_FICHA;
    int BYTE_INICIO = BIT_INICIAL/8;
    int POS_DENTRO_BYTE = BIT_INICIAL%8;

    valor = valor & 0x07; //por más eficiencia, nos aseguramos en usar solo 3 bits
    if (POS_DENTRO_BYTE <= 5){

        unsigned char mascara_LIMPIEZA = (unsigned char)~(0x07 << POS_DENTRO_BYTE); //poder borrar el valor viejo de esa ficha sin afectar contiguidad antes de escribir el valor nuevo.
        PUNTERO_BLOQUE_MEMORIA[BYTE_INICIO] = (PUNTERO_BLOQUE_MEMORIA[BYTE_INICIO]&mascara_LIMPIEZA) |(valor << POS_DENTRO_BYTE);
    }
    else{
        int BITS_EN_PRIMERBYTE = 8-POS_DENTRO_BYTE;
        int BITS_EN_SEGUNBYTE = BITS_POR_FICHA - BITS_EN_PRIMERBYTE;

        //limpiamos los bits con parte mas significativa
        unsigned char mascara_PRIMERBYTE = (unsigned char)~(((1<<BITS_EN_PRIMERBYTE)-1)<<POS_DENTRO_BYTE);
        unsigned char PARTE_MENOS_SIGNIFICATIVA = valor & ((1<< BITS_EN_PRIMERBYTE)-1);
        PUNTERO_BLOQUE_MEMORIA[BYTE_INICIO] = (PUNTERO_BLOQUE_MEMORIA[BYTE_INICIO]&mascara_PRIMERBYTE|(PARTE_MENOS_SIGNIFICATIVA<<POS_DENTRO_BYTE));

        //limpiamos los bits con parte menos significativa
        unsigned char mascara_SEGUNDOBYTE =(unsigned char)~((1<< BITS_EN_SEGUNBYTE)-1);
        unsigned char PARTE_MAS_SIGNIFICATIVA = valor >>BITS_EN_PRIMERBYTE;
        PUNTERO_BLOQUE_MEMORIA[BYTE_INICIO+1] = (PUNTERO_BLOQUE_MEMORIA[BYTE_INICIO+1]&mascara_SEGUNDOBYTE) | PARTE_MAS_SIGNIFICATIVA;
    }
}


//Utlidad de depuracion del funcionamiento de operaciones

void Resultado_PUNTERO_BLOQUE_MEMORIA_BINARIO(const unsigned char* PUNTERO_BLOQUE_MEMORIA , int reserva_bytes){
    for (int i = 0; i < reserva_bytes; ++i) {
        cout<<"BYTE "<<i<<":"<<endl;
        for (int bit = 7; bit >=0; --bit) {
            cout<<((( PUNTERO_BLOQUE_MEMORIA[i]>>bit) & 0x01) ? '1' :'0'); //determina si su estado es 1 o 0
        }
        cout<<endl;
    }
}
