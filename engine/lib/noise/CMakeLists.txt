cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 17)
project(bucket_noise VERSION 0.0.1 DESCRIPTION "This is the bucket engine noise module.")

set(NOISE_DIR "${CMAKE_SOURCE_DIR}/engine/lib/noise")

set(NOISE_HEADERS
  ${NOISE_DIR}/noise.h
  )

set(NOISE_SOURCES
  ${NOISE_DIR}/noise.cpp
  )

add_library(bucket_noise STATIC
  ${NOISE_HEADERS}
  ${NOISE_SOURCES})

SET_TARGET_PROPERTIES(bucket_noise PROPERTIES LINKER_LANGUAGE CXX)