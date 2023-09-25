#include <string>

using namespace std;

struct Vector {
    float x;
    float y;
};

struct Entity {
    Vector position;
    Vector velocity;
    float bounce;
    float drag;
};

struct Circle: Entity {
    float radius;
    int texture;

    string charFromTexture() {
        return string() + ASCII_CHARS[texture];
    }
};