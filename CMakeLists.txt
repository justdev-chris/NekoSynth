cmake_minimum_required(VERSION 3.20)
project(NekoSynth VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/CMakeLists.txt")
    message(FATAL_ERROR "JUCE not found! Please clone JUCE into ${CMAKE_CURRENT_SOURCE_DIR}/JUCE")
endif()

# Set vendor information BEFORE adding JUCE subdirectory
set(JUCE_MODULE_VENDOR "justdev-chris")
set(JUCE_PLUGIN_MANUFACTURER "justdev-chris")

add_subdirectory(JUCE)

juce_add_plugin(NekoSynth
    PRODUCT_NAME "NekoSynth"
    FORMATS VST3
    PLUGIN_MANUFACTURER_CODE "JDC1"      # 4-character unique code
    PLUGIN_CODE "NSyn"                    # 4-character plugin code
    VST3_PLUGIN_MANUFACTURER "justdev-chris"    # Shows in DAW
    VST3_PLUGIN_NAME "NekoSynth"          # Plugin name
    VST3_PLUGIN_VENDOR "justdev-chris"    # Vendor for VST3
    VST3_PLUGIN_URL "https://github.com/justdev-chris"  # Optional
    VST3_PLUGIN_EMAIL "your@email.com"    # Optional
    DESCRIPTION "Meow + Bark Synth"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    COPY_PLUGIN_AFTER_BUILD TRUE           # Copies plugin to proper location
)

target_sources(NekoSynth PRIVATE
    PluginProcessor.cpp
    PluginEditor.cpp
)

# Link JUCE modules
target_link_libraries(NekoSynth PRIVATE
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_audio_plugin_client
    juce::juce_dsp
    juce::juce_audio_utils
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_basics
    juce::juce_gui_basics
    juce::juce_graphics
    juce::juce_data_structures
    juce::juce_events
    juce::juce_core
)

target_include_directories(NekoSynth PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(NekoSynth PRIVATE
    JUCE_PLUGINHOST_VST3=1
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    JUCE_WEB_BROWSER=0                      # Disable if not needed
    JUCE_USE_CURL=0                         # Disable if not needed
    # Force VST3 vendor metadata
    JUCE_VST3_MANUFACTURER_NAME="justdev-chris"
    JUCE_VST3_PLUGIN_VENDOR="justdev-chris"
    # Ensure manufacturer code is set
    JucePlugin_Manufacturer="justdev-chris"
    JucePlugin_ManufacturerCode=0x4A444331  # 'JDC1' in hex
)

set_target_properties(NekoSynth PROPERTIES
    JUCE_PLUGIN_CLIENT_ENABLED TRUE
    CXX_VISIBILITY_PRESET "hidden"          # Better for plugins
)

# Optional: Add a post-build step to show success
add_custom_command(TARGET NekoSynth POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "========================================"
    COMMAND ${CMAKE_COMMAND} -E echo "NekoSynth built successfully!"
    COMMAND ${CMAKE_COMMAND} -E echo "Vendor: justdev-chris"
    COMMAND ${CMAKE_COMMAND} -E echo "Plugin: NekoSynth.vst3"
    COMMAND ${CMAKE_COMMAND} -E echo "========================================"
)

# Optional: Install target for easy copying to plugin folder
install(TARGETS NekoSynst
    RUNTIME DESTINATION .
    LIBRARY DESTINATION .
)
