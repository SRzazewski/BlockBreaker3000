#ifndef PHYSIC_OF_OBJECT_HPP
#define PHYSIC_OF_OBJECT_HPP

#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

struct game_area
{
    float x_start;
    float x_stop;
    float y_start;
    float y_stop;
};

void move_objects(sf::Clock &clock, paddle &paddle_obj, std::vector<ball> &balls, std::vector<block> &blocks, game_area area, game_states &game_state);

class physic_of_object
{
    public:
    physic_of_object();
    ~physic_of_object();
    

};

#endif