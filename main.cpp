#include <iostream>
#include <math.h>
#include <raylib.h>
#include <board.cpp>

using namespace std;

#define WIDTH 1500
#define HEIGHT 980
#define TITLE "HexGrid"

#define COLOR_BLACK (Color) {19, 19, 19, 255}
#define COLOR_WHITE (Color) {236, 236, 236, 255}
#define COLOR_RED (Color) {229, 78, 48, 255}
#define COLOR_GREEN (Color) {100, 160, 60, 255}
#define COLOR_BLUE (Color) {55, 107, 186, 255}

Vector2 hexToDrawPosition(Hex hex, Vector2 offset, Vector2 boardHexRadius) {
    float verticalOffset = (sin(PI/3) * boardHexRadius.x);

    int hexGridOffset = (hex.r % 2 != 0) ? 0 : 75;

    return (Vector2) {
        .x = offset.x + hexGridOffset + (float)(hex.q) * (boardHexRadius.x * 3),
        .y = offset.y + (float)(hex.r) * verticalOffset
    };
}

int main () {

    Board board = Board();
    board.fillBoard();
    board.addFeatures(5, 5);

    Hex h1 = Hex(0, 0);
    Vector2 p = hexToDrawPosition(h1, (Vector2) {100, 100}, (Vector2) {100, 100});
    cout << " ++++++ " << p.x << " " << p.y << endl;

    InitWindow(WIDTH, HEIGHT, "My first RAYLIB program!");
    SetTargetFPS(60);

    const int hexRadius = 50;
    const Vector2 originVector = (Vector2) {100, 50};
    

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(COLOR_WHITE);

        for (int r = 0; r < 10; r++) {
            for (int q = 0; q < 10; q++) {
                DrawPoly(hexToDrawPosition(board.hexBoard[r][q], originVector, (Vector2) {50, 50}), 6, 50, 30, BLUE);
                DrawPolyLines(hexToDrawPosition(board.hexBoard[r][q], originVector, (Vector2) {50, 50}), 6, 50, 30, BLACK);
//                 if (r % 2 != 0) {
                    
//                     
//                     /* DrawPoly((Vector2) {originVector.x + (q * 150), originVector.y + r * verticalOffset}, 
//                     6, hexRadius, 30, COLOR_BLUE);
//                     DrawPolyLines((Vector2) {originVector.x + (q * 150), originVector.y + r * verticalOffset}, 
//                     6, hexRadius, 30, COLOR_BLACK);
//  */
//                 }
//                 else {
                    
//                     // DrawPoly((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
//                     // 6, hexRadius, 30, COLOR_BLUE);
//                     // DrawPolyLines((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
//                     // 6, hexRadius, 30, COLOR_BLACK);
//                 }
//                 if (r == 0 && q == 0) {
//                     // DrawPoly((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
//                     // 6, hexRadius, 30, COLOR_RED);
//                     // DrawPolyLines((Vector2) {originVector.x + 75 + (q * 150), originVector.y + r * verticalOffset}, 
//                     // 6, hexRadius, 30, COLOR_BLACK);
//                 }
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