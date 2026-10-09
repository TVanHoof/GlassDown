#pragma once

#include "Segment.h"

#include <vector>

using point = std::pair<double, double>;

class Graph{
  public:
    Graph();

    template <typename T>
    T applyLookup(T& sample);

    void applySegments(const std::vector<point>& segments);
  private:
    std::vector<Segment> segments;
};
