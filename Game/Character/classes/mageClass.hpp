#ifndef MAGECLASS_HPP
#define MAGECLASS_HPP

#include "charClass.hpp"
#include "../skills/fireballSkill.hpp"
#include <iostream>

class MageClass : public CharClass
{
public:
    MageClass();
    ~MageClass();
    
    void classUpdate();
};


#endif