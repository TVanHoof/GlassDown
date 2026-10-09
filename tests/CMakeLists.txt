add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../deps/googletest
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest
                 EXCLUDE_FROM_ALL)

add_executable(PluginLogicTests
  PluginLogic/SegmentTests.cpp
  PluginLogic/GraphTests.cpp
)

target_link_libraries(PluginLogicTests
  PRIVATE
    PluginLogic
    GTest::gtest_main
)

target_compile_features(PluginLogicTests PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(PluginLogicTests)
