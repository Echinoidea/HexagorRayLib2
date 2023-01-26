#include <raylib.h>

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

struct Hex {
    int r, q;
    Hex* adjacents;

    int radius = 50;
    Color color = (Color) {55, 107, 186, 255};

    Vector2 position;

    HexClaimState claimState = HCS_UNCLAIMED;
    HexFeatureState featureState = HFS_EMPTY;
    HexTroopState troopState = HTS_EMPTY;

    Hex(int r_, int q_): r(r_), q(q_) {}

    Hex() {} 
    
};