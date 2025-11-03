#pragma once

struct Stat {
    float current;
    float max;

    Stat() : current(1), max(99) {}
};

Stat Attack;
Stat Defense;
Stat Magic;