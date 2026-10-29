#pragma once

#include <atomic>

class Smoothener{
  public:
    enum class Phase { Idle, Smoothing };

    void prepareToPlay(double sampleRate, double smootheningTime);

    Phase phase() const;
    void startSmoothening();
    bool isSmoothening();
    template <typename T>
    T smoothen(T from, T to);

  private:
    std::atomic<int> countdown{0};
    std::atomic<int> samplesDuringSmoothening{1};
};
