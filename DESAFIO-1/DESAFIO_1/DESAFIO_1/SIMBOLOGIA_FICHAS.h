#ifndef SIMBOLOGIA_FICHAS_H
#define SIMBOLOGIA_FICHAS_H
#include "FUNCIONES_MODULO1.h"

// Aqui solo agregamos los codigos de las 6 fichas normales ya que el modulo 3 las necesita conocer

const unsigned char FICHA_AMPERSAND= 1; // 001
const unsigned char FICHA_EXCLAMACION = 2; // 010
const unsigned char FICHA_P = 3; // 011
const unsigned char FICHA_G= 4; // 100
const unsigned char FICHA_X= 5; // 101
const unsigned char FICHA_Y= 6; // 110
//si el usuario ingresa etre 1 y 6 tenemos que ter encuenta que vacio y espacial quedan excuidas de la detecciom de combinaciond¿es por defecto
inline bool esFichaNormal(unsigned char valor) { //inline:compilador puede copiar el código de la función directamente en el lugar donde se llama
    return valor >= FICHA_AMPERSAND && valor <= FICHA_Y;
}

const int LONGITUD_MINIMA_COMBO = 3; // cuantas fichas seguidas hacen na combinacion
const int PUNTOS_POR_FICHA = 10; // criterio de puntuación: 10 pts por cada ficha eliminada en una combinacion

#endif // SIMBOLOGIA_FICHAS_H
