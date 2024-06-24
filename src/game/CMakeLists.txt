add_library(Game 
    game.cpp)

# add_library(BlockBreaker3000::Paddle ALIAS Paddle)
target_link_libraries(Game 
    PRIVATE 
        sfml-graphics
        GameObject
        Paddle
        Ball
        Block)

target_include_directories(Game 
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}
)