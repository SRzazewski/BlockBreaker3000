#!/usr/bin/python3

import subprocess
import sys
import os

game_file_execution = "build/bin/BlockBreaker3000"
game_file_execution_tests = "build/bin/BlockBreaker3000_tests"

flags_const = {
    "value" : 0,
    "flag" : 1
}

flags_dictionary = {
    "test" : 0,
    "clean" : 1,
    "build" : 2,
    "help" : 3
}

flags = [
    [False, ("--test", "-T", "Run unit tests")],
    [False, ("--clean", "-C", "Clean all build files")],
    [False, ("--build", "-B", "Build project")],
    [False, ("--help", "-H", "Show commands")]
]

def display_help():
    print("BlockBreak3000 - build script.")
    print("Flags:")
    for flag in flags:
        print(" ", flag[flags_const.get("flag")][0],",",
            flag[flags_const.get("flag")][1], " - ",
            flag[flags_const.get("flag")][2])
    print("\n")

argument_list = sys.argv[1:]

if argument_list:
    for arg in argument_list:
        command_found = False
        for flag in flags:
            if flag[flags_const.get("flag")][0] == arg \
                    or flag[flags_const.get("flag")][1] == arg:
                flag[flags_const.get("value")] = True
                command_found = True
                break
        if not command_found:
            sys.exit(print("Argument \"", arg,"\" unrecognized!"))

if True == flags[flags_dictionary.get("help")][flags_const.get("value")]:
    sys.exit(display_help())

if True == flags[flags_dictionary.get("build")][flags_const.get("value")]:
    if True == flags[flags_dictionary.get("clean")][flags_const.get("value")]:
        subprocess.run(["make -C build clean"], shell = True, executable="/usr/bin/bash")
    subprocess.run(["cmake -S . -B build"], shell = True, executable="/usr/bin/bash")
    subprocess.run(["make -C build"], shell = True, executable="/usr/bin/bash")
    sys.exit()

if True == flags[flags_dictionary.get("clean")][flags_const.get("value")]:
    subprocess.run(["make -C build clean"], shell = True, executable="/usr/bin/bash")
    sys.exit()

if flags[flags_dictionary.get("test")][flags_const.get("value")]:
    exe_file = game_file_execution_tests
else:
    exe_file = game_file_execution

print("Executed file: ", exe_file)

execution_command = "./" + exe_file

if os.path.exists(exe_file):
    subprocess.run([execution_command])
else:
    subprocess.run(["cmake -S . -B build"], shell = True, executable="/usr/bin/bash")
    subprocess.run(["make -C build"], shell = True, executable="/usr/bin/bash")
    subprocess.run([execution_command])