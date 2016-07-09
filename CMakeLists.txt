CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -pthread")

#GMock & GTest
ADD_SUBDIRECTORY(./libs/googletest/googlemock)
ENABLE_TESTING()
INCLUDE_DIRECTORIES(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
INCLUDE_DIRECTORIES(project)

PROJECT(egnyte)


ADD_LIBRARY(egnyte_lib project/TimerV1.cpp project/TimerV1.hpp project/TimerV0.cpp project/TimerV0.hpp)
ADD_EXECUTABLE(egnyte project/main.cpp)
TARGET_LINK_LIBRARIES(egnyte egnyte_lib)


ADD_EXECUTABLE(runUnitTests
               project/test_TimerV1.cpp
               project/test_TimerV0.cpp)
TARGET_LINK_LIBRARIES(runUnitTests gtest gtest_main)
TARGET_LINK_LIBRARIES(runUnitTests egnyte_lib)
