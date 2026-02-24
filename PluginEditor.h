#pragma once
#include <JuceHeader.h>
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
    
    // GUI Components
    juce::TextButton catButton;
    juce::TextButton dogButton;
    juce::Slider volumeSlider;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    // Labels
    juce::Label volumeLabel;
    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;
    
    // Animation
    float earWiggle = 0.0f;
    float tailWag = 0.0f;
    int lastNote = 0;
    
    // Parameter attachments
    using Attachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<Attachment> catAttachment;
    std::unique_ptr<Attachment> dogAttachment;
    std::unique_ptr<SliderAttachment> volumeAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NekoSynthAudioProcessorEditor)
};