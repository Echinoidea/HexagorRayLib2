#include <iostream>
#include <math.h>
#include <raylib.h>
#include <vector>
#include <board.cpp>

using namespace std;

#define WIDTH 1500
#define HEIGHT 980
#define TITLE "HexGrid"

#define HEX_RADIUS 50

#define COLOR_BLACK (Color) {19, 19, 19, 255}
#define COLOR_WHITE (Color) {236, 236, 236, 255}
#define COLOR_RED (Color) {229, 78, 48, 255}
#define COLOR_GREEN (Color) {100, 160, 60, 255}
#define COLOR_BLUE (Color) {55, 107, 186, 255}

Vector2 hexToDrawPosition(Hex hex, Vector2 offset) {
    float horizontalOffset = (sin(PI/3) * HEX_RADIUS);
    int verticalOffset = 75;

    return (Vector2) {
        .x = offset.x + (horizontalOffset * hex.r) + (float)(hex.q) * (horizontalOffset * 2),//(cos(PI/6) * 100),
        .y = offset.y + (float)(hex.r) * verticalOffset
    };
}



void drawBoardRhombus(Board board) {
    for (int r = 0; r < board.N; r++) {
        for (int q = 0; q < board.N; q++) {
            DrawPoly(hexToDrawPosition(board.hexBoard[r][q], (Vector2) {100, 100}), 6, 50, 0, board.hexBoard[r][q].color);
            DrawPolyLines(hexToDrawPosition(board.hexBoard[r][q], (Vector2) {100, 100}), 6, 50, 0, COLOR_BLACK);
            DrawCircleLines(hexToDrawPosition(board.hexBoard[r][q], (Vector2) {100, 100}).x, hexToDrawPosition(board.hexBoard[r][q], (Vector2) {100, 100}).y, (cos(PI/6) * 50), COLOR_WHITE);
        }
    }
}

int main () {
    /*
    //Board board = Board();
    board.fillBoard();
    board.addFeatures(5, 5); */

    InitWindow(WIDTH, HEIGHT, "Hexes");
    SetTargetFPS(60);

    Board board = Board();
    Layout layout = Layout(layoutPointy, (Vector2) {10, 10}, (Vector2) {100, 100});



    // Fuck it. Doing rhombus map instead of hexagonal map
    for (int r = 0; r < board.N; r++) {
        for (int q = 0; q < board.N; q++) {
            int s = (q * -1) - r;

            board.hexBoard[r][q] = Hex(q, r, s);
            //printf("(%d, %d, %d)\n", q, r, s);
            
        }
    }

    //printf("%d, %d\n", board.hexToPixel(layout, board.hexBoard[0][0]).x, board.hexToPixel(layout, board.hexBoard[0][0]).y);
    
    //Vector2 p;
    //board.pixelToHex(layout, (Vector2) {100, 100});

    //printf("Hex: %d, %d", p.x, p.y);

    // TODO: Create colliders on hexes, have an invisible object follow mouse, on click and collision, do stuff

    while (WindowShouldClose() == false) {
        BeginDrawing();

        ClearBackground(COLOR_WHITE);
        drawBoardRhombus(board);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            
            Vector2 target = board.getHexFromPixel(GetMousePosition(), (Vector2) {100, 100});
            cout << target.x << ", " << target.y << endl;

            board.hexBoard[(int)round(target.y)][(int)round(target.x)].color = COLOR_RED;
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