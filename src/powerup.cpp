#include "powerup.hpp"
#include <SFML/Graphics.hpp>

void powerup::set_position(sf::Vector2f new_position)
{
    powerup_shape.setPosition(new_position);
}

sf::Vector2f powerup::get_position() const
{
    return powerup_shape.getPosition();
}

sf::CircleShape powerup::get_powerup() const
{
    return this->powerup_shape;
}

void powerup::set_velocity_vector(sf::Vector2f vector)
{
    velocity_vector = vector;
}

sf::Vector2f powerup::get_velocity_vector() const
{
    return velocity_vector;
}

void powerup::draw(sf::RenderWindow &window)
{
    window.draw(powerup_shape);
}

int powerup::get_points()
{
    return points;
}
