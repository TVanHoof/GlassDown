#pragma once

#include <semaphore>

// Deliberately free of any JUCE dependency: this library holds the DSP logic
// only, so it compiles once without dragging in the JUCE modules, and can be
// unit-tested without a JUCE build. Callers own buffer/channel iteration.
#include "Graph.h"
#include "Smoothener.h"
#include "TrippleBuffer.h"

class PluginLogic{
  public:
    PluginLogic();

    // Processes a single channel of samples in place.
    template <typename T>
    void process(T* samples, int numSamples);

    void prepareToPlay(double sampleRate, double smootheningTime);

    using point = std::pair<double, double>;
    void applySegments(const std::vector<point>& points);
    void loadPreset(const std::vector<point>& points);

  private:
    std::binary_semaphore third_updated{0};

    TrippleBuffer<Graph> trippleBuffer;
    Smoothener smoothener;
};
