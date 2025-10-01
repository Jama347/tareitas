#ifndef TODO_HPP
#define TODO_HPP // Asegúrate que el #define esté aquí y sea el mismo que el #ifndef

#include <iostream>
#include <string>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <vector>  // Necesario para la corrección de selección de armas si se usa std::vector
#include <algorithm> // Necesario para std::random_shuffle si se usa
#include <numeric>   // Necesario para std::iota si se usa

// Asumo que "estructuras_datos 1.hpp" define Lista si es diferente de tu 'list'
// Si "Lista" es tu "list", entonces necesitarás ajustar el código de SalaNode y SistemaJuego.
// Por ahora, me centro en los errores de compilación que indicaste.
#include "estructuras_datos 1.hpp" // Si este archivo define 'Lista', está bien.

using namespace std;

//TDA de listas para armas

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
    ~list(){ // Deberías implementar la limpieza aquí si 'clear' no se llama siempre
        clear(); // Es una buena práctica limpiar en el destructor
    };

    void clear(){
       node<T>* temp;
        //curr = head; // No necesitas mover curr aquí para la lógica de clear
        node<T>* current_node = head; // Usar una variable local
        while (current_node != nullptr) {
            temp = current_node;
            current_node = current_node->sig;
            delete temp;
        }
        head = tail = curr = nullptr;
        listSize = 0;
        pos = 0;
    };

    int insert(T item){ // Inserta después de curr
        if (curr == nullptr) { // Si curr es nullptr (lista vacía o cursor fuera de rango)
            append(item); // Añade al final (o inicio si está vacía)
            // Si append actualiza curr, pos también debería actualizarse
            // Si la lista estaba vacía, curr ahora es head/tail, pos 0.
            // Si no, append añade al final, curr podría no moverse.
            // Esta lógica podría necesitar revisión dependiendo del comportamiento deseado de 'curr' y 'pos' tras 'insert'.
            // Por ahora, asumimos que append mueve 'curr' al nuevo nodo si es relevante.
            // Si insertas y curr era nullptr (por ej. fin de lista), append pone el nuevo item al final,
            // pero curr no se mueve a ese nuevo item automáticamente por append.
            // Si se espera que curr apunte al nuevo item insertado:
            // append(item); curr = tail; pos = listSize -1; return pos;
            return currPos(); // O la posición del nuevo elemento
        }

        node<T>* newNode = new node<T>{item, curr->sig};
        //curr->sig = new node<T>; // Esto crea un nodo vacío y luego lo llena, es menos eficiente
        //curr->sig->data = item;
        //curr->sig->sig = aux;
        curr->sig = newNode;

        if (curr == tail) { // Si curr es la cola, el nuevo nodo es la nueva cola
            tail = newNode;
        }
        listSize++;
        // No se actualiza 'pos' aquí, lo que podría ser inconsistente si se espera que 'pos' sea la posición de 'curr'.
        // 'insert' inserta *después* de 'curr', 'curr' no se mueve.
    return pos; // Retorna la posición de 'curr', no del elemento insertado.
};
    void append(T item){
        node<T>* newNode = new node<T>{item, nullptr};
        if (head == nullptr) {
            head = tail = curr = newNode;
            pos = 0; // Cuando se añade el primer elemento, curr está en pos 0
        } else {
            tail->sig = newNode;
            tail = newNode;
            // curr y pos no se actualizan aquí, lo cual es consistente si append siempre añade al final
            // y no mueve el cursor.
        }
        listSize++;
};
    void erase(){ // Borra el nodo en 'curr'
        if (curr == nullptr || head == nullptr) return; // No se puede borrar si curr es nulo o la lista está vacía

        node<T>* tempNodeToDelete = curr;

        if (curr == head) {
            head = head->sig;
            if (head == nullptr) { // Si la lista queda vacía
                tail = nullptr;
            }
            curr = head; // Mover curr al nuevo head (o nullptr si la lista quedó vacía)
            pos = 0;
        } else {
            // Necesitamos encontrar el nodo anterior a 'curr'
            node<T>* prevNode = head;
            //unsigned int prevPos = 0; // Para mantener 'pos' sincronizado
            while (prevNode != nullptr && prevNode->sig != curr) {
                prevNode = prevNode->sig;
                //prevPos++;
            }

            if (prevNode == nullptr) return; // No debería pasar si curr es válido y no es head

            prevNode->sig = curr->sig;
            if (curr == tail) { // Si estamos borrando la cola
                tail = prevNode;
            }
            curr = prevNode->sig; // Mover curr al nodo siguiente al borrado
            // pos se mantiene en la posición del nodo anterior si curr se movió a prev->sig
            // Si curr es ahora nullptr (porque se borró la cola), pos debería ser listSize (conceptual)
            // Si 'prev' se usó para actualizar 'pos': pos = prevPos;
            // Si 'curr' ahora es el sucesor, 'pos' no necesita cambiar ya que el sucesor está en la misma 'pos' que el borrado.
            // Sin embargo, si 'curr' era el último y se borra, 'curr' podría ser 'tail' o 'nullptr'.
            // Si curr = prevNode->sig; pos no cambia si curr no es nullptr.
            // Si curr se vuelve nullptr (ex-cola borrada), pos debería ser listSize (después de decrementar).

        }
        delete tempNodeToDelete;
        listSize--;
        if (curr == nullptr && listSize > 0) { // Si se borró la cola y la lista no está vacía
             moveToEnd(); // Mover curr a la nueva cola, y pos a listSize -1
        } else if (listSize == 0) {
            pos = 0;
        }
        // Si no, curr apunta al siguiente del borrado, y pos es la de ese nodo (que es la misma que la del borrado).
    };

    void moveToStart(){ curr = head; pos = 0;};
    void moveToEnd(){
        if (listSize == 0) {
            curr = nullptr;
            pos = 0;
        } else {
            curr = tail;
            pos = listSize - 1; // Posición es 0-indexada
        }
    };
    void next(){
        if (curr != nullptr && curr != tail) {
            curr = curr->sig;
            pos++;
        }
    };
    void prev(){
        if (curr == nullptr || curr == head) return;
        node<T>* temp = head;
        while (temp != nullptr && temp->sig != curr) {
            temp = temp->sig;
        }
        curr = temp; // temp es el anterior a curr, o nullptr si algo falló (no debería)
        if (curr != nullptr) pos--;
    };
    int length(){return listSize;};
    int currPos(){ // Retorna la posición actual del cursor, o un valor indicativo si curr es nullptr
        if (curr == nullptr && listSize > 0) return listSize; // Conceptual: cursor después del último
        if (listSize == 0) return 0; // O -1 para indicar no válido
        return pos;
    };
    void moveToPos(unsigned int posicion){
        if (posicion >= listSize && listSize > 0) { // Si la posición está fuera de rango (o es listSize para apuntar después)
             // Podrías mover curr a tail y pos a listSize-1, o curr a nullptr y pos a listSize
             if (posicion == listSize) { // Permitir mover a la posición "después del último"
                 curr = nullptr; // O curr = tail; para algunas implementaciones de 'insertar al final'
                 pos = listSize;
                 return;
             }
             return; // O manejar como error
        }
        if (listSize == 0 && posicion == 0) {
             curr = nullptr;
             pos = 0;
             return;
        }
        if (listSize == 0) return; // No se puede mover en lista vacía a menos que pos sea 0

        curr = head;
        pos = 0;
        for (unsigned int i = 0; i < posicion; i++){
            if (curr == nullptr) return; // Seguridad
            curr = curr->sig;
            pos++;
        }
    };
    T getValue(){ return curr->data;}; // Cuidado si curr es nullptr
    
    void copy(const list<T>& orig) {
        clear();
        node<T>* tempNode = orig.head;
        while (tempNode != nullptr) {
            append(tempNode->data);
            tempNode = tempNode->sig;
        }
        // Después de copiar, curr y pos de la lista actual estarán donde append los dejó
        // (probablemente head y 0 si la lista original no estaba vacía, o nullptr y 0 si estaba vacía).
        // Podrías querer restaurar el estado del cursor de la lista original si es necesario,
        // pero la copia de datos es lo principal aquí.
        // Si orig.curr != nullptr, podrías hacer moveToPos(orig.pos) si esa es la intención.
    }

    // CORRECCIÓN: Eliminada la línea "template<typename T>" de aquí
    node<T>* getNodeAt(int p) { // 'pos' como nombre de parámetro sombrea al miembro 'pos'
        if (p < 0 || static_cast<unsigned int>(p) >= listSize) return nullptr;
        node<T>* temp = head;
        for (int i = 0; i < p; i++) {
            if (temp == nullptr) return nullptr; // Seguridad adicional
            temp = temp->sig;
        }
        return temp;
    }

    void randomize() {
        static bool seed_init = false; // Renombrada para evitar conflicto con miembro 'seed' de Weapon
        if (!seed_init) {
            srand(static_cast<unsigned>(time(0)));
            seed_init = true;
        }
        
        if (listSize < 2) return;

        // srand(time(nullptr)); // No es necesario llamar a srand repetidamente si ya se inicializó una vez.

        for (int i = listSize - 1; i > 0; i--) {
            int j = rand() % (i + 1);

            node<T>* nodeI = getNodeAt(i);
            node<T>* nodeJ = getNodeAt(j);

            if (nodeI && nodeJ) {
                T tempData = nodeI->data;
                nodeI->data = nodeJ->data;
                nodeJ->data = tempData;
            }
        }
    }
};

