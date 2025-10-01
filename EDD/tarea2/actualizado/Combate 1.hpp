#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "items.hpp"
using namespace std;

//TDA de listas para armas

#ifndef COMBATE_HPP
#define COMBATE_HPP

#define pD physic
#define fD fire
#define iD ice
#define wD wind
#define eD electric

void timer(double wait){
    time_t start;
    time_t curr;
    time(&start);
    time(&curr);
    while (difftime(curr, start) < wait){
        time(&curr);
    }
}

template <typename T>
struct node {
    T data;
    node* sig;
};

template <typename T>
class list {
private:

    node<T>* head;
    node<T>* tail;
    node<T>* curr;

    unsigned int listSize;
    unsigned int pos;

public:

    list(){
        head = tail = curr = nullptr;
        listSize = 0;
        pos = 0;
    }
    ~list(){};

    void clear(){
       node<T>* temp;
        curr = head;
        while (curr != nullptr) {
            temp = curr;
            curr = curr->sig;
            delete temp;
        }
        head = tail = curr = nullptr;
        listSize = 0;
        pos = 0;
    };
    int insert(T item){
        if (curr == nullptr) {
            append(item);
            return pos;
        }

        node<T>* aux = curr->sig;
        curr->sig = new node<T>;
        curr->sig->data = item;
        curr->sig->sig = aux;
        if (curr == tail) tail = curr->sig;
            listSize++;
    return pos;
};
    void append(T item){
        node<T>* newNode = new node<T>{item, nullptr};
        // tail = tail->sig;
        if (head == nullptr) {
            head = tail = curr = newNode;
        } else {
            tail->sig = newNode;
            tail = newNode;
        }
        listSize++;
};
    void erase(){
        if (head == nullptr) return;

        if (head == curr){
            node<T>* temp = head;
            head = head->sig;
            delete temp;
            listSize--;
            return;
        }

    // node<T>* prev = head;
    // while (prev->sig != nullptr && prev->sig->data != item) {
    //     prev = prev->sig;
    // }
    // if (prev->sig == nullptr) return false;

        node<T>* temp = curr;
        curr = temp->sig;
        delete temp;
        listSize--;
    };
    void moveToStart(){ curr = head; pos = 0;};
    void moveToEnd(){curr = tail; pos = listSize;};
    void next(){if (curr != tail) {curr = curr->sig; pos++;}};
    void prev(){
        node<T>* temp;
        if (curr == head) return;
        temp = head;
        while (temp->sig != curr) temp = temp->sig;
        curr = temp;
        pos--;
    };
    int length(){return listSize;};
    int currPos(){return pos;};
    void moveToPos(unsigned int posicion){
        unsigned int i;
        if (posicion < 0 || posicion > listSize) return;
        curr = head;
        pos = 0;
        for (i = 0; i < posicion; i++){
            curr = curr->sig;
            pos++;
        }
    };
    T getValue(){ return curr->data;};
    void copy(const list<T>& orig) {
        clear();

        node<T>* tempNode = orig.head;
        while (tempNode != nullptr) {
            append(tempNode->data);
            tempNode = tempNode->sig;
        }
    }

    template<typename T>
    node<T>*getNodeAt(int pos) {
    if (pos < 0 || static_cast<unsigned int>(pos) >= listSize) return nullptr;
        node<T>* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->sig;
        }
        return temp;
    }
    void randomize() {

        static bool seed = false;
        if (!seed) {
            srand(static_cast<unsigned>(time(0)));
            seed = true;
        }
        
        if (listSize < 2) return;

        srand(time(nullptr));  // Inicializa semilla aleatoria (solo una vez)

        for (int i = listSize - 1; i > 0; i--) {
            int j = rand() % (i + 1);

            // Obtener nodos en las posiciones i y j
            node<T>* nodeI = getNodeAt(i);
            node<T>* nodeJ = getNodeAt(j);

            if (nodeI && nodeJ) {
                // Intercambiar datos
                T tempData = nodeI->data;
                nodeI->data = nodeJ->data;
                nodeJ->data = tempData;
            }
        }
    }
};

struct Damage {
    float physic, fire, ice, wind, electric;

