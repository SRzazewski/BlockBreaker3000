#include "game.hpp"
#include "block.hpp"
#include <cmath>
#include <random>
// #include <iostream>

game::game(sf::Font &font, game_area area):
    block_breaker_area(area)
{
    game_area_field.setSize(sf::Vector2f(block_breaker_area.x_stop - block_breaker_area.x_start, block_breaker_area.y_stop - block_breaker_area.y_start));
    game_area_field.setFillColor(sf::Color::Black);
    game_area_field.setPosition(sf::Vector2f(block_breaker_area.x_start, block_breaker_area.y_start));
    game_state = game_states::game_init;
    game_state_requested = game_states::level_1_init;
    score = 0;
    score_level = 0;
    text_obj.setFont(font);
    text_obj.setString("BlockBreaker3000");
    text_obj.setCharacterSize(24);
    text_obj.setFillColor(sf::Color::Red);
    text_obj.setStyle(sf::Text::Bold);
    text_score.setFont(font);
    text_score.setString("Score: " + std::to_string(score + score_level));
    text_score.setCharacterSize(24);
    text_score.setFillColor(sf::Color::Red);
    text_score.setStyle(sf::Text::Bold);
    text_score.setPosition(0.0f, 30.0f);
}

void game::serve_events(const sf::Event event, sf::RenderWindow &window)
{
    auto state_is_from_scope = [](game_states state, const std::array<game_states, 5> scope) -> bool
    {
        for(game_states st : scope)
        {
            if(state == st)
            {
                return true;
            }
        }
        return false;
    };

    if(event.type == sf::Event::Closed)
    {
        window.close();
    }
    else
    { 
        if(state_is_from_scope(game_state, states_init))
        {
            game::serve_events_level_init(event);
        }
        else if(state_is_from_scope(game_state, states_playing))
        {
            game::serve_events_level(event);
        }
        else if(game_state == game_states::level_won)
        {
            game::serve_events_level_won(event);
        }
        else if(game_state == game_states::level_lost)
        {
            game::serve_events_level_lost(event);
        }
    }
}

void game::serve_events_level_init(const sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::S)
        {
            if (game_state == game_states::level_1_init)
            {
                game_state_requested = game_states::level_1;
            }
            else if (game_state == game_states::level_2_init)
            {
                game_state_requested = game_states::level_2;
            }
            else if (game_state == game_states::level_3_init)
            {
                game_state_requested = game_states::level_3;
            }
            else if (game_state == game_states::level_4_init)
            {
                game_state_requested = game_states::level_4;
            }
            else if (game_state == game_states::level_5_init)
            {
                game_state_requested = game_states::level_5;
            }
        }
    default:
        break;
    }
}

void game::serve_events_level(const sf::Event event)
{
switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Left)
        {
            paddle_obj.set_velocity_vector(sf::Vector2f(-paddle_velocity, 0.0f));
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            paddle_obj.set_velocity_vector(sf::Vector2f(paddle_velocity, 0.0f));
        }
        break;
    case sf::Event::KeyReleased:
        if (event.key.code == sf::Keyboard::Left)
        {
            paddle_obj.set_velocity_vector(sf::Vector2f(0.0f, 0.0f));
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            paddle_obj.set_velocity_vector(sf::Vector2f(0.0f, 0.0f));
        }
        break;
    default:
        break;
    }
}

void game::serve_events_level_won(const sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::N)
        {
            if (game_state_previus == game_states::level_1)
            {
                game_state_requested = game_states::level_2_init;
            }
            else if (game_state_previus == game_states::level_2)
            {
                game_state_requested = game_states::level_3_init;
            }
            else if (game_state_previus == game_states::level_3)
            {
                game_state_requested = game_states::level_4_init;
            }
            else if (game_state_previus == game_states::level_4)
            {
                game_state_requested = game_states::level_5_init;
            }
            else if (game_state_previus == game_states::level_5_init)
            {
                game_state_requested = game_states::level_1_init;
            }
        }
    default:
        break;
    }
}

void game::serve_events_level_lost(const sf::Event event)
{

    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::R)
        {
            if (game_state_previus == game_states::level_1)
            {
                game_state_requested = game_states::level_1_init;
            }
            else if (game_state_previus == game_states::level_2)
            {
                game_state_requested = game_states::level_2_init;
            }
            else if (game_state_previus == game_states::level_3)
            {
                game_state_requested = game_states::level_3_init;
            }
            else if (game_state_previus == game_states::level_4)
            {
                game_state_requested = game_states::level_4_init;
            }
            else if (game_state_previus == game_states::level_5)
            {
                game_state_requested = game_states::level_5_init;
            }
        }
        break;
    default:
        break;
    }
}