struct Damage {
    float physic, fire, ice, wind, electric;

    Damage() : physic(0), fire(0), ice(0), wind(0), electric(0) {}; // Constructor por defecto
    Damage(float p, float f, float i, float w, float e)
        : physic(p), fire(f), ice(i), wind(w), electric(e) {};

    Damage(float a) // Constructor para daño uniforme
        : physic(a), fire(a), ice(a), wind(a), electric(a) {};
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
    Weapon() : accuracy(0.0f), attack(), energyCost(0), type(0), burst(1), multipleShot(false),
               baseAmmo(0), ammo(0), reloadCost(0), manaCost(0), physicMagic(0.0f) {} // Constructor por defecto

    // CORRECCIÓN: Reordenados los inicializadores y añadido 'ammo'
    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot, int t, int amun, int rCost, float pDamage, int mCost)
        : name(n), accuracy(acc), attack(atk), energyCost(eCost), type(t), burst(bur), multipleShot(mShot),
          baseAmmo(t == 2 ? amun : 0), ammo(t == 2 ? amun : 0), reloadCost(t == 2 ? rCost : 0),
          manaCost(t == 3 ? mCost : 0), physicMagic(t == 3 ? pDamage : 0.0f) {}

    // CORRECCIÓN: Reordenados los inicializadores y añadido el resto para consistencia
    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot) // Melee (type 1 implícito)
        : name(n), accuracy(acc), attack(atk), energyCost(eCost), type(1), burst(bur), multipleShot(mShot),
          baseAmmo(0), ammo(0), reloadCost(0), manaCost(0), physicMagic(0.0f) {}

    // CORRECCIÓN: Reordenados los inicializadores y añadido 'ammo' y el resto
    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot, int amun, int rCost) // Ranger (type 2 implícito)
        : name(n), accuracy(acc), attack(atk), energyCost(eCost), type(2), burst(bur), multipleShot(mShot),
          baseAmmo(amun), ammo(amun), reloadCost(rCost), manaCost(0), physicMagic(0.0f) {}

    // CORRECCIÓN: Reordenados los inicializadores y añadido el resto
    Weapon(string n, Damage atk, float acc, int eCost, int bur, bool mShot, float pDamage, int mCost) // Magic (type 3 implícito)
        : name(n), accuracy(acc), attack(atk), energyCost(eCost), type(3), burst(bur), multipleShot(mShot),
          baseAmmo(0), ammo(0), reloadCost(0), manaCost(mCost), physicMagic(pDamage) {}


    string getName() {return name;}
    int getType(){return type;}
    int getBurst(){return burst;}
    Damage getAttack() { return attack; }
    float getAccuracy(){ return accuracy;}
    bool isMultipleShot() { return multipleShot; }
    int getEnergyCost() { return energyCost; } // Getter útil


    // En canAttack, considera pasar Player& para modificar su energía/maná directamente
    // o devolver los costos para que la lógica externa los maneje.
    // Por ahora, se modifica por referencia implícita si energy y mana son referencias.
    // Pero son pasados por valor, así que los cambios a energy/mana no se reflejan fuera.
    // Cambiando a referencias: bool canAttack(int& energy, int& mana)
    bool canAttack(int& playerEnergy, int& playerMana){ // Cambiado a referencias
        if (playerEnergy < energyCost){
            cout << "Not enough energy. ";
            return false;
        }
        if (type == 2 && ammo == 0){
            if (playerEnergy < reloadCost + energyCost){ // Considerar si el ataque aún consume energía si se recarga
                cout << "Not enough energy to reload or attack. ";
                return false;
            }
            // Si se recarga, ¿se ataca en el mismo turno?
            // La lógica actual sugiere que recargar es una acción que impide atacar.
            // Si es así, canAttack debería fallar si necesita recargar.
            cout << "Weapon needs to reload. "; // Mensaje más claro
             // Esto podría ser una acción separada "reloadWeapon"
            // Si recargar es parte del intento de ataque:
            // playerEnergy -= reloadCost;
            // ammo = baseAmmo;
            // cout << "Weapon reloaded." << endl;
            // Pero entonces el chequeo de energía para el ataque debe ser después.
            // Asumamos que recargar es una acción que impide este ataque:
            return false; // Indica que no se puede atacar, se necesita recargar.
        }
        if (type == 3 && playerMana < manaCost){
            cout << "Not enough Battery (Mana). ";
            return false;
        }

        // Si todos los chequeos pasan, descontar recursos
        playerEnergy -= energyCost;

        if (type == 2) {
            ammo--;
        }
        if (type == 3) {
            playerMana -= manaCost;
        }
        return true;
    }
    // Función de recarga separada sería más limpia:
    bool reload(int& playerEnergy) {
        if (type == 2) {
            if (playerEnergy >= reloadCost) {
                playerEnergy -= reloadCost;
                ammo = baseAmmo;
                cout << "Weapon reloaded." << endl;
                return true;
            } else {
                cout << "Not enough energy to reload." << endl;
                return false;
            }
        }
        return false; // No es un arma de tipo 2 o no necesita recarga
    }
};

