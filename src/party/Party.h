#ifndef PARTY_H
#define PARTY_H

#include "../character/Character.h"
#include <iostream>

class Party {
  private:
	std::vector<Character*> party;

  public:
	Party() = default;

	Party(std::vector<Character*> members);

	std::vector<Character*> getParty() const;

	Character* operator[](int index) const;

	size_t getPartySize() const;

	void printPartyInfo() const;

	void insertMember(Character* member);

	void removeMember(int index);

	void healParty();

	bool getIsAlive() const;
};

#endif
