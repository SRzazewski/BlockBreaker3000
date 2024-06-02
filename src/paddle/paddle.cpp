#include "paddle.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

paddle::paddle(sf::RenderWindow *const app_window, sf::Clock *const app_clock, float game_area):
    window(app_window),
    clock(app_clock),
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

void paddle::move_paddle_left()
{
    if (player_s_paddle.getPosition().x - 10 < (player_s_paddle.getSize().x/2.0f))
    {
        player_s_paddle.setPosition(sf::Vector2f((player_s_paddle.getSize().x/2.0f), player_s_paddle.getPosition().y));
    }
    else
    {
        player_s_paddle.setPosition(sf::Vector2f(player_s_paddle.getPosition().x - 10, player_s_paddle.getPosition().y));
    }
}

void paddle::move_paddle_right()
{
    if ((player_s_paddle.getPosition().x + 10) > (paddle_area - player_s_paddle.getSize().x/2.0f))
    {
        player_s_paddle.setPosition(sf::Vector2f(paddle_area - player_s_paddle.getSize().x/2.0f, player_s_paddle.getPosition().y));
    }
    else
    {
        player_s_paddle.setPosition(sf::Vector2f(player_s_paddle.getPosition().x + 10, player_s_paddle.getPosition().y));
    }
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

void paddle::display()
{
    window->draw(player_s_paddle);
}
