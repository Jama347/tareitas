#include <iostream>
#include <cstdlib>
#include "estructuras_datos.hpp"
#include <ctime>
#include <string>
#include "construir.cpp"
using namespace std;

// ===== INICIALIZACIÓN DE LISTAS =====

void inicializarEnemigosBase(ListaEnlazada<Enemy>& enemigosBase) {
    // Desechos vivientes
    enemigosBase.insertarAlFinal(Enemy("desecho_verde", 12, 10, {0, 0, 0, 0, 0}, 0.85));
    enemigosBase.insertarAlFinal(Enemy("desecho_azul", 14, 8, {0.01, -0.1, 0.1, 0.1, -0.1}, 0.85));
    enemigosBase.insertarAlFinal(Enemy("desecho_rojo", 10, 12, {0.01, 0.01, -0.1, -0.1, 0.01}, 0.85));
    
    // Cadáveres en descomposición
    enemigosBase.insertarAlFinal(Enemy("no_muerto", 18, 12, {0, 0.04, 0.04, -0.3, -0.3}, 0.8));
    enemigosBase.insertarAlFinal(Enemy("no_muerto_pesado", 20, 12, {0.5, 0, 0, -0.2, -0.2}, 0.8));
    enemigosBase.insertarAlFinal(Enemy("no_muerto_violento", 14, 16, {0, 0.04, 0.04, -0.2, -0.2}, 0.85));
}

void inicializarEnemigosDefensivos(ListaEnlazada<Enemy>& enemigosDefensivos) {
    // Rocas Vivientes
    enemigosDefensivos.insertarAlFinal(Enemy("Gran_Roca", 35, 4, {-0.5, 0.5, 0.5, 0.5, 0.5}, 0.6));
    enemigosDefensivos.insertarAlFinal(Enemy("Roca_Brillante_Caliente", 30, 6, {-0.5, 0.9, 0.2, 0.2, 0.2}, 0.6));
    enemigosDefensivos.insertarAlFinal(Enemy("Roca_Brillante_Fria", 37, 3, {-0.6, -0.3, 0.95, 0.4, 0.4}, 0.5));
    enemigosDefensivos.insertarAlFinal(Enemy("Roca_Flotante", 33, 9, {-0.4, 0.6, -0.2, 1, -0.4}, 0.75));
    enemigosDefensivos.insertarAlFinal(Enemy("Roca_Electrica", 35, 7, {-0.5, 0.2, 0.2, 0.2, 0.9}, 0.85));
    
    // Ratas
    enemigosDefensivos.insertarAlFinal(Enemy("Rata", 17, 10, {-1, 0.8, 0.8, 0.8, 0.8}, 0.8));
    enemigosDefensivos.insertarAlFinal(Enemy("Rata_Bola_de_Fuego", 17, 10, {-1, -1, 0.95, 0.95, 0.95}, 0.8));
    enemigosDefensivos.insertarAlFinal(Enemy("Rata_Carambano", 17, 10, {-1, 0.95, -1, 0.95, 0.95}, 0.8));
    enemigosDefensivos.insertarAlFinal(Enemy("Rata_Vendaval", 17, 10, {-1, 0.95, 0.95, -1, 0.95}, 0.8));
    enemigosDefensivos.insertarAlFinal(Enemy("Rata_Carga", 17, 10, {-1, 0.95, 0.95, 0.95, -1}, 0.8));
}

void inicializarEnemigosFuertes(ListaEnlazada<Enemy>& enemigosFuertes) {
    // Saqueadores
    enemigosFuertes.insertarAlFinal(Enemy("Saqueador", 10, 16, {0.2, -0.1, -0.1, -0.1, -0.1}, 0.65));
    enemigosFuertes.insertarAlFinal(Enemy("Saqueador_con_kunai", 12, 20, {0, 0.1, 0.1, -0.3, -0.1}, 0.70));
    enemigosFuertes.insertarAlFinal(Enemy("Saqueador_sobre_una_ballesta", 14, 30, {0.2, -0.2, -0.2, -0.1, 0.3}, 0.3));
    enemigosFuertes.insertarAlFinal(Enemy("Saqueador_Brayan", 6, 19, {0.2, -0.3, 0.1, -0.1, 0}, 0.85));
    enemigosFuertes.insertarAlFinal(Enemy("Saqueador_en_un_tanque_roto", 24, 35, {0.6, -0.2, -0.2, -0.2, -0.2}, 0.45));
    enemigosFuertes.insertarAlFinal(Enemy("Saqueador_en_un_cohete", 4, 35, {0, 0, 0, 0, 0}, 0.50));
    
    // Mutantes
    enemigosFuertes.insertarAlFinal(Enemy("Mutante", 18, 19, {0.2, -0.1, 0.2, -0.3, 0.1}, 0.3));
    enemigosFuertes.insertarAlFinal(Enemy("Mutante_con_un_palo", 18, 24, {0, -0.4, 0, 0, 0.3}, 0.2));
    enemigosFuertes.insertarAlFinal(Enemy("Orco_con_dos_palos", 18, 29, {0, -0.8, -0.4, 0, 0.6}, 0.15));
    enemigosFuertes.insertarAlFinal(Enemy("Dos_Mutantes_amarrados_por_la_lengua", 36, 38, {0, 0, 0, 0, 0}, 0.1));
    enemigosFuertes.insertarAlFinal(Enemy("Mutante_Mujer", 16, 18, {-0.3, 0, -0.1, 0, 0.2}, 0.6));
    
    // Enemigos especiales
    enemigosFuertes.insertarAlFinal(Enemy("Pois", 150, 0.5, {0.85, 0.85, 0.85, 0.85, 0.85}, 0.95));
    enemigosFuertes.insertarAlFinal(Enemy("Jama", 0.001, 999, {-1, -1, -1, -1, -1}, 0.0001));
}

