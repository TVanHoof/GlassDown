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
  juce::ignoreUnused(sampleRate);
  juce::ignoreUnused(maximumExpectedSamplesPerBlock);

  applySegments();
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
  std::vector<point> points;
  pluginlogic.applySegments(points);
}

juce::AudioProcessorEditor* PluginProcessor::createEditor(){
  return new PluginEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new PluginProcessor();
}
