#include "mageClass.hpp"

MageClass::MageClass(){
    className = "Mage";
    speed = 20; 
    critChance = 0.05;
    baseDmg = 5; 
    atkAccuracy = 1;
    maxMp = 120;
    this->classUpdate();
}

MageClass::~MageClass(){

}

void MageClass::classUpdate(){
    skills.push_back(new FireballSkill);
}