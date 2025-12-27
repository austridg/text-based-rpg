#include "DamageHp.h"
#include "../character/Character.h"
#include "../Terminal.h"

DamageHp::DamageHp(std::string n, bool magic, bool dmg, float p, float c, TargetType tt)
    : Skill(n,magic,dmg,p,c,tt) {}

void DamageHp::useSkill(Character* source, Character* target) {
    float dmgStat = (isMagic) ? source->getMagic() : source->getAtk();
    float dmgPoints;

    dmgPoints = target->getIsDefending() ? (dmgStat*0.2) * points - target->getDef()*1.5 : (dmgStat*0.2) * points - target->getDef();

    target->setHp(target->getHp() - dmgPoints);
    if (target->getHp() < 0) { target->setHp(0); }
    std::cout << terminal::foreground(target->getHealthColor()) << target->getName() << terminal::reset << " lost " << ((isMagic) ? terminal::foreground(terminal::brightBlue) : terminal::foreground(terminal::brightRed)) << dmgPoints << terminal::reset << " HP!\n";
}