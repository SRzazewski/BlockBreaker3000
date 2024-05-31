#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class paddle
{
public:
    paddle(sf::RenderWindow *const app_window, sf::Clock *const app_clock, float game_area);
    void move_paddle_left();
    void move_paddle_right();
    sf::RectangleShape get_paddle() const;
    sf::Vector2f get_position() const;
    void display_paddle();


private:
    sf::RenderWindow *const window;
    sf::Clock *const clock;
    float paddle_area;
    sf::RectangleShape player_s_paddle;
};

#endif