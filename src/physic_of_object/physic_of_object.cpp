#include "physic_of_object.hpp"

#include "paddle.hpp"
#include "ball.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

void move_objects(paddle paddle_obj, std::vector<ball> &balls, game_area area)
{
    sf::Vector2f position_of_ball = balls[0].get_position();
    sf::Vector2f velocity_of_ball = balls[0].get_velocity_vector();
    sf::Time delay = balls[0].count_delta_time();
    
    position_of_ball.x = position_of_ball.x + (velocity_of_ball.x * delay.asSeconds());
    position_of_ball.y = position_of_ball.y + (velocity_of_ball.y * delay.asSeconds());
    if (velocity_of_ball.y > 0 
        && (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f - balls[0].get_ball().getRadius()) < position_of_ball.y)
    {
        if((position_of_ball.x > (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f))
            && (position_of_ball.x) < (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f))
        {
            position_of_ball.y = 2 * (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f - balls[0].get_ball().getRadius()) - position_of_ball.y;
            velocity_of_ball.y *= -1.0;
        }
    }

    if (position_of_ball.x < balls[0].get_ball().getRadius())
    {
        position_of_ball.x = 2 * (balls[0].get_ball().getRadius()) - position_of_ball.x;
        velocity_of_ball.x *= -1.0;
    }
    else if(position_of_ball.x > (area.x_stop - balls[0].get_ball().getRadius()))
    {
        position_of_ball.x = 2 * (area.x_stop - balls[0].get_ball().getRadius()) - position_of_ball.x;
        velocity_of_ball.x *= -1.0;
    }

    if (position_of_ball.y < balls[0].get_ball().getRadius())
    {
        position_of_ball.y = 2 * (balls[0].get_ball().getRadius()) - position_of_ball.y;
        velocity_of_ball.y *= -1.0;
    }
    else if(position_of_ball.y > (area.y_stop - balls[0].get_ball().getRadius()))
    {
        position_of_ball.y = 2 * (area.y_stop - balls[0].get_ball().getRadius()) - position_of_ball.y;
        velocity_of_ball.y *= -1.0;
    }

    balls[0].set_velocity_vector(velocity_of_ball);
    balls[0].set_position(position_of_ball);
}