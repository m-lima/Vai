cmake_minimum_required(VERSION 3.2)
set(SUB_PROJECT_NAME VaiTest)
set(EXECUTABLE_NAME vai_test)

project("${SUB_PROJECT_NAME}" CXX)

##------------------------------------------------------------------------------
## Initialization
##

include(ExternalProject)
# Set base directories
set(CPP_TEST_DIR "src/cpp")
set(LIB_DIR "lib")

# Add manual libs
list(APPEND INCLUDE_DIRS "include")

##------------------------------------------------------------------------------
## Dependencies
##

ExternalProject_add(
    gtest
    URL https://github.com/google.googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
#add_subdirectory("${LIB_DIR}/googletest")
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

##------------------------------------------------------------------------------
## Sources
##

list(APPEND TESTS
    ${CPP_TEST_DIR}/model/word_parser_test.cpp
    )

##------------------------------------------------------------------------------
## Tests
##

add_executable(${EXECUTABLE_NAME} ${TESTS})
#add_dependencies(${EXECUTABLE_NAME} googletest)
#target_link_libraries(${SUB_PROJECT_NAME} gtest gtest_main)
add_test(tests ${EXECUTABLE_NAME})

