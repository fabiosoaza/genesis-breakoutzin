#ifndef _BRICK_H_
#define _BRICK_H_

#include <genesis.h>
#include "base/entity.h"
#include "configs.h"

#define BRICK_WIDTH 16
#define BRICK_HEIGHT 8

typedef enum
{
    INVISIBLE,
    RED,
    ORANGE,
    DARK_YELLOW,
    YELLOW_BRASILIS,
    GREEN,
    BLUE,
    UNBREAKABLE

} BlockType;

typedef struct
{
    int rows;
    int cols;
    u8 **map;
} BrickMap;

typedef struct
{
    Entity base;
    BrickMap *map;

} BrickWall;

BrickWall BrickWall_create(BrickMap *map, u16 posY);
u16 Brick_getColorByBlockType(BlockType type);
u16 Brick_getColorIndexByBlockType(BlockType type);
u8 Brick_getScore(BlockType type);
void BrickWall_draw(BrickWall *wall);
void BrickWall_reset(BrickWall *wall);

BrickWall BrickWall_create(BrickMap *map, u16 posY)
{

    int BRICK_TOP_SPACING = 16;
    int topStart = (int)(posY + BRICK_TOP_SPACING);
    // centralize bricks
    int leftStart = ((SCREEN_WIDTH / 2) - ((BRICK_WIDTH * map->cols) / 2));

    int posXInTile = leftStart;
    int posYInTile = topStart;

    BrickWall bricks = {
        .map = map,
        .base = (Entity){
            .enabled = FALSE,
            .width = BRICK_WIDTH * map->cols,
            .height = BRICK_HEIGHT * map->rows,
            .velX = 0,
            .velY = 0,
            .x = leftStart,
            .y = topStart,
            .oldX = leftStart,
            .oldY = topStart

        }};
    return bricks;
}

u16 Brick_getColorByBlockType(BlockType type)
{
    switch (type)
    {
    case RED:
        return RGB24_TO_VDPCOLOR(0xD55546);
        break;
    case ORANGE:
        return RGB24_TO_VDPCOLOR(0xD07237);
        break;
    case DARK_YELLOW:
        return RGB24_TO_VDPCOLOR(0xBB7A2D);
        break;
    case YELLOW_BRASILIS:
        return RGB24_TO_VDPCOLOR(0xA79A27);
        break;
    case GREEN:
        return RGB24_TO_VDPCOLOR(0x469146);
        break;
    case BLUE:
        return RGB24_TO_VDPCOLOR(0x4960D0);
        break;
    case UNBREAKABLE:
        return RGB24_TO_VDPCOLOR(0x8E8E8E);
        break;
    default:
        return PAL_getColor(0);
        break;
    }
}

u16 Brick_getColorIndexByBlockType(BlockType type)
{
    switch (type)
    {
    case RED:
        return 10;
        break;
    case ORANGE:
        return 11;
        break;
    case DARK_YELLOW:
        return 12;
        break;
    case YELLOW_BRASILIS:
        return 13;
        break;
    case GREEN:
        return 14;
        break;
    case BLUE:
        return 15;
        break;
    case UNBREAKABLE:
        return 9;
        break;
    default:
        return 0;
        break;
    }
}

u8 Brick_getScore(BlockType type)
{
    switch (type)
    {
    case RED:
    case ORANGE:
        return 7;
        break;
    case DARK_YELLOW:
    case YELLOW_BRASILIS:
        return 4;
        break;
    case GREEN:
    case BLUE:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

BlockType getBrickTypeByPosition(BrickWall *wall, int posX, int posY)
{
    int posXInTile = posX / 8;
    int posYInTile = posY / 8;
}

void BrickWall_draw(BrickWall *wall)
{
    if (wall->base.enabled)
    {

        int widthInTile = BRICK_WIDTH / 8;
        int heightInTile = BRICK_HEIGHT / 8;

        int leftStart = wall->base.x / 8;
        int posXInTile = leftStart;
        int posYInTile = wall->base.y / 8;

        for (int row = 0; row < wall->map->rows; row++)
        {
            for (int col = 0; col < wall->map->cols; col++)
            {
                int colorIndex = Brick_getColorIndexByBlockType((BlockType)wall->map->map[row][col]);
                VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, colorIndex), posXInTile, posYInTile, widthInTile, heightInTile);
                posXInTile += 2;
            }
            posXInTile = leftStart;
            posYInTile++;
        }
    }
}

void BrickWall_clear(BrickWall *wall)
{

    int widthInTile = BRICK_WIDTH / 8;
    int heightInTile = BRICK_HEIGHT / 8;

    int leftStart = wall->base.x / 8;
    int posXInTile = leftStart;
    int posYInTile = wall->base.y / 8;

    VDP_clearTileMapRect(BG_B, posXInTile, posYInTile, wall->map->cols * widthInTile, wall->map->rows * heightInTile);
}

#endif //_BRICK_H_