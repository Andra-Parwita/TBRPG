#ifndef OVERUIMANAGER_HPP
#define OVERUIMANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#include "Character/character.hpp"
#include "Character/characterSpriteLoader.hpp"
#include "Character/party.hpp"
#include <deque>

class OverUiManager
{
private:
    sf::RenderWindow* window;
    Party* currentParty;
    std::vector<sf::Vector2f> previousPositions; //last movement id
    std::vector<std::deque<sf::IntRect>> textureHistory;  // Stores past textures for smooth turning
    std::vector<std::deque<sf::Vector2f>> positionHistory;
    int trailLength = 25; 

public:
    std::vector<characterSpriteLoader*> charSprites;

    OverUiManager();
    OverUiManager(Party*);
    ~OverUiManager();

    void moveCharUp(int);
    void moveCharDown(int);
    void moveCharLeft(int);
    void moveCharRight(int);

    void moveChar(int,float,float,int,sf::Vector2f);

    bool collisionCheck(sf::Vector2f, float, float,int); //checking if 
    void followingCheck(); //for following
    void updateSprites(); //for char death
}; 


#endif