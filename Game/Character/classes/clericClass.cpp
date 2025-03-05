#include "clericClass.hpp"

ClericClass::ClericClass(){
    className = "Cleric";
    speed = 30; 
    critChance = 0.1;
    baseDmg = 10; 
    atkAccuracy = 1;
    maxMp = 100;
    classUpdate();
}

ClericClass::~ClericClass(){

}

void ClericClass::classUpdate(){

}