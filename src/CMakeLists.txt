# Add an executable
add_executable(BlockBreaker3000 
    BlockBreaker3000.cpp)


# add_executable(SFML_TEST src/main.cpp)
target_link_libraries(BlockBreaker3000 
    PRIVATE 
        sfml-graphics
        Paddle
        Ball
        PhysicOfObject
        GameObject)
        
target_compile_features(BlockBreaker3000 PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET BlockBreaker3000
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:BlockBreaker3000>
        VERBATIM)
endif()

add_subdirectory(interface_classes)
add_subdirectory(paddle)
add_subdirectory(ball)
add_subdirectory(physic_of_object)