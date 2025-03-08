#include "OverUiManager.hpp"

OverUiManager::OverUiManager(Party* party) {
    this->currentParty = party;
    positionHistory.resize(currentParty->get_numMembers(), std::deque<sf::Vector2f>(trailLength, {0.f, 0.f}));

    for (int i = 0; i < currentParty->get_numMembers(); i++) {
        charSprites.push_back(currentParty->members[i]->spriteChibi);
        
        sf::Vector2f spriteSize = sf::Vector2f(charSprites[i]->characterSprite.getGlobalBounds().width, charSprites[i]->characterSprite.getGlobalBounds().height);
        float spacing = spriteSize.x + 10.f;
        charSprites[i]->characterSprite.setPosition(sf::Vector2f(50.f, 50.f));

        charSprites[i]->characterSprite.setTextureRect(sf::Rect<int>({0,0},{32,32}));
        charSprites[i]->characterSprite.setScale(4,4);

        positionHistory.push_back(std::deque<sf::Vector2f>(trailLength, charSprites[i]->characterSprite.getPosition()));
        textureHistory.push_back(std::deque<sf::IntRect>(trailLength, sf::IntRect(0, 0, 32, 32)));
    }
}

OverUiManager::~OverUiManager(){}

void OverUiManager::moveChar(int id, float moveX, float moveY, int directionId, sf::Vector2f bounds){
    if (id >= 0 && id < currentParty->get_numMembers()){
        if (collisionCheck(bounds,moveX,moveY,id)){
            sf::Rect<int> textureDir;

            charSprites[id]->characterSprite.move(moveX,moveY);
            switch (directionId)
            {
            case 1:
                textureDir = sf::Rect<int>({0,32},{32,32}); //up
                break;
            case 2:
                textureDir = sf::Rect<int>({0,0},{32,32}); //down
                break;
            case 3:
                textureDir = sf::Rect<int>({32,32},{32,32}); //left
                break;
            case 4:
                textureDir = sf::Rect<int>({32,0},{32,32}); //right
                break;
            default:
                break;
            }
            charSprites[id]->characterSprite.setTextureRect(textureDir);

            positionHistory[id].push_front(charSprites[id]->characterSprite.getPosition());
            textureHistory[id].push_front(textureDir);

            if (positionHistory[id].size() > trailLength) {positionHistory[id].pop_back();}
            if (textureHistory[id].size() > trailLength) {textureHistory[id].pop_back();}
        }
    }
}


void OverUiManager::followingCheck() {
    if (currentParty->get_numMembers() > 1) {
        for (int i = 1; i < currentParty->get_numMembers(); i++) {
            if (!positionHistory[i-1].empty() && positionHistory[i-1].size() > trailLength / 2) {
                charSprites[i]->characterSprite.setPosition(positionHistory[i-1][trailLength / 2]); 
                charSprites[i]->characterSprite.setTextureRect(textureHistory[i - 1][trailLength / 2]);
            }

            positionHistory[i].push_front(charSprites[i]->characterSprite.getPosition());
            textureHistory[i].push_front(charSprites[i]->characterSprite.getTextureRect());

            if (positionHistory[i].size() > trailLength) {positionHistory[i].pop_back();}
            if (textureHistory[i].size() > trailLength) {textureHistory[i].pop_back();}
        }
    }
}

bool OverUiManager::collisionCheck(sf::Vector2f bounds, float newX, float newY, int id){
    if ((charSprites[id]->characterSprite.getPosition().x + newX < bounds.x - 100) && 
    (charSprites[id]->characterSprite.getPosition().y + newY < bounds.y - 100) && 
    (charSprites[id]->characterSprite.getPosition().y + newY > 0) &&
    (charSprites[id]->characterSprite.getPosition().x + newX > 0)){
        std::cout << charSprites[id]->characterSprite.getPosition().x << " + " << bounds.x << std::endl;
        return true;
    } 
    return false;
}
