#ifndef BALL_HPP
#define BALL_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>

constexpr float ball_radius = 10.0f;

class ball : public moving_object
{
public:
    ball(sf::Vector2f start_position = sf::Vector2f(385.0f, 500.0f))
    {
        ball_shape.setOrigin({ball_radius, ball_radius});
        ball_shape.setFillColor(sf::Color(255, 0, 0));
        ball_shape.setPosition(start_position);
    }
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::CircleShape get_ball() const;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;
    void draw(sf::RenderWindow &window) override;


private:
    sf::CircleShape ball_shape  = sf::CircleShape(ball_radius);
    sf::Vector2f velocity_vector = sf::Vector2f(250.f, 250.f);
    sf::Vector2f position;
};

#endif