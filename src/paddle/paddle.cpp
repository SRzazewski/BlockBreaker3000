#include "paddle.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

paddle::paddle()
{
    this->player_s_paddle = std::make_shared<sf::RectangleShape>();
    this->player_s_paddle->setSize(sf::Vector2f(120.f, 20.f));
    this->player_s_paddle->setFillColor(sf::Color(100, 250, 50));
    position_x = 340;
    position_y = 550;
    this->player_s_paddle->setPosition(position_x, position_y);
}

paddle::~paddle() {}

void paddle::move_paddle_left()
{
    position_x -= 10;
    if (position_x < 0)
    {
        position_x = 0;
    }
    this->player_s_paddle->setPosition(position_x, position_y);
}

void paddle::move_paddle_right()
{
    position_x += 10;
    if (position_x > 800.0f - 120.f)
    {
        position_x = 800.0f - 120.f;
    }
    this->player_s_paddle->setPosition(position_x, position_y);
}

std::shared_ptr<sf::RectangleShape> paddle::get_paddle()
{
    return this->player_s_paddle;
}
