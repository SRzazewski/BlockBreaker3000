#! /usr/bin/bash

game_file_execution=build/bin/BlockBreaker3000
game_file_execution_tests=build/bin/BlockBreaker3000_tests

arg="$1"
echo $arg
if [ "$arg" = "test" ]; then
    exe_file=$game_file_execution_tests
else
    exe_file=$game_file_execution
fi

echo "Executed file: $exe_file"

command=./$exe_file

if [ -f $exe_file ]; then
    $command
else
    make_command="make -C build"
    $make_command
    $command
fi
