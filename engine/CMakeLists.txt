cmake_minimum_required(VERSION 3.16)

project(engine VERSION 0.0.1 DESCRIPTION "This is the bucket engine.")
add_definitions(-DEXPORT_MOLECULE_DLL)

set(ENGINE_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Application.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Log.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Layer.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/LayerStack.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/linux/X11Window.cpp
)
set(ENGINE_HEADER_FILES
  ${CMAKE_SOURCE_DIR}/engine/src/engine.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Application.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Core.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/EntryPoint.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Log.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Layer.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/LayerStack.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Window.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/ApplicationEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/Event.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/KeyEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/MouseEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/platform/linux/X11Window.h
)

set(GLAD_DIR "${CMAKE_SOURCE_DIR}/engine/vendor/glad")

add_library(engine SHARED 
  ${ENGINE_SOURCE_FILES}
  ${ENGINE_HEADER_FILES}
)

set_target_properties(engine PROPERTIES SOVERSION 1)

target_include_directories(engine PRIVATE engine/src)
include_directories(
  "${CMAKE_SOURCE_DIR}/engine/vendor/spdlog/include/spdlog"
  "${GLAD_DIR}/include"
)
target_precompile_headers(engine PRIVATE ${CMAKE_SOURCE_DIR}/engine/src/bepch.h)

add_subdirectory(${CMAKE_SOURCE_DIR}/engine/vendor/glfw-3.3.2)
# target_include_directories(engine PUBLIC "${GLAD_DIR}/include")

add_library(glad SHARED ${GLAD_DIR}/src/glad.c)
# target_include_directories(glad PRIVATE "${GLAD_DIR}/include")


#glad_add_library(glad SHARED MX API gl:core=3.3)


find_package(OpenGL REQUIRED)
target_link_libraries(engine OpenGL::GL glad glfw)

# add_library("glad" "${GLAD_DIR}/src/glad.c")
# target_include_directories("glad" PRIVATE ${GLAD_DIR}/include)
# target_include_directories(engine PRIVATE "${GLAD_DIR}/include")
# target_link_libraries(engine "glad" "${CMAKE_DL_LIBS}")

include(GNUInstallDirs)

install(TARGETS engine
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

