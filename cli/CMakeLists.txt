include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(nit-colex nit-colex.cc)
target_link_libraries(nit-colex nit ${Boost_LIBRARIES})

add_executable(nit-eval nit-eval.cc)
target_link_libraries(nit-eval nit ${Boost_LIBRARIES})

add_executable(nit-lut nit-lut.cc)
target_link_libraries(nit-lut nit ${Boost_LIBRARIES})

set(CMAKE_JS_INC "/home/jaimin/.cmake-js/node-x64/v8.10.0/include/node;/usr/local/lib/node_modules/nan")
add_library(nit-addon "nit-addon.cc")
set_target_properties(nit-addon PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(nit-addon nit ${Boost_LIBRARIES})
target_include_directories(nit-addon PRIVATE ${CMAKE_JS_INC})