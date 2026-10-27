#!/bin/bash
set -e
target='minigine'

if [ $# -eq 0 ]; then
    cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -G Ninja
    cmake --build build/debug --verbose
    echo "Copying build/debug/main/${target} to project root..."
    cp build/debug/main/${target} .
    echo 'Copied.'

    cp build/debug/compile_commands.json compile_commands.json
    echo 'compile_commands.json created'
else
    case $1 in
    release)
        cmake -S . -B build/release -G Ninja
        cmake --build build/release --verbose

        echo "Copying build/release/main/${target} to project root..."
        cp build/release/main/${target} .
        echo 'Copied.'

        ln -sf build/release/compile_commands.json compile_commands.json
        echo 'compile_commands.json created'
        ;;

    clean)
        rm -rf build
        rm -rf ./*.out
        ;;
    *)
        echo 'Unknown Option. Please use with no args, with "debug", or with "clean"'
        ;;
    esac
fi
