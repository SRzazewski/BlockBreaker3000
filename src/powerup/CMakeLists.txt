add_library(Powerup 
    powerup.cpp)
    
target_link_libraries(Powerup 
    PRIVATE 
        sfml-graphics
        GameObject)

target_include_directories(Powerup 
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}
)