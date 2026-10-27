cmake_minimum_required(VERSION 3.23)

project(perlin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "_debug")

find_package(SDL3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(glm REQUIRED)

add_executable(main.out)

target_sources(main.out
    PRIVATE
        src/main.cc
        src/shader.cc
        src/stb.cc
        src/camera.cc
        src/node.cc
        src/rendering_engine.cc
        src/cube.cc

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            src
        FILES
            src/shader.h
            src/main.h
            src/camera.h
            src/node.h
            src/rendering_engine.h
            src/cube.h
)

add_library(glad)

target_sources(glad
    PRIVATE
        thirdparty/glad/glad.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            thirdparty
        FILES
            thirdparty/glad/glad.h
            thirdparty/KHR/khrplatform.h
)

target_link_libraries(main.out
    PRIVATE
        GL
        X11
        pthread
        Xrandr
        Xi
        dl
        SDL3
        spdlog::spdlog
        glad
)

