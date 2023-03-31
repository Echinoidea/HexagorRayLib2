#include <iostream>
#include <math.h>
#include <raylib.h>
#include <vector>
#include <board.cpp>
#include <constants.cpp>
#include <textures.cpp>

using namespace std;
using namespace constants;
using namespace textures;

// Can't create a global variable for this without causing hovering bugs for some reason.
//Vector2 (Vector2) {100, 100}; 

Vector2 hexToDrawPosition(Hex hex, Vector2 offset) {
  float horizontalOffset = (sin(PI/3) * HEX_RADIUS);
  int verticalOffset = HEX_RADIUS + (HEX_RADIUS / 2);

  return (Vector2) {
    .x = offset.x + (horizontalOffset * hex.r) + (float)(hex.q) * (horizontalOffset * 2),//(cos(PI/6) * 100),
    .y = offset.y + (float)(hex.r) * verticalOffset
  };
}


void mapRhombus(Board board) { 
  // Fuck it. Doing rhombus map instead of hexagonal map
  for (int r = 0; r < N; r++) {
    for (int q = 0; q < N; q++) {
      int s = (q * -1) - r;

      board.hexBoard[r][q] = Hex(q, r, s);
      //printf("(%d, %d, %d)\n", q, r, s);
      
    }
  }
}





void drawBoardRhombus(Board board) {
  for (int r = 0; r < N; r++) {
    for (int q = 0; q < N; q++) {
      Hex hex = board.hexBoard[r][q];
      Vector2 hexPosition = hexToDrawPosition(hex, (Vector2) {100, 100});
      DrawPoly(hexPosition, 6, HEX_RADIUS, 0, hex.color);
      DrawPolyLines(hexPosition, 6, HEX_RADIUS, 0, COLOR_BLACK);
      //DrawCircleLines(hexToDrawPosition(board.hexBoard[r][q], (Vector2) {100, 100}).x, hexToDrawPosition(board.hexBoard[r][q], (Vector2) {100, 100}).y, (cos(PI/6) * 50), COLOR_WHITE);
      hex.hexTexture = getTexture(hex);
      DrawTexture(hex.hexTexture, hexPosition.x - (HEX_RADIUS / 4), hexPosition.y - (HEX_RADIUS / 4), COLOR_BLUE);
    }
  }
}


void changeColor(Hex& hex, Color color) {
  hex.color = color;
}


void hoverOnHex(Board& board, Vector2 target) {
  //Vector2 target = board.getHexFromPixel(GetMousePosition(), (Vector2) {100, 100});

  int y = (int)round(target.y);
  int x = (int)round(target.x);

  Hex& targetHex = board.hexBoard[y][x];

  targetHex.isHoverOver = true;
  if (targetHex.isHoverOver) {
    changeColor(targetHex, (Color) {targetHex.color.r, targetHex.color.g, targetHex.color.b, targetHex.color.a + 50});
  }
}


int main () {

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hexes");
  SetTargetFPS(60);

  LoadImages();

  Board board = Board(50, 20);

  for (int r = 0; r < N; r++) {
    for (int q = 0; q < N; q++) {
      int s = (q * -1) - r;

      board.hexBoard[r][q] = Hex(q, r, s);
      //printf("(%d, %d, %d)\n", q, r, s);
      
    }
  }
  
  Vector2 prevHover;
  
  Vector2 currentHover = (Vector2) {120, 120};

  while (WindowShouldClose() == false) {
    BeginDrawing();

    ClearBackground(COLOR_WHITE);

    drawBoardRhombus(board);
    
    
    currentHover = board.getHexFromPixel(GetMousePosition(), (Vector2) {100, 100});
    /* Hex& currentHex = board.hexBoard[(int)round(currentHover.y)][(int)round(currentHover.x)];*/

    if (Vector2Equals(currentHover, prevHover) == 0) {
      hoverOnHex(board,  currentHover);
      Hex& prevHex = board.hexBoard[(int)round(prevHover.y)][(int)round(prevHover.x)];
      changeColor(prevHex, prevHex.getColor());
      prevHover = currentHover;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      Vector2 target = board.getHexFromPixel(GetMousePosition(), (Vector2) {100, 100});

      Hex& currentHex = board.hexBoard[(int)round(target.y)][(int)round(target.x)];
      currentHex.claimState = HCS_PLAYERCLAIM;

    }

    EndDrawing();
  }

  

  CloseWindow();

  return 0;
}