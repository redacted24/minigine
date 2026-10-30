cmake_minimum_required(VERSION 3.23)
cmake_policy(SET CMP0135 NEW)

project(minigine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "_debug")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy"; "--warnings-as-errors=*")

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(thirdparty)
add_subdirectory(core)
add_subdirectory(drivers)
add_subdirectory(tests)
add_subdirectory(main)
