#include "skeleton.hpp"

Skeleton::Skeleton(){
    this->name = "Skeleton";
    this->expectedFileSize = "64";
    this->set_isAlive(true);
    this->enemyId = 1;
    this->baseDmg = 5;
}

Skeleton::~Skeleton(){}