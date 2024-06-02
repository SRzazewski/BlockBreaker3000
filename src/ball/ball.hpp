#ifndef BALL_HPP
#define BALL_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class ball : public moving_object
{
public:
    ball(sf::RenderWindow *const app_window, sf::Clock *const app_clock);
    ~ball();
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::CircleShape get_ball() const;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;
    sf::Time count_delta_time();
    void display() override;


private:
    sf::RenderWindow *const window;
    sf::Clock *const clock;
    sf::CircleShape ball_shape;
    sf::Vector2f velocity_vector;
    sf::Vector2f position;
    sf::Time previus_time;
};

#endif