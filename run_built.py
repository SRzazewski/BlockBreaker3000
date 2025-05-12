#!/usr/bin/python3

import subprocess
import sys
import os

game_file_execution = "build/bin/BlockBreaker3000"
game_file_execution_tests = "build/bin/BlockBreaker3000_tests"

argument_list = sys.argv[1:]

if argument_list:
    exe_file = game_file_execution_tests
else:
    exe_file = game_file_execution

print("Executed file: ", exe_file)

execution_command = "./" + exe_file

if os.path.exists(exe_file):
    subprocess.run([execution_command])
else:
    subprocess.run(["cmake -S . -B build"])
    subprocess.run(["make -C build"])
    subprocess.run([execution_command])