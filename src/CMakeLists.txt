# Add an executable
add_library(BlockBreaker3000_core STATIC)
add_library(BlockBreaker3000::BlockBreaker3000_core ALIAS BlockBreaker3000_core )

target_sources(BlockBreaker3000_core
    PRIVATE
        ball.cpp
        ball.hpp
        block.hpp
        block.cpp
        game.cpp
        game.hpp
        game_object.hpp
        paddle.cpp
        paddle.hpp
        powerup.cpp
        powerup.hpp
        mode.cpp
        mode.hpp
        common.hpp
        move.cpp
        move.hpp
        # level.cpp
        # level.hpp
    )

target_include_directories(BlockBreaker3000_core 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}
)

# add_executable(SFML_TEST src/main.cpp)
target_link_libraries(BlockBreaker3000_core 
    PUBLIC 
        SFML::Graphics)
        
target_compile_features(BlockBreaker3000_core PUBLIC cxx_std_20)

target_compile_options(BlockBreaker3000_core PUBLIC -Wall -Wextra -Wpedantic)

add_executable(BlockBreaker3000)

target_sources(BlockBreaker3000 PRIVATE BlockBreaker3000.cpp)

target_link_libraries(BlockBreaker3000 PRIVATE BlockBreaker3000_core)

if(WIN32)
    add_custom_command(
        TARGET BlockBreaker3000
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:BlockBreaker3000>
        VERBATIM)
endif()

add_custom_command(
    TARGET BlockBreaker3000 POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_LIST_DIR}/font/arial.ttf" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/font/arial.ttf"
    COMMENT "Copying ${arial.ttf} to build directory"
)