// SPDX-License-Identifier: AGPL-3.0-or-later

/*
 * The GlassDown audio plugin.
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

#include <juce_audio_processors/juce_audio_processors.h>
#include <PluginLogic/PluginLogic.h>

class PluginProcessor: public juce::AudioProcessor{
  public:
    PluginProcessor();
    ~PluginProcessor() override;

    // boilerplate JUCE requirements
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    const juce::String getProgramName(int index) override;

    bool hasEditor() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    void changeProgramName(int index, const juce::String& name) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;

    void releaseResources() override;

    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override;
    void processBlock(juce::AudioBuffer<double> &buffer, juce::MidiBuffer& midiMessages) override;

    double getTailLengthSeconds() const override;

    juce::AudioProcessorEditor* createEditor() override;

    // custom
    void applySegments();
    void loadPreset();

  private:
    PluginLogic pluginlogic;
};
