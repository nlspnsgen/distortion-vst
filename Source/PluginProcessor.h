#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#define DRIVE_ID "drive"
#define DRIVE_NAME "Drive"
#define RANGE_ID "range"
#define RANGE_NAME "Range"
#define BLEND_ID "blend"
#define BLEND_NAME "Blend"
#define VOLUME_ID "volume"
#define VOLUME_NAME "Volume"
class DistortionAudioProcessor  : public AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    DistortionAudioProcessor();
    ~DistortionAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void parameterChanged  (const String &parameterID, float newValue) override;
    
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    AudioProcessorValueTreeState treeState;

private:
    float drive;
    float blend;
    float range;
    float volume;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessor)
};
