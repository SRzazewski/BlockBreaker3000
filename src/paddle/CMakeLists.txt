add_library(Paddle 
    paddle.cpp)

# add_library(BlockBreaker3000::Paddle ALIAS Paddle)
target_link_libraries(Paddle 
    PRIVATE 
        sfml-graphics
        GameObject)

target_include_directories(Paddle 
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}
)