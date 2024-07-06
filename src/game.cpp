#include "game.hpp"
#include "block.hpp"
#include <cmath>
#include <numbers>

void game::serve_events(const sf::Event event)
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
            paddle_obj.set_velocity_vector(sf::Vector2f({}));
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            paddle_obj.set_velocity_vector(sf::Vector2f({}));
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
            for (auto i = 0ul; i < balls.size(); ++i)
            {
                if(!move_ball(balls[i], time_delta))
                {
                    balls.erase(balls.begin() + i);
                    --i;

                    if(balls.empty())
                    {
                        game_state_requested = game_states::level_lost;
                    }
                }
            }

            move_paddle(time_delta);

            for (auto i = 0ul; i < powerups.size(); ++i)
            {
                if(!move_powerup(powerups[i], time_delta))
                {
                    powerups.erase(powerups.begin() + i);
                    --i;
                }
            }
            break;
        }   
    }
}

void game::obj_reset()
{
    balls.clear();
    blocks.clear();
    paddle_obj.reset();
    powerups.clear();
    powerup_from_blocks.clear();
    score_level = 0;
    text_score.setString("Score: " + std::to_string(score + score_level));
}

void game::rand_powerups(int powerup_number)
{
    std::uniform_int_distribution<int> dist(powerup_banned_blocks, blocks.size() - 1);
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
    
    for(int i = 0; i < rows_number; ++i)
    {
        for(int j = 0; j < blocks_in_row; ++j)
        {
            blocks.push_back(block(
                sf::Vector2f(
                    j * (block_size.x + 2*block_outline_thickness) 
                    + (block_size.x + 2*block_outline_thickness)/2 + block_breaker_area.x_start, 
                    (i + ready_rows) * (block_size.y + 2*block_outline_thickness) 
                    + (block_size.y + 2*block_outline_thickness)/2 + block_breaker_area.y_start), 
                block_type));
        }
    }
}

void game::game_state_level_1_prepare()
{
    obj_reset();

    balls.push_back(ball());

    put_blocks(block_blue, 2);

    rand_powerups(2);
}

void game::game_state_level_2_prepare()
{
    obj_reset();

    balls.push_back(ball());

    put_blocks(block_yellow, 1);
    put_blocks(block_blue, 2);

    rand_powerups(4);
}

void game::game_state_level_3_prepare()
{
    obj_reset();

    balls.push_back(ball());

    put_blocks(block_orange, 1);
    put_blocks(block_yellow, 1);
    put_blocks(block_blue, 1);

    rand_powerups(5);
}

void game::game_state_level_4_prepare()
{
    obj_reset();

    balls.push_back(ball());

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
    }
    else if (game_state_requested == game_states::level_2_init)
    {
        game::game_state_level_2_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 2");
    }
    else if (game_state_requested == game_states::level_3_init)
    {
        game::game_state_level_3_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 3");
    }
    else if (game_state_requested == game_states::level_4_init)
    {
        game::game_state_level_4_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 4");
    }
    else if (game_state_requested == game_states::level_5_init)
    {
        game::game_state_level_5_prepare();
        text_obj.setString("BlockBreaker3000 - Press S to start level 5");
    }
    else if (game_state_requested == game_states::level_1)
    {
        text_obj.setString("BlockBreaker3000 - level 1");
    }
    else if (game_state_requested == game_states::level_2)
    {
        text_obj.setString("BlockBreaker3000 - level 2");
    }
    else if (game_state_requested == game_states::level_3)
    {
        text_obj.setString("BlockBreaker3000 - level 3");
    }
    else if (game_state_requested == game_states::level_4)
    {
        text_obj.setString("BlockBreaker3000 - level 4");
    }
    else if (game_state_requested == game_states::level_5)
    {
        text_obj.setString("BlockBreaker3000 - level 5");
    }
    else if (game_state_requested == game_states::level_lost)
    {
        text_obj.setString("BlockBreaker3000 - You lost :( Press R to reset level");
    }
    else if (game_state_requested == game_states::level_won)
    {
        text_obj.setString("BlockBreaker3000 - You won :) Press N to next level");
        score_level += static_cast<int>(balls.size()) * points_for_ball;
        score += score_level;
        text_score.setString("Score: " + std::to_string(score));
        window.setTitle("BlockBreaker3000 - Score: " + std::to_string(score));
    }
    game_state_previus = game_state;
    game_state = game_state_requested;
}

