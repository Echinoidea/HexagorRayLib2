#include <iostream>
#include <math.h>
#include <raylib.h>
#include <vector>
#include <board.cpp>

using namespace std;



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
    for (int r = 0; r < N; r++) {
        for (int q = 0; q < N; q++) {
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

    InitWindow(WIDTH, HEIGHT, "Hexes");
    SetTargetFPS(60);

    LoadImages();

    Board board = Board();

    for (int r = 0; r < N; r++) {
        for (int q = 0; q < N; q++) {
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
        }

        //if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {    
            Vector2 target = board.getHexFromPixel(GetMousePosition(), (Vector2) {100, 100});
            //cout << target.x << ", " << target.y << endl;

            int y = (int)round(target.y);
            int x = (int)round(target.x);
        }

        EndDrawing();
    }

    

    CloseWindow();

    return 0;
}