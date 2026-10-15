// SPDX-License-Identifier: AGPL-3.0-or-later

/*
 * Sample processing for GlassDown.
 *
 * Copyright (C) 2026  Thomas Van Hoof
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
