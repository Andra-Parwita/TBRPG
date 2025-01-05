#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include "Character/characterSpriteLoader.hpp"
#include "Character/party.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "battleManager.hpp"
#include <set>

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
    std::vector<sf::Text*> CharTurnOrderText; //character Turn list

    sf::Text* chanceToHitText; //percent to hit limb

    std::vector<characterSpriteLoader*> charSprites;
    std::vector<characterSpriteLoader*> enemySprites;

    std::vector<characterSpriteLoader*> charHpIndicator; //mini limb shower
    std::vector<sf::Text*> TotalHp; //hp text
    std::vector<sf::RectangleShape*> HealthBar; //health bar
    sf::Vector2f defaultHpBarSize;

    UiManager();
    UiManager(Party*);
    ~UiManager();

    void InitBattleMenu();
    void InitCharStatsMenu();

    void load_BattleManager(BattleManager*);

    void update_CharStats();
    void update_Menu(int, int);
    void update_Sprites();

    void positionBattleBack();
    void positionBattleParty();
    void positionBattleEnemy();
    void positionTurnOrderDisp();

    void syncEnemyList();
    void cleanupCharSprites();
};


#endif