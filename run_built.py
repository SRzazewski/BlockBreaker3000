#!/usr/bin/python3

import subprocess
import sys
import os

game_file_execution = "build/bin/BlockBreaker3000"
game_file_execution_tests = "build/bin/BlockBreaker3000_tests"

flags = [
    ["test",     "",     False],
    ["--clean",  "-C",   False] # clean files before build
    ]

argument_list = sys.argv[1:]

if argument_list:
    for flag in argument_list:
        command_found = False
        for j in flags:
            if j[0] == flag or j[1] == flag:
                j[2] = True
                command_found = True
                break
        if not command_found:
            sys.exit(print("Flag ", flag," unrecognized!"))

if flags[0][2]:
    exe_file = game_file_execution_tests
else:
    exe_file = game_file_execution

print("Executed file: ", exe_file)

execution_command = "./" + exe_file

if True == flags[1][2]:
    subprocess.run(["make -C build clean"], shell = True, executable="/usr/bin/bash")

if os.path.exists(exe_file):
    subprocess.run([execution_command])
else:
    subprocess.run(["cmake -S . -B build"], shell = True, executable="/usr/bin/bash")
    subprocess.run(["make -C build"], shell = True, executable="/usr/bin/bash")
    subprocess.run([execution_command])