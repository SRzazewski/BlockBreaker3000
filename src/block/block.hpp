#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>

class block : public game_object
{
public:
    block(sf::RenderWindow *const app_window, sf::Vector2f start_position);
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::RectangleShape get_block();
    void break_obj();
    bool is_broken();
    void display() override;

private:
    sf::RenderWindow *const window;
    sf::RectangleShape block_obj;
    bool broken;
};

#endif