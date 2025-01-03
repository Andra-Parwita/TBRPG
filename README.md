# TBRPG
Plans:

Combat
- character down / death chance ~
- crits ~ for when weakness for weapon and armour types are implemented
- skills
- fleeing

- enemy types
- fixing enemy limb rendering for 64x64 sprites
- multi limbed enemies (do last or remove)
- enemy difficulty types (based on enemy class type)

Party
- classes
- level and experience
- skills based on class type
- talking?
- rest & fatigue

Equipment 
- consumables
- armour types 
- weapon types (damage type)
- inventory
- equipping

Overworld movement
- movement
- combat encounters
- party following
- map & locations

dungeon generation
- random rooms

- saves


g++ -std=c++11 main.cpp game.cpp player.cpp Character/party.cpp Character/limb.cpp Character/character.cpp Character/enemy.cpp battleManager.cpp UiManager.cpp Character/characterSpriteLoader.cpp Character/enemyClasses/skeleton.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio