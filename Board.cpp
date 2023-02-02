#include <iostream>
#include <Hex.cpp>
#include <Layout.cpp>
#include <vector>
#include <raylib.h>
#include <math.h>

#define HEX_RADIUS 30

#define COLOR_HFS_EMPTY = BLUE
#define COLOR_HFS_MOUNTAIN (Color) {169, 169, 169, 180}
#define COLOR_HFS_VILLAGE (Color) {217, 167, 26, 180}

struct Board {

    const static int N = 18;

    int mountainCount = 0;
    int villageCount = 0;

    Hex hexBoard[N][N];

    Board() {}

    void addFeatures(int mountainCount_, int villageCount_) {
        for (int i = 0; i < N * N; i++) {
            int mOrV = GetRandomValue(0, 1);
            int rq = GetRandomValue(0, N);
            int rr = GetRandomValue(0, N); 
            
            if (mOrV == 0 && mountainCount < mountainCount_ && hexBoard[rr][rq].featureState == HFS_EMPTY) {
                hexBoard[rr][rq].featureState = HFS_MOUNTAIN;
                mountainCount++;
                //hexBoard[rr][rq].color = hexBoard[rr][rq].getColor();
                printf("Created new mountain at %d, %d\n", rr, rq);
            }

            if (mOrV == 1 && villageCount < villageCount_ && hexBoard[rr][rq].featureState == HFS_EMPTY) {
                hexBoard[rr][rq].featureState = HFS_VILLAGE;
                villageCount++;
                //hexBoard[rr][rq].color = COLOR_HFS_VILLAGE;
                printf("Created new village at %d, %d\n", rr, rq);
            }
        }
    }

    void updateColor(Hex exclude) {
        for (int r = 0; r < N; r++) {
            for (int q = 0; q < N; q++) {
                if (!hexBoard[q][r].isEqual(exclude)) {
                    hexBoard[q][r].color = hexBoard[q][r].getColor();
                }
            }
        }
    }

    void updateTextures() {
        for (int r = 0; r < N; r++) {
            for (int q = 0; q < N; q++) {
                hexBoard[q][r].hexTexture = hexBoard[q][r].hexTexture;
            }
        }
    }

    float calcDistance(Vector2 a, Vector2 b) {
        return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
    }

    Hex getHexFromPixel2(Board* board, Vector2 offset) {
        Vector2 mousePosition = GetMousePosition();

        float horizontalOffset = (sin(PI/3) * HEX_RADIUS);
        int verticalOffset = 75;

        std::vector<Vector2> circles;

        for (int r = 0; r < N; r++) {
            for (int q = 0; q < N; q++) {
                circles.push_back((Vector2) {
                    .x = offset.x + (horizontalOffset * r) + (float)(q) * (horizontalOffset * 2),//(cos(PI/6) * 100),
                    .y = offset.y + (float)(r) * verticalOffset
                });
            }
        }

        // std::cout << "Click position: " << mousePosition.x << ", " << mousePosition.y << std::endl;

        Vector2 closestCircle;

        // Calculate distance from mousePosition to each Hex. Find least distance. If distance < HEX_RADIUS, then it is clicking that circle

        float closestDistance = INT_MAX;
        float distance;

        std::vector<Vector2> closeCircles;

        for (unsigned i = 0; i < circles.size(); i++) {
            distance = calcDistance(mousePosition, circles.at(i));
            //std::cout << "Distance between click and (" << circles.at(i).x << ", " << circles.at(i).y << "): " << distance << std::endl;
            if (distance < closestDistance) {
                closestDistance = distance;
                if (closestDistance <= HEX_RADIUS) {
                    closestCircle = circles.at(i);
                }
            }
        }
        /*
        .x = offset.x + (horizontalOffset * hex.r) + (float)(hex.q) * (horizontalOffset * 2), //(cos(PI/6) * 100),
        .y = offset.y + (float)(hex.r) * verticalOffset
        */

        // Use the formulas from main "hexToDrawPosition" to solve for r and q rather than x and y

        float r = ((closestCircle.y / verticalOffset) - (offset.y / verticalOffset));
        float q = ((closestCircle.x / (2 * horizontalOffset)) - (offset.x / (2 * horizontalOffset)) - (r / 2));

        return board->hexBoard[(int)round(r)][(int)round(q)];
    }

