#ifndef CHARACTERSPRITELOADER_CPP
#define CHARACTERSPRITELOADER_CPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

class characterSpriteLoader
{
private:
    std::string filePath;
    sf::Texture characterTexture;
    int textureHeight;
    int textureWidth;
    int textureLeft;
    int scaleFactor;
    int fileSizeType; //dimensons of file, eg 32x32, 64x64
public:
    std::vector<sf::Sprite*> characterLimbSprites;
    sf::Sprite characterSprite;

    characterSpriteLoader();
    characterSpriteLoader(std::string);
    ~characterSpriteLoader();

    void initLimbSprites(int, int);
    void loadSprite(std::string);
    void updateSprite(int limbId);
};




#endif