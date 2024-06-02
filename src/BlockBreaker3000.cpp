#include "paddle.hpp"
#include "ball.hpp"
#include "physic_of_object.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>



int main()
{
    game_area block_breaker_area = {0.0f, 800.0f, 0.0f, 600.0f};
    float window_size_x = 800.0f;
    float window_size_y = 600.0f;
    auto window = sf::RenderWindow{ { static_cast<unsigned int>(block_breaker_area.x_stop), static_cast<unsigned int>(block_breaker_area.y_stop) }, "BlockBreaker3000" };
    window.setFramerateLimit(144);

    sf::Clock clock_obj = sf::Clock();
    sf::Time time_obj = sf::Time();
    paddle paddle_obj = paddle(&window, &clock_obj, block_breaker_area.x_stop);
    std::vector<ball> balls = {ball(&window, &clock_obj)};
    sf::Vector2f position_of_ball;
    sf::Vector2f velocity_of_ball;


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
                    paddle_obj.move_paddle_left();
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    paddle_obj.move_paddle_right();
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left)
                {
                    paddle_obj.move_paddle_left();
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    paddle_obj.move_paddle_right();
                }
                break;
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        move_objects(paddle_obj, balls, block_breaker_area);

        window.clear(sf::Color::Black);
        // window.draw(paddle_obj.get_paddle());
        paddle_obj.display();
        // window.draw(ball_obj.get_ball());
        balls[0].display();
        window.display();
    }
}