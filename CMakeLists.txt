CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -pthread")

#GMock & GTest
ADD_SUBDIRECTORY(./libs/googletest/googlemock)
ENABLE_TESTING()
INCLUDE_DIRECTORIES(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
INCLUDE_DIRECTORIES(project)

PROJECT(egnyte)


ADD_LIBRARY(egnyte_lib
            project/Timer.cpp
            project/Timer.hpp)
ADD_EXECUTABLE(egnyte project/main.cpp)
TARGET_LINK_LIBRARIES(egnyte egnyte_lib)


ADD_EXECUTABLE(runUnitTests
               project/Timer_test.cpp
               )
TARGET_LINK_LIBRARIES(runUnitTests gtest gtest_main)
TARGET_LINK_LIBRARIES(runUnitTests egnyte_lib)
