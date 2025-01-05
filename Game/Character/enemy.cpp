 #include "enemy.hpp"
 
 Enemy::Enemy(){
    totEnemiesCreated++;
    this->name = "Empty Enemy";
    this->enemyId = totEnemiesCreated;
    this->limbNo = 6;
    this->isAlive = true;
    this->isEnemy = true;
    this->currentTurn = false;
    this->expectedFileSize = "";

    this->maxHp = 0;
    for (int i = 0; i < limbNo; i++){
        this->maxHp = this->maxHp + limbs[i]->getMaxHp();
    }
    this->currentHp = maxHp;
    std::cout << "Current Hp of " << name << " is " << currentHp << " with max of " << maxHp << std::endl;
    
 }

Enemy::Enemy(int id){
    totEnemiesCreated++;
    this->expectedFileSize = "";
    this->enemyId = totEnemiesCreated;
    this->currentTurn = false;
    this->isEnemy = true;
}

 Enemy::~Enemy(){
    totEnemiesCreated--;
 }

int Enemy::get_enemyId(){
    return enemyId;
}
int Enemy::get_limbNo(){
    return limbNo;
}

std::string Enemy::get_expectedFileSize(){
    return expectedFileSize;
}

void Enemy::set_enemyId(int Nid){
    this->enemyId = Nid;
}

int Enemy::totEnemiesCreated = 0;