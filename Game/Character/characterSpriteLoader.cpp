#include "characterSpriteLoader.hpp"

characterSpriteLoader::characterSpriteLoader(){
    fileSizeType = 32;
    scaleFactor = 1;
    textureHeight = fileSizeType;
    textureWidth = fileSizeType;
    textureLeft = 0;
    if (!characterTexture.loadFromFile("./Sprites/ManSheet.png")){
        std::cout << "Cannot load char Tex" << std::endl;
    }
    characterSprite.setTexture(characterTexture);
}

characterSpriteLoader::characterSpriteLoader(std::string fileName){
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
    filePath = "./Sprites/" + fileName + ".png";
    if (!characterTexture.loadFromFile(filePath)){
        std::cout << "Cannot load char Tex" << std::endl;
        if (!characterTexture.loadFromFile("./Sprites/ManSheet.png")){
            std::cout << "Cannot load backup char Tex" << std::endl;
        } else {
            std::cout << "Loaded: " << fileName << " as Man Sheet" << std::endl;
            filePath = "./Sprites/ManSheet.png";
        } 
    } else {
        std::cout << "Loaded: " << fileName << std::endl;
    }
    characterSprite.setTexture(characterTexture);
}

characterSpriteLoader::~characterSpriteLoader(){
    for (auto limbSprite : characterLimbSprites) {
        delete limbSprite;
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
            }
            characterLimbSprites[i]->setTextureRect(sf::Rect<int>({12, 0}, {11, 11}));
            characterLimbSprites[i]->move(0*scaleFactor+offset,0*scaleFactor);
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
