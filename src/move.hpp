#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "game_object.hpp"
#include <SFML/System/Time.hpp>

class Move
{
public:
    ~Move() = default;
    virtual void move(sf::Time time_delta, moving_object &obj) = 0;
};

class Move_paddle
{
public:
    // Move_paddle();
    void move(sf::Time time_delta, moving_object &obj);
};

#endif /* MOVE_HPP_ */