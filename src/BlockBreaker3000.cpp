#include "paddle.hpp"
#include "ball.hpp"
#include "physic_of_object.hpp"
#include "block.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>

int block::number_of_blocks = 0;

int main()
{
    const game_area block_breaker_area = {0.0f, 800.0f, 30.0f, 600.0f};
    auto window = sf::RenderWindow{ { static_cast<unsigned int>(block_breaker_area.x_stop), static_cast<unsigned int>(block_breaker_area.y_stop) }, "BlockBreaker3000" };
    window.setFramerateLimit(144);

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        window.close();
    }
    text.setFont(font);
    text.setString("BlockBreaker3000");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    sf::Clock clock_obj = sf::Clock();
    sf::Time time_obj = sf::Time();
    paddle paddle_obj = paddle(block_breaker_area.x_stop);
    std::vector<ball> balls = {ball(&window, &clock_obj)};

    std::vector<block> blocks = {block(&window, sf::Vector2f(50.0f, 50.0f)),
                                block(&window, sf::Vector2f(150.0f, 50.0f)),
                                block(&window, sf::Vector2f(250.0f, 50.0f)),
                                block(&window, sf::Vector2f(350.0f, 50.0f)),
                                block(&window, sf::Vector2f(450.0f, 50.0f)),
                                block(&window, sf::Vector2f(550.0f, 50.0f)),
                                block(&window, sf::Vector2f(650.0f, 50.0f)),
                                block(&window, sf::Vector2f(750.0f, 50.0f)),
                                block(&window, sf::Vector2f(50.0f, 80.0f)),
                                block(&window, sf::Vector2f(150.0f, 80.0f)),
                                block(&window, sf::Vector2f(250.0f, 80.0f)),
                                block(&window, sf::Vector2f(350.0f, 80.0f)),
                                block(&window, sf::Vector2f(450.0f, 80.0f)),
                                block(&window, sf::Vector2f(550.0f, 80.0f)),
                                block(&window, sf::Vector2f(650.0f, 80.0f)),
                                block(&window, sf::Vector2f(750.0f, 80.0f)),
                                block(&window, sf::Vector2f(50.0f, 110.0f)),
                                block(&window, sf::Vector2f(150.0f, 110.0f)),
                                block(&window, sf::Vector2f(250.0f, 110.0f)),
                                block(&window, sf::Vector2f(350.0f, 110.0f)),
                                block(&window, sf::Vector2f(450.0f, 110.0f)),
                                block(&window, sf::Vector2f(550.0f, 110.0f)),
                                block(&window, sf::Vector2f(650.0f, 110.0f)),
                                block(&window, sf::Vector2f(750.0f, 110.0f)),
                                block(&window, sf::Vector2f(50.0f, 140.0f)),
                                block(&window, sf::Vector2f(150.0f, 140.0f)),
                                block(&window, sf::Vector2f(250.0f, 140.0f)),
                                block(&window, sf::Vector2f(350.0f, 140.0f)),
                                block(&window, sf::Vector2f(450.0f, 140.0f)),
                                block(&window, sf::Vector2f(550.0f, 140.0f)),
                                block(&window, sf::Vector2f(650.0f, 140.0f)),
                                block(&window, sf::Vector2f(750.0f, 140.0f))};

    sf::RectangleShape game_area_shape = sf::RectangleShape();
    game_area_shape.setSize(sf::Vector2f(block_breaker_area.x_stop - block_breaker_area.x_start, block_breaker_area.y_stop - block_breaker_area.y_start));
    game_area_shape.setFillColor(sf::Color::Black);
    game_area_shape.setPosition(sf::Vector2f(block_breaker_area.x_start, block_breaker_area.y_start));

    game_states game_state = game_states::during_game;

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
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

        if (game_state == game_states::during_game)
        {
            move_objects(clock_obj, paddle_obj, balls, blocks, block_breaker_area, game_state);
            text.setString("BlockBreaker3000");
        }
        else if (game_state == game_states::init_game)
        {
            text.setString("BlockBreaker3000 - You lost :( Press R to reset");
        }
        
        if (game_state == game_states::won_game)
        {
            text.setString("BlockBreaker3000 - You won :) Press R to reset");
        }

        window.clear(sf::Color(166u, 166u, 166u));
        window.draw(game_area_shape);
        paddle_obj.draw(window);
        balls[0].draw();
        if(block::get_number_of_blocks() > 0)
        {
            for(int i =0; i < blocks.size(); ++i)
            {
                blocks[i].draw();
            }
        }
        else
        {
            game_state = game_states::won_game;
        }

        window.draw(text);
        // std::cout << "Number of blocks:" << block::get_number_of_blocks() << "\n";
        window.display();
    }
}