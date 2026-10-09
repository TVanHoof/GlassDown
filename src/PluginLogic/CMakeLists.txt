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

# No JUCE linkage on purpose. The module targets are INTERFACE libraries that
# ship their .cpp files as INTERFACE_SOURCES, so linking one here would make
# this library compile its own copy of ~16 JUCE modules, duplicating the work
# juce_add_plugin already does for the shared-code target. Keeping this target
# JUCE-free means JUCE is compiled exactly once, and it makes the DSP logic
# unit-testable without a JUCE build.
