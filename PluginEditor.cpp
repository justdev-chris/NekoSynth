#include "PluginProcessor.h"
#include "PluginEditor.h"

NekoSynthAudioProcessorEditor::NekoSynthAudioProcessorEditor(NekoSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    catButton.setButtonText("🐱 CAT");
    catButton.setClickingTogglesState(true);
    catButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(40, 40, 50));
    catButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(80, 140, 200));
    catButton.setColour(juce::TextButton::textColourOffId, juce::Colours::grey);
    catButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    addAndMakeVisible(catButton);
    
    dogButton.setButtonText("🐶 DOG");
    dogButton.setClickingTogglesState(true);
    dogButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(40, 40, 50));
    dogButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(180, 130, 80));
    dogButton.setColour(juce::TextButton::textColourOffId, juce::Colours::grey);
    dogButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    addAndMakeVisible(dogButton);
    
    volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colour::fromRGB(100, 100, 120));
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(200, 200, 220));
    addAndMakeVisible(volumeSlider);
    volumeLabel.setText("VOL", juce::dontSendNotification);
    volumeLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    volumeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(volumeLabel);
    
    for (auto* slider : { &attackSlider, &decaySlider, &sustainSlider, &releaseSlider })
    {
        slider->setSliderStyle(juce::Slider::LinearVertical);
        slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        slider->setColour(juce::Slider::trackColourId, juce::Colour::fromRGB(100, 100, 120));
        slider->setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(200, 200, 220));
        addAndMakeVisible(slider);
    }
    
    attackLabel.setText("A", juce::dontSendNotification);
    decayLabel.setText("D", juce::dontSendNotification);
    sustainLabel.setText("S", juce::dontSendNotification);
    releaseLabel.setText("R", juce::dontSendNotification);
    
    for (auto* label : { &attackLabel, &decayLabel, &sustainLabel, &releaseLabel })
    {
        label->setColour(juce::Label::textColourId, juce::Colours::grey);
        label->setJustificationType(juce::Justification::centred);
        addAndMakeVisible(label);
    }
    
    catAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "catMode", catButton);
    dogAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "dogMode", dogButton);
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "volume", volumeSlider);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);
    
    setSize(400, 250);
}

NekoSynthAudioProcessorEditor::~NekoSynthAudioProcessorEditor()
{
}

void NekoSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(25, 25, 30));
    
    if (catButton.getToggleState())
        g.setColour(juce::Colour::fromRGB(80, 140, 200));
    else if (dogButton.getToggleState())
        g.setColour(juce::Colour::fromRGB(180, 130, 80));
    else
        g.setColour(juce::Colours::darkgrey);
    
    g.fillRect(0, 0, getWidth(), 3);
    
    // justdev-chris credit
    g.setColour(juce::Colours::white.withAlpha(0.3f));
    g.setFont(juce::Font(12.0f));
    g.drawText("justdev-chris", getWidth() - 100, getHeight() - 20, 90, 15, juce::Justification::right);
}

void NekoSynthAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    
    auto topRow = area.removeFromTop(40);
    catButton.setBounds(topRow.removeFromLeft(100).reduced(2));
    dogButton.setBounds(topRow.removeFromLeft(100).reduced(2));
    
    auto sliderArea = area.reduced(10, 20);
    int sliderWidth = sliderArea.getWidth() / 5;
    
    volumeLabel.setBounds(sliderArea.removeFromLeft(sliderWidth).withHeight(20));
    volumeSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5, 20));
    
    attackLabel.setBounds(sliderArea.removeFromLeft(sliderWidth).withHeight(20));
    attackSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5, 20));
    
    decayLabel.setBounds(sliderArea.removeFromLeft(sliderWidth).withHeight(20));
    decaySlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5, 20));
    
    sustainLabel.setBounds(sliderArea.removeFromLeft(sliderWidth).withHeight(20));
    sustainSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5, 20));
    
    releaseLabel.setBounds(sliderArea.removeFromLeft(sliderWidth).withHeight(20));
    releaseSlider.setBounds(sliderArea.reduced(5, 20));
}