void game::update(sf::RenderWindow &window, sf::Time time_delta)
{
    if (game_state_requested != game_state)
    {
        game::game_state_update(window);
    }

    for(const game_states state: states_playing)
    {
        if(game_state == state)
        {   
            for (auto &ball : balls)
            {
                if(ball.get_visible())
                {
                    move_ball(ball, time_delta);
                }
            }
            move_paddle(time_delta);
            for (auto &powerup_obj : powerups)
            {
                if(powerup_obj.get_visible())
                {
                    move_powerup(powerup_obj, time_delta);
                }
            }
            break;
        }   
    }
}

void game::obj_reset()
{
    balls.clear();
    balls_number = 0;
    blocks.clear();
    blocks_number = 0;
    paddle_obj.reset();
    powerups.clear();
    powerup_from_blocks.clear();
    score_level = 0;
    text_score.setString("Score: " + std::to_string(score + score_level));
}

void game::rand_powerups(int powerup_number)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(powerup_banned_blocks, blocks.size());
    int rand_number = 0;

    for(int i = 0; i < powerup_number; ++i)
    {
        do
        { 
            rand_number = dist(mt);
        }
        while(std::find(powerup_from_blocks.begin(), powerup_from_blocks.end(), rand_number) != powerup_from_blocks.end());
        
        powerup_from_blocks.push_back(rand_number);
    }
}

void game::put_blocks(int block_type, int rows_number)
{
    int ready_rows = blocks.size()/blocks_in_row;
    
    for(int i = ready_rows; i < (ready_rows + rows_number); ++i)
    {
        for(int j = 0; j < blocks_in_row; ++j)
        {
            blocks.push_back(block(sf::Vector2f(j * (block_size.x + 2*block_outline_thickness) + (((block_size.x + 2*block_outline_thickness)/2) + block_breaker_area.x_start), 
                i * (block_size.y + 2*block_outline_thickness) + ((block_size.y + 2*block_outline_thickness)/2) + block_breaker_area.y_start), 
                block_type));
            blocks_number++;
        }
    }
}

void game::game_state_level_1_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;

    put_blocks(block_blue, 2);

    rand_powerups(2);
}

void game::game_state_level_2_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;


    put_blocks(block_yellow, 1);
    put_blocks(block_blue, 2);

    rand_powerups(4);
}

void game::game_state_level_3_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;

    put_blocks(block_orange, 1);
    put_blocks(block_yellow, 1);
    put_blocks(block_blue, 1);

    rand_powerups(5);
}

void game::game_state_level_4_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;

    put_blocks(block_brown, 1);
    put_blocks(block_orange, 1);
    put_blocks(block_yellow, 1);
    put_blocks(block_blue, 1);

    rand_powerups(6);
}

void game::game_state_level_5_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;

    put_blocks(block_brown, 2);
    put_blocks(block_orange, 1);
    put_blocks(block_yellow, 1);
    put_blocks(block_blue, 1);

    rand_powerups(8);
}

