#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

class NekoSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    NekoSynthAudioProcessorEditor(NekoSynthAudioProcessor&);
    ~NekoSynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback();

private:
    NekoSynthAudioProcessor& audioProcessor;
    
    // Mode buttons
    juce::TextButton catButton;
    juce::TextButton dogButton;
    
    // Waveform selector
    juce::ComboBox waveformSelector;
    juce::Label waveformLabel;
    
    // ADSR + Volume
    juce::Slider volumeSlider;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    juce::Label volumeLabel;
    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;
    
    // NEW CONTROLS
    // 1. Pitch Bend Range
    juce::Slider pitchRangeSlider;
    juce::Label pitchRangeLabel;
    
    // 2. Filter controls
    juce::Slider filterCutoffSlider;
    juce::Slider filterResSlider;
    juce::Label filterCutoffLabel;
    juce::Label filterResLabel;
    
    // 5. Unison controls
    juce::Slider detuneSlider;
    juce::ComboBox voiceCountCombo;
    juce::Label detuneLabel;
    juce::Label voiceCountLabel;
    
    // 7. Level meter
    juce::Label meterLabel;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    // Attachments
    std::unique_ptr<ButtonAttachment> catAttachment;
    std::unique_ptr<ButtonAttachment> dogAttachment;
    std::unique_ptr<SliderAttachment> volumeAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    std::unique_ptr<ComboAttachment> waveformAttachment;
    
    // New attachments
    std::unique_ptr<SliderAttachment> pitchRangeAttachment;
    std::unique_ptr<SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<SliderAttachment> filterResAttachment;
    std::unique_ptr<SliderAttachment> detuneAttachment;
    std::unique_ptr<ComboAttachment> voiceCountAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NekoSynthAudioProcessorEditor)
};
