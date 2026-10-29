#include <cmath>

#include "Smoothener.h"

void Smoothener::prepareToPlay(double sampleRate, double smootheningTime){
  // sample period = 1 / sample rate
  // smootheningTime / sample period = smootheningTime * sample rate
  samplesDuringSmoothening.store(std::min(1, static_cast<int>(std::ceil(smootheningTime * sampleRate))));
  countdown.store(0);
}

Smoothener::Phase Smoothener::phase() const {
  return countdown.load() > 0 ? Phase::Smoothing : Phase::Idle;
}

void Smoothener::startSmoothening(){
  countdown.store(samplesDuringSmoothening.load());
}

template <typename T>
T Smoothener::smoothen(T from, T to){
  const auto window = static_cast<int>(samplesDuringSmoothening.load());

  // no smoothening requested: pass through
  if(window <= 0)
    return from;

  const auto currentCountdown = static_cast<int>(countdown.fetch_sub(1));
  const auto ratio = static_cast<T>(window - currentCountdown) / static_cast<T>(window);
  return (1 - ratio) * from + ratio * to;
}

template double Smoothener::smoothen(double from, double to);
template float Smoothener::smoothen(float from, float to);

bool Smoothener::isSmoothening(){
  return phase() == Phase::Smoothing;
}
