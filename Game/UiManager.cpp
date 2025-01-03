#include "UiManager.hpp"

UiManager::UiManager(){
    if (!gameFont.loadFromFile("./Sprites/PixelGameFont.ttf")){
        std::cout << "Cannot load Font" << std::endl;
    }
    if (!squareTex.loadFromFile("./Sprites/Square.png")){
        std::cout << "Cannot load Square Tex" << std::endl;
    }
}

UiManager::UiManager(Party* NParty){
    if (!gameFont.loadFromFile("./Sprites/PixelGameFont.ttf")){
        std::cout << "Cannot load Font" << std::endl;
    }
    if (!squareTex.loadFromFile("./Sprites/Square.png")){
        std::cout << "Cannot load Square Tex" << std::endl;
    }
    currentParty = NParty;
    for (int i = 0; i < currentParty->get_numMembers(); i++){
        charSprites.push_back(currentParty->members[i]->sprite);
    }
}

UiManager::~UiManager(){
     for (auto spriteLoader : enemySprites) {
        delete spriteLoader;  // Make sure to delete each allocated characterSpriteLoader
    }
    enemySprites.clear();  // Clear the vector to remove the now-deleted pointers
}

void UiManager::load_BattleManager(BattleManager* importedBattleManager){
    currentEnemySelection = 0;
    this->battleManager = importedBattleManager;

    if (battleManager == nullptr) {
        std::cout << "BattleManager is nullptr!" << std::endl;
        return;
    }

    if (battleManager->get_battleStatus()){
        for (int i = 0; i < battleManager->get_numOfEnemies(); i++){
            if (battleManager->EnemyList[i] == nullptr) {
                std::cout << "Null enemy at index " << i << std::endl;
                continue;
            }
            std::string temp = battleManager->EnemyList[i]->get_name() + battleManager->EnemyList[i]->get_expectedFileSize();
            //enemySprites.push_back(new characterSpriteLoader(battleManager->EnemyList[i]->get_name()));
            enemySprites.push_back(new characterSpriteLoader(battleManager->EnemyList[i]->get_name() + battleManager->EnemyList[i]->get_expectedFileSize()));
            enemySprites[i]->characterSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
        }
    }
}

void UiManager::InitBattleMenu(){
    MainSelectMenu = new sf::Sprite[4];
    MainSelectText = new sf::Text[4];

    for (int i = 0; i < 4; i++){
        MainSelectMenu[i].setTexture(squareTex);
        MainSelectMenu[i].setColor(sf::Color::White);
        MainSelectMenu[i].setScale(sf::Vector2f(0.5f,0.5f));

        MainSelectText[i].setFont(gameFont);
        MainSelectText[i].setCharacterSize(24);
        MainSelectText[i].setOutlineThickness(2.f);
    }

    MainSelectMenu[0].setPosition(sf::Vector2f(50.f,850.f));
    MainSelectMenu[1].setPosition(sf::Vector2f(150.f,750.f));
    MainSelectMenu[2].setPosition(sf::Vector2f(250.f,850.f));
    MainSelectMenu[3].setPosition(sf::Vector2f(150.f,950.f));

    MainSelectText[0].setPosition(sf::Vector2f(50.f,850.f));
    MainSelectText[0].setString("Skill");
    MainSelectText[1].setPosition(sf::Vector2f(150.f,750.f));
    MainSelectText[1].setString("Item");
    MainSelectText[2].setPosition(sf::Vector2f(250.f,850.f));
    MainSelectText[2].setString("Attack");
    MainSelectText[3].setPosition(sf::Vector2f(150.f,950.f));
    MainSelectText[3].setString("Flee");

    for (int i = 0; i < battleManager->EnemyList.size(); i++){ //position later for enemy selection
        EnemySelectMenu.push_back(new sf::Sprite);
        EnemySelectMenu[i]->setTexture(squareTex);
    }

    EnemyLimbSelectMenu = new characterSpriteLoader("ManSheet");
    EnemyLimbSelectMenu->characterSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    EnemyLimbSelectMenu->characterSprite.setScale(10.f,10.f);
    EnemyLimbSelectMenu->characterSprite.setPosition(sf::Vector2f(35,720));
    EnemyLimbSelectMenu->initLimbSprites(6,10.f);

    for (int i = 0; i < battleManager->battleParticipants.size(); i++){
        CharTurnOrderText.push_back(new sf::Text);
        CharTurnOrderText[i]->setCharacterSize(20);
        CharTurnOrderText[i]->setFont(gameFont);
        CharTurnOrderText[i]->setOutlineThickness(2.f);
        CharTurnOrderText[i]->setString(battleManager->battleParticipants[i]->get_name());
        CharTurnOrderText[i]->setPosition(sf::Vector2f(20.f, 50*i));
    }
}