    Damage() {};
    Damage(float p, float f, float i, float w, float e)
        : physic(p), fire(f), ice(i), wind(w), electric(e) {};

    Damage(float a)
        : physic(a), fire(a), ice(a), wind(a), electric(a) {};
};

class Weapon {
private:

    //Default Damage
    string name;
    float accuracy;
    Damage attack;
    int energyCost;

    int type; //1 = melee, 2 = distancia, 3 = magia
    int burst;
    bool multipleShot;

    //Ranger Weapon
    int baseAmmo;
    int ammo;
    int reloadCost;

    //Magic Weapon
    int manaCost;
    float physicMagic; // without mana fisic damange


public:

    Weapon(){};
    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot, int t, int amun, int rCost, float pDamage, int mCost)
        : name(n), attack(atk), accuracy(acc), energyCost(eCost), burst(bur), multipleShot(mShot), type(t), baseAmmo(amun), reloadCost(rCost), physicMagic(pDamage), manaCost(mCost) {}

    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot)
        : name(n), attack(atk), accuracy(acc), energyCost(eCost), burst(bur), multipleShot(mShot), type(1) {}
    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot, int amun, int rCost)
        : name(n), attack(atk), accuracy(acc), energyCost(eCost), burst(bur), multipleShot(mShot), type(2), baseAmmo(amun), reloadCost(rCost) {}
    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot, float pDamage, int mCost)
        : name(n), attack(atk), accuracy(acc), energyCost(eCost), burst(bur), multipleShot(mShot), type(3), physicMagic(pDamage), manaCost(mCost) {}

    string getName() {return name;}

    int getType(){return type;}
    int getBurst(){return burst;}
    Damage getAttack() { return attack; }
    float getAccuracy(){ return accuracy;}
    bool isMultipleShot() { return multipleShot; }

    bool canAttack(int energy, int mana){

        if (energy < energyCost){
            cout << "Not enought energy. ";//_______________________________________________________[consola]
            return false;
        }
        if (type == 2 && ammo == 0){
            if (energy < reloadCost){
                cout << "Not enought energy. ";//_______________________________________________________[consola]
                return false;
            }
            energy -= reloadCost;
            ammo = baseAmmo;
            cout << "Weapon reloaded." << endl;//_______________________________________________________[consola]
            return false;
        }
        if (type == 3 && mana < manaCost){
            cout << "Not enought Battery. ";//_______________________________________________________[consola]
            return false;
        }
        if (type == 2)
            ammo--;
        if (type == 3)
            mana -= manaCost;
        energy -= energyCost;

        return true;
    }

};

class Enemy {
private:

    string name;

    float baseHealth;
    float health;

    float Attack;
    Damage Defence;
    float accuracy;

public:
    Enemy() {};
    Enemy(string n, float hp, float atk, Damage def, float acc) : name(n), baseHealth(hp), health(hp), Attack(atk), Defence(def), accuracy(acc) {};

    string getName() {return name;}

    float& getHealth(){return health;}
    float getAttack(){return Attack;}
    Damage getDefence(){return Defence;}
    float getAccuracy(){ return accuracy;}

    void receiveDamage(float dmg) {
        health -= dmg;
        if (health < 0)
            health = 0;
    }
};

class Player {
private:
    string name;
    //vida
    float baseHealth;
    float health;
    //energia para hacer acciones
    int baseEnergy;
    int energy;
    //mana
    int baseMana;
    int mana;
    int manaGain;

    //float attack;
    float accuracy;

    node<Weapon>* Winventory[4];
    int invLength;

    Damage attack;

public:
    Player() {};
    Player(string n, float hp, int stamina, int battery, int charge, float accur) : name(n), baseHealth(hp), health(hp), baseEnergy(stamina), energy(stamina), baseMana(battery), mana(battery), manaGain(charge), accuracy(accur) {};
    ~Player() {};

    float getHealth(){return health;}
    int getEnergy(){return energy;}
    int getMana(){return mana;}

    string getName(){return name;}
    
    float maxHealth(){return baseHealth;}
    int maxEnergy(){return baseEnergy;}
    int maxMana(){return baseMana;}

    Damage getAttack() { return attack; }
    float getAccuracy(){ return accuracy;}

