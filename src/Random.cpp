#include <random>

static std::mt19937_64 random_engine(std::random_device{}());

int randNumber(int min,int max) {
    return std::uniform_int_distribution<int>(min,max)(random_engine);
}