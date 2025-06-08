#include "powerup.hpp"
#include "move.hpp"
#include <SFML/Graphics.hpp>

powerup::powerup(sf::Vector2f start_position)
{
    move_ptr = std::make_unique<Move_powerup>();
    powerup_shape.setOrigin({powerup_radius, powerup_radius});
    powerup_shape.setFillColor(sf::Color(255, 0, 50));
    powerup_shape.setPosition(start_position);
}

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

void powerup::move(sf::Time time_delta)
{
    move_ptr->move(time_delta, *this);
}

int powerup::get_points()
{
    return points;
}
