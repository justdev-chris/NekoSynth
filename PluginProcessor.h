#pragma once

// Include JUCE modules directly (no JuceHeader.h)
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_plugin_client/juce_audio_plugin_client.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>

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
    std::atomic<float>* volume = nullptr;

private:
    class NekoVoice;
    
    juce::Synthesiser synth;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NekoSynthAudioProcessor)
};
