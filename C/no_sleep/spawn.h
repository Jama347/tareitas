#ifndef SPAWN_H
#define SPAWN_H

#include "types.h"

#define POOL_EASY 15 
#define POOL_HRD 20
#define MAX_VIVOS_FACIL 6
#define MAX_VIVOS_DIFICIL 8

void spawn_inicio(Juego *juego);
void spawn_turno(Juego *juego);
void crear_pool_facil(Juego *juego);
void crear_pool_dificil(Juego *juego);

#endif // SPAWN_H
