#include "battleManager.hpp"

BattleManager::BattleManager(Player* Nplayer) : player(Nplayer){
    srand(time(NULL));
    initBattle();
}

BattleManager::BattleManager(){
    srand(time(NULL));
    initBattle();
}

BattleManager::~BattleManager(){

}

void BattleManager::initBattle(){ //call this to start battle
    battleStatus = true;
    activeCharId = 0;

    enemySpawner(); // default for test

     // Add all party members to the battleParticipants list
    for (int i = 0; i < player->party.get_numMembers(); i++) {
        battleParticipants.push_back(&player->party.members[i]);
    }

    // Add all enemies to the battleParticipants list
    for (int i = 0; i < 1; i++) {
        battleParticipants.push_back(&enemies[i]);
    }

    // Sort the participants based on speed (higher speed first)
    sortSpeed();
    
    // For example, printing the sorted turn order by speed:
    for (Character* participant : battleParticipants) {
        std::cout << "Name Order by Speed: " << participant->get_name() << std::endl;
    }

    this->totalTurns = battleParticipants.size() -1;
    battleParticipants[0]->set_currentTurn(true); //makes the first person turn active
    turnNumber = 0;
}

void BattleManager::sortSpeed(){
    std::sort(battleParticipants.begin(), battleParticipants.end(), [](Character* a, Character* b) {
        return a->get_speed() > b->get_speed(); // Sorting in descending order of speed
    });
}

void BattleManager::enemySpawner(){ //for spawning mechanics later
    enemies = new Enemy();
    EnemyList.push_back(enemies); //add nnumber of enemies to the list
    enemyAliveNum = EnemyList.size();
    enemies->set_isAlive(true);
}

int BattleManager::check_Turns(){
    int InId = 0;
    for (Character* participant : battleParticipants){ //checking if it is the player's turn
        InId++;
        if ((participant->get_currentTurn()) && !(participant->get_isEnemy()) && (participant->get_isAlive())){
            playerTurn = true;
            activeCharId = InId;
            break;
        } else {
            playerTurn = false;
        }
        if (participant->get_isEnemy()){ //placholder for enemy ai
            hasActionTaken = true;
            std::cout << "Enemy action Placeholder! \n" << std::endl;
            if (!(participant->get_isAlive())){
                std::cout << participant->get_name() << ": is dead" << std::endl;
                removeDeadEnemies();
            }
        }
        sortSpeed();
    }

    if ((hasActionTaken)) { //action turns
        battleParticipants[turnNumber]->set_currentTurn(false); //ends char turn
        std::cout << "Ended turn of: " << battleParticipants[turnNumber]->get_name() << " Turn No: " << turnNumber << " of: " << totalTurns <<std::endl;
        turnNumber++;
        if (turnNumber > totalTurns){
            turnNumber = 0;
        }
        battleParticipants[turnNumber]->set_currentTurn(true); //starts next char turn
        std::cout << "\nStarted turn of: " << battleParticipants[turnNumber]->get_name() <<  " Turn No: " << turnNumber << " of: " << totalTurns <<std::endl;
        if (hasActionTaken) {
            hasActionTaken = false; //reset
        }
        if (battleParticipants[turnNumber]->get_isEnemy()){ //goes through again
            update_Status();
        }
    }
}

void BattleManager::removeDeadEnemies() {
    // Remove dead enemies from EnemyList
    EnemyList.erase(std::remove_if(EnemyList.begin(), EnemyList.end(),
        [](Enemy* enemy) { return !enemy->get_isAlive(); }), EnemyList.end());
    
    // Remove dead enemies from battleParticipants
    battleParticipants.erase(std::remove_if(battleParticipants.begin(), battleParticipants.end(),
        [](Character* participant) { return participant->get_isEnemy() && !participant->get_isAlive(); }), battleParticipants.end());

    // Update the number of enemies alive
    enemyAliveNum = EnemyList.size();
}


int BattleManager::get_TotalHealth(int){

}

void BattleManager::enemyAttackChoice(int enemyChosen, int limbChosen){
    chosenEnemy = enemyChosen;
    if (EnemyList[chosenEnemy]->limbs[limbChosen]->getHp() > 0){
        attackHitCalc(EnemyList[chosenEnemy]->limbs[limbChosen]->getlimbHitChance(),limbChosen); //default hit chance
        hasActionTaken = true;
        update_Status();
    } else {
        std::cout << "Limb is dead! \n" << std::endl;
    }
}

void BattleManager::attackHitCalc(float targetLimbChance, int limbChosen){
    float chance = ((rand() % 101)); //without modifiers 
    chance = chance/100;
    if (chance < (targetLimbChance * (1 + 1-battleParticipants[activeCharId]->get_atkAccuracy()))){
        std::cout << "\nHit by: " << battleParticipants[activeCharId]->get_name() << " Got: " << chance << " Chance: " << targetLimbChance << std::endl;
        EnemyList[chosenEnemy]->limbs[limbChosen]->setHp(EnemyList[chosenEnemy]->limbs[limbChosen]->getHp() - battleParticipants[activeCharId]->get_baseDmg());
        std::cout << "Dealt: " << battleParticipants[activeCharId]->get_baseDmg() << " Limb Hp: "<<  EnemyList[chosenEnemy]->limbs[limbChosen]->getHp()  << "/" << 
        EnemyList[chosenEnemy]->limbs[limbChosen]->getMaxHp() << "\nTotal Hp: " << EnemyList[chosenEnemy]->get_Hp()<< "/" << EnemyList[chosenEnemy]->get_MaxHp() << "\n" << std::endl;
    } else {
        std::cout << "\nMiss! Got: " << chance << " Chance: " << targetLimbChance << std::endl;
    }
    for (Character* participant : battleParticipants){
        participant->update_limbAccuracy(); //checking all party injuries
        participant->get_isAlive(); //checking for deaths
    }
}

bool BattleManager::update_Status(){
    check_Turns();
    int playerCharsAlive = battleParticipants.size() - EnemyList.size();
    for (Character* participant : battleParticipants){
        if (playerCharsAlive <= 0 || enemyAliveNum <= 0){
            battleStatus = false;
            std::cout << "end of battle" << std::endl;
        }
    }
}

int BattleManager::get_numOfEnemies(){
    return this->enemyAliveNum;
}

int BattleManager::get_numOfLimbs(int enemyChosen){
    return EnemyList[enemyChosen]->get_limbNo();
}

bool BattleManager::get_playerTurn(){
    return this->playerTurn;
}