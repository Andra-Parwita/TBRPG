# Compiler and Flags
COMPILER = g++
FLAGS = -std=c++11 -I/opt/homebrew/Cellar/sfml/2.6.1/include
INCLUDE = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files
FILES = main.cpp \
        game.cpp \
        player.cpp \
        Character/party.cpp \
        Character/limb.cpp \
        Character/character.cpp \
        Character/enemy.cpp \
        battleManager.cpp \
        UiManager.cpp \
        Character/characterSpriteLoader.cpp \
        Character/enemyClasses/skeleton.cpp \
        Character/classes/charClass.cpp \
        Character/classes/clericClass.cpp \
        Character/classes/knightClass.cpp \
        Character/classes/mageClass.cpp \
        Character/classes/roninClass.cpp \
		Character/skills/skill.cpp \
		Character/skills/fireballSkill.cpp \
        OverUiManager.cpp \

# Output binary name
OUT = a.out

# Rules
all: 
	$(COMPILER) $(FLAGS) $(FILES) -o $(OUT) $(INCLUDE)

clean:
	rm -f $(OUT)
