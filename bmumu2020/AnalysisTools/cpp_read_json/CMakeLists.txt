cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("json_reader")

enable_testing()
################################################
set(EXECUTABLE "test_reader")
set(LIBRARY "json_reader")
################################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
################################################
include_directories(include)
################################################
add_library(${LIBRARY} SHARED src/json_reader.cxx )
target_link_libraries( ${LIBRARY} ${LDEPENDENCE} )

add_executable( ${EXECUTABLE} src/test_reader.cxx )
target_link_libraries( ${EXECUTABLE} ${LIBRARY} )
################################################

