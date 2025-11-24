# ====== CONFIG ======
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Isrc
TARGET := text_rpg.exe

# ====== FILES ======
# Explicitly list each .cpp file (guaranteed to work)
SRCS := \
    src/main.cpp \
    src/Game.cpp \
    src/character/Character.cpp \
    src/combat/Combat.cpp \
    src/combat/Action.cpp \
    src/skills/Skill.cpp \
    src/skills/DamageHp.cpp \
    src/skills/BuffDef.cpp \
    src/skills/SkillList.cpp \
    src/character_classes/Warrior.cpp \
    src/character_classes/Mage.cpp \
    src/character_classes/Healer.cpp \
    src/character_classes/Archer.cpp \
    src/character_classes/Enemy.cpp \
    src/character_classes/Boss.cpp \

OBJS := $(SRCS:.cpp=.o)

# ====== TARGETS ======
.PHONY: all run clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo [LINK] $@
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp
	@echo [CXX ] $<
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	@echo [CLEAN]
	del /q $(OBJS) 2>nul || true
	del /q $(TARGET) 2>nul || true

rebuild: clean all
