#ifndef PARTY_H
#define PARTY_H

#include "character/Character.h"
#include <iostream>

class Party {
private:
    vector<Character*> party;
public:
    Party(vector<Character*> members);

    vector<Character*> getParty() const;
    
    Character* operator[](int index) const;

    size_t getPartySize() const;

    void printPartyInfo() const;

    void insertMember(Character* member);

    void removeMember(int index);

    bool getIsAlive() const;
};

#endif