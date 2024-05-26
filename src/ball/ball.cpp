#include "ball.hpp"
#include <SFML/Graphics.hpp>

ball::ball()
{
    this->ball_shape = std::make_shared<sf::CircleShape>();
    this->ball_shape->setRadius(15.0);
    this->ball_shape->setFillColor(sf::Color(255, 0, 0));
    position.x = 385;
    position.y = 500;
    velocity_vector.x = 100.0f;
    velocity_vector.y = 100.0f;
    this->ball_shape->setPosition(position.x, position.y);
}

ball::~ball() {}

void ball::set_position(sf::Vector2f new_position)
{
    position = new_position;
    this->ball_shape->setPosition(position.x, position.y);
}

sf::Vector2f ball::get_position() const
{
    return position;
}

std::shared_ptr<sf::CircleShape> ball::get_ball() const
{
    return this->ball_shape;
}

void ball::set_velocity_vector(sf::Vector2f vector)
{
    velocity_vector = vector;
}

sf::Vector2f ball::get_velocity_vector() const
{
    return velocity_vector;
}
