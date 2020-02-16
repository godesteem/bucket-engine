cmake_minimum_required(VERSION 3.16)

project(engine VERSION 0.0.1 DESCRIPTION "This is the bucket engine.")
add_definitions(-DEXPORT_MOLECULE_DLL)

set(ENGINE_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Application.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Log.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/linux/X11Window.cpp
)
set(ENGINE_HEADER_FILES
  src/engine/events/Event.h
  src/engine/events/ApplicationEvent.h
  src/engine/events/KeyEvent.h
  src/engine/events/MouseEvent.h

  src/engine/Application.h
  src/engine/Core.h
  src/engine/EntryPoint.h
  src/engine/Log.h
  src/engine/Window.h
  
  src/platform/linux/X11Window.h
)

add_library(engine SHARED 
  ${ENGINE_SOURCE_FILES}
  ${ENGINE_HEADER_FILES}
)

set_target_properties(engine PROPERTIES SOVERSION 1)
target_precompile_headers(engine 
  PUBLIC src/bepch.h)
#set_target_properties(engine PROPERTIES COMPILE_FLAGS "${CMAKE_SOURCE_DIR}/engine/src/bepch.h")
#set_source_files_properties(std.cpp PROPERTIES COMPILE_FLAGS "${CMAKE_SOURCE_DIR}/engine/src/bepch.h")

target_include_directories(engine PRIVATE engine/include)
target_include_directories(engine PRIVATE engine/src)



include_directories(
  vendor/spdlog/include/spdlog
  vendor/glfw-3.3.2/include/GLFW
)
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

find_package(glm REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(glfw3 REQUIRED)
message(STATUS "GLFW3 included at ${GLFW3_INCLUDE_DIR}")

# add_library(STB_IMAGE "lib/stb_image.h")
# add_library(GLAD "lib/src/glad.c")

set(LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLM_LIBRARY})

# add_library(GLAD "lib/src/glad.c")
target_link_libraries(engine ${LIBS})


include(GNUInstallDirs)

install(TARGETS engine
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

