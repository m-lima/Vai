cmake_minimum_required(VERSION 3.2)
set(SUB_PROJECT_NAME VaiTest)
set(EXECUTABLE_NAME vai_test)

project("${SUB_PROJECT_NAME}" CXX)

##------------------------------------------------------------------------------
## Initialization
##

# Set base directories
set(CPP_TEST_DIR "src/cpp")
set(LIB_DIR "lib")

# Add manual libs
list(APPEND INCLUDE_DIRS "include")

##------------------------------------------------------------------------------
## Dependencies
##

add_subdirectory("${LIB_DIR}/googletest")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

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
target_link_libraries(${EXECUTABLE_NAME} gtest gtest_main)
add_test(tests ${EXECUTABLE_NAME})

