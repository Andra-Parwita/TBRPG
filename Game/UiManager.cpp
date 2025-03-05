#include "UiManager.hpp"

UiManager::UiManager(){
    if (!gameFont.loadFromFile("./Sprites/PixelGameFont.ttf")){
        std::cout << "Cannot load Font" << std::endl;
    }
    if (!squareTex.loadFromFile("./Sprites/Square.png")){
        std::cout << "Cannot load Square Tex" << std::endl;
    }
    animationPlaying = false;
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
    animationPlaying = false;
}

UiManager::~UiManager(){
    for (auto spriteLoader : enemySprites) {
        delete spriteLoader;  // Make sure to delete each allocated characterSpriteLoader
    }
    enemySprites.clear(); 
    std::cout << "Enemy Sprites cleared" << std::endl;

    charSprites.clear(); 
    std::cout << "Charsprites Cleared" << std::endl; 

    for (auto EnemyMenu : EnemySelectMenu) {
        delete EnemyMenu;  
    }
    EnemySelectMenu.clear();
    std::cout << "EnemySelect Cleared" << std::endl;

    for (auto SkillMenu : SkillSelectMenu) {
        delete SkillMenu;  
    }
    SkillSelectMenu.clear();
    std::cout << "SkillMenu Cleared" << std::endl;

    for (auto Items : ItemSelectMenu) {
        delete Items;  
    }
    ItemSelectMenu.clear();
    std::cout << "ItemMenu Cleared" << std::endl;

    for (auto TurnOrderText : CharTurnOrderText) {
        delete TurnOrderText;  
    }
    CharTurnOrderText.clear();
    std::cout << "TurnOrder Cleared" << std::endl;

    for (auto HpIndicator : charHpIndicator) {
        delete HpIndicator;  
    }
    charHpIndicator.clear();
    std::cout << "HP Indicator Cleared" << std::endl;

    //non vector
    /* if (MainSelectMenu != nullptr) {
        std::cout << "Main test Clearing: "  << MainSelectMenu << std::endl;
        delete MainSelectMenu;
        MainSelectMenu = nullptr;  // Avoid dangling pointer
        std::cout << "Main Select Menu Cleared" << std::endl;
    } 

    if (MainSelectText != nullptr) {
        std::cout << "Main selec Clearing: "  << MainSelectText << std::endl;
        delete MainSelectText;
        MainSelectText = nullptr;
        std::cout << "Main Select Text Cleared" << std::endl;
    } 

    if (EnemyLimbSelectMenu != nullptr) {
        std::cout << "Limbs Clearing: "  << EnemyLimbSelectMenu << std::endl;
        delete EnemyLimbSelectMenu;
        EnemyLimbSelectMenu = nullptr;
        std::cout << "Enemy Limbs Cleared" << std::endl;
    }

    if (CharStatsText != nullptr) {
        std::cout << "stats Clearing: "  << CharStatsText << std::endl;
        delete CharStatsText;
        CharStatsText = nullptr;
        std::cout << "Char Stats Cleared" << std::endl;
    }

    if (dmgIndicator != nullptr) {
        std::cout << "dmg Clearing: "  << dmgIndicator << std::endl;
        delete dmgIndicator;
        dmgIndicator = nullptr;
        std::cout << "Dmg Indicator Cleared" << std::endl;
    }

    if (accuracyIndicator != nullptr) {
        std::cout << "acc Clearing: "  << accuracyIndicator << std::endl;
        delete accuracyIndicator;
        accuracyIndicator = nullptr;
        std::cout << "Acc Indicator Cleared" << std::endl;
    } */

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

    MainSelectText[0].setPosition(sf::Vector2f(80.f,885.f));
    MainSelectText[0].setString("Skill");
    MainSelectText[1].setPosition(sf::Vector2f(180.f,785.f));
    MainSelectText[1].setString("Item");
    MainSelectText[2].setPosition(sf::Vector2f(260.f,885.f));
    MainSelectText[2].setString("Attack");
    MainSelectText[3].setPosition(sf::Vector2f(180.f,985.f));
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
        TotalHp[i]->setPosition(sf::Vector2f(480+300.f*i, 850.f));
        TotalHp[i]->setString("       "+ currentParty->members[i]->get_name() + 
        "\n\nHP: "+ std::to_string(currentParty->members[i]->get_Hp()) + "/" 
        + std::to_string(currentParty->members[i]->get_MaxHp()));

        charHpIndicator.push_back(new characterSpriteLoader("Man"));
        charHpIndicator[i]->characterSprite.setPosition(TotalHp[i]->getPosition().x - 100.f, 880.f);
        charHpIndicator[i]->initLimbSprites(6, 3.f);

        HealthBar.push_back(new sf::RectangleShape);
        HealthBar[i]->setPosition(TotalHp[i]->getPosition());
        HealthBar[i]->move(sf::Vector2f(-10.f,45.f));
        HealthBar[i]->setFillColor(sf::Color::Red);
        HealthBar[i]->setSize(defaultHpBarSize);
    }
    accuracyIndicator = new sf::Text;
    accuracyIndicator->setFont(gameFont);
    accuracyIndicator->setOutlineThickness(2.f);
    accuracyIndicator->setCharacterSize(20);

    dmgIndicator = new sf::Text;
    dmgIndicator->setFont(gameFont);
    dmgIndicator->setOutlineThickness(2.f);
    dmgIndicator->setCharacterSize(24);
    
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
    std::ostringstream oss;

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

        for (int i = 0; i < battleManager->EnemyList[currentEnemySelection]->limbs.size(); i++){
            if(battleManager->EnemyList[currentEnemySelection]->limbs[i]->getHp() < battleManager->EnemyList[currentEnemySelection]->limbs[i]->getMaxHp()){
                float temp = static_cast<float>(battleManager->EnemyList[currentEnemySelection]->limbs[i]->getHp())/static_cast<float>(battleManager->EnemyList[currentEnemySelection]->limbs[i]->getMaxHp());

                int red = static_cast<int>(255 * (1 - temp));  // Red decreases as HP increases
                int green = static_cast<int>(255 * temp);      // Green increases as HP increases

                EnemyLimbSelectMenu->characterLimbSprites[i]->setColor(sf::Color(red, green, 0));
            }
        }
        EnemyLimbSelectMenu->characterLimbSprites[selectedId]->setColor(sf::Color(0,255,255,200)); 



        accuracyIndicator->setPosition(enemySprites[currentEnemySelection]->characterLimbSprites[selectedId]->getPosition());
        if (selectedId == 0 || selectedId == 1){
            accuracyIndicator->move(20.f,40.f); //offset
        } else {
            accuracyIndicator->move(0.f,20.f); //offset
        }
        oss << std::fixed << std::setprecision(1) << battleManager->EnemyList[currentEnemySelection]->limbs[selectedId]->getlimbHitChance() * 100;
        accuracyIndicator->setString(oss.str() + "%");

        break;

    default:
        break;
    }
}


