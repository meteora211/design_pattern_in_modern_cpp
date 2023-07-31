cmake_minimum_required(VERSION 3.12)
project(design_pattern)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(MATMUL_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(chpt1_intro)
