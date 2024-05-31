#include "paddle.hpp"
#include "ball.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

int main()
{
    float window_size_x = 800.0f;
    float window_size_y = 600.0f;
    auto window = sf::RenderWindow{ { static_cast<unsigned int>(window_size_x), static_cast<unsigned int>(window_size_y) }, "BlockBreaker3000" };
    window.setFramerateLimit(144);

    sf::Clock clock_obj = sf::Clock();
    sf::Time time_obj = sf::Time();
    paddle paddle_obj = paddle(window_size_x);
    ball ball_obj = ball(&window, &clock_obj);
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
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        time_obj = clock_obj.getElapsedTime();
        clock_obj.restart();
        position_of_ball = ball_obj.get_position();
        velocity_of_ball = ball_obj.get_velocity_vector();
        
        position_of_ball.x = position_of_ball.x + (velocity_of_ball.x * time_obj.asSeconds());
        position_of_ball.y = position_of_ball.y + (velocity_of_ball.y * time_obj.asSeconds());
        
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

        if (position_of_ball.x < ball_obj.get_ball().getRadius())
        {
            position_of_ball.x = 2 * (ball_obj.get_ball().getRadius()) - position_of_ball.x;
            velocity_of_ball.x *= -1.0;
        }
        else if(position_of_ball.x > (window_size_x - ball_obj.get_ball().getRadius()))
        {
            position_of_ball.x = 2 * (window_size_x - ball_obj.get_ball().getRadius()) - position_of_ball.x;
            velocity_of_ball.x *= -1.0;
        }

        if (position_of_ball.y < ball_obj.get_ball().getRadius())
        {
            position_of_ball.y = 2 * (ball_obj.get_ball().getRadius()) - position_of_ball.y;
            velocity_of_ball.y *= -1.0;
        }
        else if(position_of_ball.y > (window_size_y - ball_obj.get_ball().getRadius()))
        {
            position_of_ball.y = 2 * (window_size_y - ball_obj.get_ball().getRadius()) - position_of_ball.y;
            velocity_of_ball.y *= -1.0;
        }

        // std::cout << "Ball position x , y:" << position_of_ball.x << " ," << position_of_ball.y << "\n";
        // std::cout << "Ball velocity x , y:" << velocity_of_ball.x << " ," << velocity_of_ball.y << "\n";

        ball_obj.set_velocity_vector(velocity_of_ball);
        ball_obj.set_position(position_of_ball);

        window.clear(sf::Color::Black);
        window.draw(paddle_obj.get_paddle());
        // window.draw(ball_obj.get_ball());
        ball_obj.display_ball();
        window.display();
    }
}