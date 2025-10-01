#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Combate 1.hpp"

using namespace std;

#ifndef DATOS_HPP
#define DATOS_HPP

// ===== INICIALIZACIÓN DE LISTAS =====

void inicializarEnemigosBase(list<Enemy>& enemigosBase) {
    // Desechos vivientes
    enemigosBase.append(Enemy("desecho_verde", 12, 10, {0, 0, 0, 0, 0}, 0.85));
    enemigosBase.append(Enemy("desecho_azul", 14, 8, {0.01, -0.1, 0.1, 0.1, -0.1}, 0.85));
    enemigosBase.append(Enemy("desecho_rojo", 10, 12, {0.01, 0.01, -0.1, -0.1, 0.01}, 0.85));
    
    // Cadáveres en descomposición
    enemigosBase.append(Enemy("no_muerto", 18, 12, {0, 0.04, 0.04, -0.3, -0.3}, 0.8));
    enemigosBase.append(Enemy("no_muerto_pesado", 20, 12, {0.5, 0, 0, -0.2, -0.2}, 0.8));
    enemigosBase.append(Enemy("no_muerto_violento", 14, 16, {0, 0.04, 0.04, -0.2, -0.2}, 0.85));
}

void inicializarEnemigosDefensivos(list<Enemy>& enemigosDefensivos) {
    // Rocas Vivientes
    enemigosDefensivos.append(Enemy("Gran_Roca", 35, 4, {-0.5, 0.5, 0.5, 0.5, 0.5}, 0.6));
    enemigosDefensivos.append(Enemy("Roca_Brillante_Caliente", 30, 6, {-0.5, 0.9, 0.2, 0.2, 0.2}, 0.6));
    enemigosDefensivos.append(Enemy("Roca_Brillante_Fria", 37, 3, {-0.6, -0.3, 0.95, 0.4, 0.4}, 0.5));
    enemigosDefensivos.append(Enemy("Roca_Flotante", 33, 9, {-0.4, 0.6, -0.2, 1, -0.4}, 0.75));
    enemigosDefensivos.append(Enemy("Roca_Electrica", 35, 7, {-0.5, 0.2, 0.2, 0.2, 0.9}, 0.85));
    
    // Ratas
    enemigosDefensivos.append(Enemy("Rata", 17, 10, {-1, 0.8, 0.8, 0.8, 0.8}, 0.8));
    enemigosDefensivos.append(Enemy("Rata_Bola_de_Fuego", 17, 10, {-1, -1, 0.95, 0.95, 0.95}, 0.8));
    enemigosDefensivos.append(Enemy("Rata_Carambano", 17, 10, {-1, 0.95, -1, 0.95, 0.95}, 0.8));
    enemigosDefensivos.append(Enemy("Rata_Vendaval", 17, 10, {-1, 0.95, 0.95, -1, 0.95}, 0.8));
    enemigosDefensivos.append(Enemy("Rata_Carga", 17, 10, {-1, 0.95, 0.95, 0.95, -1}, 0.8));
}

void inicializarEnemigosFuertes(list<Enemy>& enemigosFuertes) {
    // Saqueadores
    enemigosFuertes.append(Enemy("Saqueador", 10, 16, {0.2, -0.1, -0.1, -0.1, -0.1}, 0.65));
    enemigosFuertes.append(Enemy("Saqueador_con_kunai", 12, 20, {0, 0.1, 0.1, -0.3, -0.1}, 0.70));
    enemigosFuertes.append(Enemy("Saqueador_sobre_una_ballesta", 14, 30, {0.2, -0.2, -0.2, -0.1, 0.3}, 0.3));
    enemigosFuertes.append(Enemy("Saqueador_Brayan", 6, 19, {0.2, -0.3, 0.1, -0.1, 0}, 0.85));
    enemigosFuertes.append(Enemy("Saqueador_en_un_tanque_roto", 24, 35, {0.6, -0.2, -0.2, -0.2, -0.2}, 0.45));
    enemigosFuertes.append(Enemy("Saqueador_en_un_cohete", 4, 35, {0, 0, 0, 0, 0}, 0.50));
    
    // Mutantes
    enemigosFuertes.append(Enemy("Mutante", 18, 19, {0.2, -0.1, 0.2, -0.3, 0.1}, 0.3));
    enemigosFuertes.append(Enemy("Mutante_con_un_palo", 18, 24, {0, -0.4, 0, 0, 0.3}, 0.2));
    enemigosFuertes.append(Enemy("Orco_con_dos_palos", 18, 29, {0, -0.8, -0.4, 0, 0.6}, 0.15));
    enemigosFuertes.append(Enemy("Dos_Mutantes_amarrados_por_la_lengua", 36, 38, {0, 0, 0, 0, 0}, 0.1));
    enemigosFuertes.append(Enemy("Mutante_Mujer", 16, 18, {-0.3, 0, -0.1, 0, 0.2}, 0.6));
    
    // Enemigos especiales
    enemigosFuertes.append(Enemy("Pois", 150, 0.5, {0.85, 0.85, 0.85, 0.85, 0.85}, 0.95));
    enemigosFuertes.append(Enemy("Jama", 0.001, 999, {-1, -1, -1, -1, -1}, 0.0001));
}
#endif /* DATOS_HPP */