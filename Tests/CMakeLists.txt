project(gootest)

add_subdirectory(lib/googletest-master)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES Test1.h Test1.cpp)

#core è la libreria che abbiamo definito dentro il cmake iniziale del progetto
#che altro non contiene che tutti i cpp e h files
target_link_libraries(gootest ${GTEST_BOTH_LIBRARIES} core)