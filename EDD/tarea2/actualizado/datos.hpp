#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "todo1.hpp"

using namespace std;

#ifndef DATOS_HPP
#define DATOS_HPP


void inicializarArmasMelee(list<Weapon>& armasMelee) {
    armasMelee.append(Weapon("kunai", {5, 0, 0, 0, 0}, 1, 5, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("kunaikunai", {10, 0, 0, 0, 0}, 1, 10, 2, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Machete", {8, 0, 0, 0, 0}, 1, 7, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Machete_al_Machote", {13, 0, 0, 0, 0}, 1, 9, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Hacha_Oxidada", {9, 0, 0, 0, 0}, 0.9, 7, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Hacha", {15, 0, 0, 0, 0}, 0.9, 10, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Hacha_de_Guerra", {20, 0, 0, 0, 0}, 0.85, 15, 2, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Microfono", {6, 0, 0, 0, 0}, 1, 4, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Chatarra", {2, 0, 0, 0, 0}, 0.7, 7, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("TUS_MANOS!!!", {3, 0, 0, 0, 0}, 1, 2, 5, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Puños_Americano", {5, 0, 0, 0, 0}, 1, 2, 5, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Latigo_de_Cuero", {10, 0, 0, 0, 0}, 0.9, 12, 1, true, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Cadena_Larga", {15, 0, 0, 0, 0}, 0.9, 17, 1, true, 1, 0, 0, 0, 0));
}

void inicializarArmasMeleeElementales(list<Weapon>& armasMeleeElementales) {
    armasMeleeElementales.append(Weapon("Kunais_Cargados", {10, 0, 0, 0, 5}, 1, 10, 2, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.append(Weapon("Machete_en_Llamas", {13, 7, 0, 0, 0}, 1, 9, 1, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.append(Weapon("Hacha_Tundrica", {20, 0, 10, 0, 0}, 0.85, 15, 2, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.append(Weapon("Chatarra_Radioactiva", {2, 2, 2, 2, 2}, 0.85, 7, 1, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.append(Weapon("Puños_ligeros", {5, 0, 0, 3, 0}, 1, 10, 5, false, 1, 0, 0, 0, 0));
}

void inicializarArmasRanger(list<Weapon>& armasRanger) {
    armasRanger.append(Weapon("Arco_Improvisado", {9, 0, 0, 0, 0}, 0.7, 4, 5, false, 2, 5, 15, 0, 0));
    armasRanger.append(Weapon("Arco", {12, 0, 0, 0, 0}, 0.9, 10, 3, false, 2, 6, 15, 0, 0));
    armasRanger.append(Weapon("Ballesta", {16, 0, 0, 0, 0}, 0.8, 10, 2, false, 2, 3, 17, 0, 0));
    armasRanger.append(Weapon("Pistola", {1, 0, 0, 0, 0}, 0.95, 3, 10, false, 2, 30, 17, 0, 0));
    armasRanger.append(Weapon("Escopeta", {18, 0, 0, 0, 0}, 0.8, 14, 2, true, 2, 4, 19, 0, 0));
    armasRanger.append(Weapon("ESCOPETA!!!", {25, 0, 0, 0, 0}, 0.85, 18, 2, true, 2, 4, 25, 0, 0));
    armasRanger.append(Weapon("smg", {0.5, 0, 0, 0, 0}, 0.95, 7, 30, false, 2, 60, 17, 0, 0));
    armasRanger.append(Weapon("RATATATATTATATTATATATTA!!!!!", {1, 0, 0, 0, 0}, 0.95, 7, 30, false, 2, 60, 17, 0, 0));
    armasRanger.append(Weapon("BOOM!!!", {30, 0, 0, 0, 0}, 0.3, 30, 1, true, 2, 5, 30, 0, 0));
    armasRanger.append(Weapon("KABOOM!!!", {50, 0, 0, 0, 0}, 0.3, 35, 1, true, 2, 5, 30, 0, 0));
}

void inicializarArmasRangerElementales(list<Weapon>& armasRangerElementales) {
    armasRangerElementales.append(Weapon("Ballesta_Encantada", {16, 0, 0, 4, 4}, 0.8, 10, 2, false, 2, 5, 15, 0, 0));
    armasRangerElementales.append(Weapon("Lanzallamas", {2, 20, 0, 0, 0}, 0.95, 20, 5, true, 2, 30, 7, 0, 0));
}

void inicializarArmasMagicasLowCost(list<Weapon>& armasMagicasLow) {
    armasMagicasLow.append(Weapon("Ascuas", {0, 13, 0, 0, 0}, 0.95, 5, 3, true, 3, 0, 0, 3, 5));
    armasMagicasLow.append(Weapon("Bola_Hielo", {0, 0, 15, 0, 0}, 0.95, 5, 3, false, 3, 0, 0, 3, 5));
    armasMagicasLow.append(Weapon("Aerochorro", {0, 0, 0, 13, 0}, 0.95, 5, 3, true, 3, 0, 0, 3, 5));
    armasMagicasLow.append(Weapon("Chispa", {0, 0, 0, 0, 15}, 0.95, 5, 3, false, 3, 0, 0, 3, 5));
    armasMagicasLow.append(Weapon("Ascuas_Aerochorreantes", {0, 13, 0, 13, 0}, 0.95, 10, 6, true, 3, 0, 0, 3, 10));
    armasMagicasLow.append(Weapon("Bola_de_ChispaHielo", {0, 0, 15, 0, 15}, 0.95, 10, 6, false, 3, 0, 0, 3, 10));
    armasMagicasLow.append(Weapon("TetraElementalidad", {0, 7, 7, 7, 7}, 0.95, 10, 5, true, 3, 0, 0, 3, 10));
}

void inicializarArmasMagicasHighDamage(list<Weapon>& armasMagicasHigh) {
    armasMagicasHigh.append(Weapon("Bola_de_Fuego", {0, 22, 0, 0, 0}, 0.9, 7, 3, true, 3, 0, 0, 10, 20));
    armasMagicasHigh.append(Weapon("Carambano", {0, 0, 27, 0, 0}, 0.9, 7, 3, false, 3, 0, 0, 10, 20));
    armasMagicasHigh.append(Weapon("Vendaval", {0, 0, 0, 22, 0}, 0.9, 7, 3, true, 3, 0, 0, 10, 20));
    armasMagicasHigh.append(Weapon("Chispa_HD", {0, 0, 0, 0, 27}, 0.9, 7, 3, false, 3, 0, 0, 10, 20));
    armasMagicasHigh.append(Weapon("Vendaval_de_Fuego", {0, 22, 0, 22, 0}, 0.9, 10, 4, true, 3, 0, 0, 14, 25));
    armasMagicasHigh.append(Weapon("Carambano_Chispiante", {0, 0, 27, 0, 27}, 0.9, 10, 5, false, 3, 0, 0, 14, 25));
    armasMagicasHigh.append(Weapon("Hiper_TetraElementalidad", {0, 11, 14, 11, 14}, 0.9, 15, 2, true, 3, 0, 0, 15, 35));
    armasMagicasHigh.append(Weapon("ZETTAFLAREEEEEE!!!!", {0, 999, 0, 0, 0}, 0.5, 50, 1, true, 3, 0, 0, 3, 50));
}


#endif /* DATOS_HPP */