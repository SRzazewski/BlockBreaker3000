#ifndef PHYSIC_OF_OBJECT_HPP
#define PHYSIC_OF_OBJECT_HPP

#include "paddle.hpp"
#include "ball.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

struct game_area
{
    float x_start;
    float x_stop;
    float y_start;
    float y_stop;
};

void move_objects(paddle paddle_obj, std::vector<ball> &balls, game_area area);

class physic_of_object
{
    public:
    physic_of_object();
    ~physic_of_object();
    

};

#endif