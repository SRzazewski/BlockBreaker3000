#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class powerup : public moving_object
{
public:
    powerup(sf::Vector2f start_position);
    ~powerup();
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::CircleShape get_powerup() const;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;
    sf::Time count_delta_time(sf::Clock &clock);
    void draw(sf::RenderWindow &window) override;
    void set_visible(bool is_visable);
    bool get_visible();

private:
    sf::CircleShape powerup_shape;
    sf::Vector2f velocity_vector;
    sf::Vector2f position;
    sf::Time previus_time;
    bool visible;
};

#endif