#ifndef LIMB_HPP
#define LIMB_HPP

#include <string>

enum limbType{
    eHead, eTorso,
    eRArm, eLArm,
    eRLeg, eLLeg
};

class Limb
{
private:
    std::string limbName;
    int hp;
    int maxHp;
    bool state;
    float limbHitChance;

    limbType hashit(std::string const&);

public:
    //constructors
    Limb();
    Limb(int);
    Limb(int, std::string);
    Limb(int, std::string, float);
    ~Limb();

    //getters
    bool getState();
    int getHp();
    int getMaxHp();
    std::string get_limbName();
    float getlimbHitChance();

    //setter
    void set_limbName(std::string);
    void setHp(int);
    void setMaxHp(int);
    void setLimbHitChance(float);

};

#endif