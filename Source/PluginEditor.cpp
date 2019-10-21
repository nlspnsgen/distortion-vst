#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionAudioProcessorEditor::DistortionAudioProcessorEditor (DistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    driveKnob.setSliderStyle(Slider::Rotary);
    driveKnob.setTextBoxStyle(Slider::NoTextBox, true, 100, 100);
    driveKnobValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, DRIVE_ID, driveKnob);
    addAndMakeVisible(&driveKnob);
    processor.treeState.addParameterListener(DRIVE_ID, &processor);
    driveLabel.setText("Drive", dontSendNotification);
    addAndMakeVisible(driveLabel);
  
    rangeKnob.setSliderStyle(Slider::Rotary);
    rangeKnob.setTextBoxStyle(Slider::NoTextBox, true, 100, 100);
    rangeKnobValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, RANGE_ID, rangeKnob);
    addAndMakeVisible(&rangeKnob);
    processor.treeState.addParameterListener(RANGE_ID, &processor);
    rangeLabel.setText("Range", dontSendNotification);
    addAndMakeVisible(rangeLabel);

    blendKnob.setSliderStyle(Slider::Rotary);
    blendKnob.setTextBoxStyle(Slider::NoTextBox, true, 100, 100);
    blendKnobValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, BLEND_ID, blendKnob);
    addAndMakeVisible(&blendKnob);
    processor.treeState.addParameterListener(BLEND_ID, &processor);
    blendLabel.setText("Blend", dontSendNotification);
    addAndMakeVisible(blendLabel);
    
    
    volumeKnob.setSliderStyle(Slider::Rotary);
    volumeKnob.setTextBoxStyle(Slider::NoTextBox, true, 100, 100);
    volumeKnobValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, VOLUME_ID, volumeKnob);
    addAndMakeVisible(&volumeKnob);
    processor.treeState.addParameterListener(VOLUME_ID, &processor);
    volumeLabel.setText("Volume", dontSendNotification);
    addAndMakeVisible(volumeLabel);
    

    setSize (500, 200);
}

DistortionAudioProcessorEditor::~DistortionAudioProcessorEditor()
{
}

//==============================================================================
void DistortionAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
}

void DistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto rectangle = getLocalBounds();
    driveKnob.setBounds(rectangle.removeFromLeft(getWidth()/4).reduced(10));
    driveLabel.setBounds(35, 130, 100, 50);
    rangeKnob.setBounds(rectangle.removeFromLeft(getWidth()/4).reduced(10));
    rangeLabel.setBounds(165, 130, 100, 50);
    blendKnob.setBounds(rectangle.removeFromLeft(getWidth()/4).reduced(10));
    blendLabel.setBounds(290, 130, 100, 50);
    volumeKnob.setBounds(rectangle.removeFromLeft(getWidth()/4).reduced(10));
    volumeLabel.setBounds(410, 130, 100, 50);
}
