#include "game.hpp"
#include <iostream>

game::game() 
{
    block_breaker_area = {0.0f, 800.0f, 30.0f, 600.0f};
    game_state = game_states::during_game;
    game_state_request = game_states::during_game;
    game_area_field.setSize(sf::Vector2f(block_breaker_area.x_stop - block_breaker_area.x_start, block_breaker_area.y_stop - block_breaker_area.y_start));
    game_area_field.setFillColor(sf::Color::Black);
    game_area_field.setPosition(sf::Vector2f(block_breaker_area.x_start, block_breaker_area.y_start));
}

game::game(game_area area):
    block_breaker_area(area)
{
    game_state = game_states::during_game;
    game_state_request = game_states::during_game;
    game_area_field.setSize(sf::Vector2f(block_breaker_area.x_stop - block_breaker_area.x_start, block_breaker_area.y_stop - block_breaker_area.y_start));
    game_area_field.setFillColor(sf::Color::Black);
    game_area_field.setPosition(sf::Vector2f(block_breaker_area.x_start, block_breaker_area.y_start));
    blocks_number = 0;
}


void game::init(sf::Font &font)
{
    text_obj.setFont(font);
    text_obj.setString("BlockBreaker3000");
    text_obj.setCharacterSize(24);
    text_obj.setFillColor(sf::Color::Red);
    text_obj.setStyle(sf::Text::Bold);

    balls.push_back(ball());

    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            blocks.push_back(block(sf::Vector2f(j * 100.0f + 50.0f, i * 30.0f + 50.0f)));
            blocks_number++;
        }
    }
}

void game::serve_events(const sf::Event event, sf::RenderWindow &window, sf::Clock &clock_obj)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Left)
        {
            if(game_state == game_states::during_game) paddle_obj.set_velocity_vector(sf::Vector2f(-300.0f, 0.0f));
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            if(game_state == game_states::during_game) paddle_obj.set_velocity_vector(sf::Vector2f(300.0f, 0.0f));
        }
        else if (event.key.code == sf::Keyboard::R)
        {
            if(game_state == game_states::init_game || game_state == game_states::won_game) 
            {
                for(int i =0; i < blocks.size(); ++i)
                {
                    blocks[i].reset();
                }
                blocks_number = blocks.size();
                paddle_obj.reset();
                balls[0].reset();
                game_state_request = game_states::during_game;
                clock_obj.restart();
            }
        }
        break;
    case sf::Event::KeyReleased:
        if (event.key.code == sf::Keyboard::Left)
        {
            if(game_state == game_states::during_game) paddle_obj.set_velocity_vector(sf::Vector2f(0.0f, 0.0f));
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            if(game_state == game_states::during_game) paddle_obj.set_velocity_vector(sf::Vector2f(0.0f, 0.0f));
        }
        break;
    default:
        break;
    }
}

void game::update(sf::Clock &clock_obj)
{
    if (game_state_request != game_state)
    {
        game::game_state_update();
    }

    if (game_state == game_states::during_game)
    {
        sf::Time current_time = clock_obj.getElapsedTime();
        time_delta = current_time - previus_time;
        previus_time = current_time;

        for (int i = 0; i < balls.size(); ++i)
        {
            move_ball(balls[i]);
        }
        move_paddle();
    }
}

void game::draw(sf::RenderWindow &window)
{
    window.draw(game_area_field);

    paddle_obj.draw(window);
    balls[0].draw(window);
    if(blocks_number > 0)
    {
        for(int i =0; i < blocks.size(); ++i)
        {
            blocks[i].draw(window);
        }
    }
    else
    {
        game_state_request = game_states::won_game;
    }

    window.draw(text_obj);
}

void game::game_state_update()
{
    if (game_state_request == game_states::during_game)
    {
        // std::cout << "phase game: during game\n";
        text_obj.setString("BlockBreaker3000");
        game_state = game_states::during_game;
    }
    else if (game_state_request == game_states::init_game)
    {
        text_obj.setString("BlockBreaker3000 - You lost :( Press R to reset");
        game_state = game_states::init_game;
    }
    
    if (game_state_request == game_states::won_game)
    {
        text_obj.setString("BlockBreaker3000 - You won :) Press R to reset");
        game_state = game_states::won_game;
    }
}

