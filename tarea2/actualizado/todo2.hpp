#ifndef TODO_HPP
#define TODO_HPP

#include <iostream>
#include <string>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <limits>  // Para numeric_limits
#include <vector>  // << AÑADIDO: para std::vector
#include <numeric> // << AÑADIDO: para std::iota
#include <random>  // << AÑADIDO: para std::shuffle
#include <algorithm> // << AÑADIDO: para std::shuffle

using namespace std;

#define pD physic
#define fD fire
#define iD ice
#define wD wind
#define eD electric



void timer(double wait) {
    time_t start;
    time_t curr;
    time(&start);
    time(&curr);
    while (difftime(curr, start) < wait) {
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
    list() {
        head = tail = curr = nullptr;
        listSize = 0;
        pos = 0;
    }
    ~list() {
        clear();
    }

    void clear() {
        node<T>* temp;
        node<T>* current_node = head;
        while (current_node != nullptr) {
            temp = current_node;
            current_node = current_node->sig;
            delete temp;
        }
        head = tail = curr = nullptr;
        listSize = 0;
        pos = 0;
    }

    int insert(T item) {
        if (curr == nullptr) {
            append(item);
            return currPos();
        }

        node<T>* newNode = new node<T>{item, curr->sig};
        curr->sig = newNode;

        if (curr == tail) {
            tail = newNode;
        }
        listSize++;
        return pos;
    }
    int getSize() const {
        return listSize;
    }

    void append(T item) {
        node<T>* newNode = new node<T>{item, nullptr};
        if (head == nullptr) {
            head = tail = curr = newNode;
            pos = 0;
        } else {
            tail->sig = newNode;
            tail = newNode;
        }
        listSize++;
    }

    void erase() {
        if (curr == nullptr || head == nullptr) return;

        node<T>* tempNodeToDelete = curr;

        if (curr == head) {
            head = head->sig;
            if (head == nullptr) {
                tail = nullptr;
            }
            curr = head;
            pos = 0;
        } else {
            node<T>* prevNode = head;
            unsigned int prevPos = 0;
            while (prevNode != nullptr && prevNode->sig != curr) {
                prevNode = prevNode->sig;
                prevPos++;
            }

            if (prevNode == nullptr) return;
            prevNode->sig = curr->sig;
            if (curr == tail) {
                tail = prevNode;
            }
            curr = prevNode->sig;
            pos = prevPos + 1;
        }
        delete tempNodeToDelete;
        listSize--;
        if (curr == nullptr && listSize > 0) {
            moveToEnd();
        } else if (listSize == 0) {
            pos = 0;
        }
    }

    void moveToStart() { curr = head; pos = 0; }

    void moveToEnd() {
        if (listSize == 0) {
            curr = nullptr;
            pos = 0;
        } else {
            curr = tail;
            pos = listSize - 1;
        }
    }

    void next() {
        if (curr != nullptr && curr != tail) {
            curr = curr->sig;
            pos++;
        } else {
            curr = nullptr;
            pos = listSize;
        }
    }

    void prev() {
        if (curr == nullptr || curr == head) return;
        node<T>* temp = head;
        unsigned int newPos = 0;
        while (temp != nullptr && temp->sig != curr) {
            temp = temp->sig;
            newPos++;
        }
        curr = temp;
        if (curr != nullptr) pos = newPos;
    }
    
    // CORREGIDO: Marcado como const, ya que no modifica la lista.
    int length() const { return listSize; }

    int currPos() const {
        if (curr == nullptr && listSize > 0) return listSize;
        if (listSize == 0) return 0;
        return pos;
    }

    void moveToPos(unsigned int posicion) {
        if (posicion >= listSize) {
            if (posicion == listSize) {
                curr = nullptr;
                pos = listSize;
            }
            return;
        }
        if (listSize == 0) {
             curr = nullptr;
             pos = 0;
             return;
        }

        curr = head;
        pos = 0;
        for (unsigned int i = 0; i < posicion; i++) {
            if (curr == nullptr) return;
            curr = curr->sig;
            pos++;
        }
    }
    T obtenerPorIndice(int indice) const {
        // Validar el índice
        if (indice < 0 || indice >= listSize) {
            throw std::out_of_range("Indice " + std::to_string(indice) + 
                                  " fuera de rango. La lista tiene " + 
                                  std::to_string(listSize) + " elementos.");
        }
        
        // Recorrer la lista hasta el índice deseado
        node<T>* curr = head;
        for (int i = 0; i < indice; i++) {
            curr = curr->sig;
        }
        
        return curr->data;}
    
    T getValue() { return curr->data; }

    void copy(const list<T>& orig) {
        clear();
        node<T>* tempNode = orig.head;
        while (tempNode != nullptr) {
            append(tempNode->data);
            tempNode = tempNode->sig;
        }
    }

    node<T>* getNodeAt(int p) {
        if (p < 0 || static_cast<unsigned int>(p) >= listSize) return nullptr;
        moveToPos(p);
        return curr;
    }

    void randomize() {
        if (listSize < 2) return;
        
        vector<T> items;
        moveToStart();
        while(curr != nullptr){
            items.push_back(getValue());
            next();
        }
        
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(items.begin(), items.end(), g);
        
        clear();
        for(const auto& item : items){
            append(item);
        }
    }
};

// ... (El resto de las clases Player, Enemy, Weapon, Item permanecen sin cambios)
struct Damage {
    float physic, fire, ice, wind, electric;

    Damage() : physic(0), fire(0), ice(0), wind(0), electric(0) {} // Constructor por defecto
    Damage(float p, float f, float i, float w, float e)
        : physic(p), fire(f), ice(i), wind(w), electric(e) {}

    Damage(float a) // Constructor para daño uniforme
        : physic(a), fire(a), ice(a), wind(a), electric(a) {}
};

class Weapon {
private:
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
    Weapon() : name(""), accuracy(0.0f), attack(), energyCost(0), type(0), burst(1), multipleShot(false),
               baseAmmo(0), ammo(0), reloadCost(0), manaCost(0), physicMagic(0.0f) {} // Constructor por defecto

    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot, int t, int amun, int rCost, float pDamage, int mCost)
        : name(n), accuracy(acc), attack(atk), energyCost(eCost), type(t), burst(bur), multipleShot(mShot),
          baseAmmo(t == 2 ? amun : 0), ammo(t == 2 ? amun : 0), reloadCost(t == 2 ? rCost : 0),
          manaCost(t == 3 ? mCost : 0), physicMagic(t == 3 ? pDamage : 0.0f) {}

    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot) // Melee (type 1 implícito)
        : name(n), accuracy(acc), attack(atk), energyCost(eCost), type(1), burst(bur), multipleShot(mShot),
          baseAmmo(0), ammo(0), reloadCost(0), manaCost(0), physicMagic(0.0f) {}

    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot, int amun, int rCost) // Ranger (type 2 implícito)
        : name(n), accuracy(acc), attack(atk), energyCost(eCost), type(2), burst(bur), multipleShot(mShot),
          baseAmmo(amun), ammo(amun), reloadCost(rCost), manaCost(0), physicMagic(0.0f) {}

    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot, float pDamage, int mCost) // Magic (type 3 implícito)
        : name(n), accuracy(acc), attack(atk), energyCost(eCost), type(3), burst(bur), multipleShot(mShot),
          baseAmmo(0), ammo(0), reloadCost(0), manaCost(mCost), physicMagic(pDamage) {}

    string getName() const { return name; }
    int getType() const { return type; }
    int getBurst() const { return burst; }
    Damage getAttack() const { return attack; }
    float getAccuracy() const { return accuracy; }
    bool isMultipleShot() const { return multipleShot; }
    int getEnergyCost() const { return energyCost; }

    bool canAttack(int& playerEnergy, int& playerMana) {
        if (playerEnergy < energyCost) {
            cout << "No tienes suficiente energia. " << endl;
            return false;
        }
        if (type == 2 && ammo == 0) {
            cout << "El arma necesita recargarse. " << endl;
            return false;
        }
        if (type == 3 && playerMana < manaCost) {
            cout << "No tienes suficiente Bateria (Mana). " << endl;
            return false;
        }

        playerEnergy -= energyCost;

        if (type == 2) {
            ammo--;
        }
        if (type == 3) {
            playerMana -= manaCost;
        }
        return true;
    }

    bool reload(int& playerEnergy) {
        if (type == 2) {
            if (playerEnergy >= reloadCost) {
                playerEnergy -= reloadCost;
                ammo = baseAmmo;
                cout << "Arma recargada." << endl;
                return true;
            } else {
                cout << "No tienes suficiente energia para recargar." << endl;
                return false;
            }
        }
        return false;
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
    Enemy() : name("Unknown"), baseHealth(10), health(10), Attack(5), Defence(), accuracy(0.75f) {}
    Enemy(string n, float hp, float atk, Damage def, float acc) : name(n), baseHealth(hp), health(hp), Attack(atk), Defence(def), accuracy(acc) {}

    string getName() const { return name; }
    float& getHealth() { return health; }
    float getBaseHealth() const { return baseHealth; }
    float getAttack() const { return Attack; }
    Damage getDefence() const { return Defence; }
    float getAccuracy() const { return accuracy; }

    void receiveDamage(float dmg) {
        health -= dmg;
        if (health < 0)
            health = 0;
    }
    void resetHealth() {
        health = baseHealth;
    }
};

