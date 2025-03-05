#include "character.hpp"

Character::Character(){ //default
    this->name = "N/A";
    this->classType = 0;
    this->isAlive = false;
    this->isEnemy = false;
    this->currentTurn = false;
    this->atkAccuracy = 1;
    this->baseDmg = 5;
    charInit(0);
}

Character::Character(std::string Iname, int IclassType) : name(Iname){ //input class
    this->classType = IclassType;
    this->isAlive = true;
    this->isEnemy = false;
    this->currentTurn = false;
    this->atkAccuracy = 1;
    this->baseDmg = 5;
    sprite = new characterSpriteLoader(this->name);
    spriteChibi = new characterSpriteLoader(this->name + "Chib");
    charInit(IclassType);
}

void Character::charInit(int classType){//initalise the character
    reset_limbDebuff();
    switch (classType)
    {
    case 0: //N/A
        charClass = new CharClass;
        break;
    case 1: //knight
        charClass = new KnightClass;
        break;
    case 2: //samurai
        charClass = new RoninClass;
        break;
    case 3: //cleric
        charClass = new ClericClass;
        break;
    case 4: //mage
        charClass = new MageClass;
        break;
    default:
        charClass = new CharClass;
        break;
    }
    this->atkAccuracy = charClass->get_atkAccuracy();
    this->baseDmg = charClass->get_baseDmg();
    this->critChance = charClass->get_baseDmg();
    this->speed = charClass->get_speed();
    this->className = charClass->get_className();
    this->maxMp = charClass->get_maxMp();

    //setting limb HP
    limbs.push_back(new Limb(15, "Head")); //0
    limbs.push_back(new Limb(50, "Torso")); //1
    limbs.push_back(new Limb(20, "Right Arm")); //2
    limbs.push_back(new Limb(20, "Left Arm")); //3
    limbs.push_back(new Limb(30, "Left Leg")); //4
    limbs.push_back(new Limb(30, "Right Leg")); //5

    this->level = 1;
    this->exp = 0;
    this->maxHp = 0;
    for (int i = 0; i < limbs.size(); i++){
        this->maxHp = (this->maxHp + limbs[i]->getMaxHp());
    }
    this->currentHp = maxHp;
    this->currentMp = maxMp;
    std::cout << "Current Hp of " << name << " is " << currentHp << " with max of " << maxHp 
    << " Class type: " << className << std::endl;
}

//destructor
Character::~Character(){
    delete sprite;
    delete spriteChibi;
    for (auto limb : limbs) {
        delete limb;  // Make sure to delete each
        limb = nullptr;
    }
    limbs.clear();  // Clear the vector to remove the now-deleted pointers

}

//getting

int Character::get_MaxHp(){
    return this->maxHp;
}

int Character::get_limbHP(int i){
    if ((i >= 0) && (i < limbs.size())){
        return limbs[i]->getHp();
    }
    std::cout << "Error getting Hp id" << std::endl;
    return -1;
}

int Character::get_limbMaxHP(int i){
    if ((i >= 0) && (i < limbs.size())){
        return limbs[i]->getMaxHp();
    }
    std::cout << "Error getting Hp id" << std::endl;
    return -1;
}

int Character::get_Hp(){
    int temp = 0;
    for (int i = 0; i < limbs.size(); i++){
        temp = (temp + limbs[i]->getHp());
    }
    this->currentHp = temp;
    return this->currentHp;
}

int Character::get_classType(){
    return this->classType;
}

int Character::get_Level(){
    return this->level;
}
int Character::get_speed(){
    return this->speed;
}

std::string Character::get_name(){
    return this->name;
}

bool Character::get_isAlive(){
    if ((currentHp <= maxHp*0.4) || (limbs[0]->get_limbName() == "Head" && limbs[0]->getHp() <= 0) || (limbs[1]->get_limbName() == "Torso" && limbs[1]->getHp() <= 0)){
        isAlive = false;
    }
    return this->isAlive;
}

bool Character::get_currentTurn(){
    return this->currentTurn;
}

bool Character::get_isEnemy(){
    return this->isEnemy;
}

float Character::get_critChance(){
    return this->critChance;
}

int Character::get_baseDmg(){
    return this->baseDmg;
}

float Character::get_atkAccuracy(){
    return this->atkAccuracy;
}

int Character::get_maxMp(){
    return this->maxMp;
}

