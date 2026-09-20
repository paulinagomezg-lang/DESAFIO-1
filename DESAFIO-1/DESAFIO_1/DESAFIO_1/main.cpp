#include <iostream>
#include <cstdlib>
#include <ctime>
#include "FUNCIONES_MODULO4.h"
using namespace std;

int main()
{
    srand((unsigned int)time(0)); // semilla distinta en cada partida real
    int filas = 0, columnas = 0;
    dimensionesIni(filas, columnas);

    int reserva_bytes = 0;
    unsigned char* Tablerito = creaciontablero(filas, columnas, reserva_bytes);

    Llenar_espacios_vacios(Tablerito, filas, columnas);

    int puntuacion = 0, cascadasActuales = 0, fichasEliminadasTotal = 0;
    int combinacionesDetectadas = 0, eliminacionesUsuario = 0;
    ejecutarCicloCascada(Tablerito, filas, columnas, reserva_bytes,puntuacion, cascadasActuales,fichasEliminadasTotal, combinacionesDetectadas);

    dibujarFichas(Tablerito, filas, columnas);mostrarProgreso(puntuacion, eliminacionesUsuario, fichasEliminadasTotal,combinacionesDetectadas, cascadasActuales);

    // Ciclo principal del juego
    bool jugando = true;
    while (jugando) {
        int Opcion_Elegida = menuPrincipal();

        switch (Opcion_Elegida) {

        case 1: { // Eliminar ficha
            int Fila_Seleccionada = 0, Columna_Seleccionada = 0;
            bool Selecciono = seleccionUsuario(filas, columnas, Fila_Seleccionada, Columna_Seleccionada);
            if (Selecciono) {
                Establecer_fichas(Tablerito, Fila_Seleccionada, Columna_Seleccionada, columnas, ESTADO_VACIO);
                eliminacionesUsuario++;
                ejecutarCicloCascada(Tablerito, filas, columnas, reserva_bytes,puntuacion, cascadasActuales,fichasEliminadasTotal, combinacionesDetectadas);
            }
            break;
        }

        case 2: { // Insertar fila
            int Fila_Destino = seleccionIndice("Fila donde insertar", filas); // 0 a filas (incluye el final)
            Agregar_fila(Tablerito, filas, columnas, reserva_bytes, Fila_Destino);
            break;
        }

        case 3: { // Eliminar fila
            if (filas <= 1) {
                cout << "No se puede eliminar la unica fila que queda.\n";
            } else {
                int Fila_Destino = seleccionIndice("Fila a eliminar", filas - 1);
                Eliminar_fila(Tablerito, filas, columnas, reserva_bytes, Fila_Destino);
            }
            break;
        }

        case 4: { // Insertar columna
            int Columna_Destino = seleccionIndice("Columna donde insertar", columnas);
            Agregar_Columna(Tablerito, filas, columnas, reserva_bytes, Columna_Destino);
            break;
        }

        case 5: { // Eliminar columna
            if (columnas <= 1) {
                cout << "No se puede eliminar la unica columna que queda.\n";
            } else {
                int Columna_Destino = seleccionIndice("Columna a eliminar", columnas - 1);
                Eliminar_columnas(Tablerito, filas, columnas, reserva_bytes, Columna_Destino);
            }
            break;
        }

        case 0: // Salir
            jugando = false;
            break;

        default:
            cout << "OPCION INVALIDA :0.\n";
            break;
        }

        if (jugando) {
            dibujarFichas(Tablerito, filas, columnas);
            dibujarBinario(Tablerito, filas, columnas);
            mostrarProgreso(puntuacion, eliminacionesUsuario, fichasEliminadasTotal,
                            combinacionesDetectadas, cascadasActuales);
        }
    }

    liberatablero(Tablerito);
    cout << "GRACIAS POR JUGAR CON NUESTRO JUEGO <3.\n";
    return 0;
}