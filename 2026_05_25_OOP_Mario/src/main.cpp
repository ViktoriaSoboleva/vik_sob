#include "Level.hpp"
#include "Map.hpp"

#include <windows.h>

// TODO
// 1. Rename Level to GameController
// 2. LevelController.load use switch among if-else
// 3. GameObject module split into modules for each class

int main() {
    Level level;
    level.load(1);

    Map map;

    while (GetKeyState(VK_ESCAPE) >= 0) {
        map.clear();
        level.update();
        level.draw(map);
        map.render();
        Sleep(5);
    }

    return 0;
}
