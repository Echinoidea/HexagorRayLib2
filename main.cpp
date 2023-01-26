#include <iostream>
#include <math.h>
#include <raylib.h>
#include <board.cpp>

using namespace std;

#define WIDTH 1200
#define HEIGHT 980
#define TITLE "HexGrid"

#define COLOR_BLACK (Color) {19, 19, 19, 255}
#define COLOR_WHITE (Color) {236, 236, 236, 255}
#define COLOR_RED (Color) {229, 78, 48, 255}
#define COLOR_GREEN (Color) {100, 160, 60, 255}
#define COLOR_BLUE (Color) {55, 107, 186, 255}

int main () {

    Board board = Board();
    board.fillBoard();
    board.addFeatures(5, 5);

    InitWindow(WIDTH, HEIGHT, "My first RAYLIB program!");
    SetTargetFPS(60);

    const int hexRadius = 50;
    const Vector2 originVector = (Vector2) {100, 50};
    const float verticalOffset = (sin(PI/3) * hexRadius);

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(COLOR_WHITE);

        for (int r = 0; r < 21; r++) {
            for (int q = 0; q < 7; q++) {
                if (r % 2 != 0) {
                    
                    DrawPoly((Vector2) {originVector.x + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_BLUE);
                    DrawPolyLines((Vector2) {originVector.x + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_BLACK);

                }
                else {
                    
                    DrawPoly((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_BLUE);
                    DrawPolyLines((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_BLACK);
                }
                if (r == 0 && q == 0) {
                    DrawPoly((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_RED);
                    DrawPolyLines((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_BLACK);
                }
            }
            
        }
        


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
/**
 * if (r % 2 != 0) {
                    DrawPoly((Vector2) {originVector.x + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_BLUE);
                    DrawPolyLines((Vector2) {originVector.x + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_BLACK);
                }
                else {
                    DrawPoly((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_BLUE);
                    DrawPolyLines((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
                    6, hexRadius, 30, COLOR_BLACK);
                }
*/