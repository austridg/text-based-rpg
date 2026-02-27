#ifndef BOSS_H
#define BOSS_H

#include "../character/Character.h"

class Boss : public Character {
  public:
	Boss(const std::string& n, int lvl);

	void setHpStat() override;
	void setResourceStat() override;
	void setAtkStat() override;
	void setDefStat() override;
	void setMagicStat() override;
	void setResistanceStat() override;

	void printClass() const override;
};

#endif
