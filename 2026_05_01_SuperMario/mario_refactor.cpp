#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <string.h>

#define mapWidth 80
#define mapHeight 25
#define maxLvl 3

typedef struct SObject {
    float x;
    float y;

    float width;
    float height;

    float vertSpeed;

    BOOL IsFly;

    char cType;

    float horizSpeed;

} TObject;

typedef struct SGame {

    char map[mapHeight][mapWidth + 1];

    TObject mario;

    TObject *brick;
    int brickLength;

    TObject *moving;
    int movingLength;

    int level;
    int score;

} TGame;

void SetObjectPos(TObject *obj, float xPos, float yPos)
{
    obj->x = xPos;
    obj->y = yPos;
}

void InitObject(
    TObject *obj,
    float xPos,
    float yPos,
    float oWidth,
    float oHeight,
    char inType
) {
    SetObjectPos(obj, xPos, yPos);

    obj->width = oWidth;
    obj->height = oHeight;

    obj->vertSpeed = 0;

    obj->IsFly = FALSE;

    obj->cType = inType;

    obj->horizSpeed = 0.2;
}

BOOL IsCollision(TObject o1, TObject o2)
{
    return (
        ((o1.x + o1.width) > o2.x) &&
        (o1.x < (o2.x + o2.width)) &&
        ((o1.y + o1.height) > o2.y) &&
        (o1.y < (o2.y + o2.height))
    );
}

BOOL IsPosInMap(int x, int y)
{
    return (
        (x >= 0) &&
        (x < mapWidth) &&
        (y >= 0) &&
        (y < mapHeight)
    );
}

void ClearMap(TGame *game)
{
    for (int i = 0; i < mapWidth; i++) {
        game->map[0][i] = ' ';
    }

    game->map[0][mapWidth] = '\0';

    for (int j = 1; j < mapHeight; j++) {
        sprintf(game->map[j], game->map[0]);
    }
}

void ShowMap(TGame *game)
{
    game->map[mapHeight - 1][mapWidth - 1] = '\0';

    for (int j = 0; j < mapHeight; j++) {
        printf("%s\n", game->map[j]);
    }
}

void PutObjectOnMap(TGame *game, TObject obj)
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);

    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < ix + iWidth; i++) {

        for (int j = iy; j < iy + iHeight; j++) {

            if (IsPosInMap(i, j)) {
                game->map[j][i] = obj.cType;
            }
        }
    }
}

void PutScoreOnMap(TGame *game)
{
    char c[30];

    sprintf(c, "Score: %d", game->score);

    int len = strlen(c);

    for (int i = 0; i < len; i++) {
        game->map[1][i + 5] = c[i];
    }
}

