cmake_minimum_required(VERSION 3.15)

project(sage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB INCLUDE_FILES "include" "*/include")
include_directories(${INCLUDE_FILES})

if(WIN32)
    file(GLOB WIN_DEPS_INCLUDE "deps/*/include")
    file(GLOB WIN_DEPS_LIB "deps/*/lib")
    message(WARNING ${WIN_DEPS_INCLUDE})
    include_directories(${WIN_DEPS_INCLUDE})
    link_directories(${WIN_DEPS_LIB})
endif(WIN32)

add_subdirectory("W3D_Reader")
add_subdirectory("3d_engine")
add_subdirectory("logger")

add_executable(test_w3d_reader "tests/w3d_reader.cpp")
target_link_libraries(test_w3d_reader w3d_reader)

add_executable(test_3d_engine "tests/3d_engine.cpp")
target_link_libraries(test_3d_engine 3d_engine w3d_reader)

if (WIN32)
    set_property(TARGET test_w3d_reader PROPERTY
      MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set_property(TARGET test_3d_engine PROPERTY
      MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(WIN32)

add_custom_command(TARGET test_3d_engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/tests/data/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders)
