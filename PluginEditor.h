#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

class NekoSynthAudioProcessorEditor : public juce::AudioProcessorEditor,
                                      private juce::Timer
{
public:
    NekoSynthAudioProcessorEditor(NekoSynthAudioProcessor&);
    ~NekoSynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    NekoSynthAudioProcessor& audioProcessor;
    
    // Group boxes
    juce::GroupComponent modeGroup;
    juce::GroupComponent oscGroup;
    juce::GroupComponent unisonGroup;
    juce::GroupComponent ampGroup;
    juce::GroupComponent filterGroup;
    juce::GroupComponent pitchGroup;
    
    // Mode buttons
    juce::TextButton catButton;
    juce::TextButton dogButton;
    
    // Waveform selector
    juce::ComboBox waveformSelector;
    
    // Unison controls
    juce::ComboBox voiceCountCombo;
    
    // ADSR + Volume
    juce::Slider volumeSlider;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    // Filter controls
    juce::Slider filterCutoffSlider;
    juce::Slider filterResSlider;
    
    // Pitch controls
    juce::Slider pitchRangeSlider;
    juce::Slider detuneSlider;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    std::unique_ptr<ButtonAttachment> catAttachment;
    std::unique_ptr<ButtonAttachment> dogAttachment;
    std::unique_ptr<ComboAttachment> waveformAttachment;
    std::unique_ptr<SliderAttachment> volumeAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    std::unique_ptr<SliderAttachment> pitchRangeAttachment;
    std::unique_ptr<SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<SliderAttachment> filterResAttachment;
    std::unique_ptr<SliderAttachment> detuneAttachment;
    std::unique_ptr<ComboAttachment> voiceCountAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NekoSynthAudioProcessorEditor)
};