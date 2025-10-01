#include "tablero.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

Tablero* tablero_crear(int ancho, int alto) {
    Tablero *t = malloc(sizeof(Tablero));
    t->W = ancho; 
    t->H = alto;

    t->celdas = malloc(alto * sizeof(void**));
    
    for (int y = 0; y < alto; y++) {
        t->celdas[y] = malloc(ancho * sizeof(void*));
        
        for (int x = 0; x < ancho; x++) {
            Celda *celda = malloc(sizeof(Celda));
            celda->alien = NULL;
            celda->dano_pend = 0;
            t->celdas[y][x] = celda;
        }
    } 
    return t;
}

Tablero* crea_tablero_dificultad(int dificultad) {
    if (dificultad == 1) {
        return tablero_crear(EASY_W, EASY_H);
    } else {
        return tablero_crear(HRD_W, HRD_H);
    }
}

void tablero_imprimir(Juego *juego) {
    // Imprimir indicador de posición del jugador en la parte superior
    printf("\nPosición del jugador: ");
    for (int x = 0; x < juego->t->W; x++) {
        if (x == juego->jugador_x) {
            printf(" ↓ ");
        } else {
            printf("   ");
        }
    }
    printf("\n");

    // Imprimir línea separadora
    for (int x = 0; x < juego->t->W; x++) {
        printf("===");
    }
    printf("\n");

    for (int y = 0; y < juego->t->H; y++) {
        for (int x = 0; x < juego->t->W; x++) {
            if (juego->t->celdas[y][x] != NULL) {
                Celda *celda = (Celda*)juego->t->celdas[y][x];
                if (celda->alien != NULL) {
                    Alien *alien = (Alien*)celda->alien;
                    if (alien->tipo == 0) {
                        printf("\\O/");
                    } else if (alien->tipo == 1) {
                        printf("[D]");
                    } else if (alien->tipo == 2) {
                        printf("[S]");
                    } else if (alien->tipo == 3) {
                        printf("[E]");
                    }
                } else {
                    printf("[ ]");
                }
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
}

void tablero_cerrar(Tablero *tablero) {
    for (int y = 0; y < tablero->H; y++) {
        for (int x = 0; x < tablero->W; x++) {
            if (tablero->celdas[y][x] != NULL) {
                Celda *celda = tablero->celdas[y][x];
                if (celda->alien != NULL) {
                    free(celda->alien);
                }
                free(celda);
            }
        }
        free(tablero->celdas[y]);
    }
    free(tablero->celdas);
    free(tablero);
}
