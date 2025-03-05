#include "fireballSkill.hpp"

FireballSkill::FireballSkill(){
    skillDmg = 20;
    cost = 10;
    isAtk = true;
    usedOnEnemy = true;

    name = "Fireball";
    skillDesc = "boom";

    limbSpecific = false;
    skillAcc = 0.8;
}

FireballSkill::~FireballSkill(){}

void FireballSkill::skillAbility(){}