#pragma once

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 650;
const int GRID_PIECE_SIDE = 40;
const int GRID_WIDTH = 15;
const int GRID_HEIGHT = 15;
const int GRID_X_POSITION = 2;
const int GRID_Y_POSITION = 2;
const int GRID_PIXEL_WIDTH = GRID_WIDTH * GRID_PIECE_SIDE;
const int GRID_PIXEL_HEIGHT = GRID_HEIGHT * GRID_PIECE_SIDE;
const int SPACER = 10;
const int INFO_BOX_X = GRID_X_POSITION + GRID_PIXEL_WIDTH + (SPACER * 2);
const int INFO_BOX_Y = GRID_Y_POSITION + 300;
const int INFO_BOX_WIDTH = 200;
const int INFO_BOX_HEIGHT = 200;
const int INFO_BOX_TEXT_X = INFO_BOX_X + SPACER;
const double FRAME_DELAY = 33.0;
const char ESC = 27;