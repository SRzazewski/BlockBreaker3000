#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class paddle
{
public:
    paddle();
    ~paddle();
    void move_paddle_left();
    void move_paddle_right();
    std::shared_ptr<sf::RectangleShape> get_paddle();


private:
    std::shared_ptr<sf::RectangleShape> player_s_paddle;
    float position_x;
    float position_y;
};

#endif