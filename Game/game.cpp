#include "game.hpp"

//Initialisation

void Game::initVariables(){ // initalises variables
    this->window = nullptr;
    this->currentSelectionId = 0;
    this->confirmedSelection = 0;
    this->currentSelectedEnemy = 0;
    this->confirmedSelectedEnemy = 0;
    this->currentSelectedELimb = 0;
    this->confirmedSelectedElimb = 0;

    inBattle = true;
    MainSelectMenuBool = true;
    EnemySelectMenuBool = false;

    battleManager = new BattleManager(&player);
}  

void Game::initWindow(){ // starts the window
    this->videoMode.height = 1080;
    this->videoMode.width = 1920;
    this->window = new sf::RenderWindow(this->videoMode, "RPG");
    this->window->setFramerateLimit(60);
}    

void Game::initSprites(){
    if (!gameFont.loadFromFile("./Sprites/PixelGameFont.ttf")){
        std::cout << "Cannot load Font" << std::endl;
    }

    if (!squareTex.loadFromFile("./Sprites/Square.png")){
        std::cout << "Cannot load Square Tex" << std::endl;
    }

    MenuLeft.setTexture(squareTex);
    MenuLeft.setColor(sf::Color(25,25,25,125));
    MenuLeft.setScale(sf::Vector2f(2.5f,3.0f));
    MenuLeft.setPosition(sf::Vector2f(0.f,730.f));

    MenuRight.setTexture(squareTex);
    MenuRight.setColor(sf::Color(25,25,25,125));
    MenuRight.setScale(sf::Vector2f(7.0f,3.0f));
    MenuRight.setPosition(sf::Vector2f(500.f,730.f));

    MainSelectMenu = new sf::Sprite[4];
    for (int i = 0; i < 4; i++){
        MainSelectMenu[i].setTexture(squareTex);
        MainSelectMenu[i].setColor(sf::Color::White);
        MainSelectMenu[i].setScale(sf::Vector2f(0.5f,0.5f));
    }
    MainSelectMenu[0].setPosition(sf::Vector2f(50.f,850.f));
    MainSelectMenu[1].setPosition(sf::Vector2f(150.f,750.f));
    MainSelectMenu[2].setPosition(sf::Vector2f(250.f,850.f));
    MainSelectMenu[3].setPosition(sf::Vector2f(150.f,950.f));

    if (!SamuraiTex.loadFromFile("./Sprites/Hikari.png")){
        std::cout << "Cannot load Samurai Tex" << std::endl;
    }

    SamuraiDisp.setTexture(SamuraiTex);
    SamuraiDisp.setPosition(sf::Vector2f(850.f,730.f));
    SamuraiDisp.setScale(sf::Vector2f(5.f,5.f));

}

//Game constructors

Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initSprites();
}
Game::~Game(){
    delete this->window;
	std::cout << "Window was freed" << std::endl;

}

//looping


const bool Game::getWindowIsOpen() const {
    return this->window->isOpen();
}


