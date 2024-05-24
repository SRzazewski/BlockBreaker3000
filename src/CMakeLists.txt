# Add an executable
add_executable(ARKANOID3000 
    main.cpp)


# add_executable(SFML_TEST src/main.cpp)
target_link_libraries(ARKANOID3000 PRIVATE sfml-graphics)
target_compile_features(ARKANOID3000 PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET ARKANOID3000
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:ARKANOID3000>
        VERBATIM)
endif()