void inicializarArmasMelee(ListaEnlazada<Weapon>& armasMelee) {
    armasMelee.insertarAlFinal(Weapon("kunai", {5, 0, 0, 0, 0}, 1, 5, 1, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("kunaikunai", {10, 0, 0, 0, 0}, 1, 10, 2, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Machete", {8, 0, 0, 0, 0}, 1, 7, 1, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Machete_al_Machote", {13, 0, 0, 0, 0}, 1, 9, 1, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Hacha_Oxidada", {9, 0, 0, 0, 0}, 0.9, 7, 1, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Hacha", {15, 0, 0, 0, 0}, 0.9, 10, 1, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Hacha_de_Guerra", {20, 0, 0, 0, 0}, 0.85, 15, 2, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Microfono", {6, 0, 0, 0, 0}, 1, 4, 1, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Chatarra", {2, 0, 0, 0, 0}, 0.7, 7, 1, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("TUS_MANOS!!!", {3, 0, 0, 0, 0}, 1, 2, 5, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Puños_Americano", {5, 0, 0, 0, 0}, 1, 2, 5, false, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Latigo_de_Cuero", {10, 0, 0, 0, 0}, 0.9, 12, 1, true, 1, 0, 0, 0, 0));
    armasMelee.insertarAlFinal(Weapon("Cadena_Larga", {15, 0, 0, 0, 0}, 0.9, 17, 1, true, 1, 0, 0, 0, 0));
}

void inicializarArmasMeleeElementales(ListaEnlazada<Weapon>& armasMeleeElementales) {
    armasMeleeElementales.insertarAlFinal(Weapon("Kunais_Cargados", {10, 0, 0, 0, 5}, 1, 10, 2, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.insertarAlFinal(Weapon("Machete_en_Llamas", {13, 7, 0, 0, 0}, 1, 9, 1, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.insertarAlFinal(Weapon("Hacha_Tundrica", {20, 0, 10, 0, 0}, 0.85, 15, 2, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.insertarAlFinal(Weapon("Chatarra_Radioactiva", {2, 2, 2, 2, 2}, 0.85, 7, 1, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.insertarAlFinal(Weapon("Puños_ligeros", {5, 0, 0, 3, 0}, 1, 10, 5, false, 1, 0, 0, 0, 0));
}

void inicializarArmasRanger(ListaEnlazada<Weapon>& armasRanger) {
    armasRanger.insertarAlFinal(Weapon("Arco_Improvisado", {9, 0, 0, 0, 0}, 0.7, 4, 5, false, 2, 5, 15, 0, 0));
    armasRanger.insertarAlFinal(Weapon("Arco", {12, 0, 0, 0, 0}, 0.9, 10, 3, false, 2, 6, 15, 0, 0));
    armasRanger.insertarAlFinal(Weapon("Ballesta", {16, 0, 0, 0, 0}, 0.8, 10, 2, false, 2, 3, 17, 0, 0));
    armasRanger.insertarAlFinal(Weapon("Pistola", {1, 0, 0, 0, 0}, 0.95, 3, 10, false, 2, 30, 17, 0, 0));
    armasRanger.insertarAlFinal(Weapon("Escopeta", {18, 0, 0, 0, 0}, 0.8, 14, 2, true, 2, 4, 19, 0, 0));
    armasRanger.insertarAlFinal(Weapon("ESCOPETA!!!", {25, 0, 0, 0, 0}, 0.85, 18, 2, true, 2, 4, 25, 0, 0));
    armasRanger.insertarAlFinal(Weapon("smg", {0.5, 0, 0, 0, 0}, 0.95, 7, 30, false, 2, 60, 17, 0, 0));
    armasRanger.insertarAlFinal(Weapon("RATATATATTATATTATATATTA!!!!!", {1, 0, 0, 0, 0}, 0.95, 7, 30, false, 2, 60, 17, 0, 0));
    armasRanger.insertarAlFinal(Weapon("BOOM!!!", {30, 0, 0, 0, 0}, 0.3, 30, 1, true, 2, 5, 30, 0, 0));
    armasRanger.insertarAlFinal(Weapon("KABOOM!!!", {50, 0, 0, 0, 0}, 0.3, 35, 1, true, 2, 5, 30, 0, 0));
}

void inicializarArmasRangerElementales(ListaEnlazada<Weapon>& armasRangerElementales) {
    armasRangerElementales.insertarAlFinal(Weapon("Ballesta_Encantada", {16, 0, 0, 4, 4}, 0.8, 10, 2, false, 2, 5, 15, 0, 0));
    armasRangerElementales.insertarAlFinal(Weapon("Lanzallamas", {2, 20, 0, 0, 0}, 0.95, 20, 5, true, 2, 30, 7, 0, 0));
}

void inicializarArmasMagicasLowCost(ListaEnlazada<Weapon>& armasMagicasLow) {
    armasMagicasLow.insertarAlFinal(Weapon("Ascuas", {0, 13, 0, 0, 0}, 0.95, 5, 3, true, 3, 0, 0, 3, 5));
    armasMagicasLow.insertarAlFinal(Weapon("Bola_Hielo", {0, 0, 15, 0, 0}, 0.95, 5, 3, false, 3, 0, 0, 3, 5));
    armasMagicasLow.insertarAlFinal(Weapon("Aerochorro", {0, 0, 0, 13, 0}, 0.95, 5, 3, true, 3, 0, 0, 3, 5));
    armasMagicasLow.insertarAlFinal(Weapon("Chispa", {0, 0, 0, 0, 15}, 0.95, 5, 3, false, 3, 0, 0, 3, 5));
    armasMagicasLow.insertarAlFinal(Weapon("Ascuas_Aerochorreantes", {0, 13, 0, 13, 0}, 0.95, 10, 6, true, 3, 0, 0, 3, 10));
    armasMagicasLow.insertarAlFinal(Weapon("Bola_de_ChispaHielo", {0, 0, 15, 0, 15}, 0.95, 10, 6, false, 3, 0, 0, 3, 10));
    armasMagicasLow.insertarAlFinal(Weapon("TetraElementalidad", {0, 7, 7, 7, 7}, 0.95, 10, 5, true, 3, 0, 0, 3, 10));
}

void inicializarArmasMagicasHighDamage(ListaEnlazada<Weapon>& armasMagicasHigh) {
    armasMagicasHigh.insertarAlFinal(Weapon("Bola_de_Fuego", {0, 22, 0, 0, 0}, 0.9, 7, 3, true, 3, 0, 0, 10, 20));
    armasMagicasHigh.insertarAlFinal(Weapon("Carambano", {0, 0, 27, 0, 0}, 0.9, 7, 3, false, 3, 0, 0, 10, 20));
    armasMagicasHigh.insertarAlFinal(Weapon("Vendaval", {0, 0, 0, 22, 0}, 0.9, 7, 3, true, 3, 0, 0, 10, 20));
    armasMagicasHigh.insertarAlFinal(Weapon("Chispa_HD", {0, 0, 0, 0, 27}, 0.9, 7, 3, false, 3, 0, 0, 10, 20));
    armasMagicasHigh.insertarAlFinal(Weapon("Vendaval_de_Fuego", {0, 22, 0, 22, 0}, 0.9, 10, 4, true, 3, 0, 0, 14, 25));
    armasMagicasHigh.insertarAlFinal(Weapon("Carambano_Chispiante", {0, 0, 27, 0, 27}, 0.9, 10, 5, false, 3, 0, 0, 14, 25));
    armasMagicasHigh.insertarAlFinal(Weapon("Hiper_TetraElementalidad", {0, 11, 14, 11, 14}, 0.9, 15, 2, true, 3, 0, 0, 15, 35));
    armasMagicasHigh.insertarAlFinal(Weapon("ZETTAFLAREEEEEE!!!!", {0, 999, 0, 0, 0}, 0.5, 50, 1, true, 3, 0, 0, 3, 50));
}


void inicializarPersonajes(ListaEnlazada<Player>& personajes) {
    personajes.insertarAlFinal(Player("Guapo_Rubio_Mazado", 120, 30, 10, 3, 0.95));
    personajes.insertarAlFinal(Player("Japones_Vestido_de_Ninja", 100, 25, 20, 5, 0.99));
    personajes.insertarAlFinal(Player("Swiftie", 90, 40, 10, 3, 0.9));
    personajes.insertarAlFinal(Player("Freddy_Mercury", 110, 35, 10, 4, 0.95));
    personajes.insertarAlFinal(Player("Rata_Mutante", 70, 40, 30, 15, 0.8));
    personajes.insertarAlFinal(Player("Cientifico_del_Tzar", 85, 25, 35, 12, 0.95));
    personajes.insertarAlFinal(Player("Espia_de_la_CIA", 105, 27, 32, 12, 0.95));
    personajes.insertarAlFinal(Player("Persona_con_Mochila", 115, 35, 10, 4, 0.9));
}