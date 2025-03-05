#ifndef BATTLEMANAGER_HPP
#define BATTLEMANAGER_HPP

#include "player.hpp"
#include "Character/character.hpp"
#include <vector>
#include "Character/enemy.hpp"
#include "Character/enemyClasses/skeleton.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <time.h>
#include <algorithm>

class BattleManager
{
private:
    Player* player;

    int turnNumber; //current turn number
    int totalTurns; //max turns before reset
    bool hasActionTaken; //if the action has been taken
    bool playerTurn; //if it is player's turn

    int chosenEnemy;
    bool battleStatus; //checking if battle continues or not
    int entityNum; //number of entities
    int enemyAliveNum;
    int skillPoints; //number of skill points

    sf::Clock turnClock;

    bool canFlee;

public:
    bool attacked; //animation
    std::string attackOutcome; //animation 

    std::vector<Character*> battleParticipants;
    std::vector<Enemy*> EnemyList;
    BattleManager(Player*);
    BattleManager();
    ~BattleManager();

    void initBattle(); //set up battle
    void sortSpeed();

    void enemySpawner();
    void enemyAttackChoice(int,int);
    void flee();
    void removeDeadEnemies();
    void enemyTurn();

    void attackHitCalc(float, int);

    void removeDeadChars();

    int check_Turns();
    bool update_Status();

    void set_battleStatus(bool);
    void set_canFlee(bool);

    int get_numOfEnemies();
    int get_numOfLimbs(int);
    bool get_playerTurn();
    bool get_battleStatus();
    bool get_hasActionTaken();
    int get_activeCharId();
    bool get_canFlee();

    int get_CharSkillListSize();
    bool get_skill_usedOnEnemy(int);
    bool get_skill_limbSpecific(int);
};


#endif