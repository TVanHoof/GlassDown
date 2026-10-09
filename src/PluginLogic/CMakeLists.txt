set(SOURCES
  Graph.cpp
  PluginLogic.cpp
  Segment.cpp
)

set(HEADERS
  Graph.h
  PluginLogic.h
  Segment.h
)

add_library(PluginLogic STATIC "${SOURCES}" "${HEADERS}")

target_include_directories(PluginLogic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_features(PluginLogic PUBLIC cxx_std_17)

target_compile_definitions(PluginLogic PUBLIC JUCE_WEB_BROWSER=0)

target_link_libraries(PluginLogic PUBLIC juce::juce_audio_processors)
