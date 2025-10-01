#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Combate 1.hpp"

using namespace std;

// Constante para el número máximo de items
const int MAX_ITEMS = 30;

// Función para crear un item específico por índice
Item createSpecificItem(int index) {
    switch(index) {
        case 0: {
            Item item("Carne Podrida");
            item.setAttackMod(Damage(3, 0, 0, 0, 0), Damage(1));
            item.setHealthMod(-10, 1);
            return item;
        }
        case 1: {
            Item item("Carne");
            item.setAttackMod(Damage(5, 1, 1, 1, 1), Damage(1));
            return item;
        }
        case 2: {
            Item item("Carne de Lujo");
            item.setAttackMod(Damage(7, 2, 2, 2, 2), Damage(1));
            return item;
        }
        case 3: {
            Item item("Jugo Sabor Canela");
            item.setAttackMod(Damage(0, 4, 0, 4, 0), Damage(1));
            return item;
        }
        case 4: {
            Item item("Jugo Sabor Menta");
            item.setAttackMod(Damage(0, 0, 4, 0, 4), Damage(1));
            return item;
        }
        case 5: {
            Item item("Esteroides Anabolicos");
            item.setAttackMod(Damage(12, 0, 0, 0, 0), Damage(1));
            item.addEffect(0, -10, 1);
            return item;
        }
        case 6: {
            Item item("Inyeccion de Canela");
            item.setAttackMod(Damage(0, 8, 0, 8, 0), Damage(1));
            return item;
        }
        case 7: {
            Item item("Inyeccion de Menta");
            item.setAttackMod(Damage(0, 0, 8, 0, 8), Damage(1));
            return item;
        }
        case 8: {
            Item item("Video Motivacional");
            item.setAttackMod(Damage(0), Damage(2));
            return item;
        }
        case 9: {
            Item item("Una Lechuga");
            item.setHealthMod(15, 1);
            return item;
        }
        case 10: {
            Item item("Un Tomate");
            item.setHealthMod(20, 1);
            return item;
        }
        case 11: {
            Item item("Balde");
            item.setHealthMod(17, 1);
            return item;
        }
        case 12: {
            Item item("Tocar Pasto");
            item.setHealthMod(0, 1.2f);
            return item;
        }
        case 13: {
            Item item("Vendas");
            item.setHealthMod(25, 1);
            return item;
        }
        case 14: {
            Item item("Botiquin");
            item.setHealthMod(50, 1);
            return item;
        }
        case 15: {
            Item item("Una Pareja!!!");
            item.setHealthMod(0, 3);
            return item;
        }
        case 16: {
            Item item("Trotar un Rato");
            item.addEffect(0, 10, 1);
            return item;
        }
        case 17: {
            Item item("Barrita Energetica");
            item.addEffect(0, 5, 1);
            return item;
        }
        case 18: {
            Item item("Cafe Suave");
            item.addEffect(0, 0, 1.2f);
            return item;
        }
        case 19: {
            Item item("Cafe Cargado");
            item.addEffect(0, 0, 1.5f);
            return item;
        }
        case 20: {
            Item item("Cafe Doble Extra Cargado");
            item.addEffect(0, 0, 3.0f);
            item.setHealthMod(-25, 1);
            return item;
        }
        case 21: {
            Item item("Libro Ruso de Experimentos");
            item.addEffect(1, 20, 1);
            item.addEffect(2, 3, 1);
            return item;
        }
        case 22: {
            Item item("Investigacion de la CIA");
            item.addEffect(1, 17, 1);
            item.addEffect(2, 6, 1);
            return item;
        }
        case 23: {
            Item item("Caramelos de Colores");
            item.addEffect(1, 5, 1);
            return item;
        }
        case 24: {
            Item item("Caramelo Azul");
            item.addEffect(2, 1, 1);
            return item;
        }
        case 25: {
            Item item("Caramelo Rojo");
            item.addEffect(2, 1, 1);
            return item;
        }
        case 26: {
            Item item("Mantequilla");
            return item;
        }
        default: {
            Item item("Bendicion de Dios");
            return item;
        }
    }
}


