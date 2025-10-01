/**
 * estructuras_datos.hpp
 * Implementación de varias estructuras de datos en C++:
 * - Lista enlazada simple
 * - Lista basada en arreglo
 * - Pila (Stack)
 * - Cola (Queue)
 * - Árbol Binario
 * - Árbol Ternario
 */

#ifndef ESTRUCTURAS_DATOS_HPP
#define ESTRUCTURAS_DATOS_HPP

#include <iostream>
#include <memory>

/* ===== LISTA ENLAZADA SIMPLE ===== */

template <typename Tlista>
class ListaEnlazada {
private:
    struct Nodo {
        Tlista dato;
        Nodo* siguiente;
        
        Nodo(const Tlista& valor) : dato(valor), siguiente(nullptr) {}
    };
    
    Nodo* cabeza;
    int longitud;
    
public:
    // Constructor
    ListaEnlazada() : cabeza(nullptr), longitud(0) {}
    
    // Destructor
    ~ListaEnlazada() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
    
    // Insertar al principio
    void insertarAlPrincipio(const Tlista& dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
        longitud++;
    }
    
    // Insertar al final
    void insertarAlFinal(const Tlista& dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoNodo;
        }
        
        longitud++;
    }
    
    // Eliminar elemento
    bool eliminarElemento(const Tlista& dato) {
        if (cabeza == nullptr) return false;
        
        if (cabeza->dato == dato) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            longitud--;
            return true;
        }
        
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->dato != dato) {
            actual = actual->siguiente;
        }
        
        if (actual->siguiente == nullptr) return false;
        
        Nodo* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        longitud--;
        
        return true;
    }
    
    // Buscar elemento
    bool buscarElemento(const Tlista& dato) const {
        Nodo* actual = cabeza;
        
        while (actual != nullptr) {
            if (actual->dato == dato) return true;
            actual = actual->siguiente;
        }
        
        return false;
    }
    
    // Obtener longitud
    int obtenerLongitud() const {
        return longitud;
    }
    
    // Verificar si está vacía
    bool estaVacia() const {
        return cabeza == nullptr;
    }
};

/* ===== LISTA ARREGLO ===== */

// Estructura simple de lista dinámica para reemplazar vector
template<typename Tlista>
class Lista {
private:
    Tlista* info;
    int capacidad;
    int tamano;
    
    void resize() {
        capacidad *= 2;
        Tlista* newinfo = new Tlista[capacidad];
        for (int i = 0; i < tamano; ++i) {
            newinfo[i] = info[i];
        }
        delete[] info;
        info = newinfo;
    }
    
public:
    Lista() : info(new Tlista[2]), capacidad(2), tamano(0) {}
    
    ~Lista() {
        delete[] info;
    }
    
    void append(const Tlista& item) {
        if (tamano >= capacidad) {
            resize();
        }
        info[tamano++] = item;
    }

    Tlista& operator[](int index) {
        return info[index];
    }
    
    const Tlista& operator[](int index) const {
        return info[index];
    }
    
    int getSize() const {
        return tamano;
    }
    
    bool empty() const {
        return tamano == 0;
    }
    
    void removeAt(int index) {
        if (index < 0 || index >= tamano) return;
        for (int i = index; i < tamano - 1; ++i) {
            info[i] = info[i + 1];
        }
        tamano--;
    }
    
    int findIndex(const Tlista& item) const {
        for (int i = 0; i < tamano; ++i) {
            if (info[i] == item) return i;
        }
        return -1;
    }
};

/* ===== PILA (STACK) ===== */

template <typename Tpila>
class Pila {
private:
    struct Nodo {
        Tpila dato;
        Nodo* siguiente;
        
        Nodo(const Tpila& valor) : dato(valor), siguiente(nullptr) {}
    };
    
    Nodo* tope;
    int tamaño;
    
public:
    // Constructor
    Pila() : tope(nullptr), tamaño(0) {}
    
    // Destructor
    ~Pila() {
        Nodo* actual = tope;
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
    
    // Verificar si está vacía
    bool estaVacia() const {
        return tope == nullptr;
    }
    
    // Insertar elemento (push)
    void push(const Tpila& dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        nuevoNodo->siguiente = tope;
        tope = nuevoNodo;
        tamaño++;
    }
    
    // Eliminar elemento (pop)
    bool pop(Tpila& dato) {
        if (estaVacia()) return false;
        
        dato = tope->dato;
        Nodo* temp = tope;
        tope = tope->siguiente;
        delete temp;
        tamaño--;
        
        return true;
    }
    
    // Ver elemento superior (peek)
    bool peek(Tpila& dato) const {
        if (estaVacia()) return false;
        
        dato = tope->dato;
        return true;
    }
    
    // Obtener tamaño
    int obtenerTamaño() const {
        return tamaño;
    }
};

/* ===== COLA (QUEUE) ===== */

template <typename Tcola>
class Cola {
private:
    struct Nodo {
        Tcola dato;
        Nodo* siguiente;
        
