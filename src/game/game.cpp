#include "game.hpp"
#include <iostream>

game::game() 
{
    block_breaker_area = {0.0f, 800.0f, 30.0f, 600.0f};
    game_state = game_states::during_game;
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
            if(game_state == game_states::during_game) paddle_obj.set_velocity_vector(sf::Vector2f(-200.0f, 0.0f));
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            if(game_state == game_states::during_game) paddle_obj.set_velocity_vector(sf::Vector2f(200.0f, 0.0f));
        }
        else if (event.key.code == sf::Keyboard::R)
        {
            if(game_state == game_states::init_game || game_state == game_states::won_game) 
            {
                for(int i =0; i < blocks.size(); ++i)
                {
                    blocks[i].reset();
                }
                block::set_number_of_blocks(blocks.size());
                paddle_obj.reset();
                balls[0].reset();
                game_state = game_states::during_game;
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
    if (game_state == game_states::during_game)
    {
        move_objects(clock_obj, paddle_obj, balls, blocks, block_breaker_area, game_state);
    }
}

void game::draw(sf::RenderWindow &window)
{
    if (game_state == game_states::during_game)
    {
        // std::cout << "phase game: during game\n";
        text_obj.setString("BlockBreaker3000");
    }
    else if (game_state == game_states::init_game)
    {
        text_obj.setString("BlockBreaker3000 - You lost :( Press R to reset");
    }
    
    if (game_state == game_states::won_game)
    {
        text_obj.setString("BlockBreaker3000 - You won :) Press R to reset");
    }

    paddle_obj.draw(window);
    balls[0].draw(window);
    if(block::get_number_of_blocks() > 0)
    {
        for(int i =0; i < blocks.size(); ++i)
        {
            blocks[i].draw(window);
        }
    }
    else
    {
        game_state = game_states::won_game;
    }

    window.draw(text_obj);
}