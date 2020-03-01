cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 17)
project(engine VERSION 0.0.1 DESCRIPTION "This is the bucket engine.")
add_definitions(-DEXPORT_MOLECULE_DLL)
set(imgui_root ${CMAKE_SOURCE_DIR}/engine/vendor/imgui)

if(BE_PLATFORM_WINDOWS)
  add_compile_definitions(IMGUI_API=__declspec(dllexport))
elseif(BE_PLATFORM_LINUX)
  add_compile_definitions(IMGUI_API)
endif(BE_PLATFORM_WINDOWS)

set(CORE_DIR ${CMAKE_SOURCE_DIR}/engine/src/engine/core/)

set(ENGINE_SOURCE_FILES
  # sources
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Application.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Log.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Layer.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/LayerStack.cpp

  #GUI
  ${CMAKE_SOURCE_DIR}/engine/src/engine/imgui/ImGuiLayer.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/imgui/ImGUIBuild.cpp

  # renderer
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Shader.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Buffer.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Renderer.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/RenderCommand.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/RendererAPI.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/VertexArray.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/OrthographicCamera.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/OrthographicCameraController.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Texture.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Model.cpp

  #platform
  ${CMAKE_SOURCE_DIR}/engine/src/platform/linux/X11Window.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/linux/LinuxInput.cpp

  # renderer
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLContext.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLBuffer.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLRendererAPI.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLVertexArray.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLShader.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLTexture.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLModel.cpp

  #3rd party
  ${imgui_root}/imgui.cpp
  ${imgui_root}/imgui_demo.cpp
  ${imgui_root}/imgui_draw.cpp
  ${imgui_root}/imgui_widgets.cpp
  )
set(ENGINE_HEADER_FILES
  # sources
  ${CMAKE_SOURCE_DIR}/engine/src/engine.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Application.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Core.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/EntryPoint.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Log.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Layer.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/LayerStack.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Window.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/KeyCodes.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/MouseButtonCodes.h
  ${CORE_DIR}Timestep.h

  #GUI
  ${CMAKE_SOURCE_DIR}/engine/src/engine/imgui/ImGuiLayer.h

  # events
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/ApplicationEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/Event.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/KeyEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/MouseEvent.h

  # input
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Input.h

  # renderer
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/GraphicsContext.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Buffer.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Shader.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Renderer.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/RenderCommand.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/VertexArray.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/OrthographicCamera.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/OrthographicCameraController.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Texture.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/Model.h

  ## Platform
  # windows
  ${CMAKE_SOURCE_DIR}/engine/src/platform/linux/X11Window.h
  ${CMAKE_SOURCE_DIR}/engine/src/platform/linux/LinuxInput.h

  # renderer
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLContext.h
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLRendererAPI.h
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLBuffer.h
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLVertexArray.h
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLShader.h
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLTexture.h
  ${CMAKE_SOURCE_DIR}/engine/src/platform/opengl/OpenGLModel.h

  #3rd party
  ${imgui_root}/imconfig.h
  ${imgui_root}/imgui.h
  ${imgui_root}/imgui_internal.h
  ${imgui_root}/imstb_rectpack.h
  ${imgui_root}/imstb_textedit.h
  ${imgui_root}/imstb_truetype.h
  )

set(GLAD_DIR "${CMAKE_SOURCE_DIR}/engine/vendor/glad")

add_library(engine STATIC
  ${ENGINE_SOURCE_FILES}
  ${ENGINE_HEADER_FILES}
#  ${CMAKE_SOURCE_DIR}/engine/src/engine.def
)

set_target_properties(engine PROPERTIES SOVERSION 1)

target_include_directories(engine PRIVATE engine/src)
include_directories(
  "${CMAKE_SOURCE_DIR}/engine/vendor/spdlog/include/spdlog"
  "${GLAD_DIR}/include"
  "${imgui_root}"
  "${CMAKE_SOURCE_DIR}/engine/vendor/stb_image"
)
target_precompile_headers(engine PRIVATE ${CMAKE_SOURCE_DIR}/engine/src/bepch.h)
add_library(stb_image STATIC
  ${CMAKE_SOURCE_DIR}/engine/vendor/stb_image/stb_image.cpp
  ${CMAKE_SOURCE_DIR}/engine/vendor/stb_image/stb_image.h
)
add_subdirectory(${CMAKE_SOURCE_DIR}/engine/vendor/glfw-3.3.2)
add_subdirectory(${CMAKE_SOURCE_DIR}/engine/vendor/glm/glm)
#add_library(glm SHARED ${CMAKE_SOURCE_DIR}/engine/vendor/glm/glm)
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)
#add_subdirectory(${CMAKE_SOURCE_DIR}/engine/vendor/imgui)
# target_include_directories(engine PUBLIC "${GLAD_DIR}/include")

# target_include_directories(glad PRIVATE "${GLAD_DIR}/include")

find_package(OpenGL REQUIRED)
target_link_libraries(engine PUBLIC OpenGL::GL glad glfw glm stb_image)

# add_library("glad" "${GLAD_DIR}/src/glad.c")
# target_include_directories(engine PRIVATE "${GLAD_DIR}/include")
# target_link_libraries(engine "glad" "${CMAKE_DL_LIBS}")

include(GNUInstallDirs)

install(TARGETS engine
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

