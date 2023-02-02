#include <iostream>
#include <math.h>
#include <raylib.h>
#include <vector>
#include <board.cpp>

using namespace std;

#define WIDTH 1500
#define HEIGHT 980
#define TITLE "HexGrid"

#define HEX_RADIUS 30

#define COLOR_BLACK (Color) {19, 19, 19, 255}
#define COLOR_WHITE (Color) {236, 236, 236, 255}
#define COLOR_RED (Color) {229, 78, 48, 255}
#define COLOR_GREEN (Color) {100, 160, 60, 255}
#define COLOR_BLUE (Color) {55, 107, 186, 255}

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
    for (int r = 0; r < board.N; r++) {
        for (int q = 0; q < board.N; q++) {
            int s = (q * -1) - r;

            board.hexBoard[r][q] = Hex(q, r, s);
            //printf("(%d, %d, %d)\n", q, r, s);
            
        }
    }
}

Image sources[2]; 
Texture2D textures[3];

void LoadImages() {
    sources[0] = LoadImage(".\\assets\\mountains.png");
    sources[1] = LoadImage(".\\assets\\village.png");

    ImageResize(&sources[0], HEX_RADIUS - (HEX_RADIUS / 3), HEX_RADIUS - (HEX_RADIUS / 3));
    ImageResize(&sources[1], HEX_RADIUS - (HEX_RADIUS / 3), HEX_RADIUS - (HEX_RADIUS / 3));

    textures[0] = LoadTexture(NULL);
    textures[1] = LoadTextureFromImage(sources[0]);
    textures[2] = LoadTextureFromImage(sources[1]);
}

Texture2D getTexture(Hex hex) {
    Image src;
    Texture2D tx;

    if (hex.featureState == HFS_MOUNTAIN) {
        tx = textures[1];
    }
    else if (hex.featureState == HFS_VILLAGE) {
        tx = textures[2];
    }
    else {
        tx = textures[0];
    }
    
    return tx;
}


void drawBoardRhombus(Board board) {
    for (int r = 0; r < board.N; r++) {
        for (int q = 0; q < board.N; q++) {
            Hex hex = board.hexBoard[r][q];
            Vector2 hexPosition = hexToDrawPosition(hex, (Vector2) {100, 100});
            DrawPoly(hexPosition, 6, HEX_RADIUS, 0, hex.color);
            DrawPolyLines(hexPosition, 6, HEX_RADIUS, 0, COLOR_BLACK);
            //DrawCircleLines(hexToDrawPosition(board.hexBoard[r][q], (Vector2) {100, 100}).x, hexToDrawPosition(board.hexBoard[r][q], (Vector2) {100, 100}).y, (cos(PI/6) * 50), COLOR_WHITE);
            hex.hexTexture = getTexture(hex);
            DrawTexture(hex.hexTexture, hexPosition.x, hexPosition.y, COLOR_BLUE);
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
    /*
    //Board board = Board();
    board.fillBoard();
    board.addFeatures(5, 5); */

    InitWindow(WIDTH, HEIGHT, "Hexes");
    SetTargetFPS(60);

    LoadImages();

    Board board = Board();
    //Layout layout = Layout(layoutPointy, (Vector2) {10, 10}, (Vector2) {100, 100});

    for (int r = 0; r < board.N; r++) {
        for (int q = 0; q < board.N; q++) {
            int s = (q * -1) - r;

            board.hexBoard[r][q] = Hex(q, r, s);
            //printf("(%d, %d, %d)\n", q, r, s);
            
        }
    }
    
    Vector2 prevHover;

    board.addFeatures(10, 5);

    
    Vector2 currentHover = (Vector2) {120, 120};

    while (WindowShouldClose() == false) {
        BeginDrawing();

        ClearBackground(COLOR_WHITE);

        drawBoardRhombus(board);
        
        
        currentHover = board.getHexFromPixel(GetMousePosition(), (Vector2) {100, 100});
        Hex& currentHex = board.hexBoard[(int)round(currentHover.y)][(int)round(currentHover.x)];

        if (Vector2Equals(currentHover, prevHover) == 0) {
            hoverOnHex(board,  currentHover);
            Hex& prevHex = board.hexBoard[(int)round(prevHover.y)][(int)round(prevHover.x)];
            changeColor(prevHex, prevHex.getColor());
            prevHover = currentHover;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            Vector2 target = board.getHexFromPixel(GetMousePosition(), (Vector2) {100, 100});
            //cout << target.x << ", " << target.y << endl;

            Hex& currentHex = board.hexBoard[(int)round(target.y)][(int)round(target.x)];
            currentHex.claimState = HCS_PLAYERCLAIM;

            int y = (int)round(target.y);
            int x = (int)round(target.x);



            // changeColor(currentHex, BLACK);
            // Hex t = board.getHexFromPixel2(&board, (Vector2) {100, 100});
            // changeColor(t, YELLOW);
        }

        //if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {    
            Vector2 target = board.getHexFromPixel(GetMousePosition(), (Vector2) {100, 100});
            //cout << target.x << ", " << target.y << endl;

            int y = (int)round(target.y);
            int x = (int)round(target.x);



            // if (!board.hexBoard[y][x].isHoverOver) {
            //     board.hexBoard[y][x].isHoverOver = true;
            //     board.hexBoard[y][x].color = (Color) {0, 121, 241, 25};
            // }
            // else {
            //     board.hexBoard[y][x].isHoverOver = false;
            //     board.hexBoard[y][x].color = COLOR_BLUE;
            // }

            
            //board.hexBoard[y][x].isHoverOver = true;

            // cout << board.hexBoard[y][x].hexNeighbor(1).q << " " << board.hexBoard[y][x].hexNeighbor(1).q << endl;

            // int adj_x = board.hexBoard[y][x].hexNeighbor(1).q;
            // int adj_y = board.hexBoard[y][x].hexNeighbor(1).r;

            // board.hexBoard[adj_y][adj_x].color = COLOR_GREEN;
        }



        //board.hexBoard[y][x].color = (Color) {0, 121, 241, 25};


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