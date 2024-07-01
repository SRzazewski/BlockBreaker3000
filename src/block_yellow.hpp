#ifndef BLOCK_YELLOW_HPP
#define BLOCK_YELLOW_HPP

#include "block.hpp"
#include <SFML/Graphics.hpp>

class block_yellow : public block
{
public:
    block_yellow(sf::Vector2f start_position);
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::RectangleShape get_block() override;
    int break_obj() override;
    bool is_broken() override;
    void draw(sf::RenderWindow &window) override;

private:
    sf::RectangleShape block_obj;
    int number_hits_to_break;
    int point_for_breaking;
};

#endif