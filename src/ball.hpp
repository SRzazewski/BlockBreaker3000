#ifndef BALL_HPP
#define BALL_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class ball : public moving_object
{
public:
    ball(sf::Vector2f start_position = sf::Vector2f(385.0f, 500.0f));
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::CircleShape get_ball() const;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;
    void draw(sf::RenderWindow &window) override;


private:
    sf::CircleShape ball_shape;
    sf::Vector2f velocity_vector;
    sf::Vector2f position;
    sf::Time previus_time;
};

#endif