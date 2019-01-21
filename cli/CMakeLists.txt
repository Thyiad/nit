include_directories("${PROJECT_SOURCE_DIR}/src")

add_library(nit-addon SHARED "nit-addon.cc")
set_target_properties(nit-addon PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(nit-addon nit ${Boost_LIBRARIES})
target_include_directories(nit-addon PRIVATE ${CMAKE_JS_INC})
