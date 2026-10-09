cmake_minimum_required(VERSION 3.22)

set(PROJECTNAME SwitchBoard)

project(${PROJECTNAME} VERSION 0.0.0)

add_subdirectory(deps/JUCE)

juce_add_plugin(${PROJECTNAME}
  COMPANY_NAME "EpiCenter"
  BUNDLE_ID com.epicenter,${PROJECTNAME}

  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT FALSE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE

  EDITOR_WANTS_KEYBOARD_FOCUS FALSE

  COPY_PLUGIN_AFTER_BUILD TRUE

  PLUGIN_MANUFACTURER_CODE EpiC
  PLUGIN_CODE SwBo

  FORMATS VST3 AU Standalone

  PRODUCT_NAME ${PROJECTNAME}
)

target_sources(${PROJECTNAME}
  PRIVATE
    src/PluginProcessor.cpp
    src/PluginEditor.cpp
)

add_subdirectory(src/PluginLogic)

# Lets the plugin sources include plugin code by its path relative to src/,
# e.g. #include <PluginLogic/PluginLogic.h>
target_include_directories(${PROJECTNAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_features(${PROJECTNAME} PRIVATE cxx_std_17)

target_compile_definitions(${PROJECTNAME} PUBLIC JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${PROJECTNAME}
  PRIVATE
    juce::juce_audio_utils
    PluginLogic

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
)
