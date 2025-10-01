#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "datos.hpp"
#include "items.hpp"     // Incluir para acceder a la función de items aleatorios

// Función para seleccionar enemigos aleatorios de una lista
void selectRandomEnemiesFromList(list<Enemy>& sourceList, Enemy* targetArray, int& currentIndex, int maxToSelect) {
    if (sourceList.length() == 0) return;
    
    // Crear una copia temporal de la lista para no modificar la original
    list<Enemy> tempList;
    tempList.copy(sourceList);
    tempList.randomize(); // Mezclar la lista
    
    tempList.moveToStart();
    int selected = 0;
    
    while (selected < maxToSelect && currentIndex < 4 && tempList.currPos() < tempList.length()) {
        targetArray[currentIndex] = tempList.getValue();
        currentIndex++;
        selected++;
        tempList.next();
    }
}

// Implementacion completa de la clase Combat con los metodos faltantes
class Combat {
private:
    int enemyListSize;
    Enemy* enemys;
    
    // Listas de enemigos por categoria
    list<Enemy> enemigosBase;
    list<Enemy> enemigosDefensivos;
    list<Enemy> enemigosFuertes;
    bool listsInitialized;

public:
    Combat() : enemyListSize(0), enemys(nullptr), listsInitialized(false) {}
    
    ~Combat() {
        if (enemys != nullptr) {
            delete[] enemys;
        }
    }
    
    // Inicializar las listas de enemigos
    void initializeEnemyLists() {
        if (!listsInitialized) {
            inicializarEnemigosBase(enemigosBase);
            inicializarEnemigosDefensivos(enemigosDefensivos);
            inicializarEnemigosFuertes(enemigosFuertes);
            listsInitialized = true;
        }
    }

    void setEnemyList() {
        // Inicializar listas si no están inicializadas
        initializeEnemyLists();
        
        // Limpiar enemigos anteriores si existen
        if (enemys != nullptr) {
            delete[] enemys;
        }
        
        // Inicializar generador aleatorio
        static bool seedInitialized = false;
        if (!seedInitialized) {
            srand(static_cast<unsigned>(time(0)));
            seedInitialized = true;
        }
        
        // Determinar número de enemigos (1-4)
        enemyListSize = (rand() % 4) + 1;
        enemys = new Enemy[enemyListSize];
        
        int currentIndex = 0;
        
        // Seleccionar enemigos de diferentes categorías aleatoriamente
        while (currentIndex < enemyListSize) {
            int category = rand() % 3; // 0: base, 1: defensivos, 2: fuertes
            
            switch (category) {
                case 0:
                    selectRandomEnemiesFromList(enemigosBase, enemys, currentIndex, 1);
                    break;
                case 1:
                    selectRandomEnemiesFromList(enemigosDefensivos, enemys, currentIndex, 1);
                    break;
                case 2:
                    selectRandomEnemiesFromList(enemigosFuertes, enemys, currentIndex, 1);
                    break;
            }
        }
        
        cout << "\n=== ENEMIGOS APARECEN ===" << endl;
        for (int i = 0; i < enemyListSize; i++) {
            cout << (i+1) << ". " << enemys[i].getName() 
                 << " (HP: " << enemys[i].getHealth() << ")" << endl;
        }
        cout << "=========================" << endl;
    }

    bool enemyHealth() {
        for (int i = 0; i < enemyListSize; i++) {
            if (enemys[i].getHealth() > 0) return false;
        }
        return true;
    }

