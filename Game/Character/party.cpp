#include "party.hpp"

Party::Party(){
    initParty();
    this->numMembers = members.size();
}

void Party::initParty(){
    members.push_back(new Character("Syvis",1));
    members.push_back(new Character("Hikari",2));
    members.push_back(new Character("Nomu",3));
    members.push_back(new Character("Yharb",4));
}

Party::~Party(){
    for (auto character : members) {
        delete character;  // Make sure to delete each
        character = nullptr;
    }
    members.clear();  // Clear the vector to remove the now-deleted pointers
}

int Party::get_numMembers(){
    return this->numMembers;
}

bool Party::partyUpdate(){
    for (int i = 0; i < numMembers; i++){
        if (members[i]->get_isAlive() == true){ //if there is a party member alive
            return true; //party is still active
        }
    }
    return false; //all members are dead
}