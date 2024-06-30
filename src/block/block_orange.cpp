#include "block_orange.hpp"
#include <iostream>

block_orange::block_orange(sf::Vector2f start_position)
{
    float size_x = 90.f;
    float size_y = 20.f;
    broken = false;
    block_obj = sf::RectangleShape();
    block_obj.setSize(sf::Vector2f(size_x, size_y));
    block_obj.setOrigin(size_x/2.0f, size_y/2.0f);
    block_obj.setOutlineThickness(5.0f);
    block_obj.setPosition(start_position);
    block_obj.setFillColor(sf::Color(219, 142, 0));
    block_obj.setOutlineColor(sf::Color(255, 165, 0));
    point_for_breaking = 100;
}

void block_orange::set_position(sf::Vector2f position) 
{
    block_obj.setPosition(position);
}

sf::Vector2f block_orange::get_position() const
{
    return block_obj.getPosition();
}

sf::RectangleShape block_orange::get_block()
{
    return block_obj;
}

int block_orange::break_obj()
{
    broken = true;
    return point_for_breaking;
}

bool block_orange::is_broken()
{
    return broken;
}

void block_orange::draw(sf::RenderWindow &window)
{
    if (!broken)
    {
        window.draw(block_obj);
    }
}
