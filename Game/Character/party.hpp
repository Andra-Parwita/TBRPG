#ifndef PARTY_HPP
#define PARTY_HPP

#include "character.hpp"
#include <iostream>
#include <string>

class Party
{
private:
    int numMembers;
    void initParty();
    bool partyStatus;
public:
    std::vector<Character*> members;
    Party();
    ~Party();

    bool partyUpdate(); //checks status of party
    int get_numMembers();
};


#endif