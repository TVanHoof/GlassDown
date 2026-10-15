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

#include <semaphore>

// Deliberately free of any JUCE dependency: this library holds the DSP logic
// only, so it compiles once without dragging in the JUCE modules, and can be
// unit-tested without a JUCE build. Callers own buffer/channel iteration.
#include "Graph.h"
#include "Smoothener.h"
#include "TrippleBuffer.h"

class PluginLogic{
  public:
    PluginLogic();

    // Processes a single channel of samples in place.
    template <typename T>
    void process(T* samples, int numSamples);

    void prepareToPlay(double sampleRate, double smootheningTime);

    using point = std::pair<double, double>;
    void applySegments(const std::vector<point>& points);
    void loadPreset(const std::vector<point>& points);

  private:
    std::binary_semaphore third_updated{0};

    TrippleBuffer<Graph> trippleBuffer;
    Smoothener smoothener;
};
