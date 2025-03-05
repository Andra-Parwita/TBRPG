#include "skill.hpp"

Skill::Skill() : skillDmg(0), cost(0), isAtk(false), usedOnEnemy(false) {}

Skill::~Skill() {}

void Skill::skillAbility() {
    // Default implementation (can be overridden)
}

int Skill::get_skillDmg(){
    return this->skillDmg;
}
int Skill::get_cost(){
    return this->cost;
}
bool Skill::get_isAtk(){
    return this->isAtk;
}
bool Skill::get_usedOnEnemy(){
    return this->usedOnEnemy;
}
bool Skill::get_limbSpecific(){
    return this->limbSpecific;
}
float Skill::get_skillAcc(){
    return this->skillAcc;
}