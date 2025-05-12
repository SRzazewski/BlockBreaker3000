#!/usr/bin/python3

import subprocess
import sys
import os

game_file_execution = "build/bin/BlockBreaker3000"
game_file_execution_tests = "build/bin/BlockBreaker3000_tests"

flags = [
    "--clean", "-C" # clean built files
    ]

argument_list = sys.argv[1:]

if argument_list and "test" == argument_list[0]:
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