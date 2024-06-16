#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>

class block : public game_object
{
public:
    block(sf::Vector2f start_position);
    ~block();
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::RectangleShape get_block();
    void break_obj();
    bool is_broken();
    static int get_number_of_blocks();
    static void decrement_number_of_blocks();
    static void set_number_of_blocks(int number);
    void draw(sf::RenderWindow &window) override;
    void reset() override;

private:
    sf::RectangleShape block_obj;
    static int number_of_blocks;
    bool broken;
};

#endif