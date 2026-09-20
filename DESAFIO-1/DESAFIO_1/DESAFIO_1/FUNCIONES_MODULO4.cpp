#include <iostream>
#include <cstdlib> // para la funcion srand
#include "FUNCIONES_MODULO3.h"
#include "FUNCIONES_MODULO1.h"
#include "SIMBOLOGIA_FICHAS.h"
using namespace std;

// Traduce el código de 3 bits al símbolo acordado por el equipo.
// Nota: devuelve const char* (literal de C)
static const char* simboloDeFicha(unsigned char valor) {
    switch (valor) {
    case ESTADO_VACIO:    return "Ø";
    case FICHA_RHO:       return "ρ";
    case FICHA_PI:        return "π";
    case FICHA_EPSILON:   return "ε";
    case FICHA_DELTA:     return "Δ";
    case FICHA_X:         return "X";
    case FICHA_Y:         return "Y";
    case ESTADO_ESPACIAL: return "$";
    default:              return "?";
    }
}


static int leerEnteroValidado() { // static: constante global Y HACE QUE EQL VALOR NO SE BORRE Y SOLO SE PUEDE UTILIZAR ENMODULO 1
    int valor;
    while (!(cin >> valor)) {
        if (cin.eof()) {
            cout << "Entrada terminada inesperadamente. Cerrando el programa."<<endl;
            exit(0);
        }
        cin.clear(); // limpia el estado de error de cin
        cin.ignore(1000000, '\n'); // descarta la entrada invalida
        cout << "Entrada invalida, ingrese un numero entero: "<<endl;
    }
    return valor;
}

void dibujarFichas(const unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas, int columnas) {
    cout << "TABLERO DE FICHAS :0"<<endl;
    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            unsigned char valor = Obtener_Fichas(PUNTERO_BLOQUE_MEMORIA, fila, columna, columnas);
            cout << simboloDeFicha(valor) << " "<<endl;
        }
        cout << endl;
    }
}

void dibujarBinario(const unsigned char* PUNTERO_BLOQUE_MEMORIA, int filas, int columnas) {
    int Total_Bits = filas * columnas * 3;
    int Total_Bytes = (Total_Bits + 7) / 8;

    cout << "VISTA BINARIA DELL TABLERO"<<endl;
    for (int Byte_Actual = 0; Byte_Actual < Total_Bytes; Byte_Actual++) {
        for (int bit = 7; bit >= 0; bit--) {
            unsigned char Bit_Val = (PUNTERO_BLOQUE_MEMORIA[Byte_Actual] >> bit) & 0x01;
            cout << (int)Bit_Val;
        }
        cout << " ";
        if ((Byte_Actual + 1) % 4 == 0) cout <<endl;
    }
    cout << endl;
}

void mostrarProgreso(int puntuacion, int eliminacionesUsuario, int fichasEliminadasTotal,int combinacionesDetectadas, int cascadasActuales) {
    cout <<"ESTADO DEL JUEGO :)"<<endl;
    cout << "PUNTUACION: " << puntuacion << endl;
    cout << "ELIMINACIONES DEL USUARIO: " << eliminacionesUsuario << endl;
    cout << "TOTAL DE FICHAS ELIMINADAS: " << fichasEliminadasTotal << endl;
    cout << "COMBINACIONES DETECTADAS: " << combinacionesDetectadas <<endl;
    cout << "CASCADAS EN LA ULTIMA JUGADA: " << cascadasActuales <<endl;
}

int menuPrincipal() {
    cout << "MENU DEL JUEGO"<<endl;
    cout << "1. ELIMINA FICHA :0"<<endl;
    cout << "2. INSERTAR FILA ;)"<<endl;
    cout << "3. ELIMINAR FILA :0"<<endl;
    cout << "4. INSERTAR COLUMNA :)"<<endl;
    cout << "5. ELIMINAR COLUMNA"<<endl;
    cout << "0. SALIR :/"<<endl;
    cout << "OPCION: "<<endl;
    return leerEnteroValidado();
}

bool seleccionUsuario(int filas, int columnas, int& Fila_Seleccionada, int& Columna_Seleccionada) {
    while (true) {
        cout << "SELECCIONE UNA FICHA PARA ELIMINAR(FILA Y COLUMNA O ELIJA -1 -1 PARA VOLVER AL MENU: "<<endl;
        Fila_Seleccionada = leerEnteroValidado();
        Columna_Seleccionada = leerEnteroValidado();

        if (Fila_Seleccionada == -1 && Columna_Seleccionada == -1) return false;

        if (Fila_Seleccionada >= 0 && Fila_Seleccionada < filas && Columna_Seleccionada >= 0 && Columna_Seleccionada < columnas) return true;

        cout << "LA POSICION ELEGIDA ESTA FUERA DEL RANGO. INTENTE DE NUEVO"<<endl;
    }
}


int seleccionIndice(const char* mensaje, int Limite_Inclusive) {
    while (true) {
        cout << mensaje << " (0 a " << Limite_Inclusive << "): ";
        int Indice_Elegido = leerEnteroValidado();
        if (Indice_Elegido >= 0 && Indice_Elegido <= Limite_Inclusive) return Indice_Elegido;
        cout << "Indice fuera de rango. Intente de nuevo.\n";
    }
}

void dimensionesIni(int& filas, int& columnas) {
    do {
        cout << "Numero de filas del tablero: ";
        filas = leerEnteroValidado();
        if (filas <= 0) cout << "Debe ser un numero positivo.\n";
    } while (filas <= 0);

    do {
        cout << "Numero de columnas del tablero: ";
        columnas = leerEnteroValidado();
        if (columnas <= 0) cout << "Debe ser un numero positivo.\n";
    } while (columnas <= 0);
}


