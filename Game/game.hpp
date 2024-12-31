#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#include "player.hpp"
#include "battleManager.hpp"

class Game {
    private:
        // Variables
        sf::RenderWindow* window;  // window
        sf::VideoMode videoMode;   // window size params
        sf::Event ev;  // gets current input events on the window (continuous)

        bool inBattle;

        //player
        Player player;

        //battleManager
        BattleManager* battleManager;

        sf::Sprite SamuraiDisp;

        //MenuTypes
        sf::Sprite MenuLeft; //default menu
        sf::Sprite MenuRight;
        sf::Text* CharStatsText;

        sf::Sprite* MainSelectMenu; //Action combat menu
        bool MainSelectMenuBool;
        sf::Text* MainSelectText;

        sf::Sprite* EnemySelectMenu; //Limb Selection Menu
        bool EnemySelectMenuBool;

        sf::Sprite* EnemyLimbSelectMenu; //Limb Selection Menu
        bool EnemyLimbSelectMenuBool;

        sf::Sprite* SkillSelectMenu; //Skill Selection menu
        bool SkillSelectMenuBool;
        sf::Text* SkillSelectText;

         sf::Sprite* ItemSelectMenu; //Item Selection Menu
        bool ItemSelectMenuBool;
        sf::Text* ItemSelectText;

        bool FleeBool; //if fleeing or not

        bool GuardBool; //if guarding or not

        //current Selection
        int currentSelectionId; //switching between selection options
        int confirmedSelection; //the confirmed selection choice

        int currentSelectedEnemy;
        int confirmedSelectedEnemy; 

        int currentSelectedELimb;
        int confirmedSelectedElimb;

        //sprites and textures
        sf::Texture squareTex; //default square tex
        sf::Texture SamuraiTex; //char text 2
        sf::Font gameFont; //game font

        sf::Text* CharNames; //list of character names


        //initialisation
        void initVariables();  // initalises variables
        void initWindow();     // starts the window
        void initSprites(); //init sprites

    public:
        //const
        Game();
        ~Game();
        
        // accessor
        const bool getWindowIsOpen() const;

        // Functions
        void pollEvents();
        void update();
        void render();
};


#endif