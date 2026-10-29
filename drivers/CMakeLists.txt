add_library(drivers)
target_sources(drivers
    PRIVATE
        shader.cc
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ./
        FILES
            shader.h
)
target_link_libraries(drivers
    PUBLIC
        thirdparty
)
