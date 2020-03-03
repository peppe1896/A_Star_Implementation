project(gootest)

add_subdirectory(lib/googletest-master)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES Test1.h Test1.cpp)


target_link_libraries(gootest ${GTEST_BOTH_LIBRARIES} core)