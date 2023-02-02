#include <iostream>
#include <Hex.cpp>
#include <vector>
#include <raylib.h>
#include <math.h>

struct Board {

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
};