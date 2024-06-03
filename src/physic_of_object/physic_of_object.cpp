#include "physic_of_object.hpp"

#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

void move_objects(paddle &paddle_obj, std::vector<ball> &balls, std::vector<block> &blocks, game_area area, int &game_state)
{
    sf::Vector2f position_of_ball = balls[0].get_position();
    sf::Vector2f velocity_of_ball = balls[0].get_velocity_vector();
    sf::Time ball_delay = balls[0].count_delta_time();
    
    position_of_ball.x = position_of_ball.x + (velocity_of_ball.x * ball_delay.asSeconds());
    position_of_ball.y = position_of_ball.y + (velocity_of_ball.y * ball_delay.asSeconds());

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

    if (velocity_of_ball.x > 0 
        && (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f - balls[0].get_ball().getRadius()) < position_of_ball.x
        && (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f + balls[0].get_ball().getRadius()) > position_of_ball.x)
    {
        if((position_of_ball.y > (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f))
            && (position_of_ball.y) < (paddle_obj.get_position().y + paddle_obj.get_paddle().getSize().y/2.0f))
        {
            position_of_ball.x = 2 * (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f - balls[0].get_ball().getRadius()) - position_of_ball.x;
            velocity_of_ball.x *= -1.0;
        }
    }
    else if (velocity_of_ball.x < 0 
        && (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f - balls[0].get_ball().getRadius()) < position_of_ball.x
        && (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f + balls[0].get_ball().getRadius()) > position_of_ball.x)
    {
        if((position_of_ball.y > (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f))
            && (position_of_ball.y) < (paddle_obj.get_position().y + paddle_obj.get_paddle().getSize().y/2.0f))
        {
            position_of_ball.x = 2 * (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f + balls[0].get_ball().getRadius()) - position_of_ball.x;
            velocity_of_ball.x *= -1.0;
        }
    }


    for(int i =0; i < blocks.size(); ++i)
    {
        if(!blocks[i].is_broken())
        {
            if (velocity_of_ball.y > 0 
                && (blocks[i].get_position().y - blocks[i].get_block().getSize().y/2.0f - 5.0f - balls[0].get_ball().getRadius()) < position_of_ball.y
                && (blocks[i].get_position().y + blocks[i].get_block().getSize().y/2.0f + 5.0f + balls[0].get_ball().getRadius()) > position_of_ball.y)
            {
                if((position_of_ball.x > (blocks[i].get_position().x - blocks[i].get_block().getSize().x/2.0f - 5.0f))
                    && (position_of_ball.x) < (blocks[i].get_position().x + blocks[i].get_block().getSize().x/2.0f + 5.0f))
                {
                    position_of_ball.y = 2 * (blocks[i].get_position().y - blocks[i].get_block().getSize().y/2.0f - balls[0].get_ball().getRadius() - 5.0f) - position_of_ball.y;
                    velocity_of_ball.y *= -1.0;

                    blocks[i].break_obj();
                    block::decrement_number_of_blocks();
                    // blocks.erase(blocks.begin() + i);
                }
            }
            else if (velocity_of_ball.y < 0
                && (blocks[i].get_position().y + blocks[i].get_block().getSize().y/2.0f + 5.0f + balls[0].get_ball().getRadius()) > position_of_ball.y
                && (blocks[i].get_position().y - blocks[i].get_block().getSize().y/2.0f - 5.0f - balls[0].get_ball().getRadius()) < position_of_ball.y)
            {
                if((position_of_ball.x > (blocks[i].get_position().x - blocks[i].get_block().getSize().x/2.0f - 5.0f))
                    && (position_of_ball.x) < (blocks[i].get_position().x + blocks[i].get_block().getSize().x/2.0f + 5.0f))
                {
                    position_of_ball.y = 2 * (blocks[i].get_position().y + blocks[i].get_block().getSize().y/2.0f + balls[0].get_ball().getRadius() + 5.0f) - position_of_ball.y;
                    velocity_of_ball.y *= -1.0;

                    blocks[i].break_obj();
                    block::decrement_number_of_blocks();
                    // blocks.erase(blocks.begin() + i);
                }
            }

            if (velocity_of_ball.x > 0 
                && (blocks[i].get_position().x - blocks[i].get_block().getSize().x/2.0f - 5.0f - balls[0].get_ball().getRadius()) < position_of_ball.x
                && (blocks[i].get_position().x + blocks[i].get_block().getSize().x/2.0f + 5.0f + balls[0].get_ball().getRadius()) > position_of_ball.x)
            {
                if((position_of_ball.y > (blocks[i].get_position().y - blocks[i].get_block().getSize().y/2.0f - 5.0f))
                    && (position_of_ball.y) < (blocks[i].get_position().y + blocks[i].get_block().getSize().y/2.0f + 5.0f))
                {
                    position_of_ball.x = 2 * (blocks[i].get_position().x - blocks[i].get_block().getSize().x/2.0f - balls[0].get_ball().getRadius() - 5.0f) - position_of_ball.x;
                    velocity_of_ball.x *= -1.0;

                    blocks[i].break_obj();
                    block::decrement_number_of_blocks();
                    // blocks.erase(blocks.begin() + i);
                }
            }
            else if (velocity_of_ball.x < 0
                && (blocks[i].get_position().x + blocks[i].get_block().getSize().x/2.0f + 5.0f + balls[0].get_ball().getRadius()) > position_of_ball.x
                && (blocks[i].get_position().x - blocks[i].get_block().getSize().x/2.0f - 5.0f - balls[0].get_ball().getRadius()) < position_of_ball.x)
            {
                if((position_of_ball.y > (blocks[i].get_position().y - blocks[i].get_block().getSize().y/2.0f - 5.0f))
                    && (position_of_ball.y) < (blocks[i].get_position().y + blocks[i].get_block().getSize().y/2.0f + 5.0f))
                {
                    position_of_ball.x = 2 * (blocks[i].get_position().x + blocks[i].get_block().getSize().x/2.0f + balls[0].get_ball().getRadius() + 5.0f) - position_of_ball.x;
                    velocity_of_ball.x *= -1.0;

                    blocks[i].break_obj();
                    block::decrement_number_of_blocks();
                    // blocks.erase(blocks.begin() + i);
                }
            }
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
        // position_of_ball.y = 2 * (area.y_stop - balls[0].get_ball().getRadius()) - position_of_ball.y;
        // velocity_of_ball.y *= -1.0;
        game_state = 0;
    }

    balls[0].set_velocity_vector(velocity_of_ball);
    balls[0].set_position(position_of_ball);







    sf::Vector2f position_of_paddle = paddle_obj.get_position();
    sf::Vector2f velocity_of_paddle = paddle_obj.get_velocity_vector();
    sf::Time paddle_delay = paddle_obj.count_delta_time();
    position_of_paddle.x = position_of_paddle.x + (velocity_of_paddle.x * paddle_delay.asSeconds());

    if (velocity_of_paddle.x < 0)
    {
        if (position_of_paddle.x < (area.x_start + paddle_obj.get_paddle().getSize().x/2.0f))
        {
            paddle_obj.set_position(sf::Vector2f((paddle_obj.get_paddle().getSize().x/2.0f), paddle_obj.get_position().y));
        }
        else
        {
            paddle_obj.set_position(sf::Vector2f(position_of_paddle.x, paddle_obj.get_position().y));
        }
    }

    if (velocity_of_paddle.x > 0) 
    {
        if (position_of_paddle.x > (area.x_stop - paddle_obj.get_paddle().getSize().x/2.0f))
        {
            paddle_obj.set_position(sf::Vector2f(((area.x_stop - paddle_obj.get_paddle().getSize().x/2.0f)), paddle_obj.get_position().y));    }
        else
        {
            paddle_obj.set_position(sf::Vector2f(position_of_paddle.x, paddle_obj.get_position().y));
        }
    }
}