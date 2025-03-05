#ifndef CHARCLASS_HPP
#define CHARCLASS_HPP

#include "../skills/skill.hpp"
#include <string>
#include <vector>
#include <iostream>

class CharClass 
{
protected:
    std::string className;
    int speed; //speed 
    float critChance; //crit chance of char
    int baseDmg; //base dmg of char
    float atkAccuracy; //attack accuracy of char
    int maxMp; //max Mp;

public:
    CharClass();
    virtual ~CharClass();
    std::vector<Skill*> skills; //list of available skills

    //getting
    int get_speed();
    std::string get_className();
    float get_critChance();
    int get_baseDmg();
    float get_atkAccuracy();
    int get_maxMp();

    //setters
    void set_speed(int);
    void set_critChance(float);
    void set_baseDmg(int);
    void set_atkAccuracy(float);
    void set_maxMp(int);

    virtual void classUpdate(); //skillchecks, level updates
};

#endif
