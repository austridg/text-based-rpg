#include "Action.h"

Action::Action(Character* s, Character* t, Skill* sk)
    : source(s), target(t), skill(sk) {}