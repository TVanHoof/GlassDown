# SPDX-License-Identifier: AGPL-3.0-or-later
#
# Copyright (C) 2026  Thomas Van Hoof
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU Affero General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version. See LICENSE for the full text.

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

target_compile_features(PluginLogicTests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(PluginLogicTests)
