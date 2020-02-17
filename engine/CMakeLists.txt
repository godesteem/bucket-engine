cmake_minimum_required(VERSION 3.16)

project(engine VERSION 0.0.1 DESCRIPTION "This is the bucket engine.")
add_definitions(-DEXPORT_MOLECULE_DLL)

set(ENGINE_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Application.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Log.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/linux/X11Window.cpp
)
set(ENGINE_HEADER_FILES
  ${CMAKE_SOURCE_DIR}/engine/src/engine.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Application.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Core.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/EntryPoint.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Log.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Window.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/ApplicationEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/Event.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/KeyEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/MouseEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/platform/linux/X11Window.h
)


add_library(engine SHARED 
  ${ENGINE_SOURCE_FILES}
  ${ENGINE_HEADER_FILES}
)

set_target_properties(engine PROPERTIES SOVERSION 1)

target_include_directories(engine PRIVATE engine/src)
include_directories(
  "${CMAKE_SOURCE_DIR}/engine/vendor/spdlog/include/spdlog"
)
target_precompile_headers(engine PRIVATE ${CMAKE_SOURCE_DIR}/engine/src/bepch.h)

add_subdirectory(${CMAKE_SOURCE_DIR}/engine/vendor/glfw-3.3.2)
target_link_libraries(engine glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(engine OpenGL::GL)

include(GNUInstallDirs)

install(TARGETS engine
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

