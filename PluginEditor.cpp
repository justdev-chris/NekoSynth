#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NekoSynthAudioProcessorEditor::NekoSynthAudioProcessorEditor(NekoSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    catButton.setButtonText("😺 MEOW");
    catButton.setClickingTogglesState(true);
    catButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::orange);
    addAndMakeVisible(catButton);
    
    dogButton.setButtonText("🐕 BARK");
    dogButton.setClickingTogglesState(true);
    dogButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::brown);
    addAndMakeVisible(dogButton);
    
    // Sliders setup
    volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::pink);
    addAndMakeVisible(volumeSlider);
    volumeLabel.setText("VOL", juce::dontSendNotification);
    volumeLabel.attachToComponent(&volumeSlider, false);
    volumeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(volumeLabel);
    
    attackSlider.setSliderStyle(juce::Slider::LinearVertical);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    attackSlider.setColour(juce::Slider::thumbColourId, juce::Colours::lightblue);
    addAndMakeVisible(attackSlider);
    attackLabel.setText("A", juce::dontSendNotification);
    attackLabel.attachToComponent(&attackSlider, false);
    attackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(attackLabel);
    
    decaySlider.setSliderStyle(juce::Slider::LinearVertical);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    decaySlider.setColour(juce::Slider::thumbColourId, juce::Colours::lightgreen);
    addAndMakeVisible(decaySlider);
    decayLabel.setText("D", juce::dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, false);
    decayLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(decayLabel);
    
    sustainSlider.setSliderStyle(juce::Slider::LinearVertical);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    sustainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    addAndMakeVisible(sustainSlider);
    sustainLabel.setText("S", juce::dontSendNotification);
    sustainLabel.attachToComponent(&sustainSlider, false);
    sustainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(sustainLabel);
    
    releaseSlider.setSliderStyle(juce::Slider::LinearVertical);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    releaseSlider.setColour(juce::Slider::thumbColourId, juce::Colours::purple);
    addAndMakeVisible(releaseSlider);
    releaseLabel.setText("R", juce::dontSendNotification);
    releaseLabel.attachToComponent(&releaseSlider, false);
    releaseLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(releaseLabel);
    
    // Parameter attachments
    catAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        audioProcessor.apvts, "catMode", catButton);
    dogAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        audioProcessor.apvts, "dogMode", dogButton);
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "volume", volumeSlider);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "release", releaseSlider);
    
    startTimerHz(30);
    setSize(500, 300);
}

NekoSynthAudioProcessorEditor::~NekoSynthAudioProcessorEditor()
{
}

void NekoSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(255, 230, 240));
    
    g.setColour(juce::Colours::black);
    
    static float frameCounter = 0.0f;
    frameCounter += 0.1f;
    float earWiggle = std::sin(frameCounter) * 3.0f;
    float tailWag = std::sin(frameCounter * 2.0f) * 5.0f;
    
    if (catButton.getToggleState())
    {
        g.fillEllipse(120 + earWiggle, 40, 30, 30);
        g.fillEllipse(250 - earWiggle, 40, 30, 30);
        
        g.setColour(juce::Colours::orange);
        g.fillEllipse(150, 70, 100, 80);
        
        g.setColour(juce::Colours::white);
        g.fillEllipse(170, 100, 20, 25);
        g.fillEllipse(210, 100, 20, 25);
        
        g.setColour(juce::Colours::black);
        g.fillEllipse(175, 110, 10, 10);
        g.fillEllipse(215, 110, 10, 10);
        
        g.drawLine(140, 120, 110, 115);
        g.drawLine(140, 125, 110, 125);
        g.drawLine(140, 130, 110, 135);
        g.drawLine(260, 120, 290, 115);
        g.drawLine(260, 125, 290, 125);
        g.drawLine(260, 130, 290, 135);
    }
    else
    {
        g.setColour(juce::Colours::brown);
        g.fillEllipse(130, 40, 40, 60);
        g.fillEllipse(230, 40, 40, 60);
        g.fillEllipse(150, 70, 100, 90);
        
        g.setColour(juce::Colours::saddlebrown);
        g.fillEllipse(180, 120, 40, 30);
        
        g.setColour(juce::Colours::white);
        g.fillEllipse(170, 100, 15, 20);
        g.fillEllipse(210, 100, 15, 20);
        
        g.setColour(juce::Colours::black);
        g.fillEllipse(175, 110, 8, 8);
        g.fillEllipse(215, 110, 8, 8);
        
        g.setColour(juce::Colours::brown);
        g.drawLine(250 + tailWag, 150, 280 + tailWag, 130);
    }
}

void NekoSynthAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(10);
    
    catButton.setBounds(10, 10, 100, 40);
    dogButton.setBounds(120, 10, 100, 40);
    
    auto sliderArea = area.removeFromBottom(100);
    int sliderWidth = sliderArea.getWidth() / 7;
    
    volumeSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5));
    attackSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5));
    decaySlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5));
    sustainSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5));
    releaseSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5));
}

void NekoSynthAudioProcessorEditor::timerCallback()
{
    repaint();
}
