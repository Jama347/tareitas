#include <iostream>
#include <cstdlib>
#include <ctime>
#include "estructuras_datos 1.hpp"
#include "datos.hpp"
#include "Combate 1.hpp"

using namespace std;

// Función auxiliar para obtener un elemento aleatorio usando eliminación y reinserción
template<typename T>
T obtenerElementoAleatorio(list<T>& lista, int indice) {
    int longitud = lista.obtenerLongitud();
    if (longitud == 0) {
        return T(); // Retorna elemento por defecto si la lista está vacía
    }
    // Creamos un array temporal para almacenar todos los elementos
    T* elementos = new T[longitud];
    int contador = 0;
    
    // Extraer todos los elementos de la lista original
    while (!lista.estaVacia()) {
        T elemento;
        if (contador == 0) {
            elementos[contador] = T(); // Elemento por defecto
        }
        
        contador++;
        if (contador >= longitud) break;
    }
    T elementoSeleccionado = elementos[indice];
    
    // Reinsertar todos los elementos en la lista original
    for (int i = 0; i < longitud; i++) {
        lista.insertarAlFinal(elementos[i]);
    }
    
    delete[] elementos;
    return elementoSeleccionado;
}

// Función para contar elementos en una ListaEnlazada
template<typename T>
int contarElementos(list<Weapon>& lista) {
    return lista.length();
}

void createWeaponList(list<Weapon>& weaponList){
    inicializarArmasMelee(weaponList);
    inicializarArmasMeleeElementales(weaponList);
    inicializarArmasRanger(weaponList);
    inicializarArmasRangerElementales(weaponList);
    inicializarArmasMagicasLowCost(weaponList);
    inicializarArmasMagicasHighDamage(weaponList);
}
void createWeaponPool(list<Weapon>& weaponPool, list<Weapon>& weaponList){
    weaponPool.copy(weaponList);
    weaponPool.randomize();
}

void mostrarOpcionesArmas(Player& jugador, list<Weapon>& weaponPool){
    // list<Weapon>& armasMelee,
    // list<Weapon>& armasMeleeElementales, 
    // list<Weapon>& armasRanger,
    // list<Weapon>& armasRangerElementales,
    // list<Weapon>& armasMagicasLow,
    // list<Weapon>& armasMagicasHigh) {
    
    // Inicializar semilla para números aleatorios (solo una vez)
    static bool semillaInicializada = false;
    if (!semillaInicializada) {
        srand(static_cast<unsigned>(time(0)));
        semillaInicializada = true;
    }
    
    // // Contar total de armas en todas las listas
    // int totalMelee = contarElementos(armasMelee);
    // int totalMeleeElemental = contarElementos(armasMeleeElementales);
    // int totalRanger = contarElementos(armasRanger);
    // int totalRangerElemental = contarElementos(armasRangerElementales);
    // int totalMagicLow = contarElementos(armasMagicasLow);
    // int totalMagicHigh = contarElementos(armasMagicasHigh);
    
    // int totalArmas = totalMelee + totalMeleeElemental + totalRanger + 
    //                  totalRangerElemental + totalMagicLow + totalMagicHigh;
    
    if (weaponPool.length() == 0) {
        cout << "No hay armas disponibles." << endl;
        return;
    }
    
    cout << "\n=== OPCIONES DE ARMAS DISPONIBLES ===" << endl;
    
    // Generar 3 armas aleatorias
    node<Weapon>* options[3];

    // nose como usar eso de tu semilla ns
    int a = rand() % weaponPool.length();
    int b,c;
    while (b == a){b = rand() % weaponPool.length();}
    while (c == a || c == b){c = rand() % weaponPool.length();}
    
    weaponPool.moveToPos(a);
    options[0] = weaponPool.getNodeAt(a);
    weaponPool.moveToPos(b);
    options[1] = weaponPool.getNodeAt(b);
    weaponPool.moveToPos(c);
    options[2] = weaponPool.getNodeAt(c);

    //Weapon opciones[3];
    string nombresOpciones[3];
    
    // Mostrar opciones
    for (int i = 0; i < 3; i++) {
        cout << (i + 1) << ". " << nombresOpciones[i] << endl;
    }
    
    cout << "\nSelecciona un arma (1-3): ";
    int seleccion;
    cin >> seleccion;
    
    if (seleccion < 1 || seleccion > 3) {
        cout << "Selección inválida." << endl;
        return;
    }
    
    // Verificar si el inventario está lleno (asumiendo que invLenght indica armas actuales)
    if (jugador.AmountWeapons() >= 4 ) {  // hay que hacer el metodo que retorne la cantidad de armas en el inventario
        cout << "\nTu inventario de armas está lleno." << endl;
        cout << "¿Quieres reemplazar un arma? (s/n): ";
        char respuesta;
        cin >> respuesta;
        
        if (respuesta == 's' || respuesta == 'S') {
            cout << "\nArmas actuales en tu inventario:" << endl;
            
            // Mostrar armas actuales (hay que poner aqui un getName)
            for (int i = 0; i < 4; i++) {
                cout << (i + 1) << ". [Arma en posición " << i << ": " << jugador.invWeapon(i)->data.getName() << "]" << endl;
            }
            
            cout << "¿Qué arma quieres reemplazar? (1-4): ";
            int indiceReemplazo;
            cin >> indiceReemplazo;
            
            if (indiceReemplazo >= 1 && indiceReemplazo <= 4) {
                // Remover arma actual y agregar nueva
                int go;
                if (seleccion == 1) go = a;
                if (seleccion == 2) go = b;
                if (seleccion == 3) go = c;
                weaponPool.moveToPos(go);
                jugador.getNewWeapon(indiceReemplazo, options[seleccion-1]);
                weaponPool.erase();// el erase tiene que ser despues o si no la cantidad de espacios que tiene en el inventario se bugearia
                cout << "Arma en posición " << indiceReemplazo << " reemplazada." << endl;
                /*asignar_arma(jugador, opciones[seleccion - 1]);*/
                cout << "¡Nueva arma agregada exitosamente!" << endl;
            } else {
                cout << "Índice inválido." << endl;
            }
        } else {
            cout << "Operación cancelada." << endl;
        }
    } else {
        jugador.getNewWeapon(jugador.AmountWeapons(), options[seleccion-1]);
        cout << "¡Arma agregada al inventario!" << endl;
    }
}