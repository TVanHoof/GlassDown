cmake_minimum_required(VERSION 3.22)

set(PROJECTNAME GlassDown)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(PLUGIN_VERSION 0.0.1)
  set(GENERATE_MANIFEST TRUE)
else()
  set(PLUGIN_VERSION 0.0.0)
  set(GENERATE_MANIFEST FALSE)
endif()

project(${PROJECTNAME} VERSION 0.0.0)

add_subdirectory(deps/JUCE)

juce_add_plugin(${PROJECTNAME}
  PRODUCT_NAME ${PROJECTNAME}
  VERSION ${PLUGIN_VERSION}
  COMPANY_NAME "EpiCenter"
  BUNDLE_ID com.epicenter.${PROJECTNAME}

  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT FALSE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE

  EDITOR_WANTS_KEYBOARD_FOCUS FALSE

  COPY_PLUGIN_AFTER_BUILD TRUE

  PLUGIN_MANUFACTURER_CODE EpiC
  PLUGIN_CODE GlDo

  FORMATS VST3 AU Standalone
  VST3_AUTO_MANIFEST ${GENERATE_MANIFEST}
)

get_target_property(_gd_bundle_id ${PROJECTNAME} JUCE_BUNDLE_ID)
if(NOT _gd_bundle_id MATCHES "^[A-Za-z0-9][A-Za-z0-9.-]*$")
  message(FATAL_ERROR "BUNDLE ID '${_gd_bundle_id}' is not a valid Apple bundle identifier "
    "(letters, digits, '.' and '-' are the only valid characters")
endif()

target_sources(${PROJECTNAME}
  PRIVATE
    src/PluginProcessor.cpp
    src/PluginEditor.cpp
)

add_subdirectory(src/PluginLogic)

# Defines BUILD_TESTING (ON by default) and the `test` target. Wrapped so
# release builds can configure with -DBUILD_TESTING=OFF to skip the tests.
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

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
