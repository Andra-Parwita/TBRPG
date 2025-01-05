# TBRPG
V0.1.1
reorganised and more ui and polished up some segmentation faults. Made ui manager less dependent on BattleManager  

Done:  
- Speedchecking for turns  
- Basic Battle UI for atk  
- Enemy and Limb Selection  
- loading sprite types  
- Placeholder for limbs and enemy  
- early character sprites  
- enemy base atk and atk to enemy

Plans:  

UI  
- Battle UI  
- Main Menu  
- Inventory system  
- Party Info  
- Map  

- Mouse Input


Combat:  
- character down / death chance ~  
- crits ~ for when weakness for weapon and armour types are implemented  
- skills (class dependent)  
- fleeing  

- enemy types (location dependent)
- fixing enemy limb rendering for 64x64 sprites  
- enemy difficulty types (based on enemy class type)  
- Combat Animations
- Enemy Waves / hordes
- multi limbed enemies (do last or remove)  

Party:  
- classes  
- level and experience  
- skills based on class type  
- talking?  
- rest & fatigue / stamina  
- trust?  

Equipment:  
- consumables  
- armour types   
- weapon types (damage type)  
- inventory  
- equipping weapons and armour on chars  


Overworld movement:  
- movement  
- combat encounters  
- party following  
- map & locations  
- shop & main hub  

- random encounters in travel  
- party rest area  (overworld in dungeon)  

- dungeon enemies  

- quests  
- bosses  
- stealth? (enemy view cone?)  
- fogOfwar?


dungeon generation:  
- random rooms  
- loot chests  
- enemy drops    

Misc:  
- MC  
- saves (only at rest locations)  


g++ -std=c++11 main.cpp game.cpp player.cpp Character/party.cpp Character/limb.cpp Character/character.cpp Character/enemy.cpp battleManager.cpp UiManager.cpp Character/characterSpriteLoader.cpp Character/enemyClasses/skeleton.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio