project(gootest)

add_subdirectory(lib/googletest-master)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES Test1.h)

#core è la libreria definita nel CMakeList del progetto
add_library(googleTest ${SOURCE_FILES})

add_executable(Test1.h)

target_link_libraries(gootest ${GTEST_BOTH_LIBRARIES} core googleTest)