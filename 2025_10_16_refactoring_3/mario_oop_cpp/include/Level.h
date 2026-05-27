#pragma once

#include "GameObject.h"
#include "Map.h"

#include <vector>
#include <memory>
#include <algorithm>

// ============================================================
//  class Level — главный менеджер игры
//  Хранит все объекты (кирпичи, враги, монеты, Марио),
//  загружает уровни, управляет игровым циклом (update/draw).
// ============================================================
class Level {
public:
    std::vector<std::unique_ptr<Brick>>      bricks;   // статичные кирпичи и платформы
    std::vector<std::unique_ptr<GameObject>> entities; // движущиеся объекты: враги, монеты
    Mario mario;              // объект игрока
    int   levelNum  = 1;      // номер текущего уровня
    int   score     = 0;      // счёт игрока
    int   maxLevel  = 3;      // количество уровней всего
    bool  needReload = false; // флаг: перезагрузить уровень (смерть игрока)
    bool  nextLevel  = false; // флаг: перейти на следующий уровень

    // Создаёт кирпич любого типа и добавляет в вектор bricks.
    // Возвращает сырой указатель на созданный объект.
    template<typename T, typename... Args>
    T* addBrick(Args&&... args) {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = ptr.get();
        bricks.push_back(std::move(ptr));
        return raw;
    }

    // Создаёт движущийся объект (Enemy, Coin) и добавляет в entities.
    template<typename T, typename... Args>
    T* addEntity(Args&&... args) {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = ptr.get();
        entities.push_back(std::move(ptr));
        return raw;
    }

    // Сдвигает всю карту на dx символов по горизонтали (скроллинг).
    // Вместо того чтобы двигать Марио — двигаем весь мир вокруг него.
    void scrollMap(float dx);

    // Загружает уровень с номером lvl: очищает объекты, создаёт новые
    void load(int lvl);

    // Вызывается при гибели Марио: красный экран, пауза, перезагрузка
    void playerDead();

    // Переходит на следующий уровень: зелёный экран, пауза, загрузка
    void goNextLevel();

    // Удаляет из entities все объекты с флагом markedForDelete
    void purgeEntities();

    // Главный тик: обновляет всех участников игры за один кадр
    void update();

    // Рисует все объекты уровня на буфере экрана
    void draw(Map& map);
};
