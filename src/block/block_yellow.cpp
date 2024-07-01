#include "block_yellow.hpp"
#include <iostream>

block_yellow::block_yellow(sf::Vector2f start_position)
{
    block_obj = sf::RectangleShape();
    block_obj.setSize(block_size);
    block_obj.setOrigin(block_size.x/2.0f, block_size.y/2.0f);
    block_obj.setOutlineThickness(block_outline_thickness);
    block_obj.setPosition(start_position);
    block_obj.setFillColor(sf::Color(238, 230, 0));
    block_obj.setOutlineColor(sf::Color(238, 255, 27));
    number_hits_to_break = 2;
    point_for_breaking = 100;
}

void block_yellow::set_position(sf::Vector2f position) 
{
    block_obj.setPosition(position);
}

sf::Vector2f block_yellow::get_position() const
{
    return block_obj.getPosition();
}

sf::RectangleShape block_yellow::get_block()
{
    return block_obj;
}

int block_yellow::break_obj()
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

bool block_yellow::is_broken()
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

void block_yellow::draw(sf::RenderWindow &window)
{
    if (!is_broken())
    {
        window.draw(block_obj);
    }
}
