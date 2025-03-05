#include "knightClass.hpp"

KnightClass::KnightClass(){
    className = "Knight";
    speed = 10; 
    critChance = 0.2;
    baseDmg = 10; 
    atkAccuracy = 1;
    maxMp = 50;
    classUpdate();
}

KnightClass::~KnightClass(){

}

void KnightClass::classUpdate(){

}