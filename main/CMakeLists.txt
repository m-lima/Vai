cmake_minimum_required(VERSION 3.2)
set(SUB_PROJECT_NAME Vai)
set(EXECUTABLE_NAME vai)
set(TESTER_NAME tester)

project("${SUB_PROJECT_NAME}" CXX)

##------------------------------------------------------------------------------
## Initialization
##

#SET(GCC_LINK_FLAGS "-v")
SET(CMAKE_SHARED_LINKER_FLAGS "-v")
SET(CMAKE_MODULE_LINKER_FLAGS "-v")
SET(CMAKE_EXE_LINKER_FLAGS "-v")

# Set base directories
set(CPP_SRC_DIR "src/cpp")
set(LIB_DIR "lib")

# Add manual libs
list(APPEND INCLUDE_DIRS ${GLOBAL_INCLUDE_DIR})
list(APPEND INCLUDE_DIRS "include")

# Set verbose
add_definitions("-DVERBOSE")

##------------------------------------------------------------------------------
## Dependencies
##

add_subdirectory("${LIB_DIR}/fmt")
list(APPEND INCLUDE_DIRS "${LIB_DIR}/fmt")
list(APPEND LIBRARIES fmt::fmt-header-only)

find_package(Threads)
list(APPEND LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")

##------------------------------------------------------------------------------
## Sources
##

list(APPEND SOURCES
    ${CPP_SRC_DIR}/view/console.cpp
    ${CPP_SRC_DIR}/config/config_manager.cpp
    ${CPP_SRC_DIR}/config/config_parser.cpp
    ${CPP_SRC_DIR}/config/executor/executor_parser.cpp
    ${CPP_SRC_DIR}/config/executor/parser/parser_registry.cpp
    )

list(APPEND HEADERS
    ${CPP_SRC_DIR}/view/console.hpp
    ${CPP_SRC_DIR}/config/config_manager.hpp
    ${CPP_SRC_DIR}/config/config_parser.hpp
    ${CPP_SRC_DIR}/config/executor/executor.hpp
    ${CPP_SRC_DIR}/config/executor/executor_manager.hpp
    ${CPP_SRC_DIR}/config/executor/executor_parser.hpp
    ${CPP_SRC_DIR}/config/executor/parser/abstract_parser.hpp
    ${CPP_SRC_DIR}/config/executor/parser/parser_registry.hpp
    ${CPP_SRC_DIR}/config/executor/parser/word_parser.hpp
    ${CPP_SRC_DIR}/config/executor/parser/dumb_parser.hpp
    )

list(APPEND SOURCES ${HEADERS})

##------------------------------------------------------------------------------
## Targets
##

# Create project
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${CPP_SRC_DIR}/main.cpp)
add_executable(${TESTER_NAME} ${SOURCES} ${CPP_SRC_DIR}/test.cpp)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES CXX_LANGUAGE_STANDARD 14 C_STANDARD 11)

# Organize the source
source_group("Headers" FILES ${HEADERS})

# Link with FIND_PACKAGE
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARIES})
target_link_libraries(${TESTER_NAME} PRIVATE ${LIBRARIES})

# Add manual includes
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIRS})
target_include_directories(${TESTER_NAME} PRIVATE ${INCLUDE_DIRS})

