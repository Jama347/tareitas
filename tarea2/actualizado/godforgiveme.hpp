#ifndef SALAS_HPP
#define SALAS_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "estructuras_datos 1.hpp"
#include "Combate 1.hpp"
#include "datos.hpp"
#include "items.hpp"
#include "weaponSelector 1.hpp"

using namespace std;

// Enumeración para tipos de sala
enum TipoSala {
    INICIO = 0,
    COMBATE = 1,
    ITEMS = 2,
    ARMAS = 3,
    LORE = 4,
    FINAL = 5
};

// Estructura del nodo de sala con toda la información necesaria
struct SalaNode {
    // Información básica
    string nombre;
    string mensajeEntrada;
    TipoSala tipo;
    
    // Para navegación
    Lista<SalaNode*> siguientesSalas;
    
    // Constructor
    SalaNode(string n, string msg, TipoSala t) : nombre(n), mensajeEntrada(msg), tipo(t) {}
    
    // Método para agregar sala siguiente
    void agregarSalaSiguiente(SalaNode* sala) {
        siguientesSalas.append(sala);
    }
    
    // Método para ejecutar las acciones de la sala
    void ejecutarAcciones(Player& jugador, Combat& combate, list<Weapon>& weaponPool, SalaNode*& salaActual, bool& juegoTerminado);
    
    // Métodos auxiliares
    void mostrarOpciones();
    SalaNode* elegirSiguienteSala();
};



// Implementación del método ejecutarAcciones
void SalaNode::ejecutarAcciones(Player& jugador, Combat& combate, list<Weapon>& weaponPool, SalaNode*& salaActual, bool& juegoTerminado) {
    cout << "\n================================" << endl;
    cout << "  " << nombre << endl;
    cout << "================================" << endl;
    cout << mensajeEntrada << endl;
    cout << "================================" << endl;
    
    switch(tipo) {
        case INICIO:
            // 1. Mostrar siguientes ubicaciones
            // 2. Llevar a la ubicación elegida
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
            
        case COMBATE:
            // 1. Iniciar combate
            cout << "\n¡Prepárate para el combate!" << endl;
            combate.setEnemyList();
            combate.Combating(jugador);
            
            // 2. Verificar resultado
            if (jugador.getHealth() <= 0) {
                // Derrota - eliminar árbol y volver a inicio
                cout << "\nRegresando a la zona de inicio..." << endl;
                juegoTerminado = true; // Señal para reiniciar
                return;
            }
            
            // 3. Victoria - continuar
            cout << "\n¡Victoria! Puedes continuar explorando." << endl;
            
            // 4. Mostrar siguientes ubicaciones
            // 5. Llevar a la ubicación elegida
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
            
        case ITEMS:
            // 1. Ofrecer items aleatorios
            cout << "\n¡Has encontrado algunos objetos útiles!" << endl;
            selectRandomItems(jugador);
            
            // 2. Mostrar siguientes ubicaciones
            // 3. Llevar a la ubicación elegida
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
            
        case ARMAS:
            // 1. Ofrecer armas aleatorias
            cout << "\n¡Has encontrado armamento!" << endl;
            mostrarOpcionesArmas(jugador, weaponPool);
            
            // 2. Mostrar siguientes ubicaciones
            // 3. Llevar a la ubicación elegida
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
            
        case LORE:
            // Solo mostrar el lore y continuar
            // 1. Mostrar siguientes ubicaciones
            // 2. Llevar a la ubicación elegida
            cout << "\nPresiona Enter para continuar...";
            cin.ignore();
            cin.get();
            
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
            
        case FINAL:
            // Terminar el juego
            cout << "\n¡El juego ha terminado!" << endl;
            juegoTerminado = true;
            break;
    }
}

void SalaNode::mostrarOpciones() {
    if (siguientesSalas.getSize() == 0) return;
    
    cout << "\n--- UBICACIONES DISPONIBLES ---" << endl;
    for (int i = 0; i < siguientesSalas.getSize(); i++) {
        cout << (i + 1) << ". " << siguientesSalas[i]->nombre << endl;
    }
    cout << "-------------------------------" << endl;
}

