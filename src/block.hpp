#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <array>

struct block_type
{
    const int hits_to_break;
    const int points_for_breaking;
    const sf::Color fill_color;
    const sf::Color outline_color;
};

const std::array<block_type, 5> block_types =
{{  
    {0, 0, sf::Color(0, 0, 0), sf::Color(0, 0, 0)},
    {1, 50, sf::Color(0, 0, 255), sf::Color(100, 150, 255)},
    {2, 100, sf::Color(238, 230, 0), sf::Color(238, 255, 27)},
    {3, 200, sf::Color(219, 142, 0), sf::Color(255, 165, 0)},
    {4, 300, sf::Color(165, 42, 42), sf::Color(205, 133, 63)}
}};

constexpr int block_blue = 1;
constexpr int block_yellow = 2;
constexpr int block_orange = 3;
constexpr int block_brown = 4;

const sf::Vector2f block_size = sf::Vector2f(90.0f, 20.0f);
constexpr float block_outline_thickness = 5.0f;

class block : public game_object
{
public:
    block(const sf::Vector2f start_position, const int hits_to_break);
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    void draw(sf::RenderWindow &window) override;
    sf::RectangleShape get_block() const;
    int hit_obj();
    bool is_broken();
    void update_color();

protected:
    sf::RectangleShape block_obj;
    int hits_to_break;
    int points_for_breaking;
};

#endif