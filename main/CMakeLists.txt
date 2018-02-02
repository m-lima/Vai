cmake_minimum_required(VERSION 3.2)
set(PROJECT_NAME Vai)
set(EXECUTABLE_NAME vai)

project("${PROJECT_NAME}" CXX)

##------------------------------------------------------------------------------
## Initialization
##

# Set base directories
set(CPP_SRC_DIR "src/cpp")
set(LIB_DIR "lib")

# Add manual libs
list(APPEND INCLUDE_DIRS "include")

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
    ${CPP_SRC_DIR}/main.cpp
    )

list(APPEND HEADERS
    ${CPP_SRC_DIR}/model/executor.hpp
    ${CPP_SRC_DIR}/model/parser/abstract_parser.hpp
    ${CPP_SRC_DIR}/model/parser/word_parser.hpp
    )

list(APPEND SOURCES ${HEADERS})

##------------------------------------------------------------------------------
## Targets
##

# Create project
add_executable(${EXECUTABLE_NAME} ${SOURCES})
#add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS} ${SOURCES_CL})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES CXX_LANGUAGE_STANDARD 14 C_STANDARD 11)

# Organize the source
source_group("Headers" FILES ${HEADERS})

# Link with FIND_PACKAGE
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARIES})

# Add manual includes
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIRS})

