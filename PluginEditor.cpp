#include "PluginProcessor.h"
#include "PluginEditor.h"

NekoSynthAudioProcessorEditor::NekoSynthAudioProcessorEditor(NekoSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Modern Cat button
    catButton.setButtonText("CAT");
    catButton.setClickingTogglesState(true);
    catButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(30, 30, 35));
    catButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(0, 160, 255));
    catButton.setColour(juce::TextButton::textColourOffId, juce::Colours::lightgrey);
    catButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    addAndMakeVisible(catButton);
    
    // Modern Dog button
    dogButton.setButtonText("DOG");
    dogButton.setClickingTogglesState(true);
    dogButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(30, 30, 35));
    dogButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(255, 140, 40));
    dogButton.setColour(juce::TextButton::textColourOffId, juce::Colours::lightgrey);
    dogButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    addAndMakeVisible(dogButton);
    
    // Volume slider
    volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colour::fromRGB(60, 60, 70));
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(0, 160, 255));
    addAndMakeVisible(volumeSlider);
    volumeLabel.setText("VOLUME", juce::dontSendNotification);
    volumeLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    volumeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(volumeLabel);
    
    // ADSR Sliders
    for (auto* slider : { &attackSlider, &decaySlider, &sustainSlider, &releaseSlider })
    {
        slider->setSliderStyle(juce::Slider::LinearVertical);
        slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        slider->setColour(juce::Slider::trackColourId, juce::Colour::fromRGB(60, 60, 70));
        slider->setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(200, 200, 220));
        addAndMakeVisible(slider);
    }
    
    attackLabel.setText("ATTACK", juce::dontSendNotification);
    decayLabel.setText("DECAY", juce::dontSendNotification);
    sustainLabel.setText("SUSTAIN", juce::dontSendNotification);
    releaseLabel.setText("RELEASE", juce::dontSendNotification);
    
    for (auto* label : { &attackLabel, &decayLabel, &sustainLabel, &releaseLabel })
    {
        label->setColour(juce::Label::textColourId, juce::Colours::grey);
        label->setJustificationType(juce::Justification::centred);
        addAndMakeVisible(label);
    }
    
    // Parameter attachments
    catAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "catMode", catButton);
    dogAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "dogMode", dogButton);
    volumeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "volume", volumeSlider);
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);
    
    setSize(500, 350);
}

NekoSynthAudioProcessorEditor::~NekoSynthAudioProcessorEditor()
{
}

void NekoSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Dark gradient background
    g.setGradientFill(juce::ColourGradient::vertical(
        juce::Colour::fromRGB(20, 20, 25), 0,
        juce::Colour::fromRGB(10, 10, 15), getHeight()));
    g.fillAll();
    
    // Title
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(28.0f, juce::Font::bold));
    g.drawText("NekoSynth", 0, 20, getWidth(), 40, juce::Justification::centred);
    
    // Subtitle / mode indicator
    if (catButton.getToggleState())
    {
        g.setColour(juce::Colour::fromRGB(0, 160, 255));
        g.setFont(juce::Font(16.0f, juce::Font::italic));
        g.drawText("cat mode • meow", 0, 55, getWidth(), 25, juce::Justification::centred);
    }
    else if (dogButton.getToggleState())
    {
        g.setColour(juce::Colour::fromRGB(255, 140, 40));
        g.setFont(juce::Font(16.0f, juce::Font::italic));
        g.drawText("dog mode • bark", 0, 55, getWidth(), 25, juce::Justification::centred);
    }
    
    // Draw separator line
    g.setColour(juce::Colour::fromRGB(40, 40, 45));
    g.drawLine(20, 85, getWidth() - 20, 85, 1);
    
    // Footer with alias
    g.setColour(juce::Colours::grey);
    g.setFont(juce::Font(11.0f));
    g.drawText("justdev-chris", getWidth() - 100, getHeight() - 25, 90, 20, juce::Justification::right);
}

void NekoSynthAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(30, 0);
    
    // Title area (leave space)
    area.removeFromTop(80);
    
    // Button row
    auto buttonArea = area.removeFromTop(40);
    buttonArea = buttonArea.reduced(100, 0);
    catButton.setBounds(buttonArea.removeFromLeft(80).reduced(5));
    dogButton.setBounds(buttonArea.removeFromRight(80).reduced(5));
    
    area.removeFromTop(20);
    
    // Sliders
    auto sliderArea = area.reduced(30, 0);
    int sliderWidth = sliderArea.getWidth() / 5;
    
    // Volume
    auto volArea = sliderArea.removeFromLeft(sliderWidth);
    volumeLabel.setBounds(volArea.removeFromBottom(20));
    volumeSlider.setBounds(volArea.reduced(10, 0));
    
    // Attack
    auto attArea = sliderArea.removeFromLeft(sliderWidth);
    attackLabel.setBounds(attArea.removeFromBottom(20));
    attackSlider.setBounds(attArea.reduced(10, 0));
    
    // Decay
    auto decArea = sliderArea.removeFromLeft(sliderWidth);
    decayLabel.setBounds(decArea.removeFromBottom(20));
    decaySlider.setBounds(decArea.reduced(10, 0));
    
    // Sustain
    auto susArea = sliderArea.removeFromLeft(sliderWidth);
    sustainLabel.setBounds(susArea.removeFromBottom(20));
    sustainSlider.setBounds(susArea.reduced(10, 0));
    
    // Release
    auto relArea = sliderArea.removeFromLeft(sliderWidth);
    releaseLabel.setBounds(relArea.removeFromBottom(20));
    releaseSlider.setBounds(relArea.reduced(10, 0));
}