SalaNode* SalaNode::elegirSiguienteSala() {
    if (siguientesSalas.getSize() == 0) return nullptr;
    
    int opcion;
    do {
        cout << "Elige tu destino (1-" << siguientesSalas.getSize() << "): ";
        cin >> opcion;
        
        if (opcion < 1 || opcion > siguientesSalas.getSize()) {
            cout << "Opción inválida. Intenta de nuevo." << endl;
        }
    } while (opcion < 1 || opcion > siguientesSalas.getSize());
    
    return siguientesSalas[opcion - 1];
}

// Clase para manejar el sistema de salas
class SistemaJuego {
private:
    SalaNode* salaInicio;
    Lista<SalaNode*> todasLasSalas;
    
    // Listas de salas por categoría
    Lista<SalaNode*> salasCombate;
    Lista<SalaNode*> salasItems;
    Lista<SalaNode*> salasArmas;
    Lista<SalaNode*> salasLore;
    Lista<SalaNode*> salasFinales;
    
public:
    SistemaJuego() : salaInicio(nullptr) {
        inicializarSalas();
        configurarConexiones();
    }
    
    ~SistemaJuego() {
        // Limpiar memoria
        for (int i = 0; i < todasLasSalas.getSize(); i++) {
            delete todasLasSalas[i];
        }
    }
    
