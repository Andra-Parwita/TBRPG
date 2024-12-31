 #include "enemy.hpp"
 
 Enemy::Enemy(){
    this->name = "Empty Enemy";
    this->enemyId = 0;
    this->limbNo = 6;
    this->isAlive = true;
    this->isEnemy = true;
    this->currentTurn = false;

    this->maxHp = 0;
    for (int i = 0; i < limbNo; i++){
        this->maxHp = this->maxHp + limbs[i]->getMaxHp();
    }
    this->currentHp = maxHp;
    
 }

Enemy::Enemy(int id){
    this->enemyId = id;
    this->currentTurn = false;
    this->isEnemy = true;
}

 Enemy::~Enemy(){

 }

int Enemy::get_enemyId(){
    return enemyId;
}
int Enemy::get_limbNo(){
    return limbNo;
}

void Enemy::set_enemyId(int Nid){
    this->enemyId = Nid;
}
