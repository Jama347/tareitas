#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "types.h"

extern const Alien drone;
extern const Alien skater;
extern const Alien especial;

void mover_aliens(Juego *juego);
void resolver_danos(Juego *juego);
void crear_jugador(Juego *juego);

#endif // ENTIDADES_H