cmake_minimum_required(VERSION 3.16)
project(bucket-engine)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/src/*.hpp)

link_directories(${CMAKE_SOURCE_DIR}/lib)

configure_file(src/helpers/root-dir.h.in src/helpers/root-dir.h )

include_directories(${CMAKE_BINARY_DIR}/src)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
add_executable(bucket-engine ${HEADER_FILES} ${SOURCE_FILES})

# find & configure openGL
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# find_package(glm REQUIRED)
# message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# find_package(glfw3 REQUIRED)
# message(STATUS "GLFW3 included at ${GLFW3_INCLUDE_DIR}")

# add_library(STB_IMAGE "lib/stb_image.h")
# add_library(GLAD "lib/src/glad.c")

set(LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

include_directories(
	"${CMAKE_SOURCE_DIR}/src"	
	"${CMAKE_SOURCE_DIR}/include"
	OPENGL_INCLUDE_DIRS
	GLUT_INCLUDE_DIRS
)

target_link_libraries(bucket-engine ${LIBS})

