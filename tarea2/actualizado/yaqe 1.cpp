#include <iostream>
#include <cstdlib>
#include <ctime>
#include "estructuras_datos 1.hpp"

using namespace std;

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
        cout << "Error: Nodo padre nulo o lista de candidatos vacía" << endl; //_______________________________________________________[consola]
        return;
    }
    
    // Decidir aleatoriamente si asignar 2 o 3 hijos
    int numChildren = 2 + (rand() % 2); // Genera 2 o 3
    
    cout << "Asignando " << numChildren << " hijos al nodo " << parent->data << ":" << endl; //_______________________________________________________[consola]
    
    for (int i = 0; i < numChildren; ++i) {
        int randomIndex = rand() % candidateNodes.getSize();
        parent->AgregarSala(candidateNodes[randomIndex]);
        cout << "  - Hijo: Nodo " << candidateNodes[randomIndex]->data << endl; //_______________________________________________________[consola]
    }
}

// // Función de ejemplo de uso
// int main() {
//     // Inicializar generador de números aleatorios
//     srand(time(0));
    
//     // Crear nodo padre
//     TreeNode* parent = new TreeNode(1);
    
//     // Crear lista de nodos candidatos
//     Lista<TreeNode*> candidates;
//     TreeNode* nodes[5];
//     for (int i = 0; i < 5; ++i) {
//         nodes[i] = new TreeNode(i + 2);
//         candidates.append(nodes[i]);
//     }
    
//     std::cout << "=== ASIGNACIÓN DE HIJOS CON REUTILIZACIÓN ===" << std::endl; //_______________________________________________________[consola]
//     std::cout << "Nodos candidatos disponibles: "; //_______________________________________________________[consola]
//     for (int i = 0; i < candidates.getSize(); ++i) {
//         std::cout << candidates[i]->data << " ";
//     }
//     cout << endl << endl;//_______________________________________________________[consola]
    
//     // Asignar hijos aleatoriamente 
//     assignRandomChildren(parent, candidates);
    
//     cout << endl << "Estructura del árbol resultante:" << endl; //_______________________________________________________[consola]
//     parent->MostrarSalas();
    
//     // Ejemplo adicional con otro nodo
//     cout << std::endl << "=== SEGUNDO EJEMPLO ===" << endl; //_______________________________________________________[consola]
//     TreeNode* parent2 = new TreeNode(10);
//     assignRandomChildren(parent2, candidates);
    
//     cout << endl << "Estructura del segundo árbol:" << endl;//_______________________________________________________[consola]
//     parent2->MostrarSalas();
    
//     // Limpieza de memoria
//     delete parent;
//     delete parent2;
//     for (int i = 0; i < 5; ++i) {
//         delete nodes[i];
//     }
    
    


//     return 0;
// }