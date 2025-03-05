#include "characterSpriteLoader.hpp"

characterSpriteLoader::characterSpriteLoader(){
    isActive = true;
    fileSizeType = 32;
    scaleFactor = 1;
    textureHeight = fileSizeType;
    textureWidth = fileSizeType;
    textureLeft = 0;
    if (!characterTexture.loadFromFile("./Sprites/ManSheet.png")){
        std::cout << "Cannot load char Tex" << std::endl;
    }
    characterSprite.setTexture(characterTexture);
    animated = false;
}

characterSpriteLoader::characterSpriteLoader(std::string fileName){
    animated = true;
    isActive = true;
    fileSizeType = 32;
    if (fileName.size() >= 2){
        std::string temp = fileName.substr(fileName.size()-2);
        if (temp == "64"){
            fileSizeType = 64;
        }
    }
    scaleFactor = 1;
    textureHeight = fileSizeType;
    textureWidth = fileSizeType;
    textureLeft = 0;
    filePath = "./Sprites/" + fileName + "Ani.png";
    if (!characterTexture.loadFromFile(filePath)){
        std::cout << "No animated File, finding default..." << std::endl;
        filePath = "./Sprites/" + fileName + ".png";
        animated = false;
        if (!characterTexture.loadFromFile(filePath)){
            std::cout << "Cannot load char Tex" << std::endl;
            if (!characterTexture.loadFromFile("./Sprites/ManSheet.png")){
                std::cout << "Cannot load backup char Tex" << std::endl;
            } else {
                std::cout << "Loaded: " << fileName << " as Man Sheet" << std::endl;
                filePath = "./Sprites/ManSheet.png";
            } 
        }
    } else {
        std::cout << "Loaded: " << fileName << std::endl;
    }
    characterSprite.setTexture(characterTexture);
    if (animated){
        characterSprite.setTextureRect(sf::Rect<int>({0,0},{fileSizeType,fileSizeType}));
    }
}

characterSpriteLoader::~characterSpriteLoader(){
    for (auto limbSprite : characterLimbSprites) {
        delete limbSprite;
        limbSprite = nullptr;
    }
    characterLimbSprites.clear();
}

void characterSpriteLoader::initLimbSprites(int limbNum, int NscaleFactor){
    scaleFactor = NscaleFactor;
    if (fileSizeType > 32){
        scaleFactor = scaleFactor/2;
    }
    int offset = 12*scaleFactor;
    if (characterLimbSprites.size() < limbNum) {
        characterLimbSprites.resize(limbNum);
    }
    for (int i = 0; i < limbNum; i++){
        if (characterLimbSprites[i] == nullptr) {
            characterLimbSprites[i] = new sf::Sprite;
        }
        characterLimbSprites[i]->setTexture(this->characterTexture);
        characterLimbSprites[i]->setPosition(this->characterSprite.getPosition());
        characterLimbSprites[i]->setScale(scaleFactor, scaleFactor);
        switch (i)
        {
        case 0: //head
            if (fileSizeType > 32){
                characterLimbSprites[i]->setTextureRect(sf::Rect<int>({12, 0}, {11, 11}));
                characterLimbSprites[i]->move(0*scaleFactor+offset,0*scaleFactor);
            } else {
                characterLimbSprites[i]->setTextureRect(sf::Rect<int>({12, 0}, {11, 11}));
                characterLimbSprites[i]->move(0*scaleFactor+offset,0*scaleFactor);
            }
            break;
        case 1: //torso
            characterLimbSprites[i]->setTextureRect(sf::Rect<int>({12, 11}, {9, 12}));
            characterLimbSprites[i]->move(0*scaleFactor+offset,11*scaleFactor);
            break;
        case 2: //L arm
            characterLimbSprites[i]->setTextureRect(sf::Rect<int>({9, 11}, {4, 12}));
            characterLimbSprites[i]->move(-3*scaleFactor+offset,11*scaleFactor);
            break;
        case 3: //R arm 
            characterLimbSprites[i]->setTextureRect(sf::Rect<int>({20, 11}, {4, 12}));
            characterLimbSprites[i]->move(8*scaleFactor+offset, 11*scaleFactor);
            break;
        case 4: // L leg
            characterLimbSprites[i]->setTextureRect(sf::Rect<int>({12, 22}, {5, 10}));
            characterLimbSprites[i]->move(0*scaleFactor+offset, 23*scaleFactor);
            break;
        case 5: //R leg
            characterLimbSprites[i]->setTextureRect(sf::Rect<int>({16, 22}, {5, 10}));
            characterLimbSprites[i]->move(4*scaleFactor+offset, 23*scaleFactor);
            break;
        default:
            break;
        }
    }
} 

void characterSpriteLoader::loadSprite(std::string fileName){
    fileSizeType = 32;
    if (fileName.size() >=2){
        std::string temp = fileName.substr(fileName.size()-2);
        if (temp == "64"){
            fileSizeType = 64;
        }
    } 
    filePath = "./Sprites/" + fileName + ".png";
    if (!characterTexture.loadFromFile(filePath)){
        std::cout << "Cannot load char Tex" << std::endl;
    }
    characterSprite.setTexture(characterTexture);
}

void characterSpriteLoader::updateSprite(int limbId){ //for damage models
    if (limbId >= 0 && limbId < characterLimbSprites.size() && characterLimbSprites[limbId] != nullptr){
        if (characterLimbSprites[limbId]->getTextureRect().top < fileSizeType ){
            int height = characterLimbSprites[limbId]->getTextureRect().height;
            int width =characterLimbSprites[limbId]->getTextureRect().width;
            int left = characterLimbSprites[limbId]->getTextureRect().left;
            int newTop = characterLimbSprites[limbId]->getTextureRect().top + fileSizeType;
            characterLimbSprites[limbId]->setTextureRect(sf::Rect<int>({left,newTop},{width,height}));
        }
    } else {
        std::cerr << "Invalid limbId or uninitialized sprite!" << std::endl; 
    }
}

bool characterSpriteLoader::get_isActive(){
    return isActive;
}

void characterSpriteLoader::set_isActive(bool Nbool){
    isActive = Nbool;
}

void characterSpriteLoader::idleAnimate(){
    if (animated){
        if (idleClock.getElapsedTime().asSeconds() > 0.25){
            int left = characterSprite.getTextureRect().left + fileSizeType;
            if (left >= fileSizeType*4){
                left = 0;
            }
            int width = characterSprite.getTextureRect().width;
            int height = characterSprite.getTextureRect().height;
            int top = characterSprite.getTextureRect().top;
            characterSprite.setTextureRect(sf::Rect<int>({left,top},{width,height}));
            idleClock.restart();
        }
    }

}
