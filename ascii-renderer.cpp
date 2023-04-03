#include <string>
#include <iostream>
#include <cmath>
#include <unistd.h>
#include <stdlib.h>

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
        switch(texture) {
            case 0:
                return "x";
            case 1:
                return ".";
            case 2:
                return "@";
            case 3:
                return "^";
            case 4:
                return "O";
            default:
                return "x";
        }
    }
};

float getRandom(float max) {
    const int mult = 10000;
    return max * (rand() % mult / (float(mult)));
}

class Game {
    int width = 100;
    int height = 100;

    static const int N = 100;
    Circle balls[N];

    std::string getTile(int x, int y) {
        if (x == 0 || x == width - 1) {
            return "|";
        } else if (y == 0 || y == height - 1) {
            return " -";
        }

        for (int i=0; i<N; i++) {
            if (checkCirclePosition(balls[i], x, y)) {
                string a = " ";
                string b = balls[i].charFromTexture();
                return a + b;
            }
        }

        return "  ";
    }

    bool checkPosition(Entity entity, int x, int y) {
        return (int)entity.position.x == x && (int)entity.position.y == y;
    }

    bool checkCirclePosition(Circle circle, int x, int y) {
        float distX = (float)x - circle.position.x;
        float distY = (float)y - circle.position.y;
        float dist = sqrt(pow(distX, 2.0) + pow(distY, 2.0));
        return (dist - circle.radius) < 0;
    }

    public:
    Game() {
        initializeBalls();
    }

    void initializeBalls() {
        const int mult = 10000;
        for (int i=0; i<N; i++) {
            balls[i].position.x = getRandom((float)width);
            balls[i].position.y = getRandom((float)height);
            
            balls[i].velocity.x = getRandom(6) - 3;
            balls[i].velocity.y = getRandom(6) - 3;

            balls[i].bounce = 0.9 + getRandom(0.09);
            balls[i].drag = 0.999;

            balls[i].radius = 1.0 + getRandom(3);
            balls[i].texture = rand() % 5;
        }
    }

    void update() {
        for (int i=0; i<N; i++) {
            Circle &entity = balls[i];
            entity.position.x += entity.velocity.x;
            entity.position.y += entity.velocity.y;

            int posX = (int) entity.position.x;
            int posY = (int) entity.position.y;
            int rad = (int) entity.radius;

            if (posX - rad < 1) {
                entity.position.x = rad + 1;
                entity.velocity.x *= -entity.bounce;
            } else if (posX + rad > width - 1) {
                entity.position.x = width - rad - 1;
                entity.velocity.x *= -entity.bounce;
            }

            if (posY - rad < 1) {
                entity.position.y = rad + 1;
                entity.velocity.y *= -entity.bounce;
            } else if (posY + rad > height - 1) {
                entity.position.y = height - rad - 1;
                entity.velocity.y *= -entity.bounce;

                // Random jump
                if (getRandom(1) < 0.005) {
                    entity.velocity.y = -6;
                }
            }

            // Gravity
            entity.velocity.y += 0.5;

            entity.velocity.x *= entity.drag;
            entity.velocity.y *= entity.drag;
        }
    }

    void render() {
        system("clear");
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                std::cout << getTile(j, i);
            }
            std::cout << std::endl;
        }
    }
};

const float FRAME_RATE = 30.0;

int main() {
    Game game = Game();
    while (true) {
        game.update();
        game.render();
        usleep(7000);
    }
    return 0;
}