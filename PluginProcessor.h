#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_plugin_client/juce_audio_plugin_client.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>
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

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;
    
    // Existing parameters
    std::atomic<float>* catMode = nullptr;
    std::atomic<float>* dogMode = nullptr;
    std::atomic<float>* volume = nullptr;
    std::atomic<float>* attack = nullptr;
    std::atomic<float>* decay = nullptr;
    std::atomic<float>* sustain = nullptr;
    std::atomic<float>* release = nullptr;
    std::atomic<float>* waveform = nullptr;
    
    // NEW PARAMETERS
    std::atomic<float>* pitchBendRange = nullptr;  // 1. Pitch bend range
    std::atomic<float>* filterCutoff = nullptr;    // 2. Low-pass filter cutoff
    std::atomic<float>* filterRes = nullptr;        // 2. Filter resonance
    std::atomic<float>* detune = nullptr;           // 5. Unison detune
    std::atomic<float>* voiceCount = nullptr;       // 5. Number of unison voices

private:
    class NekoVoice;
    
    juce::Synthesiser synth;
    
    // For level meter
    std::atomic<float> currentLevel { 0.0f };
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
public:
    float getCurrentLevel() const { return currentLevel.load(); }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NekoSynthAudioProcessor)
};
