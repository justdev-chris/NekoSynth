#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NekoSynthAudioProcessorEditor::NekoSynthAudioProcessorEditor(NekoSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Set up Cat button
    catButton.setButtonText("😺 MEOW");
    catButton.setClickingTogglesState(true);
    catButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::orange);
    addAndMakeVisible(catButton);
    
    // Set up Dog button
    dogButton.setButtonText("🐕 BARK");
    dogButton.setClickingTogglesState(true);
    dogButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::brown);
    addAndMakeVisible(dogButton);
    
    // Set up volume slider
    volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider.setRange(0, 1, 0.01);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::pink);
    addAndMakeVisible(volumeSlider);
    volumeLabel.setText("VOL", juce::dontSendNotification);
    volumeLabel.attachToComponent(&volumeSlider, false);
    volumeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(volumeLabel);
    
    // ADSR Sliders
    attackSlider.setSliderStyle(juce::Slider::LinearVertical);
    attackSlider.setRange(0, 5, 0.01);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    attackSlider.setColour(juce::Slider::thumbColourId, juce::Colours::lightblue);
    addAndMakeVisible(attackSlider);
    attackLabel.setText("A", juce::dontSendNotification);
    attackLabel.attachToComponent(&attackSlider, false);
    attackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(attackLabel);
    
    decaySlider.setSliderStyle(juce::Slider::LinearVertical);
    decaySlider.setRange(0, 5, 0.01);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    decaySlider.setColour(juce::Slider::thumbColourId, juce::Colours::lightgreen);
    addAndMakeVisible(decaySlider);
    decayLabel.setText("D", juce::dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, false);
    decayLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(decayLabel);
    
    sustainSlider.setSliderStyle(juce::Slider::LinearVertical);
    sustainSlider.setRange(0, 1, 0.01);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    sustainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    addAndMakeVisible(sustainSlider);
    sustainLabel.setText("S", juce::dontSendNotification);
    sustainLabel.attachToComponent(&sustainSlider, false);
    sustainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(sustainLabel);
    
    releaseSlider.setSliderStyle(juce::Slider::LinearVertical);
    releaseSlider.setRange(0, 5, 0.01);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    releaseSlider.setColour(juce::Slider::thumbColourId, juce::Colours::purple);
    addAndMakeVisible(releaseSlider);
    releaseLabel.setText("R", juce::dontSendNotification);
    releaseLabel.attachToComponent(&releaseSlider, false);
    releaseLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(releaseLabel);
    
    // Parameter attachments
    catAttachment = std::make_unique<Attachment>(audioProcessor.apvts, "catMode", catButton);
    dogAttachment = std::make_unique<Attachment>(audioProcessor.apvts, "dogMode", dogButton);
    volumeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "volume", volumeSlider);
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);
    
    // Start timer for animations
    startTimerHz(30);
    
    // Set window size
    setSize(500, 300);
}

NekoSynthAudioProcessorEditor::~NekoSynthAudioProcessorEditor()
{
}

void NekoSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Background
    g.fillAll(juce::Colour::fromRGB(255, 230, 240)); // Soft pink
    
    // Draw cat/dog face based on active mode
    g.setColour(juce::Colours::black);
    
    if (catButton.getToggleState())
    {
        // Draw cat face with ear wiggle
        float earOffset = earWiggle * 3.0f;
        
        // Cat ears
        g.fillEllipse(120 + earOffset, 40, 30, 30); // Left ear
        g.fillEllipse(250 - earOffset, 40, 30, 30); // Right ear
        
        // Cat face
        g.setColour(juce::Colours::orange);
        g.fillEllipse(150, 70, 100, 80);
        
        // Eyes
        g.setColour(juce::Colours::white);
        g.fillEllipse(170, 100, 20, 25);
        g.fillEllipse(210, 100, 20, 25);
        
        g.setColour(juce::Colours::black);
        g.fillEllipse(175, 110, 10, 10);
        g.fillEllipse(215, 110, 10, 10);
        
        // Whiskers
        g.drawLine(140, 120, 110, 115);
        g.drawLine(140, 125, 110, 125);
        g.drawLine(140, 130, 110, 135);
        
        g.drawLine(260, 120, 290, 115);
        g.drawLine(260, 125, 290, 125);
        g.drawLine(260, 130, 290, 135);
    }
    else
    {
        // Draw dog face with tail wag
        float wagOffset = tailWag * 5.0f;
        
        // Dog ears (floppy)
        g.setColour(juce::Colours::brown);
        g.fillEllipse(130, 40, 40, 60);
        g.fillEllipse(230, 40, 40, 60);
        
        // Dog face
        g.fillEllipse(150, 70, 100, 90);
        
        // Snout
        g.setColour(juce::Colours::saddlebrown);
        g.fillEllipse(180, 120, 40, 30);
        
        // Eyes
        g.setColour(juce::Colours::white);
        g.fillEllipse(170, 100, 15, 20);
        g.fillEllipse(210, 100, 15, 20);
        
        g.setColour(juce::Colours::black);
        g.fillEllipse(175, 110, 8, 8);
        g.fillEllipse(215, 110, 8, 8);
        
        // Tail (wagging)
        g.setColour(juce::Colours::brown);
        g.drawLine(250 + wagOffset, 150, 280 + wagOffset, 130);
    }
}

void NekoSynthAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(10);
    
    // Position buttons
    catButton.setBounds(10, 10, 100, 40);
    dogButton.setBounds(120, 10, 100, 40);
    
    // Position sliders at bottom
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
    // Update animations
    earWiggle = std::sin(getFrameCounter() * 0.2f) * 0.5f;
    tailWag = std::sin(getFrameCounter() * 0.5f) * 0.5f + 0.5f;
    
    repaint();
}