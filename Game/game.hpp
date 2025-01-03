#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#include "player.hpp"
#include "battleManager.hpp"
#include "UiManager.hpp"

class Game {
    private:
        // Variables
        sf::RenderWindow* window;  // window
        sf::VideoMode videoMode;   // window size params
        sf::Event ev;  // gets current input events on the window (continuous)

        bool inBattle;

        //player
        Player player;

        //Managers
        BattleManager* battleManager;
        UiManager* uiManager;

        bool MainSelectMenuBool;
        bool EnemySelectMenuBool;
        bool EnemyLimbSelectMenuBool;
        bool SkillSelectMenuBool;
        bool ItemSelectMenuBool;
        bool FleeBool; //if fleeing or not

        //current Selection
        int currentSelectionId; //switching between selection options
        int confirmedSelection; //the confirmed selection choice

        int currentSelectedEnemy;
        int confirmedSelectedEnemy; 

        int currentSelectedELimb;
        int confirmedSelectedElimb;

        //sprites and textures
        sf::Texture squareTex; //default square tex
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
        void inBattleEvents();

        void update();
        void render();
};


#endif