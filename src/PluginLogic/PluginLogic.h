#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "Graph.h"

class PluginLogic{
  public:
    PluginLogic();

    template <typename T>
    void process(juce::AudioBuffer<T> &buffer, juce::MidiBuffer& midiMessages);


    void applySegments();

  private:
    Graph graph;
};
