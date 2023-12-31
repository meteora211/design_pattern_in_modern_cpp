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
add_subdirectory(chpt6_adapter)
add_subdirectory(chpt7_bridge)
add_subdirectory(chpt8_composite)
add_subdirectory(chpt9_decorator)
add_subdirectory(chpt10_facade)
add_subdirectory(chpt11_flyweight)
add_subdirectory(chpt12_proxy)
add_subdirectory(chpt13_chain_of_responsibility)
add_subdirectory(chpt14_command)
add_subdirectory(chpt15_interpreter)
add_subdirectory(chpt16_iterator)
add_subdirectory(chpt17_mediator)
add_subdirectory(chpt18_memento)
add_subdirectory(chpt19_null_object)
add_subdirectory(chpt20_observer)
add_subdirectory(chpt21_state)
add_subdirectory(chpt22_strategy)
add_subdirectory(chpt23_template_method)
add_subdirectory(chpt24_visitor)
