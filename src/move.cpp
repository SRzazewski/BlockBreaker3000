#include "move.hpp"
#include "game_object.hpp"
#include "game.hpp"
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
        obj.set_position(sf::Vector2f(paddle_position.x, paddle_position.y));
    }
}

void Move_paddle::set_game_instance(game *game_inst)
{

}

void Move_ball::move(sf::Time time_delta, moving_object &obj)
{
    sf::Vector2f ball_position_new = obj.get_position();
    sf::Vector2f ball_velocity = obj.get_velocity_vector();
    
    ball_position_new += (ball_velocity * time_delta.asSeconds());
    
    game_instance->ball_meets_paddle(static_cast<ball&>(obj), 
                                    ball_position_new);
    ball_position_new = obj.get_position();
    game_instance->ball_meets_block(static_cast<ball&>(obj), 
                                    ball_position_new);
    ball_position_new = obj.get_position();
    game_instance->ball_meets_edge(static_cast<ball&>(obj), 
                                    ball_position_new);
}

void Move_ball::set_game_instance(game *game_inst)
{
    game_instance = game_inst;
}