    void inicializarSalas() {
        // SALA DE INICIO
        salaInicio = new SalaNode(
            "ZONA DE INICIO",
            "El mundo ha visto su fin producto a una devastadora guerra nuclear, pocos viven,\n"
            "muchos menos están suficientemente sanos como para llevar una vida normal.\n"
            "Tú eres de los pocos que pueden deambular por el mundo, sales desde una base militar\n"
            "con el objetivo de conseguir armamento, provisiones y hacer limpieza.\n"
            "Te enfrentarás a enemigos peligrosos así que ve con cuidado.",
            INICIO
        );
        todasLasSalas.append(salaInicio);
        
        // SALAS DE COMBATE
        salasCombate.append(new SalaNode(
            "Campo Abierto",
            "Una presencia maligna te observa pero no sabes de dónde.",
            COMBATE
        ));
        
        salasCombate.append(new SalaNode(
            "Basural Radioactivo",
            "Escuchas algo moverse entre la basura.",
            COMBATE
        ));
        
        salasCombate.append(new SalaNode(
            "Edificio en Ruinas",
            "El aire es pesado, te cuesta respirar.",
            COMBATE
        ));
        
        salasCombate.append(new SalaNode(
            "Bosque Mutante",
            "Sientes como si los árboles te hablaran, o quizás de verdad lo hacen.",
            COMBATE
        ));
        
        // SALAS DE ITEMS
        salasItems.append(new SalaNode(
            "Caja Random",
            "Parece que es solo una caja, la abres para ver qué hay dentro.",
            ITEMS
        ));
        
        salasItems.append(new SalaNode(
            "Cuerpo Humano Tirado",
            "Ya está muerto, ahora sus cosas son tus cosas.",
            ITEMS
        ));
        
        salasItems.append(new SalaNode(
            "Almacén Pequeño",
            "No parece haber nadie, llévate algo.",
            ITEMS
        ));
        
        salasItems.append(new SalaNode(
            "Montón de Basura",
            "Algo útil debe haber, dale revisa.",
            ITEMS
        ));
        
        // SALAS DE ARMAS
        salasArmas.append(new SalaNode(
            "Asentamiento Militar Abandonado",
            "Estoy seguro que es ilegal entrar aquí, así que llévate algo rápido.",
            ARMAS
        ));
        
        salasArmas.append(new SalaNode(
            "Un Campo de Batalla",
            "Pucha se murieron, bueno, a lootear se ha dicho.",
            ARMAS
        ));
        
        salasArmas.append(new SalaNode(
            "Un Militar Durmiendo",
            "Shhh ni se te ocurra despertarlo.",
            ARMAS
        ));
        
        salasArmas.append(new SalaNode(
            "Caja de Armas",
            "Apuesto a que no sabes qué hay dentro.",
            ARMAS
        ));
        
        salasArmas.append(new SalaNode(
            "Caja Grande de Armas",
            "¿Crees que haya muchas armas por el hecho de ser grande?",
            ARMAS
        ));
        
        salasArmas.append(new SalaNode(
            "Una Única Arma en el Piso",
            "¡¡Sorpresa!! En realidad son 3.",
            ARMAS
        ));
        
        // SALAS DE LORE
        salasLore.append(new SalaNode(
            "Libro Rojo",
            "Encuentras un libro en el piso lo abres para ver que tiene escrito.\n"
            "Autor: Jama\n"
            "Ha empezado a hacer mucho frío por algún motivo, eso del invierno nuclear no era una\n"
            "exageración, rusos hijos de puta como se les ocurre empezar a lanzar bombas.",
            LORE
        ));
        
        salasLore.append(new SalaNode(
            "Libro Azul",
            "Encuentras un libro, tiene carátula roja, lo abres.\n"
            "Autor: Jama\n"
            "Ayer encontré un perro muerto, y me puso muy triste, de la tristeza\n"
            "empecé a pegar tiros al aire, pegando tiros al aire me acordé de los\n"
            "tiroteos escolares e insulté a los gringos por empezar a tirar bombas.\n"
            "Me sentí mejor después de eso.",
            LORE
        ));
        
        salasLore.append(new SalaNode(
            "Libro Verde",
            "¡¡Ostia un libro!!, ábrelo ábrelo!!.\n"
            "Autor: Jama\n"
            "Escuché que hay científicos que han logrado usar desechos radioactivos y energía\n"
            "solar para desarrollar una especie de magia, aún no se sabe mucho si.",
            LORE
        ));
        
        salasLore.append(new SalaNode(
            "Libro Amarillo",
            "Hay un libro en el piso, ¿quién lo dejó ahí?\n"
            "Autor: Jama\n"
            "Se me ocurrió una fantabulosa idea, voy a escribir libros con carátulas de distintos\n"
            "colores y los voy a esparcir por ahí para que gente los encuentre y los lea, la wea\n"
            "más cómica existente, sería una pena que alguien solo leyera un párrafo, ¿verdad?",
            LORE
        ));
        
        salasLore.append(new SalaNode(
            "Libro Bizarro",
            "En la portada hay un hombre musculoso con un estilo muy particular.\n"
            "Autor: Hirohiko Araki\n"
            "ORAOROAORAORAOROAOROAROAOROAROAORAORAOROARAOROAOROAROAOROAROAOROAROA!!!!!!!ORAAA!!!",
            LORE
        ));
        
        // SALAS FINALES
        salasFinales.append(new SalaNode(
            "Edificio Militar Azul",
            "Entras para ver si hay alguien, sí que lo había, agentes de la CIA\n"
            "te ven armado y te disparan rápidamente.\n"
            "Mueres...",
            FINAL
        ));
        
        salasFinales.append(new SalaNode(
            "Edificio Militar Rojo",
            "Knock knock, ¿quién es?\n"
            "¡¡¡COMUNISTAS!!! Te roban todo lo que tienes para 'dárselo al estado'\n"
            "te tiran a la intemperie sin nada...",
            FINAL
        ));
        
        salasFinales.append(new SalaNode(
            "Campamento Civil",
            "Llegas a un campamento, te recibe una señora muy amigable y te da\n"
            "sopita.\n"
            "Te quedas con ellos...",
            FINAL
        ));
        
        // Agregar todas las salas a la lista principal
        for (int i = 0; i < salasCombate.getSize(); i++) {
            todasLasSalas.append(salasCombate[i]);
        }
        for (int i = 0; i < salasItems.getSize(); i++) {
            todasLasSalas.append(salasItems[i]);
        }
        for (int i = 0; i < salasArmas.getSize(); i++) {
            todasLasSalas.append(salasArmas[i]);
        }
        for (int i = 0; i < salasLore.getSize(); i++) {
            todasLasSalas.append(salasLore[i]);
        }
        for (int i = 0; i < salasFinales.getSize(); i++) {
            todasLasSalas.append(salasFinales[i]);
        }
    }
    