    node<Weapon>* invWeapon(int i) {
        if (i >= 0 && i < 4)
            return Winventory[i];
        return nullptr;
    }
    int AmountWeapons(){return invLength;}

    void getNewWeapon(int slot, node<Weapon>* node){
        if (slot >= 0 && slot < 4){
            if (Winventory[slot] == nullptr) invLength++;
            Winventory[slot] = node;
        }
    }

    void startBattle(){health = baseHealth; energy = baseEnergy; mana = baseMana;}
    void playerTurn(){energy = baseEnergy; mana += manaGain;}

    void receiveDamage(float dmg) {
        health -= dmg;
        if (health < 0)
            health = 0;
    }

    void healthMod (float sum, float mult){
        baseHealth += sum;
        baseHealth *= mult;
    }

    void attackMod (Damage sum, Damage mult){
        attack.pD += sum.pD;
        attack.pD *= mult.pD;
        attack.fD += sum.fD;
        attack.fD *= mult.fD;
        attack.iD += sum.iD;
        attack.iD *= mult.iD;
        attack.wD += sum.wD;
        attack.wD *= mult.wD;
        attack.eD += sum.eD;
        attack.eD *= mult.eD;
    }

    void effect(int code, int sum, float mult) {
        switch (code) {
            case 0: baseEnergy += sum; baseEnergy *= mult; break;
            case 1: baseMana += sum; baseMana *= mult; break;
            case 2: manaGain += sum; manaGain *= mult; break;
            case 3: accuracy *= mult; break;
        }
    }

};

//const int MAX_EFFECTS = 4;
const int MAX_GEN_EFFECTS = 4;

class Item {
private:
    string name;

    // Efectos directos
    bool hasHealthMod = false;
    float hSum = 0, hMult = 1;

    bool hasAttackMod = false;
    Damage aSum, aMult;

    // Efectos generales (usando codes)
    int fxCode[MAX_GEN_EFFECTS];
    int fxSum[MAX_GEN_EFFECTS];
    float fxMult[MAX_GEN_EFFECTS];
    int fxCount = 0;

public:

    Item(string name) : name(name) {}

    void setHealthMod(float sum, float mult) {
        hasHealthMod = true;
        hSum = sum;
        hMult = mult;
    }

    void setAttackMod(Damage sum, Damage mult) {
        hasAttackMod = true;
        aSum = sum;
        aMult = mult;
    }

    void addEffect(int code, int sum, float mult) {
        if (fxCount < MAX_GEN_EFFECTS) {
            fxCode[fxCount] = code;
            fxSum[fxCount] = sum;
            fxMult[fxCount] = mult;
            fxCount++;
        }
    }

    void applyTo(Player& p) {
        if (hasHealthMod)
            p.healthMod(hSum, hMult);
        if (hasAttackMod)
            p.attackMod(aSum, aMult);
        for (int i = 0; i < fxCount; i++)
            p.effect(fxCode[i], fxSum[i], fxMult[i]);
    }
};


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
    // ===== INICIALIZACIÓN DE LISTAS =====

void inicializarEnemigosBase(list<Enemy>& enemigosBase) {
    // Desechos vivientes
    enemigosBase.append(Enemy("desecho_verde", 12, 10, {0, 0, 0, 0, 0}, 0.85));
    enemigosBase.append(Enemy("desecho_azul", 14, 8, {0.01, -0.1, 0.1, 0.1, -0.1}, 0.85));
    enemigosBase.append(Enemy("desecho_rojo", 10, 12, {0.01, 0.01, -0.1, -0.1, 0.01}, 0.85));
    
    // Cadáveres en descomposición
    enemigosBase.append(Enemy("no_muerto", 18, 12, {0, 0.04, 0.04, -0.3, -0.3}, 0.8));
    enemigosBase.append(Enemy("no_muerto_pesado", 20, 12, {0.5, 0, 0, -0.2, -0.2}, 0.8));
    enemigosBase.append(Enemy("no_muerto_violento", 14, 16, {0, 0.04, 0.04, -0.2, -0.2}, 0.85));
}

