#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DistortionAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DistortionAudioProcessorEditor (DistortionAudioProcessor&);
    ~DistortionAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    DistortionAudioProcessor& processor;
    Slider driveKnob;
    Slider rangeKnob;
    Slider blendKnob;
    Slider volumeKnob;
    Label driveLabel;
    Label rangeLabel;
    Label blendLabel;
    Label volumeLabel;

public:
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveKnobValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> rangeKnobValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> blendKnobValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> volumeKnobValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessorEditor)
};
