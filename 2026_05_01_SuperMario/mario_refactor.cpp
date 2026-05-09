#pragma warning(disable : 4996)
#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>       
#include <windows.h>    
#include <string.h>     


#define mapWidth  80
#define mapHeight 25


typedef struct SObject {
    float x, y;          
    float width, height; 
    float vertSpeed;     
    BOOL  IsFly;         
    char  cType;         
    float horizSpeed;   
} TObject;


typedef struct {
    TObject mario;           
    TObject* brick;          
    int brickLength;
    TObject* moving;         
    int movingLength;
    int level;               
    int score;              
    int maxLvl;              
} GameState;


void CreateLevel(GameState* game, int lvl);

BOOL IsCollision(TObject o1, TObject o2);

TObject* GetNewBrick(GameState* game);

TObject* GetNewMoving(GameState* game);

void ClearMap(char map[mapHeight][mapWidth + 1]);

void ShowMap(char map[mapHeight][mapWidth + 1]);

void SetObjectPos(TObject* obj, float xPos, float yPos);

void InitObject(TObject* obj, float xPos, float yPos, float oWidth, float oHeight, char inType);

void PlayerDead(GameState* game);

void VertMoveObject(TObject* obj, GameState* game, char map[mapHeight][mapWidth + 1]);

void DeleteMoving(GameState* game, int i);

void MarioCollision(GameState* game);

void HorizonMoveObject(TObject* obj, GameState* game);

BOOL IsPosInMap(int x, int y);

void PutObjectOnMap(char map[mapHeight][mapWidth + 1], TObject obj);

void PutScoreOnMap(char map[mapHeight][mapWidth + 1], int score);

void setCur(int x, int y);

void HorizonMoveMap(GameState* game, float dx);


void ClearMap(char map[mapHeight][mapWidth + 1]) {
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = ' ';
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++)
        sprintf(map[j], "%s", map[0]);
}


void ShowMap(char map[mapHeight][mapWidth + 1]) {
    map[mapHeight - 1][mapWidth - 1] = '\0';
    for (int j = 0; j < mapHeight; j++)
        printf("%s\n", map[j]);
}


void SetObjectPos(TObject* obj, float xPos, float yPos) {
    obj->x = xPos;
    obj->y = yPos;
}


void InitObject(TObject* obj, float xPos, float yPos,
    float oWidth, float oHeight, char inType) {
    SetObjectPos(obj, xPos, yPos);
    obj->width = oWidth;
    obj->height = oHeight;
    obj->vertSpeed = 0.0f;
    obj->IsFly = FALSE;
    obj->cType = inType;
    obj->horizSpeed = 0.2f;
}


void PlayerDead(GameState* game) {
    system("color 4F");
    Sleep(500);
    CreateLevel(game, game->level);
}


void VertMoveObject(TObject* obj, GameState* game, char map[mapHeight][mapWidth + 1]) {
    obj->IsFly = TRUE;
    obj->vertSpeed += 0.05f;
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);

    for (int i = 0; i < game->brickLength; i++)
        if (IsCollision(*obj, game->brick[i])) {
            if (obj->vertSpeed > 0)
                obj->IsFly = FALSE;

            if ((game->brick[i].cType == '?') &&
                (obj->vertSpeed < 0) &&
                (obj == &game->mario)) {
                game->brick[i].cType = '-';
                InitObject(GetNewMoving(game), game->brick[i].x, game->brick[i].y - 3, 3, 2, '$');
                game->moving[game->movingLength - 1].vertSpeed = -0.7f;
            }

            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0.0f;

            if (game->brick[i].cType == '+') {
                game->level++;
                if (game->level > game->maxLvl) game->level = 1;
                system("color 2F");
                Sleep(500);
                CreateLevel(game, game->level);
            }
            break;
        }
}


void DeleteMoving(GameState* game, int i) {
    game->movingLength--;
    game->moving[i] = game->moving[game->movingLength];
    game->moving = (TObject*)realloc(game->moving, sizeof(TObject) * game->movingLength);
}


