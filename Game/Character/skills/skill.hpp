#ifndef SKILL_HPP
#define SKILL_HPP

#include <string>

class Skill 
{
protected:
    std::string name;
    std::string skillDesc;

    int skillDmg; //base values for healing, dmg etc
    int cost;
    bool isAtk;
    bool usedOnEnemy; //false = used on team
    bool limbSpecific;
    float skillAcc; //skill accuracy

public:
    Skill();
    virtual ~Skill(); 
    virtual void skillAbility();  //any special features of the skill;

    int get_skillDmg();
    int get_cost();
    bool get_isAtk();
    bool get_usedOnEnemy();
    float get_skillAcc();
    bool get_limbSpecific();
};

#endif
