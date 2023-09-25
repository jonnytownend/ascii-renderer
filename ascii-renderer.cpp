#include <cmath>

#include "src/game.h"

class Renderer {

    int width, height;

    float shader(int x, int y) {
        Vector uv;
        uv.x = ((float)x - ((float)width / 2.0)) / (float)width;
        uv.y = ((float)y - ((float)height / 2.0)) / (float)height;
        float xOut = pow(uv.x, 2.);
        float yOut = pow(uv.y, 2.);
        return xOut + yOut;
    }

    string toAscii(float x) {
        int index = (int)(x * ASCII_CHARS.length());
        return string() + " " + ASCII_CHARS[index];
    }

    public:
    Renderer(int width, int height) {
        this->width = width;
        this->height = height;
    }

    void render() {
        system("clear");
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                std::cout << toAscii(shader(j, i));
            }
            std::cout << std::endl;
        }
    }
};

// int main() {
//     Renderer renderer = Renderer(80, 80);
//     while (true) {
//         renderer.render();
//         usleep(7000);
//     }
//     return 0;
// }

int main() {
    Game game = Game();
    while (true) {
        game.update();
        game.render();
        usleep(7000);
    }
    return 0;
}