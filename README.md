# BlockBreaker3000

## External libraries
This project uses SFML(Simple and Fast Multimedia Library). More information https://www.sfml-dev.org/

## How to build the project
First the following software is required:
- Compiler: GNU g++-12.2.0(other version of this compiler is not tested)
- CMake: version 3.25 or newer
### For Linux(tested on Debian 12)
1. Download the project
2. Open Terminal and enter to the project folder BlockBreaker3000
3. Run the following command for generate makefiles
```
cmake -B . -S name_of_folder_for_build_files
```
4. Enter to the _name_of_folder_for_build_files_
```
cd name_of_folder_for_build_files
```
5. Build the project
```
make
```
6. Run the executable file
- Game
```
./bin/BlockBreaker3000
```
- Unit tests
```
./bin/BlockBreaker3000_tests
```



### For Windows
1. Download the project
2. Open Terminal and enter to the project folder BlockBreaker3000
3. Run the following command for generate makefiles
```
cmake -B . -S name_of_folder_for_build_files
```
4. Enter to the _name_of_folder_for_build_files_
```
cd name_of_folder_for_build_files
```
5. Build the project
```
make
```
6. Run the executable file
- Game
```
./bin/BlockBreaker3000
```
- Unit tests
```
./bin/BlockBreaker3000_tests
```