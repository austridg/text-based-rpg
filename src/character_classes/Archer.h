#ifndef ARCHER_H
#define ARCHER_H

#include "../character/Character.h"

class Archer : public Character {
  public:
	Archer(const std::string& n, int lvl);

	void setHpStat() override;
	void setResourceStat() override;
	void setAtkStat() override;
	void setDefStat() override;
	void setMagicStat() override;
	void setResistanceStat() override;

	void printClass() const override;
};

#endif
