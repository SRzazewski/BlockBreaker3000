#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class paddle
{
public:
    paddle(float game_area);
    ~paddle();
    void move_paddle_left();
    void move_paddle_right();
    std::shared_ptr<sf::RectangleShape> get_paddle() const;
    sf::Vector2f get_position() const;


private:
    float paddle_area;
    std::shared_ptr<sf::RectangleShape> player_s_paddle;
    sf::Vector2f position;
};

#endif