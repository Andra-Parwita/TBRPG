#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <string>
#include "limb.hpp"
#include "character.hpp"

class Enemy : public Character
{
protected:
    int enemyId;
    std::string expectedFileSize;

public:
    static int totEnemiesCreated;
    int limbNo;
    Enemy();
    Enemy(int);
    ~Enemy();

    int get_enemyId();
    int get_limbNo();
    std::string get_expectedFileSize();

    void set_enemyId(int);

};


#endif