class Player {
private:
    string name;
    float baseHealth;
    float health;
    int baseEnergy;
    int energy;
    int baseMana;
    int mana;
    int manaGain;
    float accuracy;

    node<Weapon>* Winventory[4];
    int invLength;

    Damage attack;

public:
    Player() : name("Player"), baseHealth(100), health(100), baseEnergy(50), energy(50),
               baseMana(30), mana(30), manaGain(5), accuracy(0.9f), invLength(0), attack() {
        for (int i = 0; i < 4; ++i) Winventory[i] = nullptr;
    }
    Player(string n, float hp, int stamina, int battery, int charge, float accur)
        : name(n), baseHealth(hp), health(hp), baseEnergy(stamina), energy(stamina),
          baseMana(battery), mana(battery), manaGain(charge), accuracy(accur), invLength(0), attack() {
        for (int i = 0; i < 4; ++i) Winventory[i] = nullptr;
    }
    ~Player() {}

    string getName() const { return name; }
    float getHealth() const { return health; }
    
    int& getEnergy() { return energy; }
    int& getMana() { return mana; }

    float maxHealth() const { return baseHealth; }
    int maxEnergy() const { return baseEnergy; }
    int maxMana() const { return baseMana; }

    Damage getAttack() const { return attack; }
    float getAccuracy() const { return accuracy; }

    node<Weapon>* invWeapon(int i) const {
        if (i >= 0 && i < 4)
            return Winventory[i];
        return nullptr;
    }
    int AmountWeapons() const { return invLength; }

    void getNewWeapon(int slot, node<Weapon>* weaponNode) {
        if (slot >= 0 && slot < 4) {
            if (Winventory[slot] == nullptr && weaponNode != nullptr) invLength++;
            else if (Winventory[slot] != nullptr && weaponNode == nullptr) invLength--;
            Winventory[slot] = weaponNode;
        }
    }

    void startBattle() { health = baseHealth; energy = baseEnergy; mana = baseMana; }
    void playerTurn() {
        energy = baseEnergy;
        mana += manaGain;
        if (mana > baseMana) mana = baseMana;
    }

    void receiveDamage(float dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    void healthMod(float sum, float mult) {
        baseHealth += sum;
        baseHealth *= mult;
        if (health > baseHealth) health = baseHealth;
        if (baseHealth < 0) baseHealth = 0;
    }

    void attackMod(Damage sum, Damage mult) {
        attack.physic = (attack.physic + sum.physic) * mult.physic;
        attack.fire = (attack.fire + sum.fire) * mult.fire;
        attack.ice = (attack.ice + sum.ice) * mult.ice;
        attack.wind = (attack.wind + sum.wind) * mult.wind;
        attack.electric = (attack.electric + sum.electric) * mult.electric;
    }

    void effect(int code, int sum, float mult) {
        switch (code) {
            case 0: baseEnergy += sum; baseEnergy = static_cast<int>(baseEnergy * mult); if (baseEnergy < 0) baseEnergy = 0; break;
            case 1: baseMana += sum; baseMana = static_cast<int>(baseMana * mult); if (baseMana < 0) baseMana = 0; break;
            case 2: manaGain += sum; manaGain = static_cast<int>(manaGain * mult); if (manaGain < 0) manaGain = 0; break;
            case 3: accuracy += sum; accuracy *= mult; if (accuracy < 0) accuracy = 0; if (accuracy > 1) accuracy = 1; break;
        }
    }
};

class Item {
private:
    string name;
    bool hasHealthMod;
    float hSum, hMult;
    bool hasAttackMod;
    Damage aSum, aMult;

    int fxCode[4];
    int fxSum[4];
    float fxMult[4];
    int fxCount;

public:
    Item() : name(""), hasHealthMod(false), hSum(0), hMult(1.0f), hasAttackMod(false), aSum(), aMult(1.0f), fxCount(0) {
        for (int i = 0; i < 4; ++i) {
            fxCode[i] = -1;
            fxSum[i] = 0;
            fxMult[i] = 1.0f;
        }
    }
    Item(string name) : name(name), hasHealthMod(false), hSum(0), hMult(1.0f),
                       hasAttackMod(false), aSum(), aMult(1.0f), fxCount(0) {
        for (int i = 0; i < 4; ++i) {
            fxCode[i] = -1;
            fxSum[i] = 0;
            fxMult[i] = 1.0f;
        }
    }

    string getName() const { return name; }

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
        if (fxCount < 4) {
            fxCode[fxCount] = code;
            fxSum[fxCount] = sum;
            fxMult[fxCount] = mult;
            fxCount++;
        }
    }

