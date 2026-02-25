#include "PluginProcessor.h"
#include "PluginEditor.h"

NekoSynthAudioProcessorEditor::NekoSynthAudioProcessorEditor(NekoSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // ===== CAT BUTTON =====
    catButton.setButtonText("CAT");
    catButton.setClickingTogglesState(true);
    catButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(25, 25, 30));
    catButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(0, 180, 255));
    catButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    catButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    catButton.setColour(juce::TextButton::buttonNormalBackground, juce::Colour::fromRGB(25, 25, 30));
    addAndMakeVisible(catButton);
    
    // ===== DOG BUTTON =====
    dogButton.setButtonText("DOG");
    dogButton.setClickingTogglesState(true);
    dogButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(25, 25, 30));
    dogButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(255, 140, 40));
    dogButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    dogButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    dogButton.setColour(juce::TextButton::buttonNormalBackground, juce::Colour::fromRGB(25, 25, 30));
    addAndMakeVisible(dogButton);
    
    // ===== WAVEFORM SELECTOR =====
    waveformSelector.addItem("SINE", 1);
    waveformSelector.addItem("SAW", 2);
    waveformSelector.addItem("SQUARE", 3);
    waveformSelector.setSelectedId(1);
    waveformSelector.setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGB(20, 20, 25));
    waveformSelector.setColour(juce::ComboBox::textColourId, juce::Colours::white);
    waveformSelector.setColour(juce::ComboBox::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    waveformSelector.setColour(juce::ComboBox::buttonColourId, juce::Colour::fromRGB(80, 80, 90));
    addAndMakeVisible(waveformSelector);
    
    waveformLabel.setText("WAVE", juce::dontSendNotification);
    waveformLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    waveformLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(waveformLabel);
    
    // ===== SLIDERS =====
    auto setupSlider = [](juce::Slider& slider)
    {
        slider.setSliderStyle(juce::Slider::LinearVertical);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        slider.setColour(juce::Slider::trackColourId, juce::Colour::fromRGB(60, 60, 70));
        slider.setColour(juce::Slider::thumbColourId, juce::Colours::white);
        slider.setColour(juce::Slider::backgroundColourId, juce::Colour::fromRGB(30, 30, 35));
    };
    
    setupSlider(volumeSlider);
    setupSlider(attackSlider);
    setupSlider(decaySlider);
    setupSlider(sustainSlider);
    setupSlider(releaseSlider);
    
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    
    // ===== LABELS =====
    volumeLabel.setText("VOL", juce::dontSendNotification);
    attackLabel.setText("ATK", juce::dontSendNotification);
    decayLabel.setText("DEC", juce::dontSendNotification);
    sustainLabel.setText("SUS", juce::dontSendNotification);
    releaseLabel.setText("REL", juce::dontSendNotification);
    
    for (auto* label : { &volumeLabel, &attackLabel, &decayLabel, &sustainLabel, &releaseLabel })
    {
        label->setColour(juce::Label::textColourId, juce::Colours::grey);
        label->setJustificationType(juce::Justification::centred);
        label->setFont(juce::Font(12.0f, juce::Font::bold));
        addAndMakeVisible(label);
    }
    
    // ===== ATTACHMENTS =====
    catAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "catMode", catButton);
    dogAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "dogMode", dogButton);
    volumeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "volume", volumeSlider);
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);
    waveformAttachment = std::make_unique<ComboAttachment>(audioProcessor.apvts, "waveform", waveformSelector);
    
    setSize(600, 400);
}

NekoSynthAudioProcessorEditor::~NekoSynthAudioProcessorEditor()
{
}

void NekoSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Background gradient
    g.setGradientFill(juce::ColourGradient::vertical(
        juce::Colour::fromRGB(18, 18, 22), 0,
        juce::Colour::fromRGB(10, 10, 14), getHeight()));
    g.fillAll();
    
    // Title with nice font
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(42.0f, juce::Font::bold));
    g.drawText("NEKO", 30, 25, 200, 50, juce::Justification::left);
    
    g.setColour(catButton.getToggleState() ? juce::Colour::fromRGB(0, 180, 255) : 
                (dogButton.getToggleState() ? juce::Colour::fromRGB(255, 140, 40) : juce::Colours::grey));
    g.setFont(juce::Font(42.0f, juce::Font::bold));
    g.drawText("SYNTH", 30, 65, 200, 50, juce::Justification::left);
    
    // Decorative line
    g.setColour(juce::Colour::fromRGB(40, 40, 48));
    g.drawRect(20, 120, getWidth() - 40, 1);
    
    // Mode indicator
    juce::String modeText = catButton.getToggleState() ? "cat mode • meow" : 
                            (dogButton.getToggleState() ? "dog mode • bark" : "select mode");
    g.setColour(juce::Colours::white.withAlpha(0.5f));
    g.setFont(juce::Font(14.0f));
    g.drawText(modeText, 30, 135, 200, 20, juce::Justification::left);
    
    // Alias
    g.setColour(juce::Colours::white.withAlpha(0.2f));
    g.setFont(juce::Font(11.0f));
    g.drawText("justdev-chris", getWidth() - 120, getHeight() - 25, 100, 20, juce::Justification::right);
}

void NekoSynthAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(30);
    
    // Title area (skip)
    area.removeFromTop(120);
    
    // Mode buttons
    auto buttonRow = area.removeFromTop(40);
    catButton.setBounds(buttonRow.removeFromLeft(80).reduced(5));
    dogButton.setBounds(buttonRow.removeFromLeft(80).reduced(5));
    
    area.removeFromTop(20);
    
    // Waveform selector
    auto waveArea = area.removeFromTop(40);
    waveformSelector.setBounds(waveArea.removeFromLeft(100).reduced(5));
    waveformLabel.setBounds(waveArea);
    
    area.removeFromTop(30);
    
    // Sliders
    auto sliderArea = area;
    int sliderWidth = sliderArea.getWidth() / 5;
    
    // Volume
    auto volArea = sliderArea.removeFromLeft(sliderWidth);
    volumeSlider.setBounds(volArea.reduced(10, 20));
    volumeLabel.setBounds(volArea.removeFromBottom(20));
    
    // Attack
    auto attArea = sliderArea.removeFromLeft(sliderWidth);
    attackSlider.setBounds(attArea.reduced(10, 20));
    attackLabel.setBounds(attArea.removeFromBottom(20));
    
    // Decay
    auto decArea = sliderArea.removeFromLeft(sliderWidth);
    decaySlider.setBounds(decArea.reduced(10, 20));
    decayLabel.setBounds(decArea.removeFromBottom(20));
    
    // Sustain
    auto susArea = sliderArea.removeFromLeft(sliderWidth);
    sustainSlider.setBounds(susArea.reduced(10, 20));
    sustainLabel.setBounds(susArea.removeFromBottom(20));
    
    // Release
    auto relArea = sliderArea.removeFromLeft(sliderWidth);
    releaseSlider.setBounds(relArea.reduced(10, 20));
    releaseLabel.setBounds(relArea.removeFromBottom(20));
}