// Función para obtener un item por nombre
Item* getItemByName(Item items[], const string& name) {
    string itemNames[28] = {
        "Carne Podrida", "Carne", "Carne de Lujo", "Jugo Sabor Canela", "Jugo Sabor Menta",
        "Esteroides Anabolicos", "Inyeccion de Canela", "Inyeccion de Menta", "Video Motivacional",
        "Una Lechuga", "Un Tomate", "Balde", "Tocar Pasto", "Vendas", "Botiquin", "Una Pareja!!!",
        "Trotar un Rato", "Barrita Energetica", "Cafe Suave", "Cafe Cargado", "Cafe Doble Extra Cargado",
        "Libro Ruso de Experimentos", "Investigacion de la CIA", "Caramelos de Colores", 
        "Caramelo Azul", "Caramelo Rojo", "Mantequilla", "Bendicion de Dios"
    };
    
    for (int i = 0; i < 28; i++) {
        if (itemNames[i] == name) {
            return &items[i];
        }
    }
    return nullptr;
}

// Función para aplicar efectos especiales que no se pueden manejar con la clase Item
void applySpecialItemEffects(const string& itemName, Player& player) {
    if (itemName == "Mantequilla") {
        cout << "La mantequilla ha eliminado el arma del primer slot!" << endl;
        player.getNewWeapon(0, nullptr); // Quita el arma del primer espacio
    }
    else if (itemName == "Bendicion de Dios") {
        cout << "dios a muerto" << endl;
    }
    else if (itemName == "Balde") {
        cout << "Tu estilo ha disminuido en 1 punto (pero sigues siendo genial)" << endl;
    }
    else if (itemName == "Cafe Doble Extra Cargado") {
        cout << "ahora tienes ansiedad!!" << endl;
    }
}

// Función para usar un item en un jugador
void useItem(Item& item, Player& player, const string& itemName) {
    cout << "Usando item: " << itemName << endl;
    
     if (itemName == "Mantequilla") {
         applySpecialItemEffects(itemName, player);
    }
    else if (itemName == "Bendicion de Dios") {
         applySpecialItemEffects(itemName, player);
    }
    else if (itemName == "Balde") {
         applySpecialItemEffects(itemName, player);
    }
    else if (itemName == "Cafe Doble Extra Cargado") {
         applySpecialItemEffects(itemName, player);
    }
    else (item.applyTo(player));   
    
    cout << "Item aplicado exitosamente!" << endl;
}

// Función para mostrar todos los items disponibles
void displayAllItems() {
    string itemNames[28] = {
        "Carne Podrida", "Carne", "Carne de Lujo", "Jugo Sabor Canela", "Jugo Sabor Menta",
        "Esteroides Anabolicos", "Inyeccion de Canela", "Inyeccion de Menta", "Video Motivacional",
        "Una Lechuga", "Un Tomate", "Balde", "Tocar Pasto", "Vendas", "Botiquin", "Una Pareja!!!",
        "Trotar un Rato", "Barrita Energetica", "Cafe Suave", "Cafe Cargado", "Cafe Doble Extra Cargado",
        "Libro Ruso de Experimentos", "Investigacion de la CIA", "Caramelos de Colores", 
        "Caramelo Azul", "Caramelo Rojo", "Mantequilla", "Bendicion de Dios"
    };
    
    cout << "\n=== LISTA DE TODOS LOS ITEMS ===" << endl;
    cout << "\n--- Items de Daño ---" << endl;
    for (int i = 0; i < 9; i++) {
        cout << (i + 1) << ". " << itemNames[i] << endl;
    }
    
    cout << "\n--- Items de Vida ---" << endl;
    for (int i = 9; i < 16; i++) {
        cout << (i + 1) << ". " << itemNames[i] << endl;
    }
    
    cout << "\n--- Items de Energia ---" << endl;
    for (int i = 16; i < 21; i++) {
        cout << (i + 1) << ". " << itemNames[i] << endl;
    }
    
    cout << "\n--- Items de Mana ---" << endl;
    for (int i = 21; i < 26; i++) {
        cout << (i + 1) << ". " << itemNames[i] << endl;
    }
    
    cout << "\n--- Otros Items ---" << endl;
    for (int i = 26; i < 28; i++) {
        cout << (i + 1) << ". " << itemNames[i] << endl;
    }
}