    void applyDamageEnemy(Enemy& enemy, Damage weaponDmg, Damage playerDmg, Damage enemyDef, float weaponAcc, float playerAcc) {
        Damage finalDamage;

        if (static_cast<float>(rand()) / RAND_MAX > weaponAcc * playerAcc) {
            cout << "You missed the attack to " << enemy.getName() << endl;
            return;
        }

        if (weaponDmg.physic   > 0) {finalDamage.physic   = (weaponDmg.physic   + playerDmg.physic)   * (1 - enemyDef.physic  );} else {finalDamage.physic   = 0;}
        if (weaponDmg.fire     > 0) {finalDamage.fire     = (weaponDmg.fire     + playerDmg.fire)     * (1 - enemyDef.fire    );} else {finalDamage.fire     = 0;}
        if (weaponDmg.ice      > 0) {finalDamage.ice      = (weaponDmg.ice      + playerDmg.ice)      * (1 - enemyDef.ice     );} else {finalDamage.ice      = 0;}
        if (weaponDmg.wind     > 0) {finalDamage.wind     = (weaponDmg.wind     + playerDmg.wind)     * (1 - enemyDef.wind    );} else {finalDamage.wind     = 0;}
        if (weaponDmg.electric > 0) {finalDamage.electric = (weaponDmg.electric + playerDmg.electric) * (1 - enemyDef.electric);} else {finalDamage.electric = 0;}

        float totalDamage = finalDamage.physic + finalDamage.fire + finalDamage.ice + finalDamage.wind + finalDamage.electric;
        if (totalDamage < 0) {
            enemy.receiveDamage(totalDamage);
            cout << enemy.getName() << " regenerated " << -totalDamage << " of health." << endl;
            return;
        }
        enemy.receiveDamage(totalDamage);
        cout << enemy.getName() << " received " << totalDamage << " of damage.";

        if (weaponDmg.electric > 0) {effectivityMessage(enemyDef.electric); return;}
        if (weaponDmg.wind     > 0) {effectivityMessage(enemyDef.wind    ); return;}
        if (weaponDmg.ice      > 0) {effectivityMessage(enemyDef.ice     ); return;}
        if (weaponDmg.fire     > 0) {effectivityMessage(enemyDef.fire    ); return;}
        if (weaponDmg.physic   > 0) {effectivityMessage(enemyDef.physic  ); return;}
    }

    void effectivityMessage(float def) {
        if (def < -1) { cout << " That was very effective."   << endl;} else
        if (def < 0)  { cout << " That was effective."        << endl;} else
        if (def == 0) { cout <<                                  endl;} else
        if (def < 0.5){ cout << " That was uneffective."      << endl;} else
        if (def < 1)  { cout << " That was very uneffective." << endl;} else
        if (def == 1) { cout << " Enemy is Inmune."           << endl;}
    }

    void Combating(Player& player) {
        player.startBattle();
        
        while (true) {
            player.playerTurn();
            playerTurn(player);

            if (enemyHealth()) {
                // VICTORIA - implementación completa
                cout << "\n========================================" << endl;
                cout << "           ¡¡¡VICTORIA!!!" << endl;
                cout << "========================================" << endl;
                cout << "Has derrotado a todos los enemigos!" << endl;
                cout << "¡Felicitaciones guerrero!" << endl;
                cout << "========================================" << endl;
                
                // Ofrecer item aleatorio como recompensa
                cout << "\nComo recompensa por tu victoria," << endl;
                cout << "¡has encontrado items especiales!" << endl;
                selectRandomItems(player);
                
                return; // Salir del combate
            }
            
            enemyTurn(player);

            if (player.getHealth() <= 0) {
                cout << "\n========================================" << endl;
                cout << "           DERROTA..." << endl;
                cout << "========================================" << endl;
                cout << "Has sido derrotado en combate." << endl;
                cout << "¡Mejor suerte la próxima vez!" << endl;
                cout << "========================================" << endl;
                return; // Salir del combate
            }
        }
    }