void game::draw(sf::RenderWindow &window)
{
    window.draw(game_area_field);

    paddle_obj.draw(window);
    
    for(auto &ball : balls)
    {
        ball.draw(window);
    }

    for(auto powerup : powerups)
    {
        powerup.draw(window);
    }

    if(!blocks.empty())
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

    if (paddle_position.x < position_paddle_x_min)
    {
        paddle_obj.set_position(sf::Vector2f(position_paddle_x_min, paddle_position.y));
    }
    else if (paddle_position.x > position_paddle_x_max)
    {
        paddle_obj.set_position(sf::Vector2f(position_paddle_x_max, paddle_position.y));
    }
    else
    {
        paddle_obj.set_position(sf::Vector2f(paddle_position.x, paddle_position.y));
    }
}

bool game::move_ball(ball &ball_obj, sf::Time time_delta)
{
    sf::Vector2f ball_position_new = ball_obj.get_position();
    sf::Vector2f ball_velocity = ball_obj.get_velocity_vector();
    
    ball_position_new += (ball_velocity * time_delta.asSeconds());
    
    ball_meets_paddle(ball_obj, ball_position_new);
    for (auto i = 0ul; i < blocks.size(); ++i)
    {
        if(ball_meets_block(ball_obj, blocks[i], ball_position_new))
        {
            blocks.erase(blocks.begin() + i);
            --i;
        }
    }
    return !ball_meets_edge(ball_obj, ball_position_new);
}

bool game::move_powerup(powerup &powerup_obj, sf::Time time_delta)
{
    sf::Vector2f powerup_position_new = powerup_obj.get_position();
    sf::Vector2f powerup_velocity = powerup_obj.get_velocity_vector();
    
    powerup_position_new.x = powerup_position_new.x + (powerup_velocity.x * time_delta.asSeconds());
    powerup_position_new.y = powerup_position_new.y + (powerup_velocity.y * time_delta.asSeconds());

    if(!powerup_meets_paddle(powerup_obj) && !powerup_meets_edge(powerup_obj))
    {
        powerup_obj.set_position(powerup_position_new);
        return true;
    }
    return false;
}

bool game::ball_meets_edge(ball &ball_obj, sf::Vector2f ball_position)
{
    sf::Vector2f ball_velocity = ball_obj.get_velocity_vector();

    if (ball_position.x < (block_breaker_area.x_start + ball_obj.get_ball().getRadius()))
    {
        ball_position.x = 2 * (block_breaker_area.x_start + ball_obj.get_ball().getRadius()) - ball_position.x;
        float fi = atan2(ball_velocity.y, ball_velocity.x);
        if(ball_velocity.y < 0)
        {
            fi += std::numbers::pi_v<float>/2;
            fi *= -1.0f;
        }
        else if(ball_velocity.y > 0)
        {
            fi += -std::numbers::pi_v<float>/2;
            fi *= -1.0;
        }
        fi *= 2.0f;
        ball_velocity = game::calculate_new_vector(ball_velocity, fi);
    }
    else if(ball_position.x > (block_breaker_area.x_stop - ball_obj.get_ball().getRadius()))
    {
        ball_position.x = 2 * (block_breaker_area.x_stop - ball_obj.get_ball().getRadius()) - ball_position.x;
        float fi = atan2(ball_velocity.y, ball_velocity.x);
        // std::cout << "1Angle before:" << 180/std::numbers::pi_v<float>*fi << "\n";
        if(ball_velocity.y < 0)
        {
            fi = std::numbers::pi_v<float>/2 + fi;
            fi *= -1.0;
        }
        else if(ball_velocity.y > 0)
        {
            fi = std::numbers::pi_v<float>/2 - fi;
        }
        fi *= 2.0f;
        // std::cout << "Angle after:" << 180/std::numbers::pi_v<float>*fi << "\n";
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
            fi += std::numbers::pi_v<float>;
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
        return true;
    }

    ball_obj.set_velocity_vector(ball_velocity);
    ball_obj.set_position(ball_position);

    return false;
}

