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

#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginProcessor::PluginProcessor():
                AudioProcessor(){
}
PluginProcessor::~PluginProcessor(){
}

const juce::String PluginProcessor::getName() const {  return JucePlugin_Name; }
bool PluginProcessor::acceptsMidi() const {      return JucePlugin_WantsMidiInput; }
bool PluginProcessor::producesMidi() const {     return JucePlugin_ProducesMidiOutput; }
bool PluginProcessor::isMidiEffect() const {     return JucePlugin_IsMidiEffect; }
bool PluginProcessor::hasEditor() const {        return true; }

int PluginProcessor::getNumPrograms() {    return 1; }
int PluginProcessor::getCurrentProgram() { return 0; }
void PluginProcessor::setCurrentProgram(int index) { juce::ignoreUnused(index); }
const juce::String PluginProcessor::getProgramName(int index) {juce::ignoreUnused(index); return "None"; }
void PluginProcessor::changeProgramName(int index, const juce::String& name) { juce::ignoreUnused(index, name); }

double PluginProcessor::getTailLengthSeconds() const { return 0.0f; }

void PluginProcessor::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock){
  juce::ignoreUnused(maximumExpectedSamplesPerBlock);

  loadPreset();
  // pluginlogic.prepareToPlay needs to the last call to not fade into the graph
  pluginlogic.prepareToPlay(sampleRate, 0.02f);
}

void PluginProcessor::releaseResources(){

}

void PluginProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
  juce::ignoreUnused(midiMessages);

  const auto nChannels = buffer.getNumChannels();
  const auto nSamples  = buffer.getNumSamples();

  for(int channelIdx = 0; channelIdx < nChannels; ++channelIdx)
    pluginlogic.process(buffer.getWritePointer(channelIdx), nSamples);
}

void PluginProcessor::processBlock(juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages){
  juce::ignoreUnused(midiMessages);

  const auto nChannels = buffer.getNumChannels();
  const auto nSamples  = buffer.getNumSamples();

  for(int channelIdx = 0; channelIdx < nChannels; ++channelIdx)
    pluginlogic.process(buffer.getWritePointer(channelIdx), nSamples);
}

void PluginProcessor::getStateInformation(juce::MemoryBlock& destData){
  juce::ignoreUnused(destData);
}
void PluginProcessor::setStateInformation(const void* data, int sizeInBytes){
  juce::ignoreUnused(data);
  juce::ignoreUnused(sizeInBytes);
}

void PluginProcessor::applySegments(){
  // GUI-thread -> PluginLogic access to state used by processBlock must hold the callback lock.
  juce::CriticalSection::ScopedLockType lock(getCallbackLock());
  std::vector<point> points;
  pluginlogic.applySegments(points);
}

void PluginProcessor::loadPreset(){
  // GUI-thread -> PluginLogic access to state used by processBlock must hold the callback lock.
  juce::CriticalSection::ScopedLockType lock(getCallbackLock());
  std::vector<point> points;
  pluginlogic.loadPreset(points);
}

juce::AudioProcessorEditor* PluginProcessor::createEditor(){
  return new PluginEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new PluginProcessor();
}
