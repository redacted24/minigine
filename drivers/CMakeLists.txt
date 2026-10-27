add_library(drivers)
target_sources(drivers
    PRIVATE
        character.cc
        shader.cc
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ./
        FILES
            character.h
            shader.h
)
target_link_libraries(drivers
    PUBLIC
        thirdparty
)
