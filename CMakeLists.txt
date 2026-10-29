cmake_minimum_required(VERSION 3.23)

project(minigine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "_debug")

add_subdirectory(thirdparty)
add_subdirectory(core)
add_subdirectory(drivers)
# add_subdirectory(tests)
add_subdirectory(main)
# add_subdirectory(examples)
