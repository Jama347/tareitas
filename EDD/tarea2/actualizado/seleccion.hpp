#ifndef CHARACTER SELECTION HPP
#define CHARACTER SELECTION HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Combate 1.hpp"
#include "godforgiveme.hpp"

using namespace std;

class CharacterSelector {
private:
    list<Player> personajesDisponibles;
    
public:
    CharacterSelector() {
        inicializarPersonajes();
    }
    
    void inicializarPersonajes() {
        personajesDisponibles.append(Player("Guapo Rubio Mazado", 120, 30, 10, 3, 0.95));
        personajesDisponibles.append(Player("Japones Vestido de Ninja", 100, 25, 20, 5, 0.99));
        personajesDisponibles.append(Player("Swiftie", 90, 40, 10, 3, 0.9));
        personajesDisponibles.append(Player("Freddy Mercury", 110, 35, 10, 4, 0.95));
        personajesDisponibles.append(Player("Rata Mutante", 70, 40, 30, 15, 0.8));
        personajesDisponibles.append(Player("Cientifico del Tzar", 85, 25, 35, 12, 0.95));
        personajesDisponibles.append(Player("Espia de la CIA", 105, 27, 32, 12, 0.95));
        personajesDisponibles.append(Player("Persona con Mochila", 115, 35, 10, 4, 0.9));
    }
    
    void mostrarPersonajes() {
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    SELECCIÓN DE PERSONAJE                    ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        cout << endl;
        
        personajesDisponibles.moveToStart();
        int contador = 1;
        
        while (personajesDisponibles.currPos() < personajesDisponibles.length()) {
            Player personajeActual = personajesDisponibles.getValue();
            
            cout << "┌─ [" << contador << "] " << formatearNombre(personajeActual) << " ─┐" << endl;
            cout << "│ Salud:     " << personajeActual.maxHealth() << " HP" << endl;
            cout << "│ Energía:   " << personajeActual.maxEnergy() << " EP" << endl;
            cout << "│ Maná:      " << personajeActual.maxMana() << " MP" << endl;
            cout << "│ Precisión: " << (personajeActual.getAccuracy() * 100) << "%" << endl;
            cout << "│ Descripción: " << obtenerDescripcion(personajeActual) << endl;
            cout << "└" << string(60, '─') << "┘" << endl;
            cout << endl;
            
            personajesDisponibles.next();
            contador++;
        }
    }
    
    string obtenerDescripcion(const Player& personaje) {
        string nombre = personaje.getName();
        
        if (nombre == "Guapo Rubio Mazado") {
            return "Tanque resistente con alta salud y precisión";
        } else if (nombre == "Japones Vestido de Ninja") {
            return "Asesino ágil con máxima precisión y regeneración de maná";
        } else if (nombre == "Swiftie") {
            return "Berserker con alta energía pero frágil";
        } else if (nombre == "Freddy Mercury") {
            return "Equilibrado en todos los aspectos";
        } else if (nombre == "Rata Mutante") {
            return "Mago especialista con mucho maná pero poca salud";
        } else if (nombre == "Cientifico del Tzar") {
            return "Soporte mágico con excelente regeneración de maná";
        } else if (nombre == "Espia de la CIA") {
            return "Especialista táctico equilibrado";
        } else if (nombre == "Persona con Mochila") {
            return "Superviviente versátil con buena resistencia";
        }
        
        return "Superviviente del apocalipsis";
    }
    
    Player seleccionarPersonaje() {
        mostrarPersonajes();
        
        int opcion;
        bool seleccionValida = false;
        
        while (!seleccionValida) {
            cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
            cout << "Elige tu personaje (1-" << personajesDisponibles.length() << "): ";
            cin >> opcion;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "❌ Entrada inválida. Por favor ingresa un número." << endl;
                continue;
            }
            
            if (opcion >= 1 && opcion <= personajesDisponibles.length()) {
                seleccionValida = true;
            } else {
                cout << "❌ Opción inválida. Elige entre 1 y " << personajesDisponibles.length() << "." << endl;
            }
        }
        
