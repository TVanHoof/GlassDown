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