class Enemy {
private:
    string name;
    float baseHealth;
    float health;
    float Attack; // Stat de ataque del enemigo
    Damage Defence;
    float accuracy;

public:
    Enemy() : name("Unknown"), baseHealth(10), health(10), Attack(5), Defence(), accuracy(0.75f) {};
    Enemy(string n, float hp, float atk, Damage def, float acc) : name(n), baseHealth(hp), health(hp), Attack(atk), Defence(def), accuracy(acc) {};

    string getName() const {return name;} // const getter
    float& getHealth(){return health;} // Devuelve referencia para modificar
    float getBaseHealth() const {return baseHealth;} // const getter
    float getAttack() const {return Attack;} // const getter
    Damage getDefence() const {return Defence;} // const getter
    float getAccuracy() const { return accuracy;} // const getter

    void receiveDamage(float dmg) {
        health -= dmg;
        if (health < 0)
            health = 0;
    }
    // Método para restaurar vida, útil para reinicios de combate
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

    node<Weapon>* Winventory[4]; // Inventario de 4 armas
    int invLength; // Número actual de armas en el inventario

    Damage attack; // Ataque base del jugador (ej. desarmado o bonus)

public:
    Player() : name("Player"), baseHealth(100), health(100), baseEnergy(50), energy(50),
               baseMana(30), mana(30), manaGain(5), accuracy(0.9f), invLength(0), attack() {
        for(int i=0; i<4; ++i) Winventory[i] = nullptr; // Inicializar inventario
    };
    Player(string n, float hp, int stamina, int battery, int charge, float accur)
        : name(n), baseHealth(hp), health(hp), baseEnergy(stamina), energy(stamina),
          baseMana(battery), mana(battery), manaGain(charge), accuracy(accur), invLength(0), attack() {
        for(int i=0; i<4; ++i) Winventory[i] = nullptr; // Inicializar inventario
    };
    ~Player() {
       
    };

