#include "powerup.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

powerup::powerup(sf::Vector2f start_position)
{
    float radius = 10.0f;
    powerup_shape = sf::CircleShape(radius, 3);
    powerup_shape.setRadius(radius);
    powerup_shape.setOrigin(radius, radius);
    powerup_shape.setFillColor(sf::Color(255, 0, 50));
    velocity_vector.x = 0.0f;
    velocity_vector.y = 100.0f;
    powerup_shape.setPosition(start_position);
    points = 50;
}

powerup::~powerup() {}

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
