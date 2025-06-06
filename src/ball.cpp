#include "ball.hpp"
#include <SFML/Graphics.hpp>

void ball::set_position(sf::Vector2f new_position)
{
    ball_shape.setPosition(new_position);
}

sf::Vector2f ball::get_position() const
{
    return ball_shape.getPosition();
}

sf::CircleShape ball::get_ball() const
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

void ball::draw(sf::RenderWindow &window)
{
    window.draw(ball_shape);
}
void ball::move(sf::Time time_delta)
{
    
}