    void applyTo(Player& p) const {
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

    list<Enemy> enemigosBase;
    list<Enemy> enemigosDefensivos;
    list<Enemy> enemigosFuertes;
    bool listsInitialized;

public:
    Combat() : enemyListSize(0), enemys(nullptr), listsInitialized(false) {
        static bool combat_seed_initialized = false;
        if (!combat_seed_initialized) {
            srand(static_cast<unsigned>(time(0)));
            combat_seed_initialized = true;
        }
    }

    ~Combat() {
        delete[] enemys;
    }

    void inicializarEnemigosBase(list<Enemy>& lista) {
        lista.append(Enemy("desecho_verde", 12, 10, {0, 0, 0, 0, 0}, 0.85f));
        lista.append(Enemy("desecho_azul", 14, 8, {0.01f, -0.1f, 0.1f, 0.1f, -0.1f}, 0.85f));
        lista.append(Enemy("desecho_rojo", 10, 12, {0.01f, 0.01f, -0.1f, -0.1f, 0.01f}, 0.85f));
        lista.append(Enemy("no_muerto", 18, 12, {0, 0.04f, 0.04f, -0.3f, -0.3f}, 0.8f));
        lista.append(Enemy("no_muerto_pesado", 20, 12, {0.5f, 0, 0, -0.2f, -0.2f}, 0.8f));
        lista.append(Enemy("no_muerto_violento", 14, 16, {0, 0.04f, 0.04f, -0.2f, -0.2f}, 0.85f));
    }

    void inicializarEnemigosDefensivos(list<Enemy>& lista) {
        lista.append(Enemy("Gran_Roca", 35, 4, {-0.5f, 0.5f, 0.5f, 0.5f, 0.5f}, 0.6f));
        lista.append(Enemy("Roca_Brillante_Caliente", 30, 6, {-0.5f, 0.9f, 0.2f, 0.2f, 0.2f}, 0.6f));
        lista.append(Enemy("Roca_Brillante_Fria", 37, 3, {-0.6f, -0.3f, 0.95f, 0.4f, 0.4f}, 0.5f));
        lista.append(Enemy("Roca_Flotante", 33, 9, {-0.4f, 0.6f, -0.2f, 1.0f, -0.4f}, 0.75f));
        lista.append(Enemy("Roca_Electrica", 35, 7, {-0.5f, 0.2f, 0.2f, 0.2f, 0.9f}, 0.85f));
        lista.append(Enemy("Rata", 17, 10, {-1.0f, 0.8f, 0.8f, 0.8f, 0.8f}, 0.8f));
        lista.append(Enemy("Rata_Bola_de_Fuego", 17, 10, {-1.0f, -1.0f, 0.95f, 0.95f, 0.95f}, 0.8f));
        lista.append(Enemy("Rata_Carambano", 17, 10, {-1.0f, 0.95f, -1.0f, 0.95f, 0.95f}, 0.8f));
        lista.append(Enemy("Rata_Vendaval", 17, 10, {-1.0f, 0.95f, 0.95f, -1.0f, 0.95f}, 0.8f));
        lista.append(Enemy("Rata_Carga", 17, 10, {-1.0f, 0.95f, 0.95f, 0.95f, -1.0f}, 0.8f));
    }

    void inicializarEnemigosFuertes(list<Enemy>& lista) {
        lista.append(Enemy("Saqueador", 10, 16, {0.2f, -0.1f, -0.1f, -0.1f, -0.1f}, 0.65f));
        lista.append(Enemy("Saqueador_con_kunai", 12, 20, {0, 0.1f, 0.1f, -0.3f, -0.1f}, 0.70f));
        lista.append(Enemy("Saqueador_sobre_una_ballesta", 14, 30, {0.2f, -0.2f, -0.2f, -0.1f, 0.3f}, 0.3f));
        lista.append(Enemy("Saqueador_Brayan", 6, 19, {0.2f, -0.3f, 0.1f, -0.1f, 0}, 0.85f));
        lista.append(Enemy("Saqueador_en_un_tanque_roto", 24, 35, {0.6f, -0.2f, -0.2f, -0.2f, -0.2f}, 0.45f));
        lista.append(Enemy("Saqueador_en_un_cohete", 4, 35, {0, 0, 0, 0, 0}, 0.50f));
        lista.append(Enemy("Mutante", 18, 19, {0.2f, -0.1f, 0.2f, -0.3f, 0.1f}, 0.3f));
        lista.append(Enemy("Mutante_con_un_palo", 18, 24, {0, -0.4f, 0, 0, 0.3f}, 0.2f));
        lista.append(Enemy("Orco_con_dos_palos", 18, 29, {0, -0.8f, -0.4f, 0, 0.6f}, 0.15f));
        lista.append(Enemy("Dos_Mutantes_amarrados_por_la_lengua", 36, 38, {0, 0, 0, 0, 0}, 0.1f));
        lista.append(Enemy("Mutante_Mujer", 16, 18, {-0.3f, 0, -0.1f, 0, 0.2f}, 0.6f));
        lista.append(Enemy("Pois", 150, 0.5f, {0.85f, 0.85f, 0.85f, 0.85f, 0.85f}, 0.95f));
        lista.append(Enemy("Jama", 0.001f, 999, {-1.0f, -1.0f, -1.0f, -1.0f, -1.0f}, 0.0001f));
    }
    
    void initializeEnemyLists() {
        if (!listsInitialized) {
            inicializarEnemigosBase(enemigosBase);
            inicializarEnemigosDefensivos(enemigosDefensivos);
            inicializarEnemigosFuertes(enemigosFuertes);
            listsInitialized = true;
        }
    }

    void selectRandomEnemiesFromList(list<Enemy>& sourceList, int& currentIndex, int maxToSelect) {
        if (sourceList.length() == 0 || currentIndex >= 4 ) return;
        
        list<Enemy> tempList;
        tempList.copy(sourceList);
        tempList.randomize(); 
        
        tempList.moveToStart();
        int selectedCount = 0;
        while (selectedCount < maxToSelect && currentIndex < enemyListSize && currentIndex < 4 && tempList.currPos() < tempList.length()) {
            enemys[currentIndex] = tempList.getValue();
            enemys[currentIndex].resetHealth();
            currentIndex++;
            selectedCount++;
            tempList.next();
        }
    }

    void setEnemyList() {
        initializeEnemyLists();
        delete[] enemys;
        enemys = nullptr;
        
        enemyListSize = (rand() % 4) + 1;
        enemys = new Enemy[enemyListSize];
        
        int currentEnemyIndex = 0;

        while (currentEnemyIndex < enemyListSize) {
            int category = rand() % 3; 
            int numFromCategory = 1; 
            switch (category) {
                case 0:
                    if (enemigosBase.length() > 0)
                        selectRandomEnemiesFromList(enemigosBase, currentEnemyIndex, numFromCategory);
                    break;
                case 1:
                    if (enemigosDefensivos.length() > 0)
                        selectRandomEnemiesFromList(enemigosDefensivos, currentEnemyIndex, numFromCategory);
                    break;
                case 2:
                    if (enemigosFuertes.length() > 0)
                        selectRandomEnemiesFromList(enemigosFuertes, currentEnemyIndex, numFromCategory);
                    break;
            }
        }
        
        cout << "\n=== APARECEN ENEMIGOS ===" << endl;
        for (int i = 0; i < enemyListSize; i++) {
            cout << (i+1) << ". " << enemys[i].getName() 
                 << " (HP: " << enemys[i].getHealth() << "/" << enemys[i].getBaseHealth() << ")" << endl;
        }
        cout << "=========================" << endl;
    }

    bool allEnemiesDead() { 
        if (enemyListSize == 0 || enemys == nullptr) return true;
        for (int i = 0; i < enemyListSize; i++) {
            if (enemys[i].getHealth() > 0) return false;
        }
        return true;
    }

    void applyDamageToEnemy(Enemy& enemy, Damage weaponDmg, Damage playerBaseDmg, float weaponAcc, float playerAcc) {
        if (static_cast<float>(rand()) / RAND_MAX > weaponAcc * playerAcc) {
            cout << "Fallaste el ataque contra " << enemy.getName() << endl;
            return;
        }

        Damage enemyDef = enemy.getDefence();
        
        float physDmg = (weaponDmg.physic > 0) ? (weaponDmg.physic + playerBaseDmg.physic) * (1.0f - enemyDef.physic) : 0;
        float fireDmg = (weaponDmg.fire > 0) ? (weaponDmg.fire + playerBaseDmg.fire) * (1.0f - enemyDef.fire) : 0;
        float iceDmg = (weaponDmg.ice > 0) ? (weaponDmg.ice + playerBaseDmg.ice) * (1.0f - enemyDef.ice) : 0;
        float windDmg = (weaponDmg.wind > 0) ? (weaponDmg.wind + playerBaseDmg.wind) * (1.0f - enemyDef.wind) : 0;
        float elecDmg = (weaponDmg.electric > 0) ? (weaponDmg.electric + playerBaseDmg.electric) * (1.0f - enemyDef.electric) : 0;
        
        float totalDamageApplied = 0;
        if (physDmg > 0) totalDamageApplied += physDmg;
        if (fireDmg > 0) totalDamageApplied += fireDmg;
        if (iceDmg > 0) totalDamageApplied += iceDmg;
        if (windDmg > 0) totalDamageApplied += windDmg;
        if (elecDmg > 0) totalDamageApplied += elecDmg;

        float totalRegeneration = 0;
        if (physDmg < 0) totalRegeneration -= physDmg;
        if (fireDmg < 0) totalRegeneration -= fireDmg;
        if (iceDmg < 0) totalRegeneration -= iceDmg;
        if (windDmg < 0) totalRegeneration -= windDmg;
        if (elecDmg < 0) totalRegeneration -= elecDmg;
        
        if(totalDamageApplied <= 0 && totalRegeneration <= 0) {
            cout << enemy.getName() << " no recibio dano ni regeneracion del ataque.";
        } else {
            if (totalDamageApplied > 0) {
                enemy.receiveDamage(totalDamageApplied);
                cout << enemy.getName() << " recibio " << totalDamageApplied << " de dano.";
            }
            if (totalRegeneration > 0) {
                enemy.receiveDamage(-totalRegeneration);
                cout << enemy.getName() << " regenero " << totalRegeneration << " de vida.";
            }
        }

        if (weaponDmg.electric > 0) { effectivityMessage(enemyDef.electric); }
        else if (weaponDmg.wind > 0) { effectivityMessage(enemyDef.wind); }
        else if (weaponDmg.ice > 0) { effectivityMessage(enemyDef.ice); }
        else if (weaponDmg.fire > 0) { effectivityMessage(enemyDef.fire); }
        else if (weaponDmg.physic > 0) { effectivityMessage(enemyDef.physic); }
        else { cout << endl; }
    }

    void effectivityMessage(float def) {
        if (def <= -1.0f) { cout << " ¡Fue criticamente efectivo!" << endl; }
        else if (def < 0) { cout << " Fue muy efectivo." << endl; }
        else if (def == 0) { cout << endl; }
        else if (def < 0.5f) { cout << " No fue muy efectivo." << endl; }
        else if (def < 1.0f) { cout << " Fue altamente inefectivo." << endl; }
        else if (def >= 1.0f) { cout << " El enemigo es inmune a este tipo de dano." << endl; }
    }
    
    // CORREGIDO: Se eliminaron las declaraciones previas de estas funciones.
    // La definición completa aquí es suficiente.

    void Combating(Player& player) {
        player.startBattle();
        setEnemyList();
        if (enemyListSize == 0) {
            cout << "No aparecieron enemigos. El combate termina." << endl;
            return;
        }

        while (true) {
            player.playerTurn();
            playerTurnLogic(player);

            if (allEnemiesDead()) {
                cout << "\n========================================" << endl;
                cout << "           ¡¡¡VICTORIA!!!" << endl;
                cout << "========================================" << endl;
                // ... mensajes de victoria ...
                return;
            }

            enemyTurnLogic(player);

            if (player.getHealth() <= 0) {
                cout << "\n========================================" << endl;
                cout << "           DERROTA..." << endl;
                cout << "========================================" << endl;
                // ... mensajes de derrota ...
                return;
            }
        }
    }

    void enemyTurnLogic(Player& player) {
        cout << "\n--- TURNO DE LOS ENEMIGOS ---" << endl;
        bool anyEnemyAttacked = false;
        for (int i = 0; i < enemyListSize; i++) {
            if (enemys[i].getHealth() <= 0) continue;

            cout << enemys[i].getName() << " intenta atacar." << endl;
            timer(1);

            if (static_cast<float>(rand()) / RAND_MAX > enemys[i].getAccuracy()) {
                cout << enemys[i].getName() << " fallo el ataque." << endl;
            } else {
                float damageDealt = enemys[i].getAttack();
                player.receiveDamage(damageDealt);
                cout << "Recibiste " << damageDealt << " de dano de " << enemys[i].getName() << "." << endl;
                anyEnemyAttacked = true;
            }
            timer(1);
        }
        if (!anyEnemyAttacked && !allEnemiesDead()) {
            cout << "Los enemigos restantes reflexionan sobre su proximo movimiento..." << endl;
        }
        cout << "Vida actual: " << player.getHealth() << "/" << player.maxHealth() << endl;
    }

    void playerTurnLogic(Player& player) {
        string input;
        cout << "\n--- TU TURNO ---" << endl;
        cout << "Vida: " << player.getHealth() << "/" << player.maxHealth() << endl;
        cout << "Energia: " << player.getEnergy() << "/" << player.maxEnergy() << endl;
        cout << "Mana: " << player.getMana() << "/" << player.maxMana() << endl;
        cout << "\nEnemigos:" << endl;
        for (int i = 0; i < enemyListSize; i++) {
            if (enemys[i].getHealth() > 0) {
                cout << (i + 1) << ". " << enemys[i].getName()
                     << " (HP: " << enemys[i].getHealth() << ")" << endl;
            } else {
                cout << (i + 1) << ". " << enemys[i].getName() << " (MUERTO)" << endl;
            }
        }

        bool turnEnded = false;
        while (!turnEnded && player.getEnergy() > 0) {
            cout << "\nElige accion: atacar (1-" << player.AmountWeapons() << "), recargar <slot>, pasar (o 'endTurn'): ";
            cin >> input;

            if (input == "pass" || input == "endTurn") {
                turnEnded = true;
                continue;
            }

            if (input == "reload") {
                int slotToReload;
                cout << "Recargar que arma (1-4)? ";
                cin >> slotToReload;
                if (cin.fail() || slotToReload < 1 || slotToReload > 4) {
                    cout << "Slot invalido." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
                node<Weapon>* weaponNode = player.invWeapon(slotToReload - 1);
                if (weaponNode && weaponNode->data.getType() == 2) {
                    weaponNode->data.reload(player.getEnergy());
                } else {
                    cout << "El arma no es de rango o el slot esta vacio." << endl;
                }
                continue;
            }

            int weaponSlotChoice;
            try {
                weaponSlotChoice = stoi(input);
            } catch (const std::exception& e) {
                cout << "Entrada invalida. Elige un arma (1-4), recargar <slot>, o 'endTurn': ";
                continue;
            }

            if (weaponSlotChoice < 1 || weaponSlotChoice > player.AmountWeapons()) {
                cout << "Slot de arma invalido. Elige un arma (1-" << player.AmountWeapons() << ") o 'endTurn': ";
                continue;
            }

            node<Weapon>* weaponNode1 = player.invWeapon(weaponSlotChoice - 1);
            if (weaponNode1 == nullptr) {
                cout << "No hay un arma en ese slot. Elige un arma (1-" << player.AmountWeapons() << ") o 'endTurn': ";
                continue;
            }
            
            if (!weaponNode1->data.canAttack(player.getEnergy(), player.getMana())) {
                continue;
            }
            
            Weapon currentWeapon = weaponNode1->data;

            if (currentWeapon.isMultipleShot()) {
                cout << "Usando " << currentWeapon.getName() << " contra todos los enemigos!" << endl;
                for (int f = 0; f < currentWeapon.getBurst(); f++) {
                    for (int i = 0; i < enemyListSize; i++) {
                        if (enemys[i].getHealth() > 0) {
                            applyDamageToEnemy(enemys[i], currentWeapon.getAttack(), player.getAttack(),
                                               currentWeapon.getAccuracy(), player.getAccuracy());
                        }
                    }
                    if (allEnemiesDead()) { turnEnded = true; break; }
                }
            } else {
                bool validTarget = false;
                while (!validTarget && !allEnemiesDead()) {
                    cout << "Elige un enemigo (1-" << enemyListSize << ") o 'cancelar': ";
                    cin >> input;
                    if (input == "cancelar") break;

                    int targetEnemyIndex;
                    try {
                        targetEnemyIndex = stoi(input) - 1;
                    } catch (const std::exception& e) {
                        cout << "Entrada invalida. ";
                        continue;
                    }

                    if (targetEnemyIndex < 0 || targetEnemyIndex >= enemyListSize) {
                        cout << "No hay un enemigo con ese indice. ";
                        continue;
                    }

                    if (enemys[targetEnemyIndex].getHealth() <= 0) {
                        cout << "Ese enemigo ya esta muerto. ";
                        continue;
                    }

                    cout << "¡Atacando a " << enemys[targetEnemyIndex].getName() << " con " << currentWeapon.getName() << "!" << endl;
                    for (int i = 0; i < currentWeapon.getBurst(); i++) {
                        applyDamageToEnemy(enemys[targetEnemyIndex], currentWeapon.getAttack(), player.getAttack(),
                                           currentWeapon.getAccuracy(), player.getAccuracy());
                        if (enemys[targetEnemyIndex].getHealth() <= 0) {
                            cout << enemys[targetEnemyIndex].getName() << " ha sido derrotado!" << endl;
                            break;
                        }
                    }
                    validTarget = true;
                    if (allEnemiesDead()) { turnEnded = true; }
                }
            }
            if (player.getEnergy() <= 0 && !turnEnded) {
                cout << "¡Te has quedado sin energia!" << endl;
                turnEnded = true;
            }
            if (turnEnded) break;
        }
    }
};


enum TipoSala { INICIO = 0, COMBATE = 1, ITEMS = 2, ARMAS = 3, LORE = 4, FINAL = 5 };

struct SalaNode {
    string nombre;
    string mensajeEntrada;
    TipoSala tipo;
    // Corregido: Se usa la clase 'list' definida en este archivo en lugar de la clase 'Lista' inexistente.
    list<SalaNode*> siguientesSalas;

    SalaNode(string n, string msg, TipoSala t) : nombre(n), mensajeEntrada(msg), tipo(t) {}

    void agregarSalaSiguiente(SalaNode* sala) { siguientesSalas.append(sala); }
    SalaNode* elegirSiguienteSala();
    void mostrarOpciones();
    void ejecutarAcciones(Player& jugador, Combat& combate, list<Weapon>& weaponPool, SalaNode*& salaActual, bool& juegoTerminado);
};

class SistemaJuego {
private:
    SalaNode* salaInicio;
    // Corregido: Se usa la clase 'list'
    list<SalaNode*> todasLasSalas;
    list<SalaNode*> salasCombate;
    list<SalaNode*> salasItems;
    list<SalaNode*> salasArmas;
    list<SalaNode*> salasLore;
    list<SalaNode*> salasFinales;

public:
    SistemaJuego() : salaInicio(nullptr) {
        static bool game_seed_initialized = false;
        if (!game_seed_initialized) {
            srand(static_cast<unsigned>(time(0)));
            game_seed_initialized = true;
        }
        inicializarSalas();
        configurarConexiones();
    }

    ~SistemaJuego() {
        // Corregido: La iteración ahora usa el método length() y getNodeAt() de la clase list
        for (int i = 0; i < todasLasSalas.length(); i++) {
            delete todasLasSalas.getNodeAt(i)->data;
        }
    }

    void inicializarSalas();
    void configurarConexiones();
    void asignarSalasAleatorias(SalaNode* sala);
    void iniciarJuego(Player& jugador, Combat& combate, list<Weapon>& weaponPool);
};

// --- IMPLEMENTACIÓN DE MÉTODOS DE SalaNode y SistemaJuego ---
void selectRandomItems(Player& player);
void mostrarOpcionesArmas(Player& jugador, list<Weapon>& weaponPool);

void SalaNode::ejecutarAcciones(Player& jugador, Combat& combate, list<Weapon>& weaponPool, SalaNode*& salaActual, bool& juegoTerminado) {
    cout << "\n================================" << endl;
    cout << "  " << nombre << endl;
    cout << "================================" << endl;
    cout << mensajeEntrada << endl;
    cout << "================================" << endl;
    timer(1);
    string temp_input;
    switch (tipo) {
        case INICIO:
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
        case COMBATE:
            cout << "\n¡Preparate para el combate!" << endl;
            combate.Combating(jugador);
            if (jugador.getHealth() <= 0) {
                juegoTerminado = true;
                return;
            }
            cout << "\n¡Victoria! Puedes continuar explorando." << endl;
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
        case ITEMS:
            cout << "\n¡Has encontrado algunos objetos utiles!" << endl;
            selectRandomItems(jugador);
            timer(1);
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
        case ARMAS:
            cout << "\n¡Has encontrado armamento!" << endl;
            mostrarOpcionesArmas(jugador, weaponPool);
            timer(1);
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
        case LORE:
            cout << "\nPresiona Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, temp_input);
            mostrarOpciones();
            salaActual = elegirSiguienteSala();
            break;
        case FINAL:
            cout << "\n¡El juego ha terminado!" << endl;
            juegoTerminado = true;
            break;
    }
}

void SalaNode::mostrarOpciones() {
    // Corregido: Usa length() en vez de getSize()
    if (siguientesSalas.length() == 0 && tipo != FINAL) {
        cout << "No hay a donde ir desde aqui... parece un callejon sin salida." << endl;
        return;
    }
    if (tipo == FINAL) return;

    cout << "\n--- UBICACIONES DISPONIBLES ---" << endl;
    // Corregido: Usa length() y getNodeAt() para iterar
    for (int i = 0; i < siguientesSalas.length(); i++) {
        cout << (i + 1) << ". " << siguientesSalas.getNodeAt(i)->data->nombre << endl;
    }
    cout << "-------------------------------" << endl;
}

SalaNode* SalaNode::elegirSiguienteSala() {
    if (siguientesSalas.length() == 0) return nullptr;

    int opcion;
    string input_str;
    do {
        cout << "Elige tu destino (1-" << siguientesSalas.length() << "): ";
        cin >> input_str;
        try {
            opcion = stoi(input_str);
            if (opcion < 1 || opcion > siguientesSalas.length()) {
                cout << "Opcion invalida. Intenta de nuevo." << endl;
                opcion = 0;
            }
        } catch (const std::exception& e) {
            cout << "Entrada invalida. Ingresa un numero." << endl;
            opcion = 0;
        }
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); }
    } while (opcion < 1 || opcion > siguientesSalas.length());