void UiManager::update_Sprites() {
    cleanupCharSprites();
    for (auto chars : charSprites){
        chars->idleAnimate();
    }

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
    float spHeight = 600.f;
    for (int i = 0; i < charSprites.size(); i++){
        
        charSprites[i]->characterSprite.setScale(sf::Vector2f(8.f,8.f));
        charSprites[i]->characterSprite.setPosition(sf::Vector2f(400 + 300.f * i,spHeight));
    }
}

void UiManager::positionBattleBack(){ //pos background
    MenuLeft.setTexture(squareTex);
    MenuLeft.setColor(sf::Color(25,25,25));
    MenuLeft.setScale(sf::Vector2f(2.f,4.0f));
    MenuLeft.setPosition(sf::Vector2f(0.f,730.f));

    MenuRight.setTexture(squareTex);
    MenuRight.setColor(sf::Color(25,25,25,170));
    MenuRight.setScale(sf::Vector2f(10.0f,4.0f));
    MenuRight.setPosition(sf::Vector2f(400.f,830.f));
}

void UiManager::positionBattleEnemy() {
    syncEnemyList();
    float defaultHeight = 250.f;

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

void UiManager::dmgPopupAnimation(sf::RenderWindow* window) {
    // Start the animation only if it's not already playing
    if (!animationPlaying) {
        animationPlaying = true;
        aniClock.restart();  // Reset the animation clock

        sf::Vector2f enemyPos = enemySprites[currentEnemySelection]->characterSprite.getPosition();
        dmgIndicator->setPosition(enemyPos.x + 130, enemyPos.y-10);  
        dmgIndicator->setString(battleManager->attackOutcome); 
        dmgIndicator->setFillColor(sf::Color::Red);
    }

    // Update the popup animation over time
    float elapsedTime = aniClock.getElapsedTime().asSeconds();
    if (elapsedTime < 1.f) {  // Animation duration (1 second)
        // Move the damage text upwards
        dmgIndicator->move(0.f, -0.5f);  // Adjust the speed of movement

        // Fade out the text
        int alpha = static_cast<int>(255 - (255 * elapsedTime));  // Fade over time
        dmgIndicator->setFillColor(sf::Color(255, 0, 0, alpha));

        // Draw the damage text
        window->draw(*dmgIndicator);
    } else {
        // Once the animation is done, make the text invisible and stop the animation
        dmgIndicator->setFillColor(sf::Color(0, 0, 0, 0));  // Make the text invisible when done
        animationPlaying = false;  // End the animation
        battleManager->attacked = false;
    }
}
