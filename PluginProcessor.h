#pragma once
#include <JuceHeader.h>

class NekoSynthAudioProcessor : public juce::AudioProcessor
{
public:
    NekoSynthAudioProcessor();
    ~NekoSynthAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "NekoSynth"; }

    // Parameters
    juce::AudioProcessorValueTreeState apvts;
    
    // Animal selection
    std::atomic<float>* catMode = nullptr;
    std::atomic<float>* dogMode = nullptr;

private:
    // Synth voice class (defined in .cpp)
    class NekoVoice;
    
    juce::Synthesiser synth;
    
    // Parameter layout
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NekoSynthAudioProcessor)
};