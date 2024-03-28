cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(bplus_fit)

file(GLOB_RECURSE SOURCE_FILES "source/*.cxx")
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS RIO Net RooFit MathCore)

include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(bplus_fit SHARED ${SOURCE_FILES})
target_link_libraries(bplus_fit ${ROOT_LIBRARIES})

#add_executable(treemaker source/test.cxx)
#target_link_libraries(treemaker treemakerDict ${ROOT_LIBRARIES})