bool game::block_broke(block &block_obj)
{
    int points_for_block = block_obj.hit_obj();
    score_level += points_for_block;
    if (points_for_block > 0)
    {
        text_score.setString("Score: " + std::to_string(score + score_level));
        for(int i : powerup_from_blocks)
        {
            if (i == static_cast<int>(blocks.size()))
            {
                powerups.push_back(powerup(block_obj.get_position()));
            }
        }
        return true;
    }
    return false;
}

bool game::ball_meets_block(ball &ball_obj, block &block_obj, sf::Vector2f ball_position)
{
    sf::Vector2f ball_velocity = ball_obj.get_velocity_vector();
    bool ret_val = false;

    if (ball_velocity.y > 0 
        && (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - block_obj.get_block().getOutlineThickness() - ball_obj.get_ball().getRadius()) < ball_position.y
        && (block_obj.get_position().y + block_obj.get_block().getSize().y/2.0f + block_obj.get_block().getOutlineThickness() + ball_obj.get_ball().getRadius()) > ball_position.y)
    {
        if((ball_position.x > (block_obj.get_position().x - block_obj.get_block().getSize().x/2.0f - block_obj.get_block().getOutlineThickness()))
            && (ball_position.x) < (block_obj.get_position().x + block_obj.get_block().getSize().x/2.0f + block_obj.get_block().getOutlineThickness()))
        {
            ball_position.y = 2 * (block_obj.get_position().y - block_obj.get_block().getSize().y/2.0f - ball_obj.get_ball().getRadius() - block_obj.get_block().getOutlineThickness()) - ball_position.y;
            ball_velocity.y *= -1.0;

            ret_val = block_broke(block_obj);
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

            ret_val = block_broke(block_obj);
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

            ret_val = block_broke(block_obj);
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

            ret_val = block_broke(block_obj);
        }
    }

    ball_obj.set_velocity_vector(ball_velocity);
    ball_obj.set_position(ball_position);

    return ret_val;
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
                fi += ((paddle_obj.get_position().x - ball_position.x)/(paddle_obj.get_paddle().getSize().x/2.0f))*(std::numbers::pi_v<float>/24);
                fi *= -1.0f;
            }
            else
            {
                fi = std::numbers::pi_v<float> - fi;
                fi += ((paddle_obj.get_position().x - ball_position.x)/(paddle_obj.get_paddle().getSize().x/2.0f))*(-std::numbers::pi_v<float>/24);
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
                fi = std::numbers::pi_v<float>/2 - fi;
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
                fi = fi - std::numbers::pi_v<float>/2;
                fi *= -1.0f;
                fi *= 2.0f;
                ball_velocity = game::calculate_new_vector(ball_velocity, fi);
            }
        }
    }

    ball_obj.set_velocity_vector(ball_velocity);
    ball_obj.set_position(ball_position);
}

bool game::powerup_meets_paddle(powerup &powerup_obj)
{
    if((powerup_obj.get_position().x > (paddle_obj.get_position().x - paddle_obj.get_paddle().getSize().x/2.0f))
        && (powerup_obj.get_position().x < (paddle_obj.get_position().x + paddle_obj.get_paddle().getSize().x/2.0f))
        && (powerup_obj.get_position().y > (paddle_obj.get_position().y - paddle_obj.get_paddle().getSize().y/2.0f))
        && (powerup_obj.get_position().y < (paddle_obj.get_position().y + paddle_obj.get_paddle().getSize().y/2.0f)))
    {
        balls.push_back(ball(sf::Vector2f(paddle_obj.get_position().x + ball_start_position_shift.x, 
            paddle_obj.get_position().y + ball_start_position_shift.y)));
        score_level += powerup_obj.get_points();
        text_score.setString("Score: " + std::to_string(score + score_level));
        return true;
    }
    return false;
}

bool game::powerup_meets_edge(powerup &powerup_obj)
{
    return powerup_obj.get_position().y > (block_breaker_area.y_stop + powerup_obj.get_powerup().getRadius());
}

sf::Vector2f game::calculate_new_vector(sf::Vector2f vector_current, float fi)
{
    sf::Vector2f vector_new;
    vector_new.x = vector_current.x * cos(fi) - vector_current.y * sin(fi);
    vector_new.y = vector_current.x * sin(fi) + vector_current.y * cos(fi);
    return vector_new;
}