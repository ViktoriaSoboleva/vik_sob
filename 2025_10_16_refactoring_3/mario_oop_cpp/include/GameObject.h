#pragma once

#include "Map.h"

#include <vector>
#include <memory>

// Предварительное объявление: класс Level будет определён позже,
// но методы GameObject уже принимают Level& в параметрах
class Level;

// ============================================================
//  class GameObject — базовый класс для всех объектов игры
//  От него наследуются: Brick, Enemy, Coin, Mario
// ============================================================
class GameObject {
public:
    float x, y;             // позиция левого верхнего угла
    float width, height;    // размер объекта в символах
    float vertSpeed  = 0;   // вертикальная скорость (>0 — вниз, <0 — вверх)
    float horizSpeed = 0;   // горизонтальная скорость (>0 — вправо, <0 — влево)
    bool  isFlying   = false; // true — объект в воздухе
    char  cType;              // символ отображения на экране
    bool  markedForDelete = false; // true — удалить в конце тика

    // Конструктор: задаёт начальную позицию, размер и символ отображения
    GameObject(float x, 
               float y,
               float w, 
               float h, 
               char type)
               : 
                 x(x), 
                 y(y), 
                 width(w), 
                 height(h), 
                 cType(type) {}

    // Виртуальный деструктор — для корректного удаления через базовый указатель
    virtual ~GameObject() = default;

    // Проверяет пересечение двух прямоугольников (AABB-коллизия)
    bool collidesWith(const GameObject& o) const {
        return (x + width)  > o.x && x < (o.x + o.width) &&
               (y + height) > o.y && y < (o.y + o.height);
    }

    // Рисует объект на буфере экрана — заполняет прямоугольник символом cType
    void drawOn(Map& map) const {
        int ix = (int)round(x),     iy = (int)round(y);
        int iw = (int)round(width), ih = (int)round(height);
        for (int i = ix; i < ix + iw; i++)
            for (int j = iy; j < iy + ih; j++)
                map.setChar(i, j, cType);
    }

    // Применяет гравитацию и вертикальные столкновения с кирпичами.
    // Возвращает false если объект уже не существует (переход уровня).
    virtual bool applyGravity(Level& lvl);

    // Применяет горизонтальное движение и столкновения со стенами.
    virtual void applyHorizMove(Level& lvl);

    // Вызывается каждый игровой тик.
    // Подклассы переопределяют под своё поведение.
    virtual void update(Level& lvl) {}
};

// ============================================================
//  class Brick — статичный кирпич или платформа
// ============================================================
class Brick : public GameObject {
public:
    Brick(float x, float y, float w, float h, char type)
        : GameObject(x, y, w, h, type) {}
};

// ============================================================
//  class QuestionBrick — блок '?'
//  При ударе Марио снизу выдаёт монету и становится блоком '-'
// ============================================================
class QuestionBrick : public Brick {
public:
    bool used = false; // true — блок уже выбит

    QuestionBrick(float x, float y, float w, float h)
        : Brick(x, y, w, h, '?') {}

    // Вызывается из applyGravity когда Марио бьёт блок головой снизу
    void onHitFromBelow(Level& lvl);
};

// ============================================================
//  class FinishBrick — финишный блок '+'
//  При касании переводит игру на следующий уровень
// ============================================================
class FinishBrick : public Brick {
public:
    FinishBrick(float x, float y, float w, float h)
        : Brick(x, y, w, h, '+') {}
};

// ============================================================
//  class Coin — монета '$'
//  Вылетает из блока '?', летит вверх, падает, скользит, исчезает при подборе.
// ============================================================
class Coin : public GameObject {
public:
    // Кирпич-источник: коллизия с ним игнорируется пока монета летит вниз,
    // иначе монета сразу залипнет на блоке '-' который только что появился.
    Brick* sourceBrick = nullptr;

    // source — кирпич-источник (по умолчанию nullptr)
    Coin(float x, float y, Brick* source = nullptr)
        : GameObject(x, y, 3, 2, '$'), sourceBrick(source) {
        vertSpeed  = -0.7f; // начальная скорость вверх
        horizSpeed =  0.2f; // горизонтальное скольжение по платформе
    }

    void update(Level& lvl) override;
};

// ============================================================
//  class Enemy — враг 'o'
//  Ходит горизонтально туда-сюда, не прыгает с платформ.
// ============================================================
class Enemy : public GameObject {
public:
    Enemy(float x, float y)
        : GameObject(x, y, 3, 2, 'o') {
        horizSpeed = 0.2f;
    }

    void update(Level& lvl) override;
};

// ============================================================
//  class Mario — игрок '@'
//  Управляется с клавиатуры. Прыгает, ходит, бьёт блоки, топчет врагов.
// ============================================================
class Mario : public GameObject {
public:
    // Начальная позиция — середина экрана, чуть выше центра
    Mario() : GameObject(39, 10, 3, 3, '@') {}

    // Сбрасывает Марио в начальную позицию (при смерти или загрузке уровня)
    void reset(float px = 39, float py = 10) {
        x = px; y = py;
        vertSpeed  = 0;
        horizSpeed = 0;
        isFlying   = false;
    }

    void handleInput(Level& lvl);    // читает клавиши и применяет управление
    void update(Level& lvl) override; // тик: ввод + гравитация + проверка падения
};