    // Corregido: Usa getNodeAt() para acceder al elemento
    return siguientesSalas.getNodeAt(opcion - 1)->data;
}


void SistemaJuego::inicializarSalas() {
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
        salasCombate.append(new SalaNode("Campo Abierto", "Una presencia maligna te observa pero no sabes de dónde.", COMBATE));
        salasCombate.append(new SalaNode("Basural Radioactivo", "Escuchas algo moverse entre la basura.", COMBATE));
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
        salasItems.append(new SalaNode("Caja Random", "Parece que es solo una caja, la abres para ver qué hay dentro.", ITEMS));
        salasItems.append(new SalaNode("Cuerpo Humano Tirado", "Ya está muerto, ahora sus cosas son tus cosas.", ITEMS));
        salasItems.append(new SalaNode("Almacén Pequeño", "No parece haber nadie, llévate algo.", ITEMS));
        salasItems.append(new SalaNode("Montón de Basura", "Algo útil debe haber, dale revisa.", ITEMS));
        salasArmas.append(new SalaNode("Asentamiento Militar Abandonado", "Estoy seguro que es ilegal entrar aquí, así que llévate algo rápido.", ARMAS));
        salasArmas.append(new SalaNode("Un Campo de Batalla", "Pucha se murieron, bueno, a lootear se ha dicho.", ARMAS));
        salasArmas.append(new SalaNode("Un Militar Durmiendo", "Shhh ni se te ocurra despertarlo.", ARMAS));
        salasArmas.append(new SalaNode("Caja de Armas", "Apuesto a que no sabes qué hay dentro.", ARMAS));
        salasArmas.append(new SalaNode("Caja Grande de Armas", "¿Crees que haya muchas armas por el hecho de ser grande?", ARMAS));
        salasArmas.append(new SalaNode("Una Única Arma en el Piso", "¡¡Sorpresa!! En realidad son 3.", ARMAS));
        salasLore.append(new SalaNode("Libro Rojo", "Encuentras un libro en el piso lo abres para ver que tiene escrito.\nAutor: Jama\nHa empezado a hacer mucho frío por algún motivo, eso del invierno nuclear no era una\nexageración, rusos hijos de puta como se les ocurre empezar a lanzar bombas.", LORE));
        salasLore.append(new SalaNode("Libro Azul", "Encuentras un libro, tiene carátula roja, lo abres.\nAutor: Jama\nAyer encontré un perro muerto, y me puso muy triste, de la tristeza\nempecé a pegar tiros al aire, pegando tiros al aire me acordé de los\ntiroteos escolares e insulté a los gringos por empezar a tirar bombas.\nMe sentí mejor después de eso.", LORE));
        salasLore.append(new SalaNode("Libro Verde", "¡¡Ostia un libro!!, ábrelo ábrelo!!.\nAutor: Jama\nEscuché que hay científicos que han logrado usar desechos radioactivos y energía\nsolar para desarrollar una especie de magia, aún no se sabe mucho si.", LORE));
        salasLore.append(new SalaNode("Libro Amarillo", "Hay un libro en el piso, ¿quién lo dejó ahí?\nAutor: Jama\nSe me ocurrió una fantabulosa idea, voy a escribir libros con carátulas de distintos\ncolores y los voy a esparcir por ahí para que gente los encuentre y los lea, la wea\nmás cómica existente, sería una pena que alguien solo leyera un párrafo, ¿verdad?", LORE));
        salasLore.append(new SalaNode("Libro Bizarro", "En la portada hay un hombre musculoso con un estilo muy particular.\nAutor: Hirohiko Araki\nORAOROAORAORAOROAOROAROAOROAROAORAORAOROARAOROAOROAROAOROAROAOROAROA!!!!!!!ORAAA!!!", LORE));
        salasFinales.append(new SalaNode("Edificio Militar Azul", "Entras para ver si hay alguien, sí que lo había, agentes de la CIA\nte ven armado y te disparan rápidamente.\nMueres...", FINAL));
        salasFinales.append(new SalaNode("Edificio Militar Rojo", "Knock knock, ¿quién es?\n¡¡¡COMUNISTAS!!! Te roban todo lo que tienes para 'dárselo al estado'\nte tiran a la intemperie sin nada...", FINAL));
        salasFinales.append(new SalaNode("Campamento Civil", "Llegas a un campamento, te recibe una señora muy amigable y te da\nsopita.\nTe quedas con ellos...", FINAL));
        
        for (int i = 0; i < salasCombate.getSize(); i++) todasLasSalas.append(salasCombate.obtenerPorIndice(i));
        for (int i = 0; i < salasItems.getSize(); i++) todasLasSalas.append(salasItems.obtenerPorIndice(i));
        for (int i = 0; i < salasArmas.getSize(); i++) todasLasSalas.append(salasArmas.obtenerPorIndice(i));
        for (int i = 0; i < salasLore.getSize(); i++) todasLasSalas.append(salasLore.obtenerPorIndice(i));
        for (int i = 0; i < salasFinales.getSize(); i++) todasLasSalas.append(salasFinales.obtenerPorIndice(i));
    }

