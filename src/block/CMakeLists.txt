add_library(Block
    block_blue.cpp
    block_orange.cpp)

target_link_libraries(Block
    PRIVATE 
        sfml-graphics
        GameObject
)

target_include_directories(Block 
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}
)