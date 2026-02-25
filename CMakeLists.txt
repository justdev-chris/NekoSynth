cmake_minimum_required(VERSION 3.20)
project(NekoSynth VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_DEBUG_LOGGING "Enable debug logging to Downloads folder" OFF)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/CMakeLists.txt")
    message(FATAL_ERROR "JUCE not found! Please clone JUCE into ${CMAKE_CURRENT_SOURCE_DIR}/JUCE")
endif()

add_subdirectory(JUCE)

juce_add_plugin(NekoSynth
    PRODUCT_NAME "NekoSynth"
    FORMATS VST3
    PLUGIN_MANUFACTURER_CODE "JDC"
    PLUGIN_CODE "NSyn"
    DESCRIPTION "Meow+Bark Synth"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
)

target_sources(NekoSynth PRIVATE
    PluginProcessor.cpp
    PluginEditor.cpp
    DebugLogger.h
)

target_link_libraries(NekoSynth PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_gui_basics
    juce::juce_graphics
    juce::juce_data_structures
    juce::juce_events
    juce::juce_core
    shell32.lib
)

target_include_directories(NekoSynth PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(ENABLE_DEBUG_LOGGING)
    target_compile_definitions(NekoSynth PRIVATE DEBUG_MODE=1)
    message(STATUS "Debug logging enabled - logs will go to Downloads folder")
endif()

target_compile_definitions(NekoSynth PRIVATE
    JUCE_PLUGINHOST_VST3=1
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)

set_target_properties(NekoSynth PROPERTIES
    JUCE_PLUGIN_CLIENT_ENABLED TRUE
)