#include "limb.hpp"

Limb::Limb(){
    this->limbName = "Default Limb";
    this->limbHitChance = 0.8;
    this->hp = 10;
    this->maxHp = 10;
    this->state = true;
};
Limb::Limb(int IHP) : hp(IHP){
    this->limbName = "Default Limb (cHP)";
    this->limbHitChance = 0.8;
    this->state = true;
    this->maxHp = IHP;
}

Limb::Limb(int IHP, std::string newName) : hp(IHP), maxHp(IHP), limbName(newName){
    this->state = true;

    limbType tempLimbId = hashit(newName); 
    switch (tempLimbId)
    {
    case eHead:
        this->limbHitChance = 0.2;
        break;
    case eTorso:
        this->limbHitChance = 0.9;
        break;
    case eRArm:
        this->limbHitChance = 0.7;
        break;
    case eLArm:
        this->limbHitChance = 0.7;
        break;
    case eLLeg:
        this->limbHitChance = 0.8;
        break;
    case eRLeg:
        this->limbHitChance = 0.8;
        break;
    default:
        this->limbHitChance = 0.8;
        break;
    }
}

Limb::Limb(int IHP, std::string newName, float hit) : hp(IHP), limbName(newName), limbHitChance(hit){
    this->state = true;
}
Limb::~Limb(){}

limbType Limb::hashit(std::string const& inString){
    if(inString == "Head") {return eHead;}
    if(inString == "Torso") {return eTorso;}
    if(inString == "Right Arm") {return eRArm;}
    if(inString == "Left Arm") {return eLArm;}
    if(inString == "Left Leg") {return eLLeg;}
    if(inString == "Right Leg") {return eRLeg;}
}

bool Limb::getState(){
    return state;
}

int Limb::getHp(){
    return hp;
}

int Limb::getMaxHp(){
    return maxHp;
}

std::string Limb::get_limbName(){
    return this->limbName;
}

float Limb::getlimbHitChance(){
    return limbHitChance;
}

void Limb::setHp(int newHp){
    this->hp = newHp;
    if (hp <= 0){
        this->state = false;
    }
}

void Limb::setMaxHp(int newHp){
    this->maxHp = newHp;
}

void Limb::set_limbName(std::string newName){
    this->limbName = newName;
}

void Limb::setLimbHitChance(float newHit){
    this->limbHitChance = newHit;
}