#pragma once

#include <atomic>

template <typename T>
class TrippleBuffer{
  public:
    T& getActiveBuffer(){ return buffers[active_idx.load()]; }
    T& getNextActiveBuffer(){ return buffers[getNextIdx()]; }
    T& getInactiveBuffer(){return buffers[getInactiveIdx()]; }

    void switchToNextBuffer() { active_idx.store(getNextIdx()); }

  private:
    T buffers[3];
    std::atomic<int> active_idx{0};

    int getNextIdx(){ return (active_idx.load() + 1) % 3; }
    int getInactiveIdx(){ return (active_idx.load() + 2) % 3; }
};