// Función para mostrar la descripción detallada de un item
void showItemDescription(const string& itemName) {
    cout << "\n=== " << itemName << " ===" << endl;
    
    if (itemName == "Carne Podrida") {
        cout << "Efecto: +3 ataque fisico, -10 vida maxima" << endl;
    }
    else if (itemName == "Carne") {
        cout << "Efecto: +5 ataque fisico, +1 a todos los ataques elementales" << endl;
    }
    else if (itemName == "Carne de Lujo") {
        cout << "Efecto: +7 ataque fisico, +2 a todos los ataques elementales" << endl;
    }
    else if (itemName == "Jugo Sabor Canela") {
        cout << "Efecto: +4 ataque de fuego y viento" << endl;
    }
    else if (itemName == "Jugo Sabor Menta") {
        cout << "Efecto: +4 ataque de hielo y electricidad" << endl;
    }
    else if (itemName == "Esteroides Anabolicos") {
        cout << "Efecto: +12 ataque fisico, -10 energia maxima" << endl;
    }
    else if (itemName == "Inyeccion de Canela") {
        cout << "Efecto: +8 ataque de fuego y viento" << endl;
    }
    else if (itemName == "Inyeccion de Menta") {
        cout << "Efecto: +8 ataque de hielo y electricidad" << endl;
    }
    else if (itemName == "Video Motivacional") {
        cout << "Efecto: x2 a todos los ataques" << endl;
    }
    else if (itemName == "Una Lechuga") {
        cout << "Efecto: +15 vida maxima" << endl;
    }
    else if (itemName == "Un Tomate") {
        cout << "Efecto: +20 vida maxima" << endl;
    }
    else if (itemName == "Balde") {
        cout << "Efecto: +17 vida maxima, -1 al estilo" << endl;
    }
    else if (itemName == "Tocar Pasto") {
        cout << "Efecto: x1.2 vida maxima" << endl;
    }
    else if (itemName == "Vendas") {
        cout << "Efecto: +25 vida" << endl;
    }
    else if (itemName == "Botiquin") {
        cout << "Efecto: +50 vida" << endl;
    }
    else if (itemName == "Una Pareja!!!") {
        cout << "Efecto: x3 vida maxima" << endl;
    }
    else if (itemName == "Trotar un Rato") {
        cout << "Efecto: +10 energia maxima" << endl;
    }
    else if (itemName == "Barrita Energetica") {
        cout << "Efecto: +5 energia maxima" << endl;
    }
    else if (itemName == "Cafe Suave") {
        cout << "Efecto: x1.2 energia maxima" << endl;
    }
    else if (itemName == "Cafe Cargado") {
        cout << "Efecto: x1.5 energia maxima" << endl;
    }
    else if (itemName == "Cafe Doble Extra Cargado") {
        cout << "Efecto: x3 energia maxima, -25 vida, ansiedad!" << endl;
    }
    else if (itemName == "Libro Ruso de Experimentos") {
        cout << "Efecto: +20 mana maximo, +3 regeneracion de mana" << endl;
    }
    else if (itemName == "Investigacion de la CIA") {
        cout << "Efecto: +17 mana maximo, +6 regeneracion de mana" << endl;
    }
    else if (itemName == "Caramelos de Colores") {
        cout << "Efecto: +5 mana maximo" << endl;
    }
    else if (itemName == "Caramelo Azul") {
        cout << "Efecto: +1 regeneracion de mana" << endl;
    }
    else if (itemName == "Caramelo Rojo") {
        cout << "Efecto: +1 regeneracion de mana" << endl;
    }
    else if (itemName == "Mantequilla") {
        cout << "Efecto: Te quita el arma del primer slot" << endl;
    }
    else if (itemName == "Bendicion de Dios") {
        cout << "Efecto: Muestra mensaje especial" << endl;
    }
}

