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
