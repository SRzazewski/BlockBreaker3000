#include "paddle.hpp"
#include "ball.hpp"
#include "physic_of_object.hpp"
#include "block.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>



int main()
{
    game_area block_breaker_area = {0.0f, 800.0f, 0.0f, 600.0f};
    auto window = sf::RenderWindow{ { static_cast<unsigned int>(block_breaker_area.x_stop), static_cast<unsigned int>(block_breaker_area.y_stop) }, "BlockBreaker3000" };
    window.setFramerateLimit(144);

    sf::Clock clock_obj = sf::Clock();
    sf::Time time_obj = sf::Time();
    paddle paddle_obj = paddle(&window, &clock_obj, block_breaker_area.x_stop);
    std::vector<ball> balls = {ball(&window, &clock_obj)};
    std::vector<block> blocks = {block(&window, sf::Vector2f(50.0f, 30.0f)),
                                block(&window, sf::Vector2f(150.0f, 30.0f)),
                                block(&window, sf::Vector2f(250.0f, 30.0f)),
                                block(&window, sf::Vector2f(350.0f, 30.0f)),
                                block(&window, sf::Vector2f(450.0f, 30.0f)),
                                block(&window, sf::Vector2f(550.0f, 30.0f)),
                                block(&window, sf::Vector2f(650.0f, 30.0f)),
                                block(&window, sf::Vector2f(750.0f, 30.0f))};

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
                    paddle_obj.set_velocity_vector(sf::Vector2f(-200.0f, 0.0f));
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    paddle_obj.set_velocity_vector(sf::Vector2f(200.0f, 0.0f));
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

        move_objects(paddle_obj, balls, blocks, block_breaker_area);

        window.clear(sf::Color::Black);
        paddle_obj.display();
        balls[0].display();
        for(int i =0; i < blocks.size(); ++i)
        {
            blocks[i].display();
        }
        window.display();
    }
}