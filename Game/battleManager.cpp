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

    enemySpawner(); // default for test

     // Add all party members to the battleParticipants list
    for (int i = 0; i < player->party.get_numMembers(); i++) {
        battleParticipants.push_back(player->party.members[i]);
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
    std::cout << "\n \n" << std::endl;
    std::sort(battleParticipants.begin(), battleParticipants.end(), [](Character* a, Character* b) {
        return a->get_speed() > b->get_speed(); // Sorting in descending order of speed
    });
    this->totalTurns = battleParticipants.size() -1;
    std::cout << "Turn Order:" << std::endl;
    for (Character* participants : battleParticipants){
        std::cout << participants->get_name() << std::endl;
    }
}

void BattleManager::enemySpawner(){ //for spawning mechanics later
    enemies = new Skeleton();
    EnemyList.push_back(enemies); //add nnumber of enemies to the list
    enemyAliveNum = EnemyList.size();
    enemies->set_isAlive(true);
}

int BattleManager::check_Turns(){
    for (Character* participant : battleParticipants){ //checking if it is the player's turn
        if ((participant->get_currentTurn()) && (participant->get_isAlive()) && !(participant->get_isEnemy())){
            playerTurn = true;
            break;
        } else {
            playerTurn = false;
        }
        if (participant->get_isEnemy() && !playerTurn && !hasActionTaken && ((battleParticipants.size() - EnemyList.size()) > 0)){ //placholder for enemy ai
            enemyTurn();
        } else if (battleParticipants.size() - EnemyList.size() <= 0){
            update_Status();
            break;
        }
    }

    if ((hasActionTaken)) { //action turns
        battleParticipants[turnNumber]->set_currentTurn(false); //ends char turn
        std::cout << "Ended turn of: " << battleParticipants[turnNumber]->get_name() << " Turn No: " << turnNumber << " of: " << totalTurns <<std::endl;
        turnNumber++;
        if (turnNumber > totalTurns){
            sortSpeed(); //sorts speed based on new loop turn
            turnNumber = 0;
        }
        battleParticipants[turnNumber]->set_currentTurn(true); //starts next char turn
        std::cout << "\n\nStarted turn of: " << battleParticipants[turnNumber]->get_name() <<  " Turn No: " << turnNumber << " of: " << totalTurns << "\n" << std::endl;
            
        hasActionTaken = false; //reset

        if (battleParticipants[turnNumber]->get_isEnemy()){ //goes through again
            update_Status();
        }
    }
}

void BattleManager::removeDeadChars(){
    // Remove dead enemies from battleParticipants
    battleParticipants.erase(std::remove_if(battleParticipants.begin(), battleParticipants.end(),
        [](Character* participant) { return !participant->get_isEnemy() && !participant->get_isAlive(); }), battleParticipants.end());
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

void BattleManager::enemyAttackChoice(int enemyChosen, int limbChosen){
    chosenEnemy = enemyChosen;
    if (EnemyList[chosenEnemy]->limbs[limbChosen]->getHp() > 0){
        attackHitCalc(EnemyList[chosenEnemy]->limbs[limbChosen]->getlimbHitChance(),limbChosen); //default hit chance
        hasActionTaken = true;
        update_Status();
    } else {
        std::cout << "Limb is dead! \n" << std::endl;
        update_Status();
    }
}

void BattleManager::attackHitCalc(float targetLimbChance, int limbChosen){
    float chance = ((rand() % 101)); //without modifiers 
    chance = chance/100;
    std::cout << battleParticipants[turnNumber]->get_name() << " " << turnNumber << "\n";
    if (chance < (targetLimbChance * (1 + 1-battleParticipants[turnNumber]->get_atkAccuracy()))){
        std::cout << "\nHit by: " << battleParticipants[turnNumber]->get_name() << " Got: " << chance << " Chance: " << targetLimbChance << std::endl;
        EnemyList[chosenEnemy]->limbs[limbChosen]->setHp(EnemyList[chosenEnemy]->limbs[limbChosen]->getHp() - battleParticipants[turnNumber]->get_baseDmg());
        std::cout << "Dealt: " << battleParticipants[turnNumber]->get_baseDmg() << " Limb Hp: "<<  EnemyList[chosenEnemy]->limbs[limbChosen]->getHp()  << "/" << 
        EnemyList[chosenEnemy]->limbs[limbChosen]->getMaxHp() << "\nTotal Hp: " << EnemyList[chosenEnemy]->get_Hp()<< "/" << EnemyList[chosenEnemy]->get_MaxHp() << "\n" << std::endl;
    } else {
        std::cout << "\nMiss! Got: " << chance << " Chance: " << targetLimbChance << std::endl;
    }
    int playerCharsAlive = battleParticipants.size() - EnemyList.size();
    for (Character* participant : battleParticipants){
        participant->update_limbAccuracy(); //checking all party injuries
        participant->get_isAlive(); //checking for deaths
    }
}

bool BattleManager::update_Status(){
    int playerCharsAlive = battleParticipants.size() - EnemyList.size();
    for (Character* participant : battleParticipants){
        if (!(participant->get_isAlive()) && participant->get_isEnemy()){
            std::cout << participant->get_name() << ": is dead" << std::endl;
            removeDeadEnemies();
            sortSpeed(); 
        } else if (!participant->get_isAlive() && !(participant->get_isEnemy())){
            std::cout << participant->get_name() << ": is dead" << std::endl;
            removeDeadChars();
            sortSpeed(); 
        }
        if (playerCharsAlive <= 0 || enemyAliveNum <= 0){
            battleStatus = false;
            std::cout << "end of battle" << std::endl;
            break;
        }
        participant->update_limbAccuracy();
    }
    if (battleStatus){
        check_Turns();
    }
}

void BattleManager::enemyTurn(){ //add ai difficulty types later instead of pure random
    //char choice
    int chosenChar = rand() % totalTurns;
    std::cout << "Chosen Char: " << chosenChar << std::endl;
    while (battleParticipants[chosenChar]->get_isEnemy()){
        chosenChar = rand() % totalTurns;
        std::cout << "Chosen Char: " << chosenChar << std::endl;
    }
    //limb choice
    int chosenLimb = rand () % 6; //0-5
    std::cout << "Chosen limb: " << chosenLimb << std::endl;

    //hit chance
    float chance = ((rand() % 101)); //without modifiers 
    chance = chance/100;

    if (chance < (battleParticipants[chosenChar]->limbs[chosenLimb]->getlimbHitChance()* (1 + 1-battleParticipants[turnNumber]->get_atkAccuracy()))) {
        battleParticipants[chosenChar]->set_limbHP(chosenLimb, battleParticipants[chosenChar]->get_limbHP(chosenLimb) - battleParticipants[turnNumber]->get_baseDmg());

        std::cout << battleParticipants[turnNumber]->get_name() << " Dealt: "<< battleParticipants[turnNumber]->get_baseDmg()*10 << " To: " << battleParticipants[chosenChar]->get_name() << "\n "
        << "Limb id: "<< chosenLimb << " :" << battleParticipants[chosenChar]->get_limbHP(chosenLimb) << "/" << battleParticipants[chosenChar]->limbs[chosenLimb]->getMaxHp() << "\n";
    } else {
        std::cout << "Enemy missed!" << std::endl;
    }
    hasActionTaken = true;
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

bool BattleManager::get_battleStatus(){
    return this->battleStatus;
}

void BattleManager::set_battleStatus(bool nStatus){
    this->battleStatus = nStatus;
}