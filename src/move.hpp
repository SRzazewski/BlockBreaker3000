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
    virtual void set_game_instance(game *game_inst) = 0;
};

class Move_paddle : public Move
{
public:
    void move(sf::Time time_delta, moving_object &obj) override;
    void set_game_instance(game *game_inst) override;
};

class Move_ball : public Move
{
public:
    void move(sf::Time time_delta, moving_object &obj) override;
    void set_game_instance(game *game_inst) override;
private:
    game *game_instance;
};

#endif /* MOVE_HPP_ */