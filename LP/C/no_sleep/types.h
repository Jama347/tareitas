#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef struct Alien {
    int tipo;
    int hp;
    int x, y;
    int dx;
} Alien;

typedef struct Celda {
    Alien *alien;
    int dano_pend;
} Celda;

typedef struct Tablero {
    int W, H;
    Celda ***celdas;
} Tablero;

typedef struct PoolAliens {
    int especial;
    int skater;
    int drone;
    int vivos_tope;
} PoolAliens;

struct Juego;  // forward declaration
typedef bool (*FuncArmas)(struct Juego* j);

typedef struct Armas {
    int ammo_perforador;
    int ammo_especial;
    FuncArmas fn[3];
} Armas;

typedef struct Juego {
    Tablero *t;
    Armas armas;
    PoolAliens pool;
    int dificultad;
    int turno, vivos, jugador_x;
} Juego;

#endif // TYPES_H
