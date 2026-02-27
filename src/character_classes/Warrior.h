#ifndef WARRIOR_H
#define WARRIOR_H

#include "../character/Character.h"

class Warrior : public Character {
  public:
	Warrior(const std::string& n, int lvl);

	void setHpStat() override;
	void setResourceStat() override;
	void setAtkStat() override;
	void setDefStat() override;
	void setMagicStat() override;
	void setResistanceStat() override;

	void printClass() const override;
};

#endif
