cmake_minimum_required(VERSION 3.2)
project(Vai CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Current state
if (WIN32)
  message(STATUS "WIN32")
endif ()
if (MSVC)
  message(STATUS "MSVC")
endif ()
if (APPLE)
  message(STATUS "APPLE")
endif ()

message(STATUS "Using C: " ${CMAKE_C_COMPILER_ID})
message(STATUS "Using CXX: " ${CMAKE_CXX_COMPILER_ID})

# Set high warning levels
if (MSVC)
  if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif ()
else ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wno-long-long -pedantic")
endif ()

# Make $HOME compatible with windows
STRING(REGEX REPLACE "\\\\" "/" ENV_HOME_DIR "$ENV{HOME}")

# Add custom modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/findcmake")

# Set base directories
set(CPP_SRC_DIR "src/main/cpp")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

# Add manual libs
list(APPEND INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")

##------------------------------------------------------------------------------
## Dependencies
##

# add_subdirectory("${LIB_DIR}/fmt")
# list(APPEND INCLUDE_DIRS "${LIB_DIR}/fmt")
# list(APPEND LIBRARIES fmt::fmt-header-only)

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
add_executable(vai ${SOURCES})
#add_executable(vai ${SOURCES} ${HEADERS} ${SOURCES_CL})
set_target_properties(vai PROPERTIES CXX_LANGUAGE_STANDARD 14 C_STANDARD 11)

# Organize the source
source_group("Headers" FILES ${HEADERS})

# Link with FIND_PACKAGE
target_link_libraries(vai PRIVATE ${LIBRARIES})

# Add manual includes
target_include_directories(vai PRIVATE ${INCLUDE_DIRS})

