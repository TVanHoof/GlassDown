#pragma once

// Deliberately free of any JUCE dependency: this library holds the DSP logic
// only, so it compiles once without dragging in the JUCE modules, and can be
// unit-tested without a JUCE build. Callers own buffer/channel iteration.
#include "Graph.h"

class PluginLogic{
  public:
    PluginLogic();

    // Processes a single channel of samples in place.
    template <typename T>
    void process(T* samples, int numSamples);

    using point = std::pair<double, double>;
    void applySegments(const std::vector<point>& points);

  private:
    Graph graph;
};
