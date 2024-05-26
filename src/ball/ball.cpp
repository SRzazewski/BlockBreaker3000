#include "ball.hpp"
#include <SFML/Graphics.hpp>

ball::ball()
{
    this->ball_shape = std::make_shared<sf::CircleShape>();
    this->ball_shape->setRadius(15.0);
    this->ball_shape->setFillColor(sf::Color(255, 0, 0));
    position_x = 385;
    position_y = 500;
    this->ball_shape->setPosition(position_x, position_y);
}

ball::~ball() {}


void ball::move_ball()
{
    // position_x -= 10;
    this->ball_shape->setPosition(position_x, position_y);
}

std::shared_ptr<sf::CircleShape> ball::get_ball()
{
    return this->ball_shape;
}
