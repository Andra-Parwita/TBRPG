#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include "Character/characterSpriteLoader.hpp"
#include "Character/party.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "battleManager.hpp"

class UiManager //sprite positioner && assigner
{
private:
    Party* currentParty;
    sf::Texture squareTex;
    sf::Font gameFont; //game font
    BattleManager* battleManager;
    int currentEnemySelection;
    
public:

    //menus
    sf::Sprite* MainSelectMenu;
    sf::Text* MainSelectText;

    std::vector<sf::Sprite*> EnemySelectMenu; //Enemy Selection Menu

    characterSpriteLoader* EnemyLimbSelectMenu; //Limb Selection Menu
    sf::Text* EnemyLimbSelectText;

    std::vector<sf::Sprite*> SkillSelectMenu; //Skill Selection menu
    sf::Text* SkillSelectText;

    std::vector<sf::Sprite*> ItemSelectMenu; //Item Selection Menu
    sf::Text* ItemSelectText;

    sf::Sprite MenuLeft; //MenuBg
    sf::Sprite MenuRight; //MenuBg
    sf::Text* Back;
    sf::RectangleShape* BackBox;

    //stats
    sf::Text* CharStatsText;
    sf::Text* dmgIndicator;
    std::vector<sf::Text*> CharTurnOrderText;


    std::vector<characterSpriteLoader*> charSprites;
    std::vector<characterSpriteLoader*> enemySprites;

    UiManager();
    UiManager(Party*);
    ~UiManager();

    void InitBattleMenu();

    void load_BattleManager(BattleManager*);

    void update_Menu(int, int);
    void update_Sprites();

    void positionBattleBack();
    void positionBattleParty();
    void positionBattleEnemy();
    void positionTurnOrderDisp();

    void cleanupCharSprites();
};


#endif