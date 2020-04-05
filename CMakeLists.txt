cmake_minimum_required(VERSION 3.16)
project(bucket-rpg)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_CXX_STANDARD 17)

set(ENV{ROOT_DIR} ${CMAKE_SOURCE_DIR})

if (WIN32 OR MSVC)
  add_compile_definitions(BE_PLATFORM_WINDOWS)
else()
  add_compile_definitions(BE_PLATFORM_LINUX)
endif (WIN32 OR MSVC)

if(BE_PLATFORM_WINDOWS)
  add_compile_definitions(IMGUI_API=__declspec(dllimport))
elseif(BE_PLATFORM_LINUX)
  add_compile_definitions(IMGUI_API)
endif(BE_PLATFORM_WINDOWS)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/sandbox/src/*.c ${CMAKE_SOURCE_DIR}/sandbox/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/sandbox/src/*.h ${CMAKE_SOURCE_DIR}/sandbox/src/*.hpp)

set(TEST_SOURCES
  ${CMAKE_SOURCE_DIR}/engine/tests/main.cpp
  ${CMAKE_SOURCE_DIR}/engine/tests/tests.cpp
)

set(TEST_HEADERS
  ${CMAKE_SOURCE_DIR}/engine/tests/test_math.h
  ${CMAKE_SOURCE_DIR}/engine/tests/core/test_timestep.h
)


if(BE_PLATFORM_WINDOWS)
  add_compile_definitions(IMGUI_API=__declspec(dllimport))
elseif(BE_PLATFORM_LINUX)
  add_compile_definitions(IMGUI_API)
endif(BE_PLATFORM_WINDOWS)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
  add_compile_definitions(BE_DEBUG)
  add_compile_definitions(BE_ENABLE_ASSERTS)
  add_compile_definitions(GLFW_INCLUDE_NONE)
  message("Build type Debug")
elseif(CMAKE_BUILD_TYPE EQUAL "Release")
  add_compile_definitions(BE_RELEASE)
  message("Build type Release")
  set(CMAKE_CXX_FLAGS "-Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif(CMAKE_BUILD_TYPE EQUAL "Dist")
  add_compile_definitions(BE_DIST)
  message("Build type Dist")
  set(CMAKE_CXX_FLAGS "-Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else(CMAKE_BUILD_TYPE EQUAL "Debug")
  add_compile_definitions(BE_DEBUG)
  message("Build type Debug")
endif(CMAKE_BUILD_TYPE EQUAL "Debug")

# Docs
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
  # set input and output files
  set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/doxygen.conf)

  message("Doxygen build started")

  # note the option ALL which allows to build the docs together with the application
  add_custom_target( doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


include_directories(${CMAKE_SOURCE_DIR}/engine/src)
include_directories(${CMAKE_SOURCE_DIR}/engine/vendor)
include_directories(${CMAKE_SOURCE_DIR}/engine/lib)

add_subdirectory(./engine)

link_directories(${CMAKE_SOURCE_DIR}/lib)

include_directories(${CMAKE_BINARY_DIR}/sandbox/src)
include_directories(${CMAKE_BINARY_DIR}/sandbox/assets)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
add_executable(bucket-rpg ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(bucket-rpg PRIVATE engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
add_executable(engine-test ${TEST_HEADERS} ${TEST_SOURCES})

target_include_directories(engine-test PUBLIC
  ${CMAKE_SOURCE_DIR}/engine/src
  ${CMAKE_SOURCE_DIR}/engine/vendor
  ${CMAKE_SOURCE_DIR}/engine/lib)

target_link_libraries(engine-test PRIVATE engine)
enable_testing()
add_test(NAME engine-test-all COMMAND engine-test)
add_test(NAME engine-test1 COMMAND engine-test 1)
