cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("pileup_maps")
################################################
file(GLOB_RECURSE SOURCE_FILES "source/*.cxx")
find_package(Boost)
find_package(ROOT)
################################################
include(${ROOT_USE_FILE})
include_directories(include)
include_directories(${Boost_INCLUDE_DIRS})
################################################
add_library(reader SHARED ${SOURCE_FILES} )
target_link_libraries( reader ${ROOT_LIBRARIES} ${Boost_LIBRARIES} )

add_library(writer SHARED ${SOURCE_FILES} )
target_link_libraries( writer ${ROOT_LIBRARIES} ${Boost_LIBRARIES} )

add_executable( tester source/tester.cxx )
target_link_libraries( tester reader writer )
################################################

