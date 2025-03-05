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
    this->currentSelectedSkill = 0;
    this->confirmedSelectedSkill = 0;


    inBattle = true;
    inOverworld = false;

    MainSelectMenuBool = true;
    EnemySelectMenuBool = false;

    overworldManager = new OverUiManager(&player.party);
    battleManager = new BattleManager(&player);
    uiManager = new UiManager(&player.party);
    uiManager->load_BattleManager(battleManager);

    uiManager->InitBattleMenu();
}  

void Game::initWindow(){ // starts the window
    this->videoMode.height = 1080; 
    this->videoMode.width = 1920;
    this->window = new sf::RenderWindow(this->videoMode, "RPG", (sf::Style::Resize + sf::Style::Close));
    this->window->setFramerateLimit(60);

    view.setSize(1920, 1080);
    view.setCenter( view.getSize().x / 2, view.getSize().y / 2 );
    view = getLetterboxView( view, 1920, 1080);  
}    

void Game::initSprites(){
    if (!gameFont.loadFromFile("./Sprites/PixelGameFont.ttf")){
        std::cout << "Cannot load Font" << std::endl;
    }

    if (!squareTex.loadFromFile("./Sprites/Square.png")){
        std::cout << "Cannot load Square Tex" << std::endl;
    }

}

//Game constructors

Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initSprites();
}
Game::~Game(){
    std::cout << "Clearing: " << uiManager << std::endl;
    delete this->uiManager;
    uiManager = nullptr;
	std::cout << "Ui was freed" << std::endl;
    std::cout << "Clearing: " << battleManager << std::endl;
    delete this->battleManager;
    battleManager = nullptr;
	std::cout << "Battle was freed" << std::endl;
    std::cout << "Clearing: " << window << std::endl;
    delete this->window;
    window = nullptr;
	std::cout << "Window was freed" << std::endl;

}

//looping
const bool Game::getWindowIsOpen() const {
    return this->window->isOpen();
}