    Vector2 getHexFromPixel(Vector2 point, Vector2 offset) {
        Vector2 mousePosition = GetMousePosition();

        float horizontalOffset = (sin(PI/3) * HEX_RADIUS);
        int verticalOffset = HEX_RADIUS + (HEX_RADIUS / 2);

        std::vector<Vector2> circles;

        for (int r = 0; r < N; r++) {
            for (int q = 0; q < N; q++) {
                circles.push_back((Vector2) {
                    .x = offset.x + (horizontalOffset * r) + (float)(q) * (horizontalOffset * 2),//(cos(PI/6) * 100),
                    .y = offset.y + (float)(r) * verticalOffset
                });
            }
        }

        // std::cout << "Click position: " << mousePosition.x << ", " << mousePosition.y << std::endl;

        Vector2 closestCircle;

        // Calculate distance from mousePosition to each Hex. Find least distance. If distance < HEX_RADIUS, then it is clicking that circle

        float closestDistance = INT_MAX;
        float distance;

        std::vector<Vector2> closeCircles;

        for (unsigned i = 0; i < circles.size(); i++) {
            distance = calcDistance(mousePosition, circles.at(i));
            //std::cout << "Distance between click and (" << circles.at(i).x << ", " << circles.at(i).y << "): " << distance << std::endl;
            if (distance < closestDistance) {
                closestDistance = distance;
                if (closestDistance <= HEX_RADIUS) {
                    closestCircle = circles.at(i);
                }
            }
        }
        
        // std::cout << "Closest circle: " << (int)round(closestCircle.x) << ", " << (int)round(closestCircle.y) << std::endl;

        /*
        .x = offset.x + (horizontalOffset * hex.r) + (float)(hex.q) * (horizontalOffset * 2), //(cos(PI/6) * 100),
        .y = offset.y + (float)(hex.r) * verticalOffset
        */

        // Use the formulas from main "hexToDrawPosition" to solve for r and q rather than x and y

        float r = ((closestCircle.y / verticalOffset) - (offset.y / verticalOffset));
        float q = ((closestCircle.x / (2 * horizontalOffset)) - (offset.x / (2 * horizontalOffset)) - (r / 2));

        //printf("NEW : %d, %d\n", q, r);

        return (Vector2) {q, r};
    }

    Vector2 hexToPixel(Hex hex, Vector2 offset) {
        float horizontalOffset = (sin(PI/3) * HEX_RADIUS);
        int verticalOffset = 75;

        return (Vector2) {
            .x = offset.x + (horizontalOffset * hex.r) + (float)(hex.q) * (horizontalOffset * 2),//(cos(PI/6) * 100),
            .y = offset.y + (float)(hex.r) * verticalOffset
        };
    }





    /*
    Hex pixelToHex(Layout layout, Vector2 point) {
        const Orientation& m = layout.orientation;
        Vector2 pt = (Vector2) {(point.x - layout.origin.x) / layout.size.x, (point.y - layout.origin.y) / layout.size.y};

        double x = (m.b0 * pt.x + m.b1 * pt.y);
        double y = (m.b2 * pt.x + m.b2 * pt.y);

        //return Hex((Vector3) {x, y, (-x - y)});
        return Hex(x, y, (-x - y));
    }*/

