#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class ball
{
public:
    ball(sf::RenderWindow *const app_window, sf::Clock *const app_clock);
    ~ball();
    void set_position(sf::Vector2f position);
    sf::Vector2f get_position() const;
    sf::CircleShape get_ball() const;
    void set_velocity_vector(sf::Vector2f vector);
    sf::Vector2f get_velocity_vector() const;
    void display_ball();


private:
    sf::RenderWindow *const window;
    sf::Clock *const clock;
    sf::CircleShape ball_shape;
    sf::Vector2f velocity_vector;
    sf::Vector2f position;
    float radius = 16.0f;
};

#endif