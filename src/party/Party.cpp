#include "Party.h"

Party::Party(std::vector<Character*> members)
    : party(members) {}

std::vector<Character*> Party::getParty() const { return party; }

Character* Party::operator[](int index) const {
    return party[index];
}

size_t Party::getPartySize() const { return party.size(); }

void Party::printPartyInfo() const {
    for (size_t i = 0; i < party.size(); i++) {
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
    for(size_t i = 0; i < party.size(); i++) {
        party[i]->fullHeal();
        party[i]->setIsAlive(true);
    }
}

bool Party::getIsAlive() const {
    for (size_t i = 0; i < party.size(); i++) {
        if(party[i]->getIsAlive()) { return true; }
    }
    return false;
}