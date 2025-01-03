#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "limb.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "characterSpriteLoader.hpp"

class Character 
{
protected:
    std::string name; //name
    int currentHp; //current total HP
    int level; //level
    int exp; //experience points

    int speed; //speed 
    int maxHp; //max total HP
    float critChance; //crit chance of char
    int baseDmg; //base dmg of char
    float atkAccuracy; //attack accuracy of char

    int classType; //class of the character
    bool isAlive;
    bool isEnemy;
    bool currentTurn;

    void charInit(int);

    //debuff checks for damaged body
    bool headEffect;
    bool headExposed;
    bool bothArmEffect;
    bool armEffect;
    bool LlegEffect;
    bool RlegEffect;

public:
    std::vector<Limb*> limbs; //limbs of character
    characterSpriteLoader* sprite;
    //getters

    int get_MaxHp();
    int get_Hp();
    int get_Level();
    int get_speed();
    int get_classType();
    int get_limbMaxHP(int);
    int get_limbHP(int);
    bool get_isAlive();
    bool get_currentTurn();
    std::string get_name();
    bool get_isEnemy();

    float get_critChance();
    int get_baseDmg();
    float get_atkAccuracy();

    //setters
    virtual void set_limbHP(int, int);
    void set_speed(int);
    void set_level(int);
    void set_experience(int);
    void set_currentTurn(bool);
    void set_isAlive(bool);

    void set_critChance(float);
    void set_baseDmg(int);
    void set_atkAccuracy(float);

    void reset_limbDebuff();


    //function
    virtual void update_limbAccuracy();

    //init
    Character();
    Character(std::string, int);
    ~Character();
};


#endif