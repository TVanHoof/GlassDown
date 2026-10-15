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

#include <atomic>

#include "Graph.h"

Graph::Graph(){
}

template <typename T>
T Graph::applyLookup(T& in){
  const double sample = static_cast<double>(in);

  // Not enough segments yet: pass the sample through unchanged, but protect against possible damage
  if(size < 1)
    return std::clamp(in, static_cast<T>(-1), static_cast<T>(1));

  if(sample < segments[0].getXMin())
    return std::clamp(static_cast<T>(segments[0].applyLookup(sample)), static_cast<T>(-1), static_cast<T>(1));
  if(sample > segments[size-1].getXMax())
    return std::clamp(static_cast<T>(segments[size-1].applyLookup(sample)), static_cast<T>(-1), static_cast<T>(1));

  size_t min = 0;
  size_t max = size - 1;
  size_t mid = (min + max ) / 2;

//{
//  const auto& seg = segments[mid];
//  if(seg.contains(sample))
//    return static_cast<T>(seg.applyLookup(sample));
//  if(sample < seg.getXMin()){
//    max = mid;
//  }
//  if(sample > seg.getXMax()){
//    min = mid;
//  }
//  mid = (min + max) / 2;
//}

  for(size_t i = 0; i < size; i++){
    const auto& seg = segments[i];
    if(seg.contains(sample)){
      return static_cast<T>(seg.applyLookup(sample));
    }
  }

  //should never get here
  return sample;
}

// Explicit instantiations: the definition lives in this TU, so every type used
// by callers must be listed here.
template float Graph::applyLookup(float&);
template double Graph::applyLookup(double&);

void Graph::applySegments(const std::vector<point>& points){
  size = points.size() < 2 ? 0 :  points.size() - 1; // 2 points create 1 segment, x points create x - 1 segments
  if(size >= kMaxSegments) size = kMaxSegments - 1;
  for(size_t i = 1; i <= size; i++){
    segments[i-1].update(points[i-1].first,
                         points[i-1].second,
                         points[i].first,
                         points[i].second);
  }
}
