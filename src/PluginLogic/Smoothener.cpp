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
