cmake_minimum_required(VERSION 3.20)
project(NekoSynth VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find JUCE
if(NOT JUCE_ROOT)
    set(JUCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/JUCE")
endif()

add_subdirectory(${JUCE_ROOT} JUCE)

# Create plugin target
juce_add_plugin(NekoSynth
    PRODUCT_NAME "NekoSynth"
    FORMATS VST3
    PLUGIN_MANUFACTURER_CODE "Neko"
    PLUGIN_CODE "Neko"
    DESCRIPTION "Meow+Bark Synth"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
)

target_sources(NekoSynth PRIVATE
    PluginProcessor.cpp
    PluginEditor.cpp
)

target_compile_definitions(NekoSynth PRIVATE
    JUCE_PLUGINHOST_VST3=1
    JUCE_VST3_CAN_REPLACE_VST2=0
)

# Link JUCE modules
target_link_libraries(NekoSynth PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_gui_basics
    juce::juce_graphics
    juce::juce_data_structures
    juce::juce_events
)

# Enable implicit JUCE plugin client
set_target_properties(NekoSynth PROPERTIES
    JUCE_PLUGIN_CLIENT_ENABLED TRUE
)