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
    addAndMakeVisible(catButton);
    
    // ===== DOG BUTTON =====
    dogButton.setButtonText("DOG");
    dogButton.setClickingTogglesState(true);
    dogButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(25, 25, 30));
    dogButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(255, 140, 40));
    dogButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    dogButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
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
    
    // ===== SLIDER SETUP HELPER =====
    auto setupSlider = [](juce::Slider& slider, juce::Colour thumbColour)
    {
        slider.setSliderStyle(juce::Slider::LinearVertical);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        slider.setColour(juce::Slider::trackColourId, juce::Colour::fromRGB(60, 60, 70));
        slider.setColour(juce::Slider::thumbColourId, thumbColour);
        slider.setColour(juce::Slider::backgroundColourId, juce::Colour::fromRGB(30, 30, 35));
    };
    
    // ===== ADSR + VOLUME SLIDERS =====
    setupSlider(volumeSlider, juce::Colours::white);
    setupSlider(attackSlider, juce::Colour::fromRGB(100, 150, 255));
    setupSlider(decaySlider, juce::Colour::fromRGB(100, 200, 150));
    setupSlider(sustainSlider, juce::Colour::fromRGB(255, 220, 100));
    setupSlider(releaseSlider, juce::Colour::fromRGB(255, 120, 120));
    
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    
    // ===== NEW PITCH RANGE SLIDER =====
    setupSlider(pitchRangeSlider, juce::Colour::fromRGB(180, 130, 255));
    addAndMakeVisible(pitchRangeSlider);
    pitchRangeLabel.setText("PITCH", juce::dontSendNotification);
    pitchRangeLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    pitchRangeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(pitchRangeLabel);
    
    // ===== NEW FILTER SLIDERS =====
    setupSlider(filterCutoffSlider, juce::Colour::fromRGB(255, 150, 200));
    setupSlider(filterResSlider, juce::Colour::fromRGB(200, 150, 255));
    addAndMakeVisible(filterCutoffSlider);
    addAndMakeVisible(filterResSlider);
    
    filterCutoffLabel.setText("CUT", juce::dontSendNotification);
    filterResLabel.setText("RES", juce::dontSendNotification);
    filterCutoffLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    filterResLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    filterCutoffLabel.setJustificationType(juce::Justification::centred);
    filterResLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(filterCutoffLabel);
    addAndMakeVisible(filterResLabel);
    
    // ===== NEW UNISON CONTROLS =====
    setupSlider(detuneSlider, juce::Colour::fromRGB(150, 200, 255));
    addAndMakeVisible(detuneSlider);
    detuneLabel.setText("DETUNE", juce::dontSendNotification);
    detuneLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    detuneLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(detuneLabel);
    
    voiceCountCombo.addItem("1", 1);
    voiceCountCombo.addItem("2", 2);
    voiceCountCombo.addItem("3", 3);
    voiceCountCombo.addItem("4", 4);
    voiceCountCombo.addItem("5", 5);
    voiceCountCombo.addItem("6", 6);
    voiceCountCombo.addItem("7", 7);
    voiceCountCombo.addItem("8", 8);
    voiceCountCombo.setSelectedId(1);
    voiceCountCombo.setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGB(20, 20, 25));
    voiceCountCombo.setColour(juce::ComboBox::textColourId, juce::Colours::white);
    voiceCountCombo.setColour(juce::ComboBox::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    addAndMakeVisible(voiceCountCombo);
    
    voiceCountLabel.setText("VOICES", juce::dontSendNotification);
    voiceCountLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    voiceCountLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(voiceCountLabel);
    
    // ===== LABELS FOR EXISTING SLIDERS =====
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
    
    // ===== LEVEL METER LABEL =====
    meterLabel.setText("LEVEL", juce::dontSendNotification);
    meterLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    meterLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(meterLabel);
    
    // ===== ATTACHMENTS =====
    catAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "catMode", catButton);
    dogAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "dogMode", dogButton);
    waveformAttachment = std::make_unique<ComboAttachment>(audioProcessor.apvts, "waveform", waveformSelector);
    
    volumeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "volume", volumeSlider);
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);
    
    // New attachments
    pitchRangeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "pitchBendRange", pitchRangeSlider);
    filterCutoffAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "filterCutoff", filterCutoffSlider);
    filterResAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "filterRes", filterResSlider);
    detuneAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "detune", detuneSlider);
    voiceCountAttachment = std::make_unique<ComboAttachment>(audioProcessor.apvts, "voiceCount", voiceCountCombo);
    
    // Start timer for meter updates
    startTimerHz(30);
    
    setSize(900, 450);
}

NekoSynthAudioProcessorEditor::~NekoSynthAudioProcessorEditor()
{
}

