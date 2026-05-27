#include "Level.h"

#include <stdlib.h>   // system()
#include <windows.h>  // Sleep
#include <algorithm>  // std::remove_if

void Level::scrollMap(float dx) {
    mario.x -= dx; // временно двигаем Марио в обратную сторону
    for (auto& b : bricks)
        if (mario.collidesWith(*b)) {
            mario.x += dx;
            return;
        }
    mario.x += dx; // возвращаем Марио на место

    for (auto& b : bricks)   b->x += dx;
    for (auto& e : entities) e->x += dx;
}

void Level::load(int lvl) {
    system("color 9F"); // синий фон, белый текст
    bricks.clear();
    entities.clear();
    mario.reset();
    levelNum   = lvl;
    needReload = false;
    nextLevel  = false;

    if (lvl == 1) {
        addBrick<Brick>       ( 20, 20, 40,  5, '#');
        addBrick<QuestionBrick>( 30, 10,  5,  3);
        addBrick<QuestionBrick>( 50, 10,  5,  3);
        addBrick<Brick>       ( 60, 15, 40, 10, '#');
        addBrick<Brick>       ( 60,  5, 10,  3, '-');
        addBrick<QuestionBrick>( 70,  5,  5,  3);
        addBrick<Brick>       ( 75,  5,  5,  3, '-');
        addBrick<QuestionBrick>( 80,  5,  5,  3);
        addBrick<Brick>       ( 85,  5, 10,  3, '-');
        addBrick<Brick>       (100, 20, 20,  5, '#');
        addBrick<Brick>       (120, 15, 10, 10, '#');
        addBrick<Brick>       (150, 20, 40,  5, '#');
        addBrick<FinishBrick> (210, 15, 10, 10);

        addEntity<Enemy>( 25, 10);
        addEntity<Enemy>( 80, 10);
    }

    if (lvl == 2) {
        addBrick<Brick>      ( 20, 20, 40,  5, '#');
        addBrick<Brick>      ( 60, 15, 10, 10, '#');
        addBrick<Brick>      ( 80, 20, 20,  5, '#');
        addBrick<Brick>      (120, 15, 10, 10, '#');
        addBrick<Brick>      (150, 20, 40,  5, '#');
        addBrick<FinishBrick>(210, 15, 10, 10);

        addEntity<Enemy>( 25, 10);
        addEntity<Enemy>( 80, 10);
        addEntity<Enemy>( 65, 10);
        addEntity<Enemy>(120, 10);
        addEntity<Enemy>(160, 10);
        addEntity<Enemy>(175, 10);
    }

    if (lvl == 3) {
        addBrick<Brick>      ( 20, 20, 40,  5, '#');
        addBrick<Brick>      ( 80, 20, 15,  5, '#');
        addBrick<Brick>      (120, 15, 15, 10, '#');
        addBrick<FinishBrick>(160, 10, 15, 15);

        addEntity<Enemy>( 25, 10);
        addEntity<Enemy>( 50, 10);
        addEntity<Enemy>( 80, 10);
        addEntity<Enemy>( 90, 10);
        addEntity<Enemy>(120, 10);
        addEntity<Enemy>(130, 10);
    }
}

void Level::playerDead() {
    system("color 4F"); // красный фон
    Sleep(500);
    needReload = true;
}

void Level::goNextLevel() {
    levelNum++;
    if (levelNum > maxLevel) levelNum = 1;
    system("color 2F"); // зелёный фон
    Sleep(500);
    load(levelNum);
}

void Level::purgeEntities() {
    entities.erase(
        std::remove_if(
            entities.begin(), entities.end(),
            [](const std::unique_ptr<GameObject>& p) {
                return p->markedForDelete;
            }
        ),
        entities.end()
    );
}

void Level::update() {
    mario.update(*this);
    if (needReload) { load(levelNum); return; }

    // Итерируем по индексу — новые объекты (монеты), добавленные внутри update(),
    // начнут обновляться только со следующего кадра.
    int count = (int)entities.size();
    for (int i = 0; i < count; i++) {
        if (!entities[i]->markedForDelete)
            entities[i]->update(*this);
    }
    purgeEntities();
}

void Level::draw(Map& map) {
    for (auto& b : bricks)   b->drawOn(map);
    for (auto& e : entities) e->drawOn(map);
    mario.drawOn(map);
    map.putScore(score);
}