void setCur(int x, int y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

TObject *GetNewBrick(TGame *game)
{
    game->brickLength++;

    game->brick = (TObject*)realloc(
        game->brick,
        sizeof(*game->brick) * game->brickLength
    );

    return game->brick + game->brickLength - 1;
}

TObject *GetNewMoving(TGame *game)
{
    game->movingLength++;

    game->moving = (TObject*)realloc(
        game->moving,
        sizeof(*game->moving) * game->movingLength
    );

    return game->moving + game->movingLength - 1;
}

void AddBrick(
    TGame *game,
    float xPos,
    float yPos,
    float width,
    float height,
    char type
) {
    InitObject(
        GetNewBrick(game),
        xPos,
        yPos,
        width,
        height,
        type
    );
}

void AddMoving(
    TGame *game,
    float xPos,
    float yPos,
    float width,
    float height,
    char type
) {
    InitObject(
        GetNewMoving(game),
        xPos,
        yPos,
        width,
        height,
        type
    );
}

void DeleteMoving(TGame *game, int i)
{
    game->movingLength--;

    game->moving[i] =
        game->moving[game->movingLength];

    game->moving = (TObject*)realloc(
        game->moving,
        sizeof(*game->moving) * game->movingLength
    );
}

void CreateLevel(TGame *game, int lvl);

void PlayerDead(TGame *game)
{
    system("color 4F");

    Sleep(500);

    CreateLevel(game, game->level);
}

void VertMoveObject(TGame *game, TObject *obj)
{
    obj->IsFly = TRUE;

    obj->vertSpeed += 0.05;

    SetObjectPos(
        obj,
        obj->x,
        obj->y + obj->vertSpeed
    );
    for (int i = 0; i < game->brickLength; i++) {

        if (IsCollision(*obj, game->brick[i])) {

            if (obj->vertSpeed > 0) {
                obj->IsFly = FALSE;
            }

            if (
                (game->brick[i].cType == '?') &&
                (obj->vertSpeed < 0) &&
                (obj == &game->mario)
            ) {
                game->brick[i].cType = '-';

                InitObject(
                    GetNewMoving(game),
                    game->brick[i].x,
                    game->brick[i].y - 3,
                    3,
                    2,
                    '$'
                );

                game->moving[
                    game->movingLength - 1
                ].vertSpeed = -0.7;
            }

            obj->y -= obj->vertSpeed;

            obj->vertSpeed = 0;

            if (game->brick[i].cType == '+') {

                game->level++;

                if (game->level > maxLvl) {
                    game->level = 1;
                }

                system("color 2F");

                Sleep(500);

                CreateLevel(game, game->level);
            }

            break;
        }
    }
}

void MarioCollision(TGame *game)
{
    for (int i = 0; i < game->movingLength; i++) {

        if (
            IsCollision(
                game->mario,
                game->moving[i]
            )
        ) {

            if (game->moving[i].cType == 'o') {

                if (
                    (game->mario.IsFly == TRUE) &&
                    (game->mario.vertSpeed > 0) &&
                    (
                        game->mario.y +
                        game->mario.height <
                        game->moving[i].y +
                        game->moving[i].height * 0.5
                    )
                ) {
                    game->score += 50;

                    DeleteMoving(game, i);

                    i--;

                    continue;
                }

                PlayerDead(game);
            }

            if (game->moving[i].cType == '$') {

                game->score += 100;

                DeleteMoving(game, i);

                i--;

                continue;
            }
        }
    }
}

void HorizonMoveObject(TGame *game, TObject *obj)
{
    obj->x += obj->horizSpeed;

    for (int i = 0; i < game->brickLength; i++) {

        if (IsCollision(*obj, game->brick[i])) {

            obj->x -= obj->horizSpeed;

            obj->horizSpeed =
                -obj->horizSpeed;

            return;
        }
    }

    if (obj->cType == 'o') {

        TObject tmp = *obj;

        VertMoveObject(game, &tmp);

        if (tmp.IsFly == TRUE) {

            obj->x -= obj->horizSpeed;

            obj->horizSpeed =
                -obj->horizSpeed;
        }
    }
}

void HorizonMoveMap(TGame *game, float dx)
{
    game->mario.x -= dx;

    for (int i = 0; i < game->brickLength; i++) {

        if (
            IsCollision(
                game->mario,
                game->brick[i]
            )
        ) {
            game->mario.x += dx;

            return;
        }
    }

    game->mario.x += dx;

    for (int i = 0; i < game->brickLength; i++) {
        game->brick[i].x += dx;
    }

    for (int i = 0; i < game->movingLength; i++) {
        game->moving[i].x += dx;
    }
}

void CreateLevel(TGame *game, int lvl)
{
    system("color 9F");

    game->brickLength = 0;

    game->brick =
        (TObject*)realloc(game->brick, 0);

    game->movingLength = 0;

    game->moving =
        (TObject*)realloc(game->moving, 0);

    InitObject(
        &game->mario,
        39,
        10,
        3,
        3,
        '@'
    );

    if (lvl == 1) {

        AddBrick(game, 20, 20, 40, 5, '#');
        AddBrick(game, 30, 10, 5, 3, '?');
        AddBrick(game, 50, 10, 5, 3, '?');

        AddBrick(game, 60, 15, 40, 10, '#');

        AddBrick(game, 60, 5, 10, 3, '-');
        AddBrick(game, 70, 5, 5, 3, '?');

        AddBrick(game, 75, 5, 5, 3, '-');
        AddBrick(game, 80, 5, 5, 3, '?');

        AddBrick(game, 85, 5, 10, 3, '-');
        AddBrick(game, 100, 20, 20, 5, '#');

        AddBrick(game, 120, 15, 10, 10, '#');

        AddBrick(game, 150, 20, 40, 5, '#');

        AddBrick(game, 210, 15, 10, 10, '+');

        AddMoving(game, 25, 10, 3, 2, 'o');
        AddMoving(game, 80, 10, 3, 2, 'o');
    }

    if (lvl == 2) {

        AddBrick(game, 20, 20, 40, 5, '#');

        AddBrick(game, 60, 15, 10, 10, '#');

        AddBrick(game, 80, 20, 20, 5, '#');

        AddBrick(game, 120, 15, 10, 10, '#');

        AddBrick(game, 150, 20, 40, 5, '#');

        AddBrick(game, 210, 15, 10, 10, '+');

        AddMoving(game, 25, 10, 3, 2, 'o');
        AddMoving(game, 80, 10, 3, 2, 'o');

        AddMoving(game, 65, 10, 3, 2, 'o');
        AddMoving(game, 120, 10, 3, 2, 'o');

        AddMoving(game, 160, 10, 3, 2, 'o');
        AddMoving(game, 175, 10, 3, 2, 'o');
    }

    if (lvl == 3) {

        AddBrick(game, 20, 20, 40, 5, '#');

        AddBrick(game, 80, 20, 15, 5, '#');

        AddBrick(game, 120, 15, 15, 10, '#');

        AddBrick(game, 160, 10, 15, 15, '+');

        AddMoving(game, 25, 10, 3, 2, 'o');
        AddMoving(game, 50, 10, 3, 2, 'o');

        AddMoving(game, 80, 10, 3, 2, 'o');
        AddMoving(game, 90, 10, 3, 2, 'o');

        AddMoving(game, 120, 10, 3, 2, 'o');
        AddMoving(game, 130, 10, 3, 2, 'o');
    }
}

int main()
{
    TGame game;

    game.brick = NULL;
    game.brickLength = 0;

    game.moving = NULL;
    game.movingLength = 0;

    game.level = 1;
    game.score = 0;

    CreateLevel(&game, game.level);

    do {

        ClearMap(&game);

        if (
            (game.mario.IsFly == FALSE) &&
            (GetKeyState(VK_SPACE) < 0)
        ) {
            game.mario.vertSpeed = -1;
        }

        if (GetKeyState('A') < 0) {
            HorizonMoveMap(&game, 1);
        }

        if (GetKeyState('D') < 0) {
            HorizonMoveMap(&game, -1);
        }

        if (game.mario.y > mapHeight) {
            PlayerDead(&game);
        }

        VertMoveObject(&game, &game.mario);

        MarioCollision(&game);

        for (int i = 0; i < game.brickLength; i++) {
            PutObjectOnMap(
                &game,
                game.brick[i]
            );
        }

        for (int i = 0; i < game.movingLength; i++) {

            VertMoveObject(
                &game,
                game.moving + i
            );

            HorizonMoveObject(
                &game,
                game.moving + i
            );

            if (game.moving[i].y > mapHeight) {

                DeleteMoving(&game, i);

                i--;

                continue;
            }

            PutObjectOnMap(
                &game,
                game.moving[i]
            );
        }

        PutObjectOnMap(
            &game,
            game.mario
        );

        PutScoreOnMap(&game);

        setCur(0, 0);

        ShowMap(&game);

        Sleep(10);

    } while (GetKeyState(VK_ESCAPE) >= 0);

    free(game.brick);

    free(game.moving);

    return 0;
}