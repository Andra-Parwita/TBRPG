#include "roninClass.hpp"

RoninClass::RoninClass(){
    className = "Ronin";
    speed = 40; 
    critChance = 0.3;
    baseDmg = 15; 
    atkAccuracy = 1;
    maxMp = 80;
    classUpdate();
}

RoninClass::~RoninClass(){

}

void RoninClass::classUpdate(){

}