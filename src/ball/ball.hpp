#ifndef BALL_HPP
#define BALL_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class ball : public moving_object
{
public:
    ball();
    ~ball();
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::CircleShape get_ball() const;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;
    sf::Time count_delta_time(sf::Clock &clock);
    void draw(sf::RenderWindow &window);
    void draw() override;//TODO remove after update moving_object
    void reset() override;


private:
    sf::CircleShape ball_shape;
    sf::Vector2f velocity_vector;
    sf::Vector2f position;
    sf::Time previus_time;
};

#endif