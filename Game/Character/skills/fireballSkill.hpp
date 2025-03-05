#ifndef FIREBALLSKILL_HPP
#define FIREBALLSKILL_HPP

#include "skill.hpp"

class FireballSkill : public Skill
{
public:
    FireballSkill();
    virtual ~FireballSkill(); 
    void skillAbility();  
};

#endif
