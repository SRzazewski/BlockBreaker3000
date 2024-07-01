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
    visible = true;
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

sf::Time powerup::count_delta_time(sf::Clock &clock)
{
    sf::Time current_time = clock.getElapsedTime();
    sf::Time delta = current_time - previus_time;
    previus_time = current_time;
    return delta;
}

void powerup::draw(sf::RenderWindow &window)
{
    if(visible)
    {
        window.draw(powerup_shape);
    }
}

void powerup::set_visible(bool is_visable)
{
    visible = is_visable;
}

bool powerup::get_visible()
{
    return visible;
}

int powerup::get_points()
{
    return points;
}
