#include "PluginProcessor.h"
#include "PluginEditor.h"

NekoSynthAudioProcessorEditor::NekoSynthAudioProcessorEditor(NekoSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // ===== MODE GROUP =====
    modeGroup.setText("MODE");
    modeGroup.setTextLabelPosition(juce::Justification::centred);
    modeGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    modeGroup.setColour(juce::GroupComponent::textColourId, juce::Colours::grey);
    addAndMakeVisible(modeGroup);
    
    catButton.setButtonText("CAT");
    catButton.setClickingTogglesState(true);
    catButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(25, 25, 30));
    catButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(0, 180, 255));
    catButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    catButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    addAndMakeVisible(catButton);
    
    dogButton.setButtonText("DOG");
    dogButton.setClickingTogglesState(true);
    dogButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(25, 25, 30));
    dogButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(255, 140, 40));
    dogButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    dogButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    addAndMakeVisible(dogButton);
    
    // ===== OSCILLATOR GROUP =====
    oscGroup.setText("OSCILLATOR");
    oscGroup.setTextLabelPosition(juce::Justification::centred);
    oscGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    oscGroup.setColour(juce::GroupComponent::textColourId, juce::Colours::grey);
    addAndMakeVisible(oscGroup);
    
    waveformSelector.addItem("SINE", 1);
    waveformSelector.addItem("SAW", 2);
    waveformSelector.addItem("SQUARE", 3);
    waveformSelector.setSelectedId(1);
    waveformSelector.setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGB(20, 20, 25));
    waveformSelector.setColour(juce::ComboBox::textColourId, juce::Colours::white);
    waveformSelector.setColour(juce::ComboBox::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    addAndMakeVisible(waveformSelector);
    
    // ===== UNISON GROUP =====
    unisonGroup.setText("UNISON");
    unisonGroup.setTextLabelPosition(juce::Justification::centred);
    unisonGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    unisonGroup.setColour(juce::GroupComponent::textColourId, juce::Colours::grey);
    addAndMakeVisible(unisonGroup);
    
    voiceCountCombo.addItem("1", 1);
    voiceCountCombo.addItem("2", 2);
    voiceCountCombo.addItem("3", 3);
    voiceCountCombo.addItem("4", 4);
    voiceCountCombo.addItem("5", 5);
    voiceCountCombo.addItem("6", 6);
    voiceCountCombo.addItem("7", 7);
    voiceCountCombo.addItem("8", 8);
    voiceCountCombo.setSelectedId(4);
    voiceCountCombo.setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGB(20, 20, 25));
    voiceCountCombo.setColour(juce::ComboBox::textColourId, juce::Colours::white);
    voiceCountCombo.setColour(juce::ComboBox::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    addAndMakeVisible(voiceCountCombo);
    
    // ===== SLIDER SETUP =====
    auto setupSlider = [](juce::Slider& slider, juce::Colour thumbColour, const juce::String& suffix = "")
    {
        slider.setSliderStyle(juce::Slider::LinearVertical);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);
        slider.setNumDecimalPlacesToDisplay(2);
        slider.setColour(juce::Slider::trackColourId, juce::Colour::fromRGB(60, 60, 70));
        slider.setColour(juce::Slider::thumbColourId, thumbColour);
        slider.setColour(juce::Slider::backgroundColourId, juce::Colour::fromRGB(30, 30, 35));
        slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
        slider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour::fromRGB(20, 20, 25));
        slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour::fromRGB(60, 60, 70));
        if (suffix.isNotEmpty())
            slider.setTextValueSuffix(suffix);
    };
    
    // ===== AMPLITUDE GROUP =====
    ampGroup.setText("AMPLITUDE");
    ampGroup.setTextLabelPosition(juce::Justification::centred);
    ampGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    ampGroup.setColour(juce::GroupComponent::textColourId, juce::Colours::grey);
    addAndMakeVisible(ampGroup);
    
    setupSlider(volumeSlider, juce::Colours::white, "");
    setupSlider(attackSlider, juce::Colour::fromRGB(100, 150, 255), "s");
    setupSlider(decaySlider, juce::Colour::fromRGB(100, 200, 150), "s");
    setupSlider(sustainSlider, juce::Colour::fromRGB(255, 220, 100), "");
    setupSlider(releaseSlider, juce::Colour::fromRGB(255, 120, 120), "s");
    
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    
    // ===== FILTER GROUP =====
    filterGroup.setText("FILTER");
    filterGroup.setTextLabelPosition(juce::Justification::centred);
    filterGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    filterGroup.setColour(juce::GroupComponent::textColourId, juce::Colours::grey);
    addAndMakeVisible(filterGroup);
    
    setupSlider(filterCutoffSlider, juce::Colour::fromRGB(255, 150, 200), "Hz");
    setupSlider(filterResSlider, juce::Colour::fromRGB(200, 150, 255), "");
    addAndMakeVisible(filterCutoffSlider);
    addAndMakeVisible(filterResSlider);
    
    // ===== PITCH GROUP =====
    pitchGroup.setText("PITCH");
    pitchGroup.setTextLabelPosition(juce::Justification::centred);
    pitchGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colour::fromRGB(60, 60, 70));
    pitchGroup.setColour(juce::GroupComponent::textColourId, juce::Colours::grey);
    addAndMakeVisible(pitchGroup);
    
    setupSlider(pitchRangeSlider, juce::Colour::fromRGB(180, 130, 255), "st");
    setupSlider(detuneSlider, juce::Colour::fromRGB(150, 200, 255), "ct");
    addAndMakeVisible(pitchRangeSlider);
    addAndMakeVisible(detuneSlider);
    
    // ===== ATTACHMENTS =====
    catAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "catMode", catButton);
    dogAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "dogMode", dogButton);
    waveformAttachment = std::make_unique<ComboAttachment>(audioProcessor.apvts, "waveform", waveformSelector);
    
    volumeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "volume", volumeSlider);
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);
    
    pitchRangeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "pitchBendRange", pitchRangeSlider);
    filterCutoffAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "filterCutoff", filterCutoffSlider);
    filterResAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "filterRes", filterResSlider);
    detuneAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "detune", detuneSlider);
    voiceCountAttachment = std::make_unique<ComboAttachment>(audioProcessor.apvts, "voiceCount", voiceCountCombo);
    
    startTimerHz(30);
    setSize(1000, 550);
}

