#include "spawn.h"
#include "types.h"
#include "entidades.h"
#include <stdlib.h>
#include "utils.h"

void crear_pool_facil(Juego *juego) {
    juego->pool.drone = 8;
    juego->pool.skater = 4;
    juego->pool.especial = 3;
    juego->pool.vivos_tope = MAX_VIVOS_FACIL;
}

void crear_pool_dificil(Juego *juego) {
    juego->pool.drone = 10;
    juego->pool.skater = 6;
    juego->pool.especial = 4;
    juego->pool.vivos_tope = MAX_VIVOS_DIFICIL;
}

void spawn_inicio(Juego *juego) {
    int spawned = 0;
    int max_inicial = (juego->dificultad == 1) ? 3 : 4;
    
    while (spawned < max_inicial) {
        int x = rand() % juego->t->W;
        Celda *celda = (Celda*)juego->t->celdas[0][x];
        
        if (celda->alien == NULL) {
            Alien *nuevo = malloc(sizeof(Alien));
            if (juego->pool.drone > 0) {
                *nuevo = drone;
                juego->pool.drone--;
            } else if (juego->pool.skater > 0) {
                *nuevo = skater;
                juego->pool.skater--;
            } else if (juego->pool.especial > 0) {
                *nuevo = especial;
                juego->pool.especial--;
            }
            nuevo->x = x;
            nuevo->y = 0;
            celda->alien = nuevo;
            spawned++;
            juego->vivos++;
        }
    }
}

Alien* intentar_crear_alien(Juego *juego, int x) {
    if (juego->t->celdas[0][x]->alien != NULL) {
        return NULL;  // Posición ocupada
    }

    int tipos_disponibles = 0;
    int aliens_disponibles[3] = {0};

    if (juego->pool.drone > 0) {
        aliens_disponibles[tipos_disponibles++] = 1;
    }
    if (juego->pool.skater > 0) {
        aliens_disponibles[tipos_disponibles++] = 2;
    }
    if (juego->pool.especial > 0) {
        aliens_disponibles[tipos_disponibles++] = 3;
    }

    if (tipos_disponibles == 0) {
        return NULL;
    }

    int tipo_elegido = aliens_disponibles[rand() % tipos_disponibles];
    
    Alien *nuevo = malloc(sizeof(Alien));
    switch(tipo_elegido) {
        case 1:
            *nuevo = drone;
            juego->pool.drone--;
            break;
        case 2:
            *nuevo = skater;
            juego->pool.skater--;
            break;
        case 3:
            *nuevo = especial;
            juego->pool.especial--;
            break;
    }
    nuevo->x = x;
    nuevo->y = 0;
    return nuevo;
}

void spawn_turno(Juego *juego) {
    if (juego->vivos >= juego->pool.vivos_tope) {
        return;
    }

    bool primer_spawn_exitoso = false;
    int intentos = 0;
    while (!primer_spawn_exitoso && intentos < juego->t->W) {
        int x = rand() % juego->t->W;
        Alien *nuevo = intentar_crear_alien(juego, x);
        if (nuevo != NULL) {
            juego->t->celdas[0][x]->alien = nuevo;
            juego->vivos++;
            primer_spawn_exitoso = true;
        }
        intentos++;
    }

    if (primer_spawn_exitoso && rand() % 100 < 30 && juego->vivos < juego->pool.vivos_tope) {
        intentos = 0;
        while (intentos < juego->t->W) {
            int x = rand() % juego->t->W;
            if (x != juego->jugador_x) {  // Evitar spawner sobre el jugador
                Alien *nuevo = intentar_crear_alien(juego, x);
                if (nuevo != NULL) {
                    juego->t->celdas[0][x]->alien = nuevo;
                    juego->vivos++;
                    break;
                }
            }
            intentos++;
        }
    }
}
