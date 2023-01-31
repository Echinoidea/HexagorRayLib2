#include <Orientation.cpp>
#include <cmath>
#include <raylib.h>

const Orientation layoutPointy
  = Orientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
                sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
                0.5);

struct Layout {
    const Orientation orientation;
    const Vector2 size;
    const Vector2 origin;

    Layout(Orientation orientation_, Vector2 size_, Vector2 origin_)
    : orientation(orientation_), size(size_), origin(origin_) {}
};