// Función principal para seleccionar y usar items aleatorios
void selectRandomItems(Player& player) {
    // Array con todos los nombres de items
    string itemNames[28] = {
        "Carne Podrida", "Carne", "Carne de Lujo", "Jugo Sabor Canela", "Jugo Sabor Menta",
        "Esteroides Anabolicos", "Inyeccion de Canela", "Inyeccion de Menta", "Video Motivacional",
        "Una Lechuga", "Un Tomate", "Balde", "Tocar Pasto", "Vendas", "Botiquin", "Una Pareja!!!",
        "Trotar un Rato", "Barrita Energetica", "Cafe Suave", "Cafe Cargado", "Cafe Doble Extra Cargado",
        "Libro Ruso de Experimentos", "Investigacion de la CIA", "Caramelos de Colores", 
        "Caramelo Azul", "Caramelo Rojo", "Mantequilla", "Bendicion de Dios"
    };
    
    // Inicializar generador de números aleatorios
    static bool seedInitialized = false;
    if (!seedInitialized) {
        srand(static_cast<unsigned>(time(0)));
        seedInitialized = true;
    }
    
    // Seleccionar 3 items aleatorios únicos
    int selectedIndices[3];
    bool used[28] = {false}; // Para evitar duplicados
    
    for (int i = 0; i < 3; i++) {
        int randomIndex;
        do {
            randomIndex = rand() % 28;
        } while (used[randomIndex]);
        
        selectedIndices[i] = randomIndex;
        used[randomIndex] = true;
    }
    
    // Mostrar estadísticas actuales del jugador
    cout << "\n========================================" << endl;
    cout << "       SELECCION DE ITEMS ALEATORIOS" << endl;
    cout << "========================================" << endl;
    cout << "\nEstadisticas actuales:" << endl;
    cout << "Vida: " << player.getHealth() << "/" << player.maxHealth() << endl;
    cout << "Energia: " << player.getEnergy() << "/" << player.maxEnergy() << endl;
    cout << "Mana: " << player.getMana() << "/" << player.maxMana() << endl;
    
    // Mostrar los 3 items seleccionados
    cout << "\n¡Has encontrado 3 items! Elige uno:" << endl;
    cout << "========================================" << endl;
    
    for (int i = 0; i < 3; i++) {
        cout << "\n[" << (i + 1) << "] " << itemNames[selectedIndices[i]] << endl;
        showItemDescription(itemNames[selectedIndices[i]]);
    }
    
    // Pedir al jugador que seleccione
    int choice;
    string input;
    bool validChoice = false;
    
    cout << "\n========================================" << endl;
    cout << "Ingresa tu eleccion (1-3): ";
    
    while (!validChoice) {
        cin >> input;
        
        try {
            choice = stoi(input);
            if (choice >= 1 && choice <= 3) {
                validChoice = true;
            } else {
                cout << "Opcion invalida. Ingresa 1, 2 o 3: ";
            }
        } catch (exception& e) {
            cout << "Entrada invalida. Ingresa 1, 2 o 3: ";
        }
    }
    
    // Aplicar el item seleccionado
    int selectedIndex = selectedIndices[choice - 1];
    string selectedItemName = itemNames[selectedIndex];
    
    cout << "\n========================================" << endl;
    cout << "Has seleccionado: " << selectedItemName << endl;
    cout << "========================================" << endl;
    
    // Crear y usar el item seleccionado
    Item selectedItem = createSpecificItem(selectedIndex);
    useItem(selectedItem, player, selectedItemName);
    
    // Mostrar estadísticas finales
    cout << "\n--- Estadisticas actualizadas ---" << endl;
    cout << "Vida: " << player.getHealth() << "/" << player.maxHealth() << endl;
    cout << "Energia: " << player.getEnergy() << "/" << player.maxEnergy() << endl;
    cout << "Mana: " << player.getMana() << "/" << player.maxMana() << endl;
    cout << "========================================" << endl;
    
    // Pausa para que el jugador pueda leer
    cout << "\nPresiona Enter para continuar...";
    cin.ignore();
    cin.get();
}