void UiManager::update_Menu(int MenuId, int selectedId){

    
    for (int i = 0; i < battleManager->EnemyList[currentEnemySelection]->get_limbNo(); i++){
            enemySprites[currentEnemySelection]->characterLimbSprites[i]->setColor(sf::Color::White); 
        }

    for (int i = 0; i < 6; i++){
        EnemyLimbSelectMenu->characterLimbSprites[i]->setColor(sf::Color::White); 
    }

    switch (MenuId)
    {
    case 0: //main
        for(int i = 0; i < 4; i++){
            if (i + 1 != selectedId){
                MainSelectMenu[i].setColor(sf::Color::White);
            }
        }
        MainSelectMenu[selectedId-1].setColor(sf::Color::Cyan);
        break;
    case 1: //skill
        break;
    case 2: //item
        break;
    case 3: //Enemy Select
        /*for(int i = 0; i < battleManager->EnemyList.size(); i++){
            if (i != selectedId){
                enemySprites[i]->characterSprite.setColor(sf::Color(255,255,255,100));
            }
            enemySprites[selectedId]->characterSprite.setColor(sf::Color::(0,255,255,100));
        } */

        currentEnemySelection = selectedId;
        for (int j = 0; j < enemySprites.size(); j++){
            for (int i = 0; i < battleManager->EnemyList[j]->get_limbNo(); i++){
                enemySprites[currentEnemySelection]->characterLimbSprites[i]->setColor(sf::Color::Cyan); 
            }
        }
        break;
    case 4: //flee
        break;
    case 5: //limb select
        enemySprites[currentEnemySelection]->characterLimbSprites[selectedId]->setColor(sf::Color(0,255,255,200)); 
        EnemyLimbSelectMenu->characterLimbSprites[selectedId]->setColor(sf::Color(0,255,255,200)); 
        break;
    default:
        break;
    }
}

void UiManager::update_Sprites(){
    //cleanup
    cleanupCharSprites();

    //enemy
    for (int i = 0; i < enemySprites.size(); i++){
        if (enemySprites[i] == nullptr) {
            continue;  // Skip if nullptr
        }

        for (int j = 0; j < battleManager->EnemyList[i]->get_limbNo(); j++){
            if (battleManager->EnemyList[i]->get_limbHP(j) <= battleManager->EnemyList[i]->get_limbMaxHP(j)/2) {
                if (enemySprites[i] != nullptr) {
                    enemySprites[i]->updateSprite(j);
                }
            } 
            if (battleManager->EnemyList[i]->get_limbHP(j) <= 0){
                if (enemySprites[i] != nullptr) {
                    enemySprites[i]->characterLimbSprites[j]->setColor(sf::Color(0,0,0,0));
                }
            }
        }
    }
    //player
}

void UiManager::positionBattleParty(){
    float spHeight = 550.f;
    for (int i = 0; i < charSprites.size(); i++){
        
        charSprites[i]->characterSprite.setScale(sf::Vector2f(8.f,8.f));
        switch (i)
        {
        case 0:
            charSprites[i]->characterSprite.setPosition(sf::Vector2f(350.f,spHeight));
            break;
        case 1:
            charSprites[i]->characterSprite.setPosition(sf::Vector2f(650.f,spHeight));
            break;
        case 2:
            charSprites[i]->characterSprite.setPosition(sf::Vector2f(950.f,spHeight));
            break;
        case 3:
            charSprites[i]->characterSprite.setPosition(sf::Vector2f(1250.f,spHeight));
            break;
        default:
            charSprites[i]->characterSprite.setColor(sf::Color::Magenta);
            break;
        }
    }
}

void UiManager::positionBattleBack(){
    MenuLeft.setTexture(squareTex);
    MenuLeft.setColor(sf::Color(25,25,25));
    MenuLeft.setScale(sf::Vector2f(2.f,3.0f));
    MenuLeft.setPosition(sf::Vector2f(0.f,730.f));

    MenuRight.setTexture(squareTex);
    MenuRight.setColor(sf::Color(25,25,25,170));
    MenuRight.setScale(sf::Vector2f(7.0f,3.0f));
    MenuRight.setPosition(sf::Vector2f(400.f,730.f));
}

void UiManager::positionBattleEnemy(){
    float defaultHeight = 200.f;
    for (int i = 0; i < enemySprites.size(); i++){
        if (enemySprites[i] == nullptr) {
            continue;  // Skip null pointers
        }

        switch (i)
        {
        case 0: //middle enemy
            enemySprites[i]->characterSprite.setPosition(sf::Vector2f(650.f,defaultHeight));
            break;
        case 1: //left
            enemySprites[i]->characterSprite.setPosition(sf::Vector2f(350.f,defaultHeight));
            break;
        case 2: //right
            enemySprites[i]->characterSprite.setPosition(sf::Vector2f(950.f,defaultHeight));
            break;
        default:
            break;
        }
        enemySprites[i]->characterSprite.setScale(sf::Vector2f(10.f,10.f));
        if (battleManager->EnemyList[i] != nullptr) {
            enemySprites[i]->initLimbSprites(battleManager->EnemyList[i]->get_limbNo(), 10.f);
        }
    }
}

void UiManager::positionTurnOrderDisp() {
    // Ensure CharTurnOrderText matches battleParticipants size
    size_t numParticipants = battleManager->battleParticipants.size();

    // Update CharTurnOrderText with current participant names
    for (size_t i = 0; i < numParticipants; i++) {
        if (i < CharTurnOrderText.size()) {
            CharTurnOrderText[i]->setString(battleManager->battleParticipants[i]->get_name());
            CharTurnOrderText[i]->setPosition(sf::Vector2f(20.f, 50.f * i));
            if (battleManager->battleParticipants[i]->get_currentTurn()) {
                CharTurnOrderText[i]->setString(battleManager->battleParticipants[i]->get_name() + " << CURRENT!");
            }
        }
    }

    if (numParticipants < CharTurnOrderText.size()) {
        CharTurnOrderText.resize(numParticipants);
    }
}


void UiManager::cleanupCharSprites(){
    if (!battleManager->get_battleStatus()){
        enemySprites.clear();
    }
}