#pragma once

class Segment {
  public:
    // Default-constructible so Segment can be stored in std::array.
    // Represents a flat segment at y = 0.
    Segment() = default;

    Segment(double x_min, double y1, double x_max, double y2);

    void update(double x_min, double y1, double x_max, double y2);

    bool contains(double sample) const;

    double applyLookup(double sample) const;

    // Segment domain bounds, queried by Graph when clamping a sample.
    double getXMin() const { return x_min; }
    double getXMax() const { return x_max; }

  private:
    double x_min{};
    double x_max{};
    double slope{};
    double offset{};
};
