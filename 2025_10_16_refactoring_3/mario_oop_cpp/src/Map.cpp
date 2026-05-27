#pragma warning(disable : 4996)

#include "Map.h"

#include <stdio.h>    // printf, sprintf
#include <string.h>   // strlen
#include <windows.h>  // SetConsoleCursorPosition, GetStdHandle

// Перемещает курсор консоли в позицию (x, y)
// Используется чтобы перерисовывать экран на месте, без мерцания
static void setCur(int x, int y) {
    COORD c{ (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        c
    );
}

void Map::clear() {
    for (int i = 0; i < MAP_W; i++) grid[0][i] = ' ';
    grid[0][MAP_W] = '\0';
    for (int j = 1; j < MAP_H; j++)
        sprintf(grid[j], grid[0]);
}

void Map::setChar(int x, int y, char ch) {
    if (x >= 0 && x < MAP_W && y >= 0 && y < MAP_H)
        grid[y][x] = ch;
}

void Map::putScore(int score) {
    char buf[32];
    sprintf(buf, "Score: %d", score);
    int len = (int)strlen(buf);
    for (int i = 0; i < len; i++)
        grid[1][5 + i] = buf[i];
}

void Map::render() {
    grid[MAP_H - 1][MAP_W - 1] = '\0';
    setCur(0, 0);
    for (int j = 0; j < MAP_H; j++)
        printf("%s\n", grid[j]);
}
