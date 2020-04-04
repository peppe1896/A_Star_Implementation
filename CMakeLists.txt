cmake_minimum_required(VERSION 3.15)
project(LabProgrammazione)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Game.cpp Game.h entity.h player.cpp player.h nodeMap.h nodeMap.cpp Graph.h Graph.cpp Subject.h Observer.h)

#NON è necessario impostare SFML_ROOT

set(CMAKE_MODULE_PATH "${SFML_ROOT}/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system audio network REQUIRED)

if(WIN32) #FIX: non funziona su Windows
    add_subdirectory(Tests/lib/googletest-master)
    include_directories(Tests/lib/googletest-master/googlemock/include)
    include_directories(Tests/lib/googletest-master/googletest/include)
endif()

if(UNIX)
    add_subdirectory(Tests)
endif()

add_executable(LabProgrammazione main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(LabProgrammazione core sfml-window sfml-graphics sfml-system sfml-audio sfml-network)
