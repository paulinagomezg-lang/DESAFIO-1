#include "reglas_juego.h"
#include "FUNCIONES_MODULO1.h"
#include "tablero_estructural.h"
#include "constantes.h"

void detectarCombis(const unsigned char* buffer, int filas, int cols,
                    unsigned char* marcas, int& combosEncontrados) {
    combosEncontrados = 0;

    // La función se encarga de limpiar 'marcas' -- quien la llama solo
    // necesita reservar el arreglo (tamaño filas*cols), no inicializarlo.
    for (int i = 0; i < filas * cols; i++) marcas[i] = 0;

    // --- Combinaciones horizontales ---
    for (int f = 0; f < filas; f++) {
        int c = 0;
        while (c < cols) {
            unsigned char valor = Obtener_Fichas(buffer, f, c, cols);
            if (esFichaNormal(valor)) {
                int inicio = c;
                while (c < cols && Obtener_Fichas(buffer, f, c, cols) == valor) c++;
                int longitud = c - inicio;
                if (longitud >= LONGITUD_MINIMA_COMBO) {
                    for (int k = inicio; k < c; k++) marcas[f * cols + k] = 1;
                    combosEncontrados++;
                }
            } else {
                c++;
            }
        }
    }

    // --- Combinaciones verticales ---
    for (int c = 0; c < cols; c++) {
        int f = 0;
        while (f < filas) {
            unsigned char valor = Obtener_Fichas(buffer, f, c, cols);
            if (esFichaNormal(valor)) {
                int inicio = f;
                while (f < filas && Obtener_Fichas(buffer, f, c, cols) == valor) f++;
                int longitud = f - inicio;
                if (longitud >= LONGITUD_MINIMA_COMBO) {
                    for (int k = inicio; k < f; k++) marcas[k * cols + c] = 1;
                    combosEncontrados++;
                }
            } else {
                f++;
            }
        }
    }
    // Nota: una ficha que cae en una combinación horizontal Y vertical al
    // mismo tiempo queda marcada una sola vez (marcas[idx] = 1), pero
    // ambas combinaciones se contaron por separado en combosEncontrados,
    // tal como exige el enunciado ("una misma ficha podrá hacer parte
    // simultáneamente de una combinación horizontal y de una vertical").
}

void revisarCombis(unsigned char* buffer, int filas, int cols,
                   const unsigned char* marcas,
                   int& puntuacion, int& fichasEliminadasTotal) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < cols; c++) {
            int idx = f * cols + c;
            if (marcas[idx] == 1) {
                Establecer_fichas(buffer, f, c, cols, ESTADO_VACIO);
                fichasEliminadasTotal++;
                puntuacion += PUNTOS_POR_FICHA;
            }
        }
    }
}

void ejecutarCascada(unsigned char*& buffer, int& filas, int& cols, int& bytesReservados,
                     int& puntuacion, int& cascadasActuales,
                     int& fichasEliminadasTotal, int& combinacionesDetectadas) {
    (void)bytesReservados; // una cascada no cambia filas/columnas, se deja
    // el parámetro por si a futuro se necesita
    cascadasActuales = 0;

    // Tope de seguridad: una cascada real nunca debería necesitar tantas
    // vueltas. Si algún día Hacer_vivo_el_tablero / Llenar_espacios_vacios
    // tuvieran un bug que regenerara combinaciones sin parar, esto evita
    // que el programa se cuelgue en un bucle infinito.
    const int MAX_VUELTAS_CASCADA = 10000;

    while (cascadasActuales < MAX_VUELTAS_CASCADA) {
        unsigned char* marcas = new unsigned char[filas * cols];

        int combosEstaVuelta = 0;
        detectarCombis(buffer, filas, cols, marcas, combosEstaVuelta);

        if (combosEstaVuelta == 0) {
            delete[] marcas;
            break; // tablero estable, no hay más cascadas
        }

        combinacionesDetectadas += combosEstaVuelta;
        revisarCombis(buffer, filas, cols, marcas, puntuacion, fichasEliminadasTotal);
        delete[] marcas;

        Hacer_vivo_el_tablero(buffer, filas, cols);     // Módulo 2 (gravedad)
        Llenar_espacios_vacios(buffer, filas, cols);    // Módulo 2 (relleno)

        cascadasActuales++;
    }
}