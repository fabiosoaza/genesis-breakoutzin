#ifndef _LEVELS_H_
#define _LEVELS_H_

#include <genesis.h>
#include "brick.h"


#define LOAD_LEVEL(level) \
    _loadMap(sizeof(level) / sizeof(level[0]), sizeof(level[0]) / sizeof(level[0][0]), &level)

const u8 level1[6][14] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}};
u8 level2[6][14] = {
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0},
    {0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0},
    {0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0}};
u8 level3[6][14] = {
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0},
    {0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0},
    {0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0},
    {0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0},
    {0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0}};
u8 level4[6][13] = {
    {1, 0, 1, 0, 2, 0, 3, 0, 3, 0, 4, 0, 1},
    {0, 1, 0, 2, 0, 2, 0, 3, 0, 4, 0, 4, 0},
    {1, 0, 1, 0, 2, 0, 3, 0, 3, 0, 4, 0, 1},
    {0, 5, 0, 5, 0, 5, 0, 6, 0, 6, 0, 6, 0},
    {5, 0, 5, 0, 5, 0, 6, 0, 6, 0, 6, 0, 6},
    {0, 5, 0, 5, 0, 5, 0, 6, 0, 6, 0, 6, 0}};
u8 level5[10][13] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0},
    {0, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 0},
    {0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0},
    {0, 0, 4, 4, 0, 4, 4, 4, 0, 4, 4, 0, 0},
    {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
    {0, 4, 0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 0},
    {0, 4, 0, 4, 0, 0, 0, 0, 0, 4, 0, 4, 0},
    {0, 0, 0, 0, 4, 4, 0, 4, 4, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
u8 level6[6][14] = {
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0},
    {0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0},
    {0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0}};
u8 level7[8][13] = {
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
    {0, 7, 0, 0, 0, 3, 3, 3, 0, 0, 0, 7, 0},
    {7, 7, 7, 0, 0, 0, 1, 0, 0, 0, 7, 7, 7},
    {0, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 0},
    {0, 0, 0, 5, 5, 5, 0, 6, 6, 6, 0, 0, 0},
    {0, 0, 0, 5, 5, 5, 0, 6, 6, 6, 0, 0, 0},
    {0, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 0}};
u8 level8[8][13] = {
    {0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
    {0, 7, 7, 7, 0, 0, 5, 0, 0, 7, 7, 7, 0},
    {0, 1, 1, 1, 0, 0, 5, 0, 0, 1, 1, 1, 0},
    {0, 2, 2, 2, 0, 0, 5, 0, 0, 2, 2, 2, 0},
    {0, 3, 3, 3, 0, 0, 5, 0, 0, 3, 3, 3, 0},
    {0, 7, 7, 7, 0, 0, 5, 0, 0, 7, 7, 7, 0},
    {0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0}};
u8 level9[8][14] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2},
    {3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3},
    {4, 4, 4, 4, 4, 0, 0, 0, 0, 4, 4, 4, 4, 4},
    {5, 5, 5, 5, 5, 0, 0, 0, 0, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5},
    {6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6},
    {7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7}};
u8 level10[8][14] = {
    {7, 7, 7, 7, 7, 1, 1, 1, 1, 7, 7, 7, 7, 7},
    {7, 7, 7, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 7},
    {7, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7},
    {7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
    {1, 1, 7, 1, 1, 7, 1, 1, 7, 1, 1, 7, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {7, 7, 1, 1, 1, 7, 1, 1, 7, 1, 1, 1, 7, 7},
    {7, 7, 7, 1, 7, 7, 7, 7, 7, 7, 1, 7, 7, 7}};



u8 levelTest[1][7] = {
    {7, 6, 5, 4, 3, 2, 1}

};



void Levels_destroy(BrickMap *map)
{
    if (map != NULL)
    {
        free(map->map);
        free(map);
    }
}

int Levels_totalBlocks(BrickMap *map)
{
    int total = 0;
    if (map != NULL && map->map != NULL)
    {
        for (int i = 0; i < map->rows; i++)
        {
            for (int j = 0; j < map->cols; j++)
            {
                total++;
            }
        }
    }
    return total;
}

int Levels_totalBreakableBlocks(BrickMap *map)
{
    int total = 0;
    if (map != NULL && map->map != NULL)
    {
        for (int i = 0; i < map->rows; i++)
        {
            for (int j = 0; j < map->cols; j++)
            {
                if (map->map[i][j] != UNBREAKABLE && map->map[i][j] != INVISIBLE)
                {
                    total++;
                }
            }
        }
    }
    return total;
}

static BrickMap * _loadMap(int rows, int cols, u8 map[rows][cols])
{

    BrickMap *brickMap = (BrickMap *)malloc(sizeof(BrickMap));

    u8 **bitmap = (u8 **)malloc(rows * sizeof(u8 *));

    for (int i = 0; i < rows; i++)
    {
        bitmap[i] = (u8 *)malloc(cols * sizeof(u8));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            bitmap[i][j] = map[i][j];
        }
    }

    brickMap->rows = rows;
    brickMap->cols = cols;
    brickMap->map = bitmap;

    return brickMap;
}

const BrickMap *Levels_loadLevel(int levelNumber)
{

    BrickMap *map = NULL;
    switch (levelNumber)
    {
    case 1:
        map = LOAD_LEVEL(level1);
        break;
    case 2:
        map = LOAD_LEVEL(level2);
        break;
    case 3:
        map = LOAD_LEVEL(level3);
        break;
    case 4:
        map = LOAD_LEVEL(level4);
        break;
    case 5:
        map = LOAD_LEVEL(level5);
        break;
    case 6:
        map = LOAD_LEVEL(level6);
        break;
    case 7:
        map = LOAD_LEVEL(level7);
        break;
    case 8:
        map = LOAD_LEVEL(level8);
        break;
    case 9:
        map = LOAD_LEVEL(level9);
        break;
    case 10:
        map = LOAD_LEVEL(level10);
        break;
    default:
        map = LOAD_LEVEL(levelTest);
        break;
    }

    return map;
}

#undef LOAD_LEVEL
#endif //_LEVELS_H_