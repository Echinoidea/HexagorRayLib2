#include <iostream>
#include <Hex.cpp>
#include <vector>
#include <raylib.h>

struct Board {
    static const int ROWS = 10;
    static const int COLUMNS = 10;

    int mountainCount = 0;
    int villageCount = 0;

    Hex hexBoard[ROWS][COLUMNS];

    Board() {}

    void fillBoard() {
        for (int r = 0; r < ROWS; r++) {
            for (int q = 0; q < COLUMNS; q++) {
                hexBoard[r][q] = Hex(r, q);
                printf("Created new Hex at (%i, %i)\n", r, q);
            }
        }
    }

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
    /// @return Pointers to the 6 Hexes adjacent to target.
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
};