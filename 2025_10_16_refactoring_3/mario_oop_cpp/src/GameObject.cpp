#include "Level.h"

#include <math.h>
#include <windows.h>  // GetKeyState

// ============================================================
//  GameObject — физика
// ============================================================

// Применяет гравитацию и обрабатывает вертикальные столкновения с кирпичами.
// Возвращает false если объект уже не существует (переход уровня).
bool GameObject::applyGravity(Level& lvl) {
    isFlying   = true;
    vertSpeed += 0.05f;  // ускорение вниз
    y         += vertSpeed;

    for (auto& b : lvl.bricks) {
        if (!collidesWith(*b)) continue;

        if (vertSpeed > 0) {
            // Падаем вниз — встаём точно на верхнюю грань кирпича
            isFlying = false;
            y        = b->y - height;
        } else {
            // Летим вверх — упираемся в нижнюю грань кирпича
            y = b->y + b->height;
        }

        // Марио бьёт головой снизу блок '?' — выбиваем монету
        if (b->cType == '?' && vertSpeed < 0 && this == &lvl.mario) {
            auto* qb = dynamic_cast<QuestionBrick*>(b.get());
            if (qb && !qb->used) qb->onHitFromBelow(lvl);
        }

        vertSpeed = 0;

        // Финишный блок '+' — переходим на следующий уровень
        if (b->cType == '+') {
            lvl.goNextLevel();
            return false;
        }
        break;
    }
    return true;
}

// Применяет горизонтальное движение и обрабатывает столкновения со стенами.
void GameObject::applyHorizMove(Level& lvl) {
    x += horizSpeed;

    for (auto& b : lvl.bricks) {
        if (collidesWith(*b)) {
            x         -= horizSpeed;
            horizSpeed = -horizSpeed;
            return;
        }
    }

    // Дополнительная проверка для врагов: не допускаем падения с края платформы
    if (cType == 'o') {
        float savedY = y;
        float savedV = vertSpeed;
        bool  savedF = isFlying;
        y += 0.05f; // сдвигаем чуть вниз — имитируем шаг гравитации

        bool onEdge = true;
        for (auto& b : lvl.bricks)
            if (collidesWith(*b)) { onEdge = false; break; }

        y         = savedY;
        vertSpeed = savedV;
        isFlying  = savedF;

        if (onEdge) {
            x         -= horizSpeed;
            horizSpeed = -horizSpeed;
        }
    }
}

// ============================================================
//  QuestionBrick
// ============================================================

// Выдаёт монету из блока '?' и превращает его в обычный блок '-'
void QuestionBrick::onHitFromBelow(Level& lvl) {
    used  = true;
    cType = '-';
    auto* coin = lvl.addEntity<Coin>(x, y - 3, this);
    (void)coin;
}

// ============================================================
//  Coin
// ============================================================

// Обновляет состояние монеты за один тик
void Coin::update(Level& lvl) {
    if (vertSpeed < 0) {
        // Фаза 1: монета летит ВВЕРХ — коллизии с кирпичами не проверяем,
        // иначе монета залипнет на блоке '-' который только что появился.
        vertSpeed += 0.05f;
        y         += vertSpeed;
    } else {
        // Фаза 2: монета достигла пика и теперь ПАДАЕТ
        sourceBrick = nullptr;
        applyGravity(lvl);
        applyHorizMove(lvl);
    }

    if (collidesWith(lvl.mario)) {
        lvl.score       += 100;
        markedForDelete  = true;
        return;
    }

    if (y > MAP_H) markedForDelete = true;
}

// ============================================================
//  Enemy
// ============================================================

// Обновляет состояние врага за один тик
void Enemy::update(Level& lvl) {
    applyGravity(lvl);
    applyHorizMove(lvl);

    if (y > MAP_H) { markedForDelete = true; return; }

    if (collidesWith(lvl.mario)) {
        // Марио топнул сверху: он в воздухе, летит вниз,
        // и его нижний край выше середины врага
        bool stomped = lvl.mario.isFlying
                    && lvl.mario.vertSpeed > 0
                    && lvl.mario.y + lvl.mario.height < y + height * 0.5f;
        if (stomped) {
            lvl.score      += 50;
            markedForDelete = true;
        } else {
            lvl.playerDead();
        }
    }
}

// ============================================================
//  Mario
// ============================================================

// Читает нажатые клавиши и применяет управление к Марио
void Mario::handleInput(Level& lvl) {
    // Пробел — прыжок, только если стоим на земле
    if (!isFlying && GetKeyState(VK_SPACE) < 0)
        vertSpeed = -1.0f;

    // A — влево: карта сдвигается вправо (Марио стоит на месте)
    if (GetKeyState('A') < 0) lvl.scrollMap( 1);
    // D — вправо: карта сдвигается влево
    if (GetKeyState('D') < 0) lvl.scrollMap(-1);
}

// Обновляет состояние Марио за один тик
void Mario::update(Level& lvl) {
    handleInput(lvl);
    if (y > MAP_H) { lvl.playerDead(); return; }
    applyGravity(lvl);
}