int Character::get_currentMp(){
    return this->currentMp;
}

int Character::get_NoOfSkills(){
    std::cout << name << "size is: "<< charClass->skills.size() << std::endl;
    return charClass->skills.size();
}

//setting

void Character::set_limbHP(int limbId, int newHp){
    if ((limbId >= 0) && (limbId <= 5)){
        limbs[limbId]->setHp(newHp);
    }
}

void Character::set_speed(int newSpd){
    this->speed = newSpd;
}

void Character::set_level(int newLevel){ 
    this->level = newLevel;
}

void Character::set_experience(int newExperience){
    this->exp = newExperience;
}

void Character::set_currentTurn(bool NTurn){
    this->currentTurn = NTurn;
}

void Character::set_isAlive(bool Nbool){
    this->isAlive = Nbool;
}

void Character::set_critChance(float Nchance){
    this->critChance = Nchance;
}

void Character::set_baseDmg(int NDmg){
    this->critChance = NDmg;

}

void Character::set_atkAccuracy(float NAcc){
    this->atkAccuracy = NAcc;
}

void Character::set_currentMp(int Nmp){
    this->currentMp = Nmp;
}

// hediffs
void Character::update_limbAccuracy(){
    for(Limb* currentLimb : limbs){
        if (currentLimb->get_limbName() == "Head"){
            if (((limbs[4]->getHp() <= limbs[4]->getMaxHp()/2) || (limbs[5]->getHp() <= limbs[5]->getMaxHp()/2)) && !(headEffect)){
                currentLimb->setLimbHitChance(0.4);
                std::cout << name << ": Head Weakness! \n" << std::endl;
                headEffect = true;
            } else if (!(limbs[4]->getState()) && !(limbs[5]->getState()) && !(headExposed)){
                currentLimb->setLimbHitChance(0.9);
                std::cout << name << ": Head Exposed! \n" << std::endl;
                headExposed = true;
            } else if (!(headEffect)){
                headEffect = false;
            } if (currentLimb->getHp() <= 0){
                this->isAlive = false; //kills if head is dead
                break;
            }
        } if (currentLimb->get_limbName() == "Torso"){
            if (currentLimb->getHp() <= 0){
                this->isAlive = false; //kills if torso is dead
                break;
            }
        } if ((currentLimb->get_limbName() == "Right Arm") || (currentLimb->get_limbName() == "Left Arm")){
            if ((limbs[2]->getHp() <= limbs[2]->getMaxHp()/2) && (limbs[3]->getHp() <= limbs[3]->getMaxHp()/2) && !(bothArmEffect)){
                atkAccuracy = atkAccuracy * 0.5;
                baseDmg = baseDmg - 2;
                std::cout << name << ": Both Arm Weakness! \n" << std::endl;
                bothArmEffect = true;
            } else if ((((limbs[2]->getHp() <= limbs[2]->getMaxHp()/2) && !(limbs[3]->getHp() < limbs[3]->getMaxHp()/2)) 
                        || (!(limbs[2]->getHp() <= limbs[2]->getMaxHp()/2) && (limbs[3]->getHp() < limbs[3]->getMaxHp()/2))) && !(armEffect)){

                std::cout << name << ": One Arm Weakness! \n" << std::endl;
                atkAccuracy = atkAccuracy * 0.8;
                armEffect = true;
            } 
        } if (currentLimb->get_limbName() == "Right Leg"){
            if ((currentLimb->getHp() <= currentLimb->getMaxHp()/2) && !(RlegEffect)){
                std::cout << name << ": Right Leg Weakness! \n" << std::endl;
                speed = speed - 5;
                RlegEffect = true;
            } else if (!(RlegEffect)){
                RlegEffect = false;
            }
            
        } if (currentLimb->get_limbName() == "Left Leg") {
            if ((currentLimb->getHp() <= currentLimb->getMaxHp()/2) && !(LlegEffect)){
                std::cout << name << ": Left Leg Weakness! \n" << std::endl;
                speed = speed - 5;
                LlegEffect = true;
            } else if (!(LlegEffect)){
                LlegEffect = false;
            }
        }
    }
}

void Character::reset_limbDebuff(){
    headEffect = false;
    bothArmEffect = false;
    armEffect = false;
    LlegEffect = false;
    RlegEffect = false;
    headExposed = false;
}




