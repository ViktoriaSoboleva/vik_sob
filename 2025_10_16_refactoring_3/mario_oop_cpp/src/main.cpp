#include "Level.h"
#include "Map.h"

#include <windows.h>  // GetKeyState, Sleep

// ============================================================
//  main — точка входа программы
// ============================================================
int main() {
    Level lvl;
    lvl.load(1);

    Map map;

    // Главный игровой цикл: работает пока не нажат Escape
    while (GetKeyState(VK_ESCAPE) >= 0) {
        map.clear();
        lvl.update();
        lvl.draw(map);
        map.render();
        Sleep(10); // ~100 кадров в секунду
    }

    return 0;
}
