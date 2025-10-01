#ifndef ARMAS_H
#define ARMAS_H

#include "types.h"

bool disparar_armas(Juego *juego, int arma_id);
bool arma_normal(Juego *juego);
bool arma_perforador(Juego *juego);
bool arma_especial(Juego *juego);

#endif // ARMAS_H
