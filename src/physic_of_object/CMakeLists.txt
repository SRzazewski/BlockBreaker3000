add_library(PhysicOfObject
    physic_of_object.cpp)
    
target_link_libraries(PhysicOfObject 
    PRIVATE 
        sfml-graphics
        Paddle
        Ball
        Block
        GameObject)

target_include_directories(PhysicOfObject 
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}
)