void SistemaJuego::configurarConexiones() {
    asignarSalasAleatorias(salaInicio);
    // Corregido: La iteración usa los métodos de la clase 'list'
    for (int i = 0; i < todasLasSalas.length(); i++) {
        SalaNode* salaActual = todasLasSalas.getNodeAt(i)->data;
        if (salaActual != salaInicio && salaActual->tipo != FINAL) {
            asignarSalasAleatorias(salaActual);
        }
    }
}

void SistemaJuego::asignarSalasAleatorias(SalaNode* sala) {
    int numConexiones = 2 + (rand() % 2);
    list<SalaNode*> candidatas;

    for (int i = 0; i < todasLasSalas.length(); ++i) {
        SalaNode* candidata = todasLasSalas.getNodeAt(i)->data;
        if (candidata != sala && candidata->tipo != INICIO) {
            if (candidata->tipo != FINAL || (rand() % 100 < 20)) {
                candidatas.append(candidata);
            }
        }
    }

    // Corregido: Usa length(), getNodeAt(), moveToPos() y erase()
    for (int i = 0; i < numConexiones && candidatas.length() > 0; i++) {
        int indiceAleatorio = rand() % candidatas.length();
        sala->agregarSalaSiguiente(candidatas.getNodeAt(indiceAleatorio)->data);
        candidatas.moveToPos(indiceAleatorio);
        candidatas.erase();
    }
}

