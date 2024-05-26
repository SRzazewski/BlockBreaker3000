#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class ball
{
public:
    ball();
    ~ball();
    void move_ball();
    std::shared_ptr<sf::CircleShape> get_ball();


private:
    std::shared_ptr<sf::CircleShape> ball_shape;
    float position_x;
    float position_y;
};

#endif