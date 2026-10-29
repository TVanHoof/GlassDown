#include "PluginLogic.h"

#include <cmath>

PluginLogic::PluginLogic(){

}

template <typename T>
void PluginLogic::process(T* samples, int numSamples){
  for(int sampleIdx = 0; sampleIdx < numSamples; ++sampleIdx){
    switch(smoothener.phase()){
      case Smoothener::Phase::Idle:
        samples[sampleIdx] = trippleBuffer.getActiveBuffer().applyLookup(samples[sampleIdx]);
        break;

      case Smoothener::Phase::Smoothing: {
        Graph& active = trippleBuffer.getActiveBuffer();
        Graph& next = trippleBuffer.getNextActiveBuffer();

        const auto from = active.applyLookup(samples[sampleIdx]);
        const auto to = next.applyLookup(samples[sampleIdx]);

        samples[sampleIdx] = smoothener.smoothen(from, to);
        if(!smoothener.isSmoothening()){
          trippleBuffer.switchToNextBuffer(); // Smoothing complete: promote the next buffer to active
          if(third_updated.try_acquire()){ // adopt pending work.
            smoothener.startSmoothening();
          }
        }
        break;
      }
    }
  }
}

void PluginLogic::applySegments(const std::vector<point>& points){
  switch(smoothener.phase()){
    case Smoothener::Phase::Idle:
      // no smoothening happening: update next buffer and start to smoothen towards it
      trippleBuffer.getNextActiveBuffer().applySegments(points);
      smoothener.startSmoothening();
      break;

    case Smoothener::Phase::Smoothing:
      // mid-smooth: park it in the inactive buffer and flag it pending.
      trippleBuffer.getInactiveBuffer().applySegments(points);
      third_updated.release();
      break;
  }
}

void PluginLogic::loadPreset(const std::vector<point>& points){
  trippleBuffer.getActiveBuffer().applySegments(points);
}

void PluginLogic::prepareToPlay(double sampleRate, double smootheningTime){
  smoothener.prepareToPlay(sampleRate, smootheningTime);
}

template void PluginLogic::process(float*, int);
template void PluginLogic::process(double*, int);
