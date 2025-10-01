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
    // Spawns iniciales en la primera fila
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

    // Contar cuántos tipos de aliens están disponibles
    int tipos_disponibles = 0;
    int aliens_disponibles[3] = {0};  // Para drone, skater y especial

    if (juego->pool.drone > 0) {
        aliens_disponibles[tipos_disponibles++] = 1;  // 1 = drone
    }
    if (juego->pool.skater > 0) {
        aliens_disponibles[tipos_disponibles++] = 2;  // 2 = skater
    }
    if (juego->pool.especial > 0) {
        aliens_disponibles[tipos_disponibles++] = 3;  // 3 = especial
    }

    if (tipos_disponibles == 0) {
        return NULL;  // No hay aliens disponibles
    }

    // Elegir un tipo de alien al azar entre los disponibles
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
        return;  // No spawneamos si ya hay demasiados aliens vivos
    }

    // Intentar el primer spawn (garantizado si hay espacio)
    bool primer_spawn_exitoso = false;
    int intentos = 0;
    while (!primer_spawn_exitoso && intentos < juego->t->W) {
        int x = rand() % juego->t->W;
        Alien *nuevo = intentar_crear_alien(juego, x);
        if (nuevo != NULL) {
            juego->t->celdas[0][x]->alien = nuevo;
            juego->vivos++;
            primer_spawn_exitoso = true;
            printf("\n>> Nuevo alien tipo %d apareció en la posición (0, %d)\n", nuevo->tipo, x);
            Sleep(500);
        }
        intentos++;
    }

    // 30% de probabilidad para un segundo spawn
    if (primer_spawn_exitoso && rand() % 100 < 30 && juego->vivos < juego->pool.vivos_tope) {
        intentos = 0;
        while (intentos < juego->t->W) {
            int x = rand() % juego->t->W;
            Alien *nuevo = intentar_crear_alien(juego, x);
            if (nuevo != NULL) {
                juego->t->celdas[0][x]->alien = nuevo;
                juego->vivos++;
                printf("\n>> ¡Spawn extra! Nuevo alien tipo %d apareció en la posición (0, %d)\n", nuevo->tipo, x);
                Sleep(500);
                break;
            }
            intentos++;
        }
    }
}
