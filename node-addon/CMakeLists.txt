cmake_minimum_required(VERSION 3.1)

project(test_addon)

# Build a shared library named after the project from the files in `src/`
file(GLOB SOURCE_FILES "addon/*.cc" "addon/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Gives our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Essential include files to build a node addon,
# You should add this line in every CMake.js based project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

# Essential library files to link to a node addon
# You should add this line in every CMake.js based project
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

message(STATUS "project: ${PROJECT_NAME}")
message(STATUS "source: ${SOURCE_FILES}")
message(STATUS "cmake_js_inc: ${CMAKE_JS_INC}")
message(STATUS "cmake_js_lib: ${CMAKE_JS_LIB}")