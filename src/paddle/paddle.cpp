#include "paddle.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

paddle::paddle()
{
    this->player_s_paddle = std::make_shared<sf::RectangleShape>();
    this->player_s_paddle->setSize(sf::Vector2f(120.f, 20.f));
    this->player_s_paddle->setFillColor(sf::Color(100, 250, 50));
    position.x = 340;
    position.y = 550;
    this->player_s_paddle->setPosition(position);
}

paddle::~paddle() {}

void paddle::move_paddle_left()
{
    position.x -= 10;
    if (position.x < 0)
    {
        position.x = 0;
    }
    this->player_s_paddle->setPosition(position);
}

void paddle::move_paddle_right()
{
    position.x += 10;
    if (position.x > 800.0f - 120.f)
    {
        position.x = 800.0f - 120.f;
    }
    this->player_s_paddle->setPosition(position);
}

std::shared_ptr<sf::RectangleShape> paddle::get_paddle() const
{
    return this->player_s_paddle;
}

sf::Vector2f paddle::get_position() const
{
    return position;
}
