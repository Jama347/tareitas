#include <iostream>
#include <cstdlib>
#include <ctime>
#include "estructuras_datos.hpp"
#include "construir.cpp"
using namespace std;

// Función auxiliar para obtener un elemento aleatorio usando eliminación y reinserción
template<typename T>
T obtenerElementoAleatorio(ListaEnlazada<T>& lista, int indice) {
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
int contarElementos(ListaEnlazada<T>& lista) {
    return lista.obtenerLongitud();
}

void mostrarOpcionesArmas(
    Player& jugador,
    ListaEnlazada<Weapon>& armasMelee,
    ListaEnlazada<Weapon>& armasMeleeElementales, 
    ListaEnlazada<Weapon>& armasRanger,
    ListaEnlazada<Weapon>& armasRangerElementales,
    ListaEnlazada<Weapon>& armasMagicasLow,
    ListaEnlazada<Weapon>& armasMagicasHigh) {
    
    // Inicializar semilla para números aleatorios (solo una vez)
    static bool semillaInicializada = false;
    if (!semillaInicializada) {
        srand(static_cast<unsigned>(time(0)));
        semillaInicializada = true;
    }
    
    // Contar total de armas en todas las listas
    int totalMelee = contarElementos(armasMelee);
    int totalMeleeElemental = contarElementos(armasMeleeElementales);
    int totalRanger = contarElementos(armasRanger);
    int totalRangerElemental = contarElementos(armasRangerElementales);
    int totalMagicLow = contarElementos(armasMagicasLow);
    int totalMagicHigh = contarElementos(armasMagicasHigh);
    
    int totalArmas = totalMelee + totalMeleeElemental + totalRanger + 
                     totalRangerElemental + totalMagicLow + totalMagicHigh;
    
    if (totalArmas == 0) {
        cout << "No hay armas disponibles." << endl;
        return;
    }
    
    cout << "\n=== OPCIONES DE ARMAS DISPONIBLES ===" << endl;
    
    // Generar 3 armas aleatorias
    Weapon opciones[3];
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
    if (/* jugador.invLenght >= 5 */ true) {  // hay que hacer el metodo que retorne la cantidad de armas en el inventario
        cout << "\nTu inventario de armas está lleno." << endl;
        cout << "¿Quieres reemplazar un arma? (s/n): ";
        char respuesta;
        cin >> respuesta;
        
        if (respuesta == 's' || respuesta == 'S') {
            cout << "\nArmas actuales en tu inventario:" << endl;
            
            // Mostrar armas actuales (hay que poner aqui un getName)
            for (int i = 0; i < 4; i++) {
                cout << (i + 1) << ". [Arma en posición " << i /*Winventory[i].getName */<< "]" << endl;
            }
            
            cout << "¿Qué arma quieres reemplazar? (1-5): ";
            int indiceReemplazo;
            cin >> indiceReemplazo;
            
            if (indiceReemplazo >= 1 && indiceReemplazo <= 4) {
                // Remover arma actual y agregar nueva
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
        // Inventario no está lleno, agregar directamente
        /*asignar_arma(jugador, opciones[seleccion - 1]);*/
        cout << "¡Arma agregada al inventario!" << endl;
    }
}