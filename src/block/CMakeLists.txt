add_library(Block
    block.cpp)

target_link_libraries(Block
    PRIVATE 
        sfml-graphics
        GameObject
)

target_include_directories(Block 
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}
)