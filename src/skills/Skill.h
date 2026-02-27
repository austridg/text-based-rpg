#ifndef SKILL_H
#define SKILL_H

#include "../Terminal.h"
#include <string>

enum class TargetType { SELF, ONE_ALLY, ALL_ALLIES, ONE_ENEMY, ALL_ENEMIES };

class Character;

class Skill {
  protected:
	std::string name;
	bool isMagic;
	bool isDmg;
	float points;
	float cost;
	TargetType targetType;

  public:
	// constructor / destructor
	Skill(std::string n, bool magic, bool dmg, float p, float c, TargetType tt);
	virtual ~Skill();

	// getters
	std::string getName() const;
	bool getIsMagic() const;
	float getPoints() const;
	float getCost() const;
	TargetType getTargetType() const;
	terminal::Color getSkillColor() const;

	bool canUse(Character* source);

	virtual void useSkill(Character* source, Character* target) = 0;
};

class BuffAtk : public Skill {
  public:
	BuffAtk(std::string n, bool magic, bool dmg, float p, float c,
			TargetType tt);

	void useSkill(Character* source, Character* target) override;
};

class BuffDef : public Skill {
  public:
	BuffDef(std::string n, bool magic, bool dmg, float p, float c,
			TargetType tt);

	void useSkill(Character* source, Character* target) override;
};

class DebuffRes : public Skill {
  public:
	DebuffRes(std::string n, bool magic, bool dmg, float p, float c,
			  TargetType tt);

	void useSkill(Character* source, Character* target) override;
};

class DamageHp : public Skill {
  public:
	DamageHp(std::string n, bool magic, bool dmg, float p, float c,
			 TargetType tt);

	void useSkill(Character* source, Character* target) override;
};

class HealHp : public Skill {
  public:
	HealHp(std::string n, bool magic, bool dmg, float p, float c,
		   TargetType tt);

	void useSkill(Character* source, Character* target) override;
};

#endif
