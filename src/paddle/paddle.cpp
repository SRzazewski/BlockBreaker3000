#include "paddle.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

paddle::paddle(float const game_area):
    paddle_area(game_area)
{
    float size_x = 120.f;
    float size_y = 20.f;
    player_s_paddle = sf::RectangleShape();
    player_s_paddle.setSize(sf::Vector2f(size_x, size_y));
    player_s_paddle.setOrigin(size_x/2.0f, size_y/2.0f);
    player_s_paddle.setFillColor(sf::Color(100, 250, 50));
    player_s_paddle.setPosition(sf::Vector2f(400.0f, 560.0f));
}

void paddle::set_position(sf::Vector2f position) 
{
    player_s_paddle.setPosition(position);
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
    return player_s_paddle;
}

sf::Vector2f paddle::get_position() const
{
    return player_s_paddle.getPosition();
}

sf::Time paddle::count_delta_time(sf::Clock &clock)
{
    sf::Time current_time = clock.getElapsedTime();
    sf::Time delta = current_time - previus_time;
    previus_time = current_time;
    return delta;
}

void paddle::draw(sf::RenderWindow &window)
{
    window.draw(player_s_paddle);
}

void paddle::reset()
{
    velocity_vector.x = 0.0f;
    velocity_vector.y = 0.0f;
    player_s_paddle.setPosition(sf::Vector2f(400.0f, 560.0f));
    previus_time = sf::seconds(0.0f);
}
