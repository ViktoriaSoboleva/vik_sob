#pragma once

class GameObject;
class Level;

class Movement {
public:
    static bool applyGravity(GameObject& object, Level& level);
    static void applyHorizontalMove(GameObject& object, Level& level);
    static void scrollMap(Level& level, float dx);
};
