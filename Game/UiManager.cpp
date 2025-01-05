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
     this->battleManager = importedBattleManager;
     syncEnemyList();

    if (battleManager == nullptr) {
        std::cout << "BattleManager is nullptr!" << std::endl;
        return;
    }

    if (battleManager->EnemyList.empty()) {
        std::cout << "EnemyList is empty during load_BattleManager!" << std::endl;
        return;
    }

    currentEnemySelection = 0;

    if (battleManager->get_battleStatus()) {
        for (int i = 0; i < battleManager->get_numOfEnemies(); i++) {
            if (battleManager->EnemyList[i] == nullptr) {
                std::cout << "EnemyList contains nullptr at index " << i << std::endl;
                continue;
            }
            enemySprites.push_back(new characterSpriteLoader(battleManager->EnemyList[i]->get_name() + battleManager->EnemyList[i]->get_expectedFileSize()));
            enemySprites[i]->characterSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
        }
    }

    positionBattleBack();
    positionBattleParty();
    positionBattleEnemy();
    positionTurnOrderDisp();
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

    InitCharStatsMenu();
}

void UiManager::InitCharStatsMenu(){
    defaultHpBarSize.x = 150.f;
    defaultHpBarSize.y = 25.f;
    for (int i = 0; i < currentParty->get_numMembers(); i++){
        TotalHp.push_back(new sf::Text);
        TotalHp[i]->setFont(gameFont);
        TotalHp[i]->setOutlineThickness(2.f);
        TotalHp[i]->setCharacterSize(20);
        TotalHp[i]->setPosition(sf::Vector2f(440+300.f*i, 750.f));
        TotalHp[i]->setString("       "+ currentParty->members[i]->get_name() + 
        "\n\nHP: "+ std::to_string(currentParty->members[i]->get_Hp()) + "/" 
        + std::to_string(currentParty->members[i]->get_MaxHp()));

        charHpIndicator.push_back(new characterSpriteLoader("Man"));
        charHpIndicator[i]->characterSprite.setPosition(380 + 300.f * i, 830.f);
        charHpIndicator[i]->initLimbSprites(6, 3.f);

        HealthBar.push_back(new sf::RectangleShape);
        HealthBar[i]->setPosition(TotalHp[i]->getPosition());
        HealthBar[i]->move(sf::Vector2f(-10.f,45.f));
        HealthBar[i]->setFillColor(sf::Color::Red);
        HealthBar[i]->setSize(defaultHpBarSize);

    }
}

void UiManager::update_CharStats(){ //HP and current stats of characters
    for (int i = 0; i < TotalHp.size(); i++){
        TotalHp[i]->setString("     "+currentParty->members[i]->get_name() + 
        "\n\nHP: "+  std::to_string(currentParty->members[i]->get_Hp()) + "/" 
        + std::to_string(currentParty->members[i]->get_MaxHp()));
    }

    for (int i = 0; i < charHpIndicator.size(); i++){
        for(int j = 0; j < currentParty->members[i]->limbs.size(); j++){
            if(currentParty->members[i]->limbs[j]->getHp() < currentParty->members[i]->limbs[j]->getMaxHp()){
                float temp = static_cast<float>(currentParty->members[i]->limbs[j]->getHp())/static_cast<float>(currentParty->members[i]->limbs[j]->getMaxHp());

                int red = static_cast<int>(255 * (1 - temp));  // Red decreases as HP increases
                int green = static_cast<int>(255 * temp);      // Green increases as HP increases

                charHpIndicator[i]->characterLimbSprites[j]->setColor(sf::Color(red, green, 0));
            }
        }
    }

    for (int i = 0; i < HealthBar.size(); i++){
        float temp = static_cast<float>(currentParty->members[i]->get_Hp())/static_cast<float>(currentParty->members[i]->get_MaxHp());
        HealthBar[i]->setSize(defaultHpBarSize*(temp));
    }
}


void UiManager::update_Menu(int MenuId, int selectedId){ //Menu Updates
    //syncEnemyList();

    if (currentEnemySelection >= 0 && currentEnemySelection < battleManager->EnemyList.size()) {
        if (battleManager->EnemyList[currentEnemySelection]->get_isAlive()){
            for (int i = 0; i < battleManager->EnemyList[currentEnemySelection]->get_limbNo(); i++){
                enemySprites[currentEnemySelection]->characterLimbSprites[i]->setColor(sf::Color::White); 
            }
        }
    }

    for (int i = 0; i < 6; i++){
        EnemyLimbSelectMenu->characterLimbSprites[i]->setColor(sf::Color::White); 
    } 

    size_t startSelection = currentEnemySelection;

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
    case 3: // Enemy Select
        if (selectedId >= 0 && selectedId < enemySprites.size()) {
            currentEnemySelection = selectedId;
            startSelection = currentEnemySelection;
        }

        do {
            if (enemySprites[currentEnemySelection]->get_isActive()) {
                break; // Found an active enemy
            }

            // Move to the next enemy, wrapping around if necessary
            if (currentEnemySelection == 0) {
                currentEnemySelection =  enemySprites.size()-1;
            } else {
                currentEnemySelection = (currentEnemySelection + 1) % enemySprites.size();
            }

            std::cout << "Changed to: " << currentEnemySelection << std::endl;

        } while (currentEnemySelection != startSelection); // Stop if we've looped back to the start

        if (currentEnemySelection >= 0) {
            // Clear the colors for all enemies first
            for (int j = 0; j < enemySprites.size(); j++) {
                if (enemySprites[j] != nullptr) {
                    for (int i = 0; i < 6; i++) { //must be changed if more than 6 limbs in the future
                        if (enemySprites[j]->characterLimbSprites[i] != nullptr) {
                            enemySprites[j]->characterLimbSprites[i]->setColor(sf::Color::White);
                        }
                    }
                } 
            }

            // Highlight the limbs of the selected enemy
            for (int i = 0; i < 6; i++) { //must be changed if more than 6 limbs in the future
                if (enemySprites[currentEnemySelection] != nullptr && 
                    enemySprites[currentEnemySelection]->characterLimbSprites[i] != nullptr) {
                    enemySprites[currentEnemySelection]->characterLimbSprites[i]->setColor(sf::Color::Cyan);
                }
            }
        }


        break;
    case 4: //flee
        break;
    case 5: //limb select
        for (int i = 0; i < battleManager->EnemyList[currentEnemySelection]->get_limbNo(); i++) {
            if (enemySprites[currentEnemySelection]->characterLimbSprites[i] != nullptr) {
                enemySprites[currentEnemySelection]->characterLimbSprites[i]->setColor(sf::Color::White);
            }
        }

        if (enemySprites[currentEnemySelection]->characterLimbSprites[selectedId] != nullptr) {
            enemySprites[currentEnemySelection]->characterLimbSprites[selectedId]->setColor(sf::Color::Cyan);
        }

        EnemyLimbSelectMenu->characterLimbSprites[selectedId]->setColor(sf::Color(0,255,255,200)); 
        break;

    default:
        break;
    }
}


