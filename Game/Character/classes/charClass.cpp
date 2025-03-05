#include "charClass.hpp"

CharClass::CharClass(){
    className = "N/A";
    speed = 0; 
    critChance = 0.1;
    baseDmg = 5; 
    atkAccuracy = 1; 
    maxMp = 10;
    
}
CharClass::~CharClass(){
    for (auto skill : skills) {
        delete skill;  // Make sure to delete each
    }
    skills.clear();  
}

//getting
int CharClass::get_speed(){
    return this->speed;
}
std::string CharClass::get_className(){
    return this->className;
}
float CharClass::get_critChance(){
    return this->critChance;
}
int CharClass::get_baseDmg(){
    return this->baseDmg;
}
float CharClass::get_atkAccuracy(){
    return this->atkAccuracy;
}
int CharClass::get_maxMp(){
    return this->maxMp;
}

//setters
void CharClass::set_speed(int Nspd){
    this->speed = Nspd;
}
void CharClass::set_critChance(float Ncrit){
    this->critChance = Ncrit;
}
void CharClass::set_baseDmg(int Ndmg){
    this->baseDmg = Ndmg;
}
void CharClass::set_atkAccuracy(float Nacc){
    this->atkAccuracy = Nacc;
}
void CharClass::set_maxMp(int Nmp){
    this->maxMp = Nmp;
}

void CharClass::classUpdate(){

}