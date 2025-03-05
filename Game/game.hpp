#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#include "player.hpp"
#include "battleManager.hpp"
#include "UiManager.hpp"
#include "OverUiManager.hpp"

class Game {
    private:
        // Variables
        sf::RenderWindow* window;  // window
        sf::VideoMode videoMode;   // window size params
        sf::Event ev;  // gets current input events on the window (continuous)
        sf::View view;

        //Game status bools
        bool inBattle;
        bool inOverworld;

        //player
        Player player;

        //Managers
        BattleManager* battleManager;
        UiManager* uiManager;
        OverUiManager* overworldManager;

        //selection bools
        bool MainSelectMenuBool;
        bool EnemySelectMenuBool;
        bool EnemyLimbSelectMenuBool;
        bool SkillSelectMenuBool;
        bool ItemSelectMenuBool;
        bool FleeBool; //if fleeing or not
        bool CharSelectmenuBool; // (for skill / item eg, healing)

        //current Selection
        int currentSelectionId; //switching between selection options
        int confirmedSelection; //the confirmed selection choice

        int currentSelectedEnemy;
        int confirmedSelectedEnemy; 

        int currentSelectedChar;
        int confirmedSelectedChar; 

        int currentSelectedELimb;
        int confirmedSelectedElimb;

        int currentSelectedSkill;
        int confirmedSelectedSkill;

        //sprites and textures
        sf::Texture squareTex; //default square tex
        sf::Font gameFont; //game font

        sf::Text* CharNames; //list of character names


        //initialisation
        void initVariables();  // initalises variables
        void initWindow();     // starts the window
        void initSprites(); //init sprites

        sf::View getLetterboxView(sf::View, int, int);

    public:
        //const
        Game();
        ~Game();
        
        // accessor
        const bool getWindowIsOpen() const;

        // Functions
        void pollEvents();
        void inBattleEvents();
        void inOverworldEvents();

        void update();
        void render();

};


#endif