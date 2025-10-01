#include "armas.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

bool disparar_armas(Juego *juego, int arma_id) {
    if (arma_id < 0 || arma_id > 2) {
        set_message("Arma invalida");
        return false; 
    } 
    if (juego->armas.fn[arma_id] != NULL) {
        return juego->armas.fn[arma_id](juego);
    }
    return false;
}

bool arma_normal(Juego *juego) {
    int dano = 1;
    bool hit = false;
    for (int y = juego->t->H-2; y >= 0; y--) {
        if (juego->t->celdas[y][juego->jugador_x] != NULL) {
            Celda *celda = (Celda*)juego->t->celdas[y][juego->jugador_x];
            if (celda->alien != NULL && celda->alien->tipo != 0) {  // Verificar que hay un alien (no jugador)
                celda->dano_pend += dano;
                char mensaje[100];
                sprintf(mensaje, "¡DISPARO NORMAL! Impacto en alien tipo %d en posición (%d, %d)", 
                        celda->alien->tipo, y, juego->jugador_x);
                set_message(mensaje);
                hit = true;
                break;
            }
        }
    }
    if (!hit) {
        char mensaje[100];
        sprintf(mensaje, "¡DISPARO NORMAL! Sin impactos en la columna %d", juego->jugador_x);
        set_message(mensaje);
    }
    return false;
}

bool arma_perforador(Juego *juego) {
    if (juego->armas.ammo_perforador <= 0) {
        set_message("¡Sin munición para el arma perforadora!");
        return false;
    }

    int dano = 1;
    bool hit = false;
    for (int y = juego->t->H-2; y >= 0; y--) {
        if (juego->t->celdas[y][juego->jugador_x] != NULL) {
            Celda *celda = (Celda*)juego->t->celdas[y][juego->jugador_x];
            celda->dano_pend += dano;
            hit = true;
        }
    }
    if (hit) {
        juego->armas.ammo_perforador--;
        char mensaje[100];
        sprintf(mensaje, "¡DISPARO PERFORADOR! Atacando columna %d (Munición: %d)", 
                juego->jugador_x, juego->armas.ammo_perforador);
        set_message(mensaje);
        return true;
    }
    return false;
}

bool arma_especial(Juego *juego) {
    if (juego->armas.ammo_especial <= 0) {
        set_message("¡Sin munición para el arma especial!");
        return false;
    }

    int dano = 1;
    int x = juego->jugador_x;
    bool hit = false;
    
    for (int y = juego->t->H-2; y >= 0; y--) {
        // Disparo en la columna del jugador
        if (juego->t->celdas[y][x] != NULL) {
            Celda *celda = (Celda*)juego->t->celdas[y][x];
            celda->dano_pend += dano;
            hit = true;
        }
        // Disparo en la columna izquierda adyacente
        if (x > 0 && juego->t->celdas[y][x-1] != NULL) {
            Celda *celda_izq = (Celda*)juego->t->celdas[y][x-1];
            celda_izq->dano_pend += dano;
            hit = true;
        }
        // Disparo en la columna derecha adyacente
        if (x < juego->t->W - 1 && juego->t->celdas[y][x+1] != NULL) {
            Celda *celda_der = (Celda*)juego->t->celdas[y][x+1];
            celda_der->dano_pend += dano;
            hit = true;
        }
    }
    
    if (hit) {
        juego->armas.ammo_especial--;
        char mensaje[100];
        sprintf(mensaje, "¡DISPARO ESPECIAL! Atacando columnas %d, %d y %d (Munición: %d)", 
                x - 1, x, x + 1, juego->armas.ammo_especial);
        set_message(mensaje);
        return true;
    }
    return false;
}
