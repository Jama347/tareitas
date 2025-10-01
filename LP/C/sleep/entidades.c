#include "types.h"
#include "entidades.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void mostrar_mensaje_entidad(const char* mensaje) {
    printf("\n***********************************************\n");
    printf("%s", mensaje);
    printf("\n***********************************************\n");
    pausa_ms(800);  // Pausa de 0.8 segundos
}

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
                Celda *celda = (Celda*)juego->t->celdas[y][x];
                if (celda->alien != NULL && celda->dano_pend > 0) {
                    Alien *alien = celda->alien;
                    alien->hp -= celda->dano_pend;
                    if (alien->hp <= 0) {
                        const char* tipo_alien;
                        bool drop_municion = false;
                        char mensaje_municion[100] = "";

                        switch(alien->tipo) {
                            case 1: 
                                tipo_alien = "Drone"; 
                                break;
                            case 2: 
                                tipo_alien = "Skater";
                                if (rand() % 100 < 25) {  // 25% de probabilidad
                                    juego->armas.ammo_perforador++;
                                    drop_municion = true;
                                    sprintf(mensaje_municion, "\n¡El Skater dejó munición perforadora! (+1 munición perforadora)");
                                }
                                break;
                            case 3: 
                                tipo_alien = "Especial";
                                if (rand() % 100 < 25) {  // 25% de probabilidad
                                    juego->armas.ammo_especial++;
                                    drop_municion = true;
                                    sprintf(mensaje_municion, "\n¡El Alien Especial dejó munición especial! (+1 munición especial)");
                                }
                                break;
                            default: 
                                tipo_alien = "Desconocido";
                        }

                        char mensaje[200];
                        sprintf(mensaje, "¡ALIEN %s ELIMINADO! Posición (%d, %d)%s", 
                                tipo_alien, alien->y, alien->x, mensaje_municion);
                        mostrar_mensaje_entidad(mensaje);

                        if (drop_municion) {
                            Sleep(800); // Pausa adicional para que el mensaje de munición sea visible
                        }

                        free(alien);
                        celda->alien = NULL;
                        juego->vivos--;
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
