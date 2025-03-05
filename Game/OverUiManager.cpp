#include "OverUiManager.hpp"

OverUiManager::OverUiManager(){
}

OverUiManager::OverUiManager(Party* party){
    this->currentParty = party;
    for (int i = 0; i < currentParty->get_numMembers(); i++){
        charSprites.push_back(currentParty->members[i]->spriteChibi);
        charSprites[i]->characterSprite.setPosition(sf::Vector2f(i*50.f,50.f));
        charSprites[i]->characterSprite.setTextureRect(sf::Rect<int>({0,0},{32,32}));
        charSprites[i]->characterSprite.setScale(3,3);
        movedId[i] = 0;
    }
}

OverUiManager::~OverUiManager(){
}


void OverUiManager::moveCharUp(int id){
    if (id < currentParty->get_numMembers() || id >= 0){
        charSprites[id]->characterSprite.move(0,-5.f);
        charSprites[id]->characterSprite.setTextureRect(sf::Rect<int>({0,0},{32,32})); //testing rotation
        movedId[id] = 1;
    }
}

void OverUiManager::moveCharDown(int id){
    if (id < currentParty->get_numMembers() || id >= 0){
        charSprites[id]->characterSprite.move(0,5.f);
        charSprites[id]->characterSprite.setTextureRect(sf::Rect<int>({0,32},{32,32})); //testing rotation
        movedId[id] = 2;
    }
}

void OverUiManager::moveCharLeft(int id){
    if (id < currentParty->get_numMembers() || id >= 0){
        charSprites[id]->characterSprite.move(-5.f,0);
        charSprites[id]->characterSprite.setTextureRect(sf::Rect<int>({32,32},{32,32})); //testing rotation
        movedId[id] = 3;
    }
}

void OverUiManager::moveCharRight(int id){
    if (id < currentParty->get_numMembers() || id >= 0){
        charSprites[id]->characterSprite.move(5.f,0);
        charSprites[id]->characterSprite.setTextureRect(sf::Rect<int>({32,0},{32,32})); //testing rotation
        movedId[id] = 4;
    }
}


void OverUiManager::followingCheck(){
    if (currentParty->get_numMembers() > 1){
        for (int i = 1; i < currentParty->get_numMembers(); i++){
            // if (party member is alive){}
            switch (movedId[i])
            {
            case 1:
                moveCharUp(i);
                break;
            case 2:
                moveCharDown(i);
                break;
            case 3:
                moveCharLeft(i);
                break;
            case 4:
                moveCharRight(i);
                break;
            default:
                break;
            }
            movedId[i] = movedId[i-1];
        }
    }
}