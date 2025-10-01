#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#include "entidades.h"
#include "tablero.h"
#include "armas.h"
#include "spawn.h"


// La estructura Juego ya está definida en types.h

int seleccionar_dificultad(){
    /*
    nombre: seleccionar_dificultad
    parametros: void
    devuelve: int
    descripcion: Solicita al usuario seleccionar una dificultad y la devuelve como un entero.
    */
    int dificultad;
    printf("Seleccione la dificultad:\n");
    printf("1. Facil\n");
    printf("2. Dificil\n");
    printf("Ingrese el numero correspondiente a su eleccion: ");
    scanf("%d", &dificultad);
    while (dificultad < 1 || dificultad > 2) {
        printf("Seleccion invalida. Por favor, ingrese 1 o 2: ");
        scanf("%d", &dificultad);
    }
    return dificultad;
}

void limpiar_terminal(){
    // Limpia la pantalla de la terminal (funciona en Windows y Unix)
    #ifdef _WIN32 //para Windows
        system("cls");
    #else //para Unix/Linux/Mac
        system("clear");
    #endif
}

void turno(struct Juego *juego){
    // maneja la logica de un turno, disparo, movimiento de aliens, movimiento de juagdor, HUD, etc.
    limpiar_terminal();
    spawn_turno(juego);
    tablero_imprimir(juego);
    printf("Turno: %d | Aliens vivos: %d | Posicion jugador: %d | Aliens Restantes: %d\n",
    juego->turno, juego->vivos, juego->jugador_x, juego->pool.drone + juego->pool.especial + juego->pool.skater);
    printf("Acciones: (a) Mover Izquierda | (d) Mover Derecha | (1) Disparar Normal | (2) Disparar Perforador | (3) Disparar Especial\n");
    char accion;
    scanf(" %c", &accion);
    if (accion == 'a' || accion == 'd') {
        // Obtener la celda actual del jugador
        Celda *celda_actual = juego->t->celdas[juego->t->H - 1][juego->jugador_x];
        Alien *jugador = celda_actual->alien;
        
        int nueva_pos = juego->jugador_x;
        if (accion == 'a' && juego->jugador_x > 0) {
            nueva_pos = juego->jugador_x - 1;
        } else if (accion == 'd' && juego->jugador_x < juego->t->W - 1) {
            nueva_pos = juego->jugador_x + 1;
        }
        
        // Si la posición es válida, mover al jugador
        if (nueva_pos != juego->jugador_x) {
            // Asegurarse de que la nueva celda existe
            if (juego->t->celdas[juego->t->H - 1][nueva_pos] == NULL) {
                juego->t->celdas[juego->t->H - 1][nueva_pos] = malloc(sizeof(Celda));
                juego->t->celdas[juego->t->H - 1][nueva_pos]->alien = NULL;
                juego->t->celdas[juego->t->H - 1][nueva_pos]->dano_pend = 0;
            }
            
            // Mover al jugador
            celda_actual->alien = NULL;
            juego->t->celdas[juego->t->H - 1][nueva_pos]->alien = jugador;
            jugador->x = nueva_pos;
            juego->jugador_x = nueva_pos;
            
            // Mostrar mensaje de movimiento
            const char *direccion = (accion == 'a') ? "izquierda" : "derecha";
            printf("\n==> Jugador se movió a la %s (posición %d)\n", direccion, nueva_pos);
            pausa_ms(500);
        }
    } else if (accion == '1'){
        disparar_armas(juego, 0);
        juego->turno++;
    } else if (accion == '2'){
        if (juego->armas.ammo_perforador > 0){
            disparar_armas(juego, 1);
            juego->turno++;
        } else {
            printf("No tienes municion para el arma perforadora!\n");
        }
    } else if (accion == '3'){
        if (juego->armas.ammo_especial > 0){
            disparar_armas(juego, 2);
            juego->turno++;
        } else {
            printf("No tienes municion para el arma especial!\n");
        }
    } else {
        printf("Accion invalida.\n");
    }
    resolver_danos(juego);
    // Mover aliens cada turno
    mover_aliens(juego);
    // Incrementar el turno solo cuando sea necesario
    if (accion == '1' || 
        (accion == '2' && juego->armas.ammo_perforador > 0) || 
        (accion == '3' && juego->armas.ammo_especial > 0)) {
        juego->turno++;
    }
}

int main(){
    srand(time(NULL)); // inicializa la semilla para numeros aleatorios
    struct Juego juego;
    juego.dificultad = seleccionar_dificultad();
    juego.t = crea_tablero_dificultad(juego.dificultad);
    juego.armas.ammo_perforador = 7; // municion inicial del arma perforadora
    juego.armas.ammo_especial = 5; // municion inicial del arma especial
    juego.armas.fn[0] = arma_normal;
    juego.armas.fn[1] = arma_perforador;
    juego.armas.fn[2] = arma_especial;
    crear_jugador(&juego);
    if (juego.dificultad == 1){
        crear_pool_facil(&juego);
    }else{
        crear_pool_dificil(&juego);
    }
    juego.turno = 1;
    juego.vivos = 0;
    spawn_inicio(&juego);
    while (juego.pool.drone + juego.pool.especial + juego.pool.skater > 0 || juego.vivos > 0){
        turno(&juego);
    }
    printf("Felicidades! Has eliminado a todos los aliens!\n");
    tablero_cerrar(juego.t);
    return 0;
}