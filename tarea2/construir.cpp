#include <iostream>
#include <cstdlib>
#include "estructuras_datos.hpp"
#include <ctime>
#include <string>
using namespace std;

struct Damage {
    float physic;
    float fire;
    float ice;
    float wind;
    float electric;
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
    Weapon(
        string n,
        Damage atk,
        float acc,
        int eCost,
        int bur,
        bool mShot,
        int t,
        int amun,
        int rCost,
        float pDamage,
        int mCost):
        name(n), attack(atk), accuracy(acc), energyCost(eCost), burst(bur), multipleShot(mShot), type(t), baseAmmo(amun), reloadCost(rCost), physicMagic(pDamage), manaCost(mCost) {}
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
    Enemy(
        string n,
        float hp,
        float atk,
        Damage def,
        float acc) : name(n), baseHealth(hp), health(hp), Attack(atk), Defence(def), accuracy(acc) {};
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

    Weapon* Winventory[4];
    int invLenght;

    Damage Attack;

public:
    Player() {};
    Player(
        string n,
        float hp,
        int stamina,
        int battery,
        int charge,
        float accur): name(n), baseHealth(hp), health(hp), baseEnergy(stamina), energy(stamina), baseMana(battery), mana(battery), manaGain(charge), accuracy(accur) {};
};