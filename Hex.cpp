#include <raylib.h>
#include <cmath>
#include <vector>
#include <raymath.h>
#include <assert.h>

enum HexClaimState {
    HCS_UNCLAIMED,
    HCS_PLAYERCLAIM,
    HCS_ENEMYCLAIM
};

enum HexFeatureState {
    HFS_EMPTY,
    HFS_MOUNTAIN,
    HFS_VILLAGE
};

enum HexTroopState {
    HTS_EMPTY,
    HTS_OCCUPIED
};

struct Hex{
    
    
    int q = 0, r = 0, s = 0;

    Vector3 index = (Vector3) {q, r, s};
    //Hex* adjacents;

    //int radius = 50;
    //Color color = (Color) {55, 107, 186, 255};

    //HexClaimState claimState = HCS_UNCLAIMED;
    //HexFeatureState featureState = HFS_EMPTY;
    //HexTroopState troopState = HTS_EMPTY;

    //Hex(int q_, int r_, int s_) {
        // this->index.x = q;
        // this->index.y = r;
        // this->index.z = s;
    //}

    Hex(Vector3 index_): index(index_) {}
    
    Hex(int q_, int r_, int s_): q(q_), r(r_), s(s_) {}

    //Hex(Vector3 index_): index(index_) {}

    Hex() {}

    int hexLength(Hex hex) {
        return int((abs(hex.index.x) + abs(hex.index.y) + abs(hex.index.z)));
    }

    int hexDistance(Hex targetHex) {
        return hexLength(hexSubtract(targetHex));
    }

    Hex hexAdd(Hex b) {
        //return Hex((Vector3) {this->index.x + b.index.x, this->index.y + b.index.y, this->index.z + b.index.z});
        return Hex(this->index.x + b.index.x, this->index.y + b.index.y, this->index.z + b.index.z);
    }

    Hex hexSubtract(Hex b) {
        //return Hex((Vector3) {this->index.x - b.index.x, this->index.y - b.index.y, this->index.z - b.index.z});
        return Hex(this->index.x - b.index.x, this->index.y - b.index.y, this->index.z - b.index.z);
    }

    Hex hexMultiply(int k) {
        // return Hex((Vector3) {this->index.x * k, this->index.y * k, this->index.z * k});
        return Hex(this->index.x * k, this->index.y * k, this->index.z * k);
    }

    /**std::vector<Hex> hexDirections = {
        //Hex((Vector3) {1, 0, -1}), Hex((Vector3) {1, -1, 0}), Hex((Vector3) {0, -1, 1}),
        //Hex((Vector3) {-1, 0, 1}), Hex((Vector3) {-1, 1, 0}), Hex((Vector3) {0, 1, -1})
        Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1),
        Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)
    };*/

    std::vector<Hex> getHexDirections() {
        std::vector<Hex> directions; 

        directions.push_back(Hex((Vector3) {1, 0, -1}));
        directions.push_back(Hex((Vector3) {1, -1, 0}));
        directions.push_back(Hex((Vector3) {0, -1, 1}));
        directions.push_back(Hex((Vector3) {-1, 0, 1}));
        directions.push_back(Hex((Vector3) {-1, 1, 0}));
        directions.push_back(Hex((Vector3) {0, 1, -1}));

        return directions;
    }

    /// @brief Get the hex adjacent to this hex in 'direction'
    /// @param direction number between 0 and 5
    Hex hexDirection(int direction) {
        assert(0 <= direction && direction < 6);
        return getHexDirections()[direction];
    }

    Hex hexNeighbor(int direction) {
        return hexAdd(hexDirection(direction));
    }
 };