#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>

class block : public game_object
{
public:
    block(sf::Vector2f start_position = sf::Vector2f(0.0f, 0.0f)) {};
    ~block() {};
    virtual sf::RectangleShape get_block() = 0;
    virtual int break_obj() = 0;
    virtual bool is_broken() = 0;

protected:
    sf::RectangleShape block_obj;
    bool broken;
    int point_for_breaking;
};

#endif