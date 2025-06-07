#ifndef BALL_HPP
#define BALL_HPP

#include "game_object.hpp"
#include "move.hpp"
#include <SFML/Graphics.hpp>

class game;

constexpr float ball_radius = 10.0f;

class ball : public moving_object
{
public:
    ball(game *game_inst, 
        sf::Vector2f start_position = sf::Vector2f(385.0f, 500.0f));
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::CircleShape get_ball() const;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;
    void draw(sf::RenderWindow &window) override;
    void move(sf::Time time_delta) override;


private:
    std::unique_ptr<Move_ball> move_ptr;
    sf::CircleShape ball_shape  = sf::CircleShape(ball_radius);
    sf::Vector2f velocity_vector = sf::Vector2f(250.f, 250.f);
    sf::Vector2f position;
};

#endif