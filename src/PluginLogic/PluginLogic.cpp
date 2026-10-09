#include "PluginLogic.h"

PluginLogic::PluginLogic(){

}

template <typename T>
void PluginLogic::process(T* samples, int numSamples){
  for(int sampleIdx = 0; sampleIdx < numSamples; ++sampleIdx){
    samples[sampleIdx] = graph.applyLookup(samples[sampleIdx]);
  }
}

void PluginLogic::applySegments(const std::vector<point>& points){
  graph.applySegments(points);
}

// Explicit instantiations: the definition lives in this TU, but callers live
// in PluginProcessor.cpp, so both types must be listed here.
template void PluginLogic::process(float*, int);
template void PluginLogic::process(double*, int);
