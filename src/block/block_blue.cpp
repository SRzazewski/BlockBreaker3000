#include "block_blue.hpp"
#include <iostream>

block_blue::block_blue(sf::Vector2f start_position)
{
    float size_x = 90.f;
    float size_y = 20.f;
    broken = false;
    block_obj = sf::RectangleShape();
    block_obj.setSize(sf::Vector2f(size_x, size_y));
    block_obj.setOrigin(size_x/2.0f, size_y/2.0f);
    block_obj.setOutlineThickness(5.0f);
    block_obj.setPosition(start_position);
    block_obj.setFillColor(sf::Color(0, 0, 255));
    block_obj.setOutlineColor(sf::Color(100, 150, 255));
    point_for_breaking = 50;
}

void block_blue::set_position(sf::Vector2f position) 
{
    block_obj.setPosition(position);
}

sf::Vector2f block_blue::get_position() const
{
    return block_obj.getPosition();
}

sf::RectangleShape block_blue::get_block()
{
    return block_obj;
}

int block_blue::break_obj()
{
    broken = true;
    return point_for_breaking;
}

bool block_blue::is_broken()
{
    return broken;
}

void block_blue::draw(sf::RenderWindow &window)
{
    if (!broken)
    {
        window.draw(block_obj);
    }
}
