#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "game_object.hpp"
#include "move.hpp"
#include <SFML/Graphics.hpp>

constexpr float powerup_radius = 10.0f;
constexpr int powerup_triangle = 3;

class powerup : public moving_object
{
public:
    powerup(sf::Vector2f start_position);
    void set_position(sf::Vector2f position) override;
    sf::Vector2f get_position() const override;
    sf::CircleShape get_powerup() const;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;
    sf::Time count_delta_time(sf::Clock &clock);
    void draw(sf::RenderWindow &window) override;
    void move(sf::Time time_delta) override;
    bool get_visible();
    int get_points();

private:
    std::unique_ptr<Move_powerup> move_ptr;
    sf::CircleShape powerup_shape = sf::CircleShape(powerup_radius, 
                                                        powerup_triangle);
    sf::Vector2f velocity_vector = sf::Vector2f(0.0f, 100.0f);
    int points = 50;
};

#endif