void NekoSynthAudioProcessorEditor::timerCallback()
{
    repaint(); // Trigger repaint for meter
}

void NekoSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Background gradient
    g.setGradientFill(juce::ColourGradient::vertical(
        juce::Colour::fromRGB(18, 18, 22), 0,
        juce::Colour::fromRGB(10, 10, 14), getHeight()));
    g.fillAll();
    
    // Title
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
    juce::String modeText = catButton.getToggleState() ? "cat mode - meow" : 
                            (dogButton.getToggleState() ? "dog mode - bark" : "select mode");
    g.setColour(juce::Colours::white.withAlpha(0.5f));
    g.setFont(juce::Font(14.0f));
    g.drawText(modeText, 30, 135, 200, 20, juce::Justification::left);
    
    // Level meter (7)
    float level = audioProcessor.getCurrentLevel();
    int meterWidth = 150;
    int meterX = getWidth() - meterWidth - 30;
    int meterY = 140;
    int meterHeight = 20;
    
    // Meter background
    g.setColour(juce::Colour::fromRGB(30, 30, 35));
    g.fillRect(meterX, meterY, meterWidth, meterHeight);
    
    // Meter fill
    g.setColour(catButton.getToggleState() ? juce::Colour::fromRGB(0, 180, 255) : 
                (dogButton.getToggleState() ? juce::Colour::fromRGB(255, 140, 40) : juce::Colours::white));
    g.fillRect(meterX, meterY, meterWidth * level, meterHeight);
    
    // Meter outline
    g.setColour(juce::Colour::fromRGB(60, 60, 70));
    g.drawRect(meterX, meterY, meterWidth, meterHeight, 1);
    
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
    
    area.removeFromTop(10);
    
    // Waveform selector
    auto waveArea = area.removeFromTop(40);
    waveformSelector.setBounds(waveArea.removeFromLeft(100).reduced(5));
    waveformLabel.setBounds(waveArea);
    
    area.removeFromTop(20);
    
    // Split into left and right sections
    auto leftSection = area.removeFromLeft(area.getWidth() / 2 - 15);
    auto rightSection = area;
    
    // LEFT SECTION - Basic controls
    auto adsrRow = leftSection.removeFromTop(180);
    int sliderWidth = adsrRow.getWidth() / 5;
    
    // Volume
    auto volArea = adsrRow.removeFromLeft(sliderWidth);
    volumeSlider.setBounds(volArea.reduced(5, 20));
    volumeLabel.setBounds(volArea.removeFromBottom(20));
    
    // Attack
    auto attArea = adsrRow.removeFromLeft(sliderWidth);
    attackSlider.setBounds(attArea.reduced(5, 20));
    attackLabel.setBounds(attArea.removeFromBottom(20));
    
    // Decay
    auto decArea = adsrRow.removeFromLeft(sliderWidth);
    decaySlider.setBounds(decArea.reduced(5, 20));
    decayLabel.setBounds(decArea.removeFromBottom(20));
    
    // Sustain
    auto susArea = adsrRow.removeFromLeft(sliderWidth);
    sustainSlider.setBounds(susArea.reduced(5, 20));
    sustainLabel.setBounds(susArea.removeFromBottom(20));
    
    // Release
    auto relArea = adsrRow.removeFromLeft(sliderWidth);
    releaseSlider.setBounds(relArea.reduced(5, 20));
    releaseLabel.setBounds(relArea.removeFromBottom(20));
    
    // RIGHT SECTION - New controls
    auto pitchArea = rightSection.removeFromTop(60);
    pitchRangeSlider.setBounds(pitchArea.removeFromLeft(60).reduced(5, 10));
    pitchRangeLabel.setBounds(pitchArea);
    
    auto filterArea = rightSection.removeFromTop(60);
    filterCutoffSlider.setBounds(filterArea.removeFromLeft(60).reduced(5, 10));
    filterCutoffLabel.setBounds(filterArea.removeFromLeft(60));
    filterResSlider.setBounds(filterArea.removeFromLeft(60).reduced(5, 10));
    filterResLabel.setBounds(filterArea);
    
    auto unisonArea = rightSection.removeFromTop(80);
    detuneSlider.setBounds(unisonArea.removeFromLeft(60).reduced(5, 15));
    detuneLabel.setBounds(unisonArea.removeFromLeft(60));
    voiceCountCombo.setBounds(unisonArea.removeFromLeft(80).reduced(5, 20));
    voiceCountLabel.setBounds(unisonArea);
    
    // Level meter at bottom right
    meterLabel.setBounds(rightSection.getWidth() - 150, rightSection.getHeight() - 30, 150, 20);
}
