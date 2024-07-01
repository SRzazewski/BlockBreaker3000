#include "block_brown.hpp"
#include <iostream>

block_brown::block_brown(sf::Vector2f start_position)
{
    block_obj = sf::RectangleShape();
    block_obj.setSize(block_size);
    block_obj.setOrigin(block_size.x/2.0f, block_size.y/2.0f);
    block_obj.setOutlineThickness(block_outline_thickness);
    block_obj.setPosition(start_position);
    block_obj.setFillColor(sf::Color(165, 42, 42));
    block_obj.setOutlineColor(sf::Color(205, 133, 63));
    number_hits_to_break = 4;
    point_for_breaking = 300;
}

void block_brown::set_position(sf::Vector2f position) 
{
    block_obj.setPosition(position);
}

sf::Vector2f block_brown::get_position() const
{
    return block_obj.getPosition();
}

sf::RectangleShape block_brown::get_block()
{
    return block_obj;
}

int block_brown::break_obj()
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

bool block_brown::is_broken()
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

void block_brown::draw(sf::RenderWindow &window)
{
    if (!is_broken())
    {
        window.draw(block_obj);
    }
}
