#pragma once

#include <windows.h>

// Board dimensions
const int BOARD_COLS = 14;
const int BOARD_ROWS = 6;

const int TILE_SIZE = 60;
const int HALF_TILE = TILE_SIZE / 2;

const int ROAD_SIZE = 10;
const int SIDEWALK_SIZE = 3;


// Board dimensions:
//
// 12 full tiles = 12 * 60
// 2 half tiles  = 2 * 30
// 13 internal roads = 13 * 10
//
// Plus a 10px road around the outside.

const int TILE_AREA_WIDTH =
    (12 * TILE_SIZE) +
    (2 * HALF_TILE) +
    ((BOARD_COLS - 1) * ROAD_SIZE);

const int TILE_AREA_HEIGHT =
    (BOARD_ROWS * TILE_SIZE) +
    ((BOARD_ROWS - 1) * ROAD_SIZE);

const int BOARD_WIDTH =
    TILE_AREA_WIDTH +
    (2 * ROAD_SIZE);

const int BOARD_HEIGHT =
    TILE_AREA_HEIGHT +
    (2 * ROAD_SIZE);


// Draw the complete board.
void DrawBoard(
    HDC hdc,
    int clientWidth,
    int clientHeight
);