    /*Vector2 hexCornerOffset(Layout layout, int corner) {
        Vector2 size = layout.size;

        double angle = 2.0 * PI * (layout.orientation.startAngle + corner) / 6;

        return (Vector2) {size.x * cos(angle), size.y * sin(angle)};
    }

    std::vector<Vector2> polygonCorners(Layout layout, Hex hex) {
        std::vector<Vector2> corners = {};

        Vector2 center = hexToPixel(layout, hex);

        for (int i = 0; i < 6; i++) {
            Vector2 offset = hexCornerOffset(layout, i);
            corners.push_back((Vector2) {center.x + offset.x, center.y + offset.y});
        }

        return corners;
    }*/
};


/* struct Board {
    const static int ROWS = 10;
    const static int COLUMNS = 5;

    int mountainCount = 0;
    int villageCount = 0;

    Hex hexBoard[ROWS][COLUMNS];

    //Board(int rows_, int columns_) : ROWS(rows_), COLUMNS(columns_) {}

    Board() {}

    /// @brief Fill the board with empty hexes.
    void fillBoard() {
        for (int r = 0; r < ROWS; r++) {
            for (int q = 0; q < COLUMNS; q++) {
                hexBoard[r][q] = Hex(r, q);
                printf("Created new Hex at (%i, %i)\n", r, q);
            }
        }
    }

    /// @brief Add features to random hexes.
    /// @param mountainCount_ Number of mountains to add to the board.
    /// @param villageCount_ Number of villages to add to the board.
    void addFeatures(int mountainCount_, int villageCount_) {
        for (int i = 0; i < ROWS * COLUMNS; i++) {
            int mOrV = GetRandomValue(0, 1);
            int rr = GetRandomValue(0, ROWS);
            int rq = GetRandomValue(0, COLUMNS);

            if (mOrV == 0 && mountainCount < mountainCount_ && hexBoard[rr][rq].featureState == HFS_EMPTY) {
                hexBoard[rr][rq].featureState = HFS_MOUNTAIN;
                mountainCount++;
                printf("Created new mountains at (%i, %i) - mountainCount = %i\n", rr, rq, mountainCount);
            }

            if (mOrV == 1 && villageCount < villageCount_ && hexBoard[rr][rq].featureState == HFS_EMPTY) {
                hexBoard[rr][rq].featureState = HFS_VILLAGE;
                villageCount++;
                printf("Created new village at (%i, %i) - villageCount = %i\n", rr, rq, villageCount);
            }
        }
    }

    /// @brief Get the adjacent 6 Hexes based on the offset coordinate design. See reference image.
    /// @param target The Hex to get the adjacent Hexes of.
    /// @return A vector containing the 6 Hexes adjacent to target.
    std::vector<Hex> getAdjacents(Hex target) {
        std::vector<Hex> adjacents;

        // If on odd row
        if(target.r % 2 != 0) {
            adjacents.push_back(hexBoard[target.r - 1][target.q]);
            adjacents.push_back(hexBoard[target.r - 1][target.q + 1]);

            adjacents.push_back(hexBoard[target.r][target.q - 1]);
            adjacents.push_back(hexBoard[target.r][target.q + 1]);

            adjacents.push_back(hexBoard[target.r + 1][target.q]);
            adjacents.push_back(hexBoard[target.r + 1][target.q + 1]);
        }
        else {
            adjacents.push_back(hexBoard[target.r - 1][target.q - 1]);
            adjacents.push_back(hexBoard[target.r - 1][target.q]);

            adjacents.push_back(hexBoard[target.r][target.q - 1]);
            adjacents.push_back(hexBoard[target.r][target.q + 1]);

            adjacents.push_back(hexBoard[target.r + 1][target.q - 1]);
            adjacents.push_back(hexBoard[target.r + 1][target.q]);
        }

        printf("Adjacent Hexes to Hex [%d, %d] are: \n");
        for(int i = 0; i < 6; i++) {
            printf("[%d, %d]", adjacents.at(i).r, adjacents.at(i).q);
        }
        return adjacents;
    }

    int getIndexFromHex() {
        return 0;
    }

    Hex getHexFromIndex(int row, int col) {
        return Hex();
    }
}; */