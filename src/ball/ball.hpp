#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class ball
{
public:
    ball(std::shared_ptr<sf::RenderWindow> app_window, std::shared_ptr<sf::Clock> app_clock);
    ~ball();
    void set_position(sf::Vector2f position);
    sf::Vector2f get_position() const;
    sf::CircleShape get_ball() const;
    void set_velocity_vector(sf::Vector2f vector);
    sf::Vector2f get_velocity_vector() const;


private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Clock> clock;
    sf::CircleShape ball_shape;
    sf::Vector2f velocity_vector;
    sf::Vector2f position;
};

#endif