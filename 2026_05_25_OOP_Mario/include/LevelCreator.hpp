#pragma once

class Level;

class LevelCreator {
public:
    static void load(Level& level, int levelNumber);

private:
    static void loadFirstLevel(Level& level);
    static void loadSecondLevel(Level& level);
    static void loadThirdLevel(Level& level);
};
