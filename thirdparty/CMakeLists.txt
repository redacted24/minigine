# thirdparty cmake
find_package(SDL3 REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)

set(SPDLOG_USE_EXTERNAL_FMT OFF)
add_subdirectory(spdlog)

add_library(thirdparty)
target_include_directories(thirdparty
    PUBLIC
        ./
)

target_sources(thirdparty
    PRIVATE
        glad/glad.c
        stb_image/stb_image.cc
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ./
        FILES
            glad/glad.h
            stb_image/stb_image.h
            KHR/khrplatform.h
)

# Thirdparty vendors
target_link_libraries(thirdparty
    PUBLIC
        GL
        X11
        pthread
        Xrandr
        Xi
        dl
        SDL3::SDL3
        spdlog::spdlog
        Freetype::Freetype
)