void Game::inBattleEvents(){ //battle controls
if (!uiManager->animationPlaying){
    battleManager->update_Status();                     //might be slow, due to constant checks
    if (battleManager->get_playerTurn()) {
        if(this->ev.type == sf::Event::KeyPressed){
            if ((ev.key.scancode == sf::Keyboard::Scan::Left) || (ev.key.scancode == sf::Keyboard::Scan::A)) {
                if (MainSelectMenuBool){ //main
                    this->currentSelectionId = 1;
                    std::cout << "chose ID: " << currentSelectionId << std::endl;

                } if (EnemySelectMenuBool){ //enemy
                    this->currentSelectedEnemy++;
                    if (currentSelectedEnemy > battleManager->get_numOfEnemies()-1){
                        currentSelectedEnemy = 0;
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
                    std::cout << "chose ID: " << currentSelectionId << std::endl;

                } if (EnemySelectMenuBool){ //enemy
                    this->currentSelectedEnemy--;
                    if (currentSelectedEnemy < 0){
                        currentSelectedEnemy = battleManager->get_numOfEnemies()-1;
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
                if (SkillSelectMenuBool){
                    currentSelectedSkill++;
                    if (currentSelectedSkill > battleManager->get_CharSkillListSize()-1){
                        currentSelectedSkill = 0;
                    }
                    std::cout << "Current Skill chosen: " << currentSelectedSkill << std::endl;
                }
            }

            if (ev.key.scancode == sf::Keyboard::Scan::Enter) {
                if (MainSelectMenuBool){
                    confirmedSelection = currentSelectionId;
                    std::cout << "Confimed ID: " << confirmedSelection << " from: " << currentSelectionId << std::endl;

                    if (confirmedSelection == 4){ //fleeing
                        std::cout << "Fleeing" << std::endl;
                        battleManager->flee();
                    }
                } 
                
                // attacking (default)
                if (EnemySelectMenuBool){
                    confirmedSelectedEnemy = currentSelectedEnemy;
                    confirmedSelection = 5; //moves to limb selection
                    std::cout << "Confimed ID: " << confirmedSelectedEnemy << " from: " << currentSelectedEnemy << std::endl;
                } if (EnemyLimbSelectMenuBool){
                    confirmedSelectedElimb = currentSelectedELimb;
                    battleManager->enemyAttackChoice(confirmedSelectedEnemy, confirmedSelectedElimb);
                    confirmedSelection = 0; //reset to main selection
                }

                if (SkillSelectMenuBool){
                    confirmedSelectedSkill = currentSelectedSkill;
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

void Game::inOverworldEvents(){
    if (this->ev.type == sf::Event::KeyPressed){
        if ((ev.key.scancode == sf::Keyboard::Scan::W) || (ev.key.scancode == sf::Keyboard::Scan::Up)){
            std::cout << "Move up" << std::endl;
            overworldManager->moveCharUp(0);
        }
        if ((ev.key.scancode == sf::Keyboard::Scan::D) || (ev.key.scancode == sf::Keyboard::Scan::Right)){
            std::cout << "Move right" << std::endl;
            overworldManager->moveCharRight(0);
        }
        if ((ev.key.scancode == sf::Keyboard::Scan::A) || (ev.key.scancode == sf::Keyboard::Scan::Left)){
            std::cout << "Move left" << std::endl;
            overworldManager->moveCharLeft(0);
        }
        if ((ev.key.scancode == sf::Keyboard::Scan::S) || (ev.key.scancode == sf::Keyboard::Scan::Down)){
            std::cout << "Move down" << std::endl;
            overworldManager->moveCharDown(0);
        }

        
    }
}


void Game::pollEvents(){
    while (this->window->pollEvent(this->ev)){

        // windowclose
        if (this->ev.type == sf::Event::Closed){ //close window button
            this->window->close();
        }
        if (ev.type == sf::Event::Resized){
                view = getLetterboxView( view, ev.size.width, ev.size.height );
        }

        //controls
        if (inBattle) {
            inBattleEvents();
        }
    }
    //outside of when an event is polled (updated with key press)
    if (inOverworld){
        inOverworldEvents();
    }
}

void Game::update(){ //game updates
    if (currentSelectedEnemy > battleManager->get_numOfEnemies()-1){
        std::cout << "lowered Selection to: " << currentSelectedEnemy << std::endl;
        currentSelectedEnemy--;
    }
    this->pollEvents(); //calling any user inputs
    this->inBattle = battleManager->get_battleStatus();

    if (!this->inBattle){ //checking if in battle
        inOverworld = true;
    }

    if (inBattle) { //resetSelectionOptions
        switch (confirmedSelection)
        {
        case 0: //main
            MainSelectMenuBool = true;
            SkillSelectMenuBool = false;
            ItemSelectMenuBool = false;
            EnemySelectMenuBool = false;
            EnemyLimbSelectMenuBool = false;
            FleeBool = false;
            CharSelectmenuBool = false;
            break;
        case 1: //skill
            SkillSelectMenuBool = true;
            MainSelectMenuBool = false;
            ItemSelectMenuBool  = false;
            EnemyLimbSelectMenuBool = false;
            FleeBool = false;
            EnemySelectMenuBool = false;
            CharSelectmenuBool = false;
            break;
        case 2: //item
            ItemSelectMenuBool  = true;
            MainSelectMenuBool = false;
            SkillSelectMenuBool = false;
            EnemyLimbSelectMenuBool = false;
            FleeBool = false;
            EnemySelectMenuBool = false;
            CharSelectmenuBool = false;
            break;
        case 3: //Enemy select
            EnemyLimbSelectMenuBool = false;
            MainSelectMenuBool = false;
            SkillSelectMenuBool = false;
            ItemSelectMenuBool  = false;
            FleeBool = false;
            EnemySelectMenuBool = true;
            CharSelectmenuBool = false;
            break;
        case 4: //flee
            FleeBool = true;
            MainSelectMenuBool = false;
            SkillSelectMenuBool = false;
            ItemSelectMenuBool  = false;
            EnemyLimbSelectMenuBool = false;
            EnemySelectMenuBool = false;
            CharSelectmenuBool = false;
            break;
        case 5: //limb select
            FleeBool = false;
            MainSelectMenuBool = false;
            SkillSelectMenuBool = false;
            ItemSelectMenuBool  = false;
            EnemyLimbSelectMenuBool = true;
            EnemySelectMenuBool = false;
            CharSelectmenuBool = false;
            break;
        case 6: //limb select
            FleeBool = false;
            MainSelectMenuBool = false;
            SkillSelectMenuBool = false;
            ItemSelectMenuBool  = false;
            EnemyLimbSelectMenuBool = false;
            EnemySelectMenuBool = false;
            CharSelectmenuBool = true;
            break;
        default:
            break;
        }
    }

    //update selection graphics
    if (MainSelectMenuBool){
        uiManager->update_Menu(confirmedSelection, currentSelectionId);
    }
    if (EnemySelectMenuBool){
        uiManager->update_Menu(confirmedSelection, currentSelectedEnemy);
    }
    if (EnemyLimbSelectMenuBool){
        uiManager->update_Menu(confirmedSelection, currentSelectedELimb);
    }
}

void Game::render(){ //game renders
    this->window->clear(sf::Color(20,20,20)); //clearing frame
    this->window->setView(view);
    
    //battleRender
    if (inBattle){
        uiManager->positionBattleBack();
        this->window->draw(uiManager->MenuLeft);
        uiManager->positionBattleParty();
        uiManager->positionBattleEnemy();
        uiManager->positionTurnOrderDisp();
        uiManager->update_Sprites(); 
        uiManager->update_CharStats();

        for (int i = 0; i < uiManager->charSprites.size(); i++){ //play chars
            this->window->draw(uiManager->charSprites[i]->characterSprite);
        }
        //Enemy Render
        for (int i = 0; i < uiManager->enemySprites.size(); i++){ //enemy 
            for (int j = 0; j < battleManager->EnemyList[i]->get_limbNo(); j++){
               this->window->draw(*uiManager->enemySprites[i]->characterLimbSprites[j]);
            }
        } 
        for (int i = 0; i < uiManager->CharTurnOrderText.size(); i++){ // turn order text
            this->window->draw(*uiManager->CharTurnOrderText[i]);
        }

        this->window->draw(uiManager->MenuRight); //right menu

        for (int i = 0; i < uiManager->HealthBar.size(); i++){ //healtbar
            this->window->draw(*uiManager->HealthBar[i]);
        } 

        
        for (int i = 0; i < uiManager->TotalHp.size(); i++){ //Total Hp text
            this->window->draw(*uiManager->TotalHp[i]);
        }

        for (int i = 0; i < uiManager->charHpIndicator.size(); i++){ //mini person ui for each char
            for (int j = 0; j < 6; j++){
                this->window->draw(*uiManager->charHpIndicator[i]->characterLimbSprites[j]);
            }
        } 

        if (MainSelectMenuBool){
            for (int i = 0; i < 4; i++){
                this->window->draw(uiManager->MainSelectMenu[i]);
                this->window->draw(uiManager->MainSelectText[i]);
            }
        }
        if (EnemyLimbSelectMenuBool){
            this->window->draw(*uiManager->accuracyIndicator);
            for (int i = 0; i < 6; i++){ //change if making enemies with more limbs
                this->window->draw(*uiManager->EnemyLimbSelectMenu->characterLimbSprites[i]);
            }
        }
        if (battleManager->attacked){
            uiManager->dmgPopupAnimation(this->window);
        }
        uiManager->update_Sprites(); 
    } 

    //overworld
    if (inOverworld){
        for (int i = 0; i < player.party.get_numMembers(); i++){
            this->window->draw(overworldManager->charSprites[0]->characterSprite);
        }
    }

    this->window->display(); //displays frame 
}

sf::View Game::getLetterboxView(sf::View view, int windowWidth, int windowHeight) { //taken online by

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to achieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = (float) windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;
}