    string getName(Player) const { return name; }
    float getHealth() const {return health;}
    int getEnergy() const {return energy;}
    int getMana() const {return mana;}

    float maxHealth() const {return baseHealth;}
    int maxEnergy() const {return baseEnergy;}
    int maxMana() const {return baseMana;}

    Damage getAttack() const { return attack; }
    float getAccuracy() const { return accuracy;}

    node<Weapon>* invWeapon(int i) const { // const getter
        if (i >= 0 && i < 4)
            return Winventory[i];
        return nullptr;
    }
    int AmountWeapons() const {return invLength;}

    void getNewWeapon(int slot, node<Weapon>* weaponNode){ // El nodo viene de un pool de armas
        if (slot >= 0 && slot < 4){
            // Si ya había un arma en ese slot y el nodo era 'owned', habría que borrarlo primero.
            // Asumiendo que los nodos no son 'owned' por el Player directamente, solo se reemplaza el puntero.
            if (Winventory[slot] == nullptr && weaponNode != nullptr) invLength++;
            else if (Winventory[slot] != nullptr && weaponNode == nullptr) invLength--;
            
            Winventory[slot] = weaponNode;
        }
    }

    void startBattle(){health = baseHealth; energy = baseEnergy; mana = baseMana;}
    void playerTurn(){
        energy = baseEnergy; // Restaura toda la energía al inicio del turno
        mana += manaGain;    // Gana mana
        if(mana > baseMana) mana = baseMana; // No exceder el máximo
    }

