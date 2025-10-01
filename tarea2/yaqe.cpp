#include <iostream>
#include <cstdlib>
#include <ctime>
#include "estructuras_datos.hpp"

// Estructura del nodo del árbol
struct TreeNode {
    int data;
    Lista<TreeNode*> children;
    
    TreeNode(int val) : data(val) {}
    
    // Método para agregar un hijo
    void AgregarSala(TreeNode* child) {
        children.append(child);
    }
    
    // Método para mostrar el nodo y sus hijos
    void MostrarSalas(int depth = 0) const {
        for (int i = 0; i < depth; ++i) std::cout << "  ";
        std::cout << "Nodo: " << data << std::endl;
        for (int i = 0; i < children.getSize(); ++i) {
            children[i]->MostrarSalas(depth + 1);
        }
    }
};

/**
 * Función: Asigna aleatoriamente 2 o 3 nodos como hijos
 * @param parent: Nodo padre al que se asignarán los hijos
 * @param candidateNodes: Lista de nodos candidatos para ser hijos
 */
void assignRandomChildren(TreeNode* parent, const Lista<TreeNode*>& candidateNodes) {
    
    if (!parent || candidateNodes.empty()) {
        std::cout << "Error: Nodo padre nulo o lista de candidatos vacía" << std::endl;
        return;
    }
    
    // Decidir aleatoriamente si asignar 2 o 3 hijos
    int numChildren = 2 + (rand() % 2); // Genera 2 o 3
    
    std::cout << "Asignando " << numChildren << " hijos al nodo " << parent->data << ":" << std::endl;
    
    for (int i = 0; i < numChildren; ++i) {
        int randomIndex = rand() % candidateNodes.getSize();
        parent->AgregarSala(candidateNodes[randomIndex]);
        std::cout << "  - Hijo: Nodo " << candidateNodes[randomIndex]->data << std::endl;
    }
}

// Función de ejemplo de uso
int main() {
    // Inicializar generador de números aleatorios
    srand(time(0));
    
    // Crear nodo padre
    TreeNode* parent = new TreeNode(1);
    
    // Crear lista de nodos candidatos
    Lista<TreeNode*> candidates;
    TreeNode* nodes[5];
    for (int i = 0; i < 5; ++i) {
        nodes[i] = new TreeNode(i + 2);
        candidates.append(nodes[i]);
    }
    
    std::cout << "=== ASIGNACIÓN DE HIJOS CON REUTILIZACIÓN ===" << std::endl;
    std::cout << "Nodos candidatos disponibles: ";
    for (int i = 0; i < candidates.getSize(); ++i) {
        std::cout << candidates[i]->data << " ";
    }
    std::cout << std::endl << std::endl;
    
    // Asignar hijos aleatoriamente 
    assignRandomChildren(parent, candidates);
    
    std::cout << std::endl << "Estructura del árbol resultante:" << std::endl;
    parent->MostrarSalas();
    
    // Ejemplo adicional con otro nodo
    std::cout << std::endl << "=== SEGUNDO EJEMPLO ===" << std::endl;
    TreeNode* parent2 = new TreeNode(10);
    assignRandomChildren(parent2, candidates);
    
    std::cout << std::endl << "Estructura del segundo árbol:" << std::endl;
    parent2->MostrarSalas();
    
    // Limpieza de memoria
    delete parent;
    delete parent2;
    for (int i = 0; i < 5; ++i) {
        delete nodes[i];
    }
    
    return 0;
}