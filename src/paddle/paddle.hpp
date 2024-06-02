#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class paddle : public moving_object
{
public:
    paddle(sf::RenderWindow *const app_window, sf::Clock *const app_clock, float game_area);
    void move_paddle_left();
    void move_paddle_right();

    void set_position(sf::Vector2f position) override;
    void set_velocity_vector(sf::Vector2f vector) override;
    sf::Vector2f get_velocity_vector() const override;

    sf::RectangleShape get_paddle() const;
    sf::Vector2f get_position() const override;
    void display() override;


private:
    sf::RenderWindow *const window;
    sf::Clock *const clock;
    float paddle_area;
    sf::RectangleShape player_s_paddle;
    sf::Vector2f velocity_vector;
};

#endif