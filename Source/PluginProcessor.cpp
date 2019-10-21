#include "PluginProcessor.h"
#include "PluginEditor.h"

DistortionAudioProcessor::DistortionAudioProcessor()
#ifdef JucePlugin_PreferredChannelConfigurations
         : AudioProcessor (BusesProperties()
                         #if ! JucePlugin_IsMidiEffect
                          #if ! JucePlugin_IsSynth
                           .withInput  ("Input",  AudioChannelSet::stereo(), true)
                          #endif
                           .withOutput ("Output", AudioChannelSet::stereo(), true)
                         #endif
                           ), treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#else
        : AudioProcessor (BusesProperties()
                    #if ! JucePlugin_IsMidiEffect
                        #if ! JucePlugin_IsSynth
                      .withInput  ("Input",  AudioChannelSet::stereo(), true)
                        #endif
                      .withOutput ("Output", AudioChannelSet::stereo(), true)
                    #endif
                      ), treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    treeState.addParameterListener("drive", this);
    drive = 0.9f;
    range = 0.1f;
    blend = 0.1f;
    volume = 0.0f;
}

DistortionAudioProcessor::~DistortionAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout DistortionAudioProcessor::createParameterLayout(){
    AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<AudioParameterFloat>(DRIVE_ID, DRIVE_NAME, 0.0f, 1.0f, 0.0f));
    layout.add(std::make_unique<AudioParameterFloat>(RANGE_ID, RANGE_NAME, 0.1f, 20.0f, 0.1f));
    layout.add(std::make_unique<AudioParameterFloat>(BLEND_ID, BLEND_NAME, 0.1f, 1.0f, 0.0f));
    layout.add(std::make_unique<AudioParameterFloat>(VOLUME_ID, VOLUME_NAME, 0.0f, 2.0f, 0.0f));
    return layout;
}
void DistortionAudioProcessor::parameterChanged  (const String &parameterID, float newValue){
    if (parameterID.compare("drive")==0) drive = newValue;
    if (parameterID.compare("range")==0) range = newValue;
    if (parameterID.compare("blend")==0) blend = newValue;
    if (parameterID.compare("volume")==0) volume = newValue;
}

const String DistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionAudioProcessor::getNumPrograms()
{
    return 1;
}

int DistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionAudioProcessor::setCurrentProgram (int index)
{
}

const String DistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void DistortionAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistortionAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); sample++){
            float cleanSig = *channelData;
            *channelData *= drive*range;
            *channelData = (((((2.0f/float_Pi) * atan(*channelData))*blend)+(cleanSig * (1.0f / blend))) / 2)*volume;
            channelData++;
        }
    }
}

//==============================================================================
bool DistortionAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* DistortionAudioProcessor::createEditor()
{
    return new DistortionAudioProcessorEditor (*this);
}

void DistortionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void DistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionAudioProcessor();
}


