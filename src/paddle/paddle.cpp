#include "paddle.hpp"
#include <SFML/Graphics.hpp>

paddle::paddle()
{
    this->player_s_paddle = new sf::RectangleShape;
    this->player_s_paddle->setSize(sf::Vector2f(120.f, 20.f));
    this->player_s_paddle->setFillColor(sf::Color(100, 250, 50));
    position_x = 340;
    position_y = 550;
    this->player_s_paddle->setPosition(position_x, position_y);
}

paddle::~paddle()
{
    delete player_s_paddle;
}

void paddle::move_paddle_left()
{
    position_x -= 10;
    this->player_s_paddle->setPosition(position_x, position_y);
}

void paddle::move_paddle_right()
{
    position_x += 10;
    this->player_s_paddle->setPosition(position_x, position_y);
}

sf::RectangleShape *paddle::get_paddle()
{
    return this->player_s_paddle;
}
