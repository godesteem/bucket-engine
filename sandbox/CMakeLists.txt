cmake_minimum_required(VERSION 3.16)
project(sandbox)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/sandbox/src/*.c ${CMAKE_SOURCE_DIR}/sandbox/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/sandbox/src/*.h ${CMAKE_SOURCE_DIR}/sandbox/src/*.hpp)

link_directories(${CMAKE_SOURCE_DIR}/lib)

#include_directories(${CMAKE_BINARY_DIR}/src)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
add_executable(sandbox ${HEADER_FILES} ${SOURCE_FILES})

set(LIBS ${CMAKE_SOURCE_PATH}/build/engine/libengine.so)

include_directories(
	"${CMAKE_SOURCE_DIR}/src"	
	"${CMAKE_SOURCE_DIR}/include"
)
include_directories(${CMAKE_SOURCE_DIR}/engine/vendor)

target_link_libraries(sandbox ${LIBS})