    void enemyTurn(Player& player) {
        cout << "\n--- TURNO DE LOS ENEMIGOS ---" << endl;
        for (int i = 0; i < enemyListSize; i++) {
            if (enemys[i].getHealth() <= 0) continue; // Saltar enemigos muertos
            
            if (static_cast<float>(rand()) / RAND_MAX > enemys[i].getAccuracy()) {
                cout << enemys[i].getName() << " missed the attack." << endl;
                continue;
            }
            player.receiveDamage(enemys[i].getAttack());
            cout << "You received " << enemys[i].getAttack() << " of damage from " << enemys[i].getName() << "." << endl;
        }
        cout << "Current Health: " << player.getHealth() << "/" << player.maxHealth() << endl;
    }

    void playerTurn(Player& player) {
        if (enemys == nullptr) {
            setEnemyList();
        }

        string input;
        cout << "\n--- YOUR TURN ---" << endl;
        cout << "Health: " << player.getHealth() << "/" << player.maxHealth() << endl;
        cout << "Energy: " << player.getEnergy() << "/" << player.maxEnergy() << endl;
        cout << "Mana: " << player.getMana() << "/" << player.maxMana() << endl;
        cout << "\nEnemies:" << endl;
        for (int i = 0; i < enemyListSize; i++) {
            if (enemys[i].getHealth() > 0) {
                cout << (i+1) << ". " << enemys[i].getName() 
                     << " (HP: " << enemys[i].getHealth() << ")" << endl;
            } else {
                cout << (i+1) << ". " << enemys[i].getName() << " (DEAD)" << endl;
            }
        }
        
        cout << "\nChoose weapon (1-4) or type 'endTurn' to end turn: ";
        cin >> input;

        while (input != "endTurn") {
            int w;
            try {
                w = stoi(input) - 1;
            } catch (exception& e) {
                cout << "Invalid entry. Choose weapon (1-4) or 'endTurn': ";
                cin >> input;
                continue;
            }

            if (w < 0 || w >= 4) {
                cout << "Invalid weapon slot. Choose weapon (1-4) or 'endTurn': ";
                cin >> input;
                continue;
            }

            node<Weapon>* weaponNode = player.invWeapon(w);
            if (weaponNode == nullptr) {
                cout << "There's no weapon in that slot. Choose weapon (1-4) or 'endTurn': ";
                cin >> input;
                continue;
            }

            Weapon weapon = weaponNode->data;
            if (!weapon.canAttack(player.getEnergy(), player.getMana())) {
                cout << "Choose weapon (1-4) or 'endTurn': ";
                cin >> input;
                continue;
            }

            if (weapon.isMultipleShot()) {
                cout << "Using " << weapon.getName() << " against all enemies!" << endl;
                for (int f = 0; f < weapon.getBurst(); f++) {
                    for (int i = 0; i < enemyListSize; i++) {
                        if (enemys[i].getHealth() > 0) {
                            applyDamageEnemy(enemys[i], weapon.getAttack(), player.getAttack(), 
                                           enemys[i].getDefence(), weapon.getAccuracy(), player.getAccuracy());
                        }
                    }
                }
            } else {
                bool validTarget = false;
                while (!validTarget) {
                    cout << "Choose enemy (1-" << enemyListSize << "): ";
                    cin >> input;

                    int n;
                    try {
                        n = stoi(input) - 1;
                    } catch (exception& e) {
                        cout << "Invalid entry. ";
                        continue;
                    }

                    if (n < 0 || n >= enemyListSize) {
                        cout << "There's no enemy with that index. ";
                        continue;
                    }
                    
                    if (enemys[n].getHealth() <= 0) {
                        cout << "That enemy is already dead. ";
                        continue;
                    }

                    cout << "Attacking " << enemys[n].getName() << " with " << weapon.getName() << "!" << endl;
                    for (int i = 0; i < weapon.getBurst(); i++) {
                        applyDamageEnemy(enemys[n], weapon.getAttack(), player.getAttack(), 
                                       enemys[n].getDefence(), weapon.getAccuracy(), player.getAccuracy());
                    }
                    validTarget = true;
                }
            }

            cout << "\nChoose weapon (1-4) or type 'endTurn' to end turn: ";
            cin >> input;
        }
    }
};