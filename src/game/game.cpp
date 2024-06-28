#include "game.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

game::game() 
{
    block_breaker_area = {0.0f, 800.0f, 30.0f, 600.0f};
    game_area_field.setSize(sf::Vector2f(block_breaker_area.x_stop - block_breaker_area.x_start, block_breaker_area.y_stop - block_breaker_area.y_start));
    game_area_field.setFillColor(sf::Color::Black);
    game_area_field.setPosition(sf::Vector2f(block_breaker_area.x_start, block_breaker_area.y_start));
}

game::game(game_area area):
    block_breaker_area(area)
{
    game_area_field.setSize(sf::Vector2f(block_breaker_area.x_stop - block_breaker_area.x_start, block_breaker_area.y_stop - block_breaker_area.y_start));
    game_area_field.setFillColor(sf::Color::Black);
    game_area_field.setPosition(sf::Vector2f(block_breaker_area.x_start, block_breaker_area.y_start));
}


void game::init(sf::Font &font)
{
    game_state = game_states::game_init;
    game_state_requested = game_states::level_1_init;
    text_obj.setFont(font);
    text_obj.setString("BlockBreaker3000");
    text_obj.setCharacterSize(24);
    text_obj.setFillColor(sf::Color::Red);
    text_obj.setStyle(sf::Text::Bold);
}

void game::serve_events(const sf::Event event, sf::RenderWindow &window, sf::Clock &clock_obj)
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

    if(state_is_from_scope(game_state, states_init))
    {
        game::serve_events_level_init(event, window, clock_obj);
    }
    else if(state_is_from_scope(game_state, states_playing))
    {
        game::serve_events_level(event, window, clock_obj);
    }
    else if(game_state == game_states::level_won)
    {
        game::serve_events_level_won(event, window, clock_obj);
    }
    else if(game_state == game_states::level_lost)
    {
        game::serve_events_level_lost(event, window, clock_obj);
    }
}

void game::serve_events_level_init(const sf::Event event, sf::RenderWindow &window, sf::Clock &clock_obj)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
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
            clock_obj.restart();
            previus_time = sf::seconds(0.0f);
        }
    default:
        break;
    }
}

void game::serve_events_level(const sf::Event event, sf::RenderWindow &window, sf::Clock &clock_obj)
{
switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Left)
        {
            paddle_obj.set_velocity_vector(sf::Vector2f(-400.0f, 0.0f));
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            paddle_obj.set_velocity_vector(sf::Vector2f(400.0f, 0.0f));
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

void game::serve_events_level_won(const sf::Event event, sf::RenderWindow &window, sf::Clock &clock_obj)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
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

void game::serve_events_level_lost(const sf::Event event, sf::RenderWindow &window, sf::Clock &clock_obj)
{

    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
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

void game::update(sf::Clock &clock_obj)
{
    if (game_state_requested != game_state)
    {
        game::game_state_update();
    }


    for(const game_states state: states_playing)
    {
        if(game_state == state)
        {   
            sf::Time current_time = clock_obj.getElapsedTime();
            time_delta = current_time - previus_time;
            previus_time = current_time;

            for (auto &ball : balls)
            {
                if(ball.get_visible())
                {
                    move_ball(ball);
                }
            }
            move_paddle();
            for (auto &powerup_obj : powerups)
            {
                if(powerup_obj.get_visible())
                {
                    move_powerup(powerup_obj);
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
}

void game::rand_powerups(int powerup_number)
{
    std::srand(std::time(0));
    int rand_number = 0;

    auto number_is_in_vector = [=](int number) -> bool
    {
        if(powerup_from_blocks.size() > 0)
        {
            for(int i: powerup_from_blocks)
            {
                if(i == number)
                {
                    return true;
                }
            }
        }
        return false;
    };

    for(int i = 0; i < powerup_number; ++i)
    {
        do
        { 
            rand_number = std::rand() % (blocks.size());
        }
        while(rand_number < 4 || number_is_in_vector(rand_number));
        
        powerup_from_blocks.push_back(rand_number);
    }
}

void game::game_state_level_1_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;

    for(int i = 0; i < 1; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            blocks.push_back(block(sf::Vector2f(j * 100.0f + 50.0f, i * 30.0f + 50.0f)));
            blocks_number++;
        }
    }

    rand_powerups(1);
}

void game::game_state_level_2_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;

    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            blocks.push_back(block(sf::Vector2f(j * 100.0f + 50.0f, i * 30.0f + 50.0f)));
            blocks_number++;
        }
    }

    rand_powerups(2);
}

void game::game_state_level_3_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;

    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            blocks.push_back(block(sf::Vector2f(j * 100.0f + 50.0f, i * 30.0f + 50.0f)));
            blocks_number++;
        }
    }

    rand_powerups(4);
}

void game::game_state_level_4_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;

    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            blocks.push_back(block(sf::Vector2f(j * 100.0f + 50.0f, i * 30.0f + 50.0f)));
            blocks_number++;
        }
    }

    rand_powerups(5);
}

void game::game_state_level_5_prepare()
{
    obj_reset();

    balls.push_back(ball());
    balls_number++;

    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            blocks.push_back(block(sf::Vector2f(j * 100.0f + 50.0f, i * 30.0f + 50.0f)));
            blocks_number++;
        }
    }

    rand_powerups(7);
}

void game::game_state_update()
{
    if (game_state_requested == game_states::level_1_init)
    {
        game::game_state_level_1_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 1");
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
}

void game::move_paddle()
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

void game::move_ball(ball &ball_obj)
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

void game::move_powerup(powerup &powerup_obj)
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
    block_obj.break_obj();
    for(int i : powerup_from_blocks)
    {
        if (i == blocks_number)
        {
            powerups.push_back(powerup(block_obj.get_position()));
        }
    }
    blocks_number--;
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