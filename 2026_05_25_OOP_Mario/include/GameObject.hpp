#pragma once

#include "Map.hpp"

class Level;

class GameObject {
public:
    float x;
    float y;
    float width;
    float height;
    float vertSpeed = 0;
    float horizSpeed = 0;
    bool isFlying = false;
    char cType;
    bool markedForDelete = false;

    GameObject(float x, float y, float width, float height, char type);
    virtual ~GameObject() = default;

    bool collidesWith(const GameObject& other) const;
    void drawOn(Map& map) const;
    virtual void update(Level& level) {}
};

class Brick : public GameObject {
public:
    Brick(float x, float y, float width, float height, char type);
};

class QuestionBrick : public Brick {
public:
    bool used = false;

    QuestionBrick(float x, float y, float width, float height);
    void onHitFromBelow(Level& level);
};

class FinishBrick : public Brick {
public:
    FinishBrick(float x, float y, float width, float height);
};

class Coin : public GameObject {
public:
    Brick* sourceBrick = nullptr;

    Coin(float x, float y, Brick* source = nullptr);
    void update(Level& level) override;
};

class Enemy : public GameObject {
public:
    Enemy(float x, float y);
    void update(Level& level) override;
};

class Mario : public GameObject {
public:
    Mario();

    void reset(float x = 39, float y = 10);
    void handleInput(Level& level);
    void update(Level& level) override;
};