void game::game_state_update(sf::RenderWindow &window)
{
    if (game_state_requested == game_states::level_1_init)
    {
        game::game_state_level_1_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 1");
        window.setTitle("BlockBreaker3000 - Score: " + std::to_string(score));
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_2_init)
    {
        game::game_state_level_2_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 2");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_3_init)
    {
        game::game_state_level_3_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 3");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_4_init)
    {
        game::game_state_level_4_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 4");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_5_init)
    {
        game::game_state_level_5_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 5");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_1)
    {
        text_obj.setString("BlockBreaker3000 - level 1");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_2)
    {
        text_obj.setString("BlockBreaker3000 - level 2");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_3)
    {
        text_obj.setString("BlockBreaker3000 - level 3");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_4)
    {
        text_obj.setString("BlockBreaker3000 - level 4");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_5)
    {
        text_obj.setString("BlockBreaker3000 - level 5");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_lost)
    {
        text_obj.setString("BlockBreaker3000 - You lost :( Press R to reset level");
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
    else if (game_state_requested == game_states::level_won)
    {
        text_obj.setString("BlockBreaker3000 - You won :) Press N to next level");
        score_level += balls_number * points_for_ball;
        score += score_level;
        text_score.setString("Score: " + std::to_string(score));
        window.setTitle("BlockBreaker3000 - Score: " + std::to_string(score));
        game_state_previus = game_state;
        game_state = game_state_requested;
    }
}

void game::draw(sf::RenderWindow &window)
{
    window.draw(game_area_field);

    paddle_obj.draw(window);
    
    for(auto ball : balls)
    {
        ball.draw(window);
    }

    if(powerups.size() > 0)
    {
        for(auto powerup : powerups)
        {
            powerup.draw(window);
        }
    }

    if(blocks_number > 0)
    {
        for(auto block : blocks)
        {
            block.draw(window);
        }
    }
    else
    {
        game_state_requested = game_states::level_won;
    }

    window.draw(text_obj);
    window.draw(text_score);
}

void game::move_paddle(sf::Time time_delta)
{
    sf::Vector2f paddle_position = paddle_obj.get_position();
    sf::Vector2f paddle_velocity = paddle_obj.get_velocity_vector();
    paddle_position.x = paddle_position.x + (paddle_velocity.x * time_delta.asSeconds());

    if (paddle_velocity.x < 0)
    {
        if (paddle_position.x < (block_breaker_area.x_start + paddle_obj.get_paddle().getSize().x/2.0f))
        {
            paddle_obj.set_position(sf::Vector2f((paddle_obj.get_paddle().getSize().x/2.0f), paddle_obj.get_position().y));
        }
        else
        {
            paddle_obj.set_position(sf::Vector2f(paddle_position.x, paddle_obj.get_position().y));
        }
    }

    if (paddle_velocity.x > 0) 
    {
        if (paddle_position.x > (block_breaker_area.x_stop - paddle_obj.get_paddle().getSize().x/2.0f))
        {
            paddle_obj.set_position(sf::Vector2f(((block_breaker_area.x_stop - paddle_obj.get_paddle().getSize().x/2.0f)), paddle_obj.get_position().y));    }
        else
        {
            paddle_obj.set_position(sf::Vector2f(paddle_position.x, paddle_obj.get_position().y));
        }
    }
}

void game::move_ball(ball &ball_obj, sf::Time time_delta)
{
    sf::Vector2f ball_position_new = ball_obj.get_position();
    sf::Vector2f ball_velocity = ball_obj.get_velocity_vector();
    
    ball_position_new.x = ball_position_new.x + (ball_velocity.x * time_delta.asSeconds());
    ball_position_new.y = ball_position_new.y + (ball_velocity.y * time_delta.asSeconds());
    
    ball_meets_paddle(ball_obj, ball_position_new);
    for (auto &block : blocks)
    {
        ball_meets_block(ball_obj, block, ball_position_new);
    }
    ball_meets_edge(ball_obj, ball_position_new);
}

void game::move_powerup(powerup &powerup_obj, sf::Time time_delta)
{
    sf::Vector2f powerup_position_new = powerup_obj.get_position();
    sf::Vector2f powerup_velocity = powerup_obj.get_velocity_vector();
    
    powerup_position_new.x = powerup_position_new.x + (powerup_velocity.x * time_delta.asSeconds());
    powerup_position_new.y = powerup_position_new.y + (powerup_velocity.y * time_delta.asSeconds());

    powerup_meets_paddle(powerup_obj);
    powerup_meets_edge(powerup_obj);

    powerup_obj.set_position(powerup_position_new);
}

void game::ball_meets_edge(ball &ball_obj, sf::Vector2f ball_position)
{
    sf::Vector2f ball_velocity = ball_obj.get_velocity_vector();

    if (ball_position.x < (block_breaker_area.x_start + ball_obj.get_ball().getRadius()))
    {
        ball_position.x = 2 * (block_breaker_area.x_start + ball_obj.get_ball().getRadius()) - ball_position.x;
        float fi = atan2(ball_velocity.y, ball_velocity.x);
        if(ball_velocity.y < 0)
        {
            fi += M_PI/2;
            fi *= -1.0f;
        }
        else if(ball_velocity.y > 0)
        {
            fi += -M_PI/2;
            fi *= -1.0;
        }
        fi *= 2.0f;
        ball_velocity = game::calculate_new_vector(ball_velocity, fi);
    }
    else if(ball_position.x > (block_breaker_area.x_stop - ball_obj.get_ball().getRadius()))
    {
        ball_position.x = 2 * (block_breaker_area.x_stop - ball_obj.get_ball().getRadius()) - ball_position.x;
        float fi = atan2(ball_velocity.y, ball_velocity.x);
        // std::cout << "1Angle before:" << 180/M_PI*fi << "\n";
        if(ball_velocity.y < 0)
        {
            fi = M_PI/2 + fi;
            fi *= -1.0;
        }
        else if(ball_velocity.y > 0)
        {
            fi = M_PI/2 - fi;
        }
        fi *= 2.0f;
        // std::cout << "Angle after:" << 180/M_PI*fi << "\n";
        // std::cout << "Velocity before x:" << ball_velocity.x << "\n";
        // std::cout << "Velocity before y:" << ball_velocity.y << "\n";
        ball_velocity = game::calculate_new_vector(ball_velocity, fi);
        // std::cout << "Velocity after x:" << ball_velocity.x << "\n";
        // std::cout << "Velocity after y:" << ball_velocity.y << "\n\n";
    }

    if (ball_position.y < (block_breaker_area.y_start + ball_obj.get_ball().getRadius()))
    {
        ball_position.y = 2 * (block_breaker_area.y_start + ball_obj.get_ball().getRadius()) - ball_position.y;
        float fi = atan2(ball_velocity.y, ball_velocity.x);
        if(ball_velocity.x < 0)
        {
            fi += M_PI;
            fi *= -1.0;
        }
        else if(ball_velocity.x > 0)
        {
            fi *= -1.0;
        }
        fi *= 2.0f;
        ball_velocity = game::calculate_new_vector(ball_velocity, fi);
    }
    else if(ball_position.y > (block_breaker_area.y_stop + ball_obj.get_ball().getRadius()))
    {
        balls_number--;
        ball_obj.set_visible(false);
        if(balls_number < 1)
        {
            game_state_requested = game_states::level_lost;
        }
    }

    ball_obj.set_velocity_vector(ball_velocity);
    ball_obj.set_position(ball_position);
}

void game::block_broke(block &block_obj)
{
    int points_for_block = block_obj.break_obj();
    score_level += points_for_block;
    if (points_for_block > 0)
    {
        text_score.setString("Score: " + std::to_string(score + score_level));
        for(int i : powerup_from_blocks)
        {
            if (i == blocks_number)
            {
                powerups.push_back(powerup(block_obj.get_position()));
            }
        }
        blocks_number--;
    }
}

void game::ball_meets_block(ball &ball_obj, block &block_obj, sf::Vector2f ball_position)
{
    sf::Vector2f ball_velocity = ball_obj.get_velocity_vector();
    
    if(!block_obj.is_broken())
    {
        if (ball_velocity.y > 0 
            && (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - block_obj.get_block().getOutlineThickness() - ball_obj.get_ball().getRadius()) < ball_position.y
            && (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + block_obj.get_block().getOutlineThickness() + ball_obj.get_ball().getRadius()) > ball_position.y)
        {
            if((ball_position.x > (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - block_obj.get_block().getOutlineThickness()))
                && (ball_position.x) < (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + block_obj.get_block().getOutlineThickness()))
            {
                ball_position.y = 2 * (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - ball_obj.get_ball().getRadius() - block_obj.get_block().getOutlineThickness()) - ball_position.y;
                ball_velocity.y *= -1.0;

                game::block_broke(block_obj);
            }
        }
        else if (ball_velocity.y < 0
            && (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + block_obj.get_block().getOutlineThickness() + ball_obj.get_ball().getRadius()) > ball_position.y
            && (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - block_obj.get_block().getOutlineThickness() - ball_obj.get_ball().getRadius()) < ball_position.y)
        {
            if((ball_position.x > (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - block_obj.get_block().getOutlineThickness()))
                && (ball_position.x) < (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + block_obj.get_block().getOutlineThickness()))
            {
                ball_position.y = 2 * (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + ball_obj.get_ball().getRadius() + block_obj.get_block().getOutlineThickness()) - ball_position.y;
                ball_velocity.y *= -1.0;

                game::block_broke(block_obj);
            }
        }

        if (ball_velocity.x > 0 
            && (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - block_obj.get_block().getOutlineThickness() - ball_obj.get_ball().getRadius()) < ball_position.x
            && (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + block_obj.get_block().getOutlineThickness() + ball_obj.get_ball().getRadius()) > ball_position.x)
        {
            if((ball_position.y > (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - block_obj.get_block().getOutlineThickness()))
                && (ball_position.y) < (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + block_obj.get_block().getOutlineThickness()))
            {
                ball_position.x = 2 * (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - ball_obj.get_ball().getRadius() - block_obj.get_block().getOutlineThickness()) - ball_position.x;
                ball_velocity.x *= -1.0;

                game::block_broke(block_obj);
            }
        }
        else if (ball_velocity.x < 0
            && (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + block_obj.get_block().getOutlineThickness() + ball_obj.get_ball().getRadius()) > ball_position.x
            && (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - block_obj.get_block().getOutlineThickness() - ball_obj.get_ball().getRadius()) < ball_position.x)
        {
            if((ball_position.y > (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - block_obj.get_block().getOutlineThickness()))
                && (ball_position.y) < (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + block_obj.get_block().getOutlineThickness()))
            {
                ball_position.x = 2 * (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + ball_obj.get_ball().getRadius() + block_obj.get_block().getOutlineThickness()) - ball_position.x;
                ball_velocity.x *= -1.0;

                game::block_broke(block_obj);
            }
        }

        ball_obj.set_velocity_vector(ball_velocity);
        ball_obj.set_position(ball_position);
    }
}

void game::ball_meets_paddle(ball &ball_obj, sf::Vector2f ball_position)
{
    sf::Vector2f ball_velocity = ball_obj.get_velocity_vector();
    
    if (ball_velocity.y > 0 
        && (ball_position.y > (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f - ball_obj.get_ball().getRadius()))
        && (ball_position.y < (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f)))
    {
        if((ball_position.x > (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f))
            && (ball_position.x) < (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f))
        {
            ball_position.y = 2 * (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f - ball_obj.get_ball().getRadius()) - ball_position.y;
            float fi = atan2(ball_velocity.y, ball_velocity.x);
            if (ball_velocity.x > 0)
            {
                fi += ((paddle_obj.get_position().x - ball_position.x)/(paddle_obj.get_paddle().getSize().x/2.0f))*(M_PI/24);
                fi *= -1.0f;
            }
            else
            {
                fi = M_PI - fi;
                fi += ((paddle_obj.get_position().x - ball_position.x)/(paddle_obj.get_paddle().getSize().x/2.0f))*(-M_PI/24);
            }
            fi *=2;
            ball_velocity = game::calculate_new_vector(ball_velocity, fi);
        }
        else if (ball_velocity.x > 0 
            && (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f - ball_obj.get_ball().getRadius()) < ball_position.x
            && (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f + ball_obj.get_ball().getRadius()) > ball_position.x)
        {
            if((ball_position.y > (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f))
                && (ball_position.y) < (paddle_obj.get_position().y + paddle_obj.get_paddle().getSize().y/2.0f))
            {
                ball_position.x = 2 * (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f - ball_obj.get_ball().getRadius()) - ball_position.x;
                float fi = atan2(ball_velocity.y, ball_velocity.x);
                fi = M_PI/2 - fi;
                fi *= 2;
                ball_velocity = game::calculate_new_vector(ball_velocity, fi);
            }
        }
        else if (ball_velocity.x < 0 
            && (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f - ball_obj.get_ball().getRadius()) < ball_position.x
            && (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f + ball_obj.get_ball().getRadius()) > ball_position.x)
        {
            if((ball_position.y > (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f))
                && (ball_position.y) < (paddle_obj.get_position().y + paddle_obj.get_paddle().getSize().y/2.0f))
            {
                ball_position.x = 2 * (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f + ball_obj.get_ball().getRadius()) - ball_position.x;
                float fi = atan2(ball_velocity.y, ball_velocity.x);
                fi = fi - M_PI/2;
                fi *= -1.0f;
                fi *= 2.0f;
                ball_velocity = game::calculate_new_vector(ball_velocity, fi);
            }
        }
    }

    ball_obj.set_velocity_vector(ball_velocity);
    ball_obj.set_position(ball_position);
}

void game::powerup_meets_paddle(powerup &powerup_obj)
{
    if((powerup_obj.get_position().x > (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f))
        && (powerup_obj.get_position().x < (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f))
        && (powerup_obj.get_position().y > (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f))
        && (powerup_obj.get_position().y < (paddle_obj.get_position().y + paddle_obj.get_paddle().getSize().y/2.0f)))
    {
        powerup_obj.set_visible(false);
        balls.push_back(ball(sf::Vector2f(paddle_obj.get_position().x + ball_start_position_shift.x, 
            paddle_obj.get_position().y + ball_start_position_shift.y)));
        balls_number++;
        score_level += powerup_obj.get_points();
        text_score.setString("Score: " + std::to_string(score + score_level));
    }
}

void game::powerup_meets_edge(powerup &powerup_obj)
{
    if(powerup_obj.get_position().y > (block_breaker_area.y_stop + powerup_obj.get_powerup().getRadius()))
    {
        powerup_obj.set_visible(false);
    }
}

sf::Vector2f game::calculate_new_vector(sf::Vector2f vector_current, float fi)
{
    sf::Vector2f vector_new;
    vector_new.x = vector_current.x * cos(fi) - vector_current.y * sin(fi);
    vector_new.y = vector_current.x * sin(fi) + vector_current.y * cos(fi);
    return vector_new;
}