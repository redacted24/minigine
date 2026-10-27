# main - initialization loop
add_executable(minigine)
target_link_libraries(minigine
    PRIVATE
        core
        drivers
        # tests
        thirdparty
)
target_sources(minigine
    PRIVATE
        main.cc
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ./
        FILES
            main.h
)