void MarioCollision(GameState* game) {
    for (int i = 0; i < game->movingLength; i++)
        if (IsCollision(game->mario, game->moving[i])) {
            if (game->moving[i].cType == 'o') {
                if ((game->mario.IsFly == TRUE) &&
                    (game->mario.vertSpeed > 0) &&
                    (game->mario.y + game->mario.height < game->moving[i].y + game->moving[i].height * 0.5f)) {
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


void HorizonMoveObject(TObject* obj, GameState* game) {
    obj[0].x += obj[0].horizSpeed;

    for (int i = 0; i < game->brickLength; i++)
        if (IsCollision(obj[0], game->brick[i])) {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
            return;
        }

    if (obj[0].cType == 'o') {
        TObject tmp = *obj;
        VertMoveObject(&tmp, game, NULL);
        if (tmp.IsFly == TRUE) {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
    }
}


BOOL IsPosInMap(int x, int y) {
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}


void PutObjectOnMap(char map[mapHeight][mapWidth + 1], TObject obj) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < ix + iWidth; i++)
        for (int j = iy; j < iy + iHeight; j++)
            if (IsPosInMap(i, j))
                map[j][i] = obj.cType;
}


void PutScoreOnMap(char map[mapHeight][mapWidth + 1], int score) {
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = (int)strlen(c);
    for (int i = 0; i < len; i++)
        map[1][i + 5] = c[i];
}


void setCur(int x, int y) {
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void HorizonMoveMap(GameState* game, float dx) {
    game->mario.x -= dx;

    for (int i = 0; i < game->brickLength; i++)
        if (IsCollision(game->mario, game->brick[i])) {
            game->mario.x += dx;
            return;
        }

    game->mario.x += dx;

    for (int i = 0; i < game->brickLength; i++)
        game->brick[i].x += dx;

    for (int i = 0; i < game->movingLength; i++)
        game->moving[i].x += dx;
}


BOOL IsCollision(TObject o1, TObject o2) {
    return ((o1.x + o1.width) > o2.x) &&
        (o1.x < (o2.x + o2.width)) &&
        ((o1.y + o1.height) > o2.y) &&
        (o1.y < (o2.y + o2.height));
}


TObject* GetNewBrick(GameState* game) {
    game->brickLength++;
    game->brick = (TObject*)realloc(game->brick, sizeof(TObject) * game->brickLength);
    return game->brick + game->brickLength - 1;
}


TObject* GetNewMoving(GameState* game) {
    game->movingLength++;
    game->moving = (TObject*)realloc(game->moving, sizeof(TObject) * game->movingLength);
    return game->moving + game->movingLength - 1;
}


void CreateLevel(GameState* game, int lvl) {
    system("color 9F");

    game->brickLength = 0;
    game->brick = (TObject*)realloc(game->brick, 0);

    game->movingLength = 0;
    game->moving = (TObject*)realloc(game->moving, 0);

    InitObject(&game->mario, 39, 10, 3, 3, '@');

    if (lvl == 1) {
        InitObject(GetNewBrick(game), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(game), 30, 10, 5, 3, '?');
        InitObject(GetNewBrick(game), 50, 10, 5, 3, '?');
        InitObject(GetNewBrick(game), 60, 15, 40, 10, '#');
        InitObject(GetNewBrick(game), 60, 5, 10, 3, '-');
        InitObject(GetNewBrick(game), 70, 5, 5, 3, '?');
        InitObject(GetNewBrick(game), 75, 5, 5, 3, '-');
        InitObject(GetNewBrick(game), 80, 5, 5, 3, '?');
        InitObject(GetNewBrick(game), 85, 5, 10, 3, '-');
        InitObject(GetNewBrick(game), 100, 20, 20, 5, '#');
        InitObject(GetNewBrick(game), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(game), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(game), 210, 15, 10, 10, '+');

        InitObject(GetNewMoving(game), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 80, 10, 3, 2, 'o');
    }

    if (lvl == 2) {
        InitObject(GetNewBrick(game), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(game), 60, 15, 10, 10, '#');
        InitObject(GetNewBrick(game), 80, 20, 20, 5, '#');
        InitObject(GetNewBrick(game), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(game), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(game), 210, 15, 10, 10, '+');

        InitObject(GetNewMoving(game), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 65, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 160, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 175, 10, 3, 2, 'o');
    }

    if (lvl == 3) {
        InitObject(GetNewBrick(game), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(game), 80, 20, 15, 5, '#');
        InitObject(GetNewBrick(game), 120, 15, 15, 10, '#');
        InitObject(GetNewBrick(game), 160, 10, 15, 15, '+');

        InitObject(GetNewMoving(game), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 50, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 90, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(game), 130, 10, 3, 2, 'o');
    }
}


int main() {
    GameState game;
    char map[mapHeight][mapWidth + 1];

    game.level = 1;
    game.score = 0;
    game.maxLvl = 3;
    game.brickLength = 0;
    game.movingLength = 0;
    game.brick = NULL;
    game.moving = NULL;

    CreateLevel(&game, game.level);

    do {
        ClearMap(map);

        if ((game.mario.IsFly == FALSE) && (GetKeyState(VK_SPACE) < 0))
            game.mario.vertSpeed = -1.0f;

        if (GetKeyState('A') < 0)
            HorizonMoveMap(&game, 1.0f);

        if (GetKeyState('D') < 0)
            HorizonMoveMap(&game, -1.0f);

        if (game.mario.y > mapHeight)
            PlayerDead(&game);

        VertMoveObject(&game.mario, &game, map);
        MarioCollision(&game);

        for (int i = 0; i < game.brickLength; i++)
            PutObjectOnMap(map, game.brick[i]);

        for (int i = 0; i < game.movingLength; i++) {
            VertMoveObject(game.moving + i, &game, map);
            HorizonMoveObject(game.moving + i, &game);

            if (game.moving[i].y > mapHeight) {
                DeleteMoving(&game, i);
                i--;
                continue;
            }

            PutObjectOnMap(map, game.moving[i]);
        }

        PutObjectOnMap(map, game.mario);
        PutScoreOnMap(map, game.score);

        setCur(0, 0);
        ShowMap(map);
        Sleep(10);

    } while (GetKeyState(VK_ESCAPE) >= 0);

    free(game.brick);
    free(game.moving);

    return 0;
}