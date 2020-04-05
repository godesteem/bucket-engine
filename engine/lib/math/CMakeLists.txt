cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 17)
project(bucket_math VERSION 0.0.1 DESCRIPTION "This is the bucket engine math module.")

set(MATH_DIR "${CMAKE_SOURCE_DIR}/engine/lib/math")
set(MATH_HEADERS
  ${MATH_DIR}/math.h
  ${MATH_DIR}/matrix.h
  ${MATH_DIR}/vector.h
  )
add_library(bucket_math STATIC
  ${MATH_HEADERS})
SET_TARGET_PROPERTIES(bucket_math PROPERTIES LINKER_LANGUAGE CXX)