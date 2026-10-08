#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class PluginProcessor: public juce::AudioProcessor{
  public:
    PluginProcessor();
    ~PluginProcessor() override;

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
    void processBlock(juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages) override;

    double getTailLengthSeconds() const override;

    juce::AudioProcessorEditor* createEditor() override;

  private:
    template <typename T>
    void process(juce::AudioBuffer<T> &buffer, juce::MidiBuffer& midiMessages);
};