void UiManager::update_Sprites() {
    cleanupCharSprites();
    for (size_t i = 0; i < enemySprites.size(); i++) {
        if (i >= battleManager->EnemyList.size() || enemySprites[i] == nullptr || battleManager->EnemyList[i] == nullptr) {
            continue; // Skip mismatched or null entries
        }

        auto* enemy = battleManager->EnemyList[i];
        auto* sprite = enemySprites[i];
        // Update alive enemy sprites
        for (int j = 0; j < enemy->get_limbNo(); j++) {
            if (enemy->get_limbHP(j) <= enemy->get_limbMaxHP(j) / 2) {
                sprite->updateSprite(j);
            }
            if (enemy->get_limbHP(j) <= 0) {
                sprite->characterLimbSprites[j]->setColor(sf::Color(0, 0, 0, 0));
            }
        }
    }
}



void UiManager::positionBattleParty(){ //positions char sprites
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
            charSprites[i]->characterSprite.setPosition(sf::Vector2f(100.f,spHeight));
            charSprites[i]->characterSprite.setColor(sf::Color::Magenta);
            break;
        }
    }
}

void UiManager::positionBattleBack(){ //pos background
    MenuLeft.setTexture(squareTex);
    MenuLeft.setColor(sf::Color(25,25,25));
    MenuLeft.setScale(sf::Vector2f(2.f,3.0f));
    MenuLeft.setPosition(sf::Vector2f(0.f,730.f));

    MenuRight.setTexture(squareTex);
    MenuRight.setColor(sf::Color(25,25,25,170));
    MenuRight.setScale(sf::Vector2f(7.0f,3.0f));
    MenuRight.setPosition(sf::Vector2f(400.f,730.f));
}

void UiManager::positionBattleEnemy() {
    syncEnemyList();
    float defaultHeight = 150.f;

    // Define fixed positions for enemies
    std::vector<sf::Vector2f> enemyPositions = {
        {850.f, defaultHeight}, // Middle
        {550.f, defaultHeight}, // Left
        {1150.f, defaultHeight} // Right
    };

    for (size_t i = 0; i < enemySprites.size(); i++) {
        if (enemySprites[i] == nullptr) {
            continue; // Skip null pointers
        }

        // Position the sprite
        enemySprites[i]->characterSprite.setPosition(enemyPositions[i % enemyPositions.size()]);
        enemySprites[i]->characterSprite.setScale(sf::Vector2f(10.f, 10.f));

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

void UiManager::syncEnemyList() {
    /*
    // Ensure `enemySprites` matches `EnemyList` size
    for (size_t i = 0; i < battleManager->EnemyList.size(); i++) {
        auto* enemy = battleManager->EnemyList[i];

        if (i >= enemySprites.size()) {
            // Add new sprite for the new enemy
            if (enemy != nullptr) {
                enemySprites.push_back(new characterSpriteLoader(enemy->get_name() + enemy->get_expectedFileSize()));
            } else {
                enemySprites.push_back(nullptr); // No enemy at this slot
            }
        }

        if (enemy == nullptr && enemySprites[i] != nullptr) {
            // Mark the sprite as invisible for removed enemies
            for (size_t j = 0; j < enemySprites[i]->characterLimbSprites.size(); j++) {
                enemySprites[i]->characterLimbSprites[j]->setColor(sf::Color(0, 0, 0, 0));
            }
        }
    }

    // Resize `enemySprites` to match `EnemyList` exactly
    if (enemySprites.size() > battleManager->EnemyList.size()) {
        enemySprites.resize(battleManager->EnemyList.size());
    } */
}




void UiManager::cleanupCharSprites() {
    for (size_t i = 0; i < enemySprites.size(); i++){
        bool isId = false;
        for (size_t j = 0; j < battleManager->EnemyList.size(); j++){
            if (battleManager->EnemyList[j]->get_enemyId() == i+1){
                isId = true;
            }
        }

        if (!isId){
            enemySprites[i]->set_isActive(false);
            for (size_t k = 0; k < enemySprites[i]->characterLimbSprites.size(); k++) {
                enemySprites[i]->characterLimbSprites[k]->setColor(sf::Color(0, 0, 0, 0));
            }
        }
    }
}
