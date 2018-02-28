cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME VaiMain)
project("${PROJECT_NAME}" CXX)

##------------------------------------------------------------------------------
## Initialization
##

# Enable tests
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Verboseness
SET(CMAKE_SHARED_LINKER_FLAGS "-v")
SET(CMAKE_MODULE_LINKER_FLAGS "-v")
SET(CMAKE_EXE_LINKER_FLAGS "-v")
#SET(GCC_LINK_FLAGS "-v")
#add_definitions("-DVERBOSE")

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

# Global dependency folders
set(GLOBAL_LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(GLOBAL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

##------------------------------------------------------------------------------
## Projects
##

add_subdirectory(test)
add_subdirectory(main)
