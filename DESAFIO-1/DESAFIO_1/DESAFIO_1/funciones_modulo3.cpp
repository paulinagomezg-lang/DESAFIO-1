#include "FUNCIONES_MODULO3.h"
#include "FUNCIONES_MODULO1.h"
#include "FUNCIONES_MODULO2.h"
#include "SIMBOLOGIA_FICHAS.h"

//MODULO 3 : REGLAS DEL JUEGO Y CASCADAS

//ESTA FUNCION SE ENCARGA DE DETECTAR LAS CMBINACIONES ENCOONTRADAS, PERO SIN ELIMINAR NADA
void detectarCombis(const unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas, int columnas,unsigned char* marcas, int& Combos_Encontrados) {
    Combos_Encontrados = 0;

    // quien la llama solo necesita reservar el arreglo (tamano filas*columnas), no inicializarlo.
    for (int i = 0; i < filas * columnas; i++)marcas[i] = 0;
    //COMBINACIONES HORIZONTALES
    for (int fila = 0; fila < filas; fila++) {
        int columna = 0;
        while (columna < columnas) {
            unsigned char valor = Obtener_Fichas(PUNTERO_BLOQUE_MEMORIA, fila, columna, columnas);
            if (esFichaNormal(valor)) {
                int Columna_Inicio = columna;
                while (columna < columnas && Obtener_Fichas(PUNTERO_BLOQUE_MEMORIA, fila, columna, columnas) == valor) columna++;
                int Longitud_Combo = columna - Columna_Inicio;
                if (Longitud_Combo >= LONGITUD_MINIMA_COMBO) {
                    for (int Columna_Actual = Columna_Inicio; Columna_Actual < columna; Columna_Actual++) {
                        marcas[fila * columnas + Columna_Actual] = 1;
                    }
                    Combos_Encontrados++;
                }
            }
            else {
                columna++;
            }
        }
    }

    //COMBINACIONES VERTICALES
    for (int columna = 0; columna < columnas; columna++) {
        int fila = 0;
        while (fila < filas) {
            unsigned char valor = Obtener_Fichas(PUNTERO_BLOQUE_MEMORIA, fila, columna, columnas);
            if (esFichaNormal(valor)) {
                int Fila_Inicio = fila;
                while (fila < filas && Obtener_Fichas(PUNTERO_BLOQUE_MEMORIA, fila, columna, columnas) == valor) fila++;
                int Longitud_Combo = fila - Fila_Inicio;
                if (Longitud_Combo >= LONGITUD_MINIMA_COMBO) {
                    for (int Fila_Actual = Fila_Inicio; Fila_Actual < fila; Fila_Actual++) {
                        marcas[Fila_Actual * columnas + columna] = 1;
                    }
                    combosEncontrados++;
                }
            } else {
                fila++;
            }
        }
    }
}

void revisarCombis(unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas, int columnas,const unsigned char* marcas,int& puntuacion, int& fichasEliminadasTotal) {
    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int Indice = fila * columnas + columna;
            if (marcas[Indice] == 1) {
                Establecer_fichas(PUNTERO_BLOQUE_MEMORIA, fila, columna, columnas, ESTADO_VACIO);
                fichasEliminadasTotal++;
                puntuacion += PUNTOS_POR_FICHA;
            }
        }
    }
}

void ejecutarCicloCascada(unsigned char*& PUNTERO_BLOQUE_MEMORIA, int& filas, int& columnas, int& reserva_bytes,
                          int& puntuacion, int& cascadasActuales,
                          int& fichasEliminadasTotal, int& combinacionesDetectadas) {
    (void)reserva_bytes; // una cascada no cambia filas/columnas, se deja
    // el parametro por si a futuro se necesita
    cascadasActuales = 0;

    const int Max_Vueltas_Cascada = 10000;

    while (cascadasActuales < Max_Vueltas_Cascada) {
        unsigned char* marcas = new unsigned char[filas * columnas];

        int Combos_Esta_Vuelta = 0;
        detectarCombis(PUNTERO_BLOQUE_MEMORIA, filas, columnas, marcas, Combos_Esta_Vuelta);

        if (Combos_Esta_Vuelta == 0) {
            delete[] marcas;
            break; // tablero estable, no hay mas cascadas
        }

        combinacionesDetectadas += Combos_Esta_Vuelta;
        revisarCombis(PUNTERO_BLOQUE_MEMORIA, filas, columnas, marcas, puntuacion, fichasEliminadasTotal);
        delete[] marcas;

        Hacer_vivo_el_tablero(PUNTERO_BLOQUE_MEMORIA, filas, columnas);     // Modulo 2 (gravedad)
        Llenar_espacios_vacios(PUNTERO_BLOQUE_MEMORIA, filas, columnas);    // Modulo 2 (relleno)

        cascadasActuales++;
    }
}

