#include "battleManager.hpp"

BattleManager::BattleManager(Player* Nplayer) : player(Nplayer){
    srand(static_cast<unsigned>(time(NULL)));
    canFlee = true;
    if (!player) {
        std::cerr << "Error: Player is null!" << std::endl;
        return;
    }
    initBattle();
    attackOutcome = "N/A";
}

BattleManager::BattleManager(){
    canFlee = true;
    srand(static_cast<unsigned>(time(NULL)));
    initBattle();
    attackOutcome = "N/A";
}

BattleManager::~BattleManager(){
    for (auto* enemy : EnemyList) {
        delete enemy;
    }
    EnemyList.clear();
    std::cout << "Enemy Cleared" << std::endl;
    battleParticipants.clear();  // Clear the vector
}

void BattleManager::initBattle(){ //call this to start battle
    if (!player) {
        std::cerr << "Error: Player is null!" << std::endl;
        return;
    }

    battleStatus = true;
    enemySpawner(); // default for test

     // Add all party members to the battleParticipants list
    for (int i = 0; i < player->party.get_numMembers(); i++) {
        auto* member = player->party.members[i];
        if (member) {
            battleParticipants.push_back(member);
        }
    }

    // Add all enemies to the battleParticipants list
    for (auto* enemy : EnemyList) {
        if (enemy) {
            battleParticipants.push_back(enemy);
        }
    }

    // Sort the participants based on speed (higher speed first)
    sortSpeed();
    
    // For example, printing the sorted turn order by speed:
    for (auto* participant : battleParticipants) {
        if (participant){
            std::cout << "Name Order by Speed: " << participant->get_name() << std::endl;
        }
    }

    this->totalTurns = static_cast<int>(battleParticipants.size()) -1;
    if (!battleParticipants.empty()) { //set first person active if not empty
        battleParticipants[0]->set_currentTurn(true);
    }
    turnNumber = 0;
}

void BattleManager::sortSpeed(){
    std::cout << "\n \n" << std::endl;
    std::sort(battleParticipants.begin(), battleParticipants.end(), [](Character* a, Character* b) {
        return a->get_speed() > b->get_speed(); // Sorting in descending order of speed
    });

    this->totalTurns = battleParticipants.size() -1;

    std::cout << "Turn Order:" << std::endl;
    for (auto* participants : battleParticipants){
        if (participants) {
            std::cout << participants->get_name() << std::endl;
        }
    }
}

void BattleManager::enemySpawner(){ //for spawning mechanics later
    for (int i = 0; i < 2; i++) {
        auto* newEnemy = new Enemy(); 
        if (newEnemy) {
            EnemyList.push_back(newEnemy);
            newEnemy->set_isAlive(true);
        }
    }
    enemyAliveNum = static_cast<int>(EnemyList.size());
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
    battleParticipants.erase(std::remove_if(battleParticipants.begin(), battleParticipants.end(),
    [](Character* participant) { return participant && !participant->get_isAlive(); }),battleParticipants.end());
}

void BattleManager::removeDeadEnemies() {
    EnemyList.erase(
        std::remove_if(EnemyList.begin(), EnemyList.end(),
                       [](Enemy* enemy) { return enemy && !enemy->get_isAlive(); }),
        EnemyList.end());

    // Update enemy count
    enemyAliveNum = static_cast<int>(EnemyList.size());

    // Remove dead enemies from battleParticipants
    battleParticipants.erase(
        std::remove_if(battleParticipants.begin(), battleParticipants.end(),
                       [](Character* participant) { return participant && participant->get_isEnemy() && !participant->get_isAlive(); }),
        battleParticipants.end());
}

//player options

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

void BattleManager::flee(){
    if (canFlee){
        battleStatus = false;
        EnemyList.clear();
        battleParticipants.clear();
    } else {
        update_Status();
    }
}


//internal

void BattleManager::attackHitCalc(float targetLimbChance, int limbChosen){
    float chance = ((rand() % 101)); //without modifiers 
    chance = chance/100;
    std::cout << battleParticipants[turnNumber]->get_name() << " " << turnNumber << "\n";
    if (chance < (targetLimbChance * (1 + 1-battleParticipants[turnNumber]->get_atkAccuracy()))){
        std::cout << "\nHit by: " << battleParticipants[turnNumber]->get_name() << " Got: " << chance << " Chance: " << targetLimbChance << std::endl;

        EnemyList[chosenEnemy]->limbs[limbChosen]->setHp(EnemyList[chosenEnemy]->limbs[limbChosen]->getHp() - battleParticipants[turnNumber]->get_baseDmg()); 

        std::cout << "Dealt: " << battleParticipants[turnNumber]->get_baseDmg() << " Limb Hp: "<<  EnemyList[chosenEnemy]->limbs[limbChosen]->getHp()  << "/" << 

        EnemyList[chosenEnemy]->limbs[limbChosen]->getMaxHp() << "\nTotal Hp: " << EnemyList[chosenEnemy]->get_Hp()<< "/" << EnemyList[chosenEnemy]->get_MaxHp() << "\n" << std::endl;
        attackOutcome = std::to_string(battleParticipants[turnNumber]->get_baseDmg()); //animation
    } else {
        attackOutcome = "Miss"; //displays for animation
        std::cout << "\nMiss! Got: " << chance << " Chance: " << targetLimbChance << std::endl;
    }
    int playerCharsAlive = battleParticipants.size() - EnemyList.size();
    for (Character* participant : battleParticipants){
        participant->update_limbAccuracy(); //checking all party injuries
        participant->get_isAlive(); //checking for deaths
    }
    attacked = true; // for animation
}

bool BattleManager::update_Status(){
    removeDeadEnemies();
    removeDeadChars();

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
            EnemyList.clear();
            battleParticipants.clear();
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

        std::cout << battleParticipants[turnNumber]->get_name() << " Dealt: "<< battleParticipants[turnNumber]->get_baseDmg() << " To: " << battleParticipants[chosenChar]->get_name() << "\n "
        << "Limb id: "<< chosenLimb << " :" << battleParticipants[chosenChar]->get_limbHP(chosenLimb) << "/" << battleParticipants[chosenChar]->limbs[chosenLimb]->getMaxHp() << "\n";
        attackOutcome = std::to_string(battleParticipants[turnNumber]->get_baseDmg());
    } else {
        attackOutcome = "Miss";
        std::cout << "Enemy missed!" << std::endl;
    }
    attacked = true;
    hasActionTaken = true;
}


void BattleManager::set_battleStatus(bool nStatus){
    this->battleStatus = nStatus;
}

void BattleManager::set_canFlee(bool nFLee){
    this->canFlee = nFLee;
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

bool BattleManager::get_hasActionTaken(){
    return this->hasActionTaken;
}

bool BattleManager::get_canFlee(){
    return this->canFlee;
}

int BattleManager::get_CharSkillListSize(){
    std::cout << battleParticipants[turnNumber]->get_name() << std::endl;
    return battleParticipants[turnNumber]->get_NoOfSkills();
}

bool BattleManager::get_skill_usedOnEnemy(int){}
bool BattleManager::get_skill_limbSpecific(int){}