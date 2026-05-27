#include "LevelCreator.hpp"
#include "Level.hpp"

#include <cstdlib>

void LevelCreator::load(Level& level, int levelNumber) {
    system("color 9F");

    level.bricks.clear();
    level.entities.clear();
    level.mario.reset();
    level.levelNum = levelNumber;
    level.needReload = false;
    level.nextLevel = false;

    if (levelNumber == 1) {
        loadFirstLevel(level);
    }

    if (levelNumber == 2) {
        loadSecondLevel(level);
    }

    if (levelNumber == 3) {
        loadThirdLevel(level);
    }
}

void LevelCreator::loadFirstLevel(Level& level) {
    level.addBrick<Brick>(20, 20, 40, 5, '#');
    level.addBrick<QuestionBrick>(30, 10, 5, 3);
    level.addBrick<QuestionBrick>(50, 10, 5, 3);
    level.addBrick<Brick>(60, 15, 40, 10, '#');
    level.addBrick<Brick>(60, 5, 10, 3, '-');
    level.addBrick<QuestionBrick>(70, 5, 5, 3);
    level.addBrick<Brick>(75, 5, 5, 3, '-');
    level.addBrick<QuestionBrick>(80, 5, 5, 3);
    level.addBrick<Brick>(85, 5, 10, 3, '-');
    level.addBrick<Brick>(100, 20, 20, 5, '#');
    level.addBrick<Brick>(120, 15, 10, 10, '#');
    level.addBrick<Brick>(150, 20, 40, 5, '#');
    level.addBrick<FinishBrick>(210, 15, 10, 10);

    level.addEntity<Enemy>(25, 10);
    level.addEntity<Enemy>(80, 10);
}

void LevelCreator::loadSecondLevel(Level& level) {
    level.addBrick<Brick>(20, 20, 40, 5, '#');
    level.addBrick<Brick>(60, 15, 10, 10, '#');
    level.addBrick<Brick>(80, 20, 20, 5, '#');
    level.addBrick<Brick>(120, 15, 10, 10, '#');
    level.addBrick<Brick>(150, 20, 40, 5, '#');
    level.addBrick<FinishBrick>(210, 15, 10, 10);

    level.addEntity<Enemy>(25, 10);
    level.addEntity<Enemy>(80, 10);
    level.addEntity<Enemy>(65, 10);
    level.addEntity<Enemy>(120, 10);
    level.addEntity<Enemy>(160, 10);
    level.addEntity<Enemy>(175, 10);
}

void LevelCreator::loadThirdLevel(Level& level) {
    level.addBrick<Brick>(20, 20, 40, 5, '#');
    level.addBrick<Brick>(80, 20, 15, 5, '#');
    level.addBrick<Brick>(120, 15, 15, 10, '#');
    level.addBrick<FinishBrick>(160, 10, 15, 15);

    level.addEntity<Enemy>(25, 10);
    level.addEntity<Enemy>(50, 10);
    level.addEntity<Enemy>(80, 10);
    level.addEntity<Enemy>(90, 10);
    level.addEntity<Enemy>(120, 10);
    level.addEntity<Enemy>(130, 10);
}
