#pragma once

#include "Segment.h"

#include <array>

class Graph{
  public:
    Graph();

    template <typename T>
    T applyLookup(T& sample);

    void applySegments();
  private:
    std::array<Segment, 500> segments;
    int nNodes{0};
};
