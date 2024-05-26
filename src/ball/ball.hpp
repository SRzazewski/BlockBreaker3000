#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class ball
{
public:
    ball();
    ~ball();
    void set_position(sf::Vector2f position);
    sf::Vector2f get_position();
    std::shared_ptr<sf::CircleShape> get_ball();
    void set_velocity_vector(sf::Vector2f vector);
    sf::Vector2f get_velocity_vector();


private:
    std::shared_ptr<sf::CircleShape> ball_shape;
    sf::Vector2f velocity_vector;
    sf::Vector2f position;
};

#endif