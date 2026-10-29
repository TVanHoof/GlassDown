#pragma once

#include "Segment.h"

#include <vector>
#include <array>

using point = std::pair<double, double>;
static constexpr int kMaxSegments = 1024;

class Graph{
  public:
    Graph();

    template <typename T>
    T applyLookup(T& sample);

    void applySegments(const std::vector<point>& points);
  private:
    std::array<Segment, kMaxSegments> segments{};
    size_t size{};
};
