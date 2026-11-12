#!/bin/bash
set -e
target='minigine'

if [ $# -eq 0 ]; then
    cmake --build build/release --verbose
    echo "Copying build/release/main/${target} to project root..."
    cp build/release/main/${target} .
    echo 'Copied.'

    cp build/release/compile_commands.json compile_commands.json
    echo 'compile_commands.json created'
    echo "executing ${target}"
    ./${target}
else
    case $1 in
    test)
        cd build/release/tests && ctest --output-on-failure
        ;;

    debug)
        cmake --build build/debug --verbose
        cd build/debug/tests && ctest --output-on-failure
        ;;

    config)
        cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -G Ninja
        cmake -S . -B build/release -G Ninja
        ;;

    clean)
        cmake --build build/debug --target clean
        cmake --build build/release --target clean
        ;;
    *)
        echo 'Unknown Option. Please use with no args, with "debug", or with "clean"'
        ;;
    esac
fi
