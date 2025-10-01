#ifndef TABLERO_H
#define TABLERO_H

#include "types.h"

#define HRD_W 7
#define HRD_H 15  //Dificil
#define EASY_W 5 
#define EASY_H 15  //Facil

Tablero* tablero_crear(int ancho, int alto);
Tablero* crea_tablero_dificultad(int dificultad);
void tablero_imprimir(Juego *juego);
void tablero_cerrar(Tablero *tablero);

#endif // TABLERO_H