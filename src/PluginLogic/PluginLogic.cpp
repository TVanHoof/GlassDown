#include "PluginLogic.h"

PluginLogic::PluginLogic(){

}

template <typename T>
void PluginLogic::process(juce::AudioBuffer<T> &buffer, juce::MidiBuffer& midiMessages){
  juce::ignoreUnused(midiMessages);

  const int nChannels = buffer.getNumChannels();
  const int nSamples = buffer.getNumSamples();

  for(int channelIdx = 0; channelIdx < nChannels; channelIdx++){
    auto* samples = buffer.getWritePointer(channelIdx);
    for(int sampleIdx = 0; sampleIdx < nSamples; sampleIdx++){
      samples[sampleIdx] = graph.applyLookup(samples[sampleIdx]);
    }
  }
}

void PluginLogic::applySegments(){
  graph.applySegments();
}

// Explicit instantiations: the definition lives in this TU, but callers live
// in PluginProcessor.cpp, so both types must be listed here.
template void PluginLogic::process(juce::AudioBuffer<float>&, juce::MidiBuffer&);
template void PluginLogic::process(juce::AudioBuffer<double>&, juce::MidiBuffer&);
