#include <cmath>

float getRandom(float max) {
    const int mult = 10000;
    return max * (rand() % mult / (float(mult)));
}