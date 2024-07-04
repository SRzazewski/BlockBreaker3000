#include "paddle.hpp"
#include <SFML/Graphics.hpp>

paddle::paddle()
{
    float size_x = 120.f;
    float size_y = 20.f;
    player_paddle = sf::RectangleShape();
    player_paddle.setSize(sf::Vector2f(size_x, size_y));
    player_paddle.setOrigin(size_x/2.0f, size_y/2.0f);
    player_paddle.setFillColor(sf::Color(100, 250, 50));
    player_paddle.setPosition(sf::Vector2f(400.0f, 560.0f));
}

void paddle::set_position(sf::Vector2f position) 
{
    player_paddle.setPosition(position);
}

void paddle::set_velocity_vector(sf::Vector2f vector) 
{
    velocity_vector = vector;
}

sf::Vector2f paddle::get_velocity_vector() const 
{
    return velocity_vector;
}

sf::RectangleShape paddle::get_paddle() const
{
    return player_paddle;
}

sf::Vector2f paddle::get_position() const
{
    return player_paddle.getPosition();
}

void paddle::draw(sf::RenderWindow &window)
{
    window.draw(player_paddle);
}

void paddle::reset()
{
    velocity_vector.x = 0.0f;
    velocity_vector.y = 0.0f;
    player_paddle.setPosition(sf::Vector2f(400.0f, 560.0f));
}
