#include "types.h"
#include "entidades.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

// Definición de las variables globales
const Alien drone = {1, 2, 0, 0, 0};   // inicializacion de los aliens
const Alien skater = {2, 1, 0, 0, 1};
const Alien especial = {3, 5, 0, 0, 0};

void mover_aliens(Juego *juego) {
    static int contador_movimientos = 0;  // Contador para controlar el descenso
    contador_movimientos++;

    // Primera pasada: recolectar todos los aliens y sus posiciones originales
    int max_aliens = juego->t->W * juego->t->H;
    Alien **aliens = malloc(sizeof(Alien*) * max_aliens);
    Celda **celdas_orig = malloc(sizeof(Celda*) * max_aliens);
    int num_aliens = 0;

    // Recolectar aliens de abajo hacia arriba para mover primero los más cercanos al jugador
    for (int y = juego->t->H - 1; y >= 0; y--) {
        for (int x = 0; x < juego->t->W; x++) {
            if (juego->t->celdas[y][x] != NULL) {
                Celda *celda = (Celda*)juego->t->celdas[y][x];
                if (celda->alien != NULL && celda->alien->tipo != 0) { // tipo 0 es el jugador
                    aliens[num_aliens] = celda->alien;
                    celdas_orig[num_aliens] = celda;
                    num_aliens++;
                }
            }
        }
    }

    // Segunda pasada: mover cada alien una vez
    for (int i = 0; i < num_aliens; i++) {
        Alien *alien = aliens[i];
        Celda *celda_orig = celdas_orig[i];
        
        // Calcular nueva posición
        int new_x = alien->x + alien->dx;
        int new_y = alien->y;
        
        // Si llegamos a un borde lateral
        if (new_x < 0 || new_x >= juego->t->W) {
            alien->dx = -alien->dx; // Cambiar dirección
            new_x = alien->x; // Volver a la posición X original
            // Bajar cada dos movimientos globales
            if (contador_movimientos % 2 == 0) {
                new_y = alien->y + 1;
            }
        }
        
        // Verificar si el alien ha llegado a la fila del jugador
        if (new_y == juego->t->H - 1) {
            printf("Los aliens han llegado al jugador! Fin del juego.\n");
            free(aliens);
            free(celdas_orig);
            exit(0);
        }

        // Si la nueva posición está fuera del tablero, no mover
        if (new_y >= juego->t->H) {
            continue;
        }

        // Asegurarse de que la celda destino existe
        if (juego->t->celdas[new_y][new_x] == NULL) {
            juego->t->celdas[new_y][new_x] = malloc(sizeof(Celda));
            juego->t->celdas[new_y][new_x]->alien = NULL;
            juego->t->celdas[new_y][new_x]->dano_pend = 0;
        }

        // Verificar si la nueva posición está ocupada
        Celda *celda_destino = juego->t->celdas[new_y][new_x];
        if (celda_destino->alien == NULL) {
            // Mover el alien
            celda_destino->alien = alien;
            celda_orig->alien = NULL;
            alien->x = new_x;
            alien->y = new_y;
        } else {
            // Si no podemos movernos lateralmente, intentamos bajar
            if (new_y == alien->y && contador_movimientos % 2 == 0) {
                new_y = alien->y + 1;
                if (new_y < juego->t->H && juego->t->celdas[new_y][alien->x]->alien == NULL) {
                    juego->t->celdas[new_y][alien->x]->alien = alien;
                    celda_orig->alien = NULL;
                    alien->y = new_y;
                }
            }
        }
    }

    free(aliens);
    free(celdas_orig);
                }

void resolver_danos(Juego *juego) {
    for (int y = 0; y < juego->t->H; y++) {
        for (int x = 0; x < juego->t->W; x++) {
            if (juego->t->celdas[y][x] != NULL) {
                Celda *celda = juego->t->celdas[y][x];
                if (celda->alien != NULL && celda->dano_pend > 0) {
                    celda->alien->hp -= celda->dano_pend;
                    if (celda->alien->hp <= 0) {
                        // El alien ha sido destruido
                        if (celda->alien->tipo != 0) {  // No contar al jugador
                            juego->vivos--;
                            char mensaje[100];
                            sprintf(mensaje, "¡Alien tipo %d destruido en posición (%d, %d)!", 
                                    celda->alien->tipo, y, x);
                            set_message(mensaje);
                        }
                        free(celda->alien);
                        celda->alien = NULL;
                    }
                    celda->dano_pend = 0;
                }
            }
        }
    }
}

void crear_jugador(Juego *juego) {
    Alien *jugador = malloc(sizeof(Alien));
    jugador->tipo = 0;
    jugador->hp = 1;
    jugador->x = juego->t->W / 2;
    jugador->y = juego->t->H - 1;
    
    Celda *celda = malloc(sizeof(Celda));
    celda->alien = jugador;
    celda->dano_pend = 0;
    
    juego->t->celdas[jugador->y][jugador->x] = celda;
    juego->jugador_x = jugador->x;
}
