cmake_minimum_required(VERSION 3.1)

# In-source build prevention.
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(NIT VERSION 0.0.0 LANGUAGES CXX)

option(NIT_WITH_COVERAGE "Instrument for coverage analysis" OFF)
option(NIT_BUILD_CLI "Build command-line tools" ON)
option(NIT_BUILD_TESTS "Build tests" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # Needed for Clang Tooling.

# Require C++11 support.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror -Wnon-virtual-dtor -Wold-style-cast")

if(NIT_WITH_COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wpedantic -Wredundant-decls -Wcast-align -Wlogical-op -Wvla -Wuseless-cast -Wunreachable-code -Wmissing-declarations")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "7.1")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wshadow -Wimplicit-fallthrough=0")
  endif()

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-missing-braces -Wshadow -Wunused-exception-parameter")
endif()

#
# set up boost
#
set(Boost_USE_STATIC_LIBS ON)  
set(Boost_USE_STATIC_RUNTIME ON)

file(GLOB_RECURSE boostlib_cmake_path "${CMAKE_CURRENT_SOURCE_DIR}/node_modules" "BoostLib.cmake")
list(GET boostlib_cmake_path 0 boostlib_cmake_path)
get_filename_component(boostlib_cmake_path "${boostlib_cmake_path}" DIRECTORY)
SET(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${boostlib_cmake_path}")
include(BoostLib)

require_boost_libs(">= 1.58.0" "coroutine")
include_directories(${Boost_INCLUDE_DIRS})

# Also search for includes in PROJECT_BINARY_DIR to find config.h.
include_directories("${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(src)

if(NIT_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# Command-line tools
if(NIT_BUILD_CLI)
  add_subdirectory(cli)
endif()