void game::move_paddle()
{
    sf::Vector2f position_of_paddle = paddle_obj.get_position();
    sf::Vector2f velocity_of_paddle = paddle_obj.get_velocity_vector();
    position_of_paddle.x = position_of_paddle.x + (velocity_of_paddle.x * time_delta.asSeconds());

    if (velocity_of_paddle.x < 0)
    {
        if (position_of_paddle.x < (block_breaker_area.x_start + paddle_obj.get_paddle().getSize().x/2.0f))
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
        if (position_of_paddle.x > (block_breaker_area.x_stop - paddle_obj.get_paddle().getSize().x/2.0f))
        {
            paddle_obj.set_position(sf::Vector2f(((block_breaker_area.x_stop - paddle_obj.get_paddle().getSize().x/2.0f)), paddle_obj.get_position().y));    }
        else
        {
            paddle_obj.set_position(sf::Vector2f(position_of_paddle.x, paddle_obj.get_position().y));
        }
    }
}

void game::move_ball(ball &ball_obj)
{
    sf::Vector2f position_of_ball_new = ball_obj.get_position();
    sf::Vector2f velocity_of_ball = ball_obj.get_velocity_vector();
    
    position_of_ball_new.x = position_of_ball_new.x + (velocity_of_ball.x * time_delta.asSeconds());
    position_of_ball_new.y = position_of_ball_new.y + (velocity_of_ball.y * time_delta.asSeconds());
    
    ball_meets_paddle(ball_obj, position_of_ball_new);
    for (int j = 0; j < blocks.size(); ++j)
    {
        ball_meets_block(ball_obj, blocks[j], position_of_ball_new);
    }
    ball_meets_edge(ball_obj, position_of_ball_new);
}

void game::ball_meets_edge(ball &ball_obj, sf::Vector2f position_of_ball)
{
    sf::Vector2f velocity_of_ball = ball_obj.get_velocity_vector();

    if (position_of_ball.x < (block_breaker_area.x_start + ball_obj.get_ball().getRadius()))
    {
        position_of_ball.x = 2 * (block_breaker_area.x_start + ball_obj.get_ball().getRadius()) - position_of_ball.x;
        velocity_of_ball.x *= -1.0;
    }
    else if(position_of_ball.x > (block_breaker_area.x_stop - ball_obj.get_ball().getRadius()))
    {
        position_of_ball.x = 2 * (block_breaker_area.x_stop - ball_obj.get_ball().getRadius()) - position_of_ball.x;
        velocity_of_ball.x *= -1.0;
    }

    if (position_of_ball.y < (block_breaker_area.y_start + ball_obj.get_ball().getRadius()))
    {
        position_of_ball.y = 2 * (block_breaker_area.y_start + ball_obj.get_ball().getRadius()) - position_of_ball.y;
        velocity_of_ball.y *= -1.0;
    }
    else if(position_of_ball.y > (block_breaker_area.y_stop - ball_obj.get_ball().getRadius()))
    {
        game_state_request = game_states::init_game;
    }

    ball_obj.set_velocity_vector(velocity_of_ball);
    ball_obj.set_position(position_of_ball);
}

void game::ball_meets_block(ball &ball_obj, block &block_obj, sf::Vector2f position_of_ball)
{
    sf::Vector2f velocity_of_ball = ball_obj.get_velocity_vector();
    
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
                blocks_number--;
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
                blocks_number--;
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
                blocks_number--;
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
                blocks_number--;
            }
        }

        ball_obj.set_velocity_vector(velocity_of_ball);
        ball_obj.set_position(position_of_ball);
    }
}

void game::ball_meets_paddle(ball &ball_obj, sf::Vector2f position_of_ball)
{
    sf::Vector2f velocity_of_ball = ball_obj.get_velocity_vector();
    
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