        // Obtener el personaje seleccionado
        personajesDisponibles.moveToPos(opcion - 1);
        Player personajeElegido = personajesDisponibles.getValue();
        
        // Mostrar confirmación
        cout << "\n✅ Has seleccionado: " << formatearNombre(personajeElegido) << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        
        mostrarEstadisticasFinales(personajeElegido);
        
        cout << "\nPresiona Enter para comenzar tu aventura...";
        cin.ignore();
        cin.get();
        
        return personajeElegido;
    }
    
    void mostrarEstadisticasFinales(const Player& personaje) {
        cout << "\n┌─ ESTADÍSTICAS DE " << formatearNombre(personaje) << " ─┐" << endl;
        cout << "│ ⚡ Salud:     " << personaje.maxHealth() << " HP" << endl;
        cout << "│ 🔋 Energía:   " << personaje.maxEnergy() << " EP" << endl;
        cout << "│ 🧿 Maná:      " << personaje.maxMana() << " MP" << endl;
        cout << "│ 🎯 Precisión: " << (personaje.getAccuracy() * 100) << "%" << endl;
        cout << "└" << string(40, '─') << "┘" << endl;
    }
    
    // Método para obtener un personaje aleatorio
    Player seleccionarPersonajeAleatorio() {
        static bool seedInitialized = false;
        if (!seedInitialized) {
            srand(static cast<unsigned>(time(0)));
            seedInitialized = true;
        }
        
        int indiceAleatorio = rand() % personajesDisponibles.length();
        personajesDisponibles.moveToPos(indiceAleatorio);
        Player personajeAleatorio = personajesDisponibles.getValue();
        
        cout << "\n🎲 Personaje aleatorio seleccionado: " << formatearNombre(personajeAleatorio) << endl;
        mostrarEstadisticasFinales(personajeAleatorio);
        
        return personajeAleatorio;
    }
    
    // Método para mostrar modo de selección
    Player iniciarSeleccion() {
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    LA GUERRA CALIENTE                        ║" << endl;
        cout << "║                 Sistema Post-Apocalíptico                    ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        cout << endl;
        cout << "🌍 El mundo ha caído en el caos nuclear..." << endl;
        cout << "💀 Solo los más fuertes sobreviven..." << endl;
        cout << "⚔️  Es hora de elegir tu destino..." << endl;
        cout << endl;
        
        int modoSeleccion;
        bool modoValido = false;
        
        while (!modoValido) {
            cout << "┌─ MODO DE SELECCIÓN ─┐" << endl;
            cout << "│ [1] Elegir personaje │" << endl;
            cout << "│ [2] Personaje random │" << endl;
            cout << "└─────────────────────┘" << endl;
            cout << "Elige modo (1-2): ";
            cin >> modoSeleccion;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "❌ Entrada inválida." << endl;
                continue;
            }
            
            switch (modoSeleccion) {
                case 1:
                    modoValido = true;
                    return seleccionarPersonaje();
                case 2:
                    modoValido = true;
                    return seleccionarPersonajeAleatorio();
                default:
                    cout << "❌ Opción inválida. Elige 1 o 2." << endl;
            }
        }
        
        // Esto nunca debería ejecutarse, pero por seguridad
        return seleccionarPersonaje();
    }
};

// Función principal integrada para usar en main
Player iniciarSeleccionPersonaje() {
    CharacterSelector selector;
    return selector.iniciarSeleccion();
}

// Función para integrar con el sistema de juego existente
void iniciarJuegoCompleto() {
    // 1. Seleccionar personaje
    CharacterSelector selector;
    Player jugadorSeleccionado = selector.iniciarSeleccion();
    
    // 2. Inicializar sistemas de juego
    Combat sistemaComabate;
    list<Weapon> weaponPool; // Asumiendo que tienes un sistema de armas
    
    // 3. Inicializar sistema de salas
    SistemaJuego sistemaJuego;
    
    // 4. Comenzar la aventura
    sistemaJuego.iniciarJuego(jugadorSeleccionado, sistemaComabate, weaponPool);
}

#endif /* CHARACTER SELECTION HPP */