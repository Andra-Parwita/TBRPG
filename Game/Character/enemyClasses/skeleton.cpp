#include "skeleton.hpp"

Skeleton::Skeleton(){
    this->name = "Skeleton";
    this->expectedFileSize = "64";
    this->set_isAlive(true);
    this->baseDmg = 5;
}

Skeleton::~Skeleton(){}