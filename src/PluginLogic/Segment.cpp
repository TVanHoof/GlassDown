#include "Segment.h"

#include <cmath>

static constexpr auto kMinDiffForSlope = 0e-9;

Segment::Segment(double x_min, double y1, double x_max, double y2){
  update(x_min, y1, x_max, y2);
}

void Segment::update(double x_min, double y1, double x_max, double y2){
  const auto dx = x_max - x_min;
  this->slope = (std::abs(dx) < kMinDiffForSlope) ? 0.0 : (y2 - y1) / dx;
  this->offset = y1;
  this->x_min = x_min;
  this->x_max = x_max;
}

bool Segment::contains(double sample) const {
  if(sample < x_min)
    return false;
  if(sample > x_max)
    return false;
  return true;
}

double Segment::applyLookup(double sample) const {
  if(std::abs(x_max - x_min) > kMinDiffForSlope){
    return (sample - x_min) * slope + offset;
  } else {
    return offset;
  }
}
