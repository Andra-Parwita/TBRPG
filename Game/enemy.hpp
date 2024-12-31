#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <string>
#include "limb.hpp"
#include "character.hpp"

class Enemy : public Character
{
private:
    int enemyId;

public:
    int limbNo;
    Enemy();
    Enemy(int);
    ~Enemy();

    int get_enemyId();
    int get_limbNo();

    void set_enemyId(int);

};


#endif