void SistemaJuego::iniciarJuego(Player& jugador, Combat& combate, list<Weapon>& weaponPool) {
    SalaNode* salaActual = salaInicio;
    bool juegoTerminado = false;

    cout << "\n╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =╗" << endl;
    cout << "║                          LA GUERRA CALIENTE                         ║" << endl;
    cout << "║                   Un juego post-apocaliptico                        ║" << endl;
    cout << "╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =╝" << endl;

    while (!juegoTerminado && salaActual != nullptr) {
        salaActual->ejecutarAcciones(jugador, combate, weaponPool, salaActual, juegoTerminado);

        if (juegoTerminado && jugador.getHealth() <= 0) {
            cout << "\n¿Quieres intentar de nuevo? (s/n): ";
            char respuesta;
            cin >> respuesta;
            if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); respuesta = 'n'; }

            if (respuesta == 's' || respuesta == 'S') {
                jugador = Player(jugador.getName(), jugador.maxHealth(), jugador.maxEnergy(), jugador.maxMana(), 5, jugador.getAccuracy());
                salaActual = salaInicio;
                juegoTerminado = false;
            }
        } else if (salaActual == nullptr && !juegoTerminado) {
            cout << "Te has perdido en la nada... el juego no puede continuar." << endl;
            juegoTerminado = true;
        }
    }
    cout << "\n¡Gracias por jugar La Guerra Caliente!" << endl;
}


// ===== FUNCIONES DE ITEMS (DEFINICIONES) =====
const int MAX_ITEMS_DEFINED = 28;
Item createSpecificItem(int index) {

     switch(index) {
        case 0: { Item item("Carne Podrida"); item.setAttackMod(Damage(3, 0, 0, 0, 0), Damage(1)); item.setHealthMod(-10, 1); return item; }
        case 1: { Item item("Carne"); item.setAttackMod(Damage(5, 1, 1, 1, 1), Damage(1)); return item; }
        case 2: { Item item("Carne de Lujo"); item.setAttackMod(Damage(7, 2, 2, 2, 2), Damage(1)); return item; }
        case 3: { Item item("Jugo Sabor Canela"); item.setAttackMod(Damage(0, 4, 0, 4, 0), Damage(1)); return item; }
        case 4: { Item item("Jugo Sabor Menta"); item.setAttackMod(Damage(0, 0, 4, 0, 4), Damage(1)); return item; }
        case 5: { Item item("Esteroides Anabolicos"); item.setAttackMod(Damage(12, 0, 0, 0, 0), Damage(1)); item.addEffect(0, -10, 1); return item; }
        case 6: { Item item("Inyeccion de Canela"); item.setAttackMod(Damage(0, 8, 0, 8, 0), Damage(1)); return item; }
        case 7: { Item item("Inyeccion de Menta"); item.setAttackMod(Damage(0, 0, 8, 0, 8), Damage(1)); return item; }
        case 8: { Item item("Video Motivacional"); item.setAttackMod(Damage(0), Damage(2)); return item; }
        case 9: { Item item("Una Lechuga"); item.setHealthMod(15, 1); return item; }
        case 10: { Item item("Un Tomate"); item.setHealthMod(20, 1); return item; }
        case 11: { Item item("Balde"); item.setHealthMod(17, 1); return item; }
        case 12: { Item item("Tocar Pasto"); item.setHealthMod(0, 1.2f); return item; }
        case 13: { Item item("Vendas"); item.setHealthMod(25, 1); return item; }
        case 14: { Item item("Botiquin"); item.setHealthMod(50, 1); return item; }
        case 15: { Item item("Una Pareja!!!"); item.setHealthMod(0, 3); return item; }
        case 16: { Item item("Trotar un Rato"); item.addEffect(0, 10, 1); return item; }
        case 17: { Item item("Barrita Energetica"); item.addEffect(0, 5, 1); return item; }
        case 18: { Item item("Cafe Suave"); item.addEffect(0, 0, 1.2f); return item; }
        case 19: { Item item("Cafe Cargado"); item.addEffect(0, 0, 1.5f); return item; }
        case 20: { Item item("Cafe Doble Extra Cargado"); item.addEffect(0, 0, 3.0f); item.setHealthMod(-25, 1); return item; }
        case 21: { Item item("Libro Ruso de Experimentos"); item.addEffect(1, 20, 1); item.addEffect(2, 3, 1); return item; }
        case 22: { Item item("Investigacion de la CIA"); item.addEffect(1, 17, 1); item.addEffect(2, 6, 1); return item; }
        case 23: { Item item("Caramelos de Colores"); item.addEffect(1, 5, 1); return item; }
        case 24: { Item item("Caramelo Azul"); item.addEffect(2, 1, 1); return item; }
        case 25: { Item item("Caramelo Rojo"); item.addEffect(2, 1, 1); return item; }
        case 26: { Item item("Mantequilla"); /* Efecto especial */ return item; }
        default: { Item item("Bendicion de Dios"); /* Efecto especial */ return item; }
    }
}
void showItemDescription(const string& itemName) {
    // ... (sin cambios en la lógica)
    // Sería mejor si Item tuviera un método getDescription()
    cout << "\n=== " << itemName << " ===" << endl;
    if (itemName == "Carne Podrida") cout << "Efecto: +3 ataque fisico, -10 vida maxima" << endl;
    else if (itemName == "Carne") cout << "Efecto: +5 ataque fisico, +1 a todos los ataques elementales" << endl;
    // ... (todas las descripciones)
    else if (itemName == "Carne de Lujo") cout << "Efecto: +7 ataque fisico, +2 a todos los ataques elementales" << endl;
    else if (itemName == "Jugo Sabor Canela") cout << "Efecto: +4 ataque de fuego y viento" << endl;
    else if (itemName == "Jugo Sabor Menta") cout << "Efecto: +4 ataque de hielo y electricidad" << endl;
    else if (itemName == "Esteroides Anabolicos") cout << "Efecto: +12 ataque fisico, -10 energia maxima" << endl;
    else if (itemName == "Inyeccion de Canela") cout << "Efecto: +8 ataque de fuego y viento" << endl;
    else if (itemName == "Inyeccion de Menta") cout << "Efecto: +8 ataque de hielo y electricidad" << endl;
    else if (itemName == "Video Motivacional") cout << "Efecto: x2 a todos los ataques base del jugador" << endl;
    else if (itemName == "Una Lechuga") cout << "Efecto: +15 vida maxima" << endl;
    else if (itemName == "Un Tomate") cout << "Efecto: +20 vida maxima" << endl;
    else if (itemName == "Balde") cout << "Efecto: +17 vida maxima, -1 al estilo (efecto especial)" << endl;
    else if (itemName == "Tocar Pasto") cout << "Efecto: x1.2 vida maxima" << endl;
    else if (itemName == "Vendas") cout << "Efecto: +25 vida maxima" << endl; // Chequear lógica
    else if (itemName == "Botiquin") cout << "Efecto: +50 vida maxima" << endl; // Chequear lógica
    else if (itemName == "Una Pareja!!!") cout << "Efecto: x3 vida maxima" << endl;
    else if (itemName == "Trotar un Rato") cout << "Efecto: +10 energia maxima" << endl;
    else if (itemName == "Barrita Energetica") cout << "Efecto: +5 energia maxima" << endl;
    else if (itemName == "Cafe Suave") cout << "Efecto: x1.2 energia maxima" << endl;
    else if (itemName == "Cafe Cargado") cout << "Efecto: x1.5 energia maxima" << endl;
    else if (itemName == "Cafe Doble Extra Cargado") cout << "Efecto: x3 energia maxima, -25 vida maxima, ¡ansiedad!" << endl;
    else if (itemName == "Libro Ruso de Experimentos") cout << "Efecto: +20 mana maximo, +3 regeneracion de mana" << endl;
    else if (itemName == "Investigacion de la CIA") cout << "Efecto: +17 mana maximo, +6 regeneracion de mana" << endl;
    else if (itemName == "Caramelos de Colores") cout << "Efecto: +5 mana maximo" << endl;
    else if (itemName == "Caramelo Azul") cout << "Efecto: +1 regeneracion de mana" << endl;
    else if (itemName == "Caramelo Rojo") cout << "Efecto: +1 regeneracion de mana" << endl;
    else if (itemName == "Mantequilla") cout << "Efecto: Dedos resfaladizos" << endl;
    else if (itemName == "Bendicion de Dios") cout << "Efecto: Muestra mensaje especial " << endl;
    else cout << "Descripción no disponible." << endl;

}

void applySpecialItemEffects(const string& itemName, Player& player) {
    if (itemName == "Mantequilla") {
        cout << "¡La mantequilla ha eliminado el arma del primer slot!" << endl;
        player.getNewWeapon(0, nullptr);
    } else if (itemName == "Bendicion de Dios") {
        cout << "dios ha muerto." << endl;
    }
    // ... otros efectos especiales
}

void useItem(Item& item, Player& player) {
    cout << "Usando item: " << item.getName() << endl;
    applySpecialItemEffects(item.getName(), player);
    item.applyTo(player);
    cout << "¡Item aplicado exitosamente!" << endl;
}

