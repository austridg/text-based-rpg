#ifndef MAGE_H
#define MAGE_H

#include "../character/Character.h"

class Mage : public Character {
  public:
	Mage(const std::string& n, int lvl);

	void setHpStat() override;
	void setResourceStat() override;
	void setAtkStat() override;
	void setDefStat() override;
	void setMagicStat() override;
	void setResistanceStat() override;

	void printClass() const override;
};

#endif
