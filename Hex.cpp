#include <raylib.h>
#include <cmath>
#include <vector>
#include <raymath.h>
#include <assert.h>
#include <Globals.cpp>

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

    Color color = COLOR_EMPTY;

    Texture2D hexTexture;

    HexClaimState claimState = HCS_UNCLAIMED;
    HexFeatureState featureState = HFS_EMPTY;
    HexTroopState troopState = HTS_EMPTY;

    bool isHoverOver = false;

    Hex(Vector3 index_): index(index_) {
    }


    Hex(Vector2 index_) {
        this->index.x = index_.x;
        this->index.y = index_.y;
        this->index.z = (index_.x * -1) - index_.y;
    }
    

    Hex(int q_, int r_, int s_): q(q_), r(r_), s(s_) {
    }


    Hex() {}

    

    Color getColor() {
        if (claimState == HCS_PLAYERCLAIM) {
            return COLOR_HCS_PLAYERCLAIM;
        }
        else if (claimState == HCS_ENEMYCLAIM) {
            return COLOR_HCS_ENEMYCLAIM;
        }
        else {
            return COLOR_EMPTY;
        }
    }

    
    bool isEqual(Hex& rhs) {
        return Vector3Equals(this->index, rhs.index);
    }


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