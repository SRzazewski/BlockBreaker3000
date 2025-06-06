#include "move.hpp"
#include "game_object.hpp"
#include "common.hpp"
#include <SFML/System/Time.hpp>

void Move_paddle::move(sf::Time time_delta, moving_object &obj)
{
    sf::Vector2f paddle_position = obj.get_position();
    paddle_position.x += obj.get_velocity_vector().x 
                            * time_delta.asSeconds();

    if (paddle_position.x < position_paddle_x_min)
    {
        obj.set_position(
                        sf::Vector2f(position_paddle_x_min, paddle_position.y));
    }
    else if (paddle_position.x > position_paddle_x_max)
    {
        obj.set_position(
                        sf::Vector2f(position_paddle_x_max, paddle_position.y));
    }
    else
    {
        obj.set_position(
                        sf::Vector2f(paddle_position.x, paddle_position.y));
    }
}