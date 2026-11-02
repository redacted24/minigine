#!/bin/bash
set -e
target='minigine'

if [ $# -eq 0 ]; then
    cmake --build build/debug --verbose
    echo "Copying build/debug/main/${target} to project root..."
    cp build/debug/main/${target} .
    echo 'Copied.'

    cp build/debug/compile_commands.json compile_commands.json
    echo 'compile_commands.json created'
    echo "executing ${target}"
    ./${target}
else
    case $1 in
    test)
        cmake --build build/debug --verbose
        cd build/debug/tests && ctest
        ;;

    clean)
        cmake --build build/debug --target clean
        ;;
    *)
        echo 'Unknown Option. Please use with no args, with "debug", or with "clean"'
        ;;
    esac
fi
