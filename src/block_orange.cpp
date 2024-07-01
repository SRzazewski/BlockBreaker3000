#include "block_orange.hpp"
#include <iostream>

block_orange::block_orange(sf::Vector2f start_position)
{
    block_obj = sf::RectangleShape();
    block_obj.setSize(block_size);
    block_obj.setOrigin(block_size.x/2.0f, block_size.y/2.0f);
    block_obj.setOutlineThickness(block_outline_thickness);
    block_obj.setPosition(start_position);
    block_obj.setFillColor(sf::Color(219, 142, 0));
    block_obj.setOutlineColor(sf::Color(255, 165, 0));
    number_hits_to_break = 3;
    point_for_breaking = 200;
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
    number_hits_to_break--;
    if(number_hits_to_break < 1)
    {
        return point_for_breaking;
    }
    else
    {
        return 0;
    }
}

bool block_orange::is_broken()
{
    if(number_hits_to_break < 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void block_orange::draw(sf::RenderWindow &window)
{
    if (!is_broken())
    {
        window.draw(block_obj);
    }
}
