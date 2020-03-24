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

set(ENV{ROOT_DIR} ${CMAKE_SOURCE_DIR})

set(CORE_DIR ${CMAKE_SOURCE_DIR}/engine/src/engine/core/)
set(RENDERER_DIR ${CMAKE_SOURCE_DIR}/engine/src/engine/renderer/)
set(PLATFORM_DIR ${CMAKE_SOURCE_DIR}/engine/src/platform/)
set(MATH_DIR "${CMAKE_SOURCE_DIR}/engine/lib/math")

set(NOISE_DIR "${CMAKE_SOURCE_DIR}/engine/lib/noise")
set(ENGINE_SOURCE_FILES
  # sources
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Application.cpp
  ${CORE_DIR}Layer.cpp
  ${CORE_DIR}LayerStack.cpp

  #GUI
  ${CMAKE_SOURCE_DIR}/engine/src/engine/imgui/ImGuiLayer.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/imgui/ImGUIBuild.cpp

  # renderer
  ${RENDERER_DIR}Shader.cpp
  ${RENDERER_DIR}Buffer.cpp
  ${RENDERER_DIR}Renderer.cpp
  ${RENDERER_DIR}RenderCommand.cpp
  ${RENDERER_DIR}RendererAPI.cpp
  ${RENDERER_DIR}VertexArray.cpp

  ${RENDERER_DIR}camera/OrthographicCamera.cpp
  ${RENDERER_DIR}camera/OrthographicCameraController.cpp

  ${RENDERER_DIR}mesh/Texture.cpp
  ${RENDERER_DIR}mesh/Mesh.cpp

  # i/o
  ${CORE_DIR}io/Log.cpp

  # game
  ${CMAKE_SOURCE_DIR}/engine/src/engine/game/Level.cpp
  ${CMAKE_SOURCE_DIR}/engine/src/engine/game/KineticBody.cpp


  #platform
  ${PLATFORM_DIR}linux/X11Window.cpp
  ${PLATFORM_DIR}linux/LinuxInput.cpp

  # renderer
  ${PLATFORM_DIR}opengl/OpenGLContext.cpp
  ${PLATFORM_DIR}opengl/OpenGLBuffer.cpp
  ${PLATFORM_DIR}opengl/OpenGLRendererAPI.cpp
  ${PLATFORM_DIR}opengl/OpenGLVertexArray.cpp
  ${PLATFORM_DIR}opengl/OpenGLShader.cpp
  ${PLATFORM_DIR}opengl/OpenGLTexture.cpp
  ${PLATFORM_DIR}opengl/OpenGLMesh.cpp

  #3rd party
  ${imgui_root}/imgui.cpp
  ${imgui_root}/imgui_demo.cpp
  ${imgui_root}/imgui_draw.cpp
  ${imgui_root}/imgui_widgets.cpp

  # noise
  ${NOISE_DIR}/noise.cpp
  )
set(ENGINE_HEADER_FILES
  # sources
  ${CMAKE_SOURCE_DIR}/engine/src/engine.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/Application.h
  ${CORE_DIR}Core.h
  ${CORE_DIR}EntryPoint.h
  ${CORE_DIR}Layer.h
  ${CORE_DIR}LayerStack.h
  ${CORE_DIR}Window.h
  ${CORE_DIR}Timestep.h

  #GUI
  ${CMAKE_SOURCE_DIR}/engine/src/engine/imgui/ImGuiLayer.h

  # events
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/ApplicationEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/Event.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/KeyEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/MouseEvent.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/events/CollisionEvent.h

  # input/output
  ${CORE_DIR}io/Log.h
  ${CORE_DIR}io/KeyCodes.h
  ${CORE_DIR}io/MouseButtonCodes.h
  ${CORE_DIR}io/Input.h

  # renderer
  ${RENDERER_DIR}GraphicsContext.h
  ${RENDERER_DIR}Buffer.h
  ${RENDERER_DIR}Shader.h
  ${RENDERER_DIR}Renderer.h
  ${RENDERER_DIR}RenderCommand.h
  ${RENDERER_DIR}VertexArray.h

  ${RENDERER_DIR}camera/OrthographicCamera.h
  ${RENDERER_DIR}camera/OrthographicCameraController.h

  ${RENDERER_DIR}mesh/Texture.h
  ${RENDERER_DIR}mesh/Mesh.h

  # game
  ${CMAKE_SOURCE_DIR}/engine/src/engine/game/Level.h
  ${CMAKE_SOURCE_DIR}/engine/src/engine/game/KineticBody.h


  ## Platform
  # windows
  ${PLATFORM_DIR}linux/X11Window.h
  ${PLATFORM_DIR}linux/LinuxInput.h

  # renderer
  ${PLATFORM_DIR}opengl/OpenGLContext.h
  ${PLATFORM_DIR}opengl/OpenGLRendererAPI.h
  ${PLATFORM_DIR}opengl/OpenGLBuffer.h
  ${PLATFORM_DIR}opengl/OpenGLVertexArray.h
  ${PLATFORM_DIR}opengl/OpenGLShader.h
  ${PLATFORM_DIR}opengl/OpenGLTexture.h
  ${PLATFORM_DIR}opengl/OpenGLMesh.h

  #3rd party
  ${imgui_root}/imconfig.h
  ${imgui_root}/imgui.h
  ${imgui_root}/imgui_internal.h
  ${imgui_root}/imstb_rectpack.h
  ${imgui_root}/imstb_textedit.h
  ${imgui_root}/imstb_truetype.h

  ${MATH_DIR}/math.h
  ${MATH_DIR}/matrix.h
  ${NOISE_DIR}/noise.h
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
  "${CMAKE_SOURCE_DIR}/engine/vendor/spdlog/include"
  "${GLAD_DIR}/include"
  "${imgui_root}"
  "${CMAKE_SOURCE_DIR}/engine/vendor/stb_image"
)
target_precompile_headers(engine PRIVATE ${CMAKE_SOURCE_DIR}/engine/src/bepch.h)
add_library(stb_image STATIC
  ${CMAKE_SOURCE_DIR}/engine/vendor/stb_image/stb_image.cpp
  ${CMAKE_SOURCE_DIR}/engine/vendor/stb_image/stb_image.h
)
add_subdirectory(${CMAKE_SOURCE_DIR}/engine/vendor/spdlog)
add_subdirectory(${CMAKE_SOURCE_DIR}/engine/vendor/glfw-3.3.2)
add_subdirectory(${CMAKE_SOURCE_DIR}/engine/vendor/glm/glm)
#add_subdirectory(${MATH_DIR})
#add_library(glm SHARED ${CMAKE_SOURCE_DIR}/engine/vendor/glm/glm)
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)
#add_subdirectory(${CMAKE_SOURCE_DIR}/engine/vendor/imgui)
# target_include_directories(engine PUBLIC "${GLAD_DIR}/include")

# target_include_directories(glad PRIVATE "${GLAD_DIR}/include")

find_package(OpenGL REQUIRED)
target_link_libraries(engine PUBLIC OpenGL::GL glad glfw glm stb_image spdlog)

# add_library("glad" "${GLAD_DIR}/src/glad.c")
# target_include_directories(engine PRIVATE "${GLAD_DIR}/include")
# target_link_libraries(engine "glad" "${CMAKE_DL_LIBS}")

include(GNUInstallDirs)

install(TARGETS engine
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

