cmake_minimum_required(VERSION 3.12)
project(design_pattern)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include(FetchContent)
FetchContent_Declare(
  di
  GIT_REPOSITORY https://github.com/boost-ext/di
  GIT_TAG v1.3.0 
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(di)

add_subdirectory(chpt1_intro)
add_subdirectory(chpt2_builder)
add_subdirectory(chpt3_factory)
add_subdirectory(chpt4_prototype)
add_subdirectory(chpt5_singleton)
