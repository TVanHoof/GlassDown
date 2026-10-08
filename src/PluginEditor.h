#pragma once

#include "PluginProcessor.h"

class PluginEditor: public juce::AudioProcessorEditor{
  public:
    explicit PluginEditor(PluginProcessor& p);

    void resized() override;
  private:
};