    void receiveDamage(float dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    void healthMod (float sum, float mult){
        baseHealth += sum;
        baseHealth *= mult;
        if (health > baseHealth) health = baseHealth; // Ajustar vida actual si supera el nuevo máximo
        if (baseHealth < 0) baseHealth = 0; // Evitar vida base negativa
    }

    void attackMod (Damage sum, Damage mult){
        attack.physic = (attack.physic + sum.physic) * mult.physic;
        attack.fire = (attack.fire + sum.fire) * mult.fire;
        attack.ice = (attack.ice + sum.ice) * mult.ice;
        attack.wind = (attack.wind + sum.wind) * mult.wind;
        attack.electric = (attack.electric + sum.electric) * mult.electric;
    }

    void effect(int code, int sum, float mult) {
        switch (code) {
            case 0: baseEnergy += sum; baseEnergy = static_cast<int>(baseEnergy * mult); if(baseEnergy < 0) baseEnergy = 0; break;
            case 1: baseMana += sum; baseMana = static_cast<int>(baseMana * mult); if(baseMana < 0) baseMana = 0; break;
            case 2: manaGain += sum; manaGain = static_cast<int>(manaGain * mult); if(manaGain < 0) manaGain = 0; break;
            case 3: accuracy *= mult; if(accuracy < 0) accuracy = 0; if(accuracy > 1) accuracy = 1; break; // Asumiendo que accuracy es [0,1]
        }
    }
};

const int MAX_GEN_EFFECTS = 4;

class Item {
private:
    string name;
    bool hasHealthMod;
    float hSum, hMult;
    bool hasAttackMod;
    Damage aSum, aMult;

    int fxCode[MAX_GEN_EFFECTS];
    int fxSum[MAX_GEN_EFFECTS];
    float fxMult[MAX_GEN_EFFECTS];
    int fxCount;

public:
    Item() : name(""), hasHealthMod(false), hSum(0), hMult(1) {
    }
    Item(string name) : name(name), hasHealthMod(false), hSum(0), hMult(1),
                       hasAttackMod(false), aSum(), aMult(1.0f), fxCount(0) { // Inicializar aMult a 1.0f
        for(int i=0; i<MAX_GEN_EFFECTS; ++i) {
            fxCode[i] = -1; // O un valor inválido
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
        if (fxCount < MAX_GEN_EFFECTS) {
            fxCode[fxCount] = code;
            fxSum[fxCount] = sum;
            fxMult[fxCount] = mult;
            fxCount++;
        }
    }

    void applyTo(Player& p) { // Asumo que p es el jugador al que se aplica el item
        if (hasHealthMod)
            p.healthMod(hSum, hMult);
        if (hasAttackMod)
            p.attackMod(aSum, aMult);
        for (int i = 0; i < fxCount; i++)
            p.effect(fxCode[i], fxSum[i], fxMult[i]);
    }
};


// CORRECCIÓN: Declaraciones anticipadas para funciones usadas por Combat y SalaNode
void selectRandomItems(Player& player);
void mostrarOpcionesArmas(Player& jugador, list<Weapon>& weaponPool);
// Si createSpecificItem, etc. son solo helpers de selectRandomItems,
// y selectRandomItems se define antes de Combat, no necesitan forward declaration global.
// Pero si son globales, entonces sí. Por seguridad, se pueden declarar aquí.
Item createSpecificItem(int index); 
void useItem(Item& item, Player& player, const string& itemName);
void showItemDescription(const string& itemName);

#endif //TODO_HPP