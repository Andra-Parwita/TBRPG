#include "party.hpp"

Party::Party(){
    initParty();
    this->numMembers = 4;
}

void Party::initParty(){
    members = new Character[4];
    members[0] = Character("Syvis",1);
    members[1] = Character("Hikari",2);
    members[2] = Character("Nomu",3);
    members[3] = Character("Yharb",4);
}

Party::~Party(){}

int Party::get_numMembers(){
    return this->numMembers;
}

bool Party::partyUpdate(){
    for (int i = 0; i < numMembers; i++){
        if (members[i].get_isAlive() == true){ //if there is a party member alive
            return true; //party is still active
        }
    }
    return false; //all members are dead
}