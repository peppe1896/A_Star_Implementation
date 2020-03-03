cmake_minimum_required(VERSION 3.15)
project(LabProgrammazione)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp Game.cpp Game.h)

#ATTIVA SU WINDOWS
set(SFML_ROOT "C:/Librerie/SFML-2.5.1")

set(CMAKE_MODULE_PATH "${SFML_ROOT}/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system audio network REQUIRED)

add_subdirectory(Tests/lib/googletest-master)
include_directories(Tests/lib/googletest-master/googlemock/include)
include_directories(Tests/lib/googletest-master/googletest/include)

add_executable(LabProgrammazione ${SOURCE_FILES})

add_library(core ${SOURCE_FILES})

target_link_libraries(LabProgrammazione sfml-window sfml-graphics sfml-system sfml-audio sfml-network)
target_link_libraries(LabProgrammazione gtest gtest_main)