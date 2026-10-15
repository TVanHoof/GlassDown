// SPDX-License-Identifier: AGPL-3.0-or-later

/*
 * Segment graph used by GlassDown.
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

#include "Segment.h"

#include <vector>
#include <array>

using point = std::pair<double, double>;
static constexpr int kMaxSegments = 1024;

class Graph{
  public:
    Graph();

    template <typename T>
    T applyLookup(T& sample);

    void applySegments(const std::vector<point>& points);
  private:
    std::array<Segment, kMaxSegments> segments{};
    size_t size{};
};
