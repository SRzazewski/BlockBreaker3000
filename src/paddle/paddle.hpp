#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

class paddle
{
public:
    paddle();
    ~paddle();
    void move_paddle_left();
    void move_paddle_right();
    sf::RectangleShape *get_paddle();


private:
    sf::RectangleShape *player_s_paddle;
    float position_x;
    float position_y;
};

#endif