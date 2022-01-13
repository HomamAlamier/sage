cmake_minimum_required(VERSION 3.14)

project(logger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("include")

file(GLOB SRC_DIR "src/*.cpp")
file(GLOB INCLUDE_DIR "include/*.h" "include/*/*.hpp" "include/*/*.h")
add_library(logger ${SRC_DIR} ${INCLUDE_DIR})

if (WIN32)
    set_property(TARGET logger PROPERTY
      MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(WIN32)
