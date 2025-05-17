#pragma once

/* CONTAINS CONSTANTS AND CONFIG DEFINITIONS */


/* CONFIG */

const bool PRINT_AVG_FPS = true;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const unsigned int FPS = 60;
const float FRAME_DELAY = 1000.0 / FPS;

const int GAME_TILE_ROW_COUNT = 16;
const int GAME_TILE_COL_COUNT = (SCREEN_WIDTH * 1.0 * GAME_TILE_ROW_COUNT) / SCREEN_HEIGHT;

const int FLOOR_TILE_ROW_COUNT = GAME_TILE_ROW_COUNT / 4.0;

// Square tiles.
const int TILE_W = SCREEN_WIDTH / GAME_TILE_COL_COUNT, TILE_H = TILE_W;

// Assume 1 metre -> 1 TILE_H/W
const int GRAV_ACC = 30; 

const int FLOOR_BORDER_Y = 12 * TILE_H;

const int DELTA_X = 5;
const int DELTA_Y = 15;

// To maintain consistent movement across different FPS.
const float DELTA_TIME = 60.0/FPS;

const float GROUND_FRICTION_COEFF = 0.15;
const float AIR_FRICTION_COEFF = 0.02; 

const float WALL_BOUNCE_VEL = 0.6f;
const float COLLISION_BORDER_OFFSET = 1.0f;

const float MAX_X_VELOCITY = 20;
const float MAX_Y_VELOCITY = 20;