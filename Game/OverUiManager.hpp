#ifndef OVERUIMANAGER_HPP
#define OVERUIMANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#include "Character/character.hpp"
#include "Character/characterSpriteLoader.hpp"
#include "Character/party.hpp"

class OverUiManager
{
private:
    Party* currentParty;
    std::vector<int> movedId; //last movement id
public:
    std::vector<characterSpriteLoader*> charSprites;
    OverUiManager();
    OverUiManager(Party*);
    ~OverUiManager();

    void moveCharUp(int);
    void moveCharDown(int);
    void moveCharLeft(int);
    void moveCharRight(int);

    void collisionCheck();
    void followingCheck();
};


#endif