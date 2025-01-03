#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character/party.hpp"
#include <iostream>
#include <string>

class Player
{
private:
    int money;
public:
    Party party;
    Player();
    ~Player();
};


#endif