    void configurarConexiones() {
        // Conectar sala de inicio con salas aleatorias
        asignarSalasAleatorias(salaInicio);
        
        // Para cada sala no final, asignar conexiones aleatorias
        for (int i = 0; i < todasLasSalas.getSize(); i++) {
            if (todasLasSalas[i] != salaInicio && todasLasSalas[i]->tipo != FINAL) {
                asignarSalasAleatorias(todasLasSalas[i]);
            }
        }
    }
    
    void asignarSalasAleatorias(SalaNode* sala) {
        static bool seedInitialized = false;
        if (!seedInitialized) {
            srand(static_cast<unsigned>(time(0)));
            seedInitialized = true;
        }
        
        // Decidir número de conexiones (2 o 3)
        int numConexiones = 2 + (rand() % 2);
        
        // Crear pool de salas candidatas (excluyendo la sala actual)
        Lista<SalaNode*> candidatas;
        
        // Agregar salas de diferentes tipos aleatoriamente
        agregarSalasAleatorias(candidatas, salasCombate, sala);
        agregarSalasAleatorias(candidatas, salasItems, sala);
        agregarSalasAleatorias(candidatas, salasArmas, sala);
        agregarSalasAleatorias(candidatas, salasLore, sala);
        
        // Ocasionalmente agregar salas finales (baja probabilidad)
        if (rand() % 100 < 15) { // 15% de probabilidad
            agregarSalasAleatorias(candidatas, salasFinales, sala);
        }
        
        // Seleccionar salas aleatorias del pool
        for (int i = 0; i < numConexiones && candidatas.getSize() > 0; i++) {
            int indiceAleatorio = rand() % candidatas.getSize();
            sala->agregarSalaSiguiente(candidatas[indiceAleatorio]);
            
            // Remover la sala seleccionada para evitar duplicados
            candidatas.removeAt(indiceAleatorio);
        }
    }
    
    void agregarSalasAleatorias(Lista<SalaNode*>& candidatas, Lista<SalaNode*>& fuente, SalaNode* salaActual) {
        for (int i = 0; i < fuente.getSize(); i++) {
            if (fuente[i] != salaActual) {
                candidatas.append(fuente[i]);
            }
        }
    }
    
    void iniciarJuego(Player& jugador, Combat& combate, list<Weapon>& weaponPool) {
        SalaNode* salaActual = salaInicio;
        bool juegoTerminado = false;
        
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║          LA GUERRA CALIENTE          ║" << endl;
        cout << "║        Un juego post-apocalíptico    ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        
        while (!juegoTerminado && salaActual != nullptr) {
            salaActual->ejecutarAcciones(jugador, combate, weaponPool, salaActual, juegoTerminado);
            
            // Si el juego terminó por derrota, reiniciar desde el inicio
            if (juegoTerminado && jugador.getHealth() <= 0) {
                cout << "\n¿Quieres intentar de nuevo? (s/n): ";
                char respuesta;
                cin >> respuesta;
                
                if (respuesta == 's' || respuesta == 'S') {
                    // Reiniciar jugador
                    jugador = Player("Explorador", 100, 50, 30, 5, 0.8);
                    salaActual = salaInicio;
                    juegoTerminado = false;
                    
                    // Reconfigurar conexiones para nueva experiencia
                    limpiarConexiones();
                    configurarConexiones();
                }
            }
        }
        
        cout << "\n¡Gracias por jugar La Guerra Caliente!" << endl;
    }
    
    void limpiarConexiones() {
        for (int i = 0; i < todasLasSalas.getSize(); i++) {
            todasLasSalas[i]->siguientesSalas.clear();
        }
    }
};

#endif /* SALAS_HPP */