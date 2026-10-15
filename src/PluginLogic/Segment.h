// SPDX-License-Identifier: AGPL-3.0-or-later

/*
 * Segment of a GlassDown segment graph.
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

class Segment {
  public:
    // Default-constructible so Segment can be stored in std::array.
    // Represents a flat segment at y = 0.
    Segment() = default;

    Segment(double x_min, double y1, double x_max, double y2);

    void update(double x_min, double y1, double x_max, double y2);

    bool contains(double sample) const;

    double applyLookup(double sample) const;

    // Segment domain bounds, queried by Graph when clamping a sample.
    double getXMin() const { return x_min; }
    double getXMax() const { return x_max; }

  private:
    double x_min{};
    double x_max{};
    double slope{};
    double offset{};
};
