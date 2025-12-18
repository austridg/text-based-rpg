#pragma once

struct Stats {
    int level;

    float hp; float maxHp;
    float resource; float maxResource;

    float attack; float maxAttack; 
    float defense; float maxDefense;
    float magic;  float maxMagic;
    float resistance; float maxResistance;
};

enum class ResourceType { Mana, Stamina};