        Nodo(const Tcola& valor) : dato(valor), siguiente(nullptr) {}
    };
    
    Nodo* frente;
    Nodo* final;
    int tamaño;
    
public:
    // Constructor
    Cola() : frente(nullptr), final(nullptr), tamaño(0) {}
    
    // Destructor
    ~Cola() {
        Nodo* actual = frente;
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
    
    // Verificar si está vacía
    bool estaVacia() const {
        return frente == nullptr;
    }
    
    // Insertar elemento (enqueue)
    void enqueue(const Tcola& dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        
        if (estaVacia()) {
            frente = nuevoNodo;
            final = nuevoNodo;
        } else {
            final->siguiente = nuevoNodo;
            final = nuevoNodo;
        }
        
        tamaño++;
    }
    
    // Eliminar elemento (dequeue)
    bool dequeue(Tcola& dato) {
        if (estaVacia()) return false;
        
        dato = frente->dato;
        Nodo* temp = frente;
        frente = frente->siguiente;
        delete temp;
        tamaño--;
        
        if (frente == nullptr) {
            final = nullptr;
        }
        
        return true;
    }
    
    // Ver el elemento del frente
    bool frenteCola(Tcola& dato) const {
        if (estaVacia()) return false;
        
        dato = frente->dato;
        return true;
    }
  
    // Obtener tamaño
    int obtenerTamaño() const {
        return tamaño;
    }
};

/* ===== ÁRBOL BINARIO ===== */

template <typename Tabb>
class ArbolBinario {
private:
    struct Nodo {
        Tabb dato;
        Nodo* izquierdo;
        Nodo* derecho;
        
        Nodo(const Tabb& valor) : dato(valor), izquierdo(nullptr), derecho(nullptr) {}
    };
    
    Nodo* raiz;
    
    // Función auxiliar para insertar
    Nodo* insertarRecursivo(Nodo* nodo, const Tabb& dato) {
        if (nodo == nullptr) {
            return new Nodo(dato);
        }
        
        if (dato < nodo->dato) {
            nodo->izquierdo = insertarRecursivo(nodo->izquierdo, dato);
        } else if (dato > nodo->dato) {
            nodo->derecho = insertarRecursivo(nodo->derecho, dato);
        }
        
        return nodo;
    }
    
    // Función auxiliar para buscar
    bool buscarRecursivo(Nodo* nodo, const Tabb& dato) const {
        if (nodo == nullptr) return false;
        
        if (nodo->dato == dato) return true;
        
        if (dato < nodo->dato) {
            return buscarRecursivo(nodo->izquierdo, dato);
        } else {
            return buscarRecursivo(nodo->derecho, dato);
        }
    }
    
    // Función auxiliar para encontrar el mínimo
    Nodo* encontrarMinimo(Nodo* nodo) const {
        Nodo* actual = nodo;
        
        while (actual && actual->izquierdo != nullptr) {
            actual = actual->izquierdo;
        }
        
        return actual;
    }
    
    // Función auxiliar para eliminar
    Nodo* eliminarRecursivo(Nodo* nodo, const Tabb& dato) {
        if (nodo == nullptr) return nodo;
        
        if (dato < nodo->dato) {
            nodo->izquierdo = eliminarRecursivo(nodo->izquierdo, dato);
        } else if (dato > nodo->dato) {
            nodo->derecho = eliminarRecursivo(nodo->derecho, dato);
        } else {
            // Caso 1: Nodo hoja o con un solo hijo
            if (nodo->izquierdo == nullptr) {
                Nodo* temp = nodo->derecho;
                delete nodo;
                return temp;
            } else if (nodo->derecho == nullptr) {
                Nodo* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }
            
            // Caso 2: Nodo con dos hijos
            Nodo* temp = encontrarMinimo(nodo->derecho);
            nodo->dato = temp->dato;
            nodo->derecho = eliminarRecursivo(nodo->derecho, temp->dato);
        }
        
        return nodo;
    }
    
    // Función auxiliar para liberar memoria
    void liberarRecursivo(Nodo* nodo) {
        if (nodo != nullptr) {
            liberarRecursivo(nodo->izquierdo);
            liberarRecursivo(nodo->derecho);
            delete nodo;
        }
    }
    
public:
    // Constructor
    ArbolBinario() : raiz(nullptr) {}
    
    // Destructor
    ~ArbolBinario() {
        liberarRecursivo(raiz);
    }
    
    // Insertar elemento
    void insertar(const Tabb& dato) {
        raiz = insertarRecursivo(raiz, dato);
    }
    
    // Buscar elemento
    bool buscar(const Tabb& dato) const {
        return buscarRecursivo(raiz, dato);
    }
    
    // Eliminar elemento
    void eliminar(const Tabb& dato) {
        raiz = eliminarRecursivo(raiz, dato);
    }
    
    // Verificar si el árbol está vacío
    bool estaVacio() const {
        return raiz == nullptr;
    }
};

#endif /* ESTRUCTURAS_DATOS_HPP */