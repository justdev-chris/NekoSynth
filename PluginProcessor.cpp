#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_audio_formats/juce_audio_formats.h>
#include <cmath>

class NekoSynthAudioProcessor::NekoVoice : public juce::SynthesiserVoice
{
public:
    NekoVoice(NekoSynthAudioProcessor& p) : processor(p) 
    {
        envelope.setSampleRate(44100.0);
    }
    
    bool canPlaySound(juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
    }
    
    void startNote(int midiNoteNumber, float velocity, 
                   juce::SynthesiserSound*, int) override
    {
        currentAngle = 0.0;
        level = velocity * 0.5;
        tailWagPhase = 0.0;
        
        baseFrequency = 440.0f * std::pow(2.0f, (midiNoteNumber - 69) / 12.0f);
        
        juce::ADSR::Parameters params;
        params.attack = *processor.attack;
        params.decay = *processor.decay;
        params.sustain = *processor.sustain;
        params.release = *processor.release;
        envelope.setParameters(params);
        
        envelope.noteOn();
    }
    
    void stopNote(float, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            envelope.noteOff();
        }
        else
        {
            clearCurrentNote();
            envelope.reset();
        }
    }
    
    void pitchWheelMoved(int newValue) override
    {
        pitchBend = (newValue - 8192) / 8192.0f;
    }
    
    void controllerMoved(int, int) override {}
    
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        if (!isVoiceActive())
            return;
        
        while (--numSamples >= 0)
        {
            float pitchMultiplier = 1.0f + pitchBend * 0.05f;
            float frequency = baseFrequency * pitchMultiplier;
            
            // Animal pitch modulation
            if (*processor.catMode > 0.5f)
            {
                float meowPhase = std::fmod(currentAngle * 0.2f, 1.0f);
                
                if (meowPhase < 0.3f)
                    frequency *= 1.0f + (meowPhase / 0.3f) * 0.4f;
                else if (meowPhase < 0.7f)
                    frequency *= 1.4f - ((meowPhase - 0.3f) / 0.4f) * 0.4f;
                else
                    frequency *= 1.0f + std::sin(meowPhase * 10.0f) * 0.05f;
                
                frequency *= 1.0f + std::sin(currentAngle * 5.0f) * 0.02f;
            }
            
            if (*processor.dogMode > 0.5f)
            {
                float barkPhase = std::fmod(currentAngle * 0.5f, 1.0f);
                
                if (barkPhase < 0.1f)
                    frequency *= 1.0f + std::sin(barkPhase * 31.4f) * 0.2f;
                else if (barkPhase < 0.3f)
                    frequency *= 0.9f + std::cos(barkPhase * 15.7f) * 0.1f;
                else
                    frequency *= 0.1f;
                
                float noise = std::sin(currentAngle * 50.0f) * 0.5f;
                frequency *= 1.0f + noise * 0.03f * (barkPhase < 0.3f ? 1.0f : 0.0f);
            }
            
            // Waveform selection
            float sample = 0.0f;
            int waveType = (int)*processor.waveform;
            
            if (*processor.catMode > 0.5f)
            {
                // Cat mode uses sine-based
                sample = std::sin(currentAngle);
                if (waveType == 1) // Add saw characteristics
                    sample += std::sin(currentAngle * 2.0f) * 0.3f;
                else if (waveType == 2) // Add square characteristics
                    sample = sample > 0 ? 0.5f : -0.5f;
            }
            else
            {
                // Dog mode uses saw-based
                sample = 2.0f * (currentAngle / juce::MathConstants<float>::twoPi) - 1.0f;
                
                if (waveType == 0) // Make it more sine-like
                    sample = std::sin(currentAngle);
                else if (waveType == 2) // Square
                    sample = sample > 0 ? 0.5f : -0.5f;
                else // Saw
                    sample = std::tanh(sample * 2.0f) * 0.5f;
            }
            
            float env = envelope.getNextSample();
            sample *= level * env * *processor.volume;
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, sample * 0.5f);
            }
            
            currentAngle += frequency * 2.0 * juce::MathConstants<double>::pi / getSampleRate();
            
            if (currentAngle >= juce::MathConstants<double>::twoPi)
                currentAngle -= juce::MathConstants<double>::twoPi;
            
            startSample++;
        }
        
        if (!envelope.isActive())
            clearCurrentNote();
    }
    
    juce::ADSR envelope;

private:
    NekoSynthAudioProcessor& processor;
    
    double currentAngle = 0.0;
    double baseFrequency = 440.0;
    float level = 0.0;
    float pitchBend = 0.0f;
    float tailWagPhase = 0.0f;
};

NekoSynthAudioProcessor::NekoSynthAudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", createParameters())
{
    catMode = apvts.getRawParameterValue("catMode");
    dogMode = apvts.getRawParameterValue("dogMode");
    volume = apvts.getRawParameterValue("volume");
    attack = apvts.getRawParameterValue("attack");
    decay = apvts.getRawParameterValue("decay");
    sustain = apvts.getRawParameterValue("sustain");
    release = apvts.getRawParameterValue("release");
    waveform = apvts.getRawParameterValue("waveform");
    
    for (int i = 0; i < 8; ++i)
        synth.addVoice(new NekoVoice(*this));
    
    auto* buffer = new juce::AudioSampleBuffer();
    synth.addSound(new juce::SamplerSound("default", *buffer, 440, 0, 0, 0, 10.0));
}

NekoSynthAudioProcessor::~NekoSynthAudioProcessor()
{
}

void NekoSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* voice = dynamic_cast<NekoVoice*>(synth.getVoice(i)))
        {
            voice->envelope.setSampleRate(sampleRate);
        }
    }
}

void NekoSynthAudioProcessor::releaseResources()
{
}

void NekoSynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    for (int i = 0; i < buffer.getNumChannels(); ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* NekoSynthAudioProcessor::createEditor()
{
    return new NekoSynthAudioProcessorEditor(*this);
}

juce::AudioProcessorValueTreeState::ParameterLayout NekoSynthAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("catMode", "Cat Mode", 0.0f, 1.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("dogMode", "Dog Mode", 0.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 0.0f, 5.0f, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("decay", "Decay", 0.0f, 5.0f, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", 0.0f, 1.0f, 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("release", "Release", 0.0f, 5.0f, 0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("volume", "Volume", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("waveform", "Waveform", 
        juce::StringArray({ "Sine", "Saw", "Square" }), 0));
    
    return { params.begin(), params.end() };
}

void NekoSynthAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void NekoSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr)
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NekoSynthAudioProcessor();
}