void Game::pollEvents(){
    while (this->window->pollEvent(this->ev)){

        // windowclose
        if (this->ev.type == sf::Event::Closed){ //close window button
            this->window->close();
        }
        if (inBattle) {
            if (battleManager->get_playerTurn()) {
                if(this->ev.type == sf::Event::KeyPressed){
                    if ((ev.key.scancode == sf::Keyboard::Scan::Left) || (ev.key.scancode == sf::Keyboard::Scan::A)) {
                        if (MainSelectMenuBool){ //main
                            this->currentSelectionId = 1;
                            this->MainSelectMenu[currentSelectionId-1].setColor(sf::Color::Cyan);
                            std::cout << "chose ID: " << currentSelectionId << std::endl;
                        } if (EnemySelectMenuBool){ //enemy
                            this->currentSelectedEnemy--;
                            if (currentSelectedEnemy < 0){
                                currentSelectedEnemy = battleManager->get_numOfEnemies()-1;
                            }
                            std::cout << "Current Enemy chosen: " << currentSelectedEnemy << std::endl;

                        } if (EnemyLimbSelectMenuBool){ // enemy limb
                            this->currentSelectedELimb--;
                            if (currentSelectedELimb < 0){
                                currentSelectedELimb = battleManager->get_numOfLimbs(confirmedSelectedEnemy)-1;
                            }
                            std::cout << "Current limb chosen: " << currentSelectedELimb << std::endl;
                        }

                    } else if ((ev.key.scancode == sf::Keyboard::Scan::Right) || (ev.key.scancode == sf::Keyboard::Scan::D)) {
                        if (MainSelectMenuBool){ //main
                            this->currentSelectionId = 3;
                            this->MainSelectMenu[currentSelectionId-1].setColor(sf::Color::Cyan);
                            std::cout << "chose ID: " << currentSelectionId << std::endl;
                        } if (EnemySelectMenuBool){ //enemy
                            this->currentSelectedEnemy++;
                            if (currentSelectedEnemy > battleManager->get_numOfEnemies()-1){
                                currentSelectedEnemy = 0;
                            }
                            std::cout << "Current Enemy chosen: " << currentSelectedEnemy << std::endl;

                        } if (EnemyLimbSelectMenuBool){ // enemy limb
                            this->currentSelectedELimb++;
                            if (currentSelectedELimb > battleManager->get_numOfLimbs(confirmedSelectedEnemy)-1){
                                currentSelectedELimb = 0;
                            }
                            std::cout << "Current limb chosen: " << currentSelectedELimb << std::endl;
                        }

                    } else if ((ev.key.scancode == sf::Keyboard::Scan::Up) || (ev.key.scancode == sf::Keyboard::Scan::W)) {
                        if (MainSelectMenuBool){
                            this->currentSelectionId = 2;
                            this->MainSelectMenu[currentSelectionId-1].setColor(sf::Color::Cyan);
                            std::cout << "chose ID: " << currentSelectionId << std::endl;
                        } if (EnemyLimbSelectMenuBool){ // enemy limb
                            switch (currentSelectedELimb)
                            {
                            case 0:
                                currentSelectedELimb = 4;
                                break;
                            case 1:
                            case 2:
                            case 3:
                                currentSelectedELimb = 0;
                                break;
                            case 4:
                                currentSelectedELimb = 2;
                                break;
                            case 5:
                                currentSelectedELimb = 3;
                                break;
                            default:
                                break;
                            }
                            std::cout << "Current limb chosen: " << currentSelectedELimb << std::endl;
                        }
                    } else if ((ev.key.scancode == sf::Keyboard::Scan::Down) || (ev.key.scancode == sf::Keyboard::Scan::S)) {
                        if (MainSelectMenuBool){
                            this->currentSelectionId = 4;
                            this->MainSelectMenu[currentSelectionId-1].setColor(sf::Color::Cyan);
                            std::cout << "chose ID: " << currentSelectionId << std::endl;
                        } if (EnemyLimbSelectMenuBool){ // enemy limb
                            switch (currentSelectedELimb)
                            {
                            case 0:
                                currentSelectedELimb = 1;
                                break;
                            case 1:
                            case 2:
                                currentSelectedELimb = 4;
                                break;
                            case 3:
                                currentSelectedELimb = 5;
                                break;
                            case 4:
                            case 5:
                                currentSelectedELimb = 0;
                                break;
                            default:
                                break;
                            }
                            std::cout << "Current limb chosen: " << currentSelectedELimb << std::endl;
                        }
                    }

                    if (ev.key.scancode == sf::Keyboard::Scan::Enter) {
                        if (MainSelectMenuBool){
                            confirmedSelection = currentSelectionId;
                            std::cout << "Confimed ID: " << confirmedSelection << " from: " << currentSelectionId << std::endl;
                        } if (EnemySelectMenuBool){
                            confirmedSelectedEnemy = currentSelectedEnemy;
                            confirmedSelection = 5;
                            std::cout << "Confimed ID: " << confirmedSelectedEnemy << " from: " << currentSelectedEnemy << std::endl;
                        } if (EnemyLimbSelectMenuBool){
                            confirmedSelectedElimb = currentSelectedELimb;
                            battleManager->enemyAttackChoice(confirmedSelectedEnemy, confirmedSelectedElimb);
                            confirmedSelection = 0;
                        }
                    }

                    if (ev.key.scancode == sf::Keyboard::Scan::Backspace) {
                        confirmedSelection = 0;
                        std::cout << "Back" << std::endl;
                    }
                }
            } else {
                battleManager->update_Status();
            }

        }
    }
}

void Game::update(){ //game updates
    this->pollEvents(); //calling any user inputs

    if (MainSelectMenuBool){ //updates the selection colours
        for(int i = 0; i < 4; i ++){
            if (i + 1 != currentSelectionId){
                MainSelectMenu[i].setColor(sf::Color::White);
            }
        }
    }

    if (inBattle) {
        switch (confirmedSelection)
        {
        case 0:
            MainSelectMenuBool = true;
            SkillSelectMenuBool = false;
            GuardBool = false;
            EnemySelectMenuBool = false;
            EnemyLimbSelectMenuBool = false;
            FleeBool = false;
            break;
        case 1:
            SkillSelectMenuBool = true;
            MainSelectMenuBool = false;
            GuardBool = false;
            EnemyLimbSelectMenuBool = false;
            FleeBool = false;
            EnemySelectMenuBool = false;
            break;
        case 2:
            GuardBool = true;
            MainSelectMenuBool = false;
            SkillSelectMenuBool = false;
            EnemyLimbSelectMenuBool = false;
            FleeBool = false;
            EnemySelectMenuBool = false;
            break;
        case 3:
            EnemyLimbSelectMenuBool = false;
            MainSelectMenuBool = false;
            SkillSelectMenuBool = false;
            GuardBool = false;
            FleeBool = false;
            EnemySelectMenuBool = true;
            break;
        case 4:
            FleeBool = true;
            MainSelectMenuBool = false;
            SkillSelectMenuBool = false;
            GuardBool = false;
            EnemyLimbSelectMenuBool = false;
            EnemySelectMenuBool = false;
            break;
        case 5:
            FleeBool = false;
            MainSelectMenuBool = false;
            SkillSelectMenuBool = false;
            GuardBool = false;
            EnemyLimbSelectMenuBool = true;
            EnemySelectMenuBool = false;
            break;
        default:
            break;
        }
    }
}
void Game::render(){ //game renders
    this->window->clear(sf::Color(15,15,15)); //clearing frame

    if (inBattle){
        this->window->draw(this->MenuLeft);
        this->window->draw(this->MenuRight);
        if (MainSelectMenuBool){
            for (int i = 0; i < 4; i++){
                this->window->draw(this->MainSelectMenu[i]);
            }
        }
        this->window->draw(this->SamuraiDisp);
    }

    this->window->display(); //displays frame
}