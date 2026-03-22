cmake_minimum_required(VERSION 3.16)

project(Wink)

set(CMAKE_CXX_STANDARD 20)

include_directories()

aux_source_directory(${CMAKE_SOURCE_DIR}/src WINK_SRC_LIST)
add_executable(wink ${WINK_SRC_LIST})
include_directories(wink ${CMAKE_SOURCE_DIR}/include)

set_target_properties(wink PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)