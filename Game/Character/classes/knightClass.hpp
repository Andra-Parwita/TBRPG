#ifndef KNIGHTCLASS_HPP
#define KNIGHTCLASS_HPP

#include "charClass.hpp"

class KnightClass : public CharClass
{
public:
    KnightClass();
    ~KnightClass();
    
    void classUpdate();
};


#endif