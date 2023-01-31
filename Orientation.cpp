struct Orientation {
    const double f0, f1, f2, f3;
    const double b0, b1, b2, b3;
    const double startAngle; // in multiples of 60°
    Orientation(double f0_, double f1_, double f2_, double f3_,
                double b0_, double b1_, double b2_, double b3_,
                double startAngle_)
    : f0(f0_), f1(f1_), f2(f2_), f3(f3_),
      b0(b0_), b1(b1_), b2(b2_), b3(b3_),
      startAngle(startAngle_) {}
};