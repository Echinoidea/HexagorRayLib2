#include <iostream>
#include <Hex.cpp>
#include <Layout.cpp>
#include <vector>
#include <raylib.h>

struct Board {

    const static int N = 11;

    Hex hexBoard[N][N];

    Board() {}

    Vector2 hexToPixel(Layout layout, Hex hex) {
        const Orientation& m = layout.orientation;

        double x = (layoutPointy.f0 * hex.index.x + layoutPointy.f1 * hex.index.y) * layout.size.x;
        double y = (layoutPointy.f2 * hex.index.x + layoutPointy.f3 * hex.index.y) * layout.size.y;

        return (Vector2) {x + layout.origin.x, y + layout.origin.y};
    }

    Hex pixelToHex(Layout layout, Vector2 point) {
        const Orientation& m = layout.orientation;
        Vector2 pt = (Vector2) {(point.x - layout.origin.x) / layout.size.x, (point.y - layout.origin.y) / layout.size.y};

        double x = (m.b0 * pt.x + m.b1 * pt.y);
        double y = (m.b2 * pt.x + m.b2 * pt.y);

        //return Hex((Vector3) {x, y, (-x - y)});
        return Hex(x, y, (-x - y));
    }

    Vector2 hexCornerOffset(Layout layout, int corner) {
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
    }
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