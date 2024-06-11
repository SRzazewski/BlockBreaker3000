#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class paddle : public moving_object
{
public:
    paddle(float game_area);

    void set_position(sf::Vector2f position) override;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;

    sf::RectangleShape get_paddle() const;
    sf::Vector2f get_position() const override;
    sf::Time count_delta_time(sf::Clock &clock);
    void draw() override; //TODO remove after update moving_object
    void draw(sf::RenderWindow &window);
    void reset() override;


private:
    float paddle_area;
    sf::RectangleShape player_s_paddle;
    sf::Vector2f velocity_vector;
    sf::Time previus_time;
};

#endif