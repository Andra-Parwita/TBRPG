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
    sf::Texture characterAniTexture;
    int textureHeight;
    int textureWidth;
    int textureLeft;
    int scaleFactor;
    int fileSizeType; //dimensons of file, eg 32x32, 64x64
    bool animated;
    bool isActive;
    sf::Clock idleClock;
public:
    std::vector<sf::Sprite*> characterLimbSprites;
    sf::Sprite characterSprite;

    characterSpriteLoader();
    characterSpriteLoader(std::string);
    ~characterSpriteLoader();

    void initLimbSprites(int, int);
    void loadSprite(std::string);
    void updateSprite(int limbId);

    void set_isActive(bool);
    bool get_isActive();
    void idleAnimate();
};




#endif