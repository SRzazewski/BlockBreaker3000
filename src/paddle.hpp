#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

const sf::Vector2f paddle_size = sf::Vector2f(120.0f, 20.0f);

class paddle : public moving_object, public rectangle_object
{
public:
    paddle();

    void set_position(sf::Vector2f position) override;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;
    sf::RectangleShape get_paddle() const;
    sf::Vector2f get_size() const override;
    sf::Vector2f get_position() const override;
    sf::Time count_delta_time(sf::Clock &clock);
    void draw(sf::RenderWindow &window) override;
    void reset();


private:
    sf::RectangleShape player_paddle;
    sf::Vector2f velocity_vector;
};

#endif