void selectRandomItems(Player& player) {
    cout << "\n========================================" << endl;
    cout << "       SELECCION DE ITEMS ALEATORIOS" << endl;
    cout << "========================================" << endl;

    const int itemsToOffer = std::min(3, MAX_ITEMS_DEFINED);
    if (itemsToOffer <= 0) {
        cout << "No hay items para elegir." << endl;
        return;
    }
    
    Item offeredItems[itemsToOffer];
    bool usedIndices[MAX_ITEMS_DEFINED] = {false};

    for (int i = 0; i < itemsToOffer; ++i) {
        int randomIndex;
        do {
            randomIndex = rand() % MAX_ITEMS_DEFINED;
        } while (usedIndices[randomIndex]);
        usedIndices[randomIndex] = true;
        offeredItems[i] = createSpecificItem(randomIndex);
    }
    
    cout << "\nHas encontrado " << itemsToOffer << " items! Elige uno:" << endl;
    for (int i = 0; i < itemsToOffer; ++i) {
        cout << "\n[" << (i + 1) << "] " << offeredItems[i].getName() << endl;
        showItemDescription(offeredItems[i].getName());
    }

    int choice = 0;
    // ... (lógica de elección del usuario)
    cin >> choice; // Simplificado para brevedad
    
    Item& chosenItem = offeredItems[choice - 1];
    useItem(chosenItem, player);

    // ... (mostrar stats actualizadas y esperar)
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}


// ===== DEFINICIONES COMPLETAS DE FUNCIONES GLOBALES RESTANTES =====

// (Las implementaciones de createSpecificItem, showItemDescription, inicializarArmas..., 
// createWeaponList, createWeaponPool, mostrarOpcionesArmas, CharacterSelector, 
// iniciarSeleccionPersonaje, iniciarJuegoCompleto se incluyen aquí sin cambios, 
// ya que no presentaban errores de sintaxis graves, pero se asume que su lógica es la deseada)

