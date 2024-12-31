#ifndef BATTLEMANAGER_HPP
#define BATTLEMANAGER_HPP

#include "player.hpp"
#include "character.hpp"
#include <vector>
#include "enemy.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>

class BattleManager
{
private:
    Player* player;
    Enemy* enemies;

    std::vector<Enemy*> EnemyList;

    int turnNumber; //current turn number
    int totalTurns; //max turns before reset
    bool hasActionTaken; //if the action has been taken
    bool playerTurn; //if it is player's turn
    int activeCharId;
    std::vector<Character*> battleParticipants;

    int chosenEnemy;
    bool battleStatus; //checking if battle continues or not
    int entityNum; //number of entities
    int enemyAliveNum;
    int skillPoints; //number of skill points

public:
    BattleManager(Player*);
    BattleManager();
    ~BattleManager();

    void initBattle(); //set up battle
    void sortSpeed();

    void enemySpawner();
    void enemyAttackChoice(int,int);
    void removeDeadEnemies();
    void attackHitCalc(float, int);


    int check_Turns();
    int get_TotalHealth(int);
    bool update_Status();
    int get_numOfEnemies();
    int get_numOfLimbs(int);
    bool get_playerTurn();
};


#endif