#include "Party.h"

Party::Party(vector<Character*> members)
    : party(members) {}

vector<Character*> Party::getParty() const { return party; }

Character* Party::operator[](int index) const {
    return party[index];
}

size_t Party::getPartySize() const { return party.size(); }

void Party::printPartyInfo() const {
    for (int i = 0; i < party.size(); i++) {
        party[i]->printInfo();
    }
}

void Party::insertMember(Character* member) {
    party.emplace_back(member);
}

void Party::removeMember(int index) {
    party.erase(party.begin() + index);
}

void Party::healParty() {
    for(int i = 0; i < party.size(); i++) {
        party[i]->fullHeal();
    }
}

bool Party::getIsAlive() const {
    for (int i = 0; i < party.size(); i++) {
        if(party[i]->getIsAlive()) { return true; }
    }
    return false;
}