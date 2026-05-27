#include "GameObject.hpp"
#include "Level.hpp"
#include "Movement.hpp"

#include <cmath>
#include <windows.h>

GameObject::GameObject(float x, float y, float width, float height, char type)
    : x(x), y(y), width(width), height(height), cType(type) {}

bool GameObject::collidesWith(const GameObject& other) const {
    return x + width > other.x &&
           x < other.x + other.width &&
           y + height > other.y &&
           y < other.y + other.height;
}

void GameObject::drawOn(Map& map) const {
    int ix = static_cast<int>(std::round(x));
    int iy = static_cast<int>(std::round(y));
    int iw = static_cast<int>(std::round(width));
    int ih = static_cast<int>(std::round(height));

    for (int i = ix; i < ix + iw; i++) {
        for (int j = iy; j < iy + ih; j++) {
            map.setChar(i, j, cType);
        }
    }
}

Brick::Brick(float x, float y, float width, float height, char type)
    : GameObject(x, y, width, height, type) {}

QuestionBrick::QuestionBrick(float x, float y, float width, float height)
    : Brick(x, y, width, height, '?') {}

void QuestionBrick::onHitFromBelow(Level& level) {
    used = true;
    cType = '-';
    level.addEntity<Coin>(x, y - 3, this);
}

FinishBrick::FinishBrick(float x, float y, float width, float height)
    : Brick(x, y, width, height, '+') {}

Coin::Coin(float x, float y, Brick* source)
    : GameObject(x, y, 3, 2, '$'), sourceBrick(source) {
    vertSpeed = -0.7f;
    horizSpeed = 0.2f;
}

void Coin::update(Level& level) {
    if (vertSpeed < 0) {
        vertSpeed += 0.05f;
        y += vertSpeed;
    } else {
        sourceBrick = nullptr;
        Movement::applyGravity(*this, level);
        Movement::applyHorizontalMove(*this, level);
    }

    if (collidesWith(level.mario)) {
        level.score += 100;
        markedForDelete = true;
        return;
    }

    if (y > MAP_H) {
        markedForDelete = true;
    }
}

Enemy::Enemy(float x, float y)
    : GameObject(x, y, 3, 2, 'o') {
    horizSpeed = 0.2f;
}

void Enemy::update(Level& level) {
    Movement::applyGravity(*this, level);
    Movement::applyHorizontalMove(*this, level);

    if (y > MAP_H) {
        markedForDelete = true;
        return;
    }

    if (collidesWith(level.mario)) {
        bool stomped = level.mario.isFlying &&
                       level.mario.vertSpeed > 0 &&
                       level.mario.y + level.mario.height < y + height * 0.5f;

        if (stomped) {
            level.score += 50;
            markedForDelete = true;
        } else {
            level.playerDead();
        }
    }
}

Mario::Mario()
    : GameObject(39, 10, 3, 3, '@') {}

void Mario::reset(float newX, float newY) {
    x = newX;
    y = newY;
    vertSpeed = 0;
    horizSpeed = 0;
    isFlying = false;
}

void Mario::handleInput(Level& level) {
    if (!isFlying && GetKeyState(VK_SPACE) < 0) {
        vertSpeed = -1.0f;
    }

    if (GetKeyState('A') < 0) {
        Movement::scrollMap(level, 1);
    }

    if (GetKeyState('D') < 0) {
        Movement::scrollMap(level, -1);
    }
}

void Mario::update(Level& level) {
    handleInput(level);

    if (y > MAP_H) {
        level.playerDead();
        return;
    }

    Movement::applyGravity(*this, level);
}
