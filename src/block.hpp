#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>


const sf::Vector2f block_size = sf::Vector2f(90.0f, 20.0f);
constexpr float block_outline_thickness = 5.0f;

class block : public game_object
{
public:
    virtual sf::RectangleShape get_block() = 0;
    virtual int break_obj() = 0;
    virtual bool is_broken() = 0;

protected:
    sf::RectangleShape block_obj;
    int number_hits_to_break;
    int point_for_breaking;
};

#endif