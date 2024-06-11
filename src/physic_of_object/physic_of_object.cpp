#include "physic_of_object.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

void ball_meets_paddle(ball &ball_obj, paddle &paddle_obj)
{
    sf::Vector2f position_of_ball = ball_obj.get_position();
    sf::Vector2f velocity_of_ball = ball_obj.get_velocity_vector();
    sf::Time ball_delay = ball_obj.count_delta_time();
    
    position_of_ball.x = position_of_ball.x + (velocity_of_ball.x * ball_delay.asSeconds());
    position_of_ball.y = position_of_ball.y + (velocity_of_ball.y * ball_delay.asSeconds());

    if (velocity_of_ball.y > 0 
        && (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f - ball_obj.get_ball().getRadius()) < position_of_ball.y)
    {
        if((position_of_ball.x > (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f))
            && (position_of_ball.x) < (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f))
        {
            position_of_ball.y = 2 * (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f - ball_obj.get_ball().getRadius()) - position_of_ball.y;
            velocity_of_ball.y *= -1.0;
        }
    }

    if (velocity_of_ball.x > 0 
        && (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f - ball_obj.get_ball().getRadius()) < position_of_ball.x
        && (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f + ball_obj.get_ball().getRadius()) > position_of_ball.x)
    {
        if((position_of_ball.y > (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f))
            && (position_of_ball.y) < (paddle_obj.get_position().y + paddle_obj.get_paddle().getSize().y/2.0f))
        {
            position_of_ball.x = 2 * (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f - ball_obj.get_ball().getRadius()) - position_of_ball.x;
            velocity_of_ball.x *= -1.0;
        }
    }
    else if (velocity_of_ball.x < 0 
        && (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f - ball_obj.get_ball().getRadius()) < position_of_ball.x
        && (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f + ball_obj.get_ball().getRadius()) > position_of_ball.x)
    {
        if((position_of_ball.y > (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f))
            && (position_of_ball.y) < (paddle_obj.get_position().y + paddle_obj.get_paddle().getSize().y/2.0f))
        {
            position_of_ball.x = 2 * (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f + ball_obj.get_ball().getRadius()) - position_of_ball.x;
            velocity_of_ball.x *= -1.0;
        }
    }

    ball_obj.set_velocity_vector(velocity_of_ball);
    ball_obj.set_position(position_of_ball);
}

void ball_meets_block(ball &ball_obj, block &block_obj)
{
    sf::Vector2f position_of_ball = ball_obj.get_position();
    sf::Vector2f velocity_of_ball = ball_obj.get_velocity_vector();
    sf::Time ball_delay = ball_obj.count_delta_time();
    
    position_of_ball.x = position_of_ball.x + (velocity_of_ball.x * ball_delay.asSeconds());
    position_of_ball.y = position_of_ball.y + (velocity_of_ball.y * ball_delay.asSeconds());

    if(!block_obj.is_broken())
    {
        if (velocity_of_ball.y > 0 
            && (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - 5.0f - ball_obj.get_ball().getRadius()) < position_of_ball.y
            && (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + 5.0f + ball_obj.get_ball().getRadius()) > position_of_ball.y)
        {
            if((position_of_ball.x > (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - 5.0f))
                && (position_of_ball.x) < (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + 5.0f))
            {
                position_of_ball.y = 2 * (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - ball_obj.get_ball().getRadius() - 5.0f) - position_of_ball.y;
                velocity_of_ball.y *= -1.0;

                block_obj.break_obj();
                block::decrement_number_of_blocks();
                // blocks.erase(blocks.begin() + i);
            }
        }
        else if (velocity_of_ball.y < 0
            && (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + 5.0f + ball_obj.get_ball().getRadius()) > position_of_ball.y
            && (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - 5.0f - ball_obj.get_ball().getRadius()) < position_of_ball.y)
        {
            if((position_of_ball.x > (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - 5.0f))
                && (position_of_ball.x) < (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + 5.0f))
            {
                position_of_ball.y = 2 * (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + ball_obj.get_ball().getRadius() + 5.0f) - position_of_ball.y;
                velocity_of_ball.y *= -1.0;

                block_obj.break_obj();
                block::decrement_number_of_blocks();
                // blocks.erase(blocks.begin() + i);
            }
        }

        if (velocity_of_ball.x > 0 
            && (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - 5.0f - ball_obj.get_ball().getRadius()) < position_of_ball.x
            && (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + 5.0f + ball_obj.get_ball().getRadius()) > position_of_ball.x)
        {
            if((position_of_ball.y > (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - 5.0f))
                && (position_of_ball.y) < (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + 5.0f))
            {
                position_of_ball.x = 2 * (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - ball_obj.get_ball().getRadius() - 5.0f) - position_of_ball.x;
                velocity_of_ball.x *= -1.0;

                block_obj.break_obj();
                block::decrement_number_of_blocks();
                // blocks.erase(blocks.begin() + i);
            }
        }
        else if (velocity_of_ball.x < 0
            && (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + 5.0f + ball_obj.get_ball().getRadius()) > position_of_ball.x
            && (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - 5.0f - ball_obj.get_ball().getRadius()) < position_of_ball.x)
        {
            if((position_of_ball.y > (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - 5.0f))
                && (position_of_ball.y) < (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + 5.0f))
            {
                position_of_ball.x = 2 * (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + ball_obj.get_ball().getRadius() + 5.0f) - position_of_ball.x;
                velocity_of_ball.x *= -1.0;

                block_obj.break_obj();
                block::decrement_number_of_blocks();
                // blocks.erase(blocks.begin() + i);
            }
        }

        ball_obj.set_velocity_vector(velocity_of_ball);
        ball_obj.set_position(position_of_ball);
    }
}

