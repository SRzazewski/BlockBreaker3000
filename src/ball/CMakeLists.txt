add_library(Ball 
    ball.cpp)
    
target_link_libraries(Ball 
    PRIVATE 
        sfml-graphics)

target_include_directories(Ball 
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}
)