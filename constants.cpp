#pragma once

#include <raylib.h>

namespace constants {
  // Game window dimensions
  const int WINDOW_WIDTH = 1500;
  const int WINDOW_HEIGHT = 980;

  const int HEX_RADIUS = 35;

  // Width and height of the hexagon board
  const int N = 14;  

  // Basic colors
  const Color COLOR_BLACK = (Color) {19, 19, 19, 255};
  const Color COLOR_WHITE = (Color) {236, 236, 236, 255};
  const Color COLOR_RED = (Color) {229, 78, 48, 255};
  const Color COLOR_GREEN = (Color) {100, 160, 60, 255};
  const Color COLOR_BLUE = (Color) {55, 107, 186, 255};

  // Colors to represent Hex claim states
  const Color COLOR_EMPTY = (Color) {0, 0, 0, 25};
  const Color COLOR_HCS_PLAYERCLAIM = (Color) {0, 67, 255, 180};
  const Color COLOR_HCS_ENEMYCLAIM = (Color) {255, 0, 0, 180};

  // Colors to represent Hex feature states
  const Color COLOR_HFS_MOUNTAIN = (Color) {169, 169, 169, 180};
  const Color COLOR_HFS_VILLAGE = (Color) {217, 167, 26, 180};
}