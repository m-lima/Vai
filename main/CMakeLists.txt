cmake_minimum_required(VERSION 3.2)
set(SUB_PROJECT_NAME Vai)
set(EXECUTABLE_NAME vai)
set(TESTER_NAME tester)

project("${SUB_PROJECT_NAME}" CXX)

##------------------------------------------------------------------------------
## Initialization
##

# Set base directories
set(CPP_SRC_DIR "src/cpp")
set(LIB_DIR "lib")

# Add manual libs
list(APPEND INCLUDE_DIRS ${GLOBAL_INCLUDE_DIR})
list(APPEND INCLUDE_DIRS "include")

##------------------------------------------------------------------------------
## Dependencies
##

if (NOT WIN32)
  find_package(Curses REQUIRED)
  list(APPEND INCLUDE_DIRS "${CURSES_INCLUDE_DIRS}")
  list(APPEND LIBRARIES "${CURSES_LIBRARIES}")
endif()

add_subdirectory("${LIB_DIR}/fmt")
list(APPEND INCLUDE_DIRS "${LIB_DIR}/fmt")
list(APPEND LIBRARIES fmt::fmt-header-only)

add_subdirectory("${LIB_DIR}/curlpp")
list(APPEND INCLUDE_DIRS "${LIB_DIR}/curlpp/include")
list(APPEND LIBRARIES curlpp_static)

##------------------------------------------------------------------------------
## Sources
##

list(APPEND SOURCES
    ${CPP_SRC_DIR}/view/console.cpp
    ${CPP_SRC_DIR}/config/config_parser.cpp
    ${CPP_SRC_DIR}/config/config_manager.cpp
    ${CPP_SRC_DIR}/config/executor/executor.cpp
    ${CPP_SRC_DIR}/config/executor/executor_parser.cpp
    ${CPP_SRC_DIR}/config/executor/completer/completer_registry.cpp
    ${CPP_SRC_DIR}/config/executor/completer/duck_completer.cpp
    ${CPP_SRC_DIR}/config/executor/completer/google_completer.cpp
    )

list(APPEND HEADERS
    ${CPP_SRC_DIR}/view/console.hpp
    ${CPP_SRC_DIR}/config/config_manager.hpp
    ${CPP_SRC_DIR}/config/config_parser.hpp
    ${CPP_SRC_DIR}/config/executor/executor.hpp
    ${CPP_SRC_DIR}/config/executor/executor_manager.hpp
    ${CPP_SRC_DIR}/config/executor/executor_manager_parser.hpp
    ${CPP_SRC_DIR}/config/executor/executor_parser.hpp
    ${CPP_SRC_DIR}/config/executor/completer/abstract_completer.hpp
    ${CPP_SRC_DIR}/config/executor/completer/completer_registry.hpp
    ${CPP_SRC_DIR}/config/executor/completer/duck_completer.hpp
    ${CPP_SRC_DIR}/config/executor/completer/google_completer.hpp
    ${CPP_SRC_DIR}/config/executor/completer/dumb_completer.hpp
    ${CPP_SRC_DIR}/config/executor/encoder/url_encoder.hpp
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