void inicializarEnemigosDefensivos(list<Enemy>& enemigosDefensivos) {
    // Rocas Vivientes
    enemigosDefensivos.append(Enemy("Gran_Roca", 35, 4, {-0.5, 0.5, 0.5, 0.5, 0.5}, 0.6));
    enemigosDefensivos.append(Enemy("Roca_Brillante_Caliente", 30, 6, {-0.5, 0.9, 0.2, 0.2, 0.2}, 0.6));
    enemigosDefensivos.append(Enemy("Roca_Brillante_Fria", 37, 3, {-0.6, -0.3, 0.95, 0.4, 0.4}, 0.5));
    enemigosDefensivos.append(Enemy("Roca_Flotante", 33, 9, {-0.4, 0.6, -0.2, 1, -0.4}, 0.75));
    enemigosDefensivos.append(Enemy("Roca_Electrica", 35, 7, {-0.5, 0.2, 0.2, 0.2, 0.9}, 0.85));
    
    // Ratas
    enemigosDefensivos.append(Enemy("Rata", 17, 10, {-1, 0.8, 0.8, 0.8, 0.8}, 0.8));
    enemigosDefensivos.append(Enemy("Rata_Bola_de_Fuego", 17, 10, {-1, -1, 0.95, 0.95, 0.95}, 0.8));
    enemigosDefensivos.append(Enemy("Rata_Carambano", 17, 10, {-1, 0.95, -1, 0.95, 0.95}, 0.8));
    enemigosDefensivos.append(Enemy("Rata_Vendaval", 17, 10, {-1, 0.95, 0.95, -1, 0.95}, 0.8));
    enemigosDefensivos.append(Enemy("Rata_Carga", 17, 10, {-1, 0.95, 0.95, 0.95, -1}, 0.8));
}

void inicializarEnemigosFuertes(list<Enemy>& enemigosFuertes) {
    // Saqueadores
    enemigosFuertes.append(Enemy("Saqueador", 10, 16, {0.2, -0.1, -0.1, -0.1, -0.1}, 0.65));
    enemigosFuertes.append(Enemy("Saqueador_con_kunai", 12, 20, {0, 0.1, 0.1, -0.3, -0.1}, 0.70));
    enemigosFuertes.append(Enemy("Saqueador_sobre_una_ballesta", 14, 30, {0.2, -0.2, -0.2, -0.1, 0.3}, 0.3));
    enemigosFuertes.append(Enemy("Saqueador_Brayan", 6, 19, {0.2, -0.3, 0.1, -0.1, 0}, 0.85));
    enemigosFuertes.append(Enemy("Saqueador_en_un_tanque_roto", 24, 35, {0.6, -0.2, -0.2, -0.2, -0.2}, 0.45));
    enemigosFuertes.append(Enemy("Saqueador_en_un_cohete", 4, 35, {0, 0, 0, 0, 0}, 0.50));
    
    // Mutantes
    enemigosFuertes.append(Enemy("Mutante", 18, 19, {0.2, -0.1, 0.2, -0.3, 0.1}, 0.3));
    enemigosFuertes.append(Enemy("Mutante_con_un_palo", 18, 24, {0, -0.4, 0, 0, 0.3}, 0.2));
    enemigosFuertes.append(Enemy("Orco_con_dos_palos", 18, 29, {0, -0.8, -0.4, 0, 0.6}, 0.15));
    enemigosFuertes.append(Enemy("Dos_Mutantes_amarrados_por_la_lengua", 36, 38, {0, 0, 0, 0, 0}, 0.1));
    enemigosFuertes.append(Enemy("Mutante_Mujer", 16, 18, {-0.3, 0, -0.1, 0, 0.2}, 0.6));
    
    // Enemigos especiales
    enemigosFuertes.append(Enemy("Pois", 150, 0.5, {0.85, 0.85, 0.85, 0.85, 0.85}, 0.95));
    enemigosFuertes.append(Enemy("Jama", 0.001, 999, {-1, -1, -1, -1, -1}, 0.0001));
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

    // Función para seleccionar enemigos aleatorios de una lista
    void  selectRandomEnemiesFromList(list<Enemy>& sourceList, Enemy* targetArray, int& currentIndex, int maxToSelect) {
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

#endif /* COMBATE_HPP */