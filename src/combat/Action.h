#ifndef ACTION_H
#define ACTION_H

class Skill;
class Character;

struct Action {
    Character* source;
    Character* target;
    Skill* skill;
    
    Action(Character* s, Character* t, Skill* sk);
};

#endif