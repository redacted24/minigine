# core - engine logic
add_library(core)
target_sources(core
    PRIVATE
        camera.cc
        node.cc
        rendering_engine.cc
        cube.cc
        perlin_noise.cc
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ./
        FILES
            camera.h
            node.h
            rendering_engine.h
            cube.h
            perlin_noise.h
)
target_link_libraries(core
    PUBLIC
        thirdparty
)
