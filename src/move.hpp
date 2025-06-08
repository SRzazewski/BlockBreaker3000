#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "game_object.hpp"
#include <SFML/System/Time.hpp>
#include <memory>

class game;

class Move
{
public:
    ~Move() = default;
    virtual void move(sf::Time time_delta, moving_object &obj) = 0;
    void set_game_instance(game *game_inst);
protected:
    game *game_instance; /* There have to be pointer to the object creates 
                          * the game_object*/ 
};

class Move_paddle : public Move
{
public:
    void move(sf::Time time_delta, moving_object &obj) override;
};

class Move_ball : public Move
{
public:
    void move(sf::Time time_delta, moving_object &obj) override;
};

class Move_powerup : public Move
{
public:
    void move(sf::Time time_delta, moving_object &obj) override;
};

#endif /* MOVE_HPP_ */