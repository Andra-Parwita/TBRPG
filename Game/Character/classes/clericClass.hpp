#ifndef CLERICCLASS_HPP
#define CLERICCLASS_HPP

#include "charClass.hpp"
// #include "../skills/healSkill.hpp"

class ClericClass : public CharClass
{
public:
    ClericClass();
    ~ClericClass();
    
    void classUpdate();
};


#endif