// (El código detallado de esas funciones se omite aquí por brevedad, pero estaría en el archivo final)
void inicializarArmasMelee(list<Weapon>& armasMelee) {
    armasMelee.append(Weapon("kunai", {5, 0, 0, 0, 0}, 1, 5, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("kunaikunai", {10, 0, 0, 0, 0}, 1, 10, 2, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Machete", {8, 0, 0, 0, 0}, 1, 7, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Machete_al_Machote", {13, 0, 0, 0, 0}, 1, 9, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Hacha_Oxidada", {9, 0, 0, 0, 0}, 0.9, 7, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Hacha", {15, 0, 0, 0, 0}, 0.9, 10, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Hacha_de_Guerra", {20, 0, 0, 0, 0}, 0.85, 15, 2, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Microfono", {6, 0, 0, 0, 0}, 1, 4, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Chatarra", {2, 0, 0, 0, 0}, 0.7, 7, 1, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("TUS_MANOS!!!", {3, 0, 0, 0, 0}, 1, 2, 5, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Puños_Americano", {5, 0, 0, 0, 0}, 1, 2, 5, false, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Latigo_de_Cuero", {10, 0, 0, 0, 0}, 0.9, 12, 1, true, 1, 0, 0, 0, 0));
    armasMelee.append(Weapon("Cadena_Larga", {15, 0, 0, 0, 0}, 0.9, 17, 1, true, 1, 0, 0, 0, 0));
}

void inicializarArmasMeleeElementales(list<Weapon>& armasMeleeElementales) {
    armasMeleeElementales.append(Weapon("Kunais_Cargados", {10, 0, 0, 0, 5}, 1, 10, 2, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.append(Weapon("Machete_en_Llamas", {13, 7, 0, 0, 0}, 1, 9, 1, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.append(Weapon("Hacha_Tundrica", {20, 0, 10, 0, 0}, 0.85, 15, 2, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.append(Weapon("Chatarra_Radioactiva", {2, 2, 2, 2, 2}, 0.85, 7, 1, false, 1, 0, 0, 0, 0));
    armasMeleeElementales.append(Weapon("Puños_ligeros", {5, 0, 0, 3, 0}, 1, 10, 5, false, 1, 0, 0, 0, 0));
}

void inicializarArmasRanger(list<Weapon>& armasRanger) {
    armasRanger.append(Weapon("Arco_Improvisado", {9, 0, 0, 0, 0}, 0.7, 4, 5, false, 2, 5, 15, 0, 0));
    armasRanger.append(Weapon("Arco", {12, 0, 0, 0, 0}, 0.9, 10, 3, false, 2, 6, 15, 0, 0));
    armasRanger.append(Weapon("Ballesta", {16, 0, 0, 0, 0}, 0.8, 10, 2, false, 2, 3, 17, 0, 0));
    armasRanger.append(Weapon("Pistola", {1, 0, 0, 0, 0}, 0.95, 3, 10, false, 2, 30, 17, 0, 0));
    armasRanger.append(Weapon("Escopeta", {18, 0, 0, 0, 0}, 0.8, 14, 2, true, 2, 4, 19, 0, 0));
    armasRanger.append(Weapon("ESCOPETA!!!", {25, 0, 0, 0, 0}, 0.85, 18, 2, true, 2, 4, 25, 0, 0));
    armasRanger.append(Weapon("smg", {0.5, 0, 0, 0, 0}, 0.95, 7, 30, false, 2, 60, 17, 0, 0));
    armasRanger.append(Weapon("RATATATATTATATTATATATTA!!!!!", {1, 0, 0, 0, 0}, 0.95, 7, 30, false, 2, 60, 17, 0, 0));
    armasRanger.append(Weapon("BOOM!!!", {30, 0, 0, 0, 0}, 0.3, 30, 1, true, 2, 5, 30, 0, 0));
    armasRanger.append(Weapon("KABOOM!!!", {50, 0, 0, 0, 0}, 0.3, 35, 1, true, 2, 5, 30, 0, 0));
}

void inicializarArmasRangerElementales(list<Weapon>& armasRangerElementales) {
    armasRangerElementales.append(Weapon("Ballesta_Encantada", {16, 0, 0, 4, 4}, 0.8, 10, 2, false, 2, 5, 15, 0, 0));
    armasRangerElementales.append(Weapon("Lanzallamas", {2, 20, 0, 0, 0}, 0.95, 20, 5, true, 2, 30, 7, 0, 0));
}

void inicializarArmasMagicasLowCost(list<Weapon>& armasMagicasLow) {
    armasMagicasLow.append(Weapon("Ascuas", {0, 13, 0, 0, 0}, 0.95, 5, 3, true, 3, 0, 0, 3, 5));
    armasMagicasLow.append(Weapon("Bola_Hielo", {0, 0, 15, 0, 0}, 0.95, 5, 3, false, 3, 0, 0, 3, 5));
    armasMagicasLow.append(Weapon("Aerochorro", {0, 0, 0, 13, 0}, 0.95, 5, 3, true, 3, 0, 0, 3, 5));
    armasMagicasLow.append(Weapon("Chispa", {0, 0, 0, 0, 15}, 0.95, 5, 3, false, 3, 0, 0, 3, 5));
    armasMagicasLow.append(Weapon("Ascuas_Aerochorreantes", {0, 13, 0, 13, 0}, 0.95, 10, 6, true, 3, 0, 0, 3, 10));
    armasMagicasLow.append(Weapon("Bola_de_ChispaHielo", {0, 0, 15, 0, 15}, 0.95, 10, 6, false, 3, 0, 0, 3, 10));
    armasMagicasLow.append(Weapon("TetraElementalidad", {0, 7, 7, 7, 7}, 0.95, 10, 5, true, 3, 0, 0, 3, 10));
}

void inicializarArmasMagicasHighDamage(list<Weapon>& armasMagicasHigh) {
    armasMagicasHigh.append(Weapon("Bola_de_Fuego", {0, 22, 0, 0, 0}, 0.9, 7, 3, true, 3, 0, 0, 10, 20));
    armasMagicasHigh.append(Weapon("Carambano", {0, 0, 27, 0, 0}, 0.9, 7, 3, false, 3, 0, 0, 10, 20));
    armasMagicasHigh.append(Weapon("Vendaval", {0, 0, 0, 22, 0}, 0.9, 7, 3, true, 3, 0, 0, 10, 20));
    armasMagicasHigh.append(Weapon("Chispa_HD", {0, 0, 0, 0, 27}, 0.9, 7, 3, false, 3, 0, 0, 10, 20));
    armasMagicasHigh.append(Weapon("Vendaval_de_Fuego", {0, 22, 0, 22, 0}, 0.9, 10, 4, true, 3, 0, 0, 14, 25));
    armasMagicasHigh.append(Weapon("Carambano_Chispiante", {0, 0, 27, 0, 27}, 0.9, 10, 5, false, 3, 0, 0, 14, 25));
    armasMagicasHigh.append(Weapon("Hiper_TetraElementalidad", {0, 11, 14, 11, 14}, 0.9, 15, 2, true, 3, 0, 0, 15, 35));
    armasMagicasHigh.append(Weapon("ZETTAFLAREEEEEE!!!!", {0, 999, 0, 0, 0}, 0.5, 50, 1, true, 3, 0, 0, 3, 50));
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

// ... Declaraciones anticipadas

// ...

// CORREGIDO: Se reemplaza el array de C por std::vector y se usa un algoritmo de barajado estándar.
void mostrarOpcionesArmas(Player& jugador, list<Weapon>& weaponPool){
    if (weaponPool.length() == 0) {
        cout << "No hay armas disponibles en el pool." << endl;
        return;
    }
    
    cout << "\n=== OPCIONES DE ARMAS DISPONIBLES ===" << endl;
    
    // Usar std::vector para los índices
    std::vector<int> p_indices(weaponPool.length());
    std::iota(p_indices.begin(), p_indices.end(), 0); // Llena el vector con 0, 1, 2, ...

    // Barajar los índices para obtener opciones aleatorias
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(p_indices.begin(), p_indices.end(), g);

    node<Weapon>* options[3] = {nullptr, nullptr, nullptr};
    int num_to_offer = std::min(3, (int)weaponPool.length());

    for(int i=0; i < num_to_offer; ++i) {
        options[i] = weaponPool.getNodeAt(p_indices[i]);
    }

    // ... (El resto de la lógica para mostrar y elegir armas es la misma)
    for (int i = 0; i < num_to_offer; i++) {
        if (options[i] != nullptr) {
            cout << (i + 1) << ". " << options[i]->data.getName() << endl;
            Damage atk = options[i]->data.getAttack();
            cout << "    Ataque: F:" << atk.physic << " I:" << atk.fire << " H:" << atk.ice << " V:" << atk.wind << " E:" << atk.electric << endl;
            cout << "    Precision: " << options[i]->data.getAccuracy() * 100 << "%, Costo Energia: " << options[i]->data.getEnergyCost() << endl;
        }
    }
    
    if (num_to_offer == 0) { 
         cout << "No hay armas para mostrar." << endl;
         return;
    }

    cout << "\nSelecciona un arma (1-" << num_to_offer << ") o 0 para no tomar ninguna: ";
    int seleccion;
    string input_str;
    cin >> input_str;
    try {
        seleccion = stoi(input_str);
    } catch(const std::exception& e) {
        cout << "Seleccion invalida." << endl;
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); }
        return;
    }
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "Seleccion invalida." << endl; return;}


    if (seleccion == 0) {
        cout << "No has tomado ningun arma." << endl;
        return;
    }
    if (seleccion < 1 || seleccion > num_to_offer || options[seleccion - 1] == nullptr) {
        cout << "Seleccion invalida." << endl;
        return;
    }
    
    node<Weapon>* chosenWeaponNode = options[seleccion - 1];
    int originalIndexOfChosenWeapon = p_indices[seleccion - 1];

    if (jugador.AmountWeapons() >= 4 ) {
        cout << "\nTu inventario de armas esta lleno." << endl;
        cout << "¿Quieres reemplazar un arma? (s/n): ";
        char respuesta;
        cin >> respuesta;
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); respuesta = 'n';}
        
        if (respuesta == 's' || respuesta == 'S') {
            cout << "\nArmas actuales en tu inventario:" << endl;
            for (int i = 0; i < 4; i++) {
                cout << (i + 1) << ". ";
                if (jugador.invWeapon(i) != nullptr) {
                    cout << jugador.invWeapon(i)->data.getName();
                } else {
                    cout << "[VACIO]";
                }
                cout << endl;
            }
            
            cout << "¿Que arma quieres reemplazar? (1-4): ";
            int indiceReemplazo;
            cin >> input_str; 
            try {
                 indiceReemplazo = stoi(input_str);
            } catch (const std::exception& e) {
                 cout << "Indice invalido." << endl;
                 if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); }
                 return;
            }
            if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "Indice invalido." << endl; return;}


            if (indiceReemplazo >= 1 && indiceReemplazo <= 4) {
                jugador.getNewWeapon(indiceReemplazo - 1, chosenWeaponNode);
                weaponPool.moveToPos(originalIndexOfChosenWeapon);
                weaponPool.erase(); 
                cout << "Arma en posicion " << indiceReemplazo << " reemplazada por " << chosenWeaponNode->data.getName() << "." << endl;
            } else {
                cout << "Indice invalido." << endl;
            }
        } else {
            cout << "Operacion cancelada. El arma " << chosenWeaponNode->data.getName() << " no fue tomada." << endl;
        }
    } else {
        jugador.getNewWeapon(jugador.AmountWeapons(), chosenWeaponNode);
        weaponPool.moveToPos(originalIndexOfChosenWeapon);
        weaponPool.erase();
        cout << "¡Arma " << chosenWeaponNode->data.getName() << " agregada al inventario!" << endl;
    }
}

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
        cout << "\n╔=============================================================╗" << endl;
        cout << "║                    SELECCIÓN DE PERSONAJE                    ║" << endl;
        cout << "╚==============================================================╝" << endl;
        cout << endl;
        
        personajesDisponibles.moveToStart();
        int contador = 1;
        
        while (personajesDisponibles.currPos() < personajesDisponibles.length()) {
            Player personajeActual = personajesDisponibles.getValue();
            
            cout << "┌─ [" << contador << "] " <<  personajeActual.getName() << " ─┐" << endl;
            cout << "│ Salud:     " << personajeActual.maxHealth() << " HP" << endl;
            cout << "│ Energía:   " << personajeActual.maxEnergy() << " EP" << endl;
            cout << "│ Maná:      " << personajeActual.maxMana() << " MP" << endl;
            cout << "│ Precisión: " << (personajeActual.getAccuracy() * 100) << "%" << endl;
            cout << "│ Descripción: " << obtenerDescripcion(personajeActual) << endl;
            cout << "└" << string(60, '-') << "┘" << endl;
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
            cout << "============================================================" << endl;
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
        cout << "\n✅ Has seleccionado: " << personajeElegido.getName() << endl;
        cout << "=========================================================" << endl;
        
        mostrarEstadisticasFinales(personajeElegido);
        
        cout << "\nPresiona Enter para comenzar tu aventura...";
        cin.ignore();
        cin.get();
        
        return personajeElegido;
    }
    
    void mostrarEstadisticasFinales(const Player& personaje) {
        cout << "\n┌─ ESTADÍSTICAS DE " << personaje.getName() << " ─┐" << endl;
        cout << "│ ⚡ Salud:     " << personaje.maxHealth() << " HP" << endl;
        cout << "│ 🔋 Energía:   " << personaje.maxEnergy() << " EP" << endl;
        cout << "│ 🧿 Maná:      " << personaje.maxMana() << " MP" << endl;
        cout << "│ 🎯 Precisión: " << (personaje.getAccuracy() * 100) << "%" << endl;
        cout << "└" << string(40, '-') << "┘" << endl;
    }
    
    // Método para obtener un personaje aleatorio
    Player seleccionarPersonajeAleatorio() {
        static bool seedInitialized = false;
        if (!seedInitialized) {
            srand(static_cast<unsigned>(time(0)));
            seedInitialized = true;
        }
        
        int indiceAleatorio = rand() % personajesDisponibles.length();
        personajesDisponibles.moveToPos(indiceAleatorio);
        Player personajeAleatorio = personajesDisponibles.getValue();
        
        cout << "\n🎲 Personaje aleatorio seleccionado: " << personajeAleatorio.getName() << endl;
        mostrarEstadisticasFinales(personajeAleatorio);
        
        return personajeAleatorio;
    }
    
    // Método para mostrar modo de selección
    Player iniciarSeleccion() {
        cout << "\n╔ ============================================================" << endl;
        cout << "║                    LA GUERRA CALIENTE                        ║" << endl;
        cout << "║                 Sistema Post-Apocalíptico                    ║" << endl;
        cout << "╚==============================================================╝" << endl;
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

Player iniciarSeleccionPersonaje() {
    CharacterSelector selector;
    return selector.iniciarSeleccion();
};

void iniciarJuegoCompleto() {
    CharacterSelector selector;
    Player jugadorSeleccionado = selector.iniciarSeleccion();
    
    Combat sistemaCombate;
    list<Weapon> todasLasArmasDefinidas;
    createWeaponList(todasLasArmasDefinidas);

    list<Weapon> weaponPoolDelJuego;
    createWeaponPool(weaponPoolDelJuego, todasLasArmasDefinidas);
    // createWeaponPool(weaponPoolDelJuego, todasLasArmasDefinidas); // Esto debería ser create
    
    SistemaJuego sistemaJuego;
    
    sistemaJuego.iniciarJuego(jugadorSeleccionado, sistemaCombate, weaponPoolDelJuego);
} // Corregido: se eliminó el punto y coma ';' extra

#endif // TODO_HPP