void ball_meets_edge(ball &ball_obj, game_area area, game_states &game_state)
{
    sf::Vector2f position_of_ball = ball_obj.get_position();
    sf::Vector2f velocity_of_ball = ball_obj.get_velocity_vector();
    sf::Time ball_delay = ball_obj.count_delta_time();
    
    position_of_ball.x = position_of_ball.x + (velocity_of_ball.x * ball_delay.asSeconds());
    position_of_ball.y = position_of_ball.y + (velocity_of_ball.y * ball_delay.asSeconds());
    if (position_of_ball.x < (area.x_start + ball_obj.get_ball().getRadius()))
    {
        position_of_ball.x = 2 * (area.x_start + ball_obj.get_ball().getRadius()) - position_of_ball.x;
        velocity_of_ball.x *= -1.0;
    }
    else if(position_of_ball.x > (area.x_stop - ball_obj.get_ball().getRadius()))
    {
        position_of_ball.x = 2 * (area.x_stop - ball_obj.get_ball().getRadius()) - position_of_ball.x;
        velocity_of_ball.x *= -1.0;
    }

    if (position_of_ball.y < (area.y_start + ball_obj.get_ball().getRadius()))
    {
        position_of_ball.y = 2 * (area.y_start + ball_obj.get_ball().getRadius()) - position_of_ball.y;
        velocity_of_ball.y *= -1.0;
    }
    else if(position_of_ball.y > (area.y_stop - ball_obj.get_ball().getRadius()))
    {
        game_state = game_states::init_game;
    }

    ball_obj.set_velocity_vector(velocity_of_ball);
    ball_obj.set_position(position_of_ball);
}

void move_ball(ball &ball_obj, paddle &paddle_obj, std::vector<block> &blocks, game_area area, game_states &game_state)
{
    ball_meets_paddle(ball_obj, paddle_obj);
    for (int j = 0; j < blocks.size(); ++j)
    {
        ball_meets_block(ball_obj, blocks[j]);
    }
    ball_meets_edge(ball_obj, area, game_state);
}

void move_paddle(sf::Clock &clock, paddle &paddle_obj, game_area area)
{
    sf::Vector2f position_of_paddle = paddle_obj.get_position();
    sf::Vector2f velocity_of_paddle = paddle_obj.get_velocity_vector();
    sf::Time paddle_delay = paddle_obj.count_delta_time(clock);
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

void move_objects(sf::Clock &clock, paddle &paddle_obj, std::vector<ball> &balls, std::vector<block> &blocks, game_area area, game_states &game_state)
{
    for (int i = 0; i < balls.size(); ++i)
    {
        move_ball(balls[i], paddle_obj, blocks, area, game_state);
    }

    move_paddle(clock, paddle_obj, area);

}