cmake_minimum_required(VERSION 3.16)

project(engine VERSION 0.0.1 DESCRIPTION "This is the bucket engine.")
add_definitions(-DEXPORT_MOLECULE_DLL)

file(GLOB_RECURSE ENGINE_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/engine/src/engine/*.c 
  ${CMAKE_SOURCE_DIR}/engine/src/*.c 
  ${CMAKE_SOURCE_DIR}/engine/src/engine/*.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/*.cpp
)
file(GLOB_RECURSE ENGINE_HEADER_FILES
  ${CMAKE_SOURCE_DIR}/engine/src/engine/*.h
  ${CMAKE_SOURCE_DIR}/engine/src/*.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/*.hpp
  ${CMAKE_SOURCE_DIR}/engine/src/*.hpp
)


add_library(engine SHARED 
  ${ENGINE_SOURCE_FILES}
  ${ENGINE_HEADER_FILES}
)

set_target_properties(engine PROPERTIES SOVERSION 1)

target_include_directories(engine PRIVATE engine/include)
target_include_directories(engine PRIVATE engine/src)
include_directories(
  "${CMAKE_SOURCE_DIR}/engine/vendor/spdlog/include/spdlog"	
)


include(GNUInstallDirs)

install(TARGETS engine
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