NekoSynthAudioProcessorEditor::~NekoSynthAudioProcessorEditor() {}

void NekoSynthAudioProcessorEditor::timerCallback()
{
    repaint();
}

void NekoSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Background
    g.setGradientFill(juce::ColourGradient::vertical(
        juce::Colour::fromRGB(18, 18, 22), 0,
        juce::Colour::fromRGB(10, 10, 14), getHeight()));
    g.fillAll();
    
    // Title
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(48.0f, juce::Font::bold));
    g.drawText("NEKO", 30, 20, 200, 50, juce::Justification::left);
    
    g.setColour(catButton.getToggleState() ? juce::Colour::fromRGB(0, 180, 255) : 
                (dogButton.getToggleState() ? juce::Colour::fromRGB(255, 140, 40) : juce::Colours::grey));
    g.setFont(juce::Font(48.0f, juce::Font::bold));
    g.drawText("SYNTH", 30, 60, 200, 50, juce::Justification::left);
    
    // Level meter
    float level = audioProcessor.getCurrentLevel();
    int meterWidth = 200;
    int meterX = getWidth() - meterWidth - 30;
    int meterY = 30;
    int meterHeight = 25;
    
    g.setColour(juce::Colour::fromRGB(30, 30, 35));
    g.fillRect(meterX, meterY, meterWidth, meterHeight);
    
    g.setColour(catButton.getToggleState() ? juce::Colour::fromRGB(0, 180, 255) : 
                (dogButton.getToggleState() ? juce::Colour::fromRGB(255, 140, 40) : juce::Colours::white));
    g.fillRect(meterX, meterY, (int)(meterWidth * level), meterHeight);
    
    g.setColour(juce::Colour::fromRGB(60, 60, 70));
    g.drawRect(meterX, meterY, meterWidth, meterHeight, 1);
    
    g.setColour(juce::Colours::white.withAlpha(0.5f));
    g.setFont(juce::Font(12.0f));
    g.drawText("LEVEL", meterX + 5, meterY + 5, 50, 15, juce::Justification::left);
    
    // Version
    g.setColour(juce::Colours::white.withAlpha(0.2f));
    g.setFont(juce::Font(11.0f));
    g.drawText("justdev-chris", getWidth() - 120, getHeight() - 25, 100, 20, juce::Justification::right);
}

void NekoSynthAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    area.removeFromTop(100); // Space for title
    
    auto topRow = area.removeFromTop(80);
    
    // Mode group (top left)
    modeGroup.setBounds(topRow.removeFromLeft(200).reduced(5));
    auto modeArea = modeGroup.getBounds().reduced(10);
    catButton.setBounds(modeArea.removeFromLeft(80).reduced(5));
    dogButton.setBounds(modeArea.reduced(5));
    
    // Oscillator group (top middle)
    oscGroup.setBounds(topRow.removeFromLeft(150).reduced(5));
    auto oscArea = oscGroup.getBounds().reduced(10);
    waveformSelector.setBounds(oscArea.reduced(5));
    
    // Unison group (top right)
    unisonGroup.setBounds(topRow.reduced(5));
    auto unisonArea = unisonGroup.getBounds().reduced(10);
    voiceCountCombo.setBounds(unisonArea.reduced(5));
    
    area.removeFromTop(10);
    
    // Main content row
    auto contentRow = area;
    int groupWidth = (contentRow.getWidth() - 40) / 3;
    
    // Amplitude group (left)
    ampGroup.setBounds(contentRow.removeFromLeft(groupWidth).reduced(5));
    auto ampArea = ampGroup.getBounds().reduced(15, 10);
    
    int sliderWidth = ampArea.getWidth() / 5;
    auto volArea = ampArea.removeFromLeft(sliderWidth);
    volumeSlider.setBounds(volArea.reduced(2, 5));
    
    auto attArea = ampArea.removeFromLeft(sliderWidth);
    attackSlider.setBounds(attArea.reduced(2, 5));
    
    auto decArea = ampArea.removeFromLeft(sliderWidth);
    decaySlider.setBounds(decArea.reduced(2, 5));
    
    auto susArea = ampArea.removeFromLeft(sliderWidth);
    sustainSlider.setBounds(susArea.reduced(2, 5));
    
    auto relArea = ampArea;
    releaseSlider.setBounds(relArea.reduced(2, 5));
    
    // Filter group (middle)
    filterGroup.setBounds(contentRow.removeFromLeft(groupWidth).reduced(5));
    auto filterArea = filterGroup.getBounds().reduced(15, 30);
    
    auto cutoffArea = filterArea.removeFromLeft(filterArea.getWidth() / 2);
    filterCutoffSlider.setBounds(cutoffArea.reduced(5, 10));
    filterResSlider.setBounds(filterArea.reduced(5, 10));
    
    // Pitch group (right)
    pitchGroup.setBounds(contentRow.reduced(5));
    auto pitchArea = pitchGroup.getBounds().reduced(15, 30);
    
    auto rangeArea = pitchArea.removeFromLeft(pitchArea.getWidth() / 2);
    pitchRangeSlider.setBounds(rangeArea.reduced(5, 10));
    detuneSlider.setBounds(pitchArea.reduced(5, 10));
}