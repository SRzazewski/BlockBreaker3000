#include "block.hpp"

block::block(const sf::Vector2f start_position, const int hits_to_break)
{
    block_obj = sf::RectangleShape();
    block_obj.setSize(block_size);
    block_obj.setOrigin(block_size.x/2.0f, block_size.y/2.0f);
    block_obj.setOutlineThickness(block_outline_thickness);
    block_obj.setPosition(start_position);
    number_hits_to_break = block_types[hits_to_break].hits_to_break;
    point_for_breaking = block_types[hits_to_break].points;
    block_obj.setFillColor(block_types[hits_to_break].block_color);
    block_obj.setOutlineColor(block_types[hits_to_break].thickness_color);
}

void block::set_position(sf::Vector2f position) 
{
    block_obj.setPosition(position);
}

sf::Vector2f block::get_position() const
{
    return block_obj.getPosition();
}

sf::RectangleShape block::get_block()
{
    return block_obj;
}

int block::break_obj()
{
    number_hits_to_break--;
    if(number_hits_to_break < 1)
    {
        return point_for_breaking;
    }
    else
    {
        block_obj.setFillColor(block_types[number_hits_to_break].block_color);
        block_obj.setOutlineColor(block_types[number_hits_to_break].thickness_color);
        return 0;
    }
}

bool block::is_broken()
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

void block::draw(sf::RenderWindow &window)
{
    if (!is_broken())
    {
        window.draw(block_obj);
    }
}
