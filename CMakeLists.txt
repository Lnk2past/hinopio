cmake_minimum_required(VERSION 3.18.4)

project (hinopio)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(fmt CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(GLFW3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_compile_options(-std=c++20)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

export(TARGETS hinopio FILE "${CMAKE_BINARY_DIR}/hinopioTargets.cmake")
